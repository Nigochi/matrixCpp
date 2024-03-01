CFLAGS = -Wall -Werror -Wextra

all: s21_matrix_oop.a test

rebuild: clean all

build: s21_matrix_oop.cpp
	g++ -c $(CFLAGS) -std=c++17 s21_matrix_oop.cpp -o s21_matrix_oop.o

s21_matrix_oop.a: build
	ar rcs s21_matrix_oop.a s21_matrix_oop.o
	ranlib s21_matrix_oop.a

test: s21_matrix_oop.a ./test.cpp
	g++ -lgtest -lstdc++ -std=c++17 --coverage s21_matrix_oop.cpp ./test.cpp -o test
	./test

gcov_report: test
	./test > /dev/null
	lcov -c -d . -o report.info --no-external
	genhtml -o "html_report" report.info
	open html_report/index.html

clang:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -style=Google -n *.cpp *.h
	rm .clang-format

clean:
	rm -rf *.o *.out s21_matrix_oop.a test *.gcda *.gcno report gcov_report.* gcov_report *.info html_report
