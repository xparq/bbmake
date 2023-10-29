SRC = ../src
OUT = .
PROGRAM = ../test

$(PROGRAM): $(OUT)/main.o $(OUT)/sub/sub.o
	$(CC) $^ -o $@
	@echo All done.

$(SRC)/%.c.o:
	@echo "$< -> $@"
	@mkdir -p `dirname $@`
	$(CC) -c $< -o $@
