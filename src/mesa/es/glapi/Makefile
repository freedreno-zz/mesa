TOP = ../../../..
GLAPI = ../../glapi
include $(TOP)/configs/current

OUTPUTS := glprocs.h glapitemp.h glapioffsets.h glapitable.h dispatch.h

COMMON = gl_XML.py glX_XML.py license.py typeexpr.py
COMMON := $(addprefix $(GLAPI)/, $(COMMON))

ES1_APIXML := es1_API.xml
ES2_APIXML := es2_API.xml
ES1_OUTPUT_DIR := headers-es1
ES2_OUTPUT_DIR := headers-es2

ES1_DEPS = $(ES1_APIXML) base1_API.xml es1_EXT.xml es_EXT.xml \
	   es1_COMPAT.xml es_COMPAT.xml
ES2_DEPS = $(ES2_APIXML) base2_API.xml es2_EXT.xml es_EXT.xml \
	   es2_COMPAT.xml es_COMPAT.xml

ES1_OUTPUTS := $(addprefix $(ES1_OUTPUT_DIR)/glapi/, $(OUTPUTS))
ES2_OUTPUTS := $(addprefix $(ES2_OUTPUT_DIR)/glapi/, $(OUTPUTS))

all: $(ES1_OUTPUTS) $(ES2_OUTPUTS)

$(ES1_OUTPUTS): APIXML := $(ES1_APIXML)
$(ES2_OUTPUTS): APIXML := $(ES2_APIXML)
$(ES1_OUTPUTS): $(ES1_DEPS)
$(ES2_OUTPUTS): $(ES2_DEPS)

%/glprocs.h: $(GLAPI)/gl_procs.py $(COMMON)
	@mkdir -p $(dir $@)
	$(PYTHON2) $(PYTHON_FLAGS) $< -f $(APIXML) -c > $@

%/glapitemp.h: $(GLAPI)/gl_apitemp.py $(COMMON)
	@mkdir -p $(dir $@)
	$(PYTHON2) $(PYTHON_FLAGS) $< -f $(APIXML) > $@

%/glapioffsets.h: $(GLAPI)/gl_offsets.py $(COMMON)
	@mkdir -p $(dir $@)
	$(PYTHON2) $(PYTHON_FLAGS) $< -f $(APIXML) -c > $@

%/glapitable.h: $(GLAPI)/gl_table.py $(COMMON)
	@mkdir -p $(dir $@)
	$(PYTHON2) $(PYTHON_FLAGS) $< -f $(APIXML) -c > $@

%/dispatch.h: $(GLAPI)/gl_table.py $(COMMON)
	@mkdir -p $(dir $@)
	$(PYTHON2) $(PYTHON_FLAGS) $< -f $(APIXML) -m remap_table -c > $@

verify_xml:
	@if [ ! -f gl.h ]; then \
		echo "Please copy gl.h and gl2.h to this directory"; \
		exit 1; \
	fi
	@echo "Verifying that es1_API.xml covers OpenGL ES 1.1..."
	@$(PYTHON2) $(PYTHON_FLAGS) gl_parse_header.py gl.h > tmp.xml
	@$(PYTHON2) $(PYTHON_FLAGS) gl_compare.py difference tmp.xml es1_API.xml
	@echo "Verifying that es2_API.xml covers OpenGL ES 2.0..."
	@$(PYTHON2) $(PYTHON_FLAGS) gl_parse_header.py gl2.h > tmp.xml
	@$(PYTHON2) $(PYTHON_FLAGS) gl_compare.py difference tmp.xml es2_API.xml
	@rm -f tmp.xml

clean:
	-rm -rf $(ES1_OUTPUT_DIR) $(ES2_OUTPUT_DIR)
	-rm -f *~ *.pyc *.pyo
