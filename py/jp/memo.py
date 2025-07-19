import os
import sys

if len(sys.argv) < 2:
    print("usage: python3 memo.py <mode> [memos]...", file=sys.stderr)
    print("  mode: -a: append", file=sys.stderr)
    print("        -r: read", file=sys.stderr)
    print("        -d: delete", file=sys.stderr)
    sys.exit(1)

FILE = "memo.txt"
mode = sys.argv[1]

if mode == "-a":
    f = open(FILE, "a")
    for memo in sys.argv[2:]:
        f.write(memo)
        f.write("\n")
    f.close()
elif mode == "-r":
    try:
        f = open(FILE)
        memo = f.read()
        f.close()
        print(memo, end="")
    except FileNotFoundError:
        print(f"error: file not found: '{FILE}'", file=sys.stderr)
        sys.exit(1)
    except OSError as e:
        print(f"error: os: {e}", file=sys.stderr)
        sys.exit(1)
elif mode == "-d":
    if os.path.exists(FILE):
        os.remove(FILE)
else:
    print(f"error: invalid mode: {mode}", file=sys.stderr)
    sys.exit(1)
