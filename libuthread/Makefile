# Target library
lib := libuthread.a
FLAGS := -Wall -Wextra -Werror -g
SRCFILES := queue.c uthread.c context.c preempt.c

all: $(lib)

## TODO: Phase 1
$(lib): queue.o uthread.o context.o preempt.o
	ar rcs $(lib) $^

%.o : %.c
	gcc $(FLAGS) -c -o $@ $<

clean:
	rm -f $(lib) queue.o uthread.o context.o preempt.o