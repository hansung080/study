import threading, queue
import time

def washer(dishes, dish_queue):
    for dish in dishes:
        print('washing', dish, 'dish')
        dish_queue.put(dish)
        time.sleep(2)

def dryer(dish_queue):
    while True:
        dish = dish_queue.get()
        print('drying', dish, 'dish')
        dish_queue.task_done()

def main():
    dish_queue = queue.Queue()
    dryer_thread = threading.Thread(target=dryer, args=(dish_queue,))
    dryer_thread.start()
    
    dishes = ['salad', 'bread', 'entree', 'dessert']
    washer(dishes, dish_queue)
    dish_queue.join()

if __name__ == '__main__':
    main()

