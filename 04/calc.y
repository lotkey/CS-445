%{
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sym.h"
#include "symlist.h"
  // declare the symlist
  // this will contain all the syms
  // it is dynamically allocated
  //   so that there is no limit enforced by this program
  //   to the amount of syms allowed
  struct symlist list;
%}

%union {
  double dval;
  // instead of a symptr, the symname is now a char*
  // this makes it easier to add a new sym to the symlist
  char* symname;
}

%token <symname> NAME
%token <dval> NUMBER
%left '-' '+'
%left '*' '/'
%nonassoc UMINUS

%type <dval> expression
%%
statement_list
    : statement '\n'
    | statement_list statement '\n'
    ;

statement
    : NAME '=' expression { 
      // add a new sym into the symlist
      struct sym s;
      // assign the value the expression returns as the value
      s.value = $3;
      // assign NAME as the name
      strcpy(s.name, $1);
      // add it and make it modifiable
      symlistappend(&list, s, true);
 }
| '?' { symlistprint(&list); } // print the contents of the symlist containing all the syms
    | expression { printf("= %g\n", $1); }
    ;

expression
    : expression '+' expression { $$ = $1 + $3; }
    | expression '-' expression { $$ = $1 - $3; }
    | expression '*' expression { $$ = $1 * $3; }
    | expression '/' expression {
  if($3 == 0){
    // return the value of the first operand
    $$ = $1;
    // print the error message
    printf("divide by zero\n");
  }else{
    // otherwise, business as normal
    $$ = $1 / $3;
  }
  }
    | '-' expression %prec UMINUS { $$ = -$2; }
    | '(' expression ')' { $$ = $2; }
    | NUMBER
    | NAME {
      $$ = symlistgetval(&list, $1);
      }
    ;

%%

int main(){
  // initialize the symlist
  symlistinit(&list);
  // parse
  yyparse();
}

void symlistinit(struct symlist* list){
  // initalize the symlist by allocating memory for 10 slots
  symlistinitwithlen(list, 10);
}

void symlistinitwithlen(struct symlist* list, int listlen){
  // if listlen is not a valid number, intialize the bufsize to 10
  // the bufsize is the amount of memory that is added when reallocating
  (*list).bufsize = listlen > 0 ? listlen : 10;
  // initialize the size to bufsize
  (*list).size = (*list).bufsize;
  // allocate memory for the sym*
  (*list).syms = malloc(sizeof(struct sym) * (*list).bufsize);
  // allocate memory for the bool*
  (*list).modifiable = malloc(sizeof(bool) * (*list).bufsize);
  // len is the amount of valid syms there are
  // size is different
  //   size is the amount of syms that there are memory for
  //   the max capacity of syms
  (*list).len = 0;
  struct sym pi;
  pi.name = "PI";
  pi.value = 3.14159;
  struct sym phi;
  phi.name = "PHI";
  phi.value = 1.61803;
  // add PI and PHI and make them not modifiable
  symlistappend(list, phi, false);
  symlistappend(list, pi, false);
}

bool symlistappend(struct symlist* list, struct sym newsym, bool mod){
  // if the item is in the list and is not modifiable
  if(symlistinlist(list, newsym.name) && !(*list).modifiable[symlistindexof(list, newsym.name)]){
    // do nothing, return false
    return false;
  }
  // if the item is in the list but modifiable
  else if(symlistinlist(list, newsym.name)){
    // modify it and return true
    (*list).syms[symlistindexof(list, newsym.name)].value = newsym.value;
    return true;
  }
  else{
    // add it to the list
    // if the max capacity has been reached,
    // allocate more memory
    if((*list).len >= (*list).size){
      (*list).size += (*list).bufsize;
      (*list).syms = realloc((*list).syms, (*list).size * sizeof(struct sym));
      (*list).modifiable = realloc((*list).modifiable, (*list).size * sizeof(bool));
    }
    int i, j;
    bool b = false;
    // loop through and add alphabetically
    for(i = 0; i < (*list).len && !b; i++){
      if(strcmp(newsym.name, (*list).syms[i].name) == -1 && (*list).modifiable[i]){
	// shift elements to the right
	for(j = (*list).len; j > i; j--){
	  (*list).syms[j] = (*list).syms[j - 1];
	}
	i--;
	b = true;
      }
    }
    // allocate memory for the sym
    (*list).syms[i].name = malloc(sizeof(char) * (strlen(newsym.name) + 1));
    strcpy((*list).syms[i].name, newsym.name);
    (*list).syms[i].value = newsym.value;
    (*list).modifiable[i] = mod;   
    (*list).len++;
    return true;
  }
}

bool symlistinlist(struct symlist* list, char* symname){
  int i;
  // loop through the sym list
  for(i = 0; i < (*list).len; i++){
    // if found, return true
    if(strcmp((*list).syms[i].name, symname) == 0){
      return true;
    }
  }
  // otherwise, return false
  return false;
}

int symlistindexof(struct symlist* list, char* symname){
  // same approach as symlistinlist()
  // if found, return the index
  // otherwise, return -1
  int i;
  for(i = 0; i < (*list).len; i++){
    if(strcmp((*list).syms[i].name, symname) == 0){
      return i;
    }
  }
  return -1;
}

void symlistprint(struct symlist* list){
  // loop through the list and print
  //   in the format required by the homework
  printf("num-syms: %i\n", (*list).len);
  int i;
  for(i = 0; i < (*list).len; i++){
    printf("\t%s => %f\n", (*list).syms[i].name, (*list).syms[i].value);
  }
}

struct sym* symlistlookup(struct symlist* list, char* symname){
  // return the address of the specific sym
  return &((*list).syms[symlistindexof(list, symname)]);
}

double symlistgetval(struct symlist* list, char* symname){
  int i;
  // loop through the sym list
  for(i = 0; i < (*list).len; i++){
    // if found, return the value associated with it
    if(strcmp((*list).syms[i].name, symname) == 0){
      return (*list).syms[i].value;
    }
  }
  // otherwise, return 0
  return 0.0;
}
