#
# Makefile for Generating C++ executables
#
# F18 CSCI 232 - Data Structures and Algorithms
# Phillip J. Curtiss, Assistant Professor
# Computer Science Department, Montana Tech
# Museum Buildings, Room 105
#
# Specify the Course Below
COURSE = F18 CSCI232 Data Structures and Algorirthms
# Specify the Project Name below
PROJ =	C++ Postfix Evaluation
#
# Project Files Specified Below
##
# Source files should be added to the SRCS variable
SRCS =	postfix-driver.cpp Postfix.cpp PrecondViolatedExcep.cpp LinkedStack.cpp Node.cpp
# Object files will be inferred from soruce files; adjust as needed
OBJS =	$(SRCS:.cpp=.o)
# Dependency files will be inferred from source files; adjust as needed
DEPS =	$(SRCS:.cpp=.dep)
# List all targets this Makefile is to create from source files
TARGET = postfix-driver

###################################################
# Should Not need to modify lines of Makefile below
#
# g++ compiler flags; standard is C++14; level-3 optimization
CXXFLAGS = -std=gnu++14 -O3 -Wall -Werror
# Additional Library Search Paths specified below
LDFLAGS = 
# Additional Libraries to link in with executable below
LDLIBS = 

#
# Provide Make with additionally known suffixes
.SUFFIXES:	.dia .dep

# Default rule to make if no target specified
# (make dependencies first, then all targets)
default: $(DEPS) $(TARGET) 

# Rules to generate targets
# Note: If more than one target, might need multiple rules
#       of the form below
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^

# Make dependency file for each source file
# include all dependency files so Make can 
# conditionally make required project file
%.dep: %.cpp
	$(CXX) -MM $< -o $@
-include $(DEPS)

#
# Clean up Intermediate files and targets
.PHONY: clean doxygen
clean: 
	-$(RM) $(DEPS) $(OBJS) $(TARGET)

#
# Generate Documentation for project files
Doxyfile:
	-doxygen -g
	-sed -r -i 's/(^PROJECT_NAME\s*=).*$$/\1 \"$(COURSE)\"/' $@
	-sed -r -i 's/(^PROJECT_BRIEF\s*=).*$$/\1 \"$(PROJ)\"/' $@
	-sed -r -i 's/(^OUTPUT_DIRECTORY\s*=).*$$/\1 doc/' $@
	-sed -r -i 's/(^GENERATE_TREEVIEW\s*=).*$$/\1 YES/' $@

doxygen: Doxyfile
	-doxygen $^

