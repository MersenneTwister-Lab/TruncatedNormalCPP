PANDOC = pandoc
PANDOCFLAGS = --self-contained -t html5 -c $(HOME)/.pandoc/github.css

%.html:%.md
	$(PANDOC) $(PANDOCFLAGS) -o $@ $<
