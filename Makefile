CC := gcc
TARGET := main.exe
CFLAGS := -Wall -o2
OUT  := out

SRC := $(wildcard *.c)
OBJ := $(patsubst %.c,%.o,$(SRC))

all: help

build: $(TARGET)

$(TARGET): $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $^
	@mkdir -p $(OUT)
	@mv $(OBJ) $(OUT)/
	@mv $@ $(OUT)/

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

run: build
	@./$(OUT)/$(TARGET)

help:
	@echo "build build the project"
	@echo "help for more help"
	@echo "run build and run"
	@echo "clean clean the project"

.PHONY: clean

clean:
	@-rm $(OUT)/*

