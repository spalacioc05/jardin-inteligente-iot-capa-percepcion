CC ?= cc
CFLAGS = -std=c11 -Wall -Wextra -Werror -pedantic -O2
all: test
build:
	mkdir -p build
build/test_control_logic: test_control_logic.c ../src/control_logic.c ../include/control_logic.h | build
	$(CC) $(CFLAGS) -I../include test_control_logic.c ../src/control_logic.c -o $@
test: build/test_control_logic
	./build/test_control_logic
clean:
	rm -rf build
.PHONY: all test clean
