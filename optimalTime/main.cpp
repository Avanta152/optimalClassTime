#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//node to store the names
struct ListNode {
    string name;
    ListNode* next;
};
//function to insert manes into a names list
void insertName(ListNode*& head, string& student) {
    ListNode* listNode = new ListNode;
    listNode->name = student;
    listNode->next = head;
    head = listNode;
}
//function to print the list
void printList(ListNode* head) {
    ListNode* ptr = head;
    while (ptr) {
        cout << ptr->name << " ";
        ptr = ptr->next;
    }
}
//list to store days. times, number of students, that points to the name list
struct TimeNode {
    string day;
    double time;
    int count;
    ListNode*nameList;
    TimeNode* next;
};
//function that inserts the days, times ans names, counts how many students pick the same time
TimeNode* insertTime(TimeNode*& head, string day, double t, string& name) {
    
    TimeNode* ptr = head;
    TimeNode* temp = nullptr;
    while (ptr && (ptr->day<day || (ptr->day == day && ptr->time<t))) 
    {
        temp = ptr;
        ptr=ptr->next;
    }
    //if name exists in the list
    if (ptr && ptr->day == day && ptr->time==t) {
        ListNode* check = ptr->nameList;
        bool found = false;
        while (check) {
            if (check->name == name) {
                found = true;
                break;
            }
            check=check->next;
        }
        if (!found) {
        insertName(ptr->nameList, name);
        ptr->count++;
        }
        return head;
    }
    //if name does not exist , creates a new node
    TimeNode* node = new TimeNode;
    node->day = day;
        node->time = t;
        node->count = 1;
        node->nameList = nullptr;
        insertName(node->nameList, name);
        node->next= ptr;
        if (temp==NULL) {
            head = node;
        } else {temp->next = node;}
        return head;
}

void deleteNameList(ListNode*& head) {
    while (head) {
        ListNode*temp = head;
        head = head->next;
        delete temp;
    }
}
void deleteTimeNode(TimeNode*& head) {
    while (head) {
        TimeNode* temp = head;
        deleteNameList(head->nameList);
        head=head->next;
        delete temp;
    }
}
int main(int argc , char *argv[]) {

    ListNode*nameList = NULL;
    TimeNode* head = NULL;

    for (int i = 1; i< argc; i++) {
        ifstream file(argv[i]); 

        if (!file) {
            cout<< "Could not open file!" << argv[i] << endl;
            continue;
        }
        string name = argv[i];
        insertName(nameList, name);
        string line;
        while (getline(file, line)) {
            string day = line.substr(0, line.find(':'));
        double time = stod(line.substr(line.find(':') +1));
            head = insertTime(head,day, time, name);
        }
        file.close();
        }
        int minimum;
        while (true) {
            cout << "Enter the minimum number of stidents that must have chosen the same start time or 0 to exit-->";
            cin >> minimum;
            if (minimum == 0) {
                cout <<"You exit."<< endl;
                break;
            }
        TimeNode*ptr = head;
        while (ptr ) {
            if (ptr->count >= minimum) {
            cout << "day: " << ptr->day<< " time: " << ptr->time << " names: " ;
            printList(ptr->nameList);
            cout<< endl;
            }
            ptr = ptr-> next;
        }
    }
    deleteTimeNode(head);
    deleteNameList(nameList);
    return 0;
}