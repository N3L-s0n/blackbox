# Compilation options
BUILDDIR := obj
TARGETDIR := /var/www/blackbox/bin
HOMEDIR := /var/www/blackbox

# Images and Style sheets
CSSDEST := /var/www/blackbox/css
IMGDEST := /var/www/blackbox/images
HTMLDEST := /var/www/blackbox/html

CSSSRC := www/css
IMGSRC := www/images
HTMLSRC := html

VPATH := src:src/core:src/http:src/mem:src/html:src/utils:src/db:src/domain
OBJS := $(addprefix $(BUILDDIR)/, box_headers.o box_array.o box_ntree.o \
		box_html.o box_reader.o box_tags.o box_regex.o box_http.o box_map.o \
		box_product.o box_user.o box_question.o box_credit_card.o box_cart.o\
		sql_connection.o sql_product.o sql_user.o sql_question.o sql_cart.o\
		sql_credit_card.o box_client_token.o box_url.o box_card_validation.o\
		box_entry_validation.o box_sha.o)

.PHONY: all

all: $(TARGETDIR)/$(page).cgi $(BUILDDIR)/$(page).o $(OBJS) | $(HOMEDIR) $(TARGETDIR) $(CSSDEST) $(IMGDEST) $(HTMLDEST)

$(TARGETDIR)/$(page).cgi: $(BUILDDIR)/$(page).o $(OBJS) | $(HOMEDIR) $(TARGETDIR) $(CSSDEST) $(IMGDEST) $(HTMLDEST)
	gcc -g -std=c11 $(OUTPUT_OPTION) $^ -lssl -lcrypto `mysql_config --libs | awk '{print $$1,$$2;}'`

$(BUILDDIR)/%.o: %.c %.h | $(BUILDDIR)
	gcc -g -c -std=c11 `mysql_config --cflags` $(OUTPUT_OPTION) $<

$(BUILDDIR)/%.o: %.c | $(BUILDDIR)
	gcc -g -c -std=c11 $(OUTPUT_OPTION) $<

$(OBJS): | $(BUILDDIR)

$(CSSDEST): $(CSSSRC)
	rsync -rupE --delete $(CSSSRC) $(HOMEDIR)

$(IMGDEST): $(IMGSRC)
	rsync -rupE --delete $(IMGSRC) $(HOMEDIR) 

$(HTMLDEST): $(HTMLSRC)
	rsync -rupE --delete $(HTMLSRC) $(HOMEDIR)

$(BUILDDIR):
	mkdir $(BUILDDIR)

$(HOMEDIR):
	mkdir $(HOMEDIR)

$(TARGETDIR):
	mkdir $(TARGETDIR)
