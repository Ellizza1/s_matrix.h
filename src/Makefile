# ============================================================================
# Компилятор и флаги
# ============================================================================
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
GCOV_FLAGS = --coverage
# ============================================================================
# ОС
# ============================================================================
OS := $(shell uname -s)
ifeq ($(OS), Darwin)
    CHECK_FLAGS = -lcheck -lm -lpthread
    INC = -I/opt/homebrew/include
    LIB = -L/opt/homebrew/lib
    OPEN_CMD = open
else
    CHECK_FLAGS = -lcheck -lm -lpthread -lrt -lsubunit
    INC =
    LIB =
    OPEN_CMD = xdg-open
endif
# ============================================================================
# Файлы
# ============================================================================
SRC = $(wildcard *.c)
TEST_SRC = $(wildcard tests/*.c)
OBJ = $(SRC:.c=.o)
TEST_OBJ = $(TEST_SRC:.c=.o)
LIB_NAME = s21_matrix.a
TEST_EXEC = s21_test
# ============================================================================
# Основные цели
# ============================================================================
.PHONY: all clean test gcov_report valgrind leaks rebuild
all: $(LIB_NAME)
# ============================================================================
# Библиотека
# ============================================================================
$(LIB_NAME): $(OBJ)
	ar rcs $(LIB_NAME) $(OBJ)
	ranlib $(LIB_NAME)
%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@
# ============================================================================
# Тесты
# ============================================================================
test: clean $(LIB_NAME)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(INC) -c $(SRC)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(INC) -c $(TEST_SRC)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -o $(TEST_EXEC) *.o $(LIB_NAME) $(LIB) $(CHECK_FLAGS)
	./$(TEST_EXEC)
# ============================================================================
# Покрытие
# ============================================================================
gcov_report: test
	lcov -c -d . -o coverage.info
	lcov --extract coverage.info '*/s21_*.c' -o coverage_filtered.info
	genhtml coverage_filtered.info -o coverage_html
	$(OPEN_CMD) coverage_html/index.html
# ============================================================================
# Проверка утечек памяти 
# ============================================================================
valgrind: $(LIB_NAME)
	$(CC) $(CFLAGS) $(INC) -c $(SRC)
	$(CC) $(CFLAGS) $(INC) -c $(TEST_SRC)
	$(CC) $(CFLAGS) -o $(TEST_EXEC) *.o $(LIB_NAME) $(LIB) $(CHECK_FLAGS)
	@echo "========================================="
	@echo "Running tests with memory leak detection..."
	@echo "========================================="
	@./$(TEST_EXEC) & \
	PID=$$!; \
	sleep 1; \
	echo ""; \
	echo "Checking for memory leaks..."; \
	leaks $$PID 2>&1 | grep -E "leaks for|leak:" || echo "No memory leaks found"; \
	kill $$PID 2>/dev/null || true
# ============================================================================
# Очистка
# ============================================================================
clean:
	rm -f *.o tests/*.o
	rm -f s21_matrix.a s21_test
	rm -f *.gcda *.gcno *.info
	rm -rf coverage_html
	rm -rf build
# ============================================================================
# Пересборка
# ============================================================================
rebuild: clean all