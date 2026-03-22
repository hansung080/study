from __future__ import annotations

import math


def floor_div(m: int, n: int) -> int:
    """Return floor(m / n) for n != 0."""
    return m // n


def ceil_div(m: int, n: int) -> int:
    """Return ceil(m / n) for m >= 0 (not required in Python) and n > 0."""
    return (m + n - 1) // n


def trunc_div(m: int, n: int) -> int:
    """Return trunc(m / n) for n != 0."""
    return int(m / n)


if __name__ == "__main__":
    def test_round_floor_ceil_trunc() -> None:
        cases = [
            (-10, 10, -1, -1, -1, -1),
            (-9,  10, -1, -1,  0,  0),
            (-5,  10,  0, -1,  0,  0),
            (-1,  10,  0, -1,  0,  0),
            (0,   10,  0,  0,  0,  0),
            (1,   10,  0,  0,  1,  0),
            (5,   10,  0,  0,  1,  0),  # round(0.5) == 0 (round half to even)
            (9,   10,  1,  0,  1,  0),
            (10,  10,  1,  1,  1,  1),
        ]

        for m, n, r, f, c, t in cases:
            x = m / n
            assert round(x) == r
            assert math.floor(x) == f
            assert math.ceil(x) == c
            assert math.trunc(x) == t

            assert floor_div(m, n) == f
            assert ceil_div(m, n) == c
            assert trunc_div(m, n) == t

    test_round_floor_ceil_trunc()
