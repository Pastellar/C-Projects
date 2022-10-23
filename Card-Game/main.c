#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "cards.h"
#include "cards.c"

int main(int argc, char *argv[])
{
    /**This program will accept one additional command line argument, which is the number
       of cards players will start with.
     **The program must determine if there is a command line argument:
        >If the argument DNE, print an error, and end the program.
        >If the argument exists, check to see if it is a number > 0.
            *If it is not, print and error and end the program
            *Use the function atoi() to help convert a string to an int.
        >If the argument exists, and it is a number > 0, start the game:
            *Build each player's Card linked list based on the size passed in through the command
             line arguments.
            *Print out each player's cards using printCards().
            *Start the game loop; the game will continue so long as both players have
             cards to play with.
    */

    srand( time( NULL ) ); //seed random values

    int count1 = 0;     //number of player 1's cards
    int count2 = 0;     //number of player 2's cards
    int i = 0;          //current round number

    Card *player1 = NULL; // player 1 linked list
    Card *player2 = NULL; // player 2 linked list
    Card *card = NULL;    // card to be added when a player wins
    
    //Check that enough arguments were entered
    if ( argc != 2 )
    {
        printf( "ERROR NOT ENOUGH ARGS\n" );
        return 1;
    }
    
    //Convert argument string to an int
    char* temp = argv[1];
    int numCards = atoi( temp );

    //BEGIN THE GAME
    printf( "\n============= PLAYER 1 V PLAYER 2 SHOWDOWN ============\n" );
    printf( "Start size: %d cards", numCards );
    
    //Create a deck of cards for each player ( stored in a linked list )
    player1 = buildCards( numCards ); // build player 1's deck
    player2 = buildCards( numCards ); // build player 2's deck

    //Print both player's starting deck of cards
    printf( "\nPlayer 1 starting cards: " );
    printCards( player1 ); // prints player 1 deck

    printf( "\nPlayer 2 starting cards: " );
    printCards( player2 ); // prints player 2 deck( all cards in linked list )
    printf( "\n" );

   //GAME PROCESSES BEGIN BELOW
    while ( player1 != NULL && player2 != NULL )
    {
        //Loop continues until at least one player has lost all of their cards
        printf( "\n----- ROUND %d -----\n", i + 1 );

        count1 = getLength( player1 ); // calculates the length of player 1's linked list on every iteration
        printf( "Player 1 (%d): ", count1 );
        printCard( player1 ); // prints current card played by player 1
        printf( "\n" );

        count2 = getLength( player2 ); // calculates the length of player 2's  linked list on every iteration
        printf( "Player 2 (%d): ", count2 );
        printCard( player2 ); // prints current card played by player 2
        printf( "\n" );

        //Below are the potential game scenarios that may occur

        //BOTH players ATTACK
        if ( player1->type == ATTACK && player2->type == ATTACK )
        {
            printf( "Both players ATTACK.\n" );
            
            //Player 1 WINS
            if ( player1->value > player2->value )
            {
                printf( "Player 1 wins and gets a new card." );
                card = createCard();
                player1 = addCard( player1, card );//Card is created and added to Player 1's deck

                printf( " Player 2 loses their next card into the abyss.\n" );
                if ( player2->next != NULL )
                {
                    player2 = removeCard( player2->next );//Card is removed from Player 2's deck
                }
            }

            //Player 2 WINS
            else if ( player1->value < player2->value )
            {
                printf( "Player 2 wins and gets a new card." );
                card = createCard();
                player2 = addCard( player2, card );//Card is created and added to Player 2's deck

                printf( " Player 1 loses their next card into the abyss.\n" );
                if ( player1->next != NULL )
                {
                    player1 = removeCard( player1->next );//Card is removed from Player 1's deck
                }
            }
            
            //Both Players TIE
            else
            {
                printf( "It's a tie. Nothing happens.\n" );
            }
        }

        //PLAYER 1 ATTACKs and Player 2 DEFENDs
       else if ( player1->type == ATTACK && player2->type == DEFEND )
        {
            printf( "Player 1 ATTACKs and Player 2 DEFENDs.\n" );

            //Scenario 1: Player 1 WINS
            if ( player1->value > player2->value )
            {
                printf( "Player 1 wins. Player 1 gets a new card.\n" );
                card = createCard();
                player1 = addCard( player1, card );//Card is created and added to Player 1's deck
            }
            
            //Scenario 2: Player 1 LOOSES
            else
            {
                printf( "Player 1 loses and Player 2 survives.\n" );
                printf( "Player 1 loses their next card into the abyss.\n" );
                if ( player1->next != NULL )
                    player1 = removeCard( player1->next );//Card is removed from Player 1's deck
            }
        }
        
        //PLAYER 1 ATTACKs and Player 2 RUNs
       else if ( player1->type == ATTACK && player2->type == RUN ) 
        {
            printf( "Player 1 ATTACKs and Player 2 RUNs.\n" );

            printf( "Player 2 loses their next card into the abyss.\n" );
            if ( player2->next != NULL )
            {
                player2 = removeCard( player2->next );//Card is removed from Player 2's deck
            }
        }
        
        //PLAYER 2 ATTACKs and Player 1 DEFENDs
       else if ( player1->type == DEFEND && player2->type == ATTACK )
        {
            printf( "Player 2 ATTACKs and Player 1 DEFENDs.\n" );
            
            //Scenario 1: Player 1 has a HIGHER or EQUAL value
            if ( player1->value >= player2->value )
            {
                printf( "Player 2 loses and Player 1 survives.\n" );
                printf( "Player 2 loses their next card into the abyss.\n" );
                if ( player2->next != NULL )
                {
                    player2 = removeCard( player2->next );//Card is removed from Player 2's deck
                }
            }
            
            //Scenario 2: Player 2 has a HIGHER value
            else
            {
                printf( "Player 2 wins. Player 2 gets a new card.\n" );
                card = createCard();
                player2 = addCard( player2, card );//Card is created and added to Player 2's deck
            }
        }
        
        //BOTH players DEFEND
       else if ( player1->type == DEFEND && player2->type == DEFEND )
        {
            printf( "Both players DEFEND.\nNothing happens.\n" );
        }
        
        //PLAYER 1 DEFENDs and Player 2 RUNs
       else if ( player1->type == DEFEND && player2->type == RUN )
        {
            printf( "Player 1 DEFENDs and Player2 RUNs.\n" );

            printf( "Player 1 gets a new card. " );
            card = createCard();
            player1 = addCard( player1, card );//A card is created and added to Player 1's deck

            printf( "Player 2 loses their next card into the abyss.\n" );
            if ( player2->next != NULL )
            {
                player2 = removeCard( player2->next );//Card is removed from Player 2's deck
            }
        }

        //PLAYER 2 ATTACKs and Player 1 RUNs
       else if ( player1->type == RUN && player2->type == ATTACK )
        {
            printf( "Player 2 ATTACKs and Player 1 RUNs.\n " );

            printf( "Player 1 loses their next card into the abyss.\n" );
            if ( player1->next != NULL )
            {
                player1 = removeCard(player1->next);//Card is removed from Player 1's deck
            }
        }
        
        //PLAYER 2 DEFENDs and Player 1 RUNs
       else if ( player1->type == RUN && player2->type == DEFEND )
        {
            printf( "Player 2 DEFENDs and Player 1 RUNs.\n" );

            printf( "Player 2 gets a new card. " );
            card = createCard();
            player2 = addCard( player2, card );//Card is created and added to Player 2's deck

            printf( "Player 1 loses their next card into the abyss.\n" );
            if ( player1->next != NULL )
            {
                player1 = removeCard(player1->next);//Card is removed from Player 1's deck
            }
        }
        
        //BOTH players RUN
       else if ( player1->type == RUN && player2->type == RUN )
        {
            printf( "Both players RUN.\n" );

            printf( "Both players lose their next card into the abyss.\n" );

            if ( player1->next != NULL )
            {
                player1 = removeCard( player1->next );//Card is removed from Player 1's deck
            }
            if ( player2->next != NULL ) 
            {
                player2 = removeCard( player2->next );//Card is removed from Player 2's deck
            }
        }

        player1 = player1->next;
        player2 = player2->next;
        i++;
    }

    //Game Over Processes
    printf( "\n============ GAME OVER =============\n" );

    printf( "\nPlayer1 ending cards: " );//Prints Player 1's ending cards
    printCards( player1 );

    printf( "\nPlayer2 ending cards: " );//Prints Player 2's ending cards
    printCards( player2 );

    printf( "\n" );
    
    //Ending Scenarios
    if ( player1 == NULL && player2 == NULL ) //No winner
    {
        printf( "\nBoth players ran out of cards. No winner.\n" );
    }
    else if ( player1 != NULL && player2 == NULL )//Player 1 Wins
    {
        printf( "\nPlayer 2 ran out of cards. Player 1 wins.\n" );
    }

    else //Player 2 wins
    {
    printf( "\nPlayer 1 ran out of cards. Player 2 wins.\n" );
    }

    //Game ends
    printf( "The end.\n" );
    printf( "\n" );
    

    //Destroy both player's card decks (linked list data)
    destroyCards( player1 );
    destroyCards( player2 );

    return 0;
}
