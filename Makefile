CXX=g++

SRC=main.cpp disp.cpp prog.cpp util.cpp layout.cpp obj.cpp piece.cpp scn.cpp
OBJ=$(patsubst %.cpp, %.o, $(SRC))

HDR=cam.h

LDFLAGS+=-lGLEW -lGL
LDFLAGS+=-lSDL2

.PHONY: all
all: check

%.o: %.cpp %.h
	$(CXX) -c $< -o $@ $(LDFLAGS)

main.o: main.cpp
	$(CXX) -c $< -o $@ $(LDFLAGS)

check: $(OBJ) $(HDR)
	$(CXX) $(OBJ) $(LDFLAGS) -o $@

.PHONY: clean
clean:
	rm *.o check
