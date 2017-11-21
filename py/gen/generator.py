import time

def gen():
    item = 1
    while True:
        print('send: %d' % item)
        yield item
        time.sleep(2)
        item = item + 1

def main():
    gen_ = gen()
    for item in gen_:
        print('recv: %d' % item)

if __name__ == '__main__':
    main()

