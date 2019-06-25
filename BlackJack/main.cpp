#include <iostream>
using namespace std;

int A = 11;
int J = 10;
int Q = 10;
int K = 10;

int deck[] = {A, 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K,
    A, 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K,
    A, 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K,
    A, 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K,};

void rules();
int bet(int &cash);
int playGame(int bet);
int Deck();
int User(int cardOne, int cardTwo);
int Dealer(int cardOne, int cardTwo, int user);

int main() {
    srand(time(NULL));
    char playAgain;
    int money;
    int amountBet;
    int amountWon = 0;
    
    rules();
    cout << "How much money would you Like to take out? $";
    cin >> money;
    
    do{
        if (money < 5)
        {
            cout << "Sorry, you do not have enough money to play." << endl;
            break;
        }
        amountBet = bet(money);
        while (amountBet > money)
        {
            cout << "You do not have enough money to make the bet. Try another bet" << endl;
            amountBet = bet(money);
        }
        money =  money - amountBet;
        amountWon = playGame(amountBet);
        money = money + amountWon;
        cout << "You won $" << amountWon << endl;
        cout << "Your Money: $" << money << endl;
        cout << endl;
        cout << "Would you like to play again? (Y/N) ";
        cin >> playAgain;
        cout << endl;
    }
    
    while (playAgain == 'y' || playAgain == 'Y');
    cout << "End Game." << endl;
    return 0;
}

void rules()
{
    cout << "Welcome to BlackJack." << endl;
    cout << "Payout on a Winning hand is twice your bet." << endl;
    cout << "Payout on a Natural BlackJack is 3:2" << endl;
    cout << "Enjoy your game!" << endl;
    cout << endl;
}

int bet(int &cash)
{
    int bet;
    cout << "Min Bet -- 5$      Max Bet -- $500" << endl;
    cout << "Place your bet: $";
    cin >> bet;

    return bet;
    
}

int playGame(int bet)
{
    int UserFinal, DealerFinal;
    int cards1, cards2, cards3, cards4;
    cards1 = Deck();
    cards2 = Deck();
    cards3 = Deck();
    cards4 = Deck();
    cout << "Users Cards: " << cards1 << " " << cards2 << endl;
    cout << "Dealers Cards: " << "**" << " " << cards4 << endl;
    
    cout << endl;
    
    UserFinal = User(cards1, cards2);
    DealerFinal = Dealer(cards3, cards4, UserFinal);

    
    
    
    cout << "User Final: " << UserFinal <<  endl;
    cout << "Dealer Final: " << DealerFinal << endl;
    
    if (cards1 + cards2 == 21 && DealerFinal != 21){
        bet = bet * 2.5;
    }
    
    else if (UserFinal > DealerFinal && UserFinal <= 21){
        cout << "User Wins!" << endl;
        bet = bet * 2;
    }
    
    else if (UserFinal < DealerFinal && DealerFinal <= 21){
        cout << "Dealer Wins!" << endl;
        bet = 0;
    }
    
    else if (DealerFinal > 21 && UserFinal > 21){
        cout << "Dealer Wins!" << endl;
        bet  = 0;
    }
    
    else if (DealerFinal > 21){
        cout << "User Wins!" << endl;
        bet = bet * 2;
    }
    
    else if (UserFinal > 21){
        cout << "Dealer Wins" << endl;
        bet = 0;
    }
    
    else if (UserFinal == DealerFinal){
        cout << "Push. No Winner!" << endl;
    }
    
    cout << endl;
    
    return  bet;

}

int Deck()
{
    int pick = rand() % 52;
    return deck[pick];
}

int User(int cardOne, int cardTwo)
{
    int sum = 0;
    char option;
    sum = cardOne + cardTwo;
    cout << "Users turn." << endl;
    cout << "Hit(H) or Stand(S) ";
    cin >> option;
    while (option == 'h' || option == 'H'){
        int randNum = Deck();
        int *newCard = new int(randNum);
        cout << "Card Dealt: " << *newCard << endl;
        sum += *newCard;
        if (cardOne == 11 || cardTwo == 11 || *newCard == 11)
        {
            if (sum > 21)
            {
                sum = sum - 10;
                cout << "Ace is now equal to 1" << endl;
            }
        }
        else if (sum > 21)
        {
            cout << "You Busted!" << endl;
            cout << endl;
            break;
        }
        cout << "New card total: ";
        cout << sum << endl;
        cout << "Hit(H) or Stand(S)" << endl;
        cin >> option;
    }
    
    
    
    if (option == 's' || option =='S'){
        cout << "Turn Complete" << endl;
        cout << endl;
    }
    
    return sum;
}

int Dealer(int cardOne, int cardTwo, int user)
{
    if (user > 21)
    {
        return cardOne + cardTwo;
    }
    int sum = 0;
    sum = cardOne + cardTwo;
    cout << "Dealers turn" << endl;
    if (cardOne + cardTwo < 17){
        cout << "Dealer chose to Hit" << endl;
        int randNum = Deck();
        int *newCard = new int(randNum);
        cout << "Dealer dealt a " << *newCard << endl;
        sum += *newCard;
        while (sum < 17)
        {
            cout << "Dealer chose to Hit" << endl;
            int randNum = Deck();
            int *newCard = new int(randNum);
            cout << "Dealer dealt a " << *newCard << endl;
            sum += *newCard;
            if (cardOne == 11 || cardTwo == 11 || *newCard == 11)
            {
                if (sum > 21)
                {
                    sum = sum - 10;
                }
            }
        }
        
    }
    
    if (sum > 21)
    {
        cout << "Dealer Busted!" << endl;
    }
    
    else if (cardOne + cardTwo >= 17){
        cout << "Dealer chose to Stand" << endl;
    }
    
    else if (sum >= 17){
        cout << "Dealer chose to Stand" << endl;
    }
    
    return sum;
    
}
