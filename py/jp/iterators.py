from __future__ import annotations

from collections.abc import Iterable, Iterator, Reversible, Sequence
from typing import TypeVar

_T = TypeVar("_T")


# GOOD: This implements an `Iterator` manually to demonstrate its internal implementation.
class MyIterator1(Iterator[_T]):
    def __init__(self, items: Sequence[_T]) -> None:
        self._items = items
        self._index = 0

    def __iter__(self) -> Iterator[_T]:
        return self

    def __next__(self) -> _T:
        if self._index >= len(self._items):
            raise StopIteration
        item = self._items[self._index]
        self._index += 1
        return item


# BETTER: This delegates the `Iterator` implementation to the built-in `iter` function.
#         In this case, the `MyIterator2` class is essentially unnecessary,
#         and the client code can simply call `iter(iterable)` directly.
class MyIterator2(Iterator[_T]):
    def __init__(self, iterable: Iterable[_T]) -> None:
        self._it = iter(iterable)

    def __iter__(self) -> Iterator[_T]:
        return self

    def __next__(self) -> _T:
        return next(self._it)


# GOOD
class ReversedIterator1(Iterator[_T]):
    def __init__(self, items: Sequence[_T]) -> None:
        self._items = items
        self._index = len(items) - 1

    def __iter__(self) -> Iterator[_T]:
        return self

    def __next__(self) -> _T:
        if self._index < 0:
            raise StopIteration
        item = self._items[self._index]
        self._index -= 1
        return item


# BETTER
class ReversedIterator2(Iterator[_T]):
    def __init__(self, iterable: Reversible[_T]) -> None:
        self._it = reversed(iterable)

    def __iter__(self) -> Iterator[_T]:
        return self

    def __next__(self) -> _T:
        return next(self._it)


if __name__ == "__main__":
    from testing import assert_eq, assert_raises

    it = MyIterator1([1, 2, 3])
    assert_eq(next(it), 1)
    assert_eq(next(it), 2)
    assert_eq(next(it), 3)
    assert_raises(lambda: next(it), expected=StopIteration)

    it = MyIterator2([1, 2, 3])
    assert_eq(next(it), 1)
    assert_eq(next(it), 2)
    assert_eq(next(it), 3)
    assert_raises(lambda: next(it), expected=StopIteration)

    it = ReversedIterator1([1, 2, 3])
    assert_eq(next(it), 3)
    assert_eq(next(it), 2)
    assert_eq(next(it), 1)
    assert_raises(lambda: next(it), expected=StopIteration)

    it = ReversedIterator2([1, 2, 3])
    assert_eq(next(it), 3)
    assert_eq(next(it), 2)
    assert_eq(next(it), 1)
    assert_raises(lambda: next(it), expected=StopIteration)
