BIN = c-
AR = ar rvs
CC = g++ --std=c++17 -g
DIR = .makedir.d

AST = $(DIR)/AST.d
AST_OBJS = $(AST)/*.o
AST_SRCS = ../../AST/*.cpp ../../AST/*/*.cpp ../../AST/*/*/*.cpp ../../AST/*/*/*/*.cpp
AST_HDRS = ../../AST/*.hpp ../../AST/*/*.hpp ../../AST/*/*/*.hpp ../../AST/*/*/*/*.hpp

OPTIONS = $(DIR)/Options.d
OPTIONS_OBJS = $(OPTIONS)/*.o
OPTIONS_SRCS = ../../Options/*.cpp ../../Options/*/*.cpp
OPTIONS_HDRS = ../../Options/*.hpp ../../Options/*/*.hpp

SYMTBL = $(DIR)/SymbolTable.d
SYMTBL_OBJS = $(SYMTBL)/*.o
SYMTBL_SRCS = ../../SymbolTable/*.cpp
SYMTBL_HDRS = ../../SymbolTable/*.hpp

SEMCHCK = $(DIR)/SemanticsChecker.d
SEMCHCK_OBJS = $(SEMCHCK)/*.o
SEMCHCK_SRCS = ../../SemanticsChecker/*.cpp
SEMCHCK_HDRS = ../../SemanticsChecker/*.hpp

SRCS = $(BIN).y $(BIN).l $(AST_SRCS) $(OPTIONS_SRCS) $(SYMTBL_SRCS) $(SEMCHCK_SRCS)
HDRS = $(AST_HDRS) $(OPTIONS_HDRS) $(SYMTBL_HDRS) $(SEMCHCK_HDRS)
OBJS = lex.yy.o $(BIN).tab.o

$(BIN) : $(OBJS) $(DIR) $(SYMBTBL) $(AST) $(OPTIONS) $(SEMCHCK)
	$(CC) strutil.cpp $(OBJS) $(SYMTBL_OBJS) $(AST_OBJS) $(SEMCHCK_OBJS) $(OPTIONS_OBJS) -o $(BIN)

lex.yy.c : $(BIN).l $(BIN).tab.h
	flex $(BIN).l

$(BIN).tab.h $(BIN).tab.c : $(BIN).y
	bison -v -t -d $(BIN).y

$(SEMCHCK) : $(DIR) $(AST) $(OPTIONS) $(SYMTBL)
	mkdir $(SEMCHCK)
	cd $(SEMCHCK) ; $(CC) -c $(SEMCHCK_SRCS)

$(AST) : $(DIR)
	mkdir $(AST)
	cd $(AST) ; $(CC) -c $(AST_SRCS)

$(OPTIONS) : $(DIR)
	mkdir $(OPTIONS)
	cd $(OPTIONS) ; $(CC) -c $(OPTIONS_SRCS)

$(SYMTBL) : $(DIR)
	mkdir $(SYMTBL)
	cd $(SYMTBL) ; $(CC) -c $(SYMTBL_SRCS)

clean : $(DIR)
	rm -rf $(DIR)
	rm $(BIN) $(BIN).output $(BIN).tab.c $(BIN).tab.h $(BIN).tab.o lex.yy.c lex.yy.o

tar : $(HDR) $(SRCS) makefile
	tar -cvf $(BIN).tar $(HDRS) $(SRCS) makefile

$(DIR) :
	mkdir $(DIR)