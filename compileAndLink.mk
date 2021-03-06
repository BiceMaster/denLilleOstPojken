#===============================================================================
# Dependecy list processing
#===============================================================================
# Generate lists of objects and corresponding .h-files directories
depObjects = $(foreach dir, $(projectPaths), $(wildcard $(dir)/$(objDir)/*.o))
depIncludePaths = $(addsuffix /$(srcDir),$(projectPaths))

# Add the g++ flag '-I ' before every include path
includePaths=$(addprefix -I , $(depIncludePaths))
includePaths+=$(addprefix -I , $(libIncludePaths))

# Add the g++ flag '-L ' before every library path
libPaths =$(addprefix -L , $(_libPaths))

# The prefix 'lib' and suffix '.a' is removed and the prefix '-l' is be added.
# This is the g++ syntax for linking with static libraries
_libs = $(patsubst lib%.a,%, $(__libs))
libs = $(addprefix -l,$(_libs))


#===============================================================================
# Create lists for this project
#===============================================================================
# Find all cpp files and put them in a list.
sources = $(wildcard $(srcDir)/*.cpp)

# Convert suffix to .o/.d and use to list all corresponding objects files
__objects = $(sources:.cpp=.o)
__deps = $(sources:.cpp=.d)

# Remove dir from file path. File path -> file name
_objects = $(notdir ${__objects})
_deps = $(notdir ${__deps})

# Add Object/Dependency file dir to file name
objects = $(addprefix ${objDir}/, ${_objects})
deps = $(addprefix ${depDir}/, ${_deps})


#===============================================================================
# Build
#===============================================================================

# Build all dependencies
#include $(deps)

all : createDirs $(outFile)
#	g++ -c -o obj/main.o src/main.cpp $(includePaths) 
#	g++ -o bin/main.out obj/main.o $(depObjects) $(libPaths) $(libs)

# Compile all .cpp files to .o files. 
# $< = actual cpp file. $@ .o file, the target file
$(objDir)/%.o : $(srcDir)/%.cpp
	g++ $(cFlags) -o $@ $< $(includePaths) 

# Generate dependencies
# -MF  write the generated dependency rule to a file
# -MG  assume missing headers will be generated and don't stop with an error
# -MM  generate dependency rule for prerequisite, skipping system headers
# -MP  add phony target for each header to prevent errors when header is missing
# -MT  add a target to the generated dependency
$(depDir)/%.d : $(srcDir)/%.cpp
	g++ $(cFlags) -MF"$@" -MG -MM -MP -MT"$@" -MT"$(<:.c=.o)" "$<"

# Compile object files to executable
$(outFile) : $(objects) $(deps)
ifeq ($(link),true)
	g++ $(objects) $(lFlags) -o $(binDir)/$(outFile) $(depObjects) $(libPaths) $(libs)
endif

createDirs :
	mkdir $(masDir) $(objDir) $(binDir) $(depDir)

# Debug info if anything goes wrong
info:
	@echo
	@echo Dependency info:
	@echo =======================================================
	@echo Include Paths: $(includePaths)
	@echo Library Paths: $(libPaths)
	@echo Libraries:     $(libs)
	@echo Dependency folders: $(foreach dir, $(projectPaths), $(dir)/$(objDir))
	@echo Dependencies:  $(depObjects)
	@echo =======================================================
	@echo
	@echo Compile info
	@echo =======================================================
	@echo Sources:       $(sources)
	@echo Objects:       $(objects)
	@echo Dependencies:  $(deps)
	@echo =======================================================

clean : 
	rm -rf $(masDir) $(binDir)
