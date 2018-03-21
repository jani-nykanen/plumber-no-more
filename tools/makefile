SRCDIR := "."
OBJDIR := "./obj"

SRCS := bmpconv.c
OBJ_FILES := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
LD_FLAGS := -lSDL2 -lSDL2_image
CC_FLAGS := -Wall

bmpconv: $(OBJ_FILES)
	 gcc $(CC_FLAGS) -o $@ $^ $(LD_FLAGS)

