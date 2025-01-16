/*
 *  File: lstpriv.h
 *
 *  by Bruce Mcq and Robert Ald
 */
#ifndef __LSTPRIV_H__
#define __LSTPRIV_H__

#pragma warning(disable : 4200)

struct LIST_HEAD
{
  int         CurrentIndex;

  int         CurrentTraverseIndex;

    int         MaxNumberOfObjects;

  // Recursion test variables
  unsigned char   Dump;

  unsigned char   Find;

  unsigned char   GetExtrema;

  unsigned char       Remove;

  unsigned char       Sort;
  //

  unsigned char padding[7];

  CLIENT_EVALUATE   ClientEvaluate;

  CLIENT_EQUIVALENCE  ClientEquality;

    CLIENT_COMPARE    ClientCompare;

  // NEEDS TO BE A SEPERATE ALLOCATION FOR DYNAMIC GROWTH
    CLIENT_POTYPE*      ObjectArray;

};

#endif // __LSTPRIV_H__

#pragma warning(default : 4200)
