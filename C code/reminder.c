/*Ch13 - p.62*/
#include <stdio.h>
#include <string.h>

int main(void)
{
int i,j,day,things;
char reminder[30][30],message[30+3];
i = 0;
things = 0;
do
{
    if(things==30)
    {
        printf("---No Space---\n");
        break;
    }
    printf("Enter day and reminder: ");
    scanf("%2d",&day);
    sprintf(reminder[i],"%2d",day);
    gets(message);
    strcat(reminder[i],message);
    i++;
    things++;
}while(day!=0);

for(i=0;i<things-1;i++)
    for(j=i+1;j<things-1;j++)
{
    if(strcmp(reminder[j],reminder[i])<0)
    {
        strcpy(message,reminder[j]);
        strcpy(reminder[j],reminder[i]);
        strcpy(reminder[i],message);
    }
}

printf("\n\nMonth Reminders: \n");
for(i=0;i<things-1;i++)
    printf("%s\n",reminder[i]);

return 0;
}
