GCC = g++ -Wall -Wextra -Werror
LIBS = -lgtest
LINUX = -lsubunit -lrt -lpthread -lm
VALGRIND_FLAGS = --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose
OS = $(shell uname -s)

SRC = Model/Model.cc Controller/Controller.cc
TEST_SRC = s21_test.cc
TARGET = Model.a
OBJ = Model.o Controller.o

ifeq ($(OS), Linux)
	LIBS += -lgmock -pthread
endif

all: clean $(TARGET) test

$(TARGET):
	$(GCC) -c $(SRC)
	ar rc $(TARGET) $(OBJ)
	ranlib $(TARGET)

test: clean
	$(GCC) $(SRC) $(TEST_SRC) -o test $(LIBS)
	./test --gtest_repeat=10 --gtest_break_on_failure

valgrind: clean $(TARGET)
	$(GCC) $(TEST_SRC) $(TARGET) -o test $(LIBS) $(LINUX)
	CK_FORK=no valgrind $(VALGRIND_FLAGS) --log-file=RESULT_VALGRIND.txt ./test

gcov_report: clean
	$(GCC) --coverage $(TEST_SRC) $(SRC) -o test $(LIBS) -fno-elide-constructors
	chmod +x test
	./test
	lcov -t "test" -o test.info --no-external -c -d .
	genhtml -o report/ test.info
	open ./report/index.html

clang:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -style=Google -i *.cc *.h
	clang-format -style=Google -n *.cc *.h
	rm .clang-format

clean:
	rm -rf $(OBJ)
	rm -rf $(TARGET)
	rm -rf a.out*
	rm -rf gtest.*o
	rm -rf report
	rm -rf test*
	rm -rf *.gcda
	rm -rf *.dSYM
	rm -rf RESULT_VALGRIND.txt

