from __future__ import annotations

import time
from functools import wraps
from typing import Callable, ParamSpec, TypeAlias, TypeVar

P = ParamSpec("P")
R = TypeVar("R")
Func: TypeAlias = Callable[P, R]
Wrapper: TypeAlias = Callable[P, R]


def clock(func: Func) -> Wrapper:
    @wraps(func)
    def wrapper(*args: P.args, **kwargs: P.kwargs) -> R:
        start = time.perf_counter()
        result = func(*args, **kwargs)
        elapsed = time.perf_counter() - start
        name = func.__name__
        arg_list = [repr(arg) for arg in args]
        arg_list.extend(f"{k}={v!r}" for k, v in kwargs.items())
        arg_str = ", ".join(arg_list)
        # print("[%0.8fs] %s(%s) -> %r" % (elapsed, name, arg_str, result))
        print(f"[{elapsed:0.8f}s] {name}({arg_str}) -> {result!r}")
        return result
    return wrapper


class Clock:
    def __init__(self, func: Func) -> None:
        self.func = func
        wraps(func)(self)

    def __call__(self, *args: P.args, **kwargs: P.kwargs) -> R:
        start = time.perf_counter()
        result = self.func(*args, **kwargs)
        elapsed = time.perf_counter() - start
        name = self.func.__name__
        arg_list = [repr(arg) for arg in args]
        arg_list.extend(f"{k}={v!r}" for k, v in kwargs.items())
        arg_str = ", ".join(arg_list)
        print(f"[{elapsed:0.8f}s] {name}({arg_str}) -> {result!r}")
        return result


DEFAULT_FMT = "[{elapsed:0.8f}s] {name}({args}) -> {result}"


def clock_with(fmt: str = DEFAULT_FMT) -> Callable[[Func], Wrapper]:
    def decorator(func: Func) -> Wrapper:
        @wraps(func)
        def wrapper(*args_: P.args, **kwargs: P.kwargs) -> R:
            start = time.perf_counter()
            result_ = func(*args_, **kwargs)
            elapsed = time.perf_counter() - start
            name = func.__name__
            arg_list = [repr(arg) for arg in args_]
            arg_list.extend(f"{k}={v!r}" for k, v in kwargs.items())
            args = ", ".join(arg_list)
            result = repr(result_)
            print(fmt.format(**locals()))
            return result_
        return wrapper
    return decorator


class ClockWith:
    def __init__(self, fmt: str = DEFAULT_FMT) -> None:
        self.fmt = fmt

    def __call__(self, func: Func) -> Wrapper:
        @wraps(func)
        def wrapper(*args_: P.args, **kwargs: P.kwargs) -> R:
            start = time.perf_counter()
            result_ = func(*args_, **kwargs)
            elapsed = time.perf_counter() - start
            name = func.__name__
            arg_list = [repr(arg) for arg in args_]
            arg_list.extend(f"{k}={v!r}" for k, v in kwargs.items())
            args = ", ".join(arg_list)
            result = repr(result_)
            print(self.fmt.format(**locals()))
            return result_
        return wrapper


@clock
def snooze(seconds: float) -> None:
    time.sleep(seconds)


@clock
def factorial(n: int) -> int:
    return 1 if n < 2 else n * factorial(n - 1)


@clock
def pow1(base: float, *, exp: float) -> float:
    return base ** exp


@Clock
def pow2(base: float, *, exp: float) -> float:
    return base ** exp


@clock_with()
def pow3(base: float, *, exp: float) -> float:
    return base ** exp


@clock_with("{name}: {elapsed}s")
def pow4(base: float, *, exp: float) -> float:
    return base ** exp


@ClockWith()
def pow5(base: float, *, exp: float) -> float:
    return base ** exp


@ClockWith("{name}: {elapsed}s")
def pow6(base: float, *, exp: float) -> float:
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

    assert snooze(0.123) is None
    # Output: [0.12807571s] snooze(0.123) -> None

    assert factorial(5) == 120
    # Output:
    # [0.00000075s] factorial(1) -> 1
    # [0.00001829s] factorial(2) -> 2
    # [0.00002646s] factorial(3) -> 6
    # [0.00003479s] factorial(4) -> 24
    # [0.00004575s] factorial(5) -> 120

    # NOTE: Ignore this false-positive warning from IntelliJ IDEA:
    #       Parameter(s) unfilled. Possible callees: (base: float, ..., exp: float)
    assert pow1(2, exp=3) == 8
    # Output: [0.00000279s] pow1(2, exp=3) -> 8

    assert pow2(2, exp=3) == 8
    # Output: [0.00000167s] pow2(2, exp=3) -> 8

    assert pow3(2, exp=3) == 8
    # Output: [0.00000075s] pow3(2, exp=3) -> 8

    assert pow4(2, exp=3) == 8
    # Output: pow4: 8.750002962187864e-07s

    assert pow5(2, exp=3) == 8
    # Output: [0.00000075s] pow5(2, exp=3) -> 8

    assert pow6(2, exp=3) == 8
    # Output: pow6: 6.670006769127212e-07s
