
CC = g++

CFLAGS		= -DUNIX

LDFLAGS		= -L.

.SUFFIXES: .C

SRCS		= m33.C v3.C m33v3.C angle.C geom.C

OBJECTS		= m33.o v3.o m33v3.o angle.o geom.o

DOT_H_INSTALL = *.H

LIBRARY		= SVM

CLEAN		= $(OBJECTS) lib$(LIBRARY).a *.o

install: libSVM.a
library: libSVM.a

lib$(LIBRARY).a: $(OBJECTS)
	rm -f lib$(LIBRARY).a
	ar ruv lib$(LIBRARY).a $(OBJECTS)

.C.o:
	$(CC) ${CFLAGS} -c $<

clean:
	rm -f $(CLEAN)

