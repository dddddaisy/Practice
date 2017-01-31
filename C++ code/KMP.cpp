#include <iostream>
using namespace std;

void FailureFunction(char pattern[],int f[],int len);
int KMP(char text[],char pattern[],int Tlen,int Plen,int f[]);

int main(void)
{
    int i,Plen,Tlen,result;
    char pattern[8],text[20];
    char c;

    cout<<"Welcome to KMP`s world"<<endl;
    cout<<"Pattern : ";
    i = 0;
    while(1)
    {
        cin.get(c);
        if(c=='\n'||c=='\0') break;
        pattern[i] = c;
        i++;
    }
    Plen = i;
    cout<<"Text : ";
    i = 0;
    while(1)
    {
        cin.get(c);
        if(c=='\n'||c=='\0') break;
        text[i] = c;
        i++;
    }
    Tlen = i;

    /*Here we go*/
    int f[Plen];
    FailureFunction(pattern,f,Plen);
    result = KMP(text,pattern,Tlen,Plen,f);
    if(result==-1) cout<<"Can`t find pattern in the given text."<<endl;
    else cout<<"Pattern is start from ["<<result<<"] in th given text."<<endl;

    return 0;
}

void FailureFunction(char pattern[],int f[],int len)
{
    int i,j,a,b,Max,cou;

    f[0] = -1;
    for(i=1;i<len;i++)
    {
        Max = -1;
        for(j=i;j>0;j--)
        {
            a = i;
            b = 0+(i-j);
            cou = -1;
            while(pattern[a]==pattern[b] && b>=0) {a--; b--; cou++;}
            if(b==-1 && cou>Max) Max = cou;
        }
        f[i] = Max;
    }
}

int KMP(char text[],char pattern[],int Tlen,int Plen,int f[])
{
    int i,j;

    for(i=0,j=0;i<Tlen&&j<Plen;i++,j++)
    {
        if(text[i]!=pattern[j])
        {
            if(j-1>=0) {i--; j--; j=f[j];}
            else j = -1;
        }
        if(j==Plen-1) return i-j;
    }

    return -1;
}
