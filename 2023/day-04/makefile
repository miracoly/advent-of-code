###
CFLAGS  = -std=c17
CFLAGS += -g
#CFLAGS += -Wall
#CFLAGS += -Wextra
#CFLAGS += -pedantic
#CFLAGS += -Werror
#CFLAGS += -Wmissing-declarations
CFLAGS += -DUNITY_SUPPORT_64 -DUNITY_OUTPUT_COLOR

LIBS = -lcriterion

ASANFLAGS  = -fsanitize=address
ASANFLAGS += -fno-common
ASANFLAGS += -fno-omit-frame-pointer

.PHONY: all
all: main.out
	@./main.out

main.out: ./*.c ./*.h
	@echo Compiling $@
	@$(CC) $(CFLAGS) ./main.c day_04.c -o main.out

test: tests.out
	@./tests.out

tests.out: ./*.c ./*.h
	@$(CC) $(CFLAGS) ./tests.c ./day_04.c  -o tests.out $(LIBS)

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM