from __future__ import annotations

import time
from collections.abc import Callable
from numbers import Number
from typing import ParamSpec, TypeAlias, TypeVar

P = ParamSpec("P")
R = TypeVar("R")
Func: TypeAlias = Callable[P, R]
Wrapper: TypeAlias = Callable[P, R]


def elapsed(func: Func) -> Wrapper:
    def wrapper(*args: P.args, **kwargs: P.kwargs) -> R:
        start = time.time()
        result = func(*args, **kwargs)
        end = time.time()
        print("elapsed time: %fs" % (end - start))
        return result
    return wrapper


T = TypeVar("T", bound=Number)


def pow1(base: T, exp: T) -> T:
    result = base ** exp
    print(f"pow1({base}, {exp}) -> {result}")
    return result


# Composite Function: pow1(base, exp) => elapsed(pow1(base, exp))
pow1 = elapsed(pow1)


@elapsed
def pow2(base: T, exp: T) -> T:
    result = base ** exp
    print(f"pow2({base}, {exp}) -> {result}")
    return result


if __name__ == "__main__":
    from testing import assert_eq

    result1 = pow1(2, exp=3)
    result2 = pow2(2, exp=3)

    assert_eq(result1, 8)
    assert_eq(result2, 8)
