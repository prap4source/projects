# project name (generate executable with this name)

SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin
INCDIR   = include
#Based on cc type compile c or c++
ifeq ($(CC),gcc)
	TARGET=cproject
	EXT=c
	LINKER=gcc
	CFLAGS=
	LFLAGS=
else
	TARGET=cppproject
	CC=g++
	LINKER=g++
	EXT=cpp
	CFLAGS=-std=c++11 -Wall -I. -Iinclude/
	LFLAGS   = -Wall -I. 
endif

SOURCES  := $(wildcard $(SRCDIR)/*.$(EXT))
INCLUDES := $(wildcard $(INCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.$(EXT)=$(OBJDIR)/%.o)
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
