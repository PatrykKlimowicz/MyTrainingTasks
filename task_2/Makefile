OBJDIR := tmp
SRCDIR := static_bin
LIBDIR := static_lib
TARGET := my_app

SOURCES := app.c gen_num.c
OBJECTS := $(addprefix $(OBJDIR)/,$(SOURCES:.c=.o))
STATLIB := $(addprefix $(LIBDIR)/,libstatic.a)

CC=gcc
CFLAGS=-g -Wall

$(SRCDIR)/$(TARGET): $(OBJECTS) $(STATLIB)
	$(CC) $(CFLAGS) $(OBJDIR)/app.o $(STATLIB) -o $@

$(OBJDIR)/%.o: %.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<

$(OBJECTS): | $(OBJDIR)
$(SOURCES): | $(SRCDIR)

$(STATLIB): $(OBJDIR)/gen_num.o | $(LIBDIR)
	ar rsc $@ $^

$(OBJDIR):
	mkdir $(OBJDIR)

$(SRCDIR):
	mkdir $(SRCDIR)

$(LIBDIR):
	mkdir $(LIBDIR)

clean:
	rm -rf $(OBJDIR) $(LIBDIR) $(SRCDIR)