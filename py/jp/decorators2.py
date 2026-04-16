from __future__ import annotations

from collections.abc import Callable
from numbers import Number
from typing import ParamSpec, TypeAlias, TypeVar

_P = ParamSpec("_P")
_R = TypeVar("_R")
_Wrapped: TypeAlias = Callable[_P, _R]
_Wrapper: TypeAlias = Callable[_P, _R]
_T = TypeVar("_T", bound=Number)


def add(*, n: _T) -> Callable[[_Wrapped], _Wrapper]:
    def decorator(wrapped: _Wrapped) -> _Wrapper:
        def wrapper(*args: _P.args, **kwargs: _P.kwargs) -> _R:
            m = wrapped(*args, **kwargs)
            result = m + n
            print(f"add({m}, {n}) -> {result}")
            return result
        return wrapper
    return decorator


def mul(*, n: _T) -> Callable[[_Wrapped], _Wrapper]:
    def decorator(wrapped: _Wrapped) -> _Wrapper:
        def wrapper(*args: _P.args, **kwargs: _P.kwargs) -> _R:
            m = wrapped(*args, **kwargs)
            result = m * n
            print(f"mul({m}, {n}) -> {result}")
            return result
        return wrapper
    return decorator


def pow1(base: _T, exp: _T) -> _T:
    result = base ** exp
    print(f"pow1({base}, {exp}) -> {result}")
    return result


# Composite Function: pow1(base, exp) => mul(add(pow1(base, exp), 1), 2)
pow1 = mul(n=2)(add(n=1)(pow1))


@mul(n=2)
@add(n=1)
def pow2(base: _T, exp: _T) -> _T:
    result = base ** exp
    print(f"pow2({base}, {exp}) -> {result}")
    return result


if __name__ == "__main__":
    from testing import assert_eq

    result1 = pow1(2, exp=3)
    result2 = pow2(2, exp=3)

    assert_eq(result1, 18)
    assert_eq(result2, 18)
