test: along.o main.o
	$(CC) $^ -o $@
	@echo All done.

.c.o:
	@echo "NORMAL: $< -> $@"
	$(CC) -c $<

src/%.c.o:
	@echo "YAY, path-controlled inf. rules!!! $< -> $@"
	$(CC) -c $< -o `basename $@`
