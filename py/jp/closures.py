from __future__ import annotations

from collections.abc import Callable
from decimal import Decimal
from fractions import Fraction
from typing import Generic, TypeVar

from typingx import SupportsMul

# Type Bound: _T1 is restricted to SupportsMul and its subtypes.
# - numbers.Number is intended for runtime checks, not static typing, due to ABC.register-based virtual subclassing.
_T1 = TypeVar("_T1", bound=SupportsMul)

# Type Constraints: _T2 is restricted to int, float, complex, Decimal, or Fraction.
# - bool is a numeric type, but does not satisfy T * T -> T (bool * bool -> int).
_T2 = TypeVar("_T2", int, float, complex, Decimal, Fraction)


# Generic Class 1 (legacy bounded TypeVar)
class Mul1(Generic[_T1]):
    def __init__(self, m: _T1) -> None:
        self._m: _T1 = m

    def __call__(self, n: _T1) -> _T1:
        return self._m * n


# Generic Class 2 (legacy constrained TypeVar)
class Mul2(Generic[_T2]):
    def __init__(self, m: _T2) -> None:
        self._m: _T2 = m

    def __call__(self, n: _T2) -> _T2:
        return self._m * n


# Generic Class 3 (PEP 695 bounded TypeVar)
class Mul3[T: SupportsMul]:
    def __init__(self, m: T) -> None:
        self._m: T = m

    def __call__(self, n: T) -> T:
        return self._m * n


# Generic Class 4 (PEP 695 constrained TypeVar)
class Mul4[T: (int, float, complex, Decimal, Fraction)]:
    def __init__(self, m: T) -> None:
        self._m: T = m

    def __call__(self, n: T) -> T:
        return self._m * n


# Generic Function with Closure 1 (legacy bounded TypeVar)
def mul1(m: _T1) -> Callable[[_T1], _T1]:
    def wrapper(n: _T1) -> _T1:
        return m * n
    return wrapper


# Generic Function with Closure 2 (legacy constrained TypeVar)
def mul2(m: _T2) -> Callable[[_T2], _T2]:
    def wrapper(n: _T2) -> _T2:
        return m * n
    return wrapper


# Generic Function with Closure 3 (PEP 695 bounded TypeVar)
def mul3[T: SupportsMul](m: T) -> Callable[[T], T]:
    return lambda n: m * n


# Generic Function with Closure 4 (PEP 695 constrained TypeVar)
def mul4[T: (int, float, complex, Decimal, Fraction)](m: T) -> Callable[[T], T]:
    return lambda n: m * n


if __name__ == "__main__":
    from testing import assert_eq

    mul_two1 = Mul1(2)
    mul_two2 = Mul2(2)
    mul_two3 = Mul3(2)
    mul_two4 = Mul4(2)
    mul_two5 = mul1(2)
    mul_two6 = mul2(2)
    mul_two7 = mul3(2)
    mul_two8 = mul4(2)

    assert_eq(mul_two1(10), 20)
    assert_eq(mul_two2(10), 20)
    assert_eq(mul_two3(10), 20)
    assert_eq(mul_two4(10), 20)
    assert_eq(mul_two5(10), 20)
    assert_eq(mul_two6(10), 20)
    assert_eq(mul_two7(10), 20)
    assert_eq(mul_two8(10), 20)
