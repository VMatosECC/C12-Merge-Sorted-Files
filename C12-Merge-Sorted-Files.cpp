// C12-Merge-Sorted-Files.cpp 
/*
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

    fstream file1 = openFile(fileName1, ios::in | ios::binary);
    fstream file2 = openFile(fileName2, ios::in | ios::binary);
    fstream file3 = openFile(fileName3, ios::out);

    int num1, num2;
    //read next value from file1 and file2
    bool hasNum1 = (bool)(file1 >> num1);
    bool hasNum2 = (bool)(file2 >> num2);

    while (hasNum1 && hasNum2)
    {
        if (num1 < num2) {
            file3 << num1 << endl;
            hasNum1 = (bool)(file1 >> num1);
        }
        else {
            file3 << num2 << endl;
            hasNum2 = (bool)(file2 >> num2);
        }
    }

    while (hasNum1)
    {
        file3 << num1 << endl;
        hasNum1 = (bool)(file1 >> num1);
    }

    while (hasNum2)
    {
        file3 << num2 << endl;
        hasNum2 = (bool)(file2 >> num2);
    }



    file1.close();
    file2.close();
    file3.close();

    //show the merged file
    file3 = openFile(fileName3);
    int num;
    while (file3 >> num)
    {
        cout << num << endl;
    }
    cout << "\nAll done!\n";
}

fstream openFile(string fileName, ios::openmode mode)
{
    fstream file (fileName, mode);
    if (!file)
    {
        cout << "Error opening file " << fileName << endl;
        exit(1);
    }
    return file;
}

