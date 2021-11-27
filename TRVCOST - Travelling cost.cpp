#include <cstdio>
#include <iostream>
#include <queue>

using namespace std;


struct heapNode
{
    int id;
    int dist;
    
    heapNode(int id, int dist)
    {
        this->id=id;
        this->dist=dist;
    }
};

struct compare
{
    bool operator() (heapNode a, heapNode b)
    {
        return a.dist>b.dist;
    }
};

int N;
int cost[501][501]={0};
priority_queue<heapNode, vector<heapNode>, compare > pq;
bool visited[501]={false};
int result[501] = {0};

int getNextInt()
{
    char c = getchar();
    while (c<'0' || c>'9') c=getchar();
    int result=0;
    while (c>='0' && c<='9')
    {
        result = (result<<3) + (result<<1) + (c-'0');
        c=getchar();
    }
    
    return result;
}

void dijkstra(int startNode)
{
    heapNode source(startNode, 0);
    pq.push(source);
    result[startNode]=0;
    
    while(!pq.empty())
    {
        heapNode top=pq.top();
        int topId = top.id;
        int topDist = top.dist;
        pq.pop();
        
        // This node was already visited with a better distance (guranteed by min heap property). Ignore.
        // why can we have this situation? because a node may get pushed into heap multiple times
        // in case we found a better path to it after the node was already pushed into the heap.
        if (visited[topId])
        {
            continue;
        }
        
        visited[topId]=true;
        
        for (int i=0; i<501; i++)
        {
            // There is a path between node 'topId' and node 'i'
            // But only push it if the distance can be improved.
            if (cost[topId][i] != 0
                && (result[i] == -1 || result[i] > topDist+cost[topId][i]))
            {
                heapNode temp(i, cost[topId][i]+topDist);
                pq.push(temp);
                result[i]=topDist+cost[topId][i];
            }
        }
    }
}

int main()
{
    N = getNextInt();
    
    for (int i=0; i<501; i++) result[i]=-1;
    
    for (int i=1; i<=N; i++)
    {
        int a,b,w;
        a=getNextInt(); b=getNextInt(); w=getNextInt();
        cost[a][b]=cost[b][a]=w;
    }
    
    int startNode=getNextInt();
    dijkstra(startNode);
    int Q=getNextInt();
    for (int i=1; i<=Q; i++)
    {
        int v=getNextInt();
        if (visited[v])
        {
            printf("%d\n", result[v]);
        }
        else
        {
            printf("NO PATH\n");
        }
    }
    
    return 0;
}
