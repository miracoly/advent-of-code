###
CFLAGS  = -std=c17
CFLAGS += -g
#CFLAGS += -Wall
#CFLAGS += -Wextra
#CFLAGS += -pedantic
#CFLAGS += -Werror
#CFLAGS += -Wmissing-declarations
CFLAGS += -DUNITY_SUPPORT_64 -DUNITY_OUTPUT_COLOR
CFLAGS += -O0

ASANFLAGS  = -fsanitize=address
ASANFLAGS += -fno-common
ASANFLAGS += -fno-omit-frame-pointer

.PHONY: all
all: day_03.out
	@./day_03.out

day_03.out: ./*.c ./*.h
	@echo Compiling $@
	@$(CC) $(CFLAGS) ./*.c -o day_03.out

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM