CC=g++
DEBUG_FLAGS= #-DDEBUG_LEVEL=LEVEL_DEBUG
RELEASE_FLAGS= #-DDEBUG_LEVEL=LEVEL_RELEASE

ifeq ($(VERSION), DEBUG)
	VERSION_FLAGS=$(DEBUG_FLAGS)
else
	VERSION_FLAGS=$(RELEASE_FLAGS)
	OPT=-O2
endif

CFLAGS=-g -Wall -std=c++0x $(VERSION_FLAGS) -DBASE_THRESHOLD=10
LIB=#-lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_nonfree -lopencv_legacy
SRC=main.cpp
OBJ=kd_tree.o

main: $(OBJ) $(SRC)
	$(CC) $(CFLAGS) $(OPT) $^ -o $@ $(LIB) 

kd_tree.o: kd_tree.cpp
	$(CC) $(CFLAGS) -c $^

print_vars:
	-echo ${VERSION}

clean:
	-rm $(OBJ) main
