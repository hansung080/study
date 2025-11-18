from __future__ import annotations


def sum_of_multiples(m: int, n: int, end: int) -> int:
    result = 0
    for i in range(min(m, n), end + 1):
        if i % m == 0 or i % n == 0:
            result += i
    return result


if __name__ == "__main__":
    from testing import assert_eq

    cases = [
        (3, 5, 1, 0),
        (3, 5, 3, 3),
        (3, 5, 5, 8),
        (3, 5, 15, 60),
    ]

    for m_, n_, end_, expected in cases:
        assert_eq(sum_of_multiples(m_, n_, end_), expected)
