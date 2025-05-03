/*
    Consider a scenario for Hospital to cater services to different kinds of patients as 
    a) Serious(top priority), 
    b) non-serious (medium priority), 
    c) General Checkup (Least priority).
    Implement the priority queue to cater services to the patients.

    For indexing start from 1th place.
    Left child = 2*i
    Right child = 2*i + 1
    Parent = i/2
*/

#include <iostream>
#include <string>
using namespace std;

class heap {

    private:
        pair<int, string> arr[100];
        int size;
    
    public:
        heap() {
            arr[0] = {0, "NA"}; // Dummy element at index 0
            size = 0;
        }

        void insert(int priority, string name) {
            size = size + 1;
            int index = size;
            arr[index] = {priority, name};

            while(index > 1) {
                int parent = index/2;

                if(arr[parent].first > arr[index].first) {
                    swap(arr[parent], arr[index]);
                    index = parent;
                }
                else {
                    break; 
                }
            }
        }

        void servePatient() {
            if(size == 0) {
                cout << "\nNo patients to serve." << endl;
                return;
            }

            string priority;
            if(arr[1].first == 1) priority = "Serious";
            else if(arr[1].first == 2) priority = "Non-serious";
            else priority = "General Checkup";

            cout<<"\nNow treating : "<<arr[1].second<< " (Condition - " << priority << ")" << endl;
            
            // Replace root with last element and reduce size
            arr[1] = arr[size];
            size--;
            
            // Reheapify from the root
            if(size > 0) heapifyDown(1);
        }

        void heapifyDown(int i) {
            int smallest = i;
            
            // Continue until we reach a leaf or the element is in correct position
            while(smallest <= size) {
                int leftIndex = 2 * smallest;
                int rightIndex = 2 * smallest + 1;
                int candidate = smallest;

                // Check if left child exists and has higher priority
                if(leftIndex <= size && arr[leftIndex].first < arr[candidate].first) {
                    candidate = leftIndex;
                }
                
                // Check if right child exists and has higher priority than current candidate
                if(rightIndex <= size && arr[rightIndex].first < arr[candidate].first) {
                    candidate = rightIndex;
                }
                
                // If smallest is still the same, we're done
                if(candidate == smallest) {
                    break;
                }
                
                swap(arr[smallest], arr[candidate]);
                smallest = candidate;
            }
        }

        void display() {
            if(size == 0) {
                cout << "\nNo patients in queue!" << endl;
                return;
            }
            
            cout<<"\nCurrent Patient Queue --> "<< endl;
            for(int i = 1; i <= size; i++) {
                string priority;
                if(arr[i].first == 1) {
                    priority = "Serious";
                } 
                else if(arr[i].first == 2) {
                    priority = "Non-serious";
                } 
                else {
                    priority = "General Checkup";
                }
                cout << arr[i].second << " (Priority : " << priority << ")" << endl;
            }
        }

};

int main() {
    heap h;
    int choice;
    
    while(true) {
        cout << "\n1. Add Patient" << endl;
        cout << "2. Treat Next Patient" << endl;
        cout << "3. Display Queue" << endl;
        cout << "4. Exit" << endl;
        cout << "Select option : ";
        cin >> choice;

        if(choice == 1) {
            string name;
            int p;
            cin.ignore();
            cout << "\nEnter Patient Name: ";
            getline(cin, name);
            
            cout << "1. Serious."<< endl;
            cout << "2. Non-Serious."<< endl;
            cout << "3. General Checkup. "<< endl;
            cout << "Select condition : ";
            cin >> p;
            
            if(p >= 1 && p <= 3) {
                h.insert(p, name);
                cout << "\nPatient " << name << " added to the queue." << endl;
            } else cout << "\nInvalid priority level!" << endl;
        }
        else if(choice == 2) {
            h.servePatient();
        }
        else if(choice == 3) {
            h.display();
        }
        else if(choice == 4) {
            cout << "\nExited Successfully..." << endl;
            break;
        }
        else {
            cout << "\nInvalid Option !!!!" << endl;
        }
    }
    
    return 0;
}