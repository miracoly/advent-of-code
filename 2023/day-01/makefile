###
CFLAGS  = -std=c11
CFLAGS += -g
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -pedantic
CFLAGS += -Werror
CFLAGS += -Wmissing-declarations
CFLAGS += -DUNITY_SUPPORT_64 -DUNITY_OUTPUT_COLOR

ASANFLAGS  = -fsanitize=address
ASANFLAGS += -fno-common
ASANFLAGS += -fno-omit-frame-pointer

.PHONY: all
all: day_01.out
	@./day_01.out

day_01.out: ./*.c ./*.h
	@echo Compiling $@
	@$(CC) $(CFLAGS) ./*.c -o day_01.out

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM