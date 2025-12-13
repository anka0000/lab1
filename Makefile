# Makefile для проекта Туроператор

# Компилятор
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -std=c99
LDFLAGS =

# Директории
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = include

# Имена файлов
TARGET = $(BIN_DIR)/tour_operator
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))

# Основная цель
all: $(TARGET)

# Сборка исполняемого файла
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

# Компиляция объектных файлов
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Создание директорий
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Очистка
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Запуск программы
run: $(TARGET)
	./$(TARGET)

# Отладка
debug: CFLAGS += -g
debug: clean all

# Проверка стиля кода
check:
	cppcheck --enable=all --suppress=missingIncludeSystem $(SRC_DIR) $(INCLUDE_DIR)

.PHONY: all clean run debug check
