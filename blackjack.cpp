/*******************************************************************************
 * CS 103 PR1 Twenty-One (Blackjack) Project
/******************************************************************************/

// Add other #includes if you need
#include <iostream>
#include <cstdlib>

using namespace std;

/* Prototypes */
void shuffle(int cards[], int n);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);

const int NUM_CARDS = 52;

/**
 * Global arrays to be used as look-up tables. You 
 */
 // ♥, ♠, ♦, ♣
const char* suit[4] = {"\U00002665","\U00002660","\U00002666","\U00002663"}; // H, S, D, C
const char* type[13] = 
  {"2","3","4","5","6","7",
   "8","9","10","J","Q","K","A"};
const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

/**
 * Should permute the deck of cards, effectively shuffling it.
 * You must use the Fisher-Yates / Durstenfeld shuffle algorithm
 *  described in the assignment writeup.
 */
void shuffle(int cards[], int NUM_CARDS) //rearrange array 0-51
{
  /******** You complete ****************/
  int temp;
  for (int i=0; i<52;i++){
    cards[i]=i;
  }
  for (int i=NUM_CARDS-1; i>0; i--){
    int j=rand() % (i+1); //random index from 0 to i 
    temp = cards[i];
    cards[i]=cards[j];//swap
    cards[j] = temp;
  }

}

/**
 * Prints the card in a "pretty" format:   "type-suit"
 *  Examples:  K-C  (King of clubs), 2-H (2 of hearts)
 *  Valid Types are: 2,3,4,5,6,7,8,9,10,J,Q,K,A
 *  Valid Suits are: H, D, C, S
 *
 *  Must use the suit and type arrays to lookup
 *   the appropriate characters to print.
 */
void printCard(int id)
{
  /******** You complete ****************/
  //0-12 hearts /13 =0 
  //13-25 spade /13 =1
  //26-38 diamond /13 = 2
  //39-51 club /13 =3 
  //get the needed suit 
  int index = id%13; //1-13
  int symbol = id/13; //1-4
  cout <<type[index] << suit[symbol]<< " ";


}

/**
 * Returns the numeric value of the card.
 *  Should return 11 for an ACE and can then
 *  be adjusted externally based on the sum of the score.
 *
 * Must use the values array to lookup the appropriate
 *  card return value.
 */
int cardValue(int id)
{
  /******** You complete ****************/
  int cardVal = id%13;
  return value[cardVal];

}

/**
 * Should print out each card in the hand separated by a space and
 * then print a newline at the end.  
 * Should use printCard() to print out each card.
 */
void printHand(int hand[], int numCards)
{
  /******** You complete ****************/
  for(int i=0; i<numCards;i++){
    printCard(hand[i]);
  }
  cout << endl;



}

/**
 * Should return the total score of the provided hand.  
 * ACES should be treated as 11s to make the highest possible hand
 *  and only being reduced to 1s as needed to avoid busting.
 */
int getBestScore(int hand[], int numCards)
{
  /******** You complete ****************/

  int score=0, aces=0;
  for(int i=0; i<numCards;i++){
    int cardVal=cardValue(hand[i]);
    score += cardVal;
    if (cardVal == 11){
      aces++;
    }
  }
  while (score > 21 && aces > 0){
    score -= 10;
    aces--;
  }
  return score; 
}

/**
 * Main program logic for the game of 21
 */
int main(int argc, char* argv[])
{
  //---------------------------------------
  // Do not change this code -- Begin
  //---------------------------------------
  if(argc < 2){
    cout << "Error - Please provide the seed value." << endl;
    return 1;
  }
  int seed = atoi(argv[1]);
  srand(seed);

  int cards[52];
  int dhand[9];
  int phand[9];
  //---------------------------------------
  // Do not change this code -- End
  //---------------------------------------

  /******** You complete ****************/
  //shuffle
  //deal
  //let the player play until they bust or stay
  // let the dealer play until the player stays
  //initialize array to 0-51

  char playAgain ='y'; 
  while(playAgain == 'y'){ 
    shuffle(cards, NUM_CARDS); //shuffle cards everytime
  //deal 
    int playerCards=0, dealerCards=0, deckVal=0; 
    phand[playerCards++]=cards[deckVal++]; //0p | 1d | 2p | 3d | 4playeroptional |
    dhand[dealerCards++]=cards[deckVal++];
    phand[playerCards++]=cards[deckVal++];
    dhand[dealerCards++]=cards[deckVal++];

    cout << "Dealer: ? ";
    printCard(dhand[1]);
    cout << endl;
    cout << "Player: "; 
    printHand(phand, playerCards);

    //players turn
    char choice; 
    while(getBestScore(phand, playerCards) < 21){ //while bestscore < 21 -beginning round
      cout << "Type 'h' to hit and 's' to stay: "<<endl;
      cin >> choice;
      if(choice == 's'){
        break;
      }
      phand[playerCards++] = cards[deckVal++]; //playerhand printout
      cout << "Player: ";
      printHand(phand, playerCards);
    } 
    int playerScore = getBestScore(phand, playerCards); //playerscore - getted
    if (playerScore > 21){
    cout << "Player busts"<<endl;
    cout << "Lose " << playerScore<<" "<<getBestScore(dhand,dealerCards) << endl;
    }
    //dealer
    else {
      while(getBestScore(dhand, dealerCards)<17){
        dhand[dealerCards++] = cards[deckVal++];
      }
      cout << "Dealer:";
      printHand(dhand, dealerCards);
      int dealerScore = getBestScore(dhand,dealerCards);
      if(dealerScore > 21){
        cout << "Dealer busts"<<endl; //
      }

      
      //--seperate
      if(playerScore > dealerScore || dealerScore > 21) { //
        cout << "Win ";
      }
      else if (playerScore<dealerScore){
        cout << "Lose "; 
      }
      else {
        cout << "Tie ";
      }
      cout << playerScore << " " << dealerScore;
    }
    cout << endl;
    cout << "Play again? [y/n]" << endl;
    cin >> playAgain;
  
  }



  return 0;
}
