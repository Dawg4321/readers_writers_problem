// readwrite.cpp
// written by Ryan Wiebe
// file used to read and write data in readers-writers problem solutions

#include "readwrite.h"

/* ~~~~~~~~~~~~~~~~~~~~readFile~~~~~~~~~~~~~~~~~~~~

    Function which reads and prints contents of text file.

    NOTE: Text file must be called file.txt
   
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void readFile(){
    
    cout << "\t*** Entering Read Function ***\n";

    ifstream file("file.txt",ios::in); // opening input file stream
                                       // this will be used to bring in data from file.txt

    if(file.is_open()){ // if file.txt was opened successfully
    
        cout << "\t** File Contents: **\n";

        string buff; // buffer to store data from file.txt

        while(file >> buff){ // reading data from file.txt into buff
                             // this while loop will keep reading until all strings of data have been read
            cout << "\t" << buff << "\n"; // printing buffer contents
        }
        file.close(); // closing file stream as reading is complete
        cout << "\t**\n";
    }
    else{ // if file.txt failed to open
        cout << "\t** ERROR: Failed to open file.txt **\n"; // error message
    }

    cout << "\tPress enter to leave the read function "; // asking user to press enter to exit read function
    cin.ignore();
    cout << "\t*** Leaving Read Function ***\n";
    
    return; // returning from function to main
}

/* ~~~~~~~~~~~~~~~~~~~~writeFile~~~~~~~~~~~~~~~~~~~~

    Function which appends a text file with iostream inputs.

    NOTE: Text file must be called file.txt
    
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void writeFile(){
    cout << "\t*** Entering Write Function ***\n";

    ofstream file("file.txt",std::ios::out | std::ios::app); // opening output file stream with append flag
                                                             // this will be used to append file.txt with user input

    if(file.is_open()){ // if file.txt successfully opened 
        
        string buff; // buffer to store data from user input
        
        cout << "\t** Enter a string of characters to write to file **\n\t"; // prompting user for input string
        cin >> buff; // passing keyboard input into buffer
        file << "\n" << buff; // appending file.txt with buffer contents

        file.close(); // closing file.txt as appending operation is done
        cout << "\t**\n";
    }
    else{ // if file.txt failed to open
        cout << "\t** ERROR: Failed to open file.txt **\n" ;
    }
    cout << "\tPress enter to leave the write function "; // asking using to press enter to exit read function
    cin.ignore();
    cin.ignore();
    cout << "\t*** Leaving Write Function ***\n";

    return;  // returning from function to main
}