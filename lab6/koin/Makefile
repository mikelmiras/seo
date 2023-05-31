# modulu nagusiaren objektu kodea sortu
koin.o: koin.c koin_config.h koin_aux.h
	gcc -W -c koin.c

# koin_aux.c moduluaren objektu kodea sortu
koin_aux.o: koin_aux.c koin_config.h
	gcc -W -c koin_aux.c

# Moduluen objektu kodeak estekatu exekutagarria sortzeko
koin: koin.o koin_aux.o
	gcc -W koin.o koin_aux.o -o koin

clean:
	rm -f koin koin.o koin_aux.o
