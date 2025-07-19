# <<< How to use the relative import >>>
from ..sound.echo import echo_test


def render_test():
    print("render > ", end="")
    echo_test()
