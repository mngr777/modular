AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = -I m4
AM_CXXFLAGS = -std=c++17 -iquote $(srcdir) -I $(srcdir) -Wall -Werror

HEADER_FILES = \
	modular/context.hpp \
	modular/graph.hpp \
	modular/library.hpp \
	modular/loader.hpp \
	modular/module.hpp \
	modular/package.hpp \
	modular/processor.hpp \
	modular/registry.hpp \
	modular/string.hpp \
	modular/utils/lib.hpp

SOURCE_FILES = \
	src/context.cpp \
	src/graph.cpp \
	src/loader.cpp \
	src/module.cpp \
	src/package.cpp \
	src/utils/lib.cpp

lib_LTLIBRARIES = libmodular.la
libmodular_ladir = $(includedir)
nobase_libmodular_la_HEADERS = $(HEADER_FILES)
libmodular_la_SOURCES = $(SOURCE_FILES)

## Modules
pkgmoddir = /usr/local/lib
MODULE_FLAGS = -module
MODULE_LIBS = libmodular.la
pkgmod_LTLIBRARIES =

# Tick
pkgmod_LTLIBRARIES += tick.la
tick_la_SOURCES = modules/tick/tick.hpp modules/tick/tick.cpp
tick_la_LDFLAGS = $(MODULE_FLAGS)
tick_la_LIBADD = $(MODULE_LIBS)

# Tick print
pkgmod_LTLIBRARIES += tickprint.la
tickprint_la_SOURCES = modules/tickprint/tickprint.hpp modules/tickprint/tickprint.cpp
tickprint_la_LDFLAGS = $(MODULE_FLAGS)
tickprint_la_LIBADD = $(MODULE_LIBS)

# FIFO
pkgmod_LTLIBRARIES += fifo.la
fifo_la_SOURCES = modules/fifo/fifo.hpp modules/fifo/fifo.cpp
fifo_la_LDFLAGS = $(MODULE_FLAGS)
fifo_la_LIBADD = $(MODULE_LIBS)

## Tests
TESTS = test_exec1 test_ipc1
TEST_LIBS = libmodular.la
check_PROGRAMS = $(TESTS)

test_exec1_SOURCES = tests/test_exec1.cpp
test_exec1_LDADD = $(TEST_LIBS)

test_ipc1_SOURCES = tests/test_ipc1.cpp
test_ipc1_LDADD = $(TEST_LIBS)
