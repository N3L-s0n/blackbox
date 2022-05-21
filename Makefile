# Compilation options
BUILDDIR 	:= obj
HOMEDIR 	:= /var/www/blackbox

# Images and Style sheets
CSSDEST  	:= /var/www/blackbox/css
IMGDEST 	:= /var/www/blackbox/images
HTMLDEST	:= /var/www/blackbox/html

CSSSRC		:= www/css
IMGSRC		:= www/images
HTMLSRC		:= html

VPATH := src:src/core:src/http:src/mem:src/html:src/utils
OBJS := $(addprefix $(BUILDDIR)/, box_headers.o box_array.o box_ntree.o \
		box_html.o box_reader.o box_tags.o box_regex.o box_http.o box_map.o)

.PHONY: all

all: $(HOMEDIR)/$(page).cgi $(BUILDDIR)/$(page).o $(OBJS) | $(HOMEDIR) $(CSSDEST) $(IMGDEST) $(HTMLDEST)

$(HOMEDIR)/$(page).cgi: $(BUILDDIR)/$(page).o $(OBJS) | $(HOMEDIR) $(CSSDEST) $(IMGDEST) $(HTMLDEST)
	gcc -g $(OUTPUT_OPTION) $^

$(BUILDDIR)/%.o: %.c %.h | $(BUILDDIR)
	gcc -g -c $(OUTPUT_OPTION) $<

$(BUILDDIR)/%.o: %.c | $(BUILDDIR)
	gcc -g -c $(OUTPUT_OPTION) $<

$(OBJS): | $(BUILDDIR)

$(CSSDEST):
	rsync -rupE --delete $(CSSSRC) $(HOMEDIR)

$(IMGDEST):
	rsync -rupE --delete $(IMGSRC) $(HOMEDIR) 

$(HTMLDEST):
	rsync -rupE --delete $(HTMLSRC) $(HOMEDIR)

$(BUILDDIR):
	mkdir $(BUILDDIR)

$(HOMEDIR):
	mkdir $(HOMEDIR)
