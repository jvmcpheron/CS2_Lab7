#include <iostream>
#include <list>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <ctime>
#include <string>
using namespace std;

class PlayingCard {
private:
    int suitNo;
    int cardNo;
public:

    //constructors
    int getCardNo(){
        return cardNo;
    }
    int getSuitNum(){
        return suitNo;
    }

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

bool isPlayer1Win(PlayingCard card1, PlayingCard card2) {
    if (card1.getCardNo() > card2.getCardNo()) {

        return true;
    }
    else if (card1.getCardNo() < card2.getCardNo()) {

        return false;
    }
    else { 

        return card1.getSuitNum() < card2.getSuitNum();
    }
}

int playWar(queue<PlayingCard>& p1queue, queue<PlayingCard>& p2queue) {

    int rounds = 0;

    while (!p1queue.empty() && !p2queue.empty()) {

        rounds++;
        PlayingCard p1Card = p1queue.front();
        PlayingCard p2Card = p2queue.front();
        p1queue.pop();
        p2queue.pop();

        if (isPlayer1Win(p1Card, p2Card)) {

            p1queue.push(p1Card);
            p1queue.push(p2Card);

        }
        else {

            p2queue.push(p2Card);
            p2queue.push(p1Card);
        }
    }
    return rounds;
}

void playWarGame() {
    list<PlayingCard> cards = generateShuffledDeck();

    queue<PlayingCard> p1queue;
    queue<PlayingCard> p2queue;
    
    dealCards(cards, p1queue, p2queue);
    
    int rounds = playWar(p1queue, p2queue);

    if (p1queue.empty()) {
        cout << "Player 2 won in " << rounds << " rounds" << endl;
    }
    else if (p2queue.empty()) {
        cout << "Player 1 won in " << rounds << " rounds" << endl;
    }
}

int main() {
    playWarGame();
    return 0;
}