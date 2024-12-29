# Makefile for Hospital Management System

# Compiler
CXX = g++

# Compiler Flags
CXXFLAGS = -Wall -Wextra -std=c++17

# List of source files
SRCS = main.cpp \
       Administrator.cpp \
       Doctor.cpp \
       Patient.cpp \
       PatientManager.cpp \
       Person.cpp \
       PersonManager.cpp \
       Staff.cpp \
       StaffManager.cpp \
       GenerateAccount.cpp

# Generate object file names by replacing .cpp with .o
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = Hospital_Management_System

# Default target
all: $(TARGET)

# Rule to link object files and create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Rule to compile .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target to remove object files and the executable
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets to prevent conflicts with files named 'all' or 'clean'
.PHONY: all clean
