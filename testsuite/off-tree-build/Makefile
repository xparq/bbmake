.SUFFIXES: .c src/%.c src/sub/%.c

# No pattern- or even fixed-path inference rules in the original;
# only ./along.c and src/main.o could match!

OBJS = along.o main.o sub.o
#!! ... obj/main.o obj/sub/sub.o - No support for the other way around yet...

test: $(OBJS)
	$(CC) $^ -o $@
	@echo All done.

.c.o:
	@echo "NORMAL: $< -> $@"
	$(CC) -c $<

src/%.c.o:
	@echo "YAY, path controlled inf. rule!!! $< -> $@"
	$(CC) -c $< -o $@

src/sub/%.c.o:
	@echo "OK, NMAKE-style rigid, fixed-path rules for each dir yet... $< -> $@"
	$(CC) -c $< -o $@
