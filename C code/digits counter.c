#include <stdio.h>

int main(void)
{
int keyin,digits;
printf("Enter a nonnegative interge: ");
scanf("%d",&keyin);
digits = 0;
do{
keyin /= 10.0f;
++digits;
}while(keyin>=1);
printf("The number has a %d digit(s).",digits);

return 0;
}

