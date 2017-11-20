import threading

def t_func(what):
    whoami(what)

def whoami(what):
    print("Thread %s says: %s" % (threading.current_thread(), what))

def main():
    whoami("I'm the main thread.")
    for i in range(4):
        t = threading.Thread(target=t_func, args=("I'm the %dth worker thread." % (i+1),))
        t.start()

if __name__ == '__main__':
    main()

