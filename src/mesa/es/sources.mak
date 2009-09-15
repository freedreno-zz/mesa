# LOCAL sources

ES1_LOCAL_SOURCES :=			\
	main/api_exec_es1.c		\
	main/drawtex.c			\
	main/eglimage.c			\
	main/get_es1.c			\
	main/specials_es1.c		\
	main/es_cpaltex.c		\
	main/es_fbo.c			\
	main/es_query_matrix.c		\
	main/stubs.c

ES1_GALLIUM_LOCAL_SOURCES :=		\
	$(ES1_LOCAL_SOURCES)

ES1_API_LOCAL_SOURCES :=		\

ES1_LOCAL_INCLUDES :=			\
	-I.				\
	-I./glapi/headers-es1		\
	-I./state_tracker		\
	-I$(MESA)/state_tracker

ES2_LOCAL_SOURCES :=			\
	main/api_exec_es2.c		\
	main/eglimage.c			\
	main/get_es2.c			\
	main/specials_es2.c		\
	main/es_cpaltex.c		\
	main/es_fbo.c			\
	main/stubs.c

ES2_GALLIUM_LOCAL_SOURCES :=		\
	$(ES2_LOCAL_SOURCES)

ES2_API_LOCAL_SOURCES :=

ES2_LOCAL_INCLUDES := $(subst es1,es2,$(ES1_LOCAL_INCLUDES))

# MESA sources

include $(MESA)/sources.mak

MAIN_OMITTED :=				\
	main/api_exec.c			\
	main/dlopen.c			\
	main/get.c
MAIN_SOURCES := $(filter-out $(MAIN_OMITTED), $(MAIN_SOURCES))

VBO_OMITTED :=				\
	vbo/vbo_save_api.c		\
	vbo/vbo_save.c			\
	vbo/vbo_save_draw.c		\
	vbo/vbo_save_loopback.c
VBO_SOURCES := $(filter-out $(VBO_OMITTED), $(VBO_SOURCES))

STATETRACKER_OMITTED :=				\
	state_tracker/st_cb_drawpixels.c	\
	state_tracker/st_cb_feedback.c		\
	state_tracker/st_cb_rasterpos.c		\
	state_tracker/st_api.c			\
	state_tracker/st_draw_feedback.c
STATETRACKER_SOURCES := $(filter-out $(STATETRACKER_OMITTED), $(STATETRACKER_SOURCES))

SHADER_OMITTED :=			\
	shader/atifragshader.c		\
	shader/nvfragparse.c		\
	shader/nvprogram.c		\
	shader/nvvertparse.c
SHADER_SOURCES := $(filter-out $(SHADER_OMITTED), $(SHADER_SOURCES))

STATETRACKER_SOURCES +=			\
	state_tracker/st_cb_drawtex.c

ES1_MESA_SOURCES :=			\
	$(MAIN_SOURCES)			\
	$(MATH_SOURCES)			\
	$(MATH_XFORM_SOURCES)		\
	$(VBO_SOURCES)			\
	$(TNL_SOURCES)			\
	$(SHADER_SOURCES)		\
	$(SWRAST_SOURCES)		\
	$(SWRAST_SETUP_SOURCES)		\
	$(COMMON_DRIVER_SOURCES)	\
	$(ASM_C_SOURCES)		\
	$(SLANG_SOURCES)

ES1_GALLIUM_MESA_SOURCES :=		\
	$(MAIN_SOURCES)			\
	$(MATH_SOURCES)			\
	$(MATH_XFORM_SOURCES)		\
	$(VBO_SOURCES)			\
	$(STATETRACKER_SOURCES)		\
	$(SHADER_SOURCES)		\
	$(SLANG_SOURCES)

ES1_API_MESA_SOURCES :=			\
	$(GLAPI_SOURCES)

ES1_MESA_INCLUDES := $(INCLUDE_DIRS)

# remove LOCAL sources from MESA sources
ES1_MESA_SOURCES := $(filter-out $(ES1_LOCAL_SOURCES), $(ES1_MESA_SOURCES))
ES1_GALLIUM_MESA_SOURCES := $(filter-out $(ES1_GALLIUM_LOCAL_SOURCES), $(ES1_GALLIUM_MESA_SOURCES))
ES1_API_MESA_SOURCES := $(filter-out $(ES1_API_LOCAL_SOURCES), $(ES1_API_MESA_SOURCES))

# es2 and es1 share sources
ES2_MESA_SOURCES := $(ES1_MESA_SOURCES)
ES2_GALLIUM_MESA_SOURCES := $(ES1_GALLIUM_MESA_SOURCES)
ES2_API_MESA_SOURCES := $(ES1_API_MESA_SOURCES)

ES2_MESA_INCLUDES := $(ES1_MESA_INCLUDES)


# collect sources
ES1_SOURCES := $(ES1_LOCAL_SOURCES) $(ES1_MESA_SOURCES)
ES1_GALLIUM_SOURCES := $(ES1_GALLIUM_LOCAL_SOURCES) $(ES1_GALLIUM_MESA_SOURCES)
ES1_API_SOURCES := $(ES1_API_LOCAL_SOURCES) $(ES1_API_MESA_SOURCES)

ES2_SOURCES := $(ES2_LOCAL_SOURCES) $(ES2_MESA_SOURCES)
ES2_GALLIUM_SOURCES := $(ES2_GALLIUM_LOCAL_SOURCES) $(ES2_GALLIUM_MESA_SOURCES)
ES2_API_SOURCES := $(ES2_API_LOCAL_SOURCES) $(ES2_API_MESA_SOURCES)

# collect includes
ES1_INCLUDES := $(ES1_LOCAL_INCLUDES) $(ES1_MESA_INCLUDES)
ES2_INCLUDES := $(ES2_LOCAL_INCLUDES) $(ES2_MESA_INCLUDES)

# group sources in another way
ALL_LOCAL_SOURCES :=			\
	$(ES1_LOCAL_SOURCES)		\
	$(ES1_GALLIUM_LOCAL_SOURCES)	\
	$(ES1_API_LOCAL_SOURCES)	\
	$(ES2_LOCAL_SOURCES)		\
	$(ES2_GALLIUM_LOCAL_SOURCES)	\
	$(ES2_API_LOCAL_SOURCES)
ALL_MESA_SOURCES :=			\
	$(ES1_MESA_SOURCES)		\
	$(ES1_GALLIUM_MESA_SOURCES)	\
	$(ES1_API_MESA_SOURCES)		\
	$(ES2_MESA_SOURCES)		\
	$(ES2_GALLIUM_MESA_SOURCES)	\
	$(ES2_API_MESA_SOURCES)

# sort to remove duplicates
ALL_LOCAL_SOURCES := $(sort $(ALL_LOCAL_SOURCES))
ALL_MESA_SOURCES := $(sort $(ALL_MESA_SOURCES))

# convert to objects
ES1_OBJECTS := $(ES1_SOURCES:.c=.o)
ES1_GALLIUM_OBJECTS := $(ES1_GALLIUM_SOURCES:.c=.o)
ES1_API_OBJECTS := $(ES1_API_SOURCES:.c=.o)

ES2_OBJECTS := $(ES2_SOURCES:.c=.o)
ES2_GALLIUM_OBJECTS := $(ES2_GALLIUM_SOURCES:.c=.o)
ES2_API_OBJECTS := $(ES2_API_SOURCES:.c=.o)

ALL_LOCAL_OBJECTS := $(ALL_LOCAL_SOURCES:.c=.o)
ALL_MESA_OBJECTS := $(ALL_MESA_SOURCES:.c=.o)
