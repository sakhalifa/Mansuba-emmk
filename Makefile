WIDTH ?= 5
HEIGHT ?= 4
MANSUBA_FLAGS = -DWIDTH=$(WIDTH) -DHEIGHT=$(HEIGHT)
CFLAGS = -Wall -Wextra -std=c99 -g3 $(MANSUBA_FLAGS)

BUILDDIR = build
SOURCEDIR = src

all: create project

create:
	mkdir -p build

%.o: $(SOURCEDIR)/%.c
	- gcc -c $(CFLAGS) -o $(BUILDDIR)/$@ $<

project: geometry.o neighbors.o world.o project.o
	gcc $(CFLAGS) $(BUILDDIR)/geometry.o $(BUILDDIR)/neighbors.o $(BUILDDIR)/world.o $(BUILDDIR)/project.o -o project

test_project: # (Add your dependency here, e.g "test.o")
	# (Add your compile command here, e.g "gcc $(CFLAGS) test.o -o test_project")

clean:
	rm -f $(BUILDDIR)/*.o *~
	rm project
