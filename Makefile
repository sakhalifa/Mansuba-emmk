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

test_array_list: array_list.o array_list_test.o
	gcc $(CFLAGS) $(BUILDDIR)/array_list.o $(BUILDDIR)/array_list_test.o -o test_array_list

test: test_array_list
	./test_array_list

clean:
	rm -f $(BUILDDIR)/*.o *~
	rm -f project
	rm -f test_array_list
