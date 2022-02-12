BIN = c-
CC = g++
CC_ARGS = -std=c++17

SRCS = $(BIN).y  $(BIN).l
HDRS = scanType.hpp
OBJS = lex.yy.o $(BIN).tab.o

$(BIN) : $(OBJS)
	$(CC) $(OBJS) strutil.cpp -o $(BIN) $(CC_ARGS)

lex.yy.c : $(BIN).l $(BIN).tab.hpp $(HDR)
	flex $(BIN).l

$(BIN).tab.hpp $(BIN).tab.cpp : $(BIN).y
	bison -v -t -d $(BIN).y

clean :
	rm -f *~ $(OBJS) $(BIN) lex.yy.cpp $(BIN).tab.hpp $(BIN).tab.cpp $(BIN).output

tar : $(HDR) $(SRCS) makefile
	tar -cvf $(BIN).tar $(HDRS) $(SRCS) strutil.cpp strutil.hpp makefile
