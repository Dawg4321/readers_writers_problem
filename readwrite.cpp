#include "readwrite.h"

void readFile(){
    
    cout << "\t***Entering Read Function***\n";

    ifstream file("file.txt",ios::in);

    if(file.is_open()){
        cout << "\t** File Contents: **\n";
        string buff;

        while(file >> buff){
            cout << "\t" << buff << "\n";
        }
        file.close();
        cout << "\t**\n";
    }
    else{
        cout << "\t** ERROR: Failed to open file.txt **";

    }

    cout << "\tPress enter to leave the read function ";
    cin.ignore();
    cout << "\t***Leaving Read Function***\n";
    
    return;
}

void writeFile(){
    cout << "\t***Entering Write Function***\n";
    ofstream file("file.txt",ios::out);

    if(file.is_open()){
        string buff;
        
        cout << "\t** Enter a value to write to file **\n\t";
        cin >> buff;
        file << buff;

        file.close();
        cout << "\t**\n";
    }
    else{
        cout << "\t** ERROR: Failed to open file.txt **" ;
    }
    cout << "\tPress enter to leave the write function ";
    cin.ignore();
    cout << "\t***Leaving Write Function***\n";
}