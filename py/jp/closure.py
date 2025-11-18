from __future__ import annotations

from numbers import Number
from typing import Callable, Generic, TypeVar

# Type Constraints: Generic type parameter `T` allows int or float.
# T = TypeVar("T", int, float)

# Type Bound: Generic type parameter `T` allows subtypes of Number.
T = TypeVar("T", bound=Number)


# Class
class Mul(Generic[T]):
    def __init__(self, m: T) -> None:
        self.m: T = m

    def __call__(self, n: T) -> T:
        return self.m * n


# Closure 1
def mul1(m: T) -> Callable[[T], T]:
    def wrapper(n: T) -> T:
        return m * n
    return wrapper


# Closure 2
def mul2(m: T) -> Callable[[T], T]:
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
