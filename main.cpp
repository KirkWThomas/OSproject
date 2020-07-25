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

        pcb(int ID, int arrival, int burst, int weight){
            // uniqueID = ID;
            // arrivalTime = arrival;
            // burstTime = burst;
            // priority = weight;
            // s = noob;
            // for (auto i : registers){
            //     registers[i] = 0x00000000;
            // }
            
        }

        friend ostream & operator << (ostream &out, const pcb &n);
        
};

ostream& operator<<(ostream& out, const pcb &n){
            out << "Process ID: " << n.uniqueID << endl;
            out << "Arrival Time: " << n.arrivalTime << endl;
            out << "Burst Time: " << n.burstTime << endl;
            out << "Priority: " << n.priority << endl;
            out << "Current Position: " << n.currentPosition << endl;
            out << "Current Registers: " << endl;
            for (auto i : n.registers){
                out << "\t" << n.registers[i] << endl;
            }
        }

void printPCBList(list<pcb> const &theList){
    for (auto n : theList){
        cout << n << endl;
    }
}


int main(int argc, char *argv[]){
    int input = 2;
    list<pcb> allProcesses;
    while(input != 0){
        cout << "\nPlease choose:" << endl << "0. End Program." << endl << "1. Enter process manually." << endl << "2. Enter process(es) with a file. (command line arguments will automatically be detected on first pass)" << endl << "4. Print all PCBs" << endl;
        if(argc != 2){
            cin >> input;
        }
        
        int currentPosition = 0x00000000;
        State s = noob;
        int uniqueID, arrivalTime, burstTime, priority;
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

            pcb(uniqueID, arrivalTime, burstTime, priority);
        }

        else if (input == 2){
            string fileName, temp;
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

                while (!inFile.eof()){
                    getline(inFile, temp, ',');
                    uniqueID = stoi(temp);

                    getline(inFile, temp, ',');
                    arrivalTime = stoi(temp);

                    getline(inFile, temp, ',');
                    burstTime = stoi(temp);

                    getline(inFile, temp, ',');
                    priority = stoi(temp);

                    pcb(uniqueID, arrivalTime, burstTime, priority);
                    //inFile >> currentPosition;
                }
            }
            else {
                cout << "Invlaid Input File. Please try again.";
            }
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