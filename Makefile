#===== User defined variables =====#

DIR_SRC:=src/
DIR_INC:=include/
DIR_OBJ:=build/
# Source, header and object files directories.
# The object files directory also serves for dependency files.
# All directories must end with a slash ("/") or else the makefile won't work !

CC:=g++
EXT:=cpp
TARGET:=MyDB
# The target executable file.

COMMONFLAGS:=-Wall -Wextra -O2
CFLAGS=$(COMMONFLAGS) -std=c11
CXXFLAGS=$(COMMONFLAGS) -std=c++11
# Flags added to the compilation.
COMMONLIBS:=
WIN32LIBS:=$(COMMONLIBS)
LINUXLIBS:=$(COMMONLIBS)
# Libraries needed to link the TARGET executable, for windows and for linux.

#===== Functions =====#

# All directories used in the functions must end with a slash ("/") or else they won't work !

search-dir=$(filter-out $1,$(dir $(wildcard $1*/)))
# Returns the list of subdirectories in Arg1 directory.
search-dir-all=$(strip $(call search-dir,$1) $(foreach DIR,$(call search-dir,$1),$(call search-dir-all,$(DIR))))
# Returns the list of directories and subdirectories in Arg1.
search-file=$(foreach DIR,$1,$(wildcard $(DIR)*.$(EXT)))
# Returns the list of files in Arg1 directories and their subdirectories.

#===== Variables =====#

DIR_SRC_ALL:=$(DIR_SRC) $(call search-dir-all,$(DIR_SRC))
DIR_INC_ALL:=$(DIR_INC) $(call search-dir-all,$(DIR_INC))
# List of all directories and subdirectories that can contain source and header files.
SRC:=$(notdir $(call search-file,$(DIR_SRC_ALL)))
# List of all source files in the main source directory and its subdirectories.
OBJ:=$(SRC:.$(EXT)=.o)
# List of all object files.
I_SRC:=$(addprefix -I,$(DIR_SRC_ALL))
I_INC:=$(addprefix -I,$(DIR_INC_ALL))
# The list of all -I for finding source and header files during the compilation.

VPATH:=$(DIR_SRC_ALL) $(DIR_OBJ)
# The VPATH variable contains all the source, header, object and dependency files directories.
# This is the variable Make uses to know where the targets and prerequisites are.

COMMONFLAGS+=$(I_SRC) $(I_INC) -MMD
# The flags the compiler needs to know where the source and header files are (I_SRC and I_INC).
# It compiles source files with the -MMD option that creates dependency files.

ifeq ($(OS),Windows_NT)
	LIBS:=$(WIN32LIBS)
	AND:=&
	CLEAR:=cls
	MOVE:=cmd /c move
	CLEAN:=cmd /c del /q
	OBJ_DEP:=$(DIR_OBJ:%/=%)
else
	LIBS:=$(LINUXLIBS)
	AND:=;
	CLEAR:=clear
	MOVE:=mv
	CLEAN:=rm
	OBJ_DEP:=$(DIR_OBJ)*
endif
# All these variables contain OS dependent information :
# LIBS is the list of linking flags.
# AND is the character that allows two commands to be written on one line.
# CLEAR is the command that clears the console.
# MOVE is the command used to move files from a directory to another.
# CLEAN is the command used to delete files.
# OBJ_DEP is what needs to be deleted during cleaning operations : object and dependency files.

#===== Rules =====#

.PHONY:all init clear %-depend clean

$(TARGET):$(OBJ)
	-@$(MOVE) *.o $(DIR_OBJ)
	-@$(MOVE) *.d $(DIR_OBJ)
	$(CC) $(addprefix $(DIR_OBJ),$(OBJ)) $(LIBS) -o $(TARGET)
# The main rule of the makefile : the compilation of TARGET.
# The new object and dependency files are moved in the object directory.

init:
	-@mkdir $(DIR_SRC) $(DIR_INC) $(DIR_OBJ)
	@echo Project created in the current directory

%-depend:
	-@cd obj $(AND) $(CLEAN) $(*F).o $(AND) $(CLEAN) $(*F).d
	@echo $(*F).$(EXT) dependencies will be rebuilt with next compilation.
# Deletes dependency file so it is rebuilt with next compilation.
# This rule is made to be manually called if a source file was moved from one directory to another.

clean:
	-@$(CLEAN) $(OBJ_DEP) $(TARGET)
	@echo Object directory purged and $(TARGET) deleted !
# Purges the object files directory from object and dependency files, and deletes TARGET.

-include $(DIR_OBJ)*.d
# Inclusion of all dependency files, which contains all the dependency information for creating object files.