DIR_GUARD=$(shell [ ! -d $(@D) ] && mkdir -p $(@D))

all: dist/libglad.a

dist/libglad.a: obj/glad.o
	$(DIR_GUARD)
	ar -rsv dist/libglad.a obj/glad.o

obj/glad.o: src/glad.c
	$(DIR_GUARD)
	gcc -Wall -O3 -Iinc/glad -c $< -o $@

clean:
	rm -rf obj libglad.so 
