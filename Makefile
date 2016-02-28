# @version $Id: Makefile 100 2009-02-06 08:45:12Z Administrator $
# @version $Name:$
#
# @brief Makefile for this component.
#
# @component Sample
#
# @author Kenji MINOURA / kenji@kandj.org
#
# Copyright (c) 2008 K&J Software Design, Ltd All rights reserved.

SRCDIR = ./src
TESTDIR = ./test
INCDIR = ./include
DOCDIR = ./doc

PREFIX = /usr/local
CD = cd
CC = gcc
CXX = g++
LD = $(CXX)
CP = cp
RM = rm -f
FIND = find
TOUCH = touch
XARGS = xargs
TAGS = etags
INSTALL = install
DOXYGEN = doxygen
DVIPDFM = dvipdfmx
DOXYGEN_CFG = $(DOCDIR)/doxygen.cfg
DOXYGEN_STY = $(DOCDIR)/doxygen.sty
SVN_STY = $(DOCDIR)/svn.sty
DOXYGEN_LATEXDIR = $(DOCDIR)/latex
TAGS_FILE = ./TAGS
DEPEND_CC = $(CXX) -MM -w
DEPEND_FILE = .depend

# PLATFORM contains the target os for which the package is executed.
PLATFORM = POSIX

# The Compiler shall use EXT_LIBDIR as a library dir (-L)
EXT_LIBDIR =

# The Compiler shall use EXT_INCDIR as an include dir (-I)
EXT_INCDIR =

# The Compiler shall use EXT_LIB as a library (-l)
EXT_LIB = $(SUBPKG1) pthread

# The "install" target shall install binaries (like executables, no libraries)
# to INSTALL_BIN
INSTALL_BIN = $(PREFIX)/bin

# The "install" target shall install libraries to INSTALL_BIN
INSTALL_LIB = $(PREFIX)/lib

# The "install" target shall install header files that are to be 
# exported to INSTALL_HEADER
INSTALL_HEADER = $(PREFIX)/include

# The "install" target shall install miscellaneous files to INSTALL_ETC
INSTALL_ETC = $(PREFIX)/etc

# ARCH contains the target for which the package is built (e.g. vr5500)
ARCH = i386

# ----------------------------------------------------------------------------

# The final Target
TARGET =

# The sourcedir will be configured by configure
S = $(SRCDIR)
T = $(TESTDIR)
VPATH = $S $T

SRC =
SRCS = $(SRC_1)

# ----------------------------------------------------------------------------
# 
# ----------------------------------------------------------------------------

# A list of intermediate object files, derived from the source file names
OBJ = $(addsuffix .o, $(basename $(SRC)))

# Flags for the C-Compiler
CFLAGS += -Wall $(addprefix -D, $(DEFINES)) $(addprefix -I, $(EXT_INCDIR))

# Flags for the linker.
LDFLAGS += $(addprefix -L, $(EXT_LIBDIR)) $(addprefix -l, $(EXT_LIB))

# ----------------------------------------------------------------------------

.PHONY: all test clean doc install tags depend

# ------------- make interface ------------------------------------------
ALL = $(TARGET)

all: $(ALL)

test: $(TARGET_TEST)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<
%.o: %.C
	$(CXX) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJ_1)
	$(LD) -o $(TARGET) $(OBJ) $(LDFLAGS) 
doc: $(DOXYGEN_CFG)
	$(DOXYGEN) $(DOXYGEN_CFG)
	$(CP) $(SVN_STY) $(DOXYGEN_LATEXDIR)
	($(CD) $(DOXYGEN_LATEXDIR) && make && $(DVIPDFM) refman)

clean-main:
	$(RM) $(OBJ) $(ALL) $(OBJ_TEST) $(TARGET_TEST) $(DEPEND_FILE) *~

tags: $(TAGS_FILE)

$(TAGS_FILE): $(SRC) $(SRC_TEST)
	$(FIND) . -regex '.*\.\(cpp\|c\|h\)' -print | $(XARGS) $(TAGS)

install:
	@echo "TODO"

install-doc:
	@echo "TODO"

depend: $(DEPEND_FILE)

$(DEPEND_FILE): $(SRCS)
	$(RM) $(DEPEND_FILE) ; \
	$(TOUCH) $(DEPEND_FILE) ; \
	for i in $(SRCS) ; do \
		$(DEPEND_CC) $(CFLAGS) $$i >> $(DEPEND_FILE) ; \
	done

include $(DEPEND_FILE)
