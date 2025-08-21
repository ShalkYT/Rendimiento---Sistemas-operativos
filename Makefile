GCC = gcc
BIBLIOTECAS =
MODULOS =

PROGRAMAS = Rendimiento

all: $(PROGRAMAS)

Rendimiento:
	$(GCC) $(MODULOS) $@.c -o $@

clear:
	rm -f $(PROGRAMAS)
