from __future__ import annotations

from typing import Protocol, TypeVar, runtime_checkable

_T = TypeVar("_T")


@runtime_checkable  # not required
class Repeatable(Protocol):
    def __mul__(self: _T, repeat_count: int) -> _T: ...


_RT = TypeVar("_RT", bound=Repeatable)


def double(x: _RT) -> _RT:
    return x * 2


if __name__ == "__main__":
    from fractions import Fraction
    from vector import Vector

    assert double(1.5) == 3.0
    assert double("A") == "AA"
    assert double([10, 20, 30]) == [10, 20, 30, 10, 20, 30]
    assert double(Fraction(2, 5)) == Fraction(4, 5)
    # assert double(Vector([11.0, 12.0, 13.0])) == Vector([22.0, 24.0, 26.0])

    assert isinstance(1.5, Repeatable) is True
    assert isinstance("A", Repeatable) is True
    assert isinstance([10, 20, 30], Repeatable) is True
    assert isinstance(Fraction(2, 5), Repeatable) is True
    assert isinstance(Vector([11.0, 12.0, 13.0]), Repeatable) is False
