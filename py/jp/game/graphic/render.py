from __future__ import annotations

from ..sound.echo import echo_test  # relative import


def render_test() -> None:
    print("render > ", end="")
    echo_test()
