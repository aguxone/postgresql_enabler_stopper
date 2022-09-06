# help from this link https://moritzmolch.com/blog/2510.html

# variables of makefile https://www.gnu.org/software/make/manual/html_node/File-Name-Functions.html

# special variables: https://stackoverflow.com/questions/3220277/what-do-the-makefile-symbols-and-mean

# compiling resources: https://www.allegro.cc/forums/thread/282289/282289


# We give a name to the output first, it'll be the name of the folder plus _static.
# Source code will name of the folder plus _main.cpp
OUTPUT = $(notdir $(CURDIR))_dyn
SOURCE= $(notdir $(CURDIR))_main.cpp

# If we want to print something we can use $(info what_we_want_to_print)
# $(info ${OUTPUT})

# CXXPREFIX=i686-w64-mingw32-
# This is like version of our gcc but is not necessary, it would go just before
# the g++
CXXPREFIX=x86_64-w64-mingw32- 
# Other flags that do nothing are -Os -g -mthreads
CXXFLAGS=-s -mthreads
CXXINCLUDES=-I../../librerias_cpp/wx3_2_0/include -I../../librerias_cpp/wx3_2_0/lib_release_dynamic/mswu
# CXXINCLUDES=-I../include -I../lib/Win32/Debug/mswud
# CXXLIBS=-L../lib/Win32/Debug  -lwxmsw31ud_core -lwxbase31ud
# -libwxmsw32ud_core -libwxbase32ud
CXXLIBS=-L../../librerias_cpp/wx3_2_0/lib_release_dynamic -lwxmsw32u_core -lwxbase32u 

##### Resources ##################################################
## Only to include manifest directly in this makefile ##
# RESDEFFLAGS = -DwxUSE_DPI_AWARE_MANIFEST=2 ## It need the define statement WHEN COMPILING
## THE RESOURCE, the resource.o gets compiled with using these variable to include the
## adequate manifest. If we define wxUSE_DPI... on the main.cpp or try to define the varible after compiling the resource it will do nothing because the correct manifest
## is included in resource.o . So the it is a parameter for windres!
RESINCLUDES = -I../../librerias_cpp/wx3_2_0/include
# RES1= ../../librerias_cpp/wx3_2_0/include/wx/msw/wx.rc
RES1= ./resources/resources.rc
#################################################################

#### Compilation ########################################

all: rsrc1.o ${OUTPUT} clean

# rsrc1.o: ${RES1}
# 	windres ${RESDEFFLAGS} ${RESINCLUDES} -o rsrc1.o ${RES1}

rsrc1.o: ${RES1}
	windres ${RESDEFFLAGS} ${RESINCLUDES} -o rsrc1.o ${RES1}

${OUTPUT}: ${SOURCE} rsrc1.o
	g++ ${CXXFLAGS} ${CXXINCLUDES} -o $@ $^ ${CXXLIBS} ${STATICWXLIBS} ${WXWINDEPLIBS}
## Note: $@ means that it will use the "target" variable, so the
## thing at the left of the rule. $^ means all the "prerequisites"
## meaning all the things the left of the rule.
## $< means only the first preriquisite.

clean:
# 	rm "${OUTPUT}" ## rm is for bash console only for linux
	del rsrc1.o # for windows
# 	del rsrc2.o

### How to compile??
### windres and g++ compiles the same way.
## g++ (ALL the flags and includes) -o (file to create like .exe or .o) (source files to compile from like .cpp or .rc) (all the lib directories that for some reason goes AT THE END)

## DEFAULTS: g++ will compile a .exe on windows, and windres will make a .o so in theory it is not necessary to add the add the file
## extension but it can be added.

## To compile multiple things with windred and/or g++ we need to
## define on a "rule" that is the first statement called "all" in
## the order wan like "all: resource.o file.exe"