
PROGS = gears \
	glinfo \
	texobj \
	bounce \
	terrain


##### RULES #####

.SUFFIXES:
.SUFFIXES: .c


# make executable from .c file:
.c: $(LIB_DEP)
	gcc -I../include -I../util -g $< -L../lib -lglut -lGL -lm -o $@


default: $(PROGS)


clean:
	-rm *.o *~

