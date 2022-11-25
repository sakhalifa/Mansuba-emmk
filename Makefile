WIDTH ?= 5
HEIGHT ?= 4
MANSUBA_FLAGS = -DWIDTH=$(WIDTH) -DHEIGHT=$(HEIGHT)
CFLAGS = -Wall -Wextra -std=c99 -g3 $(MANSUBA_FLAGS)
OBJCMD = gcc -c -Isrc/ $(CFLAGS) -o $(BUILDDIR)/$@ $<

BUILDDIR = build
SOURCEDIR = src
TESTSDIR = tst

all: create project

create:
	mkdir -p build

test_%.o: $(TESTSDIR)/%.c
	- $(OBJCMD)

%.o: $(SOURCEDIR)/%.c
	- $(OBJCMD)

project: geometry.o neighbors.o world.o game.o player.o moves.o position.o tree.o array_list.o
	gcc $(CFLAGS) $(addprefix $(BUILDDIR)/, $^) -o project

test_project: test_main.o test_array_list.o test_neighbors.o test_moves.o test_player.o test_tree.o tree.o moves.o world.o player.o position.o neighbors.o array_list.o geometry.o
	- gcc -Wall -Wextra -std=c99 -g3 -DWIDTH=5 -DHEIGHT=4 -Isrc/ $(addprefix $(BUILDDIR)/, $^) -o test_project
	- valgrind ./test_project

test: test_project

clean:
	rm -f $(BUILDDIR)/*.o *~
	rm -f project
	rm -f test_project
	- 
