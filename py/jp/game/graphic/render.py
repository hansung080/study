from __future__ import annotations

# --- How to Use the Relative Import ---
from ..sound.echo import echo_test


def render_test() -> None:
    print("render > ", end="")
    echo_test()
