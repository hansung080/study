from __future__ import annotations

import time
from collections.abc import Callable
from functools import wraps
from typing import ParamSpec, TypeAlias, TypeVar

# ParamSpec is not supported in PEP 695 type aliases (TypeVar only, e.g. type Func[T, R] = Callable[[T], R]),
# so legacy TypeAlias is required.
_P = ParamSpec("_P")
_R = TypeVar("_R")
_Wrapped: TypeAlias = Callable[_P, _R]
_Wrapper: TypeAlias = Callable[_P, _R]


def clock(wrapped: _Wrapped) -> _Wrapper:
    @wraps(wrapped)
    def wrapper(*args: _P.args, **kwargs: _P.kwargs) -> _R:
        start = time.perf_counter()
        result = wrapped(*args, **kwargs)
        elapsed = time.perf_counter() - start

        name = wrapped.__name__
        arg_list = [repr(arg) for arg in args]
        arg_list.extend(f"{k}={v!r}" for k, v in kwargs.items())
        arg_str = ", ".join(arg_list)

        # print("[%0.8fs] %s(%s) -> %r" % (elapsed, name, arg_str, result))
        print(f"[{elapsed:0.8f}s] {name}({arg_str}) -> {result!r}")
        return result
    return wrapper


class Clock:
    def __init__(self, wrapped: _Wrapped) -> None:
        self._wrapped = wrapped
        wraps(wrapped)(self)

    def __call__(self, *args: _P.args, **kwargs: _P.kwargs) -> _R:
        start = time.perf_counter()
        result = self._wrapped(*args, **kwargs)
        elapsed = time.perf_counter() - start

        name = self._wrapped.__name__
        arg_list = [repr(arg) for arg in args]
        arg_list.extend(f"{k}={v!r}" for k, v in kwargs.items())
        arg_str = ", ".join(arg_list)

        print(f"[{elapsed:0.8f}s] {name}({arg_str}) -> {result!r}")
        return result


DEFAULT_FMT = "[{elapsed:0.8f}s] {name}({args}) -> {result}"


def clock_with(*, fmt: str = DEFAULT_FMT) -> Callable[[_Wrapped], _Wrapper]:
    def decorator(wrapped: _Wrapped) -> _Wrapper:
        @wraps(wrapped)
        def wrapper(*args: _P.args, **kwargs: _P.kwargs) -> _R:
            start = time.perf_counter()
            result = wrapped(*args, **kwargs)
            elapsed = time.perf_counter() - start

            name = wrapped.__name__
            arg_list = [repr(arg) for arg in args]
            arg_list.extend(f"{k}={v!r}" for k, v in kwargs.items())
            arg_str = ", ".join(arg_list)

            # print(fmt.format(**locals()))
            print(fmt.format(elapsed=elapsed, name=name, args=arg_str, result=repr(result)))
            return result
        return wrapper
    return decorator


class ClockWith:
    def __init__(self, *, fmt: str = DEFAULT_FMT) -> None:
        self._fmt = fmt

    def __call__(self, wrapped: _Wrapped) -> _Wrapper:
        @wraps(wrapped)
        def wrapper(*args: _P.args, **kwargs: _P.kwargs) -> _R:
            start = time.perf_counter()
            result = wrapped(*args, **kwargs)
            elapsed = time.perf_counter() - start

            name = wrapped.__name__
            arg_list = [repr(arg) for arg in args]
            arg_list.extend(f"{k}={v!r}" for k, v in kwargs.items())
            arg_str = ", ".join(arg_list)

            print(self._fmt.format(elapsed=elapsed, name=name, args=arg_str, result=repr(result)))
            return result
        return wrapper


def clock_both(wrapped: _Wrapped | None = None, *, fmt: str = DEFAULT_FMT) -> Callable[[_Wrapped], _Wrapper] | _Wrapper:
    def decorator(wrapped_: _Wrapped) -> _Wrapper:
        @wraps(wrapped_)
        def wrapper(*args: _P.args, **kwargs: _P.kwargs) -> _R:
            start = time.perf_counter()
            result = wrapped_(*args, **kwargs)
            elapsed = time.perf_counter() - start

            name = wrapped_.__name__
            arg_list = [repr(arg) for arg in args]
            arg_list.extend(f"{k}={v!r}" for k, v in kwargs.items())
            arg_str = ", ".join(arg_list)

            print(fmt.format(elapsed=elapsed, name=name, args=arg_str, result=repr(result)))
            return result
        return wrapper

    if wrapped is None:
        return decorator
    return decorator(wrapped)


