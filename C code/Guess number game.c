//code try at home!!
#include <stdio.h>
#include <stdlib.h>

int num;

void number_check(int a)
{
    if (a > num) printf("Too high!Try again!\n");
    if (a < num) printf("Too low!Try again!\n");
}

void game(void)
{
    int inputnum,i=0;
    printf("Guess the secret number between 1 and 100.\n\n");
    srand((unsigned) time(NULL));
    num = rand()%100;
    do
    {
        printf("Enter guess: ");
        scanf("%d",&inputnum);
        number_check(inputnum);
        i++;
    }while(inputnum!=num);
    printf("You win in %d guess!",i);
    return 0;
}

int main(void)
{
    game();

    char ans;
    while(1)
    {
        printf("\n\nPlay again?(y/n)");
        ans = getchar();
        ans = getchar();
        if(ans =='y'||ans == 'Y') game();
        if(ans =='n'||ans == 'N') break;
    }
    return 0;
}
