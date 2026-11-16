# support out-of-source build
MAKEFILE_DIR := $(dir $(MAKEFILE_LIST))

OBJS := $(dir $(MAKEFILE_DIR))pool/pool.o $(dir $(MAKEFILE_DIR))arena/arena.o

TESTSRCDIR := $(dir $(MAKEFILE_DIR))tests
TESTEXE := $(patsubst %.c,%,$(wildcard $(MAKEFILE_DIR)tests/*.c))
INCLUDES := $(MAKEFILE_DIR)include

all: libgdr.so

libgdr.so: $(OBJS)
	bear -a -- gcc -fPIC -shared -I$(INCLUDES) -g -std=c23 $(CFLAGS) $(CPPFLAGS) -o $(@) $(OBJS)

%.o: %.c
	bear -a -- gcc -c -I$(INCLUDES) -g -std=c23 $(CFLAGS) $(CPPFLAGS) -o $(@) $<

check: all run_tests

run_tests: $(TESTEXE)
	@for test in $(TESTEXE); do \
		LD_LIBRARY_PATH=. "$$test"; \
	done
	@rm -rf $(TESTEXE)

$(TESTSRCDIR)/%: $(TESTSRCDIR)/%.c
	bear -a -- gcc -I$(INCLUDES) -I$(MAKEFILE_DIR) -g -std=c23 $(CFLAGS) $(CPPFLAGS) -o $@ $< -L$(MAKEFILE_DIR) -lgdr

clean:
	@rm -rf $(TESTEXE) libgdr.so $(OBJS)

.PHONY: all check run_tests clean
.SUFFIXES:
