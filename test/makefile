CC = g++ --std=c++17
AR = ar rvs
BIN = test

DIR = ./.makedir

AL = $(DIR)/awesomelibrary.a
AL_DIR = $(AL).d
AL_SRCS = awesomelibrary.cpp
AL_HDRS = awesomelibrary.hpp

OKL = $(DIR)/oklibrary.a
OKL_DIR = $(OKL).d
OKL_SRCS = oklibrary.cpp
OKL_HDRS = oklibrary.hpp

MAIN = main.cpp

$(BIN): $(AL) $(OKL) $(DIR)
	$(CC) $(MAIN) $(AL) $(OKL) -o $(BIN)

$(AL): $(DIR) $(AL_DIR)
	cd $(AL_DIR) ; $(CC) -c ../../$(AL_SRCS)
	$(AR) $(AL) $(AL_DIR)/*.o
$(AL_DIR) : $(DIR)
	mkdir $(AL_DIR)

$(OKL): $(DIR) $(OKL_DIR)
	cd $(OKL_DIR) ; $(CC) -c ../../$(OKL_SRCS)
	$(AR) $(OKL) $(OKL_DIR)/*.o
$(OKL_DIR) : $(DIR)
	mkdir $(OKL_DIR)

$(DIR):
	mkdir $(DIR)

clean:
	rm -rf $(DIR)
	rm $(BIN)