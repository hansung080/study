from __future__ import annotations  # This allows all forward references in this file.

from collections.abc import Iterator
from typing import Generic, TypeVar

T = TypeVar("T")


class MyIterator(Generic[T], Iterator[T]):
    def __init__(self, data: list[T]) -> None:
        self._data = data
        self._pos = 0

    def __iter__(self) -> MyIterator[T]:  # A forward reference of `MyIterator`
        return self

    def __next__(self) -> T:
        if self._pos >= len(self._data):
            raise StopIteration
        item = self._data[self._pos]
        self._pos += 1
        return item


class ReverseIterator(Generic[T], Iterator[T]):
    def __init__(self, data: list[T]) -> None:
        self._data = data
        self._pos = len(data) - 1

    def __iter__(self) -> ReverseIterator[T]:  # A forward reference of `ReverseIterator`
        return self

    def __next__(self) -> T:
        if self._pos < 0:
            raise StopIteration
        item = self._data[self._pos]
        self._pos -= 1
        return item


if __name__ == "__main__":
    from testing import assert_eq, assert_raises

    it = MyIterator([1, 2, 3])
    assert_eq(next(it), 1)
    assert_eq(next(it), 2)
    assert_eq(next(it), 3)
    assert_raises(lambda: next(it), expected=StopIteration)

    it = ReverseIterator([1, 2, 3])
    assert_eq(next(it), 3)
    assert_eq(next(it), 2)
    assert_eq(next(it), 1)
    assert_raises(lambda: next(it), expected=StopIteration)
