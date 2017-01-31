#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

void addition(int num1[300],int num2[300]);
int* subtraction(int num1[300],int num2[300]);
void multiplication(int num1[300],int num2[300]);
void division(int num1[300],int num2[300]);
int num_compare(int num1[300],int num2[300]);

int ans[300];

int main(void)
{
    int i,j;
    int num1_inverse[300],num2_inverse[300],num1[300],num2[300];
    int *sub;
	char ch,opr;

	for(i=0;i<300;i++)
        num1[i] = num2[i] = num1_inverse[i] = num2_inverse[i] = -1;

	for(i=0;;i++)
    {
        ch = getchar();
        if(ch>='0'&&ch<='9')
            num1_inverse[i] = ch - '0';
        else
        {
            opr = ch;
            break;
        }
    }
    for(i=0;;i++)
    {
        ch = getchar();
        if(ch>='0'&&ch<='9')
            num2_inverse[i] = ch - '0';
        else
            break;
    }

    for(i=0;;i++)
        if(num1_inverse[i]<0) break;
    i--;
    for(j=0;i>=0;j++,i--)
        num1[j] = num1_inverse[i];

    for(i=0;;i++)
        if(num2_inverse[i]<0) break;
    i--;
    for(j=0;i>=0;j++,i--)
        num2[j] = num2_inverse[i];

    switch(opr)
    {
        case '+': addition(num1,num2);
                  break;
        case '-': if (num_compare(num1,num2)==-1)
                    {
                        cout<<"-";
                        sub = subtraction(num2,num1);
                        sub += 299;
                        for(i=299;(*sub)==-1&&i>=0;sub--,i--);
                        for(;i>=1;sub--,i--)
                            cout<<(*sub);
                        cout<<(*sub);
                    }
                    else if (num_compare(num1,num2)==1)
                    {
                        sub = subtraction(num1,num2);
                        sub += 299;
                        for(i=299;(*sub)==-1&&i>=0;sub--,i--);
                        for(;i>=0;sub--,i--)
                            cout<<(*sub);
                    }
                    else cout<<"0";

                  break;
        case '*': multiplication(num1,num2);
                  break;
        case '/': division(num1,num2);
                  break;
        default : cout<<"Wrong operation!";
                  break;
    }

	return 0;
}

void addition(int num1[300],int num2[300])
{
    int i,sum_d,carry,che=0,tem[300];

    carry = 0;
    for(i=0;;i++)
    {
        if(num1[i]<0&&num2[i]<0)
            break;
        if(num1[i]<0) num1[i] = 0;
        if(num2[i]<0) num2[i] = 0;
        sum_d = num1[i]+num2[i]+carry;
        carry = sum_d/10;
        ans[i] = sum_d%10;
    }
    if(carry!=0)
    {
        ans[i] = carry;
        che = 1;
    }

    if(che==0) i--;
    for(;i>=0;i--)
        cout<<ans[i];

    return;
}

int* subtraction(int num1[300],int num2[300])
{
    int i,j,k,che=0;
    for(i=0;i<300;i++)
        ans[i] = -1;
    for(i=0;;i++)
    {
        if(num1[i]<0&&num2[i]<0)
            break;
        if(num1[i]<0) num1[i] = 0;
        if(num2[i]<0) num2[i] = 0;

        if(num1[i]>=num2[i])
            ans[i] = num1[i] - num2[i];
        else    /*small-big in digit*/
        {
            for(j=1;;j++)
            {
                if(num1[i+j]>0)
                {
                    num1[i+j]--;
                    for(j--;j>=1;j--)
                        num1[i+j] = 9;
                    ans[i] = 10+num1[i]-num2[i];
                    break;
                }
            }
        }
    }
    for(i=299;ans[i]==-1;i--);
    for(;ans[i]==0;i--)
        ans[i] = -1;

    return ans;
}

void multiplication(int num1[300],int num2[300])
{
    int i,j,k,carry;
    for(i=0;i<300;i++)
        ans[i] = 0;

    for(i=0;num2[i]>=0;i++)
    {
        for(j=0;num1[j]>=0;j++)
        {
            ans[i+j] += num1[j]*num2[i];
        }
    }

    for(i=0;i<300;i++)
    {
        if(ans[i]>9)
        {
            ans[i+1] += ans[i]/10;
            ans[i] = ans[i]%10;
        }
    }

    for(k=299;ans[k]==0;k--);
    for(;k>=1;k--)
        cout<<ans[k];
    cout<<ans[0];
    return;
}

void division(int num1[300],int num2[300])
{
    int i,j,zero[300];
    for(i=0;i<300;i++)
    {
        ans[i] = 0;
        zero[i] = -1;
    }
    zero[0] = 0;

    j = 0;
    while(num_compare(num1,zero)>=0)
    {
        for(i=0;;i++)
        {
            if(num1[i]>num2[i]) num1[i] = num1[i] - num2[i];
        }
        if(ans[j]==9) {ans[j]=0; j++; ans[j]++;}
        else ans[j]++;
    }

    for(i=299;ans[i]==0;i--);
    for(;i>=0;i--)
        cout<<ans[i];

    return;
}

int num_compare(int num1[300],int num2[300])
{
    int i,res=0;
    for(i=299;i>=0;i--)
    {
        if(num1[i]>num2[i]) {res = 1; break;}
        else if(num1[i]<num2[i]) {res = -1; break;}
    }
    return res;
}
