#!/bin/bash

echo "Preparing to Compile Readers-Writers-Problem..."

if [ ! -d "./build/readers_pref" ];then # ensuring readers preference build director exists
    mkdir -p build/readers_pref # making readers preference build directory 
fi

if [ ! -d "./build/writers_pref" ];then # ensuring writers preference build director exists
    mkdir -p build/writers_pref # making writers preference build directory 
fi
echo "Compiling readwrite.cpp..."
g++ -c readwrite.cpp -o temp # compiling readwrite.cpp
                             # this will be linked to future compilations

echo "Compiling and Linking Readers Preference..."
g++ readers_pref/writer_readpref.cpp temp -o writer-r_pref # compiling readers preference
g++ readers_pref/reader_readpref.cpp temp -o reader-r_pref

mv writer-r_pref ./build/readers_pref # moving executables to readers preference build folder
mv reader-r_pref ./build/readers_pref

echo "Compiling and Linking Writers Preference..."
g++ writers_pref/writer_writerpref.cpp temp -o writer-w_pref # compiling writers preference
g++ writers_pref/reader_writerpref.cpp temp -o reader-w_pref

mv writer-w_pref ./build/writers_pref # moving executables to writers preference build folder
mv reader-w_pref ./build/writers_pref

echo "Creating Text Files..."
touch ./build/readers_pref/file.txt # creating text files for use by executables
touch ./build/writers_pref/file.txt

echo "Removing excess build files..." 
rm temp # removing readwrite.cpp compilation files

echo "Code Successfully Compiled and Ready to Run!"
echo "Please run the executables created in the Build Directory."