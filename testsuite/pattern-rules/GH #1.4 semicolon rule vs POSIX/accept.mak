.SUFFIXES: src/%.c

all: dummy.o
	@echo All done.

src/%.c.o:; @echo "$< -> $@"
