CXX=g++

STATIC=main.cpp disp.cpp prog.cpp util.cpp obj.cpp piece.cpp layout.cpp scn.cpp
OBJ_STATIC=$(patsubst %.cpp, %.o, $(STATIC))

HDR=cam.h

GL=-lGLEW -lGL
SDL=-lSDL2
LDFLAGS+=$(SDL)
LDFLAGS+=$(GL)

.PHONY: clean

all: make

%.o: %.cpp %.h
	$(CXX) -c $< -o $@ $(LDFLAGS)

%.o: %.cpp %.h
	$(CXX) -c $< -o $@ $(LDFLAGS)

main.o: main.cpp
	$(CXX) -c $< -o $@ $(LDFLAGS)

make: $(OBJ_STATIC) $(HDR)
	$(CXX) $(OBJ_STATIC) $(LDFLAGS)

clean:
	rm *.o a.out
