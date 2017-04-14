PANDOC = pandoc
PANDOCFLAGS = --self-contained -t html5 -c $(HOME)/.pandoc/github.css

all: index.html example-qmc.html

%.html:%.md
	$(PANDOC) $(PANDOCFLAGS) -o $@ $<
