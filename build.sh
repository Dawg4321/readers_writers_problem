#!/bin/bash

echo "Preparing to Compile Readers-Writers-Problem..."

if [ ! -d "./build/readers_pref" ];then # ensuring readers preference build director exists
    mkdir -p build/readers_pref # making readers preference build directory
fi

if [ ! -d "./build/writers_pref" ];then # ensuring writers preference build director exists
    mkdir -p build/writers_pref # making writers preference build directory 
fi

rm ./build/readers_pref/* # removing any existing files in build directory
rm ./build/writers_pref/* # this ensures only the newly created files are in the build directory

cd src # changing directory into source folder

echo "Compiling readwrite.cpp..."
g++ -c ./readwrite/readwrite.cpp -o temp # compiling readwrite.cpp
                                         # this will be linked to future compilations

echo "Compiling and Linking Readers Preference..."
g++ readers_pref/writer_readpref.cpp temp -o ../build/readers_pref/writer-r_pref # compiling readers preference code
g++ readers_pref/reader_readpref.cpp temp -o ../build/readers_pref/reader-r_pref
g++ readers_pref/initialization_readpref.cpp -o ../build/readers_pref/initialization-r_pref

echo "Compiling and Linking Writers Preference..."
g++ writers_pref/writer_writerpref.cpp temp -o ../build/writers_pref/writer-w_pref # compiling writers preference
g++ writers_pref/reader_writerpref.cpp temp -o ../build/writers_pref/reader-w_pref
g++ writers_pref/initialization_writerpref.cpp -o ../build/writers_pref/initialization-w_pref

echo "Removing Excess Build files..." 
rm temp # removing readwrite.cpp compilation files

cd .. # changing to parent directory

echo "Creating Text Files..."
touch ./build/readers_pref/file.txt # creating text files for use by executables
touch ./build/writers_pref/file.txt 

echo "Code Successfully Compiled and Ready to Run!"
echo "Please run the executables created in /build to test code."