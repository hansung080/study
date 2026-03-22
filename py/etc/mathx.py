from __future__ import annotations

import math


def floor(m: int, n: int) -> int:
    """Return floor(m / n); n != 0."""
    return m // n


def ceil(m: int, n: int) -> int:
    """Return ceil(m / n); m >= 0 (not required in Python), n > 0."""
    return (m + n - 1) // n


def trunc(x: float) -> int:
    """Return trunc(x)."""
    return int(x)


if __name__ == "__main__":
    cases = [
        (-10, 10, -1, -1, -1, -1),
        (-9,  10, -1, -1,  0,  0),
        (-5,  10,  0, -1,  0,  0),
        (-1,  10,  0, -1,  0,  0),
        (0,   10,  0,  0,  0,  0),
        (1,   10,  0,  0,  1,  0),
        (5,   10,  0,  0,  1,  0),  # round(0.5) = 0, because of round half to even
        (9,   10,  1,  0,  1,  0),
        (10,  10,  1,  1,  1,  1),
    ]

    for m_, n_, r, f, c, t in cases:
        x_ = m_ / n_
        assert round(x_) == r
        assert floor(m_, n_) == f
        assert math.floor(x_) == f
        assert ceil(m_, n_) == c
        assert math.ceil(x_) == c
        assert trunc(x_) == t
        assert math.trunc(x_) == t
