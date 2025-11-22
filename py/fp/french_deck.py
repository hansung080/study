from __future__ import annotations

# from collections import namedtuple
# from typing import Iterator
from typing import NamedTuple

# Legacy-style named tuple definition
# Card = namedtuple("Card", ["rank", "suit"])


# Modern-style named tuple definition
class Card(NamedTuple):
    rank: str
    suit: str


class FrenchDeck:
    ranks: list[str] = [str(n) for n in range(2, 11)] + list("JQKA")
    suits: list[str] = "spades diamonds clubs hearts".split()

    def __init__(self) -> None:
        self._cards: list[Card] = [Card(rank, suit) for suit in self.suits for rank in self.ranks]

    def __len__(self) -> int:
        return len(self._cards)

    def __getitem__(self, position: int) -> Card:
        return self._cards[position]

    # def __iter__(self) -> Iterator[Card]:
    #     return iter(self._cards)


if __name__ == "__main__":
    from random import choice

    beer_card = Card("7", "diamonds")
    assert str(beer_card) == "Card(rank='7', suit='diamonds')"

    deck = FrenchDeck()
    assert len(deck) == 52

    assert deck[0] == Card("2", "spades")
    assert deck[-1] == Card("A", "hearts")

    print("# Random Choice")
    print(choice(deck))
    print(choice(deck))
    print(choice(deck))

    assert deck[:3] == [
        Card("2", "spades"),
        Card("3", "spades"),
        Card("4", "spades"),
    ]
    assert deck[12::13] == [
        Card("A", "spades"),
        Card("A", "diamonds"),
        Card("A", "clubs"),
        Card("A", "hearts"),
    ]

    print("\n# Iteration")
    for card in deck:
        print(card)

    print("\n# Reversed Iteration")
    for card in reversed(deck):
        print(card)

    assert Card("Q", "hearts") in deck
    assert Card("7", "beasts") not in deck

    suit_values = dict(spades=3, hearts=2, diamonds=1, clubs=0)

    def spades_high(card_: Card) -> int:
        rank_value = FrenchDeck.ranks.index(card_.rank)
        return rank_value * len(suit_values) + suit_values[card_.suit]

    print("\n# Sort by Spades High")
    # `deck` is a sequence-like iterable object by implementing __len__ and __getitem__.
    # However, the type checker doesn't know it and throws the following warning.
    # To fix the warning, FrenchDeck needs to implement __iter__.
    for card in sorted(deck, key=spades_high):
        print(card)
