# C++ compiler.
CC = g++

# Compile flags
CFLAGS = -O2 -Wall -Wno-deprecated $(HDS)

# Header files
HDS = -I../include $(QHULL_INC) $(QSLIM_INC)

# QHULL settings
#QHULL_INC = -I/usr/local/qhull

# QSLIM settings
#QSLIM_DIR = /usr/local/qslim-2.0
#QSLIM_INC = -I$(QSLIM_DIR)/mixkit/src

all: libSWIFT.a

libSWIFT.a:
	cd src; $(MAKE) CC="$(CC)" CFLAGS="$(CFLAGS)"; cd ..

example: example_prog

example_prog:
	cd example; $(MAKE) CC="$(CC)" CFLAGS="$(CFLAGS)"; cd ..

# Remove all but executables
clean:
	rm -f src/*.o lib/*.a example/*.o */Makefile.bak
	rm -rf *~ */*~

# Remove all
realclean:
	rm -f src/*.o lib/*.a example/*.o example/example example/example.exe */Makefile.bak
	rm -f *.plg *.ilk *.ncb *.opt */*.ncb */*.opt */*.plg */*.ilk
	rm -rf Debug Release */Debug */Release
	rm -rf *~ */*~
