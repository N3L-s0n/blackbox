BUILDDIR := obj
TARGETDIR := bin
VPATH := src:src/core:src/http:src/mem:src/html:src/utils
OBJS := $(addprefix $(BUILDDIR)/, box_headers.o box_array.o box_ntree.o \
		box_html.o box_reader.o box_tags.o box_regex.o box_http.o)

.PHONY: all

all: $(TARGETDIR)/$(page).cgi $(BUILDDIR)/$(page).o $(OBJS) | $(TARGETDIR)

$(TARGETDIR)/$(page).cgi: $(BUILDDIR)/$(page).o $(OBJS) | $(TARGETDIR)
	gcc -g $(OUTPUT_OPTION) $^

$(BUILDDIR)/%.o: %.c %.h
	gcc -g -c $(OUTPUT_OPTION) $<

$(OBJS): | $(BUILDDIR)

$(BUILDDIR):
	mkdir $(BUILDDIR)

$(TARGETDIR):
	mkdir $(TARGETDIR)
