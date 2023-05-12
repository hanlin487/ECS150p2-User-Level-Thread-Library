# Target library
lib := libuthread.a
FLAGS := -Wall -Wextra -Werror -g
SRCFILES := queue.c uthread.c context.c sem.c preempt.c

all: $(lib)

$(lib): queue.o uthread.o context.o sem.o preempt.o
	ar rcs $(lib) $^

%.o : %.c
	gcc $(FLAGS) -c -o $@ $<

clean:
	rm -f $(lib) queue.o uthread.o context.o sem.o preempt.o
