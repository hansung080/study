from __future__ import annotations


def gugu(n: int) -> list[int]:
    result: list[int] = []
    i = 1
    while i < 10:
        result.append(n * i)
        i += 1
    return result


if __name__ == "__main__":
    from testing import assert_eq

    cases = [
        (2, [2, 4, 6, 8, 10, 12, 14, 16, 18]),
        (9, [9, 18, 27, 36, 45, 54, 63, 72, 81]),
    ]

    for _n, expected in cases:
        assert_eq(gugu(_n), expected)
