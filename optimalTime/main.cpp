#include <iostream>
#include <fstream>
#include <string>


using namespace std;
int main(int argc , char *argv[]) {

    for (int i = 1; i< argc; i++) {
        ifstream file(argv[i]); 

        if (!file) {
            cout<< "Could not open filr!" << argv[i] << endl;
            continue;
        }
        cout << "Opened file: " << argv[i] << endl;
        string line;
        while (getline(file, line)) {
cout << line<< endl;
        }
file.close();
        }
    



    return 0;
}