#include <stdio.h>

int main(void)
{
int num,div,ten,bin;
scanf("%d",&num);
bin = 0;
for(ten=1;num!=0;ten*=10)
{
    div = num%2;
    bin += div*ten;
    num = num/2;
}
printf("%d",bin);
return 0;
}
