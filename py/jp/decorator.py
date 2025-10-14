import time


def elapsed(func):
    def wrapper(*args, **kwargs):
        start = time.time()
        result = func(*args, **kwargs)
        end = time.time()
        print("elapsed time: %fs" % (end - start))
        return result
    return wrapper


def pow1(base, exp):
    result = base ** exp
    print(f"pow1({base}, {exp}) -> {result}")
    return result


# Composite Function: pow1(base, exp) => elapsed(pow1(base, exp))
pow1 = elapsed(pow1)


@elapsed
def pow2(base, exp):
    result = base ** exp
    print(f"pow2({base}, {exp}) -> {result}")
    return result


if __name__ == "__main__":
    from testing import assert_eq

    result1 = pow1(2, exp=3)
    result2 = pow2(2, exp=3)

    assert_eq(result1, 8)
    assert_eq(result2, 8)
