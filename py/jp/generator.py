# <<< How to create an iterator >>>
# 1. Iterator Class
class SquareIter:
    def __init__(self, start, end):
        self.current = start
        self.end = end

    def __iter__(self):
        return self

    def __next__(self):
        if self.current >= self.end:
            raise StopIteration
        current = self.current
        self.current += 1
        return current * current


# 2. Generator Function
def square_gen(start, end):
    for i in range(start, end):
        yield i * i


# 4. Closure (not an iterator)
def square_closure(start, end):
    def wrapper():
        nonlocal start
        if start >= end:
            raise StopIteration
        current = start
        start += 1
        return current * current
    return wrapper


if __name__ == "__main__":
    from testing import assert_eq, assert_err

    it = SquareIter(1, 4)
    assert_eq(next(it), 1)
    assert_eq(next(it), 4)
    assert_eq(next(it), 9)
    assert_err(lambda: next(it), error=StopIteration)

    gen = square_gen(1, 4)
    assert_eq(next(gen), 1)
    assert_eq(next(gen), 4)
    assert_eq(next(gen), 9)
    assert_err(lambda: next(gen), error=StopIteration)

    # 3. Generator Expression (not a tuple comprehension)
    gen = (i * i for i in range(1, 4))
    assert_eq(next(gen), 1)
    assert_eq(next(gen), 4)
    assert_eq(next(gen), 9)
    assert_err(lambda: next(gen), error=StopIteration)

    closure = square_closure(1, 4)
    assert_eq(closure(), 1)
    assert_eq(closure(), 4)
    assert_eq(closure(), 9)
    assert_err(lambda: closure(), error=StopIteration)

    print("test: generator: ok")
