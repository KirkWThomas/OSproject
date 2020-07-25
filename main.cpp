#include <iostream>
#include <list>
#include <string>
#include <fstream>

using namespace std;
enum State{noob, ready, running, waiting, dead};

class pcb{
    public:
        int *currentPosition;
        State s = noob;
        int uniqueID, arrivalTime, burstTime, priority;
        int registers[15] = {0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, 0xB, 0xC, 0xD, 0xE};

        pcb(int currentPos, State state, int ID, int weight, int theRegisters[15]){
            currentPosition = &currentPos;
            s = state;
            uniqueID = ID;
            priority = weight;
            for (auto i : registers){
                registers[i] = theRegisters[i];
            }
            
        }

        pcb(int ID, int arrival, int burst, int weight){
            uniqueID = ID;
            arrivalTime = arrival;
            burstTime = burst;
            priority = weight;
            s = noob;
            
        }

        friend ostream & operator << (ostream &out, const pcb &n);
        
};

ostream& operator<<(ostream& out, const pcb &n){
            out << "Process ID: " << n.uniqueID << endl;
            out << "Arrival Time: " << n.arrivalTime << endl;
            out << "Burst Time: " << n.burstTime << endl;
            out << "Priority: " << n.priority << endl;
            out << "Current Position: " << n.currentPosition << endl;
            out << "Current Registers: " << endl << "\t";
            for (auto i : n.registers){
                //out << i << endl;
                out << n.registers[i] << ", ";
            }
            out << endl;
        }

void printPCBList(list<pcb> const &theList){
    list<pcb>::const_iterator it;
    
    for (it = theList.begin(); it != theList.end(); ++it){
        cout << *it << endl;
    }
}


int main(int argc, char *argv[]){
    int input = 2;
    bool onePass = false;
    list<pcb> allProcesses;
    while(input != 0){
        cout << "\nPlease choose:" << endl << "0. End Program." << endl << "1. Enter process manually." << endl << "2. Enter process(es) with a file. (command line arguments will automatically be detected on first pass)" << endl << "3. Set system q" << endl << "4. Print all PCBs" << endl;
        if(argc != 2 && !onePass){
            cin >> input;
        }
        onePass = true;
        int currentPosition = 0x00000000;
        State s = noob;
        int uniqueID, arrivalTime, burstTime, priority, q;
        int registers[15];
        string temp;
        cin.ignore();

        if (input == 1){
            cout << "Enter process ID: ";
            getline(cin, temp);
            uniqueID = stoi(temp);

            cout << "Enter process arrival time: ";
            getline(cin, temp);
            arrivalTime = stoi(temp);

            cout << "Enter process burst time: ";
            getline(cin, temp);
            burstTime = stoi(temp);

            cout << "Enter priority: ";
            getline(cin, temp);
            priority = stoi(temp);

            allProcesses.push_back(pcb(uniqueID, arrivalTime, burstTime, priority));
        }

        else if (input == 2){
            string fileName;
            int line;
            if(argc != 2){
                cout << "Enter filename: ";
                cin >> fileName;
            }
            else{
                fileName = argv[2];
            }

            ifstream inFile(fileName);
            if (inFile.is_open()){
                getline(inFile, temp, '=');
                getline(inFile, temp);
                q = stoi(temp);
                cout << "q: " << q << endl;

                getline(inFile, temp);  //discard next line

                while (!inFile.eof()){
                    getline(inFile, temp, ',');
                    uniqueID = stoi(temp);

                    getline(inFile, temp, ',');
                    arrivalTime = stoi(temp);

                    getline(inFile, temp, ',');
                    burstTime = stoi(temp);

                    getline(inFile, temp);
                    priority = stoi(temp);

                    allProcesses.push_back(pcb(uniqueID, arrivalTime, burstTime, priority));
                    //inFile >> currentPosition;
                }
            }
            else {
                cout << "Invlaid Input File. Please try again.";
            }
        }

        else if (input == 3){
            cout << "Please set q: ";
            getline(cin, temp);
            q = stoi(temp);
        }

        else if (input == 4){
            printPCBList(allProcesses);
        }

        else if (input == 0){
            return 0;
        }
        else {cout << "Invalid Input. Try again.";}
    }
    //cout << "Hello World";

    return 0;
}