CXX=g++

EXEC=check

PREFIX=/usr/local

BINDIR=$(PREFIX)/bin

SRC=main.cpp disp.cpp prog.cpp util.cpp layout.cpp obj.cpp piece.cpp scn.cpp
OBJ=$(SRC:%.cpp=$(BUILDDIR)/%.o)

HDR=cam.h math.h

BUILDDIR=build

LDFLAGS=-lGLEW -lGL -lSDL2

.PHONY: all
all: mk_build $(EXEC)

$(BUILDDIR)/%.o: %.cpp %.h
	$(CXX) -c $< -o $@

$(BUILDDIR)/main.o: main.cpp
	$(CXX) -c $< -o $@

$(EXEC): $(OBJ) $(HDR)
	$(CXX) $(OBJ) $(LDFLAGS) -o $@

.PHONY: mk_build
mk_build:
	mkdir -p $(BUILDDIR)

.PHONY: install
install:
	cp $(EXEC) $(BINDIR)

.PHONY: uninstall
uninstall:
	rm $(BINDIR)/$(EXEC)

.PHONY: clean
clean:
	rm $(BUILDDIR)/*.o $(EXEC)
