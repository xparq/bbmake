SRC = src.d
OUT = out.d
PROGRAM = test

.SUFFIXES: $(SRC)/%.c

all: linktree_kludge

test: $(OUT)/main.o $(OUT)/sub/sub.o
	$(CC) $^ -o $@
	@echo All done.

$(SRC)/%.c.o:
	@echo "$< -> $@"
	@mkdir -p `dirname $@`
	$(CC) -c $< -o $@

# Work around the rigid out/%.obj -> src/out/%.c path mapping in inf. rules:
linktree_kludge: mk_treelink .WAIT $(PROGRAM) .WAIT rm_treelink
mk_treelink:; @if [ ! -e $(SRC)/$(OUT) ]; then ln -s '.' $(SRC)/$(OUT); fi
rm_treelink:; @if [   -L $(SRC)/$(OUT) ]; then rm        $(SRC)/$(OUT); fi
