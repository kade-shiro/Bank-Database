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
//  FILE:        record2.h
//
//  DESCRIPTION:
//   This file contains the structure for Project 2.
//      
//
****************************************************************/

#ifndef RECORD_H
#define RECORD_H

struct record
{
    int                accountno;     
    char               name[25];
    char               address[80];
    struct record*     next;
};

#endif
