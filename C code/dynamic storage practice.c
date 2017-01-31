/*dynamic storage*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct node
{
char name[30];
struct node *next;
};

struct node *frist,*new_node;

void addname(void);
void searchname(void);
void deletename(void);
void showname(void);

int main(void)
{
int opr;
frist = NULL;

printf("---------------------------\n");
printf("    1 -> input name\n");
printf("    2 -> search name\n");
printf("    3 -> delete name\n");
printf("    4 -> show name\n");
printf("    5 -> exit\n");
printf("---------------------------\n\n");

while(1)
{
    printf("What are you going to do? - ");
    scanf("%d",&opr);
    switch (opr)
    {
        case 1: addname();
                printf("\n");
                break;
        case 2: searchname();
                printf("\n");
                break;
        case 3: deletename();
                printf("\n");
                break;
        case 4: showname();
                printf("\n");
                break;
        case 5: return 0;
        default : printf("---Wrong input---\n");
    }
}
return 0;
}

void addname(void)
{
    char ch=getchar();
    printf("Input one name: ");
    new_node = malloc(sizeof(struct node));
    if(new_node==NULL) printf("---No space left---\n");
    else
    {
    gets(new_node->name);
    new_node->name[0] = toupper(new_node->name[0]);
    new_node->next = frist;
    frist = new_node;
    }
}

void searchname(void)
{
    char ch=getchar();
    int che=0;
    char name[30];
    struct node *fin;
    printf("To find name: ");
    gets(name);
    name[0] = toupper(name[0]);
    for(fin=frist;fin!=NULL;fin=fin->next)
        if(strcmp(fin->name,name)==0) {che=1; break;}
    if(che==1) printf("He/She is in the linked list.\n");
    else printf("He/She isn`t in the linked list.\n");
}

void deletename(void)
{
    char ch=getchar();
    int che=0;
    char name[30];
    struct node *cur,*pre;
    printf("Who`s name you want to delete from the list: ");
    gets(name);
    name[0] = toupper(name[0]);
    for(pre=NULL,cur=frist;cur!=NULL;pre=cur,cur=cur->next)
        if(strcmp(cur->name,name)==0)
        {
            che=1;
            if(pre==NULL)
                frist = frist->next;
            else
            {
            pre->next=cur->next;
            free(cur);
            break;
            }
        }
    if(che==0) printf("This name doesn`t in the list.\n");
}

void showname(void)
{
    struct node *p;
    for(p=frist;p!=NULL;p=p->next)
        printf("%s ",p->name);
}
