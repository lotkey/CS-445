BIN = c-
AR = ar rvs
CC = g++ --std=c++17 -g

AST_SRCS = AST/*.cpp AST/*/*.cpp AST/*/*/*.cpp AST/*/*/*/*.cpp
AST_HDRS = AST/*.hpp AST/*/*.hpp AST/*/*/*.hpp AST/*/*/*/*.hpp
OPTIONS_SRCS = Options/*.cpp Options/*/*.cpp
OPTIONS_HDRS = Options/*.hpp Options/*/*.hpp
SYMTBL_SRCS = SymbolTable/*.cpp
SYMTBL_HDRS = SymbolTable/*.hpp
SEMCHCK_SRCS = SemanticsChecker/*.cpp
SEMCHCK_HDRS = SemanticsChecker/*.hpp

SRCS = $(BIN).y $(BIN).l $(AST_SRCS) $(OPTIONS_SRCS) $(SYMTBL_SRCS) $(SEMCHCK_SRCS) strutil.cpp
HDRS = $(AST_HDRS) $(OPTIONS_HDRS) $(SYMTBL_HDRS) $(SEMCHCK_HDRS) strutil.hpp scanType.hpp
OBJS = lex.yy.o $(BIN).tab.o

$(BIN) : $(OBJS)
	$(CC) strutil.cpp $(OBJS) $(SYMTBL_SRCS) $(AST_SRCS) $(SEMCHCK_SRCS) $(OPTIONS_SRCS) -o $(BIN)
	make clean

lex.yy.c : $(BIN).l $(BIN).tab.h
	flex -o lex.yy.c $(BIN).l

$(BIN).tab.h $(BIN).tab.c : $(BIN).y
	bison -v -t -d $(BIN).y -o $(BIN).tab.c

clean :
	rm -f lex.yy.c lex.yy.o $(BIN).tab.c $(BIN).tab.o $(BIN).tab.h $(BIN).output

tar : $(HDR) $(SRCS) makefile
	tar -cvf $(BIN).tar $(HDRS) $(SRCS) makefile