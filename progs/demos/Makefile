
PROGS = gears \
	glinfo \
	morph3d \
	texobj \
	bounce


##### RULES #####

.SUFFIXES:
.SUFFIXES: .c


# make executable from .c file:
.c: $(LIB_DEP)
	gcc -I../include -g $< -L../lib -lglut -lGL -lm -o $@


default: $(PROGS)


clean:
	-rm *.o *~

