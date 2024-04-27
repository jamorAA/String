.PHONY: all clean test s21_string.a gcov_report
CC = -Wall -Werror -Wextra -std=c11
OS := $(shell uname)

ifeq ($(OS), Darwin)
    FLAGS = -lcheck -lm -lpthread -fprofile-arcs -ftest-coverage
else
    FLAGS = -lcheck -lm -lpthread -lrt -lsubunit -fprofile-arcs -ftest-coverage
endif

all: clean s21_string.a test gcov_report

s21_string.a: s21_string.o
	ar -crs s21_string.a s21_*.o


s21_string.o:
	gcc $(CC) -c s21_*.c

test: s21_string.a test_string.c
	gcc test_string.c $(FLAGS) s21_*.c s21_string.a -o unit_test 
	./unit_test

clean:
	rm -rf unit_test *.a *.o *.gc* *.info report

gcov_report: clean s21_string.a test
	lcov -t "unit_test"  -o report.info -c -d .
	genhtml -o report report.info
	open ./report/index.html

clang:
	cp ../materials/linters/.clang-format ./
	clang-format -n s21_*.c *.h test_string.c
rebuild: clean s21_string.a test gcov_report
