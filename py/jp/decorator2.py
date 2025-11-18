from __future__ import annotations

from numbers import Number
from typing import Callable, ParamSpec, TypeAlias, TypeVar

T = TypeVar("T", bound=Number)
P = ParamSpec("P")
R = TypeVar("R")
Func: TypeAlias = Callable[P, R]
Wrapper: TypeAlias = Callable[P, R]


def add(n: T) -> Callable[[Func], Wrapper]:
    def decorator(func: Func) -> Wrapper:
        def wrapper(*args: P.args, **kwargs: P.kwargs) -> R:
            m = func(*args, **kwargs)
            result = m + n
            print(f"add({m}, {n}) -> {result}")
            return result
        return wrapper
    return decorator


def mul(n: T) -> Callable[[Func], Wrapper]:
    def decorator(func: Func) -> Wrapper:
        def wrapper(*args: P.args, **kwargs: P.kwargs) -> R:
            m = func(*args, **kwargs)
            result = m * n
            print(f"mul({m}, {n}) -> {result}")
            return result
        return wrapper
    return decorator


def pow1(base: T, exp: T) -> T:
    result = base ** exp
    print(f"pow1({base}, {exp}) -> {result}")
    return result


# Composite Function: pow1(base, exp) => mul(add(pow1(base, exp), 1), 2)
pow1 = mul(n=2)(add(n=1)(pow1))


@mul(n=2)
@add(n=1)
def pow2(base: T, exp: T) -> T:
    result = base ** exp
    print(f"pow2({base}, {exp}) -> {result}")
    return result


if __name__ == "__main__":
    from testing import assert_eq

    result1 = pow1(2, exp=3)
    result2 = pow2(2, exp=3)

    assert_eq(result1, 18)
    assert_eq(result2, 18)
