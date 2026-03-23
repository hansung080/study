from __future__ import annotations

from collections.abc import Generator
from typing import NamedTuple

# <<< Two Roles of a Generator >>>
#
# 1. Generator-based Iterator
#    - The generator behaves as a producer (data flow: generator -> caller).
#    - Type annotation: Iterator[_YieldT_co] or Generator[_YieldT_co, None, None]
#
# 2. Generator-based Coroutine (Classic Coroutine)
#    - The generator behaves as a consumer (data flow: caller -> generator).
#    - Type annotation: Generator[_YieldT_co, _SendT_contra, _ReturnT_co]
#
# Notes:
# - `yield` is a continuation suspension point or bidirectional rendezvous point.


class Result(NamedTuple):
    count: int
    average: float


class Sentinel:
    def __repr__(self) -> str:
        return f"<Sentinel>"


STOP = Sentinel()  # or STOP = object()


def averager() -> Generator[float, int, None]:
    total = 0.0
    count = 0
    average = 0.0
    while True:
        term = yield average
        total += term
        count += 1
        average = total / count


def averager2(*, verbose: bool = False) -> Generator[None, int | Sentinel, Result]:
    total = 0.0
    count = 0
    average = 0.0
    while True:
        term = yield
        if verbose:
            print(f"received: {term}")
        if term is STOP:
            break
        total += term
        count += 1
        average = total / count
    return Result(count, average)


if __name__ == "__main__":
    # No coroutine return value
    coro_avg = averager()
    assert next(coro_avg) == 0.0  # or assert coro_avg.send(None) == 0.0
    assert coro_avg.send(10) == 10.0
    assert coro_avg.send(30) == 20.0
    assert coro_avg.send(5) == 15.0
    assert coro_avg.send(20) == 16.25
    assert coro_avg.close() is None
    assert coro_avg.close() is None
    try:
        _ = coro_avg.send(5)
        assert False, "StopIteration not raised"
    except StopIteration as e:
        assert e.value is None

    # Get coroutine return value from `StopIteration`
    coro_avg = averager2()
    assert next(coro_avg) is None  # or assert coro_avg.send(None) is None
    assert coro_avg.send(10) is None
    assert coro_avg.send(30) is None
    assert coro_avg.send(5) is None
    assert coro_avg.send(20) is None
    try:
        coro_avg.send(STOP)
        assert False, "StopIteration not raised"
    except StopIteration as e:
        assert e.value == Result(4, 16.25)

    # Get coroutine return value from `yield from`
    def computer() -> Generator[None, int | Sentinel, Result]:
        result = yield from averager2(verbose=True)
        print(f"computed: {result}")
        return result

    coro_comp = computer()
    for v in None, 10, 30, 5, 20, STOP:
        try:
            coro_comp.send(v)
        except StopIteration as e:
            assert e.value == Result(4, 16.25)
