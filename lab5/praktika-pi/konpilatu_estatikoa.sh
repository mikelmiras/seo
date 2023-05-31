# liburutegi estatikorako objektu fitxategia sortu
echo gcc -c pi_kalkulatu.c -o pi_kalkulatu_estatikoa.o
gcc -c pi_kalkulatu.c -o pi_kalkulatu_estatikoa.o

# liburutegi estatikoa sortu
echo ar rcs libfuntzioa.a pi_kalkulatu_estatikoa.o
ar rcs libfuntzioa.a pi_kalkulatu_estatikoa.o

# programaren bertsio estatikoa sortu
echo gcc -static pi_test.c -L. -lfuntzioa -o pi_test_estatikoa
gcc -static pi_test.c -L. -lfuntzioa -o pi_test_estatikoa
