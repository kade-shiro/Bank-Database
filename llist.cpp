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
//  FILE:        llist.cpp
//
//  DESCRIPTION:
//    This function contains the list class definitions.
//
****************************************************************/

#include <fstream>
#include "record2.h"
#include "llist.h"

#ifndef DEBUGMODE
#define DEBUGMODE
#endif

using namespace std;

/*****************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION:   This fuction will read the data from a text file and store
//                 it in a linked list.
//
//  Parameters:    none
//
//  Return values:  0 : success
//                 -1 : the value was not found
//
****************************************************************/

int llist::readfile()
{
    ifstream infile;
    int retval, accountno;
    char read[80], name[25], address[80];

    retval = 0;

    infile.open(filename);

    if(infile.is_open() == false)
    {
        retval = -1;
    }    

    else
    {
        while((infile.eof()) == false && infile.getline(read, 80))
        {
            accountno = atoi(read);
            
            infile.getline(name,25);
            infile.getline(address, 80);
            infile.ignore(1000, '\n');
            strcat(address, "\t");

            addRecord(accountno, name, address);
        }

        retval = 0;
        infile.close();
    }

    return retval;
}

/*****************************************************************
//
//  Function name: writefile
//
//  DESCRIPTION:   This fuction will write the data stored in the linked
//                 list to a file.
//
//  Parameters:    none
//
//  Return values: none
//  
****************************************************************/

void llist::writefile()
{
    struct record * marker;
    ofstream outfile;
    marker = start;

    outfile.open(filename);

    while(marker != NULL)
    {
        outfile << marker->accountno << endl;
        outfile << marker->name << endl;
        outfile << marker->address << endl << endl;

        marker = marker->next;
    }

    outfile.close();
}

/*****************************************************************
//
//  Function name: reverse
//
//  DESCRIPTION:   This function reverses a linked list.
//
//  Parameters:    head (record *) : The list to be reversed.
//
//  Return values: retval (record *) : The head of the new list.
//       
****************************************************************/

record * llist::reverse(record * head)
{
    record * retval;

    if(head->next == NULL)
    {
        start = retval = head;
    }

    else
    {
        retval = reverse(head->next);
        head->next->next = head;
        head->next = NULL;
    }

    return retval;
}

/*****************************************************************
//                  
//  Function name: cleanup
//                
//  DESCRIPTION:   This function will release all the allocated
//                 spaces in the heap memory.                
//                                
//  Parameters:    none
//                     
//  Return values: none
//
****************************************************************/

void llist::cleanup()
{
    struct record * marker;
    marker = start;

    while(start != NULL)
    {
        start = start->next;
        delete(marker);
        marker = start;
    }
}

/*****************************************************************
//                  
//  Function name: llist          
//                  
//  DESCRIPTION:   This is the constructor for the list class.
//  
//  Parameters:    none
//
****************************************************************/

llist::llist()
{
    start = NULL;
    strcpy(filename,"database.txt");
    readfile();
}

/*****************************************************************
//                  
//  Function name: list
//                  
//  DESCRIPTION:   This is the constructor for the list class.  
//  Parameters:    datafile (char[]) : The file being read from.
//
****************************************************************/

llist::llist(char datafile[])
{
    start = NULL;
    strcpy(filename, datafile);
    readfile();
}

/*****************************************************************
//                  
//  Function name: list
//                  
//  DESCRIPTION:   This is the copy constructor for the list class.
//  
//  Parameters:    og (llist&) : The original list.
//
****************************************************************/

llist::llist(const llist& og)
{
    start = og.start;
    strcpy(filename, og.filename);
    readfile();
}

/*****************************************************************
//                  
//  Function name: ~llist
//                  
//  DESCRIPTION:   This is the deconstructor for the list class.
//
//  Parameters:    none
//
****************************************************************/

llist::~llist()
{
    writefile();
    cleanup();
}

/*****************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   This fuction will add data to the heap pointed to
//                 by start.
//
//  Parameters:    acctno (int) : The account number to be added.
//                 name (char[]) : The name to be added.
//                 addr (char[]) : The address to be added.
//
//  Return values:  0 : success
//                 -1 : the value was not found
//
****************************************************************/

