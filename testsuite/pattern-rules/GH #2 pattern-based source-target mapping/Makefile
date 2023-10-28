.SUFFIXES: src/%.c src/sub/%.c

# No pattern- or even fixed-path inference rules in the original;
# only ./along.c and src/main.o could match!

test.exe: o/main.o o/sub/sub.o
	$(CC) $^ -o $@
	@echo All done.

src/%.c.o:
	@echo "$< -> $@"
	$(CC) -c $< -o $@

#c/sub/%.c.o:
#	@echo "Sub: $< -> $@"
#	$(CC) -c $< -o $@
