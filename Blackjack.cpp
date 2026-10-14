#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

struct Card {
    int rank;
    int suit;
};

Card deck[52];
int currentCard = 0;

void initDeck() {
    int index = 0;

    for (int suit = 0; suit < 4; suit++) {
        for (int rank = 1; rank <= 13; rank++) {
            deck[index].rank = rank;
            deck[index].suit = suit;
            index++;
        }
    }
}

void shuffleDeck() {
    for (int i = 0; i < 52; i++) {
        int randomIndex = rand() % 52;

        Card ajutine = deck[i];
        deck[i] = deck[randomIndex];
        deck[randomIndex] = ajutine;
    }
}

Card dealCard() {
    Card card = deck[currentCard];
    currentCard++;
    return card;
}

int cardValue(Card card) {
    if (card.rank == 1) {
        return 11;
    }

    if (card.rank >= 11) {
        return 10;
    }

    return card.rank;
}

void printCard(Card card) {
    string suits[] = {"H", "D", "C", "S"};
    string rank;

    if (card.rank == 1)
        rank = "A";
    else if (card.rank == 11)
        rank = "J";
    else if (card.rank == 12)
        rank = "Q";
    else if (card.rank == 13)
        rank = "K";
    else
        rank = to_string(card.rank);

    cout << rank << suits[card.suit];
}

int handValue(Card hand[], int size) {
    int sum = 0;

    for (int i = 0; i < size; i++) {
        sum += cardValue(hand[i]);
    }

    return sum;
}

int main() {
    srand(time(0));

    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    
    char again;

do {

    currentCard = 0;

    initDeck();
    shuffleDeck();

    Card playerHand[11];
    int playerCards = 0;

    playerHand[playerCards] = dealCard();
    playerCards++;

    playerHand[playerCards] = dealCard();
    playerCards++;

    int dealerTotal = 0;

    dealerTotal += cardValue(dealCard());
    dealerTotal += cardValue(dealCard());


    while (true) {

            int total = handValue(playerHand, playerCards);

            cout << "\nSinu kaardid: ";

            for (int i = 0; i < playerCards; i++) {
                printCard(playerHand[i]);
                cout << " ";
            }

            cout << "\nSinu summa: " << total << endl;

            if (total > 21) {
                cout << "Laksid ule 21. Kaotasid!" << endl;
                break;
            }

            cout << "\n1 = Hit";
            cout << "\n2 = Stop";
            cout << "\nValik: ";

            int choice;
            cin >> choice;

            if (choice == 1) {
                playerHand[playerCards] = dealCard();
                playerCards++;
            }
            else {
                break;
            }
        }

        int playerTotal = handValue(playerHand, playerCards);

        cout << "\nDiileri summa: " << dealerTotal << endl;

        if (playerTotal <= 21) {

            if (playerTotal > dealerTotal) {
                cout << "Voitsid!" << endl;
            }
            else if (playerTotal < dealerTotal) {
                cout << "Kaotasid!" << endl;
            }
            else {
                cout << "Viik!" << endl;
            }
        }

        cout << "\nKas soovid uuesti mangida? (y/n): ";
        cin >> again;

    } while (again == 'y' || again == 'Y');

    return 0;
}