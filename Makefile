BUILDDIR := obj
TARGETDIR := bin
VPATH := src:src/core:src/http:src/mem:src/html
OBJS := $(addprefix $(BUILDDIR)/,blackbox.o box_headers.o box_array.o box_ntree.o \
		box_html.o box_reader.o box_tags.o)

$(TARGETDIR)/blackbox.cgi: $(OBJS) | $(TARGETDIR)
	gcc -g $(OUTPUT_OPTION) $^

$(BUILDDIR)/blackbox.o : blackbox.c blackbox.h
	gcc -g -c $(OUTPUT_OPTION) $<

$(BUILDDIR)/box_headers.o : box_headers.c box_headers.h
	gcc -g -c $(OUTPUT_OPTION) $<

$(BUILDDIR)/box_array.o : box_array.c box_array.h
	gcc -g -c $(OUTPUT_OPTION) $<

$(BUILDDIR)/box_ntree.o : box_ntree.c box_ntree.h
	gcc -g -c $(OUTPUT_OPTION) $<

$(BUILDDIR)/box_html.o : box_html.c box_html.h
	gcc -g -c $(OUTPUT_OPTION) $<

$(BUILDDIR)/box_reader.o : box_reader.c box_reader.h
	gcc -g -c $(OUTPUT_OPTION) $<

$(BUILDDIR)/box_tags.o : box_tags.c box_tags.h
	gcc -g -c $(OUTPUT_OPTION) $<

$(OBJS): | $(BUILDDIR)

$(BUILDDIR):
	mkdir $(BUILDDIR)

$(TARGETDIR):
	mkdir $(TARGETDIR)
