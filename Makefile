CXX=g++

STATIC=main disp prog util piece
OBJ_STATIC=$(patsubst %, %.o, $(STATIC))

HDR=layout.h

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
	$(CXX) $^ $(LDFLAGS)

clean:
	rm *.o a.out
