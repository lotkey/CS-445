BIN = c-
AR = ar rvs
CC = g++ --std=c++17 -g

GREEN="\e[0;32m"
NC="\e[0m"

AST_DIR = .ast.d
AST_SRCS = AST/*.cpp AST/*/*.cpp AST/*/*/*.cpp
AST_HDRS = AST/*.hpp AST/*/*.hpp AST/*/*/*.hpp
OPTIONS_DIR = .options.d
OPTIONS_SRCS = Options/*.cpp Options/*/*.cpp
OPTIONS_HDRS = Options/*.hpp Options/*/*.hpp
SYMTBL_DIR = .symtbl.d
SYMTBL_SRCS = SymbolTable/*.cpp
SYMTBL_HDRS = SymbolTable/*.hpp
SEMCHCK_DIR = .semchck.d
SEMCHCK_SRCS = SemanticsChecker/*.cpp
SEMCHCK_HDRS = SemanticsChecker/*.hpp
CODEGEN_DIR = .codegen.d
CODEGEN_SRC = CodeGen/*.cpp
CODEGEN_HDRS = CodeGen/*.hpp
IO_TM_CODE = CodeGen/ioTmCode.tm

SRCS = $(BIN).y $(BIN).l $(AST_SRCS) $(OPTIONS_SRCS) $(SYMTBL_SRCS) $(SEMCHCK_SRCS) strutil.cpp
HDRS = $(AST_HDRS) $(OPTIONS_HDRS) $(SYMTBL_HDRS) $(SEMCHCK_HDRS) strutil.hpp scanType.hpp
OBJS = lex.yy.o $(BIN).tab.o


$(BIN) : $(OBJS) $(AST_DIR) $(OPTIONS_DIR) $(SYMTBL_DIR) $(SEMCHCK_DIR) $(CODEGEN_DIR)
	@$(CC) strutil.cpp *.o -o $(BIN)
	@$(MAKE) clean

cmake : $(OBJS)
	@cd build; $(MAKE)
	@$(CC) *.o build/*.a -o $(BIN)
	@$(MAKE) clean

lex.yy.c : $(BIN).l $(BIN).tab.h
	@echo ${GREEN}"Flexing..."${NC}${NC}
	@flex -o lex.yy.c $(BIN).l
	@echo ${GREEN}"Finished flexing."${NC}

$(BIN).tab.h $(BIN).tab.c : $(BIN).y
	@echo ${GREEN}"Bisoning..."${NC}${NC}
	@bison -v -t -d $(BIN).y -o $(BIN).tab.c
	@echo ${GREEN}"Finished bisoning."${NC}

$(AST_DIR):
	@echo ${GREEN}"Compiling AST..."${NC}
	@$(CC) -c $(AST_SRCS)
	@echo ${GREEN}"Finished compiling AST."${NC}
	@mkdir $(AST_DIR)

$(OPTIONS_DIR):
	@echo ${GREEN}"Compiling Options..."${NC}
	@$(CC) -c $(OPTIONS_SRCS)
	@echo ${GREEN}"Finished compiling Options."${NC}
	@mkdir $(OPTIONS_DIR)

$(SYMTBL_DIR):
	@echo ${GREEN}"Compiling Symbol Table..."${NC}
	@$(CC) -c $(SYMTBL_SRCS)
	@echo ${GREEN}"Finished compiling Symbol Table."${NC}
	@mkdir $(SYMTBL_DIR)

$(SEMCHCK_DIR):
	@echo ${GREEN}"Compiling Semantics Checker..."${NC}
	@$(CC) -c $(SEMCHCK_SRCS)
	@echo ${GREEN}"Finished compiling Semantics Checker."${NC}
	@mkdir $(SEMCHCK_DIR)

$(CODEGEN_DIR):
	@echo ${GREEN}"Compiling CodeGen..."${NC}
	@$(CC) -c $(CODEGEN_SRC)
	@echo ${GREEN}"Finished compiling CodeGen."${NC}
	@mkdir $(CODEGEN_DIR)

clean :
	@echo ${GREEN}"Cleaning..."${NC}
	@rm -f *.o
	@rm -f lex.yy.c lex.yy.o $(BIN).tab.c $(BIN).tab.o $(BIN).tab.h
	@rm -rf $(AST_DIR) $(OPTIONS_DIR) $(SYMTBL_DIR) $(SEMCHCK_DIR) $(CODEGEN_DIR)
	@echo ${GREEN}"Finished cleaning."${NC}

tar : $(HDR) $(SRCS) makefile
	@tar -cvf $(BIN).tar $(HDRS) $(SRCS) $(IO_TM_CODE) makefile