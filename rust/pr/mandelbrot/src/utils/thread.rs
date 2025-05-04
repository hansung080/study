use std::sync::{Arc, mpsc, Mutex};
use std::sync::mpsc::{Receiver, Sender};
use crossbeam::thread::{Scope, ScopedJoinHandle};

pub struct ScopedThreadPool<'env, 'scope> {
    workers: Vec<ScopedWorker<'scope>>,
    sender: Sender<Message<'env>>,
}

impl<'env, 'scope> ScopedThreadPool<'env, 'scope> {
    pub fn new(scope: &'scope Scope<'env>, size: usize, quiet: bool) -> Self {
        assert!(size > 0);
        let (sender, receiver) = mpsc::channel();
        let receiver = Arc::new(Mutex::new(receiver));
        let mut workers = Vec::with_capacity(size);
        for id in 0..size {
            workers.push(ScopedWorker::new(scope, id, Arc::clone(&receiver), quiet));
        }
        ScopedThreadPool { workers, sender }
    }

    pub fn execute<F>(&self, f: F)
    where
        F: FnOnce() + Send + 'env,
    {
        let job = Box::new(f);
        self.sender.send(Message::NewJob(job)).unwrap();
    }
}

impl<'env, 'scope> Drop for ScopedThreadPool<'env, 'scope> {
    fn drop(&mut self) {
        for _ in 0..self.workers.len() {
            self.sender.send(Message::Terminate).unwrap();
        }
        for worker in self.workers.iter_mut() {
            if let Some(thread) = worker.thread.take() {
                thread.join().unwrap();
            }
        }
    }
}

struct ScopedWorker<'scope> {
    #[allow(unused)]
    id: usize,
    thread: Option<ScopedJoinHandle<'scope, ()>>,
}

impl<'scope> ScopedWorker<'scope> {
    fn new<'env>(scope: &'scope Scope<'env>, id: usize, receiver: Arc<Mutex<Receiver<Message<'env>>>>, quiet: bool) -> Self {
        let thread = scope.spawn(move |_| loop {
            let msg = receiver.lock().unwrap().recv().unwrap();
            match msg {
                Message::NewJob(job) => {
                    job();
                },
                Message::Terminate => {
                    if !quiet { println!("thread {id} terminated."); }
                    break;
                },
            }
        });
        ScopedWorker { id, thread: Some(thread) }
    }
}

enum Message<'env> {
    NewJob(Job<'env>),
    Terminate,
}

type Job<'env> = Box<dyn FnOnce() + Send + 'env>;

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn scoped_thread_pool_test() {
        crossbeam::scope(|scope| {
            let count = Arc::new(Mutex::new(0));
            let pool = ScopedThreadPool::new(scope, 4, true);
            for _ in 0..20 {
                let count = Arc::clone(&count);
                pool.execute(move || {
                    let mut count = count.lock().unwrap();
                    *count += 1;
                });
            }
            drop(pool);
            assert_eq!(*count.lock().unwrap(), 20);
        }).unwrap();
    }

    #[test]
    #[should_panic]
    fn scoped_thread_pool_error() {
        crossbeam::scope(|scope| {
            let _ = ScopedThreadPool::new(scope, 0, true);
        }).unwrap();
    }
}