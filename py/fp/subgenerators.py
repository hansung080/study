from __future__ import annotations

from collections.abc import Generator, Iterable, Iterator


def sub_gen() -> Generator[float, None, str]:
    yield 1.1
    yield 1.2
    return "done"  # raise StopIteration("done")


# Yield items from subgenerator (legacy style: for loop)
def gen1() -> Iterator[float]:
    yield 1
    for item in sub_gen():
        yield item
    yield 2


# Yield items from subgenerator (modern style: yield from)
def gen2() -> Iterator[float]:
    yield 1
    yield from sub_gen()
    yield 2


# Get return value from subgenerator (legacy style: StopIteration)
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


# Get return value from subgenerator (modern style: yield from)
def gen4() -> Iterator[float]:
    yield 1
    result = yield from sub_gen()
    print(f"gen4: {result}")
    yield 2


# Chain implementation (legacy style: for loop)
def chain1(*iterables: Iterable[object]) -> Iterator[object]:
    for iterable in iterables:
        for item in iterable:
            yield item


# Chain implementation (modern style: yield from)
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
