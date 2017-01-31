#include <stdio.h>

int main(void)
{
float i;
int j;

printf("Enter a float number:");
scanf("%f",&i);

j=i+0.5;

printf("The number after rounding is : %d",j);
return 0;
}
