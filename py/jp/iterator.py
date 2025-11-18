from __future__ import annotations  # Allows all forward references in this file.

from typing import Generic, Iterator, TypeVar

T = TypeVar("T")


class MyIterator(Generic[T], Iterator[T]):
    def __init__(self, data: list[T]) -> None:
        self.data: list[T] = data
        self.pos: int = 0

    def __iter__(self) -> MyIterator[T]:  # forward reference of MyIterator
        return self

    def __next__(self) -> T:
        if self.pos >= len(self.data):
            raise StopIteration
        item = self.data[self.pos]
        self.pos += 1
        return item


class ReverseIterator(Generic[T], Iterator[T]):
    def __init__(self, data: list[T]) -> None:
        self.data: list[T] = data
        self.pos: int = len(data) - 1

    def __iter__(self) -> ReverseIterator[T]:  # forward reference of ReverseIterator
        return self

    def __next__(self) -> T:
        if self.pos < 0:
            raise StopIteration
        item = self.data[self.pos]
        self.pos -= 1
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
