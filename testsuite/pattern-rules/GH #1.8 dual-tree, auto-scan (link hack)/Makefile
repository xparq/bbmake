# Note: no "test is up-to-date" printed in this case, because fiddling with
# the tree link still counts as a job to "update" the target...

PROGRAM = test
SRC = src
OUT = out

# --- No edits needed below!

sources != find $(SRC) -name '*.c'
objs = $(sources:$(SRC)/%.c=$(OUT)/%.o)

all: linktree_kludge # See below...

$(PROGRAM): $(objs)
	$(CC) $^ -o $@
	@echo All done.

$(SRC)/%.c.o:
	@echo "$< -> $@"
	@mkdir -p `dirname $@`
	$(CC) -c $< -o $@

# Work around the rigid out/%.o -> src/out/%.c name inference:
linktree_kludge: mk_treelink .WAIT $(PROGRAM) .WAIT rm_treelink
mk_treelink:; @if [ ! -e $(SRC)/$(OUT) ]; then ln -s '.' $(SRC)/$(OUT); fi
rm_treelink:; @if [   -L $(SRC)/$(OUT) ]; then rm        $(SRC)/$(OUT); fi
