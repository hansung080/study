import sys


def assert_eq(left, right, msg=""):
    if left != right:
        print(f"assert_eq failed: {msg}\n  left: {left}\n right: {right}", file=sys.stderr)
        sys.exit(1)


def assert_err(func, error=Exception, msg=""):
    try:
        func()
    except error:
        return
    print(f"assert_err failed: {msg}", file=sys.stderr)
    sys.exit(1)
