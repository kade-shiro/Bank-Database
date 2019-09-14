/*****************************************************************
//
//  NAME:        Kade Shiroma
//
//  HOMEWORK:    Project 2
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        April 7, 2019
//
//  FILE:        main.cpp
//
//  DESCRIPTION:
//   This file contains the user-interface function
//   for Project 2
//
//
****************************************************************/

#include "llist.h"

#ifndef DEBUGMODE
#define DEBUGMODE
#endif

/*****************************************************************
//
//  Function name:  main
//
//  DESCRIPTION:    A userinterface function that allows the user
//                  a menu of choices.
//
//  Parameters:     argc (int) : number of command line strings.
//                  argv (char * []) : the array of arguments.
//
//  Return values:  0 : success
//                 -1 : the value was not found
****************************************************************/

int main(int argc, char * argv[])
{
    int accountno, ask, count;
    char name[25], address[80], option[3], c[20], answer[10];

    ask = 1;
    count = 0;
    char dfile[] = "database.txt";

    #ifdef DEBUGMODE
        cout << "\n******* Debugmode *******" << endl;
    #endif

    llist records(dfile);

    while(ask == 1)
    {        cout << "\n******* Welcome to the Bank Database *******" << endl;
        cout << "Select one of these options below and then press enter:" << endl;
        cout << "(1) Add a new record in the database." << endl;
        cout << "(2) Print information about a record using the account number as the key." << endl;
        cout << "(3) Print all the information in the database." << endl;
        cout << "(4) Print the records whose names start with the given string as a key." << endl;
        cout << "(5) Delete an existing record from the database using the account number as a key." << endl;
        cout << "(6) Reverse the order of the records in the database." << endl;
        cout << "(7) Quit the program." << endl;

        cin >> option;
        cin.clear();
        cin.ignore(1000, '\n');

        if(option[0] == '1')
        {
            do
            {
                count = 0;

                do
                {
                    if(count > 0)
                    {
                        cout << c << ": invalid characters for account number." << endl;
                    }

                    cout << "Please enter the account number that you would like to add: ";
                    cin >> c;
                    cin.clear();
                    cin.ignore(1000, '\n');

                    accountno = atoi(c);
                    count++;
                }
                while(accountno == 0);

                cout << "Please enter your name: ";
                cin.getline(name, 25);

                cout << "Please enter your address. Plress 'tab' and enter to continue:" << endl;
                cin.get(address, 80, '\t');
                cin.clear();
                cin.ignore(1000,'\n');

                cout << "Is this information corret? (y\\n)" << endl;
                cout << " account number: " << accountno << endl;
                cout << " name: " << name << endl;
                cout << " address: " << address << endl;
                cin >> answer;
                cin.ignore();
            }
            while((strcmp(answer, "y")) != 0);

            records.addRecord(accountno, name, address);

            #ifdef DEBUGMODE
                cout << "debug: The name of the function called is addRecord." << endl;
                cout << "Parameters passed: " << endl;
                cout << " " << accountno << endl;
                cout << " " << name << endl;
                cout << " " << address << endl;
            #endif
        }

        else if(option[0] == '2')
        {
            cout << "Please enter the account number that you would like to print: ";
            cin >> accountno;
            cin.clear();
            cin.ignore(1000, '\n');

            records.printRecord(accountno);

            #ifdef DEBUGMODE
                cout << "debug: The name of the function called is printRecord." << endl;
                cout << "Parameters passed: " << endl;
                cout << " " << accountno << endl;
            #endif
        }

        else if(option[0] == '3')
        {
            cout << records;

            #ifdef DEBUGMODE
                cout << "debug: The name of the function called is operator <<" << endl;
            #endif
        }
 
        else if(option[0] == '4')
        {
            cout << "Please enter the beginning letters of a name to find its avaliable records: ";
            cin.getline(name, 25);
            cin.clear();
            cin.ignore(1000,'\n');

            records.findRecords(name);

            #ifdef DEBUGMODE
                cout << "debug: The name of the function called is findRecords" << endl;
                cout << "Parameters passed:" << endl;
                cout << name;
            #endif
        }

        else if(option[0] == '5')
        {
            cout << "Please enter the account number that you would like" << endl;
            cout << "to delete from the database: ";
            cin >> accountno;
            cin.clear();
            cin.ignore(1000, '\n');
             
            if(records.deleteRecord(accountno) == 0)
            {
                cout << "Record: " << accountno << " was deleted successfully." << endl;
            }

            else
            {
                cout << "error: Record was not found. Please try again." << endl;
            }

            #ifdef DEBUGMODE
                cout << "debug: The name of the function called is deleteRecord" << endl;
                cout << "Parameters passed:" << endl;
                cout << accountno;
            #endif
        }

        else if(option[0] == '6')
        {
            records.reverse();

            cout << "The order of the records have been reversed." << endl;
            
            #ifdef DEBUGMODE
                cout << "debug: The name of the function called is reverse" << endl;
            #endif
        }

        else if(option[0] == '7')
        {
            ask = 0;
        }

        else
        {
            cout << option << ": is an invalid option. Please try again." << endl;
        }
    }

    return 0;
}
