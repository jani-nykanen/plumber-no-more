SRCDIR := "."
OBJDIR := "./obj"

SRCS := $(shell find $(SRCDIR) -name "*.c")
OBJ_FILES := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
LD_FLAGS := -lm
CC_FLAGS := -Wall

tmx2bin: $(OBJ_FILES)
	 gcc $(CC_FLAGS) -o $@ $^ $(LD_FLAGS)

