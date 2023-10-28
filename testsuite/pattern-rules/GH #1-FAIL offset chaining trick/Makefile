.SUFFIXES: src/%.c src/o/%.c

test: o/main.o o/sub/sub.o
	$(CC) $^ -o $@
	@echo All done.

src/%.c.o:
	@echo "Virtual rule, for chaining (NOOP): $< -> $@"

# Alas, no way to separate the two "suffixes" with the current mechanics.
src/o/%.c>src/%.c:
	@echo "Chained proxy rule...: $< -> $@"
	$(CC) -c $< -o o/$(@:.c=.o)
