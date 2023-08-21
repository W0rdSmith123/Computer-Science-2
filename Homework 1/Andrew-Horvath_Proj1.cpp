#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

// Define the suits and ranks for easy access
enum Suit
{
    Spades,
    Hearts,
    Diamonds,
    Clubs
};
enum Rank
{
    Ace = 1,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King
};

// Define a Card structure
struct Card
{
    Suit suit;
    Rank rank;
};

std::string suitToString(Suit suit)
{
    switch (suit)
    {
    case Spades:
        return "Spades";
    case Hearts:
        return "Hearts";
    case Diamonds:
        return "Diamonds";
    case Clubs:
        return "Clubs";
    default:
        return "Unknown";
    }
}

std::string rankToString(Rank rank)
{
    switch (rank)
    {
    case Ace:
        return "Ace";
    case Two:
        return "Two";
    case Three:
        return "Three";
    case Four:
        return "Four";
    case Five:
        return "Five";
    case Six:
        return "Six";
    case Seven:
        return "Seven";
    case Eight:
        return "Eight";
    case Nine:
        return "Nine";
    case Ten:
        return "Ten";
    case Jack:
        return "Jack";
    case Queen:
        return "Queen";
    case King:
        return "King";
    default:
        return "Unknown";
    }
}

Card dealCard(std::vector<Card> &deck)
{
    int randomIndex = rand() % deck.size();
    Card chosenCard = deck[randomIndex];
    deck.erase(deck.begin() + randomIndex);
    return chosenCard;
}

int main()
{
    // Seed random number generator
    srand(time(0));

    // Create a deck of 52 cards
    std::vector<Card> deck;
    for (int s = Spades; s <= Clubs; s++)
    {
        for (int r = Ace; r <= King; r++)
        {
            deck.push_back({static_cast<Suit>(s), static_cast<Rank>(r)});
        }
    }

    // Deal two cards
    Card playerOneCard = dealCard(deck);
    Card playerTwoCard = dealCard(deck);

    int playerOneScore = 0, playerTwoScore = 0;
    playerOneScore += playerOneCard.rank;
    if (playerOneCard.suit == Hearts)
    {
        playerOneScore += 13;
    }

    playerTwoScore += playerTwoCard.rank;
    if (playerTwoCard.suit == Hearts)
    {
        playerTwoScore += 13;
    }

    // Display cards
    std::cout << "Player One's card: " << rankToString(playerOneCard.rank) << " of " << suitToString(playerOneCard.suit) << std::endl;
    std::cout << "Player Two's card: " << rankToString(playerTwoCard.rank) << " of " << suitToString(playerTwoCard.suit) << std::endl;

    // Determine winner
    if (playerOneScore > playerTwoScore)
    {
        std::cout << "Winner: Player One" << std::endl;
    }
    else if (playerTwoScore > playerOneScore)
    {
        std::cout << "Winner: Player Two" << std::endl;
    }
    else
    {
        std::cout << "It's a tie!" << std::endl;
    }

    return 0;
}
