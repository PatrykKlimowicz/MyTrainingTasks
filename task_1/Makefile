OBJDIR := tmp
SRCDIR := bin
TARGET := my_app

SOURCES := app.c gen_num.c
OBJECTS := $(addprefix $(OBJDIR)/,$(SOURCES:.c=.o))

CC=gcc
CFLAGS=-g -Wall

$(SRCDIR)/$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@

$(OBJDIR)/%.o: %.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<

$(OBJECTS): | $(OBJDIR)
$(SOURCES): | $(SRCDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

$(SRCDIR):
	mkdir $(SRCDIR)
clean:
	rm -f $(OBJDIR)/*.o $(SRCDIR)/*