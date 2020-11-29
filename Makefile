# Compiler info
CC        := gcc
CFLAGS    := -Wextra -Werror -std=c11
LDLIBS    := -lm
IFLAGS    := -I.

# make info
TARGET    := exe
SOURCES   := $(wildcard *.c)
OBJECTS   := $(patsubst %.c, %.o, $(SOURCES))

.PHONY: all run clean clean_dep

all: $(TARGET) clean clean_dep

# Dependency files info
DEPS = $(patsubst %.o, %.d, $(OBJECTS))
-include $(DEPS)
DFLAGS    = -MMD -MF $(@:.o=.d)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(IFLAGS) $^ -o $@ $(LDLIBS)

%.o: %.c
	$(CC) -c $(CFLAGS) $(IFLAGS) $< -o $@ $(DFLAGS)

run:
	@$(TARGET)

clean:
	rm -f *.o

clean_dep:
	rm -f *.d
