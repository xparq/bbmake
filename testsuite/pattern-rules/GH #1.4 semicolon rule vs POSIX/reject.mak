#
# Ahh..., didn't realize earlier, but POSIX mode would actually bail out
# even before recognizing (and rejecting) the one-liner! :)
# (The 'target_name' pragma almost gives it green light, but that % kills it...)
#

.POSIX:
.PRAGMA: target_name

.SUFFIXES: src/%.c

all: dummy.o
	@echo All done.

src/%.c.o:; @echo "$< -> $@"
