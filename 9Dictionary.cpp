/*

A Dictionary stores keywords and its meanings. 
Provide facility for 
    1). adding new keywords, 
    2). deleting keywords, 
    3). updating values of any entry. 
    4). Provide facility to display whole data sorted in ascending/ Descending order. 
    5). Also find how many maximum comparisons may require for finding any keyword. 
Use Height balance tree and find the complexity for finding a keyword

*/

#include <iostream>
#include <string>
using namespace std;

class Node {
    public :
        string keyword , meaning;
        Node *left , *right;
        int height;
        Node(string keyword , string meaning) {
            this->keyword = keyword;
            this->meaning = meaning;
            left = right = NULL;
            height = 1;
        }
};

int height(Node *node) {
    if(node == NULL) return 0;
    else return node->height;
}

int getBalance(Node *node) {
    if(node == NULL) return 0;
    else return height(node->left) - height(node->right);
}

Node *rightRotation(Node *root) {
    Node *child = root -> left;
    Node *childRight = child -> right;

    child -> right = root;
    root -> left = childRight;

    root -> height = 1 + max(height(root->left) , height(root->right));
    child -> height = 1 + max(height(child->left) , height(child->right));

    return child;
}

Node *leftRotation(Node *root) {
    Node *child = root -> right;
    Node *childLeft = child -> left;

    child -> left = root;
    root -> right = childLeft;

    child -> height = 1 + max(height(child->left) , height(child->right));
    root -> height = 1 + max(height(root->left) , height(root->right));

    return child;
}

Node *BalanceTree(Node *root) {
    int balanceFact = getBalance(root);

    //Left - Left
    if(balanceFact > 1 && getBalance(root->left) >= 0) {
        //Right rotation of top
        return rightRotation(root);
    }
    //Right - Right
    if(balanceFact < -1 && getBalance(root->right) <= 0) {
        //Left rotation of top
        return leftRotation(root);
    }
    //Left - Right
    else if(balanceFact > 1 && getBalance(root->left) < 0) {
        Node *middle = root->left; 
        //left rotation of middle
        //right rotation of top
        root->left = leftRotation(middle);
        return rightRotation(root);
    }
    //Right - Left
    else if(balanceFact < -1 && getBalance(root->right) > 0) {
        Node *middle = root->right;
        //Right rotation of middle
        //Left rotation of top
        root->right = rightRotation(middle);
        return leftRotation(root);
    }
    else return root;
}

Node *insert(Node *root, string keyword, string meaning) {
    if(root == NULL) return new Node(keyword , meaning);

    if(keyword < root->keyword) root->left = insert(root->left, keyword , meaning);
    else if(keyword > root->keyword) root->right = insert(root->right, keyword , meaning);
    else {
        cout<<"\nKeyword already exits."<<endl;
        return root;
    }

    root->height = 1 + max(height(root->left),height(root->right));

    return BalanceTree(root);

}

Node *minValueNode(Node *root) {
    Node *current = root;
    while(current != NULL && current->left != NULL)  
        current = current->left;
    return current;
}

Node *deleteNode(Node *root, string keyword) {
    //check if exits
    if(root == NULL) {
        cout<<"No data extis !!"<<endl;
        return NULL;
    }

    if(keyword < root->keyword) {
        root->left = deleteNode(root->left , keyword);
    }
    else if(keyword > root->keyword) {
        root->right = deleteNode(root->right , keyword);
    }
    else {
        //leaf Node 
        if(root->left == NULL && root->right == NULL) {
            delete root;
            return NULL;
        }
        //single child
        else if(root->left == NULL && root->right != NULL) {
            Node *temp = root->right;
            delete root;
            return temp;
        }
        else if(root->left != NULL && root->right == NULL) {
            Node *temp = root->left;
            delete root;
            return temp;
        }
        //both child
        else {
            Node *curr = root->right; //right side smallest element
            while(curr->left != NULL) curr = curr->left;
            root->keyword = curr->keyword;
            root->meaning = curr->meaning;
            root->right = deleteNode(root->right , curr->keyword);
        }
    }

    //update height
    root->height = 1 + max(height(root->left) , height(root->right));

    //Balance tree
    return BalanceTree(root);
}

Node *update(Node *root, string keyword, string meaning) {
    if(root==NULL) {
        cout<<"Keyword not found.."<<endl;
        return NULL;
    }
    if(keyword < root->keyword) root->left = update(root->left, keyword, meaning);
    else if(keyword > root->keyword) root->right = update(root->right, keyword, meaning);
    else root->meaning = meaning;
    return root;
}

void displayAscending(Node *root) {
    //inorder
    if(root != NULL) {
        displayAscending(root->left);
        cout<<root->keyword<<" : "<<root->meaning<<endl;
        displayAscending(root->right);
    }
}

void displayDescending(Node *root) {
    if(root != NULL) {
        displayDescending(root->right);
        cout<<root->keyword<<" : "<<root->meaning<<endl;
        displayDescending(root->left);
    }
}

int findComparisons(Node *root , string keyword , int count = 0) {
    if(root == NULL) return -1;
    count++;
    if(keyword < root->keyword) return findComparisons(root->left ,keyword, count);
    else if(keyword > root->keyword) return findComparisons(root->right, keyword, count);
    else return count;
}


int main() {
    Node *root = NULL;
    int choice;
    string key, meaning;
    
    while(true) {
        cout << "\n1. Add keyword"<<endl;
        cout << "2. Delete keyword"<<endl;
        cout << "3. Update meaning"<<endl;
        cout << "4. Display Ascending"<<endl;
        cout << "5. Display Descending"<<endl;
        cout << "6. Find comparisons for search"<<endl;
        cout << "7. Exit"<<endl;
        cout << "Enter choice: ";
        cin >> choice;

        if(choice == 1) {
            cout << "\nEnter keyword: ";
            cin >> key;
            cout << "Enter meaning: ";
            cin.ignore();
            getline(cin, meaning);
            root = insert(root, key, meaning);
        }
        else if(choice == 2) {
            cout << "\nEnter keyword to delete: ";
            cin >> key;
            root = deleteNode(root, key);
        }
        else if(choice == 3) {
            cout << "\nEnter keyword to update: ";
            cin >> key;
            cout << "Enter new meaning: ";
            cin.ignore();
            getline(cin, meaning);
            root = update(root, key, meaning);
        }
        else if(choice == 4) {
            cout << "\n--- Dictionary (Ascending Order) ---\n";
            displayAscending(root);
        }
        else if(choice == 5) {
            cout << "\n--- Dictionary (Descending Order) ---\n";
            displayDescending(root);
        }
        else if(choice == 6) {
            cout << "\nEnter keyword to search: ";
            cin >> key;
            cout << "Comparisons made: " << findComparisons(root, key) << endl;
        }
        else if(choice == 7) {
            cout << "Exiting...\n";
            break;
        }
        else cout<<"\nInvalid choice!"<<endl;
    }

    return 0;
}
