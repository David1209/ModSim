PROGNAME=modsim_assignment_2
VERSION=1.0

MKDIR=mkdir
PACK=tar -jcvf
CC=gcc
CFLAGS=-Wall -pedantic -std=c99 -lm -lgsl -lgslcblas
CP=cp
RM=rm -rf
OFILES=$(subst .c,.o,$(wildcard *.c))

$(PROGNAME): $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) -o $(PROGNAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) *.o $(PROGNAME) $(PROGNAME)-$(VERSION).tbz

run: $(PROGNAME)
	`pwd`/$(PROGNAME)

tarball: $(PROGNAME)
	$(MAKE) clean
	$(MKDIR) $(PROGNAME)-$(VERSION)
	$(CP) * $(PROGNAME)-$(VERSION) || true
	$(PACK) $(PROGNAME)-$(VERSION).tbz $(PROGNAME)-$(VERSION)/*
	$(RM) $(PROGNAME)-$(VERSION)