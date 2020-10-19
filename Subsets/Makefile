#------------------------------------------------------------------------------
# # Rudra Bhattacharya 
# rubhatta
# CMPS 12B
# April 15, 2019
# Makefile that archives Subset.class, including clean, submit, and check utilities 
# Makefile
#------------------------------------------------------------------------------
JAVASRC  = Subset.java
SOURCES  = README Makefile $(JAVASRC)
MAINCLASS  = Subset
CLASSES  = Subset.class
JARFILE  = Subset
SUBMIT  = submit cmps012b-pt.s19 pa1

all: $(JARFILE)

$(JARFILE): $(CLASSES)
	echo Main-class: $(MAINCLASS) > Manifest
	jar cvfm $(JARFILE) Manifest $(CLASSES)
	rm Manifest
	chmod +x $(JARFILE)

$(CLASSES): $(JAVASRC)
	javac -Xlint $(JAVASRC)

clean:
	rm $(CLASSES) $(JARFILE)

submit: $(SOURCES)
	$(SUBMIT) $(SOURCES)

check:
	ls  /afs/cats.ucsc.edu/class/cmps012b-pt.s19/pa1/rubhatta