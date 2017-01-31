#include <iostream>
#include <cstdio>
#include <cstdlib>
#define INF 1000000000
using namespace std;

typedef struct
{
    int v1;
    int v2;
    int weight;
    //bool choose = false;
}EdgeData;

void minSpanningTree(int VertexNum, int EdgeNum, EdgeData edge[]);
void ShortestPath(int VertexNum, int EdgeNum, EdgeData edge[], int start, int terminal);

int main(int argc,char* argv[])
{
    int i;
    char c,data[4];
    int VertexNum,EdgeNum;
    int v1,v2;
    bool run;

    FILE *graph;
    graph = fopen(argv[1],"r");
    if(!graph) {cout<<"open file "<<argv[1]<<" faile"<<endl; return 0;}

    run = true;
    while(run)
    {
        fscanf(graph,"%d\n",&VertexNum);
        fscanf(graph,"%d\n",&EdgeNum);
        EdgeData edge[EdgeNum];

        for(i=0;i<EdgeNum;i++)
            fscanf(graph,"%d %d %d\n",&edge[i].v1,&edge[i].v2,&edge[i].weight);

        /*show min spanning tree*/
        minSpanningTree(VertexNum,EdgeNum,edge);
        cout<<endl;

        while(1)
        {
            c = fgetc(graph);
            if(c=='z'||c=='Z') {run=true; break;}
            else if(c=='x'||c=='X') {run=false; break;}
            else
            {
                v1 = c - '0'; //start vertex
                c = fgetc(graph);  /*eat space*/
                c = fgetc(graph);  /*eat v2*/
                v2 = c - '0'; //end vertex
                c = fgetc(graph);  /*eat '\n'*/

                /*show shortest path*/
                ShortestPath(VertexNum,EdgeNum,edge,v1,v2);
                cout<<endl;
           }
        }
        cout<<endl;
   }

    return 0;
}

void minSpanningTree(int VertexNum, int EdgeNum, EdgeData edge[])
{
    int i,j,road;
    int _min,index;
    bool flag;
    /*initial prepare*/
    int WeightTable[VertexNum][VertexNum];
    bool visit[VertexNum];
    int parent[VertexNum],d[VertexNum];

    for(i=0;i<VertexNum;i++)
    {
        visit[i] = false;
        parent[i] = -1;
        d[i] = INF;
    }
    for(i=0;i<VertexNum;i++)
        for(j=0;j<VertexNum;j++)
            WeightTable[i][j] = INF;

    for(i=0;i<EdgeNum;i++)
    {
        WeightTable[edge[i].v1][edge[i].v2] = edge[i].weight;
        WeightTable[edge[i].v2][edge[i].v1] = edge[i].weight;
    }

    /*start*/
    parent[0] = 0;
    d[0] = 0;

    for(road=0;road<VertexNum-1;road++)
    {
        index = -1;
        _min = INF;
        for(i=0;i<VertexNum;i++)
        {
            if(!visit[i]&&d[i]<_min)
            {
                _min = d[i];
                index = i;
            }
        }

        if(index==-1) break;
        visit[index] = true;

        for(i=0;i<VertexNum;i++)
        {
            if(!visit[i]&&WeightTable[index][i]<d[i])
            {
                d[i] = WeightTable[index][i];
                parent[i] = index;
            }
        }
    }

    /*output ans*/
    flag = true;
    for(i=0;i<VertexNum;i++)
        if(d[i]==INF) flag = false;

    if(flag)
    {
        for(i=0;i<VertexNum;i++)
        {
            if(i!=parent[i])
                cout<<'('<<parent[i]<<','<<i<<"); ";
        }
    }
    else cout<<"No spanning tree";
}

void ShortestPath(int VertexNum, int EdgeNum, EdgeData edge[], int start, int terminal)
{
    int i,j,root,_min;
    bool endflag;
    /*initial prepare*/
    bool done[VertexNum];
    int path[VertexNum],parent[VertexNum];
    int WeightTable[VertexNum][VertexNum];
    for(i=0;i<VertexNum;i++)
    {
        done[i] = false;
        path[i] = INF;
        parent[i] = -1;
    }
    for(i=0;i<VertexNum;i++)
        for(j=0;j<VertexNum;j++)
            WeightTable[i][j] = INF;
    for(i=0;i<EdgeNum;i++)
    {
        WeightTable[edge[i].v1][edge[i].v2] = edge[i].weight;
        WeightTable[edge[i].v2][edge[i].v1] = edge[i].weight;
    }

    /*start*/
    done[start] = true;
    path[start] = 0;
    parent[start] = start;

    root = start;
    while(1)
    {
        for(i=0;i<VertexNum;i++)
        {
            if(!done[i]&&(path[root]+WeightTable[root][i]<path[i]))
            {
                path[i] = path[root] + WeightTable[root][i];
                parent[i] = root;
            }
        }

        _min = INF;
        for(i=0;i<VertexNum;i++)
        {
            if(!done[i]&&path[i]<_min)
            {
                _min = path[i];
                root = i;
            }
        }
        done[root] = true;


        endflag = true;
        for(i=0;i<VertexNum;i++)
            if(!done[i]) endflag = false;

        if(endflag) break;
        if(_min==INF) break;
    }

    /*output answer*/

    int AnsArr[VertexNum];
    int v;
    bool flag;

    v = terminal;
    flag = true;
    for(i=0;;i++)
    {
        AnsArr[i] = v;
        v = parent[v];
        if(v==-1) {flag=false; break;}
        if(v==start) break;
    }
    AnsArr[i+1] = start;

    if(flag)
    {
        for(;i>=0;i--)
            cout<<'('<<AnsArr[i+1]<<','<<AnsArr[i]<<"); ";
    }
    else cout<<"Not exist";

}
