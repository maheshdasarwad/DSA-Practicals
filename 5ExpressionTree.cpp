/*
Construct an expression tree from the given prefix expression eg. +--a*bc/def and
traverse it using post order traversal (non recursive) and then delete the entire tree.
*/

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

class Node {
    public :
        char data;
        Node *left;
        Node *right;

        Node (char val) {
            data = val;
            left = right = NULL;
        }
};

class ExpressionTree {
    public :
        bool isOperator(char ch) {
            if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') return true;
            return false;
        }
    
        Node *ConstructFromPrefix(string prefix) {
            stack<Node*> st;

            //Process from right to left
            for(int i = prefix.length()-1 ; i >= 0; i--) {
                char ch = prefix[i];
                Node *newNode = new Node(ch);
                if(isOperator(ch)) {
                    Node *left = st.top(); 
                    st.pop();
                    Node *right = st.top();
                    st.pop();

                    newNode -> left = left;
                    newNode -> right = right;
                }
                st.push(newNode);
            }
            return st.top(); //root 
        }

        void PostOrder(Node *root) {
            if(root == NULL) return;

            stack<Node*>st , ans;
            st.push(root);

            while(!st.empty()) {
                Node *curr = st.top();
                st.pop();
                ans.push(curr);

                if(curr->left) st.push(curr->left);
                if(curr->right) st.push(curr->right);
            }

            cout<<"\nPostorder Traversal (Non-recursice) --> "<<endl;
            while(!ans.empty()) {
                cout<<ans.top()->data<<" ";
                ans.pop();
            }
            cout<<endl;
        }

        void deleteTree(Node *root) {
            if(root == NULL) return;
            deleteTree(root->left);
            deleteTree(root->right);
            delete root;
        }
};

int main() {
    ExpressionTree obj;

    string prefix;
    cout<<"\nEnter prefix expression : ";
    cin>>prefix;

    Node *root = obj.ConstructFromPrefix(prefix);
    obj.PostOrder(root);
    obj.deleteTree(root);

    cout<<"\nExpression tree deleted successfully."<<endl;
    return 0;


}