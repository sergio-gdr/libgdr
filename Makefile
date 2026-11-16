# support out-of-source build
MAKEFILE_DIR := $(dir $(MAKEFILE_LIST))

TESTSRC := $(wildcard $(MAKEFILE_DIR)tests/*.c)
TESTEXE := $(patsubst %.c,%,$(notdir $(TESTSRC)))
INCLUDES := $(MAKEFILE_DIR)include

check: run_tests

run_tests: $(TESTEXE)
	@for test in $(TESTEXE); do \
		./"$$test"; \
	done

%: $(MAKEFILE_DIR)/tests/%.c
	@gcc -I$(INCLUDES) -g -std=c23 $(CFLAGS) $(CPPFLAGS) -o $@ $<

clean:
	@rm -rf $(TESTEXE)

.PHONY: check run_tests clean
.SUFFIXES:
