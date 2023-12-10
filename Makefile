STUDENT_ID=XXXXXXX

TASK1_SRC	:= $(wildcard task1/*.c)
TASK2_SRC 	:= $(wildcard task2/*.c)
EXE		:= task1/qsort task2/func_ptr

all: $(EXE)

task1/qsort: $(TASK1_SRC)
	gcc -Wall -std=c99 -Werror -pedantic -g $^ -o $@

task2/func_ptr: $(TASK2_SRC)
	gcc -Wall -std=c99 -Werror -pedantic -g $^ -o $@

test: task1/qsort
	./$< task1/test-data/test1.csv > task1/test-data/test1.log
	diff task1/test-data/test1.log task1/test-data/test1-exp.log

clean:
	rm -f $(EXE)

zip:
	make clean
	mkdir $(STUDENT_ID)-fp-lab
	cp -r  Makefile task1 task2 $(STUDENT_ID)-fp-lab
	zip -r $(STUDENT_ID)-fp-lab.zip $(STUDENT_ID)-fp-lab
	rm -rf $(STUDENT_ID)-fp-lab