class ClockBoth:
    def __init__(self, wrapped: _Wrapped | None = None, *, fmt: str = DEFAULT_FMT) -> None:
        self._wrapped = wrapped
        self._fmt = fmt
        if wrapped is not None:
            wraps(wrapped)(self)

    def __call__(self, *args: _P.args, **kwargs: _P.kwargs) -> _Wrapper | _R:
        if self._wrapped is None:
            wrapped = args[0]
        else:
            wrapped = self._wrapped

        @wraps(wrapped)
        def wrapper(*args_: _P.args, **kwargs_: _P.kwargs) -> _R:
            start = time.perf_counter()
            result = wrapped(*args_, **kwargs_)
            elapsed = time.perf_counter() - start

            name = wrapped.__name__
            arg_list = [repr(arg) for arg in args_]
            arg_list.extend(f"{k}={v!r}" for k, v in kwargs_.items())
            arg_str = ", ".join(arg_list)

            print(self._fmt.format(elapsed=elapsed, name=name, args=arg_str, result=repr(result)))
            return result

        if self._wrapped is None:
            return wrapper
        return wrapper(*args, **kwargs)


@clock
def snooze(seconds: float) -> None:
    time.sleep(seconds)


@clock
def factorial(n: int) -> int:
    return 1 if n < 2 else n * factorial(n - 1)


@clock
def pow1(base: float, exp: float) -> float:
    return base ** exp


@Clock
def pow2(base: float, exp: float) -> float:
    return base ** exp


@clock_with()
def pow3(base: float, exp: float) -> float:
    return base ** exp


@clock_with(fmt="{name}: {elapsed}s")
def pow4(base: float, exp: float) -> float:
    return base ** exp


@ClockWith()
def pow5(base: float, exp: float) -> float:
    return base ** exp


@ClockWith(fmt="{name}: {elapsed}s")
def pow6(base: float, exp: float) -> float:
    return base ** exp


@clock_both
def pow7(base: float, exp: float) -> float:
    return base ** exp


@clock_both(fmt="{name}: {elapsed}s")
def pow8(base: float, exp: float) -> float:
    return base ** exp


@ClockBoth
def pow9(base: float, exp: float) -> float:
    return base ** exp


@ClockBoth(fmt="{name}: {elapsed}s")
def pow10(base: float, exp: float) -> float:
    return base ** exp


if __name__ == "__main__":
    assert snooze.__name__ == "snooze"
    assert factorial.__name__ == "factorial"
    assert pow1.__name__ == "pow1"
    assert pow2.__name__ == "pow2"
    assert pow3.__name__ == "pow3"
    assert pow4.__name__ == "pow4"
    assert pow5.__name__ == "pow5"
    assert pow6.__name__ == "pow6"
    assert pow7.__name__ == "pow7"
    assert pow8.__name__ == "pow8"
    assert pow9.__name__ == "pow9"
    assert pow10.__name__ == "pow10"

    assert snooze(0.123) is None
    # Output: [0.12804812s] snooze(0.123) -> None

    assert factorial(5) == 120
    # Output:
    # [0.00000071s] factorial(1) -> 1
    # [0.00002350s] factorial(2) -> 2
    # [0.00003304s] factorial(3) -> 6
    # [0.00004467s] factorial(4) -> 24
    # [0.00005729s] factorial(5) -> 120

    assert pow1(2, exp=3) == 8
    # Output: [0.00000413s] pow1(2, exp=3) -> 8

    assert pow2(2, exp=3) == 8
    # Output: [0.00000250s] pow2(2, exp=3) -> 8

    assert pow3(2, exp=3) == 8
    # Output: [0.00000179s] pow3(2, exp=3) -> 8

    assert pow4(2, exp=3) == 8
    # Output: pow4: 2.415999915683642e-06s

    assert pow5(2, exp=3) == 8
    # Output: [0.00000237s] pow5(2, exp=3) -> 8

    assert pow6(2, exp=3) == 8
    # Output: pow6: 1.8330028979107738e-06s

    assert pow7(2, exp=3) == 8
    # Output: [0.00000175s] pow7(2, exp=3) -> 8

    assert pow8(2, exp=3) == 8
    # Output: pow8: 1.7080019460991025e-06s

    assert pow9(2, exp=3) == 8
    # Output: [0.00000100s] pow9(2, exp=3) -> 8

    assert pow10(2, exp=3) == 8
    # Output: pow10: 1.2080017768312246e-06s
