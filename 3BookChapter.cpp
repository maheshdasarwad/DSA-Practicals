/*
A book consists of chapters, chapters consist of sections and sections consist of 
subsections. Construct a tree and print the nodes. Find the time and space requirements 
of your method.
*/

//Time and Space requirement is ==> O(n)

#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string name;
    Node *next, *down;

    Node(string name) {
        this->name = name;
        next = down = NULL;
    }
};

class GLL {
    Node *headBook = new Node("dummy");

public:
    void CreateBook(Node *book) {
        Node *temp = headBook;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = book;

        Node *headChapter = new Node("dummy");
        book->down = headChapter;

        int chap;
        cout << "Enter number of Chapters: ";
        cin >> chap;
        cin.ignore();  // Clean buffer before getline
        for (int i = 0; i < chap; i++) {
            string name;
            cout << "Enter Chapter name: ";
            getline(cin, name);
            Node *chapter = new Node(name);
            CreateChapter(headChapter, chapter);
        }
    }

    void CreateChapter(Node *headChapter, Node *chapter) {
        Node *temp = headChapter;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = chapter;

        Node *headSection = new Node("dummy");
        chapter->down = headSection;

        int sec;
        cout << "Enter number of Sections: ";
        cin >> sec;
        cin.ignore();
        for (int i = 0; i < sec; i++) {
            string name;
            cout << "Enter Section name: ";
            getline(cin, name);
            Node *section = new Node(name);
            CreateSection(headSection, section);
        }
    }

    void CreateSection(Node *headSection, Node *section) {
        Node *temp = headSection;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = section;

        Node *headSubsection = new Node("dummy");
        section->down = headSubsection;

        int sub;
        cout << "Enter number of Subsections: ";
        cin >> sub;
        cin.ignore();
        for (int i = 0; i < sub; i++) {
            string name;
            cout << "Enter Subsection name: ";
            getline(cin, name);
            Node *subsection = new Node(name);
            CreateSubsection(headSubsection, subsection);
        }
    }

    void CreateSubsection(Node *headSubsection, Node *subsection) {
        Node *temp = headSubsection;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = subsection;
    }

    void display() {
        if (headBook->next == NULL) {
            cout << "\nNo book data available!!\n";
            return;
        }

        Node *bookPtr = headBook->next;
        while (bookPtr != NULL) {
            cout << "\n" << bookPtr->name << endl;

            Node *chapterPtr = bookPtr->down ? bookPtr->down->next : NULL;
            while (chapterPtr != NULL) {
                cout << " * " << chapterPtr->name << endl;

                Node *sectionPtr = chapterPtr->down ? chapterPtr->down->next : NULL;
                while (sectionPtr != NULL) {
                    cout << "   -> " << sectionPtr->name << endl;

                    Node *subPtr = sectionPtr->down ? sectionPtr->down->next : NULL;
                    while (subPtr != NULL) {
                        cout << "     = " << subPtr->name << endl;
                        subPtr = subPtr->next;
                    }
                    sectionPtr = sectionPtr->next;
                }
                chapterPtr = chapterPtr->next;
            }
            bookPtr = bookPtr->next;
        }
        cout << endl;
    }
};

int main() {
    GLL Obj;
    while (true) {
        cout << "\n1. Enter Book Details \n2. Display Books \n3. Exit\n";
        int ch;
        cout << "Select option: ";
        cin >> ch;

        if (ch == 1) {
            string name;
            cin.ignore();
            cout << "\nEnter Book Name: ";
            getline(cin, name);
            Node *book = new Node(name);
            Obj.CreateBook(book);
        } else if (ch == 2) {
            Obj.display();
        } else if (ch == 3) {
            cout << "\nExited Successfully...\n";
            break;
        } else {
            cout << "\nInvalid Option!\n";
        }
    }
    return 0;
}
