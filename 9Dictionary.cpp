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
        Node *left;
        Node *right;
        int height;
        Node( string key, string value) {
            keyword = key;
            meaning = value;
            left = right = NULL;
            height = 1;
        }
};

int height(Node *node) {
    if(node != NULL) return node->height;
    else return 0;
}

int getBalance(Node *node) {
    if(node != NULL) return height(node->left) - height(node->right);
    else return 0;
}

Node *rotateRight(Node *y) {
    Node *x = y -> left;
    Node *T2 = x -> right;

    x -> right = y;
    y -> left = T2;

    //update height
    y->height = 1 + max(height(y->left) , height(y->right));
    x->height = 1 + max(height(x->left) , height(x->right));

    return x;
}

Node *rotateLeft(Node *x) {
    Node *y = x -> right;
    Node *T2 = y -> left;

    y -> left = x;
    x -> right = T2;

    //update height
    y->height = 1 + max(height(y->left) , height(y->right));
    x->height = 1 + max(height(x->left) , height(x->right));
    return y;
}

Node *insert(Node *root, string key, string value) {
    if(root == NULL) return new Node(key,value);

    if(key < root->keyword) root->left = insert(root->left,key,value);
    else if(key > root->keyword) root->right = insert(root->right,key,value);
    else {
        cout<<"\nKeyword already exits. "<<endl;
        return root;
    }

    //Assign Height
    root->height = 1 + max(height(root->left) , height(root->right));

    //Check the balance of tree
    int balance = getBalance(root);
    //Right Right case
    if(balance > 1 && key < root->left->keyword) return rotateRight(root);
    //Right Right case
    if(balance < -1 && key > root->left->keyword) return rotateLeft(root);
    //Left Right case
    if(balance > 1 && key > root->left->keyword) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    //Right Left case
    if(balance < -1 && key < root->left->keyword) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;

}

Node *minValueNode(Node *node) {
    Node *current = node;
    while(current && current->left) current = current->left;
    return current;
}

Node *deleteNode(Node* root, string key) {
    if(root == NULL) return root;

    if(key < root->keyword) root->left = deleteNode(root->left , key);
    else if(key > root->keyword) root->right = deleteNode(root->right , key);
    else {

        //Node with 0 or 1 child
        if(root->left == NULL || root->right == NULL) {
            Node *temp;
            if(root->left != NULL) temp = root->left;
            else temp = root->right;

            if(temp == NULL) {
                temp = root;
                root=NULL;
            }
            else root = temp;
            delete temp;
        }
        //Node with 2 children
        else {
            Node *temp = minValueNode(root->right);
            root->keyword = temp->keyword;
            root->meaning = temp->meaning;
            root->right = deleteNode(root->right, temp->keyword);
        }
    }

    if(root == NULL) return root;

    //STEP 2 :
    root->height = 1 + max(height(root->left) , height(root->right));

    //STEP 3 :
    int balance = getBalance(root);

    //LEFT LEFT CASE
    if(balance > 1 && getBalance(root->left) >= 0) return rotateRight(root);
    //LEFT RIGHT CASE
    if(balance < 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    //RIGHT LEFT CASE
    if(balance < -1 && getBalance(root->right) <= 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

Node* update(Node *root, string key, string newMeaning) {
    if(root == NULL) {
        cout<<"\nKeyword not found."<<endl;
        return NULL;
    }
    if( key < root->keyword) root->left = update(root->left , key , newMeaning);
    else if(key > root->keyword) root->right = update(root->right , key , newMeaning);
    else root->meaning = newMeaning;
    return root;
}

void displayAscending(Node *root) {
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

int findComparisons(Node* root, string key, int count = 0) {
    if(root != NULL) return count;
    count++;
    if(key == root->keyword) return findComparisons(root->left, key, count);
    else return findComparisons(root->right, key, count);
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
        cout << "0. Exit"<<endl;
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
            cout << "\nComparisons made: " << findComparisons(root, key) << endl;
        }
        else if(choice == 7) {
            cout << "Exiting...\n";
            break;
        }
        else cout<<"\nInvalid choice!"<<endl;
    }

    return 0;
}
