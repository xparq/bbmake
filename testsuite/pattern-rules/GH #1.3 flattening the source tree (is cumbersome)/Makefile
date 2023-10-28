#
# For flat-tree use cases, where source tree subdirs are not mirrored by the
# outputs, with the current limited support:
# - separate rules (and .SUFFIXES entries) are needed,
# - it can only compile into the current dir!
#
# Note: for builds mirroring the source tree in the output with an offset
# path prefix, the current support is already enough; see "*dual-tree build"!
#

.SUFFIXES: .c src/%.c src/sub/%.c

# Note how 'sub.o' is neeed in this setup, not 'sub/sub.o'
test: along.o main.o sub.o # Alas, no support for $(OUT)/stuff.o; see GH #2 for that!
	$(CC) $^ -o $@

.c.o:
	@echo "NORMAL: $< -> $@"
	$(CC) -c $<

src/%.c.o:
	@echo "YAY, path controlled inf. rule!!! $< -> $@"
	$(CC) -c $< -o `basename $@`

src/sub/%.c.o:
	@echo "No real patterns yet, but NMAKE-style rigid, fixed paths for each dir..."
	$(CC) -c $< -o `basename $@`
