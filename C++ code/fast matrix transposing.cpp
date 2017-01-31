#include <iostream>
using namespace std;

void transpose(int Msize,int Melement,int ori[][3],int ans[][3]);

int main(void)
{
    int i,j;
    int Msize,Melement;

    cout<<"Matrix size: ";
    cin>>Msize;
    cout<<"Elements number: ";
    cin>>Melement;
    int ori[Melement][3],ans[Melement][3];

    cout<<"Input matrix: (row col value)"<<endl;
    for(i=0;i<Melement;i++)
        for(j=0;j<3;j++)
        {
            cin>>ori[i][j];
            ans[i][j] = 0;
        }

    cout<<"Transposing matrix: (row col value)"<<endl;
    transpose(Msize,Melement,ori,ans);
    /*show the result*/
    for(i=0;i<Melement;i++)
            cout<<ans[i][0]<<" "<<ans[i][1]<<" "<<ans[i][2]<<endl;

    return 0;
}

void transpose(int Msize,int Melement,int ori[][3],int ans[][3])
{
    int rowsize[Msize],rowstart[Msize];
    int i,NewRank;
    for(i=0;i<Msize;i++)
        rowsize[i] = rowstart[i] = 0;

    /*prepare*/
    for(i=0;i<Melement;i++)
        rowsize[ori[i][1]]++;

    rowstart[0] = 0;
    for(i=1;i<Msize;i++)
        rowstart[i] = rowsize[i-1]+rowstart[i-1];
    /*start transpose*/
    for(i=0;i<Melement;i++)
    {
        NewRank = rowstart[ori[i][1]];
        rowstart[ori[i][1]]++;
        ans[NewRank][0] = ori[i][1];
        ans[NewRank][1] = ori[i][0];
        ans[NewRank][2] = ori[i][2];
    }
}
