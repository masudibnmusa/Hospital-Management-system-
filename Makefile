# Hospital Management System Makefile
# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic
DEBUG_FLAGS = -g -DDEBUG
RELEASE_FLAGS = -O2
LIBS =

# Targets
TARGET = hospital_management
SOURCES = hospital_management.c
OBJECTS = $(SOURCES:.c=.o)

# Default build (debug)
all: $(TARGET)

# Release build
release: CFLAGS += $(RELEASE_FLAGS)
release: $(TARGET)

# Debug build
debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(TARGET)

# Main executable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)
	@echo "============================================"
	@echo "  Hospital Management System Compiled!"
	@echo "  Run with: ./$(TARGET)"
	@echo "============================================"

# Object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "Object files and executable removed"

# Clean all including data files
distclean: clean
	rm -f patients.dat doctors.dat appointments.dat bills.dat staff.dat Bill_*.txt
	@echo "All generated files removed"

# Install (copy to /usr/local/bin)
install: release
	sudo cp $(TARGET) /usr/local/bin/
	@echo "Installed to /usr/local/bin/$(TARGET)"

# Uninstall
uninstall:
	sudo rm -f /usr/local/bin/$(TARGET)
	@echo "Uninstalled from /usr/local/bin/$(TARGET)"

# Run the application
run: $(TARGET)
	./$(TARGET)

# Debug run
debug-run: debug
	./$(TARGET)

# Create backup of data files
backup:
	mkdir -p backups
	tar -czf backups/backup_$(shell date +%Y%m%d_%H%M%S).tar.gz *.dat Bill_*.txt 2>/dev/null || true
	@echo "Data backup created in backups/ directory"

# Static analysis with cppcheck
analyze:
	cppcheck --enable=all --suppress=missingIncludeSystem $(SOURCES)

# Format code (requires clang-format)
format:
	clang-format -i $(SOURCES)
	@echo "Code formatted"

# Create distribution package
dist: distclean
	mkdir -p dist/hospital_management
	cp $(SOURCES) Makefile README.md dist/hospital_management/
	tar -czf hospital_management_v1.0.tar.gz -C dist hospital_management
	rm -rf dist
	@echo "Distribution package created: hospital_management_v1.0.tar.gz"

# Show help
help:
	@echo "Hospital Management System Makefile Targets:"
	@echo ""
	@echo "  all          - Build with debug symbols (default)"
	@echo "  release      - Build with optimizations"
	@echo "  debug        - Build with debug flags"
	@echo "  clean        - Remove object files and executable"
	@echo "  distclean    - Remove all generated files including data"
	@echo "  install      - Install to /usr/local/bin"
	@echo "  uninstall    - Remove from /usr/local/bin"
	@echo "  run          - Build and run the application"
	@echo "  debug-run    - Build with debug and run"
	@echo "  backup       - Create backup of data files"
	@echo "  analyze      - Run static code analysis"
	@echo "  format       - Format source code (requires clang-format)"
	@echo "  dist         - Create distribution package"
	@echo "  help         - Show this help message"
	@echo ""
	@echo "Examples:"
	@echo "  make release && make run    - Build optimized and run"
	@echo "  make debug-run              - Build debug version and run"
	@echo "  make backup                 - Backup data files"

# Phony targets (not actual files)
.PHONY: all release debug clean distclean install uninstall run debug-run backup analyze format dist help

# Dependency information
hospital_management.o: hospital_management.c
