/*
given sequence k = k1 <k2 < … <kn of n sorted keys, with a search probability pi for each key ki . 
build the binary search tree that has the least search cost given the access probability for each key?

*/

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class Node {
    public :
        int key;
        Node *left;
        Node *right;
        Node(int val) {
            key = val;
            left = right = NULL;
        }
};

class OBST {
    pair<int,int> cost[10][10]; //here we store the cost as first and vertex_root as second .
    vector< pair<int,int> > data; //pair<key , frequency>
    int n;
    Node *root;
   
    public :
        OBST() {
            n = 0;
            root = NULL;
        }

        void input() {
            cout<<"\nEnter number of keys : ";
            cin>>n;
            data.clear();
            data.push_back({0,0}); //dummy;
            for(int i = 1; i <= n; i++) {
                int key , freq;
                cout<<"Enter key "<<i<<" : ";
                cin>>key;
                cout<<"Enter frequency for key "<<i<<" : ";
                cin>>freq;
                data.push_back({key , freq});
            }
        }

        pair<int,int> getMinCost(int x , int y) {
            int minCost = INT_MAX;
            int minRoot = -1;

            for(int r = x+1; r <= y; r++) {
                int c = cost[x][r-1].first + cost[r][y].first;
                if(c < minCost) {
                    minCost = c;
                    minRoot = r;
                }
            }

            int totalFreq = FreqSum(x , y);

            return { minCost + totalFreq, minRoot};
           
        }

        int FreqSum(int x , int y) {
            int ans = 0;
            for (int i = x + 1; i <= y; i++) {
                ans += data[i].second;
            }
            return ans;
        }

        void ObstMatrix() {
            //first own root cost set as zero
            for(int x = 0; x <= n; x++) {
                cost[x][x].first = cost[x][x].second = 0;
            }

            for(int i = 1; i <= n; i++) {
                int x = 0;
                for(int y = i; y <= n; y++) {
                    cost[x][y] = getMinCost(x , y);
                    x++;
                }
            }

            root = buildTree(0 , n);
            cout<<"\nOBST successfully built."<<endl;

        }

        Node *buildTree(int x, int y) {
            if(x == y) return NULL;
            int r = cost[x][y].second;
            Node *node = new Node(data[r].first);
            node -> left = buildTree(x , r-1);
            node -> right = buildTree(r , y);
            return node;
        }

        void inorder(Node *root) {
            if(root == NULL) return;
            inorder(root->left);
            cout<<root->key<<" ";
            inorder(root->right);
        }

        void displayInorder() {
            if(root == NULL) {
                cout<<"\nTree is empty."<<endl;
                return;
            }
            cout<<"\nInorder Traversal of OBST ----> "<<endl;
            inorder(root);
            cout<<endl;
        }

        void ObstCost() {
            if(n == 0) {
                cout<<"\nOBST not yet built."<<endl;
                return;
            }
            cout<<"\nCost of OBST Built :: "<<cost[0][n].first<<endl;
        }
};

int main() {
    OBST obj;
    obj.input();
    obj.ObstMatrix();
    int ch;

    while(true) {
        cout << "\n1. Display OBST Tree (Inorder Traversal)"<<endl;
        cout << "2. Display Minimum Search Cost"<<endl;
        cout << "3. Exit"<<endl;
        cout << "Enter your choice: ";
        cin >> ch;

        if(ch == 1) obj.displayInorder();
        else if(ch == 2) obj.ObstCost();
        else if(ch == 3) {
            cout<<"\nExiting ...."<<endl;
            break;
        }
        else {
            cout<<"\nInvalid choice. Try again.\n";
        }
    }
    return 0;
}