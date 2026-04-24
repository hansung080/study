from __future__ import annotations

import time
from collections.abc import Callable
from typing import ParamSpec, TypeAlias, TypeVar

_P = ParamSpec("_P")
_R = TypeVar("_R")
_Wrapped: TypeAlias = Callable[_P, _R]
_Wrapper: TypeAlias = Callable[_P, _R]


def elapsed(wrapped: _Wrapped[_P, _R]) -> _Wrapper[_P, _R]:
    def wrapper(*args: _P.args, **kwargs: _P.kwargs) -> _R:
        start = time.time()
        result = wrapped(*args, **kwargs)
        end = time.time()
        print("elapsed time: %fs" % (end - start))
        return result
    return wrapper


def pow1(base: float, exp: float) -> float:
    result = base ** exp
    print(f"pow1({base}, {exp}) -> {result}")
    return result


# Composite Function: pow1(base, exp) => elapsed(pow1(base, exp))
pow1 = elapsed(pow1)


@elapsed
def pow2(base: float, exp: float) -> float:
    result = base ** exp
    print(f"pow2({base}, {exp}) -> {result}")
    return result


if __name__ == "__main__":
    from testing import assert_eq

    result1 = pow1(2, exp=3)
    result2 = pow2(2, exp=3)

    assert_eq(result1, 8)
    assert_eq(result2, 8)
