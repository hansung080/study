from __future__ import annotations

# --- All Uses of __init__.py ---
# Use 1. Defining package-level items such as variables, functions, etc
VERSION = 3.5


def print_version_info() -> None:
    print(f"The version of this game is {VERSION}.")


# Use 2. Importing items in a package in advance (re-export)
from .graphic.render import render_test as render_test  # explicit re-export

# === Re-export Patterns ===
#
# Implicit Re-export: [attr-defined] error occurs from mypy --strict which enables --no-implicit-reexport.
# ```
# from .graphic.render import render_test
# ```
#
# Explicit Re-export 1: Alias is recommended primarily for explicit re-export.
# ```
# from .graphic.render import render_test as render_test
# ```
#
# Explicit Re-export 2: __all__ is used for public API declaration, wildcard import control, and explicit re-export.
# ```
# from .graphic.render import render_test
#
# __all__ = ["render_test"]
# ```

# Use 3. Writing the package initialization code
print("Initializing game...")

# Use 4. Defining the __all__ variable (See game/sound/__init__.py)
