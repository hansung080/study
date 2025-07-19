import sys


def assert_eq(left, right, msg=""):
    if left != right:
        print(f"assertion failed: {msg}\n  left: {left}\n right: {right}")
        sys.exit(1)
