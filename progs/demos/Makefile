
PROGS = gears \
	glinfo \
	texobj \
	isosurf \
	bounce \
	terrain


##### RULES #####

.SUFFIXES:
.SUFFIXES: .c


# make executable from .c file:
.c: $(LIB_DEP)
	gcc -I../include -I../util -g $< -L../lib -lglut -lGL -lGLU -lm -o $@


default: $(PROGS)


clean:
	-rm -f *.o *~ $(PROGS)

