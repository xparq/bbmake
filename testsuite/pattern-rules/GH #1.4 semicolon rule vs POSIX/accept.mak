all: dummy.o
	@echo All done.

src/%.c.o:; @echo "$< -> $@"
