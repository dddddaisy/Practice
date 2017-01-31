#include <iostream>
#include <cstdio>
#include <bitset>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct ExtractNode
{
    bool ForSymbol;
    char symbol;
    int ToLeftIdx;
    int ToRightIdx;
};

int main(void)
{
    int i;
    int ignore,SizeNum;
    char c,bit;
    vector<ExtractNode> ExtractTable;
    FILE *f;
    f = fopen("C:\\Users\\USER\\Desktop\\ZIP","rb");

    fread(&ignore, sizeof(int),1,f);
    fread(&SizeNum, sizeof(int),1,f);

    ExtractNode tmp;
    for(i=0;i<SizeNum+1;i++)
    {
        fread(&tmp, sizeof(ExtractNode), 1, f);
        ExtractTable.push_back(tmp);
    }
    cout << "Table Information" << endl;
    for(i=0;i<SizeNum+1;i++)
    {
        cout << i << " -> ";
        cout << ExtractTable[i].ForSymbol << " ";
        cout << ExtractTable[i].symbol << " ";
        cout << ExtractTable[i].ToLeftIdx << " ";
        cout << ExtractTable[i].ToRightIdx << endl;
    }

    while(1)
    {
        fread(&c, sizeof(char), 1, f);
        for(i=0;i<8;i++)
        {
            bit = ((c&(1<<(7-i)))? '1': '0');
            cout << bit ;
        }
        cout << endl; ;
        if(feof(f)) break;
    }
    cout << "ignore = " << ignore << endl;
    cout << "SizeNum = " << SizeNum << endl;

    return 0;
}

