test: main.o
src/%.c.o:
	@echo "YAY, path-aware inf. rules!!! $< -> $@"
