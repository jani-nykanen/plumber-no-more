SRCDIR := "."
OBJDIR := "./obj"

SRCS := png2bin.c
OBJ_FILES := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
LD_FLAGS := -lSDL2 -lSDL2_image
CC_FLAGS := -Wall

png2bin: $(OBJ_FILES)
	 gcc $(CC_FLAGS) -o $@ $^ $(LD_FLAGS)

