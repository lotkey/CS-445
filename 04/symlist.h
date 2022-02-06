/*
Chris McVickar
CS 240
HW5
Interface file for struct symlist
 */

#ifndef SYMLIST_H
#define SYMLIST_H
#include <stdbool.h>
#include "sym.h"

struct symlist{
  struct sym* syms;
  bool* modifiable;
  int len;
  int size;
  int bufsize;
};

void symlistinit(struct symlist*);
void symlistinitwithlen(struct symlist*, int);
bool symlistappend(struct symlist*, struct sym, bool);
bool symlistinlist(struct symlist*, char*);
int symlistindexof(struct symlist*, char*);
void symlistprint(struct symlist*);
struct sym* symlistlookup(struct symlist*, char*);
double symlistgetval(struct symlist*, char*);

#endif