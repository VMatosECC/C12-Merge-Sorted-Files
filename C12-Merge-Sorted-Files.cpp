// C12-Merge-Sorted-Files.cpp 
/*
This app merges two sorted files into a larger, sorted file.
It compares the leading elements of the two files and writes the smaller
to the ouput file. It repeats this process with the rest of the records.

TECHNICAL NOTE
file.eof() does not become true immediately upon reaching the end of the file, 
but rather after a read operation tries to go past the end.
*/

#include <iostream>
#include <fstream>
using namespace std;
//Prototypes ------------------------------------------------------------
fstream openFile(string fileName, ios::openmode mode = ios::in); //default mode is input


int main()
{
    string fileName1 = "c:/temp/mergePart1.txt";   //input file
    string fileName2 = "c:/temp/mergePart2.txt";   //input file
    string fileName3 = "c:/temp/mergePart3.txt";   //output file

    fstream file1 = openFile(fileName1, ios::in );
    fstream file2 = openFile(fileName2, ios::in );
    fstream file3 = openFile(fileName3, ios::out);

    int num1, num2;
    //read next values from file1 and file2, sets availability flags
    bool num1Available = (bool)(file1 >> num1);
    bool num2Available = (bool)(file2 >> num2);

    while (num1Available && num2Available)
    {
        if (num1 < num2) {
            file3 << num1 << endl;
            num1Available = (bool)(file1 >> num1);
        }
        else {
            file3 << num2 << endl;
            num2Available = (bool)(file2 >> num2);
        }
    }

    while (num1Available)
    {
        file3 << num1 << endl;
        num1Available = (bool)(file1 >> num1);
    }

    while (num2Available)
    {
        file3 << num2 << endl;
        num2Available = (bool)(file2 >> num2);
    }

    //Done - close files
    file1.close();
    file2.close();
    file3.close();

    //DEBUG - show the merged file
    file3 = openFile(fileName3);
    int num;
    while (file3 >> num) {
        cout << num << endl;
    }
    cout << "\nAll done!\n";
}

//--------------------------------------------------------------------------
fstream openFile(string fileName, ios::openmode mode)
{
    //Utility function to open a file with a given mode
    fstream file (fileName, mode);
    if (!file)
    {
        cout << "Error opening file " << fileName << endl;
        exit(1);
    }
    return file;
}

