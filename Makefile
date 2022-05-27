CXX=g++

SRC=main.cpp disp.cpp prog.cpp util.cpp layout.cpp obj.cpp piece.cpp scn.cpp
OBJ=$(SRC:%.cpp=$(BUILDDIR)/%.o)

HDR=cam.h math.h

BUILDDIR=build

LDFLAGS+=-lGLEW -lGL
LDFLAGS+=-lSDL2

.PHONY: all
all: mk_build check

$(BUILDDIR)/%.o: %.cpp %.h
	$(CXX) -c $< -o $@

$(BUILDDIR)/main.o: main.cpp
	$(CXX) -c $< -o $@

check: $(OBJ) $(HDR)
	$(CXX) $(OBJ) $(LDFLAGS) -o $@

.PHONY: mk_build
mk_build:
	mkdir -p $(BUILDDIR)

.PHONY: clean
clean:
	rm $(BUILDDIR)/*.o check
