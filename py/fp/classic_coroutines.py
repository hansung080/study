from __future__ import annotations

from collections.abc import Generator
from enum import Enum, auto
from typing import NamedTuple

# --- Two Roles of a Generator ---
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
    count: int  # type: ignore
    average: float


# A regular sentinel object is not a singleton type, so it does not support value-based narrowing by type checkers.
# Use type-based narrowing instead.
# (value-based narrowing: `if term is STOP:`, type-based narrowing: `if isinstance(term, StopType):`)
# ```
# class StopType:
#     def __repr__(self) -> str:
#         return "<STOP>"
#
#
# STOP = StopType()  # or STOP = object()
# ```


# An Enum-based sentinel object is a singleton type, so it supports value-based narrowing by type checkers.
class StopType(Enum):
    STOP = auto()

    def __repr__(self) -> str:
        return "<STOP>"


STOP = StopType.STOP


def averager1() -> Generator[float, int, None]:
    total = 0.0
    count = 0
    average = 0.0
    while True:
        term = yield average
        total += term
        count += 1
        average = total / count


def averager2(*, verbose: bool = False) -> Generator[None, int | StopType, Result]:
    total = 0.0
    count = 0
    average = 0.0
    while True:
        term = yield
        if verbose:
            print(f"received: {term!r}")
        if term is STOP:
            break
        total += term
        count += 1
        average = total / count
    return Result(count, average)


if __name__ == "__main__":
    # No coroutine return value
    coro_avg1 = averager1()
    assert next(coro_avg1) == 0.0  # `coro_avg1.send(None)` can be used instead of `next(coro_avg1)`.
    assert coro_avg1.send(10) == 10.0
    assert coro_avg1.send(30) == 20.0
    assert coro_avg1.send(5) == 15.0
    assert coro_avg1.send(20) == 16.25
    assert coro_avg1.close() is None
    assert coro_avg1.close() is None
    try:
        _ = coro_avg1.send(5)
        assert False, "StopIteration not raised"
    except StopIteration as e:
        assert e.value is None

    # Get coroutine return value from `StopIteration`
    coro_avg2 = averager2()
    assert next(coro_avg2) is None
    assert coro_avg2.send(10) is None
    assert coro_avg2.send(30) is None
    assert coro_avg2.send(5) is None
    assert coro_avg2.send(20) is None
    try:
        coro_avg2.send(STOP)
        assert False, "StopIteration not raised"
    except StopIteration as e:
        assert e.value == Result(4, 16.25)

    # Get coroutine return value from `yield from`
    def computer() -> Generator[None, int | StopType, Result]:
        result = yield from averager2(verbose=True)
        print(f"computed: {result!r}")
        return result

    coro_comp = computer()
    next(coro_comp)
    for v in 10, 30, 5, 20, STOP:
        try:
            coro_comp.send(v)
        except StopIteration as e:
            assert e.value == Result(4, 16.25)
