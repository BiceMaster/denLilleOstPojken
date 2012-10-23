#===============================================================================
# Project settings
#===============================================================================
# Name of out file
outFile = CoreLib

# Compiler flags when compiling objects
cFlags = -c

# Linker flags used when linking binary
lFlags =

# Link when compiling is done. This should not be done for "libraries". "link" 
# should be set to 'true' or 'false'. Everything other than 'true' results in 
# the project not being linked.
link = false

#===============================================================================
# Project dependencies
#===============================================================================
# Space separated list of directories to projects that this project depends on. 
projectPaths = ../CommonLib


#===============================================================================
# Libraries
#===============================================================================
# Space separated list of directories where libs that the project uses reside. 
# This list is ONLY for linux libs. Correspodning header files are added to
# 'libIncludePaths'.
_libPaths =  external/SFML/lib/
libIncludePaths = external/SFML/include/

# Specify the file names of the libs that should be used when compiling.
# The file MUST be prefixed with 'lib' and suffiex with '.a'
__libs = libsfml-audio.so.1.6

include ../solutionSettings.mk
include ../compileAndLink.mk

