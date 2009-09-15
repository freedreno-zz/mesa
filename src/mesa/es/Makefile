# src/mesa/es/Makefile
#
TOP := ../../..
MESA := ..

include $(TOP)/configs/current
include sources.mak

# no libes1.a and libes2.a by default
ES1_LIBS := libes1.a libes1gallium.a libes1api.a
ES2_LIBS := libes2.a libes2gallium.a libes2api.a

# Default rule: create ES1 and ES2 libs
.PHONY: default
default: subdirs $(ES1_LIBS) $(ES2_LIBS)

# force the inclusion of es's mfeatures.h
ES1_CFLAGS := -include main/mfeatures.h -D__GL_EXPORTS -UIN_DRI_DRIVER
ES2_CFLAGS := $(ES1_CFLAGS)

# rebuild when these files are changed
ES1_GLAPI_DEPS := glapi/headers-es1/glapi/dispatch.h
ES2_GLAPI_DEPS := glapi/headers-es2/glapi/dispatch.h

ES1_OBJ_DIR := objs-es1
ES2_OBJ_DIR := objs-es2

# adjust output dir
ES1_OBJECTS := $(addprefix $(ES1_OBJ_DIR)/, $(ES1_OBJECTS))
ES1_GALLIUM_OBJECTS := $(addprefix $(ES1_OBJ_DIR)/, $(ES1_GALLIUM_OBJECTS))
ES1_API_OBJECTS := $(addprefix $(ES1_OBJ_DIR)/, $(ES1_API_OBJECTS))

ES2_OBJECTS := $(addprefix $(ES2_OBJ_DIR)/, $(ES2_OBJECTS))
ES2_GALLIUM_OBJECTS := $(addprefix $(ES2_OBJ_DIR)/, $(ES2_GALLIUM_OBJECTS))
ES2_API_OBJECTS := $(addprefix $(ES2_OBJ_DIR)/, $(ES2_API_OBJECTS))

# specify prerequisites
$(foreach obj,$(ALL_LOCAL_OBJECTS), \
	$(eval $(ES1_OBJ_DIR)/$(obj): $(obj:.o=.c) $(ES1_GLAPI_DEPS)) \
	$(eval $(ES2_OBJ_DIR)/$(obj): $(obj:.o=.c) $(ES2_GLAPI_DEPS)))
$(foreach obj,$(ALL_MESA_OBJECTS), \
	$(eval $(ES1_OBJ_DIR)/$(obj): $(MESA)/$(obj:.o=.c) $(ES1_GLAPI_DEPS)) \
	$(eval $(ES2_OBJ_DIR)/$(obj): $(MESA)/$(obj:.o=.c) $(ES2_GLAPI_DEPS)))

# sort to remove duplicates
ES1_ANY_OBJECTS := $(sort $(ES1_OBJECTS) $(ES1_GALLIUM_OBJECTS))
ES2_ANY_OBJECTS := $(sort $(ES2_OBJECTS) $(ES2_GALLIUM_OBJECTS))

$(ES1_ANY_OBJECTS):
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $(ES1_CFLAGS) $(ES1_INCLUDES) $< -o $@

$(ES1_API_OBJECTS):
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $(ES1_CFLAGS) -UIN_DRI_DRIVER $(ES1_INCLUDES) $< -o $@

$(ES2_ANY_OBJECTS):
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $(ES2_CFLAGS) $(ES2_INCLUDES) $< -o $@

$(ES2_API_OBJECTS):
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $(ES2_CFLAGS) -UIN_DRI_DRIVER $(ES2_INCLUDES) $< -o $@

libes1.a: $(ES1_OBJECTS)
	@echo "Making $@"
	@$(TOP)/bin/mklib -o es1 -static $(ES1_OBJECTS)

libes2.a: $(ES2_OBJECTS)
	@echo "Making $@"
	@$(TOP)/bin/mklib -o es2 -static $(ES1_OBJECTS)

libes1gallium.a: $(ES1_GALLIUM_OBJECTS)
	@echo "Making $@"
	@$(TOP)/bin/mklib -o es1gallium -static $(ES1_GALLIUM_OBJECTS)

libes2gallium.a: $(ES2_GALLIUM_OBJECTS)
	@echo "Making $@"
	@$(TOP)/bin/mklib -o es2gallium -static $(ES2_GALLIUM_OBJECTS)

libes1api.a: $(ES1_API_OBJECTS)
	@echo "Making $@"
	@$(TOP)/bin/mklib -o es1api -static $(ES1_API_OBJECTS)

libes2api.a: $(ES2_API_OBJECTS)
	@echo "Making $@"
	@$(TOP)/bin/mklib -o es2api -static $(ES2_API_OBJECTS)

GENERATED_SOURCES :=		\
	main/api_exec_es1.c	\
	main/api_exec_es2.c	\
	main/get_es1.c		\
	main/get_es2.c

main/api_exec_es1.c: main/APIspec.txt main/es_generator.py main/apiutil.py main/es1_special
	$(PYTHON2) $(PYTHON_FLAGS) main/es_generator.py -S main/APIspec.txt -V GLES1.1 > $@

main/api_exec_es2.c: main/APIspec.txt main/es_generator.py main/apiutil.py main/es2_special
	$(PYTHON2) $(PYTHON_FLAGS) main/es_generator.py -S main/APIspec.txt -V GLES2.0 > $@

main/get_es1.c: main/get_gen.py
	$(PYTHON2) $(PYTHON_FLAGS) $< 1 > $@

main/get_es2.c: main/get_gen.py
	$(PYTHON2) $(PYTHON_FLAGS) $< 2 > $@

subdirs:
	make -C glapi

.PHONY: clean
clean:
	-rm -f $(ES1_LIBS) $(ES2_LIBS)
	-rm -rf $(ES1_OBJ_DIR) $(ES2_OBJ_DIR)
	-rm -f $(GENERATED_SOURCES)
	-rm -f *~
