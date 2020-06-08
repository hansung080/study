import threading
import time

count = 10
lock = threading.Lock()

class Worker(threading.Thread):
    def __init__(self, name):
        threading.Thread.__init__(self)
        self.name = name
        self.fixed = 0
    
    def run(self):
        global count
        while True:
            lock.acquire()
            if count > 0:
                count -= 1
                lock.release()
                self.fixed += 1
                time.sleep(0.1)
            else:
                lock.release()
                break

def main():
    workers = []
    for name in ['worker1', 'worker2', 'worker3']:
        worker = Worker(name)
        workers.append(worker)
        worker.start()
    
    for worker in workers:
        worker.join()
        print('%s -> fixed: %s' % (worker.name, worker.fixed))

if __name__ == '__main__':
    main()

