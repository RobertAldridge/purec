
CC = g++

CFLAGS		= -DUNIX -I. -I../libSVM

LDFLAGS		= -L. -L../libSVM

.SUFFIXES: .C

SRCS		= box.C Intersect.C tri.C

OBJECTS		= box.o Intersect.o tri.o

CLEAN		= $(OBJECTS) *.a *.o *~ t t_plain_c

install: libobbt.a
library: libobbt.a

libobbt.a: $(OBJECTS)
	/bin/rm -f libobbt.a
	ar ruv libobbt.a $(OBJECTS)

.C.o:
	$(CC) ${CFLAGS} -c $<

.c.o:
	cc ${CFLAGS} -c $<

t: t.C
	/bin/rm -f t
	$(CC) -o t t.C ${CFLAGS} ${LDFLAGS} -lobbt -lSVM -lm

t_plain_c: t_plain_c.c libobbt.a
	/bin/rm -f t_plain_c
	gcc -o t_plain_c t_plain_c.c ${CFLAGS} ${LDFLAGS} -lobbt -lSVM -lm

clean:
	/bin/rm -f $(CLEAN)





