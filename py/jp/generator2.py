import time


def longtime_job():
    print("job start")
    time.sleep(1)
    return "done"


if __name__ == "__main__":
    # Bad code: 'longtime_job' is called 3 times, even though only the 0-th job is used.
    print("# list comprehension")
    jobs = [longtime_job() for _ in range(3)]
    print(jobs[0])
    print()

    # Good code: 'longtime_job' is called only 1 time because of lazy evaluation.
    print("# generator expression")
    jobs = (longtime_job() for _ in range(3))
    print(next(jobs))
