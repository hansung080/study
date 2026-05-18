from __future__ import annotations

# --- All Uses of __init__.py ---
# Use 1. Defining package-level items such as variables, functions, etc
VERSION = 3.5


def print_version_info() -> None:
    print(f"The version of this game is {VERSION}.")


# Use 2. Importing items in a package in advance
from .graphic.render import render_test

# Use 3. Writing the package initialization code
print("Initializing game...")

# Use 4. Defining the __all__ variable (See game/sound/__init__.py)
