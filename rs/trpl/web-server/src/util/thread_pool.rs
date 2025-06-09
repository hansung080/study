use std::sync::{Arc, mpsc, Mutex};
use std::thread;

pub struct ThreadPool {
    workers: Vec<Worker>,
    sender: mpsc::Sender<Message>,
}

impl ThreadPool {
    pub fn new(size: usize) -> Self {
        assert!(size > 0);

        let (sender, receiver) = mpsc::channel();
        let receiver = Arc::new(Mutex::new(receiver));
        let mut workers = Vec::with_capacity(size);
        for id in 0..size {
            workers.push(Worker::new(id, Arc::clone(&receiver)));
        }

        Self { workers, sender }
    }

    pub fn execute<F>(&self, f: F)
    where
        F: FnOnce() + Send + 'static,
    {
        let job = Box::new(f);
        self.sender.send(Message::NewJob(job)).unwrap();
    }
}

impl Drop for ThreadPool {
    fn drop(&mut self) {
        println!("drop thread pool.");
        for _ in 0..self.workers.len() {
            self.sender.send(Message::Terminate).unwrap();
        }

        for worker in self.workers.iter_mut() {
            if let Some(thread) = worker.thread.take() {
                thread.join().unwrap();
                println!("Worker-{} was terminated.", worker.id);
            }
        }
    }
}

struct Worker {
    id: usize,
    thread: Option<thread::JoinHandle<()>>,
}

impl Worker {
    fn new(id: usize, receiver: Arc<Mutex<mpsc::Receiver<Message>>>) -> Self {
        let thread = thread::spawn(move || {
            loop {
                let msg = receiver.lock().unwrap().recv().unwrap();
                match msg {
                    Message::NewJob(job) => {
                        println!("Worker-{id} received Message::NewJob.");
                        job();
                        // NOTE: Using old Rust compilers, the blanket implementation on FnBox could be a workaround to solve the following compile error.
                        //       But, newer Rust compilers allow the above syntax of job(). Thus, the following legacy code has been commented out.
                        // (*job)(); // compile error: cannot move a value of type `dyn FnOnce() + Send`
                        // job.call_box(); // workaround for the above compile error
                    },
                    Message::Terminate => {
                        println!("Worker-{id} received Message::Terminate.");
                        break;
                    }
                }
            }
        });
        Self { id, thread: Some(thread) }
    }
}

enum Message {
    NewJob(Job),
    Terminate,
}

type Job = Box<dyn FnOnce() + Send + 'static>;

// type Job = Box<dyn FnBox + Send + 'static>;
//
// trait FnBox {
//     fn call_box(self: Box<Self>);
// }
//
// impl<F: FnOnce()> FnBox for F {
//     fn call_box(self: Box<Self>) {
//         (*self)()
//     }
// }

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    #[should_panic]
    fn thread_pool_new_panic() {
        let _ = ThreadPool::new(0);
    }

    #[test]
    fn thread_pool_all() {
        let counter = Arc::new(Mutex::new(0));
        let pool = ThreadPool::new(4);
        for _ in 0..50 {
            let counter = Arc::clone(&counter);
            pool.execute(move || {
                let mut counter = counter.lock().unwrap();
                *counter += 1;
            });
        }
        drop(pool);
        assert_eq!(50, *counter.lock().unwrap());
    }
}