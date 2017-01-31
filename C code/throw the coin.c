#include <stdio.h>
#include <time.h>

int flip(void);


int main(void)
{
int i,head=0,tail=0;
srand(time(NULL));

for(i=0;i<100;i++)
{
    if(flip()==0) {printf("Tails.\n"); tail++;}
    else {printf("Heads.\n"); head++;}
}

printf("\n");
printf("Heads: %d\n",head);
printf("Tails: %d\n",tail);
return 0;
}

int flip(void)
{
    int random;
    random = rand()%2;
    return random;
}
