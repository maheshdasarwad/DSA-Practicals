#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>

using namespace std;

class GraphSearch {
    vector<int> AdjList[9]; // Adjacency list to represent the graph
    string Landmark[9] = {"Gate", "SmartStore", "Dypcoe", "OpenTheater", "Diploma", "CafetArea", "Pharmacy", "Dypimr", "ArtsCollege"};

public:
    // Function to add an undirected edge in the graph
    void AddEdge(int u, int v) {
        AdjList[u].push_back(v);
        AdjList[v].push_back(u);
    }

    // Depth First Search (DFS)
    void depthFirstSearch(int start) {
        vector<bool> visited(9, false);
        stack<int> st;
        st.push(start);
        visited[start] = true;

        cout << "\nDFS Traversal ----> " << endl;
        while (!st.empty()) {
            int node = st.top();
            st.pop();
            cout << Landmark[node] << " ";

            for (int i = AdjList[node].size() - 1; i >= 0; i--) {
                int neighbor = AdjList[node][i];
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    st.push(neighbor);
                }
            }
        }
        cout << endl;
    }

    // Breadth First Search (BFS)
    void breadthFirstSearch(int start) {
        vector<bool> visited(9, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;

        cout << "\nBFS Traversal ----> " << endl;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << Landmark[node] << " ";

            for (int i = 0; i < AdjList[node].size(); i++) {
                int neighbor = AdjList[node][i];
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }

    // Function to display the adjacency list
    void display() {
        cout << "\nThe Adjacency List ---> \n";
        for (int i = 0; i < 9; i++) {
            cout << Landmark[i] << " -> [ ";
            for (int j = 0; j < AdjList[i].size(); j++) {
                cout << Landmark[AdjList[i][j]] << " ";
            }
            cout << "]" << endl;
        }
    }
};

int main() {

    // Create an object of GraphSearch to perform DFS and BFS
    GraphSearch map;

    // Adding edges based on the given college map adjacency (undirected graph)
    map.AddEdge(0, 1);  // Gate <-> SmartStore
    map.AddEdge(0, 8);  // Gate <-> ArtsCollege
    map.AddEdge(1, 2);  // SmartStore <-> Dypcoe
    map.AddEdge(2, 3);  // Dypcoe <-> OpenTheater
    map.AddEdge(2, 4);  // Dypcoe <-> Diploma
    map.AddEdge(3, 4);  // OpenTheater <-> Diploma
    map.AddEdge(3, 6);  // OpenTheater <-> Pharmacy
    map.AddEdge(4, 5);  // Diploma <-> CafetArea
    map.AddEdge(5, 6);  // CafetArea <-> Pharmacy
    map.AddEdge(6, 7);  // Pharmacy <-> Dypimr
    map.AddEdge(7, 8);  // Dypimr <-> ArtsCollege
    map.AddEdge(8, 0);  // ArtsCollege <-> Gate

    // Display the graph using adjacency list
    map.display();

    // Perform DFS and BFS starting from Gate (node 0)
    map.depthFirstSearch(0);  // Starting DFS from "Gate"
    map.breadthFirstSearch(0);  // Starting BFS from "Gate"

    return 0;
}
