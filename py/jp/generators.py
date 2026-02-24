from __future__ import annotations  # Allows all forward references in this file.

from typing import Callable, Iterator


# <<< How to create an iterator >>>
# 1. Iterator Class
class SquareIter(Iterator[int]):
    def __init__(self, start: int, end: int) -> None:
        self.current: int = start
        self.end: int = end

    def __iter__(self) -> SquareIter:  # forward reference of SquareIter
        return self

    def __next__(self) -> int:
        if self.current >= self.end:
            raise StopIteration
        current = self.current
        self.current += 1
        return current * current


# 2. Generator Function
def square_gen(start: int, end: int) -> Iterator[int]:
    for i in range(start, end):
        yield i * i


# 4. Closure (not an iterator)
def square_closure(start: int, end: int) -> Callable[[], int]:
    def wrapper() -> int:
        nonlocal start
        if start >= end:
            raise StopIteration
        current = start
        start += 1
        return current * current
    return wrapper


if __name__ == "__main__":
    from testing import assert_eq, assert_raises

    it = SquareIter(1, 4)
    assert_eq(next(it), 1)
    assert_eq(next(it), 4)
    assert_eq(next(it), 9)
    assert_raises(lambda: next(it), expected=StopIteration)

    gen1 = square_gen(1, 4)
    assert_eq(next(gen1), 1)
    assert_eq(next(gen1), 4)
    assert_eq(next(gen1), 9)
    assert_raises(lambda: next(gen1), expected=StopIteration)

    # 3. Generator Expression (not a tuple comprehension)
    gen2 = (i * i for i in range(1, 4))
    assert_eq(next(gen2), 1)
    assert_eq(next(gen2), 4)
    assert_eq(next(gen2), 9)
    assert_raises(lambda: next(gen2), expected=StopIteration)

    closure = square_closure(1, 4)
    assert_eq(closure(), 1)
    assert_eq(closure(), 4)
    assert_eq(closure(), 9)
    assert_raises(lambda: closure(), expected=StopIteration)
