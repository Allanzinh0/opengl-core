CPP_SRC = $(wildcard src/*.cpp src/**/*.cpp)
HEADERS = $(wildcard src/*.h src/**/*.h)
DEBUG_OBJS = $(patsubst src/%.cpp,obj/debug/%.o,$(CPP_SRC))
RELEASE_OBJS = $(patsubst src/%.cpp,obj/release/%.o,$(CPP_SRC))

INCLUDE_FOLDERS=vendor/glfw/include vendor/glad/inc

DEBUG_ARGS = -Wall -g -O0
RELEASE_ARGS = -Wall -O3

DIR_GUARD=$(shell [ ! -d $(@D) ] && mkdir -p $(@D))

debug: ${DEBUG_OBJS} lib/libglad.a lib/libglfw3.a 
	g++ $(DEBUG_ARGS) -Llib $(patsubst %,-I%,$(INCLUDE_FOLDERS)) -o debug.out $^

release: ${RELEASE_OBJS} lib/libglfw3.a lib/libglad.a
	g++ $(RELEASE_ARGS) -Llib $(patsubst %,-I%,$(INCLUDE_FOLDERS)) -o release.out $^

lib/libglfw3.a:
	$(DIR_GUARD)
	cmake -S vendor/glfw -B vendor/glfw/build
	make -C vendor/glfw/build
	cp vendor/glfw/build/src/libglfw3.a $@

lib/libglad.a:
	$(DIR_GUARD)
	make -C vendor/glad
	cp vendor/glad/dist/libglad.a lib/libglad.a

obj/debug/%.o: src/%.cpp $(HEADERS)
	$(DIR_GUARD)
	g++ $(DEBUG_ARGS) $(patsubst %,-I%,$(INCLUDE_FOLDERS)) -c $< -o $@

obj/release/%.o: src/%.cpp $(HEADERS)
	$(DIR_GUARD)
	g++ $(RELEASE_ARGS) $(patsubst %,-I%,$(INCLUDE_FOLDERS)) -c $< -o $@

clean:
	rm -rf obj lib debug.out release.out
