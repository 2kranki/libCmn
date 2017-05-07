# vim: ts=8 sw=8 sts=0 ai noexpandtab filetype=make

# Taken from http://make.mad-scientist.net/papers/multi-architecture-builds/

# This forces all (well, almost all) the builtin rules to be removed.
.SUFFIXES:

# This section calculates the value of $(OBJDIR). Here, a variable _ARCH is
# initialized to the output of a shell script print_arch. That’s just some
# script you can knock o" that uses uname or whatever is handy to determine
# what type of system you’re running on, then formats it into a simple string
# (suitable for a directory name–no spaces, etc.) and echos it.
ifndef _ARCH
_ARCH := $(shell print_arch)
export _ARCH
endif

# This section calculates the value of $(OBJDIR).
OBJDIR := _$(_ARCH)

# This is merely a shorthand variable containing the actual make command invoked
# to build in the target directory. Briefly, --no-print-directory is used to hide
# the fact that we’re jumping to the target directory; -C $@ is used to run the 
# sub-make in the tar- get directory; -f $(CURDIR)/Makefile tells the sub-make 
# where to find the makefile (remember that when we invoke this we’re in the 
# source directory, so $(CURDIR) is the source directory); SRCDIR=$(CURDIR) 
# overrides the value of SRCDIR in the sub-make to point to the source directory;
# and finally $(MAKECMDGOALS) invokes the sub-make with all the goals the original
# make was invoked with.
MAKETARGET = $(MAKE) --no-print-directory -C $@ -f $(CURDIR)/Makefile \
				SRCDIR=$(CURDIR) $(MAKECMDGOALS)

# These execute the makefile from the destination directory making it if needed.
.PHONY: $(OBJDIR)

$(OBJDIR):
	;+@[ -d $@ ] || mkdir -p $@
	+@$(MAKETARGET)


# Without these lines, then, make will attempt to rebuild the makefiles using
# the match-anything rule, invoking itself recursively in the target directory! 
Makefile : ;
%.mk :: ;


# When make is invoked, either without any targets (and the all: rule is chosen)
# or with some targets on the command line, it will look for a rule to build that
# target.

# The pattern, just %, will match any target make wants to build. We use the special
# double-colon (::) separator to specify that this is a terminating “match anything”
# rule; this improves efficiency. The “match anything” rule depends on the $(OBJDIR)
# rule. That means that any target will first build the $(OBJDIR) target, which will
# cause the sub-make to be invoked in the target directory. Once make builds the
# $(OBJDIR) target once, it “knows” that target has been updated and won’t try to
# build it again for this invocation. Since the $(OBJDIR) target invokes the sub-make
# with all the command line goals, in $(MAKECMDGOALS), that one invocation is enough
# to build all the targets the user asked for.

% :: $(OBJDIR) ; :

# 
.PHONY: clean

clean:
	rm -rf $(OBJDIR)








