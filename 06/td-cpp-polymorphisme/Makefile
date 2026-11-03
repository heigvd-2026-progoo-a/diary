# Travail dirigé « Interfaces et composition d'interfaces en C++ ».
#
#   make            compile le code de départ et les corrigés dans build/
#   make run        exécute chaque programme
#   make pdf        produit l'énoncé en PDF (TeXSmith, via uv)
#   make clean      supprime build/

CXX      ?= g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -Werror
BUILDDIR := build

SOURCES  := depart/zoo.cpp $(wildcard corrige/*.cpp)
PROGRAMS := $(patsubst %.cpp,$(BUILDDIR)/%,$(SOURCES))

PDF       := $(BUILDDIR)/td-interfaces.pdf
FRAGMENTS := $(wildcard fragments/*/*)
TEXSMITH  := uv run texsmith

.PHONY: all run pdf clean

all: $(PROGRAMS)

$(BUILDDIR)/%: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $< -o $@

run: $(PROGRAMS)
	@for p in $(PROGRAMS); do echo "== $$p"; ./$$p; done

pdf: $(PDF)

$(PDF): td-interfaces.md $(FRAGMENTS) pyproject.toml
	$(TEXSMITH) $< -o $(BUILDDIR)/ --build

clean:
	rm -rf $(BUILDDIR)
