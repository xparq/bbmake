# There's one quirk with this: while the user is made to forget the actual
# build happens in $(OUT), make will still report "../test is up-to-date",
# so "the abstraction still leaks"...

SRC = src
OUT = out
PROGRAM = test

build:
	-@test -d $(OUT) || mkdir $(OUT)
	@$(MAKE) -C $(OUT) -f ../Makefile PROGRAM=../$(PROGRAM) OUT=. SRC=../$(SRC) ../$(PROGRAM)

$(PROGRAM): $(OUT)/main.o $(OUT)/sub/sub.o
	$(CC) $^ -o $@
	@echo All done.

$(SRC)/%.c.o:
	@echo "$< -> $@"
	@mkdir -p `dirname $@`
	$(CC) -c $< -o $@
