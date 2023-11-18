The OON and szlib examples are working real-life setups for <10k SLOC projects

Both are using basically the same experimental raw pdpmake Makefile, which is
horribly convoluted (in large part due to difficulties regarding header auto-
dependencies with MSVC), but pretty stable and definitely usable.

The goals of putting them here is

a) to have a dedicated reference location for this particular build solution
   (fixes in those projects should propagate back up here, and improvements
   made here should be applied there),

b) and to set a baseline for comparison: bbmake should make both the Makefiles
   and (especially) the procedure significantly simpler, with the help of a
   few carefully selected changes to the original pdpmake.

------------------------------------------------------------------------------
TODO
------------------------------------------------------------------------------

- Make the examples actually build!
- Add the improved bbmake (counter)exmples for comparison!
