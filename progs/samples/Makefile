
PROGS = prim \
	star \
	line \
	point \
	depth \
	tri \
	bitmap1 \
	bitmap2


##### RULES #####

.SUFFIXES:
.SUFFIXES: .c


# make executable from .c file:
.c: $(LIB_DEP)
	gcc -I../include -g $< -L../lib -lglut -lGL -lm -o $@


default: $(PROGS)


clean:
	-rm *.o *~

