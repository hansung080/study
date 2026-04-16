from __future__ import annotations

from collections.abc import Callable
from numbers import Number
from typing import Generic, TypeVar

# Type Constraints: Generic type parameter `T` allows int or float.
# _T = TypeVar("_T", int, float)

# Type Bound: Generic type parameter `T` allows subtypes of Number.
_T = TypeVar("_T", bound=Number)


# Class
class Mul(Generic[_T]):
    def __init__(self, m: _T) -> None:
        self._m = m

    def __call__(self, n: _T) -> _T:
        return self._m * n


# Closure 1
def mul1(m: _T) -> Callable[[_T], _T]:
    def wrapper(n: _T) -> _T:
        return m * n
    return wrapper


# Closure 2
def mul2(m: _T) -> Callable[[_T], _T]:
    return lambda n: m * n


if __name__ == "__main__":
    from testing import assert_eq

    mul3 = Mul(3)
    mul5 = Mul(5)
    assert_eq(mul3(10), 30)
    assert_eq(mul5(10), 50)

    mul3 = mul1(3)
    mul5 = mul1(5)
    assert_eq(mul3(10), 30)
    assert_eq(mul5(10), 50)

    mul3 = mul2(3)
    mul5 = mul2(5)
    assert_eq(mul3(10), 30)
    assert_eq(mul5(10), 50)
