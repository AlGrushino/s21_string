CC= gcc 
CFLAGS = -Wall -Wextra -pedantic -std=c11
CCOV= -fprofile-arcs -ftest-coverage

all: s21_string.a

clean:
	@rm -rf *.o *.gcno *.gcda *.gcov *.a test logs

s21_string.a: clean minifunc.o c_sharp.o
	$(CC) $(CFLAGS) -c s21_string.c
	$(CC) $(CFLAGS) -c s21_sscanf.c
	ar rcs s21_string.a s21_string.o s21_sscanf.o minifunc.o c_sharp.o

minifunc.o: minifunc.c
	$(CC) $(CFLAGS) -c minifunc.c

c_sharp.o: c_sharp.c
	$(CC) $(CFLAGS) -c c_sharp.c

run_test:
	rm -rf test
	@make test

test: s21_string.a
	@$(CC) $(CCOV) test.c c_sharp.c s21_string.c s21_sscanf.c minifunc.c -lcheck -lm -lsubunit -o test
	@./test

gcov_report: test
	@rm -rf test-test.gcda test-test.gcno
	@mkdir logs
	@gcovr --html-self-contained --html-details -o logs/report.html
	@echo "Building report..."
	@open logs/report.html