int llist::addRecord (int acctno, char name[],char addr[])
{
    struct record *temp, *end;
    int dupe = 0;

    temp = new record();
    temp->accountno = acctno;
    strcpy(temp->name, name);
    strcpy(temp->address, addr);

    if(start == NULL)
    {
        temp->next = NULL;
        start = temp;
    }

    else
    {
        end = start;
        while(end->next != NULL && dupe == 0)
        {
            if(end->accountno != temp->accountno)
            {
                end = end->next;
            }
         
            else
            {
                dupe = -1;
            }
        }

        if(end->accountno != temp->accountno)
        {
            temp->next = NULL;
            end->next = temp;
            end = end->next;
        }
 
        else
        {
            dupe = -1;
            cout << acctno << ": Account number already exists." << endl;
        }
    }
     
    return dupe;   
}

/*****************************************************************
//
//  Function name: printRecord
//
//  DESCRIPTION:   This fuction will print the data specified by acctno.
//
//  Parameters:    acctno (int) : The account number of the record that
//                                will be displayed.
//
//  Return values:  0 : success
//                 -1 : the value was not found
//
****************************************************************/
int llist::printRecord (int acctno)
{
    struct record *marker, *previous;
    int retValue;

    marker = start;
    retValue = 0;

    while(marker != NULL && marker->accountno != acctno)
    {
        previous = marker;
        marker = previous->next;
    }       

    if(marker == NULL)
    {    
        cout << "error: The database is empty." << endl;
        retValue = -1;
    }

    else
    {
        cout << "\n Account number: " << marker->accountno << endl;
        cout << "Name: " << marker->name << endl;
        cout << "Address:\n" << marker->address << endl;
    }        

        marker = NULL;
        return retValue;
}

/***************************************************************** 
//
//  Function name: operator <<
//   
//  DESCRIPTION:   This fuction will print all of the record in
//                  the list.
//
//  Parameters:    os (ostream&) : The output stream.
//                 list (llist&) : The list of records.
//
//  Return values:  os : All of the records in the database.
//
****************************************************************/

ostream& operator << (ostream & os, const llist & list)
{
    int count;
    record * marker = list.start;

    count = 1;

    if(marker == NULL)
    {
        cout << "error: The databse is empty" << endl;
    }

    else
    {
        while(marker != NULL)
        {
            cout << "\n Record " << count << endl;
            cout << "Account number: " << marker->accountno << endl;
            cout << "Name: " << marker->name << endl;
            cout << "Address:\n" << marker->address << endl;

            count++;
            marker = marker->next;
        }
    }

    return os;
}

/*****************************************************************
//
//  Function name: findRecords
//
//  DESCRIPTION:   This fuction will display all of the records whose names
//                 begin with the specified letters.
//
//  Parameters:    name (char[]) : The letters to search for.
//
//  Return values:  0 : success
//                 -1 : the value was not found
//
****************************************************************/
int llist::findRecords(char name[ ])
{
    struct record * marker;          
    int count, retVal, len;   

    marker = start;
    count = 1;
    retVal = 0;
    len = strlen(name);

    if(marker == NULL)
    {
        cout << "error: The database is empty." << endl;
        retVal = -1;
    }

    else
    {
        while(marker != NULL)
        {
            if(strncmp(marker->name, name, len) == 0)
            {
                cout << "\n Record " << count << endl;    
                cout << "Account number: " << marker->accountno << endl;
                cout << "Name: " << marker->name << endl;
                cout << "Address:\n" << marker->address << endl;
            }

            count++;
            marker = marker->next;
        }
    }

    return retVal;
}

/*****************************************************************
//
//  Function name: deleteRecord
//
//  DESCRIPTION:   This fuction will delete the record specified by the acctno.
//
//  Parameters:    acctno (int) : The account number that will be deleted from
//                                the database.
//
//  Return values:  0 : success
//                 -1 : the value was not found
//
****************************************************************/
int llist::deleteRecord(int acctno)
{
    struct record *marker, *previous;
    int retValue;   
    marker = start;
    retValue = 0;
    while(marker != NULL && marker->accountno != acctno)
    {
        previous = marker;
        marker = previous->next;
    }
    
    if(marker == NULL)
    {
        retValue = -1;
    }
    else
    {
        if(marker == start)
        {
            start = marker->next;
            delete(marker);
        }
 
        else
        {
            previous->next = marker->next;
            delete(marker);
        }
    }
        marker = NULL;
        return retValue;        
}

/*****************************************************************
//
//  Function name: reverse
//       
//  DESCRIPTION:   This function reverses the list.
//
//  Parameters:     none
//
//  Return values:  none
//
****************************************************************/

void llist::reverse()
{
    start = reverse(start);
}
