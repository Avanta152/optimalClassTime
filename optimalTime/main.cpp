#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct ListNode {
    string name;
    ListNode* next;
};
void insertName(ListNode*& head, string& student) {
    ListNode* listNode = new ListNode;
    listNode->name = student;
    listNode->next = head;
    head = listNode;
}

void printList(ListNode* head) {
    ListNode* ptr = head;
    while (ptr) {
        cout << ptr->name << " ";
        ptr = ptr->next;
    }
}
struct TimeNode {
    double time;
    int count;
    ListNode*nameList;
    TimeNode* next;
};
TimeNode* insertTime(TimeNode*& head, double t, string& name) {
    if (!head) {
        TimeNode* node = new TimeNode;
        node->time = t;
        node->count = 1;
        node->nameList = nullptr;
        insertName(node->nameList, name);
        node->next= head;
        return node;
    }

    if (t< head->time) {
        TimeNode* node = new TimeNode;
        node->time = t;
        node->count = 1;
        node->nameList = nullptr;
        insertName(node->nameList, name);
        node->next= head;
        return node;
    }
    TimeNode* ptr = head;
    TimeNode* temp = nullptr;
    while (ptr && ptr->time<t) {
        temp = ptr;
        ptr=ptr->next;
    }
    //if name exists in the list
    if (ptr && ptr->time==t) {
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
    TimeNode* node = new TimeNode;
        node->time = t;
        node->count = 1;
        node->nameList = nullptr;
        insertName(node->nameList, name);
        node->next= ptr;
        if (temp) {
            temp->next = node;
        }
        return head;

}

int main(int argc , char *argv[]) {

    ListNode*nameList = NULL;
    TimeNode* head = NULL;

    for (int i = 1; i< argc; i++) {
        ifstream file(argv[i]); 

        if (!file) {
            cout<< "Could not open filr!" << argv[i] << endl;
            continue;
        }
        cout << "Opened file: " << argv[i] << endl;
        
        string name = argv[i];
        insertName(nameList, name);
        double time;
        string line;
        while (getline(file, line)) {
        double time = stod(line.substr(line.find(':') +1));
            head = insertTime(head, time, name);
        }
        file.close();
        }
        TimeNode*ptr = head;
        while (ptr ) {
            cout << "time: " << ptr->time << " count: " << ptr->count << " names: " ;
            printList(ptr->nameList);
            cout<< endl;
            ptr = ptr-> next;
        }
  

    return 0;
}