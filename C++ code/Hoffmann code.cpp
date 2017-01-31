#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <queue>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <math.h>
using namespace std;

// struct //
class Node
{
public:
    char symbol;
    int frequence;
    char ParentCode;

    Node* left;
    Node* right;
    Node* parent;
};

class TableNode
{
public:
    char symbol;
    string code;
};

class ExtractNode
{
public:
    bool ForSymbol;
    char symbol;
    int ToLeftIdx;
    int ToRightIdx;
};

// function prototypes //
void DoCompress(char FileName[]);
void DoExtract(char FileName[]);
void Quicksort(vector<Node> &data, int left, int right);
void SWAP(Node& a, Node& b);
Node HuffmanTree(vector<Node> &data, vector<Node*> &leaf);
void BuildHuffmanCodeTable(vector<Node*> &leaf, vector<TableNode> &table);
void BuildTreeDataWithVector(ExtractNode ExtractTable[], Node* root, int idx);
int ComputeSizeNum(int TreeNodeCount);

int main(int argc, char *argv[])
{
    char job;

    cout << "What you want to do with your file?" << endl;
    cout << "   1 - compress" << endl;
    cout << "   2 - extract" << endl;
    cout << "I want to : " ;
    cin >> job;
    switch(job)
    {
    case '1' :
        DoCompress(argv[1]);
        break;
    case '2':
        DoExtract(argv[1]);
        break;
    default:
        cout << "Wrong input!" << endl;
        return 0;
    }

    return 0;
}
void DoCompress(char FileName[])
{
    int i,j;
    char c;
    vector<Node> data;
    vector<Node*> leaf;
    vector<TableNode> table;
    Node root;
    FILE *file, *fzip;

    // Get information I need //
    file = fopen(FileName, "rb");
    if(!file) cout << "Can't open " << FileName << endl;
    while(fread(&c, sizeof(char), 1, file))
    {
        for(i=0;i<data.size();i++)
            if(data[i].symbol == c) { data[i].frequence++; break; }
        if(i==data.size())
        {
            Node tmp;
            tmp.symbol = c;
            tmp.frequence = 1;
            tmp.ParentCode = 'x';
            tmp.left = tmp.right = tmp.parent = NULL;
            data.push_back(tmp);
        }
    }
    fclose(file);

    root = HuffmanTree(data,leaf);
    root.parent = NULL;
    root.ParentCode = 'x';

    BuildHuffmanCodeTable(leaf,table);

    // Do Compress //
    /********************************************************************
     *         --ZIP FILE (fzip)--                                      *
     *           how many bits to ignore (ignore)                       *
     *           tree data size  (SizeNum)                              *
     *           tree data                                              *
     *           content                                                *
     ********************************************************************/
    int TreeNodeCount = 0;
    int SizeNum = 0;
    int ignore = 0;
    char word;
    queue<char> bitQ;
    string WriteString;

    file = fopen(FileName, "rb");
    if(!file) cout << "Can't open " << FileName << endl;
    fzip = fopen("ZIP","wb");
    if(!fzip) cout << "ZIP open failed" << endl;

    // write tree data //
    TreeNodeCount = 0;
    for(i=0;i<table.size();i++)
        if(table[i].code.size() > TreeNodeCount) TreeNodeCount = table[i].code.size();
    SizeNum = ComputeSizeNum(TreeNodeCount);
    fwrite(&SizeNum, sizeof(int), 1, fzip);
    fwrite(&SizeNum, sizeof(int), 1, fzip);

    ExtractNode ExtractTable[SizeNum+1];
    for(int i=0;i<SizeNum+1;i++)
    {
        ExtractTable[i].ForSymbol = false;
        ExtractTable[i].symbol = 'x';
        ExtractTable[i].ToLeftIdx = -1;
        ExtractTable[i].ToRightIdx = -1;
    }
    BuildTreeDataWithVector(ExtractTable, &root, 0);
    fwrite(ExtractTable, sizeof(ExtractNode), sizeof(ExtractTable)/sizeof(ExtractNode), fzip);

    cout << "size = " << sizeof(ExtractTable) << " bytes" << endl;//hereeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee

    // write compressed content //
    while(fread(&c, sizeof(char), 1, file))
    {
        for(i=0;i<table.size();i++)
    	    if(table[i].symbol == c) break;
   	    if(i!=table.size())
	    {
            for(j=0;j<table[i].code.size();j++)
       	        bitQ.push(table[i].code[j]);
   		}
	    while(bitQ.size()>=8)
        {
       	    WriteString.clear();
           	for(j=0;j<8;j++)
	        {
                WriteString.push_back(bitQ.front());
       	        bitQ.pop();
          	}
            bitset<8> WriteBit(WriteString);
           	word = WriteBit.to_ulong();
			fwrite(&word,1,1,fzip);
        }
    }
    
    if(bitQ.size()!=0)
    {
    	ignore = 8 - bitQ.size();
        while(bitQ.size()!=8)
            bitQ.push('0');
        WriteString.clear();
        for(j=0;j<8;j++)
        {
            WriteString.push_back(bitQ.front());
            bitQ.pop();
        }
        bitset<8> WriteBit(WriteString);
        word = WriteBit.to_ulong();
        fwrite(&word,1,1,fzip);
    }
    fseek(fzip, 0, SEEK_SET);
    fwrite(&ignore, sizeof(int), 1, fzip);

    fclose(file);
    fclose(fzip);

    cout << "Compress Finish!!" << endl;
}

