CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11
GCOV = -fprofile-arcs -ftest-coverage
SRCS = s21_calculator.c
TARGET = SmartCalc
TEST_LIBS = -lcheck -lm -lpthread
OBJS = $(SRCS:.c=.o)
OS := $(shell uname -s)


ifeq ($(OS), Linux)
CFLAGS += -D OS_LINUX
ADD_LIB = -lcheck -lm -lrt -lpthread
TEST_FLAGS =-lpthread -lcheck -pthread -lrt -lm
endif
ifeq ($(OS), Darwin)
CFLAGS += -D OS_MAC
ADD_LIB =
TEST_FLAGS =-lcheck
endif


all: calculator

calculator: calculator.a
	$(CC) Back/test.c -lcheck -L. calculator.a -o calculator

calculator.a:
	$(CC) -c $(CFLAGS) Back/$(SRCS)
	ar rcs calculator.a $(OBJS)
	ranlib calculator.a

install:
	qmake -o View/Makefile View/$(TARGET).pro
	cd View && make

start: install
	cd View/$(TARGET).app/Contents/MacOS && ./$(TARGET)

uninstall: clean
	rm -rf View

dist: install 
	tar -czf $(TARGET).tgz src

dvi:
	open read_me.txt

test: clean
	$(CC)  $(TEST_LIBS) Back/s21_calculator.c Back/test.c -o test
	./test

clean:
	rm -rf *.a Back/*.o View/*.o  *.o *.info *.gcno *.gcda *.gcov  test
	rm -rf s21_calculator  Back/a.out  .clang-format Back/a.out.dSYM

gcov_report:
	$(CC) $(GCOV) Back/test.c Back/$(SRCS) -o test -lcheck
	./test
	lcov -t "test" -o test.info -c -d ./
	genhtml test.info -o report
	open report/index.html

install_brew:
	cd ~
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew install lcov

valgrind_check: test
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./s21_matrix

leak: test
	CK_FORK=no leaks -atExit -- ./s21_smartcalc

style:
	cp ../materials/linters/.clang-format ./
	clang-format -n Back/*.c Back/*.h

\rebuild:
	$(MAKE) clean
	$(MAKE) all