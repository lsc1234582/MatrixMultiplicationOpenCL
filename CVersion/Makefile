# An example of standard Makefile
# x86-64 Linux with GNU g++ compiler

CPP = gcc
CPPFLAGS = -std=c99 -Wall
# -l identifies the specific names of libraries to be included in the build
#  Note no need to add lib prefix
LIB = -lOpenCL

# If AMD SDK
ifdef AMDAPPSDKROOT
 	INC_DIRS=$(AMDAPPSDKROOT)/include
 	LIB_DIRS=$(AMDAPPSDKROOT)/lib/x86
else

ifdef NVSDKCOMPUTE_ROOT
	INC_DIRS=$(NVSDKCOMPUTE_ROOT)/targets/x86_64-linux/include
	LIB_DIRS=$(NVSDKCOMPUTE_ROOT)/targets/x86_64-linux/lib
endif

endif

# -I Identifies a directory containing source files to be included in the
#  build
# -L Identifies a directory containing libraries to be included in the build
main: main.c mat.h mat4_mult_host.c
	$(CPP) $(CPPFLAGS) -o $@ $^ -I$(INC_DIRS) -L$(LIB_DIRS) $(LIB)

.PHONY: clean
clean:
	rm $(PROJ)




