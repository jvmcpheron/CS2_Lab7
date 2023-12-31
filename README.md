# CS2_Lab7

## Introduction
One game that works based on a queue is the game of War in cards.  In War, the deck of cards is shuffled and then the cards are dealt to the two players so each has half of the cards.  The game then consists of a series of turns:

do

   player 1 puts their top card down

   player 2 puts their top card down

   if player 1's card has a higher number (A > K > Q > J > 10 > 9 > 8 > 7 > 6 > 5 > 4 > 3 > 2) then
       player 1 collects both cards and adds them to their pile of cards (their queue)
   else if player 2's card has a higher number
       player 2 collects both cards and adds them to their pile of cards
   else a "War" occurs
       players add their top 3 cards to the played pile and "play" their next card, and the process repeats

until one player is out of cards

the other player is declared the winner

We are going to play a simplified version of the game that would not be very fun, as the winner will always be the player dealt the Ace of Spaces.  In our version, if the two cards have the same number, then ties will be broken by considering the suit with Spades > Hearts > Diamonds > Clubs.

So, if one player played the Ace of Spades and the other the Ace of Diamonds the person playing the Ace of Spades would win because the cards have the same number (Ace) and Spades > Diamonds.

## The Code
I wrote a set of code that implements a PlayingCard type and sets up a random initial deal of cards.  Your job is to write code to complete the game.

#include <iostream>
#include <list>
#include <stdlib.h>
#include <vector>
#include <queue>
using namespace std;

class PlayingCard {
private:
    int suitNo;
    int cardNo;
public:
    friend bool operator<(const PlayingCard &card1, const PlayingCard &card2) {
        return ((card1.cardNo < card2.cardNo) ||
                ((card1.cardNo == card2.cardNo) && (card1.suitNo < card2.suitNo)));
    }
    PlayingCard(int n, int s) { cardNo = n; suitNo = s; }
    static const string FULLSUITS[4];
    static const string SHORTSUITS[4];
    static const string CARDNAME[13];
    string shortCardName() { return CARDNAME[cardNo] + SHORTSUITS[suitNo]; }
    string longCardName() { return CARDNAME[cardNo] + FULLSUITS[suitNo]; }
};

const string PlayingCard::FULLSUITS[] = {"Clubs", "Diamonds", "Hearts", "Spades"};
const string PlayingCard::SHORTSUITS[] = {"C", "D", "H", "S"};
const string PlayingCard::CARDNAME[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};


int RandInRange(int low, int high) {
    return (low + rand()%(high - low + 1));
}

list<PlayingCard> generateShuffledDeck() {
    vector<PlayingCard> allCards;
    list<PlayingCard> shuffledCards;
    srand(time(0));
    for (int n = 0; n < 13; n++) {
        for (int s = 0; s < 4; s++) {
            allCards.push_back(PlayingCard(n,s));
        }
    }
    // for (auto c : allCards) {
    //    cout << c.shortCardName() << " " << endl;
    // }
    for (int i = 51; i >= 0; i--) {
        int choice = RandInRange(0,i);
        shuffledCards.push_back(allCards[choice]);
        allCards[choice] = allCards[i];
        allCards.pop_back();
    }
    return shuffledCards;
}

void dealCards(list<PlayingCard> cards, queue<PlayingCard> & p1queue, queue<PlayingCard> & p2queue) {
    while (!cards.empty()) {
        PlayingCard card = cards.front();
        cards.pop_front();
        p1queue.push(card);
        if (cards.empty()) {
            cerr << "WARNING! Uneven number of cards\n";
        }
        else {
            card = cards.front();
            cards.pop_front();
            p2queue.push(card);
        }
    }

}

int main() {
    list<PlayingCard> cards = generateShuffledDeck();
    queue<PlayingCard> p1queue;
    queue<PlayingCard> p2queue;
    dealCards(cards,p1queue,p2queue);
    int rounds = 0;
    // Play the game until one players wins and report how many rounds that took
    return 0;
}
At the end of the game my code prints a line describing how the game went:

Player 2 won in 304 rounds

## What to Submit
Submit your solution as a CPP file. Give the file the name AssignmentTypeNumberLastNameFirstName.cpp (so, for example, my submission for Lab 3 would be named Lab3MaclinRichard.cpp). You should also include your first and last name in the file as a comment. Add a long comment in your code showing examples (at least five) of how many rounds the game took to play out and who won.. 