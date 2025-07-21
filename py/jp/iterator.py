class MyIterator:
    def __init__(self, data):
        self.data = data
        self.pos = 0

    def __iter__(self):
        return self

    def __next__(self):
        if self.pos >= len(self.data):
            raise StopIteration
        item = self.data[self.pos]
        self.pos += 1
        return item


class ReverseIterator:
    def __init__(self, data):
        self.data = data
        self.pos = len(data) - 1

    def __iter__(self):
        return self

    def __next__(self):
        if self.pos < 0:
            raise StopIteration
        item = self.data[self.pos]
        self.pos -= 1
        return item


if __name__ == "__main__":
    from testing import assert_eq, assert_err

    it = MyIterator([1, 2, 3])
    assert_eq(next(it), 1)
    assert_eq(next(it), 2)
    assert_eq(next(it), 3)
    assert_err(lambda: next(it), error=StopIteration)

    it = ReverseIterator([1, 2, 3])
    assert_eq(next(it), 3)
    assert_eq(next(it), 2)
    assert_eq(next(it), 1)
    assert_err(lambda: next(it), error=StopIteration)

    print("test: iterator: ok")
