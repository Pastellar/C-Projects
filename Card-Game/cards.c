#include <stdio.h>
#include <stdlib.h>

#include "cards.h"

Card* createCard()
{
    /**This function dynamically allocates a new Card struct object and returns a pointer
        to that struct object which will later  be used to insert into a linked list. 
     **There are three types of card that also have a value. A card type will be assigned based
        on these random chances:
        >40% - ATTACK: the value is a random number between 1 and 5 inclusive.
        >50% - DEFEND: the value is a random number between 3 and 8 inclusive.
        >10% - RUN: the value is a random number between 1 and 8 inclusive. 
                    The value of a RUN card is only used for sorting purposes. 
    */
    Card *newCard;//Creates a new Card struct

    newCard = ( Card* )malloc( sizeof( Card ) );//Dynamically allocates the new Card struct

    int r = rand() % 10;//Value used to assign card types randomly

    //Assigns an ATTACK card
    if ( r >= 0 && r <= 3 )
    {
        newCard->type = ATTACK;
        newCard->value = rand() % 5 + 1;
    }
    
    //Assigns a DEFEND card
    else if ( r >= 4 && r <= 8 )
    {
        newCard->type = DEFEND;
        newCard->value = ( rand() % ( 8 - 3 ) ) + 3;
    }
    
    //Assigns a RUN card
    else
    {
        newCard->type = RUN;
        newCard->value = rand() % 8 + 1;
    }

    newCard->next = NULL;

    return newCard;
}

Card* removeCard( Card *head )
{
    /**This function removes and deallocates the first node in the linked list that head is
        pointing at. 
     **It returns the new head of the linked list.
    */
    Card *ptr = head;

    free( ptr );

    return head;
}

Card* addCard( Card *head, Card *c )
{
    /**This function adds a new Card struct object to the linked list that head is pointing at.
     **It is assumed that a new Card struct object is being passed onto this function as a 
        parameter c.
     **This function will add the new node in descending order of its value regardless of the action.
    */
    Card *ptr; 
    Card *prev = NULL;

    if ( head == NULL || c->value > head->value )
    {
        c->next = head;
        head = c;
    }

    else
    {
        for ( ptr = head; ptr != NULL; ptr = ptr->next )
        {
            if ( c->value <= ptr->value )
            {
                if ( ptr->next == NULL )
                {
                    ptr->next = c;
                    break;
                }
            }

            else
            {
                if ( prev != NULL )
                {
                    c->next = ptr;
                    prev->next = c;
                    break;
                }
            }
            prev = ptr;
        }
    }
    return head;
}

int getLength( Card *head )
{
    /**This function returns the lengths of the linked list that head is pointing at.
    */
    Card *ptr;
    int c = 0;//Counts the lengths

    for ( ptr = head; ptr != NULL; ptr = ptr->next )
    {
        c++;
    }

    return c;
}

void printCard( Card *head )
{
    /**This function prints a single card with abbreviations:
        >A for ATTACK
        >D for DEFEND
        >R for RUN
        along with their corresponding values.
     **Example: A5 means an ATTACK is worth 5 points.
    */
    char c;//Abbreviation for the card

    //If card is an ATTACK
    if ( head->type == ATTACK )
    {
        c = 'A';
    }

    //If card is a DEFEND
    else if ( head->type == DEFEND )
    {
        c = 'D';
    }
    
    //If card is a RUN
    else
    {
        c = 'R';
    }

    printf( "%c%d ", c, head->value );//Prints the card's type abbreviation and value
}

void printCards( Card *head )
{
    /**This function traverses the linked list that head is pointing at.
     **It will call printCard().
     **It should print from front to back.
     **Example: R6 D5 D4 A4 D3
    */
    if ( head == NULL )
        return;

    printCard( head );

    printCards( head->next );
}

Card *buildCards( int n )
{
    /**This function builds a stack of cards using a linked list.
     **The parameter n determines how many cards are created.
     **It will use createCard() and addCard().
     **It returns the head of the new linked list.
    */
    int i;//The current iteration through the linked list

    Card *head = NULL;
    Card *card[n]; //determines the amount of cards created

    for ( i = 0; i < n; i++ )
    {
        card[i] = createCard();//Iterates through and creates a card on each iteration
        head = addCard( head, card[i] );
    }
    return head;
}

Card* destroyCards( Card *head )
{
    /**This function is the destructor for a linked list that head is pointing at.
     **It should return NULL.
     */
    Card *p = head;
    
    //Loop frees the values and destroys the card data
    while ( p != NULL )
    {
        Card *temp = p;
        p = p->next;
        free( temp );
    }

    return NULL;
}
