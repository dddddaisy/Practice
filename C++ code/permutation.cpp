#include <iostream>
#include <string>
using namespace std;

void SWAP(char &a, char &b);
void permute(char *str, int l, int r);

int main(void)
{
    int len;

    while(len)
    {
        cout<<"string length: ";
        cin>>len;
        char a[len];
        cout<<"string want to permute: ";
        cin>>a;
        permute(a,0,len-1);
    }

    return 0;
}

void SWAP(char &a, char &b)
{
    char m;
    m=b; b=a; a=m;
}

void permute(char *str, int l, int r)
{
    int i;
    if(l==r)
        cout<<str<<endl;
    else
    {
        for(i=l;i<=r;i++)
        {
            SWAP(str[l],str[i]);
            permute(str,l+1,r);
            SWAP(str[i],str[l]);
        }
    }
}
