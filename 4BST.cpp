/*
Beginning with an empty binary search tree, Construct binary search tree by 
inserting the values in the order given. 
After constructing a binary tree -
i. Insert new node, 
ii. Find number of nodes in longest path from root, 
iii. Minimum data value found in the tree, 
iv. Change a tree so that the roles of the left and right pointers are swapped at 
    every node, 
v. Search a value
*/

// Height = Number of Edges
// Number of Nodes = Height + 1

#include <iostream>
#include <vector>
using namespace std;

class Node {
    public:
        int value;
        Node *left;
        Node *right;
        Node(int data) {
            value = data;
            left = right = NULL;
        }
};

class BST {
    public:
        Node* InsertBstNode(Node* root, int value) {
            if (root == NULL) return new Node(value);
            if (value < root->value) root->left = InsertBstNode(root->left, value);
            else root->right = InsertBstNode(root->right, value);
            return root;
        }

        int height(Node* root) {
            if (root == NULL) return 0;
            int leftH = height(root->left);
            int rightH = height(root->right);
            return max(leftH, rightH) + 1;
        }

        void MinValue(Node* root) {
            if (root == NULL) {
                cout<<"\nTree is empty" << endl;
                return;
            }
            Node* temp = root;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            cout<<"\nMinimum data value : " << temp->value << endl;
        }

        bool SearchInBST(Node* root, int value) {
            if (root == NULL) return false;
            if (root->value == value) return true;
            if (root->value > value) return SearchInBST(root->left, value);
            else return SearchInBST(root->right, value);
        }

        Node* MirrorTree(Node* root) {
            if (root == NULL) return NULL;
            root->left = MirrorTree(root->left);
            root->right = MirrorTree(root->right);
            swap(root->left, root->right);
            return root;
        }

        void inorder(Node* root) {
            if (root == NULL) return;
            inorder(root->left);
            cout << root->value << " ";
            inorder(root->right);
        }
};

int main() {
    BST obj;

    vector<int> v;
    int n;
    cout << "\nEnter the number of values: ";
    cin >> n;
    cout << "Enter values: ";
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        v.push_back(x);
    }

    Node* root = NULL;
    for (int i = 0; i < n; i++) {
        root = obj.InsertBstNode(root, v[i]);
    }
    cout << "\nInorder traversal of BST: ";
    obj.inorder(root);

    while (true) {
        int ch;
        cout<<"\n1. Insert new node."<<endl;
        cout<<"2. Number of nodes in Longest path"<<endl;
        cout<<"3. Mininum data value."<<endl;
        cout<<"4. Change Tree Swapped left and right."<<endl;
        cout<<"5. Search a value."<<endl;
        cout<<"6. To Exit."<<endl;
        cout<<"Select valid option : ";
        cin>>ch;

        if (ch == 1) {
            int val;
            cout << "\nEnter value to insert : ";
            cin >> val;
            root = obj.InsertBstNode(root, val);
            cout << "Updated inorder traversal : ";
            obj.inorder(root);
        }
        else if (ch == 2) {
            cout<<"\nNumber of nodes in longest path from root : " << obj.height(root) << endl;
        }
        else if (ch == 3) {
            obj.MinValue(root);
        }
        else if (ch == 4) {
            root = obj.MirrorTree(root);
            cout<<"\nTree after mirroring (inorder traversal) : ";
            obj.inorder(root);
        }
        else if (ch == 5) {
            int val;
            cout<<"\nEnter value : ";
            cin>>val;
            if(obj.SearchInBST(root,val)) cout<<"Value Found :)"<<endl;
            else cout<<"Nod Found !!"<<endl;
        }
        else if (ch == 6) {
            cout << "\nSuccessfully Exited .... :)" << endl;
            break;
        }
        else {
            cout << "\nInvalid Option Selected ....!!!!" << endl;
        }
    }

    return 0;
}
