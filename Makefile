# project name (generate executable with this name)
TARGET   = myproject

SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin
INCDIR   = include

CC       = g++
LINKER   = g++
# compiling flags here
CFLAGS   = -std=c++11 -Wall -I. -Iinclude/
# linking flags here
LFLAGS   = -Wall -I. 
SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(INCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
rm       = rm -f
all: $(BINDIR)/$(TARGET)
$(BINDIR)/$(TARGET): $(OBJECTS)
	@echo $(LINKER) $(OBJECTS) $(LFLAGS) -o $@
	@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
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
