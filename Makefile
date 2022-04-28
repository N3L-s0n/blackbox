BUILDDIR := obj
TARGETDIR := bin
VPATH := src:src/core:src/http
OBJS := $(addprefix $(BUILDDIR)/,blackbox.o box_headers.o)

$(TARGETDIR)/blacbox.cgi: $(OBJS) | $(TARGETDIR)
	gcc $(OUTPUT_OPTION) $^

$(BUILDDIR)/blackbox.o : blackbox.c blackbox.h
	gcc -c $(OUTPUT_OPTION) $<

$(BUILDDIR)/box_headers.o : box_headers.c box_headers.h
	gcc -c $(OUTPUT_OPTION) $<

$(OBJS): | $(BUILDDIR)

$(BUILDDIR):
	mkdir $(BUILDDIR)

$(TARGETDIR):
	mkdir $(TARGETDIR)
