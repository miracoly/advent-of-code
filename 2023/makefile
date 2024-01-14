###
CFLAGS  = -std=c2x
CFLAGS += -g
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -pedantic
CFLAGS += -Werror
CFLAGS += -Wmissing-declarations
CFLAGS += -DUNITY_SUPPORT_64 -DUNITY_OUTPUT_COLOR

LIBS = -lm
TEST_LIBS = -lcriterion -lm

ASANFLAGS  = -fsanitize=address
ASANFLAGS += -fno-common
ASANFLAGS += -fno-omit-frame-pointer

.PHONY: all
all: day-04.out
	@./day-04.out

day-01: day-01.out
	@./day-01.out

day-01.out: ./day-01/*.c ./day-01/*.h
	@echo Compiling $@
	@$(CC) $(CFLAGS) ./day-01/day-01.c -o day-01.out

day-02: day-02.out
	@./day-02.out

day-02.out: ./day-02/*.c
	@echo Compiling $@
	@$(CC) $(CFLAGS) ./day-02/day-02.c -o day-02.out
	
day-03: day-03.out
	@./day-03.out

day-03.out: ./day-03/*.c
	@echo Compiling $@
	@$(CC) $(CFLAGS) ./day-03/day-03.c -o day-03.out

day-04: day-04.out
	@./day-04.out

day-04.out: ./day-04/*.c ./day-04/*.h
	@echo Compiling $@
	@$(CC) $(CFLAGS) ./day-04/main.c ./day-04/day-04.c ./lib/aoc-lib.c -o day-04.out $(LIBS)

day-04-test: day-04-tests.out
	@./day-04-tests.out

day-04-tests.out: ./day-04/*.c ./day-04/*.h
	@echo Compiling $@
	@$(CC) $(CFLAGS) ./day-04/day-04.c ./day-04/day-04-tests.c ./lib/aoc-lib.c -o day-04-tests.out $(TESTLIBS)

lib-test: lib-tests.out
	@./lib-tests.out

lib-tests.out: ./lib/*.c ./lib/*.h
	@$(CC) $(CFLAGS) ./lib/aoc-lib-tests.c ./lib/aoc-lib.c -o lib-tests.out $(TESTLIBS)

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM