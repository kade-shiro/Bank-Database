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
//  DATE:        April 2, 2019
//
//  FILE:        llist.h
//
//  DESCRIPTION:
//   This file contains the llist class.
//
//
****************************************************************/

#ifndef LLIST_H
#define LLIST_H

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "record2.h"

using namespace std;

class llist
{
  private:
    record *    start;
    char        filename[16];
    int         readfile();
    void        writefile();
    record *    reverse(record * );
    void        cleanup();

  public:
    llist();
    llist(char[]);
    llist(const llist&);
    ~llist();
    int addRecord (int, char [ ],char [ ]);
    int printRecord (int);
    friend ostream& operator << (ostream&, const llist&);
    int findRecords (char [ ]);
    int deleteRecord(int);
    void reverse();
};

#endif
