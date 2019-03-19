EXEC := berimbau-tool

CC := g++
CP := cp
MK := mkdir
RM := rm

SRCDIR := src
BUILDDIR := build
EXECDIR := bin

TARGET := $(EXECDIR)/$(EXEC)

SRCEXT := cpp
SOURCES := $(wildcard $(SRCDIR)/*.$(SRCEXT))
OBJECTS := $(addprefix $(BUILDDIR)/,$(notdir $(SOURCES:.$(SRCEXT)=.o)))
CFLAGS := -g -Wall -std=c++17
LDFLAGS := -lstdc++fs
INCLUDES := -I./$(SRCDIR)/include -std=c++17

all: $(TARGET)

buildrun: all
	./$(TARGET)

run:
	./$(TARGET)

$(TARGET): $(OBJECTS)
	@echo "Linking..."
	@$(MK) -p $(EXECDIR)
	$(CC) $^ -o $(TARGET) $(LDFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo "Compiling $<"
	@$(MK) -p $(BUILDDIR)
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDES)

clean:
	@echo "Cleaning..."
	@$(RM) -rf $(BUILDDIR) $(EXECDIR) $(SHAREDIR)

.PHONY: clean