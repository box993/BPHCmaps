#include <bits/stdc++.h>
using namespace std;
std::ofstream ofs;

class Node
{
public:
    string name;
    int nodeId;
    Node(string s, int n)
    {
        name = s;
        nodeId = n;
    }
};

const int numOfNodes = 140;

vector<pair<int, string>> Nodes;
vector<pair<int, int>> adj[numOfNodes];

void addEdge(vector<pair<int, int>> adj[], int u, int v, int wt)
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
    if (!ofs.is_open())
    {
        ofs.open("path.txt", std::ios_base::app);
    }
    if (parent[j] == -1)
    {
        return;
    }
    printPath(parent, parent[j]);
    cout << j + 1 << " ";
    ofs << j + 1 << " "; //-1
}
int dijkstraDist = 0;
void dijkstra(vector<pair<int, int>> adj[], int src, int dst)
{
    src--;
    dst--;
    vector<int> dist(numOfNodes, INT_MAX), parent(numOfNodes, -1);
    vector<bool> sptSet(numOfNodes, false);

    dist[src] = 0;

    for (int count = 0; count < numOfNodes - 1; count++)
    {

        int u = minDistance(dist, sptSet);
        sptSet[u] = true;

        for (auto v : adj[u])
        {
            if (!sptSet[v.first] && dist[u] + v.second < dist[v.first])
            {
                parent[v.first] = u;
                dist[v.first] = dist[u] + v.second;
            }
        }
    }
    dijkstraDist = dist[dst];
    if (!ofs.is_open())
    {
        ofs.open("path.txt", std::ios_base::app);
    }
    cout << src + 1 << " ";
    ofs << src + 1 << " "; // 0
    printPath(parent, dst);
}

int BFSdistance = 0;

int printShortestPath(vector<pair<int, int>> adj[], vector<int> parent, int s, int d)
{
    if (!ofs.is_open())
    {
        ofs.open("path.txt", std::ios_base::app);
    }
    int level = 0;
    if (parent[s] == -1)
    {
        cout << s + 1 << " "; //-2
        ofs << s + 1 << " ";
        return level;
    }

    printShortestPath(adj, parent, parent[s], d);

    level++;
    if (s < numOfNodes)
    {
        cout << s + 1 << " "; //-1
        ofs << s + 1 << " ";
        for (auto x : adj[parent[s]])
        {
            if (x.first == s)
            {
                BFSdistance += x.second;
                break;
            }
        }
    }
    return level;
}

int BFS(vector<pair<int, int>> adj[], int src, int dest)
{

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

        for (auto i : adj[s])
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

void readnodes(string s, vector<pair<int, string>> nodes)
{

    fstream nodesFile(s, ios::in);
    if (nodesFile.is_open())
    {
        string line, word;
        while (getline(nodesFile, line))
        {
            stringstream str(line);
            vector<string> row;
            while (getline(str, word, ','))
                row.push_back(word);
            Nodes.push_back(make_pair(stoi(row[0]), row[1]));
        }
    }
    else
        cout << "Error-Nodes\n";
}

void readedges(string s, vector<pair<int, int>> adj[])
{
    fstream edgesFile(s, ios::in);
    if (edgesFile.is_open())
    {
        string line, word;
        while (getline(edgesFile, line))
        {
            stringstream str(line);
            vector<string> row;
            while (getline(str, word, ','))
                row.push_back(word);
            addEdge(adj, stoi(row[0]), stoi(row[1]), stoi(row[2]));
        }
    }
    else
        cout << "Error-Edges\n";
}

int main()
{
    ofs.open("path.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();

    readnodes("node.csv", Nodes);
    readedges("edges.csv", adj);

    bool stch = false, edch = false;
    int st, ed;
    cout << "Choose start and end location from the following POIs: \nMain Gate\tLibrary\tH-Block\tK-Block\nChess Coutryard Entrance\tWorkshop\tCafeteria\tE-Block\nRock Garden\tD-Block Entrance\tC-Block\tB-Block Entrance\nA-Block Parking\tFootball Ground\tShankar Bhavan\tMess 2\nVyas Bhavan\tWich Please\tVishawakarma Bhavan-Second Entrance\tChipotle\nYumpy's / Thickshake Factory\tGandhi Bhavan\tMess 1\tKrishna Bhavan\nMeera Bhavan\tGanga Bhavan\tMalviya Bhavan\tStudent Activity Center\nSAC Backdoor\tNew Football Ground\tSwimming Pool\tH8 (Staff Quarters)\nH8 Block\tDean's Quarters\tMedical Center\tCricket Ground\nAmul\tMaggi Hotspot\tConnaut Place Entrance 2\tConnaut Place Entrance 1\nTennis Court\tGautum Bhavan\tBasketball Stands\tThrowball Court\nVishawakarma Bhavan Entrance 1\tPhilosopher's Stone\tVolleyball Court\n\n";
    while (!stch and !edch)
    {
        string start, end;
        cout << "Enter Start location:";
        getline(cin, start);
        cout << "Enter Destination:";
        getline(cin, end);

        for (auto i : Nodes)
        {
            if (i.second == start)
            {
                st = i.first;
                stch = true;
            }
            if (i.second == end)
            {
                ed = i.first;
                edch = true;
            }
        }
        cout << endl;
        if (stch == false)
            cout << "Enter valid start\n";
        if (edch == false)
            cout << "Enter valid destination\n";
        cout << endl;
    }
    cout << "Dijkstra Path:\n";
    dijkstra(adj, st, ed);
    if (!ofs.is_open())
    {
        ofs.open("path.txt", std::ios_base::app);
    }
    cout << "\n";
    ofs << "\n"
        << dijkstraDist << "\n";
    BFS(adj, st, ed);
    if (!ofs.is_open())
    {
        ofs.open("path.txt", std::ios_base::app);
    }
    cout << "BFS Path:\n";
    ofs << "\n"
        << BFSdistance << "\n";
    char yes;
    while (yes != EOF)
        cin >> yes;
    return 0;
}