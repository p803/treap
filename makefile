TARGET ?= tests/main
SRC_DIRS ?= ./src ./tests

SRCS := $(shell find $(SRC_DIRS) -name *.cpp)
OBJS := $(addsuffix .o,$(basename $(SRCS)))
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CC := g++
CPPFLAGS ?= $(INC_FLAGS) -MMD -Wall -O2 -g
LDLIBS :=

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDLIBS)

.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJS) $(DEPS)

-include $(DEPS)
