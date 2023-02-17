.PHONY: all run gdb clean latest $(ALL)

RESULT = .result
$(shell > $(RESULT))

COLOR_RED   = \033[1;31m
COLOR_GREEN = \033[1;32m
COLOR_NONE  = \033[0m

ALL = $(basename $(notdir $(shell find tests/. -name "*.c")))

# add to understand
# use "make run", print all .c file under tests, use "make ALL=xxx run" will just print xxx
# $(error $(ALL))

all: $(addprefix Makefile., $(ALL))
	@echo "" $(ALL)

# $(shell echo "" $(ALL))

$(ALL): %: Makefile.%

# $(error $(ALL))

# remove Makefile!!!
# Make will set the special variable MAKECMDGOALS to the list of goals you specified
# on the command line.
Makefile.%: tests/%.c latest
	@echo $<
	@/bin/echo -e "NAME = $*\nSRCS = $<\nLIBS += klib\ninclude $${AM_HOME}/Makefile" > $@
# @if make -s -f $@ ARCH=$(ARCH) $(MAKECMDGOALS); then
	@if make -f $@ ARCH=$(ARCH) $(MAKECMDGOALS); then \
		printf "[%14s] $(COLOR_GREEN)PASS!$(COLOR_NONE)\n" $* >> $(RESULT); \
	else \
		printf "[%14s] $(COLOR_RED)FAIL!$(COLOR_NONE)\n" $* >> $(RESULT); \
	fi
# -@rm -f Makefile.$*

run: all
	@cat $(RESULT)
	@rm $(RESULT)

gdb: all

clean:
	rm -rf Makefile.* build/

latest:
