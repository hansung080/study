from __future__ import annotations

import math

# <<< Integer-division Semantics >>>
# 1. Trunc-division Semantics: C, C++, Java, Kotlin, Go, Rust (truncation toward zero)
# 2. Floor-division Semantics: Python, Ruby
# 3. No Integer Division: JavaScript, TypeScript


def floor_div(m: int, n: int) -> int:
    """Return floor(m / n) for n != 0."""
    return m // n


# Under floor-division semantics, correct for all m, n != 0.
# Under trunc-division semantics, correct only if n > 0 and m >= 0 or n < 0 and m <= 0.
def ceil_div1(m: int, n: int) -> int:
    """Return ceil(m / n) for n != 0."""
    if n > 0:
        return (m + n - 1) // n
    else:
        return (m + n + 1) // n


# Under floor-division semantics, correct for all m, n != 0.
# Under trunc-division semantics, not correct.
def ceil_div2(m: int, n: int) -> int:
    """Return ceil(m / n) for n != 0."""
    return -(-m // n)


def trunc_div(m: int, n: int) -> int:
    """Return trunc(m / n) for n != 0."""
    return int(m / n)


if __name__ == "__main__":
    def test_round_floor_ceil_trunc() -> None:
        cases = [
            (-10,  10, -1, -1, -1, -1),
            (-9,   10, -1, -1,  0,  0),
            (-5,   10,  0, -1,  0,  0),
            (-1,   10,  0, -1,  0,  0),
            (0,    10,  0,  0,  0,  0),
            (1,    10,  0,  0,  1,  0),
            (5,    10,  0,  0,  1,  0),  # round(0.5) == 0 (round half to even)
            (9,    10,  1,  0,  1,  0),
            (10,   10,  1,  1,  1,  1),

            (10,  -10, -1, -1, -1, -1),
            (9,   -10, -1, -1,  0,  0),
            (5,   -10,  0, -1,  0,  0),
            (1,   -10,  0, -1,  0,  0),
            (0,   -10,  0,  0,  0,  0),
            (-1,  -10,  0,  0,  1,  0),
            (-5,  -10,  0,  0,  1,  0),  # round(0.5) == 0 (round half to even)
            (-9,  -10,  1,  0,  1,  0),
            (-10, -10,  1,  1,  1,  1),
        ]

        for m, n, r, f, c, t in cases:
            x = m / n
            assert round(x) == r
            assert math.floor(x) == f
            assert math.ceil(x) == c
            assert math.trunc(x) == t

            assert floor_div(m, n) == f
            assert ceil_div1(m, n) == c
            assert ceil_div2(m, n) == c
            assert trunc_div(m, n) == t

    test_round_floor_ceil_trunc()
