#include <Python.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;

int userInput;
string str;
string fileLine;

void CallProcedure(string pName)
{
char* procname = new char[pName.length() + 1];
std::strcpy(procname, pName.c_str());

Py_Initialize();
PyObject* my_module = PyImport_ImportModule("PythonCode");
PyErr_Print();
PyObject* my_function = PyObject_GetAttrString(my_module, procname);
PyObject* my_result = PyObject_CallObject(my_function, NULL);
Py_Finalize();

delete[] procname;
}

int callIntFunc(string proc, string param)
{
char* procname = new char[proc.length() + 1];
std::strcpy(procname, proc.c_str());

char* paramval = new char[param.length() + 1];
std::strcpy(paramval, param.c_str());

PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
// Initialize the Python Interpreter
Py_Initialize();
// Build the name object
pName = PyUnicode_FromString((char*)"PythonCode");
// Load the module object
pModule = PyImport_Import(pName);
// pDict is a borrowed reference
pDict = PyModule_GetDict(pModule);
// pFunc is also a borrowed reference
pFunc = PyDict_GetItemString(pDict, procname);
if (PyCallable_Check(pFunc))
{
pValue = Py_BuildValue("(z)", paramval);
PyErr_Print();
presult = PyObject_CallObject(pFunc, pValue);
PyErr_Print();
}
else
{
PyErr_Print();
}
//printf("Result is %d\n", _PyLong_AsInt(presult));
Py_DECREF(pValue);
// Clean up
Py_DECREF(pModule);
Py_DECREF(pName);
// Finish the Python Interpreter
Py_Finalize();

// clean
delete[] procname;
delete[] paramval;


return _PyLong_AsInt(presult);
}

int callIntFunc(string proc, int param)
{
char* procname = new char[proc.length() + 1];
std::strcpy(procname, proc.c_str());

PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
// Initialize the Python Interpreter
Py_Initialize();
// Build the name object
pName = PyUnicode_FromString((char*)"PythonCode");
// Load the module object
pModule = PyImport_Import(pName);
// pDict is a borrowed reference
pDict = PyModule_GetDict(pModule);
// pFunc is also a borrowed reference
pFunc = PyDict_GetItemString(pDict, procname);
if (PyCallable_Check(pFunc))
{
pValue = Py_BuildValue("(i)", param);
PyErr_Print();
presult = PyObject_CallObject(pFunc, pValue);
PyErr_Print();
}
else
{
PyErr_Print();
}
//printf("Result is %d\n", _PyLong_AsInt(presult));
Py_DECREF(pValue);
// Clean up
Py_DECREF(pModule);
Py_DECREF(pName);
// Finish the Python Interpreter
Py_Finalize();

// clean
delete[] procname;

return _PyLong_AsInt(presult);
}


void UserMenu()
{
// Simple user menu to show options
cout << "----------------- User Menu -----------------\n";
cout << "1: Produce a list of all items purchased with quantities \n";
cout << "2: Display how many times a specific item was sold \n";
cout << "3: Produce a histogram of sales data \n";
cout << "4: Exit \n\n";
cout << "Enter your selection as a number: 1, 2, 3, or 4. \n";
cout << "---------------------------------------------\n\n";
// Take user input as menu selection
cin >> userInput;

if (userInput == 1)
{
// Call the appropriate function to print items and quantity sold
cout << "\n\nPrinting items and quantities sold today: \n\n";
CallProcedure("ItemCounter");
cout << "\n\n";
return;
}
else if (userInput == 2)
{
// Prompt the user for a specific item and store it
cout << "\n\nPlease enter the item name: \n\n";
cin >> str;
cout << "\n\n";
cout << "Printing the sales for " << str << ":\n\n";
// Call the appropriate function with the item input
cout << str << ": " << callIntFunc("SpecificItemCounter", str) << "\n\n";
return;
}
else if (userInput == 3)
{
// First write the appropriate counts from the input file to the output file
cout << "\n\nWriting items and quantities sold today to a file: \n\n";
CallProcedure("ItemCounterWriter");
cout << "\n\n";
// Open the output file and read the data
ifstream frequencyFile("frequency.dat");
string item;
int count;
// Parse through the file line by line and print the histogram
while (getline(frequencyFile, fileLine))
{
istringstream iss(fileLine);
if (!(iss >> item >> count)) { break; } // error
// Print the item name and "count" number of asterisks
cout << item << " " << string(count, '*') << endl;
}
cout << "\n\n";
return;
}
else if (userInput == 4)
{
// IF user enters "4", exit the program
cout << "\n\nExiting program . . . \n\n";
exit(EXIT_SUCCESS);
}
else
{
// If user does not enter a valid menu option, they are sent back to the menu
cout << "\n\nPlease enter a valid input . . . \n\n";
return;
}
}

int main()
{
// Infinite loop to display menu. Can be exited by inputting the "exit value"
while (1)
{
UserMenu();
}

return 0;
}