CC      := gcc
CFLAGS  := -std=c11 -Wall -Wextra -O2 -Iinclude
LDFLAGS :=
SRC     := $(wildcard src/*.c)
OUTDIR  := build
OUT     := $(OUTDIR)/server

.PHONY: all run clean

all: $(OUT)

$(OUT): $(SRC) | $(OUTDIR)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

$(OUTDIR):
	mkdir -p $(OUTDIR)

run: $(OUT)
	./$(OUT)

clean:
	rm -rf $(OUTDIR)