void DoExtract(char FileName[])
{
    string FileNameAfterExtract;
    cout << "File name after extract is : " ;
    cin >> FileNameAfterExtract;
    /********************************************************************
     *         --ZIP FILE (fzip)--                                      *
     *           how many bits to ignore (ignore)                       *
     *           tree data size  (SizeNum)                              *
     *           tree data                                              *
     *           content                                                *
     ********************************************************************/
    int i;
    int ignore,SizeNum,FileLength;
    int ptr;
    char Cnow,Cnext,bit,wri;
    string word;
    queue<char> WaitForWrite;
    FILE *file,*fori;

    file = fopen(FileName, "rb");
    if(!file) cout << "Can't open " << FileName << endl;
    fori = fopen(FileNameAfterExtract.c_str(),"wb");
    if(!fori) cout << "Can't open " << FileNameAfterExtract << endl;

    // read information I need //
    fread(&ignore, sizeof(int),1,file);
    fread(&SizeNum, sizeof(int),1,file);
    ExtractNode ExtractTable[SizeNum+1];
    fread(ExtractTable, sizeof(ExtractNode), sizeof(ExtractTable)/sizeof(ExtractNode), file);

    // read content and write extract file //
    ptr = 0;
    fread(&Cnow, sizeof(char), 1, file);
    while(1)
    {
        fread(&Cnext, sizeof(char), 1, file);
        if(feof(file))
        {
            for(i=0;i<8-ignore;i++)
            {
                bit = ((Cnow&(1<<(7-i)))? '1': '0');
                if(bit=='0')
                    ptr = ExtractTable[ptr].ToLeftIdx;
                else if(bit=='1')
                    ptr = ExtractTable[ptr].ToRightIdx;

                if(ExtractTable[ptr].ForSymbol)
                {
                    WaitForWrite.push(ExtractTable[ptr].symbol);
                    ptr = 0;
                }
            }
        }
        else
        {
            for(i=0;i<8;i++)
            {
                bit = ((Cnow&(1<<(7-i)))? '1': '0');
                if(bit=='0')
                    ptr = ExtractTable[ptr].ToLeftIdx;
                else if(bit=='1')
                    ptr = ExtractTable[ptr].ToRightIdx;
                if(ExtractTable[ptr].ForSymbol)
                {
                    WaitForWrite.push(ExtractTable[ptr].symbol);
                    ptr = 0;
                }
            }
            Cnow = Cnext;
        }

        while(WaitForWrite.size()!=0)
        {
            wri = WaitForWrite.front();
            WaitForWrite.pop();
            fwrite(&wri, sizeof(char), 1, fori);
        }

        if(feof(file)) break;
    }
    fclose(file);
    fclose(fori);

    cout << "Extract Finish!!" << endl;
}

void Quicksort(vector<Node> &data, int left, int right)
{
    int pivot, i, j;
	if(left < right)
	{
		pivot = data[left].frequence;
		i = left + 1;
		j = right;

		while(1)
		{
			while(i<=right)
			{
				if(data[i].frequence > pivot) break;
				i++;
			}
			while(j>left)
			{
				if(data[j].frequence < pivot) break;
				j--;
			}

			if(i > j) break;
			SWAP(data[i],data[j]);
		}

		SWAP(data[left],data[j]);
		Quicksort(data, left, j-1);
		Quicksort(data, j+1, right);
	}
	else return;
}

