def add(n):
    def decorator(func):
        def wrapper(*args, **kwargs):
            m = func(*args, **kwargs)
            result = m + n
            print(f"add({m}, {n}) -> {result}")
            return result
        return wrapper
    return decorator


def mul(n):
    def decorator(func):
        def wrapper(*args, **kwargs):
            m = func(*args, **kwargs)
            result = m * n
            print(f"mul({m}, {n}) -> {result}")
            return result
        return wrapper
    return decorator


def pow1(base, exp):
    result = base ** exp
    print(f"pow1({base}, {exp}) -> {result}")
    return result


# Composite Function: pow1(base, exp) => mul(add(pow1(base, exp), 1), 2)
pow1 = mul(n=2)(add(n=1)(pow1))


@mul(n=2)
@add(n=1)
def pow2(base, exp):
    result = base ** exp
    print(f"pow2({base}, {exp}) -> {result}")
    return result


if __name__ == "__main__":
    from testing import assert_eq

    result1 = pow1(2, exp=3)
    result2 = pow2(2, exp=3)

    assert_eq(result1, 18)
    assert_eq(result2, 18)
