#include "readwrite.h"

/* ~~~~~~~~~~~~~~~~~~~~readFile~~~~~~~~~~~~~~~~~~~~

    Function which reads and prints contents of text file.

    NOTE: Text file must be called file.txt
   
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void readFile(){
    
    cout << "\t*** Entering Read Function ***\n";

    ifstream file("file.txt",ios::in); // opening input file stream

    if(file.is_open()){ // successfully opened file.txt
    
        cout << "\t** File Contents: **\n";

        string buff; // buffer to store read data

        while(file >> buff){ // reading data from file.txt into buff
            cout << "\t" << buff << "\n"; // printing buffer contents
        }
        file.close(); // closing file stream
        cout << "\t**\n";
    }
    else{ // failed to open file.txt
        cout << "\t** ERROR: Failed to open file.txt **\n";
    }

    cout << "\tPress enter to leave the read function "; // asking using to press enter to exit read function
    cin.ignore();
    cout << "\t*** Leaving Read Function ***\n";
    
    return; // returning from function
}

/* ~~~~~~~~~~~~~~~~~~~~writeFile~~~~~~~~~~~~~~~~~~~~

    Function which appends a text file with iostream inputs.

    NOTE: Text file must be called file.txt
    
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void writeFile(){
    cout << "\t*** Entering Write Function ***\n";

    ofstream file("file.txt",std::ios::out | std::ios::app); // opening output file stream

    if(file.is_open()){ // successfully opened file.txt
        
        string buff; // buffer to store write data
        
        cout << "\t** Enter a value to write to file **\n\t";
        cin >> buff; // passing keyboard input into buffer
        file << "\n" << buff; // appending file with buffer contents

        file.close(); // closing file.txt
        cout << "\t**\n";
    }
    else{ // failed to open file.txt
        cout << "\t** ERROR: Failed to open file.txt **\n" ;
    }
    cout << "\tPress enter to leave the write function "; // asking using to press enter to exit read function
    cin.ignore();
    cout << "\t*** Leaving Write Function ***\n";

    return;  // returning from function
}