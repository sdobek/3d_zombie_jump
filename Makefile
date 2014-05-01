#-----------------------------------------------------------------------
# BEWARE: THIS HAS NOT YET BEEN TESTED!
#-----------------------------------------------------------------------
#  Look for "--->" for things that you need to change for your
#  particular configuration.
#-----------------------------------------------------------------------
#  This simple Makefile which compiles a single C++ program, in the
#  source file $TARGET.cpp (where the variable TARGET is set below)
#  assuming a Unix system for OpenGL, GLUT, and X-windows.  The directories
#  for OpenGL and GLUT will need to be changed depending on your system.
#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
# ---> INSERT THE NAME OF YOUR SOURCE FILE HERE
#-----------------------------------------------------------------------

TARGET = Smurfs

#-----------------------------------------------------------------------
#  Variable settings: Set these according to your system configuration
#
#  Compiler/Linker settings:
#  -------------------------
#	C++		Your favorite C++ compiler (or C compiler).
#	CFLAGS		Your compilation flags.
#	    -g		    compile for debugging (e.g., dbx or gdb).
#	    -O2/O3	    optimize code for speed
#	    -Wall	    give all warnings (highly recommended with
#			    OpenGL programs)
#	MISC_LIBS	Any miscellaneous libraries that your program
#			needs.
#			    add -lm here for math library
#			    add -lposix4 here for clock_gettime()
#			    (a real-time clock on Solaris machines).
#
#
#  System/Platform-dependent settings (which you will need to set):
#  ----------------------------------------------------------------
#	OGL_DIR		Directory where OpenGL (or Mesa) resides
#	OGL_LIBS	OpenGL library names
#	X_LIB		X11 lib directory (where libX11, libXext live)
#
#  System/Platform-dependent settings (you should not need to set):
#  ----------------------------------------------------------------
#	OGL_LIB_DIR	OpenGL library directory (where libGL lives)
#	OGL_INC_DIR	OpenGL linclude directory (where GL/gl.h lives)
#	OGL_LFLAGS	Loader flags for OpenGL stuff
#	X_LFLAGS	Loader flags for X11 stuff
#	LD_FLAGS	All loader flags
#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
# ---> USE THESE DEFINITIONS FOR CSIC Linux Cluster Machines
#-----------------------------------------------------------------------
OGL_DIR = /usr
OGL_LIBS =  -lGLU -lGL -lglut
X_LIB = /usr/lib

#-----------------------------------------------------------------------
# Setting for all UMD platforms
# ---> Set C++ to your C++ compiler
# ---> Set CFLAGS according your desired option (debug/performance)
#-----------------------------------------------------------------------
C++ = g++
CFLAGS = -O3 -Wall
# CFLAGS = -g -Wall
MISC_LIBS =  -lm

OGL_LIB_DIR  = $(OGL_DIR)/lib
OGL_INC_DIR  = $(OGL_DIR)/include

OGL_LFLAGS   = -L$(OGL_DIR)/lib -Wl $(OGL_LIBS)
INC_FLAGS = -I$(OGL_INC_DIR)
X_LFLAGS = -L$(X_LIB) -lX11 -lXext -lXmu -lXi 
LD_FLAGS = $(OGL_LFLAGS) $(X_LFLAGS) $(MISC_LIBS)

#-----------------------------------------------------------------------
# Compilation
#	This is the simplest form assuming a single source file.
#	If the file name is foo.cpp, set TARGET = foo, and the
#	object file will be put in foo.o, and the executable will
#	be put in foo.
#-----------------------------------------------------------------------
SOURCES = Smurfs.cpp RGBpixmap.cpp

OBJECTS = $(SOURCES:.cpp=.o)

#-----------------------------------------------------------------------
# Rules
#-----------------------------------------------------------------------

.cpp.o:
	$(C++) -c -I$(INCDIR) $(CFLAGS) $<

#-----------------------------------------------------------------------
# Dependencies
#-----------------------------------------------------------------------

default: $(TARGET)

RGBpixmap.o: RGBpixmap.h RGBpixmap.cpp

Smurfs.o: Smurfs.cpp


$(TARGET): $(OBJECTS)
	$(C++) $(CFLAGS) $(OBJECTS) -o $(TARGET) $(LD_FLAGS)

#-----------------------------------------------------------------------
#  Clean-up
#	make clean		remove .o and core files
#	make realclean		also removes executable
#-----------------------------------------------------------------------
clean:
	rm -f *.o core

realclean: clean
	rm -f $(TARGET)
