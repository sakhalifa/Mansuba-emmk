WIDTH ?= 5
HEIGHT ?= 4
MANSUBA_FLAGS = -DWIDTH=$(WIDTH) -DHEIGHT=$(HEIGHT)
CFLAGS = -Wall -Wextra -std=c99 -g3 $(MANSUBA_FLAGS)

all: create project

create:
	mkdir -p build

%.o: src/%.c
	- gcc -c $(CFLAGS) -o build/$@ $<

project: geometry.o neighbors.o world.o project.o
	gcc $(CFLAGS) build/geometry.o build/neighbors.o build/world.o build/project.o -o project

test_project: # (Add your dependency here, e.g "test.o")
	# (Add your compile command here, e.g "gcc $(CFLAGS) test.o -o test_project")

clean:
	rm -f build/*.o *~
	rm project
