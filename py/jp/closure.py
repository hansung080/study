class Mul:
    def __init__(self, m):
        self.m = m

    def __call__(self, n):
        return self.m * n


def mul(m):
    def wrapper(n):
        return m * n
    return wrapper


def mul2(m):
    return lambda n: m * n


if __name__ == "__main__":
    from testing import assert_eq

    mul3 = Mul(3)
    mul5 = Mul(5)
    assert_eq(mul3(10), 30)
    assert_eq(mul5(10), 50)

    mul3 = mul(3)
    mul5 = mul(5)
    assert_eq(mul3(10), 30)
    assert_eq(mul5(10), 50)

    mul3 = mul2(3)
    mul5 = mul2(5)
    assert_eq(mul3(10), 30)
    assert_eq(mul5(10), 50)

    print("test: closure: ok")
