BIN = c-
CC = g++ --std=c++17 -g

SRCS = $(BIN).y  $(BIN).l
CCSRCS = strutil.cpp AST/*.cpp AST/*/*.cpp AST/Exp/Op/*.cpp Options/*.cpp Options/ourgetopt/*.cpp
HDRS = scanType.hpp strutil.hpp AST/*.hpp AST/*/*.hpp AST/Exp/Op/*.hpp Options/*.hpp Options/ourgetopt/*.hpp
OBJS = lex.yy.o $(BIN).tab.o

$(BIN) : $(OBJS)
	$(CC) $(OBJS) $(CCSRCS) -o $(BIN)

lex.yy.c : $(BIN).l $(BIN).tab.h $(HDR)
	flex $(BIN).l

$(BIN).tab.h $(BIN).tab.c : $(BIN).y
	bison -v -t -d $(BIN).y

clean :
	rm -f *~ $(OBJS) $(BIN) lex.yy.c $(BIN).tab.h $(BIN).tab.c $(BIN).output

tar : $(HDR) $(SRCS) makefile
	tar -cvf $(BIN).tar $(HDRS) $(SRCS) $(CCSRCS) makefile
