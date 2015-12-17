###
### Makefile for LaTeX documents
###
### Yoshinari Nomura
###
### GNU make 3.81 will work for you.
###

#####################################################################
# Typeset commands and path settings
#####################################################################

#vpath graphics

STY_FILES = ./sty
BIB_FILES = ../../bibs
BST_FILES = ../../bibs/sty

TEXINPUTS := $(TEXINPUTS):${STY_FILES}:

PLATEX    = TEXINPUTS=$(TEXINPUTS) platex -interaction=nonstopmode
BIBTEX     = BSTINPUTS=${BST_FILES} BIBINPUTS=${BIB_FILES} pbibtex
#BIBTEX    = pbibtex

DVIPDFMX   = dvipdfmx -p a4     # for A4
#DVIPDFMX  = dvipdfmx -p a4  -l # for A4 Landscape

GS         = gs -q -dSAFER -dBATCH -dNOPAUSE -dAutoRotatePages=/None
#EBB        = ebb


#####################################################################
# Helper Macros
#####################################################################

# Extract trailed page number from FILE-NAME:
#  $(call pagenum,fig1.pdf) -> 1
pagenum	= $(shell echo $(basename $1) | sed 's/^[^0-9]*//')

# Add PAGE-NUMBER to FILE-NAME:
#   $(call addpage,fig.pdf,1) -> fig1.pdf
# if SUFFIX is set as the third param, it replaces the original suffix:
#   $(call addpage,fig.pdf,1,bb) -> fig1.bb
#
addpage = $(basename $(1))$(2)$(if $(3),.$(3),$(suffix $(1)))

#####################################################################
# Suffix rules
#####################################################################

.SUFFIXES:
.SUFFIXES: .pdf .dvi .tex .eps .obj .png .gif .gnuplot

.dvi.pdf:
	${DVIPDFMX} $<

# .tex.dvi:
# 	${PLATEX} $< 2>&1 > /dev/null
# #	${BIBTEX} $*
# 	${PLATEX} $<

.pdf.xbb:
	@echo "Making $@ from $<"
	@${GS} -sDEVICE=bbox -r100 $< 2> $@

#####################################################################
# Files in the project
#####################################################################

# if the main TeX file is ``myproject.tex'', set:
#   PROJECT = myproject
PROJECT		= sigos136-kobe-fujita

# All figure files are extracted from the single PDF file: FIG_MASTER_FILE.
# FIG_PAGES indicates which pages are extracted and used in the main TeX file.
#
# For example:
#   FIG_MASTER_FILE = graphics/fig.pdf
#   FIG_PAGES     = 1 2 3 4 5
# makes:
#   graphics/fig1.pdf ... graphics/fig5.pdf from graphics/fig.pdf
#
FIG_MASTER_FILE = figs/fig.pdf
FIG_PAGES       = 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34
PROJECT_BIB    = ${BIB_FILES}/mybibdata.bib

TEX_FILES      = ${PROJECT}.tex
BBL_FILES      = ${PROJECT}.bbl
FIG_PDF_FILES := $(foreach n, $(FIG_PAGES), $(call addpage,$(FIG_MASTER_FILE),$(n)))
FIG_EBB_FILES := $(foreach n, $(FIG_PAGES), $(call addpage,$(FIG_MASTER_FILE),$(n),xbb))
FIG_EPS_FILES := $(foreach n, $(FIG_PAGES), $(call addpage,$(FIG_MASTER_FILE),$(n),eps))

#####################################################################
# Common rules
#####################################################################

preview: ${PROJECT}.pdf
	acroread $<
	make clean

all:	${PROJECT}.pdf

${FIG_PDF_FILES} : ${FIG_MASTER_FILE}
	@echo 'Making $@ from $< page: $(call pagenum,$*)'
	@${GS}  -sDEVICE=pdfwrite \
		-dFirstPage=$(call pagenum,$*)  \
		-dLastPage=$(call pagenum,$*)   \
		-sOutputFile=$@ ${FIG_MASTER_FILE} 2>/dev/null

${FIG_EBB_FILES} : %.xbb : %.pdf
	@echo "Making $@ from $<"
	@${GS} -sDEVICE=bbox -r100 $< 2> $@

${FIG_EPS_FILES} : %.eps : %.pdf
	@echo "Making $@ from $<"
	@pdf2ps $< - | ps2eps -r 100 > $@

${BBL_FILES} : ${PROJECT_BIB} ${TEX_FILES}
	${PLATEX} ${PROJECT}.tex
	${BIBTEX} ${PROJECT}

${PROJECT}.dvi: ${TEX_FILES} ${FIG_PDF_FILES} ${FIG_EBB_FILES} ${BBL_FILES}
	${PLATEX} ${PROJECT}.tex
	${PLATEX} ${PROJECT}.tex

#${PROJECT}.dvi: ${TEX_FILES} ${FIG_PDF_FILES} ${FIG_EBB_FILES}

${PROJECT}.pdf: ${PROJECT}.dvi

distclean: clean figclean pdfclean

eps:  ${FIG_EPS_FILES}

clean:
	rm -f *.aux *.bak *.bbl *.blg *.dvi *.idx *.ilg *.ind *.lnk *.lof *.log *.lot *.synctex *.toc *~
figclean:
	rm -f ${FIG_PDF_FILES} ${FIG_EBB_FILES} ${FIG_EPS_FILES}
pdfclean:
	rm -f ${PROJECT}.pdf

