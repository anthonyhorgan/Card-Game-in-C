#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef enum S {CLUBS, DIAMONDS, HEARTS, SPADES} SUIT;
char suits[][10] = {"CLUBS", "DIAMONDS", "HEARTS", "SPADES"};

typedef enum F {TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE} FACE;
char faces[][10] = {"TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE", "TEN", "JACK", "QUEEN", "KING", "ACE"};

typedef struct
{
	SUIT suit; 
	FACE face;
} card;

typedef struct
{
	card cards[5];
} hand;

hand dealHand(hand handsDealt[], int numHandsDealt);

char * printCard(card aCard);

char * compareCards(card yourCard, card dealersCard);

bool fourAces(hand aHand);

void main()
{
	int i = 0;
	hand myHand, dealersHand;
	int seed = time(NULL);
	srand(seed);
	hand hands[10];
        
	myHand = dealHand(hands, 0);
        
	hands[0] = myHand;
        
        dealersHand = dealHand(hands, 1);

	while(i<5)
	{
		printf("card#%d: %s (you) vs. %s (dealer). Winner: %s \n", i+1, printCard(myHand.cards[i]), printCard(dealersHand.cards[i]),  compareCards(myHand.cards[i], dealersHand.cards[i]));
		i++;
	}
        i=0;
        
        
	while(1)
	{
		myHand = dealHand(hands,0);
		if (fourAces(myHand)) break;
		i++;
	}
       
        printf ("\n\n4 aces found after %d hands \n\n\n", i);
        
}


hand dealHand(hand handsDealt[], int numHands)//not sure whats up with this one
{
	int i = 0;
        int j, n;
        int q = 0;
        int copy = 0;
        hand tempHand;
	hand newHand;

        while(i<5){//This loop creates 5 cards
            tempHand.cards[i].suit = (rand()%4);
            tempHand.cards[i].face = (rand()%13);
            q++;
            for(j = 0; j<numHands; j++){//this loop cycles through hands already dealt
                for(n = 0; n<5; n++){//this loop cycles through each card of a given hand already dealt
                    if((tempHand.cards[i].suit == handsDealt[j].cards[n].suit && tempHand.cards[i].face == handsDealt[j].cards[n].face)){//checks if cards are identical
                        copy = 1;
                    }
                }
            }
            for(n = 0; n<5;n++){//loops through all cards in current hand
                if(tempHand.cards[i].suit == newHand.cards[n].suit && tempHand.cards[i].face == newHand.cards[n].face){//checks if cards are identical
                    copy = 1;
                }
            }
            if(copy == 0){//assigns cards to the hand if they are not copies of other cards
                newHand.cards[i].suit = tempHand.cards[i].suit;
                newHand.cards[i].face = tempHand.cards[i].face;
                i++;//i is only incremented if the card is not a copy
            }
        }
	return newHand;
}

char * compareCards(card yourCard, card dealersCard)//this works
{
	char * sptr;
	sptr = (char *)malloc(10*sizeof(char));
	
        
        //this block of code checks who the winner is
        if(yourCard.face > dealersCard.face){
            sptr = "You";
        }
        else if(yourCard.face < dealersCard.face){
            sptr = "Dealer";
        }
        else if(yourCard.face == dealersCard.face){
            sptr = "Draw";
        }
        
	return sptr;
}

char * printCard(card aCard)
{
        char *suit = suits[aCard.suit];
        char *face = faces[aCard.face];
        
        char* sptr = malloc(strlen(suit) + strlen(face) + strlen(" of ") + 10);//allocates memory for string to be returned
        sprintf(sptr, "%s of %s", face, suit);//concatenates to from final string
        
	return sptr;
}

bool fourAces(hand aHand)
{
	int i;
	int numAces = 0;
	bool fourAces = false;

        for(i=0; i<5; i++){//cycles through cards in the hand
            if(aHand.cards[i].face == 13){//checks if card is an ace
                numAces++;
            }
        }
        if(numAces == 4){
            fourAces = true;
        }
	return fourAces;

}