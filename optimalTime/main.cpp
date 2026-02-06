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



int main(int argc , char *argv[]) {

    ListNode*nameList = NULL;

    for (int i = 1; i< argc; i++) {
        ifstream file(argv[i]); 

        if (!file) {
            cout<< "Could not open filr!" << argv[i] << endl;
            continue;
        }
        cout << "Opened file: " << argv[i] << endl;
        string line;
        string name = argv[i];
        insertName(nameList, name);
        while (getline(file, line)) {
            
    cout << line<< endl;
        }
file.close();
        }
        printList(nameList);
        cout << endl;
    



    return 0;
}