void SWAP(Node& a, Node& b)
{
	Node tmp;
	tmp = a; a = b; b = tmp;
}

Node HuffmanTree(vector<Node> &data, vector<Node*> &leaf)
{
    int i,m,n;
    Node tmp;
    Node *LeftNode, *RightNode;

    Quicksort(data, 0, data.size()-1);
    for(i=0;i<data.size()-1;i++)
    {
        LeftNode = new Node;
        RightNode = new Node;

        if(data[i].left && data[i].left->left!=NULL && data[i].left->right!=NULL)
            data[i].left->parent = LeftNode;
        else if(data[i].left && data[i].left->left==NULL && data[i].left->right==NULL)
            { data[i].left->parent = LeftNode; leaf.push_back(data[i].left); }
        if (data[i].right && data[i].right->left!=NULL && data[i].right->right!=NULL)
            data[i].right->parent = LeftNode;
        else if(data[i].right && data[i].right->left==NULL && data[i].right->right==NULL)
            { data[i].right->parent = LeftNode; leaf.push_back(data[i].right); }
        if(data[i].left) data[i].left->ParentCode = '0';
        if(data[i].right) data[i].right->ParentCode = '1';
        *LeftNode = data[i];

        if(data[i+1].left && data[i+1].left->left!=NULL && data[i+1].left->right!=NULL)
            data[i+1].left->parent = RightNode;
        else if(data[i+1].left && data[i+1].left->left==NULL && data[i+1].left->right==NULL)
            { data[i+1].left->parent = RightNode; leaf.push_back(data[i+1].left); }
        if (data[i+1].right && data[i+1].right->left!=NULL && data[i+1].right->right!=NULL)
            data[i+1].right->parent = RightNode;
        else if(data[i+1].right && data[i+1].right->left==NULL && data[i+1].right->right==NULL)
            { data[i+1].right->parent = RightNode; leaf.push_back(data[i+1].right); }
        if(data[i+1].left) data[i+1].left->ParentCode = '0';
        if(data[i+1].right) data[i+1].right->ParentCode = '1';
        *RightNode = data[i+1];

        data[i+1].frequence = data[i].frequence + data[i+1].frequence;
        data[i+1].left = LeftNode;
        data[i+1].right = RightNode;
        data[i+1].parent = NULL;

        data[i].frequence = 0;

        // sort //
        for(m=i+1,n=i+2;data[m].frequence>data[n].frequence && n<data.size();m++,n++)
            SWAP(data[m],data[n]);
    }
    if(data[i].left) { data[i].left->ParentCode = '0'; data[i].left->parent = &data[i]; }
    if(data[i].right) { data[i].right->ParentCode = '1'; data[i].right->parent = &data[i]; }
    return data[i];
}

void BuildHuffmanCodeTable(vector<Node*> &leaf, vector<TableNode> &table)
{
    int i;
    Node* ptr;
    for(i=0;i<leaf.size();i++)
    {
        TableNode tmp;
        tmp.symbol = leaf[i]->symbol;
        ptr = leaf[i];
        while(ptr)
        {
            if(ptr->ParentCode=='0' || ptr->ParentCode=='1')
                tmp.code.push_back(ptr->ParentCode);
            ptr = ptr->parent;
        }
        reverse(tmp.code.begin(),tmp.code.end());
        table.push_back(tmp);
    }
}

void BuildTreeDataWithVector(ExtractNode ExtractTable[], Node* root, int idx)
{
    if(root->left==NULL && root->right==NULL) // leaf //
    {
        ExtractTable[idx].ForSymbol = true;
        ExtractTable[idx].symbol = root->symbol;
        ExtractTable[idx].ToLeftIdx = -1;
        ExtractTable[idx].ToRightIdx = -1;
        return;
    }
    else // not leaf //
    {
        ExtractTable[idx].ForSymbol = false;
        ExtractTable[idx].symbol = '0';
        ExtractTable[idx].ToLeftIdx = (idx*2)+1;
        ExtractTable[idx].ToRightIdx = (idx*2)+2;
        BuildTreeDataWithVector(ExtractTable, root->left, idx*2+1);
        BuildTreeDataWithVector(ExtractTable, root->right, idx*2+2);
    }
}

int ComputeSizeNum(int TreeNodeCount)
{
	int i,ans=0;
	for(i=0;i<TreeNodeCount+1;i++)
		ans += pow(2,i);
	return ans;
}