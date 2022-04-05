#include <bits/stdc++.h>
using namespace std;

class Node{
public:
    string name;
    int nodeId;
    Node(string n, int id){
        n = name;
        id = nodeId;
    }
};

//const int numOfNodes = 4;

vector<Node> Nodes;
vector<int> adj[4];
vector<int> djikstra;

void addEdge(vector<int> adj[], Node u, Node v/*, int distance*/){ //creates a road b/w two nodes
    adj[u.nodeId].push_back(v.nodeId);
    adj[v.nodeId].push_back(u.nodeId);
}

void initialise(){    //add all nodes here with their name and id, id is for connecting as you cant connect with their names
                      
    Node Vk("Vk", 0);
    Nodes.push_back(Vk);

    cout<<"apel";

    Node Vm("Vm", 1);
    Nodes.push_back(Vm);

    Node Shankar("Shankar", 2);
    Nodes.push_back(Shankar);

    Node Vyas("Vyas", 3);    
    Nodes.push_back(Vyas);
    
    addEdge(adj, Vk, Vm/*, 100*/); //connecting nodes with edges that have a road b/w them
    addEdge(adj, Vyas, Shankar/*, 50*/);
    addEdge(adj, Vk, Vyas/*, 50*/);
    addEdge(adj, Shankar, Vm/*, 50*/);
}

// void Djikstras(vector<int> adj[], Node start, Node end){

// }

// int printShortestPath(vector<int> adj[], int parent[], int s, int d)
// {
//     static int level = 0;
  
//     // If we reached root of shortest path tree
//     if (parent[s] == -1)
//     {
//         cout << "Shortest Path between " << s << " and "
//              << d << " is "  << s << " ";
//         return level;
//     }
  
//     printShortestPath(adj, parent, parent[s], d);
  
//     level++;
//     if (s < numOfNodes)
//         cout << s << " ";
  
//     return level;
// }

// int BFS(vector<int> adj[], int src, int dest){

//     bool *visited = new bool[2*numOfNodes];
//     int *parent = new int[2*numOfNodes];

//     for (int i = 0; i < 2*numOfNodes; i++)
//     {
//         visited[i] = false;
//         parent[i] = -1;
//     }

//     queue<int> q;
//     visited[src] = true;
//     q.push(src);
  
//     while (!q.empty())
//     {
//         int s = q.front();
  
//         if (s == dest)
//             return printShortestPath(adj, parent, s, dest);
  
//         q.pop();

//         for (auto i: adj[s])
//         {
//             if (!visited[i])
//             {
//                 visited[i] = true;
//                 q.push(i);
//                 parent[i] = s;
//             }
//         }
//     }
//     return 0;
// }

void printGraph(vector<int> adj[], int V) //for debugging purposes only
{
    for (int v = 0; v < V; ++v) {
        cout <<Nodes[v].name<<endl;
        for (auto x : adj[v])
            cout <<Nodes[x].name<<" ";
        cout<<endl;
    }
}

int main()
{
    initialise();
    printGraph(adj, 4);
    return 0;
}