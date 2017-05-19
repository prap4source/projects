# Makefile for c and cpp code compilation in directory structure
OBJDIR   = obj
BINDIR   = bin
#Based on cc type compile c or c++
ifeq ($(CC),gcc)
	INCDIR   = include_c
	SRCDIR   = src_c
	TARGET=cproject
	EXT=c
	LINKER=gcc
	override CFLAGS+= -I . --std=gnu99
	override LFLAGS+= -g -lcrypto
else
	SRCDIR   = src_cpp
	INCDIR   = include_cpp
	TARGET=cppproject
	CC=g++
	LINKER=g++
	EXT=cpp
	override CFLAGS+=-std=c++1y -I.
	override LFLAGS+= -Wall -I. 
endif

SOURCES  := $(wildcard $(SRCDIR)/*.$(EXT))
INCLUDES := $(wildcard $(INCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.$(EXT)=$(OBJDIR)/%.o)
override CFLAGS += -I$(INCDIR)/
rm       = rm -f
all: $(BINDIR)/$(TARGET)
$(BINDIR)/$(TARGET): $(OBJECTS)
	@echo $(LINKER) $(OBJECTS) $(LFLAGS) -o $@
	@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.$(EXT)
	@echo $(CC) $(CFLAGS) -c $< -o $@
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"
.PHONY: destroy
destroy: 
	@$(rm) $(BINDIR)/*
	@$(rm) $(OBJDIR)/*
	@echo "Everything removed!"
