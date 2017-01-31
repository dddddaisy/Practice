#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

class HugeInteger
{
private:
    char num[300];
    int length;
public:
    HugeInteger(){};
    HugeInteger(char* N);
public:
       friend  bool     operator >  (const HugeInteger& A,const HugeInteger& B);
       friend  bool     operator <  (const HugeInteger& A,const HugeInteger& B);
       HugeInteger&     operator =  (const HugeInteger& A);
    friend ostream&     operator << (ostream &output,const HugeInteger& A);
};

HugeInteger::HugeInteger(char* N)
{
    int i,j;
    for(i=0;N[i]!='\0';i++);
    this->length = i;
    for(i=0;i<299-this->length;i++)
        this->num[i] = '0';
    for(j=0;i<300;i++,j++)
        this->num[i] = N[j];
}



bool operator > (const HugeInteger& A,const HugeInteger& B)
{
    int i;
    if(A.length > B.length) return true;
    else if(A.length < B.length) return false;
    else
    {
        i = 0;
        while(A.num[i]=='0'&&B.num[i]=='0') i++;
        for(;i<300;i++)
        {
            if(A.num[i]>B.num[i]) return true;
            else if (A.num[i]<B.num[i]) return false;
        }
    }
}

bool operator < (const HugeInteger& A,const HugeInteger& B)
{
    int i;
    if(A.length < B.length) return true;
    else if(A.length > B.length) return false;
    else
    {
        i = 0;
        while(A.num[i]=='0'&&B.num[i]=='0') i++;
        for(;i<300;i++)
        {
            if(A.num[i]<B.num[i]) return true;
            else if (A.num[i]>B.num[i]) return false;
        }
    }
}

HugeInteger& HugeInteger::operator = (const HugeInteger& A)
{
    int i;
    for(i=0;i<300;i++)
        this->num[i] = A.num[i];
    return *this;
}

ostream& operator << (ostream &output,const HugeInteger& A)
{
    int i=0;
    while(A.num[i]=='0') i++;
    for(;i<=299;i++)
        output<<A.num[i];
}

template<class T> void sortNumber(T *arr,int length)
{
    int i,j;
    T tem;

    /*start sort*/
    for(i=0;i<length;i++)
        for(j=i+1;j<length;j++)
    {
        if(arr[i]>arr[j])
        {
           tem = arr[j];
           arr[j] = arr[i];
           arr[i] = tem;
        }
    }

    return;
}

int main(void)
{
	// integer
	int val[10] = {11 , 32 , 5 , 8 , 2 , 10 , 23 , 87 , 12 , 2};
	sortNumber(val , 10);

	for (int i = 0 ; i < 10 ; i++)
		cout << val[i] << " ";

	cout << endl;

	// Huge integer
	HugeInteger huge[6] = {"12087" , "1389" , "99783" , "870843" , "3338765" , "93673"};
	sortNumber(huge , 6);

	for (int i = 0 ; i < 6 ; i++)
		cout << huge[i] << " ";

	cout << endl;

	// other unknown fundamental types, will be given by TA after your codes are uploaded
    return 0;
}
