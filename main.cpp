#include <iostream>
#include <list>
#include <string>
#include <fstream>

using namespace std;
enum State{ready, waiting, active, finished};

class pcb{
    public:
        int *currentPosition;
        State s = ready;
        int uniqueID;
        int priority;
        int registers[15];
        pcb(int currentPos, State state, int ID, int weight, int theRegisters[15]){
            currentPosition = &currentPos;
            s = state;
            uniqueID = ID;
            priority = weight;
            for (auto i : registers){
                registers[i] = theRegisters[i];
            }
            
        }
        
};


int main(){
    int input = 10;
    list<pcb> allProcesses;
    while(input != 0){
        cout << "Please choose:" << endl << "0. End Program." << endl << "1. Enter process manually." << endl << "2. Enter process with a file." << endl;
        cin >> input;

        int *currentPosition = 0x00000000;
            State s = ready;
            int uniqueID;
            int priority;
            int registers[15];

        if (input == 1){
            cout << "Enter process ID: ";
            cin >> uniqueID;
            cout << "Enter priority: ";
            cin >> priority;
            cout << "Enter process starting address: ";
            cin >> *currentPosition;
        }

        else if (input == 2){
            string fileName;
            int line;
            cout << "Enter filename: ";
            cin >> fileName;

            ifstream inFile(fileName);
            if (inFile.is_open()){

                while (inFile >> line){
                    uniqueID = line;
                    inFile >> priority;
                    inFile >> *currentPosition;
                }
            }
            else {
                cout << "Invlaid Input File. Please try again.";
            }
        }
        else if (input == 0){
            return 0;
        }
        else {cout << "Invalid Input. Try again.";}
    }
    cout << "Hello World";

    return 0;
}