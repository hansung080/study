import time


def elapsed(func):
    def wrapper(*args, **kwargs):
        start = time.time()
        result = func(*args, **kwargs)
        end = time.time()
        print("elapsed time: %fs" % (end - start))
        return result
    return wrapper


def square(n):
    print(f"square({n})")
    return n * n


@elapsed
def power(base, exp):
    print(f"power({base}, {exp})")
    return base ** exp


if __name__ == "__main__":
    from testing import assert_eq

    result1 = elapsed(square)(2)
    result2 = power(2, exp=3)

    assert_eq(result1, 4)
    assert_eq(result2, 8)
