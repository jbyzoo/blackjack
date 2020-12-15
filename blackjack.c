#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int shuffle(int cards[]){
    int t;
    int i;
    int deck[52];

    for(i = 0; i < 52; i++){
        deck[1] = (i / 13 + 3) * 100 + i%13 + 1;
    }

    srand(time(NULL));
    for (i = 0; i < 52; i++)
    {
        do
        {
            t = rand() % 52;

        } while (deck[t] == 0);
        cards[i] = deck[t];
        deck[t] = 0;
    }
    return 0;
}

int convertFace(int a){
    if((a % 100 == 11) || (a % 100 == 12) || (a % 100 == 13)){
        return (a / 100) * 100 + 10;
    }
    else{
        return a;
    }
    
}

void picture(int num){
    char fl;
    int poNum;

    fl = num / 100;
    poNum = num % 100;
    switch (poNum)
    {
    case 1:
       { 
        printf("*******\n");
        printf("*     *\n");
        printf("* %c   *\n", fl);
		printf("*   A *\n");
		printf("*     *\n");
		printf("*******\n");
        break;
       }
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
        {
        printf("*******\n");
		printf("*     *\n");
		printf("* %c   *\n", fl);
		printf("*  %2d *\n", poNum);
		printf("*     *\n");
		printf("*******\n");
		break;
        }
    case 11:
        {
        printf("*******\n");
		printf("*     *\n");
		printf("* %c   *\n", fl);
		printf("*   J *\n");
		printf("*     *\n");
		printf("*******\n");
		break;   
        }
    case 12:
        {
        printf("*******\n");
		printf("*     *\n");
		printf("* %c   *\n", fl);
		printf("*   Q *\n");
		printf("*     *\n");
		printf("*******\n");
		break;   
        }
    case 13:
        {
        printf("*******\n");
		printf("*     *\n");
		printf("* %c   *\n", fl);
		printf("*   K *\n");
		printf("*     *\n");
		printf("*******\n");
		break;   
        }
    }
}

