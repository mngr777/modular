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
	modular/scheduler.hpp \
	modular/string.hpp \
	modular/utils/lib.hpp

SOURCE_FILES = \
	src/context.cpp \
	src/graph.cpp \
	src/loader.cpp \
	src/module.cpp \
	src/utils/lib.cpp

lib_LTLIBRARIES = libmodular.la
libmodular_ladir = $(includedir)
nobase_libmodular_la_HEADERS = $(HEADER_FILES)
libmodular_la_SOURCES = $(SOURCE_FILES)


