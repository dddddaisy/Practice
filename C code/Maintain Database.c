/*Ch16 - p.46*/
#include <stdio.h>

struct part
{
int num;
char name[30];
int on_hand;
};

int main(void)
{
int i,data,num,on_hand,change;
char oper,x,name[30];
struct part memory[50];


data = 0;
while(1)
{
printf("Enter operation code: ");
oper = getchar();
if(oper=='i')
{
    printf("Enter part number: ");
    scanf("%d",&memory[data].num);
    x = getchar();
    printf("Enter part name: ");
    gets(memory[data].name);
    printf("Enter quantity on hand: ");
    scanf("%d",&memory[data].on_hand);
    data++;
}
else if(oper=='s')
{
    printf("Enter part number: ");
    scanf("%d",&num);
    for(i=0;i<=data-1;i++)
        if(memory[i].num == num) break;
    if(memory[i].num != num) printf("Part not found.\n");
    else
    {
    printf("Part name: %s\n",memory[i].name);
    printf("Quantity on hand: %d\n",memory[i].on_hand);
    }
}
else if(oper=='u')
{
    printf("Enter part number: ");
    scanf("%d",&num);
    printf("Enter change in quantity on hand: ");
    scanf("%d",&change);
    for(i=0;i<=data-1;i++)
        if(memory[i].num == num) break;
    memory[i].on_hand += change;
}
else if(oper=='p')
{
    printf("Part Number  Part Name                Quantity on hand\n");
    for(i=0;i<=data-1;i++)
        printf("%-13d%-25s%d\n",memory[i].num,memory[i].name,memory[i].on_hand);
}
else break;
x = getchar();
printf("\n");
}
return 0;
}
