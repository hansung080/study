from __future__ import annotations

from collections.abc import Callable, Iterator


# --- Iterator Implementation Patterns ---
# Pattern 1. Iterator Class
class SquareIter(Iterator[int]):
    def __init__(self, start: int, stop: int) -> None:
        self._current = start
        self._stop = stop

    def __iter__(self) -> Iterator[int]:
        return self

    def __next__(self) -> int:
        if self._current >= self._stop:
            raise StopIteration
        current = self._current
        self._current += 1
        return current * current


# Pattern 2. Generator Function
def square_gen(start: int, stop: int) -> Iterator[int]:
    for i in range(start, stop):
        yield i * i


# Pattern 4. Closure (not an iterator)
def square_closure(start: int, stop: int) -> Callable[[], int]:
    def wrapper() -> int:
        nonlocal start
        if start >= stop:
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

    # Pattern 3. Generator Expression (not a tuple comprehension)
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
