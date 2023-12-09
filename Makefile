TASK1_SRC	:= schedsim.c util.c
EXE		:= schedsim

all: $(EXE)

schedsim: $(TASK1_SRC)
	gcc -Wall  -std=c99 -std=gnu99 -Werror -pedantic -g $^ -o $@

clean:
	rm -f $(EXE)