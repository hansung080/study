from __future__ import annotations

from collections.abc import Iterable, Iterator, Reversible, Sequence


# GOOD: This implements an Iterator manually to demonstrate its internal implementation.
class MyIterator1[T](Iterator[T]):
    def __init__(self, items: Sequence[T]) -> None:
        self._items = items
        self._index = 0

    def __iter__(self) -> Iterator[T]:
        return self

    def __next__(self) -> T:
        if self._index >= len(self._items):
            raise StopIteration
        item = self._items[self._index]
        self._index += 1
        return item


# BETTER: This delegates the Iterator implementation to the built-in iter function.
#         In this case, the MyIterator2 class is essentially unnecessary,
#         and the client code can simply call iter(iterable) directly.
class MyIterator2[T](Iterator[T]):
    def __init__(self, iterable: Iterable[T]) -> None:
        self._it = iter(iterable)

    def __iter__(self) -> Iterator[T]:
        return self

    def __next__(self) -> T:
        return next(self._it)


# GOOD
class ReversedIterator1[T](Iterator[T]):
    def __init__(self, items: Sequence[T]) -> None:
        self._items = items
        self._index = len(items) - 1

    def __iter__(self) -> Iterator[T]:
        return self

    def __next__(self) -> T:
        if self._index < 0:
            raise StopIteration
        item = self._items[self._index]
        self._index -= 1
        return item


# BETTER
class ReversedIterator2[T](Iterator[T]):
    def __init__(self, iterable: Reversible[T]) -> None:
        self._it = reversed(iterable)

    def __iter__(self) -> Iterator[T]:
        return self

    def __next__(self) -> T:
        return next(self._it)


if __name__ == "__main__":
    from testing import assert_eq, assert_raises

    it1 = MyIterator1([1, 2, 3])
    assert_eq(next(it1), 1)
    assert_eq(next(it1), 2)
    assert_eq(next(it1), 3)
    assert_raises(lambda: next(it1), expected=StopIteration)

    it2 = MyIterator2([1, 2, 3])
    assert_eq(next(it2), 1)
    assert_eq(next(it2), 2)
    assert_eq(next(it2), 3)
    assert_raises(lambda: next(it2), expected=StopIteration)

    it3 = ReversedIterator1([1, 2, 3])
    assert_eq(next(it3), 3)
    assert_eq(next(it3), 2)
    assert_eq(next(it3), 1)
    assert_raises(lambda: next(it3), expected=StopIteration)

    it4 = ReversedIterator2([1, 2, 3])
    assert_eq(next(it4), 3)
    assert_eq(next(it4), 2)
    assert_eq(next(it4), 1)
    assert_raises(lambda: next(it4), expected=StopIteration)
