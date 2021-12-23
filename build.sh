#!/bin/bash

echo "Preparing to Compile Readers-Writers-Problem..."

dir="./build" # directory to build to

reader_dir="${dir}/readers_pref" # sub directories for readers and writers preference
writer_dir="${dir}/writers_pref"

starting_text="Hello\nRay!\n" # starting text to include in file.txt

echo "Removing Current Contents of ./build/..."

if [ ! -d $reader_dir  ];then # ensuring readers preference build director exists
    mkdir -p $reader_dir # making readers preference build directory
else
    rm -- $reader_dir/* # removing any pre-existing files in build directory
fi

if [ ! -d $writer_dir ];then # ensuring writers preference build director exists
    mkdir -p $writer_dir # making writers preference build directory 
else
    rm -- $writer_dir/* # this ensures only the newly created files are in the build directory
fi

cd src # changing directory into source folder

echo "Compiling readwrite.cpp..."
g++ -c ./readwrite/readwrite.cpp -o temp # compiling readwrite.cpp
                                         # this will be linked to future compilations

echo "Compiling and Linking Readers Preference..."
g++ readers_pref/writer_readpref.cpp temp -o ".$reader_dir/writer-r_pref" # compiling readers preference code
g++ readers_pref/reader_readpref.cpp temp -o ".$reader_dir/reader-r_pref"
g++ readers_pref/initialization_readpref.cpp -o ".$reader_dir/initialization-r_pref"

echo "Compiling and Linking Writers Preference..."
g++ writers_pref/writer_writerpref.cpp temp -o ".$writer_dir/writer-w_pref" # compiling writers preference
g++ writers_pref/reader_writerpref.cpp temp -o ".$writer_dir/reader-w_pref"
g++ writers_pref/initialization_writerpref.cpp -o ".$writer_dir/initialization-w_pref"

echo "Removing Excess Build files..." 
rm temp # removing readwrite.cpp compilation files

cd .. # changing to parent directory


echo "Creating Text Files..." # creating text files with starting_text for use by executables
printf $starting_text | tee "$reader_dir/file.txt" "$writer_dir/file.txt" > /dev/null

echo "Code Successfully Compiled and Ready to Run!"
echo "Please run the executables created in ./build/ to test code."