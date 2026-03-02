from __future__ import annotations

from collections.abc import Iterable, Iterator


def sub_gen() -> Iterator[float]:
    yield 1.1
    yield 1.2
    return "done"  # raise StopIteration("done")


# Yielding items from a subgenerator (legacy style)
def gen1() -> Iterator[float]:
    yield 1
    for item in sub_gen():
        yield item
    yield 2


# Yielding items from a subgenerator (modern style)
def gen2() -> Iterator[float]:
    yield 1
    yield from sub_gen()
    yield 2


# Getting the return value from a subgenerator (legacy style)
def gen3() -> Iterator[float]:
    yield 1

    it = sub_gen()
    while True:
        try:
            yield next(it)
        except StopIteration as e:
            result = e.value
            break
    print(f"gen3: {result}")

    yield 2


# Getting the return value from a subgenerator (modern style)
def gen4() -> Iterator[float]:
    yield 1
    result = yield from sub_gen()
    print(f"gen4: {result}")
    yield 2


# Chain implementation (legacy style)
def chain1(*iterables: Iterable[object]) -> Iterator[object]:
    for iterable in iterables:
        for item in iterable:
            yield item


# Chain implementation (modern style)
def chain2(*iterables: Iterable[object]) -> Iterator[object]:
    for iterable in iterables:
        yield from iterable


if __name__ == "__main__":
    assert list(gen1()) == [1, 1.1, 1.2, 2]
    assert list(gen2()) == [1, 1.1, 1.2, 2]
    assert list(gen3()) == [1, 1.1, 1.2, 2]
    assert list(gen4()) == [1, 1.1, 1.2, 2]

    assert list(chain1("ABC", range(3))) == ["A", "B", "C", 0, 1, 2]
    assert list(chain2("ABC", range(3))) == ["A", "B", "C", 0, 1, 2]
