from __future__ import annotations


def get_total_pages(total_posts: int, posts_per_page: int) -> int:
    if total_posts % posts_per_page == 0:
        return total_posts // posts_per_page
    else:
        return total_posts // posts_per_page + 1


if __name__ == "__main__":
    from testing import assert_eq

    cases = [
        (5, 10, 1),
        (15, 10, 2),
        (25, 10, 3),
        (30, 10, 3),
    ]

    for m, n, expected in cases:
        assert_eq(get_total_pages(m, n), expected)
