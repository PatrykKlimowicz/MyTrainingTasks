CC=gcc
CFLAGS=-g -Wall

OBJDIR := tmp
SRCDIR := shared

LIBSRC := gen_num.c
APPSRC := app.c

TARGET := $(addprefix $(SRCDIR)/,my-app)
LIBOBJ := $(addprefix $(OBJDIR)/,$(LIBSRC:.c=.o))
APPOBJ := $(addprefix $(OBJDIR)/,$(APPSRC:.c=.o))

PREFIX := lib
LIBNAME := dynamic
EXTENSION := .so
ABSPATH := $(HOME)/c_training/task_3/$(SRCDIR)/


$(TARGET): $(APPOBJ) $(LIBNAME)
	$(CC) $(CFLAGS) -L$(ABSPATH) -Wl,-rpath=$(ABSPATH) $< -l$(LIBNAME) -o $@

$(SRCDIR):
	mkdir $(SRCDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

$(APPOBJ): $(APPSRC) | $(OBJDIR)
	$(CC) -c $(APPSRC) -o $@

$(LIBNAME): $(LIBOBJ) | $(SRCDIR)
	$(CC) -shared -fpic $^ -o $(SRCDIR)/$(PREFIX)$@$(EXTENSION)

$(LIBOBJ): $(LIBSRC)
	$(CC) -c -fpic $^ -o $@

clean:
	rm -rf $(OBJDIR) $(SRCDIR)
