/*

    You have a business with several offices; 
    you want to lease phone lines to connect them up with each other; 
    and the phone company charges different amounts of money to connect 
     different pairs of cities. 
    You want a set of lines that connects all your offices with a minimum total cost. 
    Solve the problem by suggesting appropriate data structures.

*/

#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

class MST {
    vector<pair<int, int>> AdjList[100];
    string Office[100];
    int n;

    public :
        MST(int size) {
            n = size;
        }

        void setOffice(int index, string name) {
            Office[index] = name;
        }

        void AddEdge(int u, int v, int cost) {
            AdjList[u].push_back({v, cost});
            AdjList[v].push_back({u, cost});
        }
       
        void PrimsAlgo( ) {
            vector<int> MinKeyWt(n , INT_MAX);
            vector<bool> mst(n , false);
            vector<int> parent(n , -1);

            MinKeyWt[0] = 0;
            parent[0] = -1;

            for(int count = 1; count < n; count++) {
                int min = INT_MAX;
                int u;
                //find the min weight node
                for(int v = 0; v < n; v++) {
                    if(mst[v] == false && MinKeyWt[v] < min) {
                        u = v;
                        min = MinKeyWt[v];
                    }
                }
                //mark min node as true
                mst[u] = true;

                //check its adjacent nodes
                for(auto it : AdjList[u]) {
                    int v = it.first;
                    int w = it.second;
                    if(mst[v] == false && w < MinKeyWt[v]) {
                        parent[v] = u;
                        MinKeyWt[v] = w;
                    }
                }
            }

            //Total MST cost
            int totalCost = 0;
            cout<<"\nConnections in MST ---> "<<endl;
            for(int i = 1; i < n; i++) {
                cout<< Office[parent[i]] << " <-> "<<Office[i]<< " (cost : "<<MinKeyWt[i] << ")"<<endl;
                totalCost += MinKeyWt[i];
            }
            cout<<"\nTotal Minimum Cost = "<<totalCost<<endl;

        }

};

int main() {
    int n = 5;
    MST graph(n);

    graph.setOffice(0, "OfficeA");
    graph.setOffice(1, "OfficeB");
    graph.setOffice(2, "OfficeC");
    graph.setOffice(3, "OfficeD");
    graph.setOffice(4, "OfficeE");

    //Graph : 0 <-> 1 weight = 10
    graph.AddEdge(0, 1, 10);
    graph.AddEdge(0, 2, 20);
    graph.AddEdge(1, 2, 5);
    graph.AddEdge(1, 3, 15);
    graph.AddEdge(2, 3, 30);
    graph.AddEdge(3, 4, 7);

    graph.PrimsAlgo();

    return 0;
}