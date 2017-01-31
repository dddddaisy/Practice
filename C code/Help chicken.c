/*Help chicken 5.30*/
#include <stdio.h>

int main(void)
{
int i,j,num,ans=0;
printf("Give a number: ");
scanf("%d",&num);

for(i=10,j=1;num/j!=0;i*=10,j*=10)
{
    ans*=10;
    ans += (num%i)/j;
}
printf("Answer is %d",ans);
return 0;
}
