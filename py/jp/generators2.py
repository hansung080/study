from __future__ import annotations

import time


def longtime_job() -> str:
    print("job start")
    time.sleep(1)
    return "done"


if __name__ == "__main__":
    # BAD: The longtime_job function is called 3 times, even though only the 0-th job is used.
    print("# list comprehension")
    jobs1 = [longtime_job() for _ in range(3)]
    print(jobs1[0])
    print()

    # GOOD: The longtime_job function is called only 1 time, because of lazy evaluation.
    print("# generator expression")
    jobs2 = (longtime_job() for _ in range(3))
    print(next(jobs2))
