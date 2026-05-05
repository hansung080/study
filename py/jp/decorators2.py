from __future__ import annotations

from collections.abc import Callable

from typingx import SupportsAdd, SupportsMul

# --- Modern-style Generics and Type Aliases (PEP 695) ---
type _Wrapped[**P, R] = Callable[P, R]
type _Wrapper[**P, R] = Callable[P, R]


def add[**P, R: SupportsAdd](*, n: float) -> Callable[[_Wrapped[P, R]], _Wrapper[P, R]]:
    def decorator(wrapped: _Wrapped[P, R]) -> _Wrapper[P, R]:
        def wrapper(*args: P.args, **kwargs: P.kwargs) -> R:
            m = wrapped(*args, **kwargs)
            result = m + n
            print(f"add({m}, {n}) -> {result}")
            return result
        return wrapper
    return decorator


def mul[**P, R: SupportsMul](*, n: float) -> Callable[[_Wrapped[P, R]], _Wrapper[P, R]]:
    def decorator(wrapped: _Wrapped[P, R]) -> _Wrapper[P, R]:
        def wrapper(*args: P.args, **kwargs: P.kwargs) -> R:
            m = wrapped(*args, **kwargs)
            result = m * n
            print(f"mul({m}, {n}) -> {result}")
            return result
        return wrapper
    return decorator


def pow1(base: float, exp: float) -> float:
    result = base ** exp
    print(f"pow1({base}, {exp}) -> {result}")
    return result


# Composite Function: pow1(base, exp) => mul(add(pow1(base, exp), 1), 2)
pow1 = mul(n=2)(add(n=1)(pow1))


@mul(n=2)
@add(n=1)
def pow2(base: float, exp: float) -> float:
    result = base ** exp
    print(f"pow2({base}, {exp}) -> {result}")
    return result


if __name__ == "__main__":
    from testing import assert_eq

    result1 = pow1(2, exp=3)
    result2 = pow2(2, exp=3)

    assert_eq(result1, 18)
    assert_eq(result2, 18)
