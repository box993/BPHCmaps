#include <bits/stdc++.h>
using namespace std;

class Node{
public:
    string name;
    int nodeId;
    Node(string s, int n){
        name = s;
        nodeId = n;
    }
};

const int numOfNodes = 140;

vector<pair<int,string>> Nodes;
vector<pair<int,int>> adj[140];

void addEdge(vector <pair<int, int> > adj[], int u, int v, int wt)
{
    u--;
    v--;
    adj[u].push_back(make_pair(v, wt));
    adj[v].push_back(make_pair(u, wt));
}

int minDistance(vector<int> dist, vector<bool> sptSet)
{
    int min = INT_MAX, min_index;
    for (int i = 0; i < numOfNodes; i++)
        if (sptSet[i] == false && dist[i] <= min)
            min = dist[i], min_index = i;
    return min_index;
}

void printPath(vector<int> parent, int j)
{
    if (parent[j] == -1)
        return;
    printPath(parent, parent[j]);
    cout << j+1 << " ";
}

void dijkstra(vector<pair<int,int>> adj[], int src, int dst)
{
    src--;
    dst--;
    vector<int> dist(numOfNodes,INT_MAX), parent(numOfNodes,-1);
    vector<bool> sptSet(numOfNodes,false);

    dist[src] = 0;

    for (int count = 0; count < numOfNodes - 1; count++) {

        int u = minDistance(dist, sptSet);
        sptSet[u] = true;

        for (auto v: adj[u]){
            if (!sptSet[v.first] && dist[u] + v.second < dist[v.first]) {
                parent[v.first] = u;
                dist[v.first] = dist[u] + v.second;
            }
        }
            
    }
    cout<<src+1<<" ";
    printPath(parent, dst);
}

int printShortestPath(vector<pair<int,int>> adj[], vector<int> parent, int s, int d)
{
    int level = 0;
    if (parent[s] == -1)
    {
        cout<<s+1<<" ";
        return level;
    }
  
    printShortestPath(adj, parent, parent[s], d);
  
    level++;
    if (s<numOfNodes)
        cout<<s+1<<" ";
  
    return level;
}

int BFS(vector<pair<int,int>> adj[], int src, int dest){

    src--;
    dest--;

    vector<bool> visited(numOfNodes, false);
    vector<int> parent(numOfNodes, -1);

    queue<int> q;
    visited[src] = true;
    q.push(src);
  
    while (!q.empty())
    {
        int s = q.front();
  
        if (s == dest)
            return printShortestPath(adj, parent, s, dest);
  
        q.pop();

        for (auto i: adj[s])
        {
            if (!visited[i.first])
            {
                visited[i.first] = true;
                q.push(i.first);
                parent[i.first] = s;
            }
        }
    }
    return 0;
}

void readnodes(string s, vector<pair<int,string>> nodes){
    
    fstream nodesFile (s, ios::in);
    if(nodesFile.is_open())
    {
        string line, word;        
        while(getline(nodesFile, line))
        {
            stringstream str(line); 
            vector<string> row; 
            while(getline(str, word, ',')) row.push_back(word);
            Nodes.push_back(make_pair(stoi(row[0]),row[1]));
        }        
    }
    else cout<<"Error-Nodes\n";
}

void readedges(string s, vector<pair<int,int>> adj[]){
    fstream edgesFile (s, ios::in);
    if(edgesFile.is_open())
    {
        string line, word;        
        while(getline(edgesFile, line))
        {
            stringstream str(line); 
            vector<string> row; 
            while(getline(str, word, ',')) row.push_back(word);
            addEdge(adj,stoi(row[0]),stoi(row[1]),stoi(row[2]));
        }        
    }
    else cout<<"Error-Edges\n";
}

int main()
{
    cout<<"Nodes file: ";
    string nodes;cin>>nodes;
    readnodes(nodes,Nodes);    

    cout<<"Edges file: ";
    string edges;cin>>edges;
    readedges(edges,adj);  

    bool stch = false, edch = false;
    int st,ed;cin>>st>>ed;
    // for(auto i: Nodes) cout<<i.second<<endl;
    // while(!stch and !edch){
    //     string start, end;
    //     cout<<"Enter Start location:";
    //     cin>>start;
    //     cout<<"Enter Destination:";
    //     cin>>end;        
        
    //     for(auto i: Nodes){
    //         if(i.second==start){
    //             st = i.first;
    //             stch = true;
    //         }
    //         if(i.second==end){
    //             ed = i.first;
    //             edch=true;
    //         }
    //     }
    //     cout<<endl;
    //     if(stch == false) cout<<"Enter valid start\n";
    //     if(edch == false) cout<<"Enter valid destination\n";
    //     cout<<endl;
    // }
    BFS(adj,st,ed);
    int yes;cin>>yes;
    return 0;
}