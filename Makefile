# support out-of-source build
MAKEFILE_DIR := $(dir $(MAKEFILE_LIST))

TESTSRC := $(wildcard $(MAKEFILE_DIR)tests/*.c)
TESTOBJ := $(patsubst %.c,%.o,$(notdir $(TESTSRC)))
INCLUDES := $(MAKEFILE_DIR)include

check: run_tests

run_tests: $(TESTOBJ)
	gcc -g -o run_tests $(TESTOBJ)
	./run_tests

%.o: $(TESTSRC)
	gcc -I$(INCLUDES) -g -std=c23 -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

clean:
	@rm -rf $(TESTOBJ) run_tests

.PHONY: check run_tests clean
.SUFFIXES:
