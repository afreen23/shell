CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -Wpedantic

SRC_DIR = src
OBJ_DIR = obj

# Create the 'obj' directory if it doesn't exist
$(shell mkdir -p $(OBJ_DIR))

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

TARGET = shell

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

.PHONY: clean

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)
