CXX=g++

STATIC=main.cpp disp.cpp prog.cpp util.cpp layout.cpp obj.cpp piece.cpp scn.cpp
OBJ_STATIC=$(patsubst %.cpp, %.o, $(STATIC))

HDR=cam.h

GL=-lGLEW -lGL
SDL=-lSDL2
LDFLAGS+=$(SDL)
LDFLAGS+=$(GL)

.PHONY: clean

all: check

%.o: %.cpp %.h
	$(CXX) -c $< -o $@ $(LDFLAGS)

main.o: main.cpp
	$(CXX) -c $< -o $@ $(LDFLAGS)

check: $(OBJ_STATIC) $(HDR)
	$(CXX) $(OBJ_STATIC) $(LDFLAGS) -o $@

clean:
	rm *.o check
