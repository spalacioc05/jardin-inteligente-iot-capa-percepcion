CC ?= cc
CFLAGS = -std=c11 -Wall -Wextra -Werror -pedantic -O2
ifeq ($(OS),Windows_NT)
EXEEXT = .exe
endif
all: test
build:
ifeq ($(OS),Windows_NT)
	if not exist build mkdir build
else
	mkdir -p build
endif
build/test_control_logic$(EXEEXT): test_control_logic.c ../src/control_logic.c ../include/control_logic.h | build
	$(CC) $(CFLAGS) -I../include test_control_logic.c ../src/control_logic.c -o $@
test: build/test_control_logic$(EXEEXT)
	./build/test_control_logic$(EXEEXT)
clean:
ifeq ($(OS),Windows_NT)
	if exist build rmdir /s /q build
else
	rm -rf build
endif
.PHONY: all test clean
