# Generated automatically from Makefile.in by configure.
DEP_DIR    := .dep
OBJDIR     := obj
BINDIR     := ../bin

EFILE      := nportredird
INCLUDES   := -I./include
SHELL      := /bin/sh
CFLAGS     := $(INCLUDES)  -I/usr/include
VERSION    := 0.6
CC         := gcc
DEFS       := -DHAVE_CONFIG_H
LIBS       := -lpthread -lnsl 
LDFLAGS    :=	
INSTALL    := /usr/bin/install -c
prefix     := /usr/local
exec_prefix := ${prefix}
SBIN_DIR    := ${exec_prefix}/sbin
MAN_DIR     := ${prefix}/man
ETC_DIR     := ${prefix}/etc
VAR_DIR     := ${prefix}/var

STRIP      := -s
YACC	      := bison -y
LEX        := lex
YACCFLAGS  := -d
LEXFLAGS  :=

vpath %.h include

DSOURCE      := configparse.c
DOBJECTS	 := $(OBJDIR)/configparse.o

SOURCES      := $(wildcard *.c)
OBJECTS      := $(patsubst %.c,$(OBJDIR)/%.o,$(SOURCES))
DEP_FILES    := $(patsubst %.c,$(DEP_DIR)/%.d,$(SOURCES))

SOURCES		 := $(SOURCES) $(DSOURCE)
OBJECTS		 := $(OBJECTS) $(DOBJECTS)
#
# Cancel built-in implicit rule for %.o
#
%.o : %.c

#
#Redifine the implicit rule fo %.o
#
$(OBJDIR)/%.o : %.c
	$(CC) -c $(CFLAGS) $(DEFS) $< -o $@


.PHONY: all
all : whatsup version $(EFILE)


$(EFILE): $(OBJECTS)
	@echo
	@echo " Linking object files..."
	@echo
	$(CC)  $(LDFLAGS) $^ -o $(BINDIR)/$(EFILE) $(LIBS)


include $(DEP_FILES)


.PHONY: whatsup
whatsup:
	@echo
	@echo " `date '+ %A, %d %B %Y'`"
	@echo " Generating object files for $(EFILE) $(VERSION)..."
	@echo
	@if [ -r configparse.y ]; then \
		$(YACC) $(YACCFLAGS) -o configparse.c configparse.y; \
		cd include; ln -sf ../configparse.h .; \
		cd ..; \
	else \
		echo "Missing grammar file..."; \
		exit; \
	fi

$(DEP_DIR)/%.d: %.c
	$(SHELL) -ec '$(CC) -M $(CFLAGS) $< \
       | sed '\''s/\($*\)\.o[ :]*/$(OBJDIR)\/\1.o $(@D)\/$(@F) : /g'\'' > $@; \
       [ -s $@ ] || rm -f $@'


.PHONY: version
version:
	@chmod 755 version.c.in; ./version.c.in


.PHONY: tags
tags:
	@echo "Updating tags file..."
	@ctags --recurse=yes --sort=yes *.[ch]

.PHONY: clean
clean:
	rm -rf obj/*.o
	rm -rf .dep/*.d
	rm -rf ../bin/*
	rm -rf core *.core *.a *.so
