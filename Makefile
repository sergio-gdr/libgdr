CC := gcc
CFLAGS +=
COMPILE_COMMAND := bear -a
SANITIZERS := -fsanitize=address -fsanitize=undefined

# support out-of-source build
MAKEFILE_DIR := $(dir $(MAKEFILE_LIST))

OBJS := $(dir $(MAKEFILE_DIR))pool/pool.o $(dir $(MAKEFILE_DIR))arena/arena.o
HEADERS := $(patsubst %.o,%.h,$(OBJS))
INCLUDE_DIR := $(MAKEFILE_DIR)include
INCLUDES := $(INCLUDE_DIR)/*.h

TESTS_DIR := $(dir $(MAKEFILE_DIR))tests
TESTS := $(patsubst %.c,%,$(wildcard $(TESTS_DIR)/*.c))

all: libgdr.so

libgdr.so: $(OBJS) $(HEADERS) $(INCLUDES)
	$(COMPILE_COMMAND) -- $(CC) $(SANITIZERS) -fPIC -shared -I$(INCLUDE_DIR) -g -std=c23 $(CFLAGS) -o $(@) $(OBJS)

%.o: %.c
	$(COMPILE_COMMAND) -- $(CC) $(SANITIZERS) -c -I$(INCLUDE_DIR) -g -std=c23 $(CFLAGS) -o $(@) $<

check: all run_tests

run_tests: tests
	@for test in $(TESTS); do \
		LD_LIBRARY_PATH=. "$$test"; \
	done
	@rm -rf $(TESTS)

tests: all $(TESTS)

$(TESTS_DIR)/%: $(TESTS_DIR)/%.c $(TESTS_DIR)/%.c $(HEADERS) $(INCLUDES)
	$(COMPILE_COMMAND) -- $(CC) $(SANITIZERS) -I$(INCLUDE_DIR) -I$(MAKEFILE_DIR) -g -std=c23 $(CFLAGS) -o $@ $< -L$(MAKEFILE_DIR) -lgdr

clean:
	@rm -rf $(TESTS) libgdr.so $(OBJS)

.PHONY: all check run_tests clean tests
.SUFFIXES:
