CC = gcc
CFLAGS = -Wall -g

SRC_DIR = .
OBJ_DIR ?= ../out/obj
BIN_DIR ?= ../out/bin

TARGET = $(BIN_DIR)/driver
DRIVER_OBJS = $(OBJ_DIR)/driver.o $(OBJ_DIR)/rbtree.o

# 오브젝트 생성 규칙
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# 실행 파일 빌드
$(TARGET): $(DRIVER_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

all: $(TARGET)

clean:
	rm -f $(OBJ_DIR)/driver.o $(OBJ_DIR)/rbtree.o $(TARGET)
