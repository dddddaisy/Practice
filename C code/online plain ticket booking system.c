#include <stdio.h>
#include <stdbool.h>
#include <time.h>

bool F_C_SeatCheck(bool Seats[10]);
bool E_SeatCheck(bool Seats[10]);
bool AllSeatCheck(bool Seats[10]);
bool a_lot_money_people(bool Seats[10]);
bool no_money_people(bool Seats[10]);

int main(void)
{
    srand(time(NULL));
    int i,ope;
    bool Seats[10];

    for(i=0;i<10;i++)
        Seats[i] = false;

    while(1)
    {
        printf("---Welcome to Airline Reservation System---\n");
        printf("** Please type 1 for \" First Class \"\n");
        printf("** Please type 2 for \" Economy \"\n");
        printf("I want to -> ");
        scanf("%d",&ope);
        if(ope==1)
        {
            a_lot_money_people(Seats);
            printf("\n-----------------------------------------------\n");

        }
        else if(ope==2)
        {
            no_money_people(Seats);
            printf("\n-----------------------------------------------\n");

        }
        else
        {
            printf("Wrong Input!!\n");
            printf("\n-----------------------------------------------\n");
        }


        if(AllSeatCheck(Seats)) break;
    }
    return 0;
}

bool F_C_SeatCheck(bool Seats[10])
{
    int i;
    for(i=0;i<5;i++)
        if(Seats[i]==false) return false;
    return true;
}

bool E_SeatCheck(bool Seats[10])
{
    int i;
    for(i=5;i<10;i++)
        if(Seats[i]==false) return false;
    return true;
}

bool AllSeatCheck(bool Seats[10])
{
    int i;
    for(i=0;i<10;i++)
        if(Seats[i]==false) return false;
    printf("There are no seats, next flight leaves in 3 hours.\n");
    return true;
}

bool a_lot_money_people(bool Seats[10])
{
    char ans;
    int given_seat;
    if(F_C_SeatCheck(Seats)==true)
    {
        printf("There are no seat for First Class, are you willing to have a seat at Economy? ");
        while(1)
        {
            while((ans=getchar())==' '||ans=='\n');
            if(ans=='y'||ans=='Y')
            {
                no_money_people(Seats);
                break;
            }
            else if(ans=='n'||ans=='N')
            {
                printf("Next flight leaves in 3 hours.\n");
                break;
            }
            else printf("Wrong Input!!\n");
        }
        return Seats[10];
    }
    while(1)
    {
        given_seat = rand()%5;
        if(Seats[given_seat]==false) break;
    };
    Seats[given_seat] = true;

    printf("Your Ticket : \n");
    printf("\t\t First Class seat-%d\n",given_seat+1);
    return Seats[10];
}

bool no_money_people(bool Seats[10])
{
    int given_seat;
    if(E_SeatCheck(Seats)==true)
    {
        printf("There no seat for Economy.\n");
        return Seats[10];
    }

    while(1)
    {
        given_seat = rand()%5+5;
        if(Seats[given_seat]==false) break;
    };
    Seats[given_seat] = true;

    printf("Your Ticket : \n");
    printf("\t\t Economy seat-%d",given_seat+1);
    return Seats[10];
}