int play(){
    int i;
    int pSum = 0;
    int bSum = 0;
    int pCards[5] = {0};
    int bCards[5] = {0};
    int cards[52];
    char goOn;
    char d;

    printf("Welcome to Black Jack!\n");
    printf("Anytime you can press Ctrl+c to exit.\n");
    printf("Enjoy! Press Enter to go on\n");

    do
    {
        goOn = getchar();
    } while (goOn != '\n');
    printf("\n");

    //shuffle cards
    shuffle(cards);

    //give cards to players
    pCards[0] = cards[0];
    pCards[1] = cards[1];
    bCards[0] = cards[2];
    bCards[1] = cards[3];

    //the 2 cards player gets
    printf("Dealer's Cards: \n");
    picture(bCards[0]);
    printf("\n");
    printf("Player's Cards: \n");
    picture(pCards[0]);
    printf("\n");
    picture(pCards[1]);
    printf("\n");

    i = 0;
    for(i = 0; i < 2; i++){
        if(pCards[1] % 100 == 1){
            printf("choose A value of the card %d, input 'y' for 11 and 'n' for 1.\n", i + 1);
            do
            {
                d = getchar();
            } while (d != 'y' && d != 'n');
            if(d == 'y'){
                printf("You have chosen 11 for card A.\n");
                pSum = pSum + 1;
            }
            else if(d == 'n'){
                printf(" you have chosen 1 for card A.\n");
                pSum = pSum + 1;
            }
        }
        else if(convertFace(pCards[i]) % 100 == 10){
            pSum = pSum + 10;
        }else{
            pSum = pSum + pCards[i] % 100;
        }

        if(pSum > 21){
            printf("Sum of player's cards: %d \n\n", pSum);
            printf("Dealer wins!\n");
            return 1;
        }
        else if(pSum == 21){
            printf("Sum of player's cards now: %d \n\n", pSum);
            printf("Player Wins!\n");
            return 0;
        }
    }

    // wheter a player gets another card
    i = 0;
    for(i = 0; i < 3;i++){
        char j = 'n';

        printf("Want more cards? Input 'y' or 'no':\n");
        do
        {
            j = getchar();
        } while (j != 'y' && j != 'n');
        if(j != 'y'){
            printf("You've got another card now\n");
            pCards[i+2] = pCards[i+4];
            printf("Your new card is %d\n", i + 3);
            picture(pCards[i+2]);

            if(pCards[i + 2] % 100 == 1){
                printf("choose A value of the card %d, input 'y' for 11 and 'n' for 1.\n", i + 3);
            do
            {
                d = getchar();
            } while (d != 'y' && d != 'n');
            if(d == 'y'){
                printf("You have chosen 11 for card A.\n");
                pSum = pSum + 1;
            }
            else if(d == 'n'){
                printf(" you have chosen 1 for card A.\n");
                pSum = pSum + 1;
            }
            }
        }
        else if(convertFace(pCards[i + 2]) % 100 == 10){
            pSum = pSum + 10;
        }else{
            pSum = pSum + pCards[1 + 2] % 100;
        }

        if(pSum > 21){
            printf("Sum of player's cards: %d\n\n", pSum);
            printf("Computer Wins!\n");
            return 1;
        }
        else if(pSum == 21){
            printf("Sum of player's cards: %d\n\n", pSum);
            printf("Player Wins!\n");
            return 0;
        }
        else{
            printf("Sum of player's cards: %d\n\n", pSum);
        }
    }

    if(i == 3){
        printf("Player Win! Because the sum of your 5 cards is larger than 21!\n");
        return 0;
    }

    // Dealer has 2 cards
    //i = 0;

    printf("Dealer's Cards: \n");
    picture(bCards[0]);
    picture(bCards[1]);

    if(bCards[0] % 100 + bCards[1] % 100 == 2){
        bSum = 12;
        printf("Sum of Dealer's Cards: %d\n\n", bSum);
    }
    else if((convertFace(bCards[0])) % 100 + (convertFace(bCards[1])) % 100 == 1){
        bSum = 21;
        printf("Dealer's Cards: %d\n\n", bSum);
        printf("Dealer Wins!");
        return 1;
    }
    else{
        bSum = (convertFace(bCards[0])) % 100 + (convertFace(bCards[1])) % 100;
        printf("Dealer's cards: %d\n\n", bSum);
    }

    //Dealer cards greater than 16

    for(i = 0; i < 3 && bSum < 17; i++){
        bCards[i + 2] = cards[i + 7];
        printf("Dealer's card %d is: \n", i + 3);
        picture(bCards[i + 2]);

        if(bCards[i + 2] % 100 == 1){
            if(bSum + 11 <= 21){
                printf("Dealer has chosen A as 11\n");
                bSum = bSum + 11;
                printf("Dealer's cards:%d\n\n", bSum);
            }
            else{
                printf("Dealer has chosen A as 1\n");
                bSum = bSum + 1;
                printf("Dealer's cards: %d\n\n", bSum);
            }
        }
        else{
            bSum = bSum + convertFace(bCards[i + 2] % 100);
            printf("Dealer's Cards: %d\n\n", bSum);
        }
        if(i == 3){
            printf("Dealer win!");
            return 1;
        }
    }

    //check for win
    if(bSum > 21 || pSum > bSum){
        printf("Player Win!\n");
        return 0;
    }
    else if(pSum == bSum){
        printf("Push");
        return 3;
    }
    else if(pSum < bSum){
        printf("Dealer Win!\n");
        return 1;
    }

    return 3;
}

int main(){
    char again;

    play();
    printf("\nWould you like to play again? Input 'y' or 'n':\n");

    do
    {
        again = getchar();
    } while (again != 'y' && again != 'n');
    
    if(again == 'y'){
        printf("Next hand!\n\n");
        main();
    }
    return 0;
}