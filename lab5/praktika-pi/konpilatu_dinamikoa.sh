# liburutegi dinamikorako objektu fitxategia sortu
echo gcc -fPIC -c pi_kalkulatu.c -o pi_kalkulatu_dinamikoa.o
gcc -fPIC -c pi_kalkulatu.c -o pi_kalkulatu_dinamikoa.o

# liburutegi dinamikoa sortu
echo ld -shared -soname libfuntzioa.so.1 -o libfuntzioa.so.1.0 -lc pi_kalkulatu_dinamikoa.o
ld -shared -soname libfuntzioa.so.1 -o libfuntzioa.so.1.0 -lc pi_kalkulatu_dinamikoa.o
/sbin/ldconfig -v -n .
ln -sf libfuntzioa.so.1 libfuntzioa.so

# programaren bertsio dinamikoa sortu
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
echo gcc pi_test.c -o pi_test_dinamikoa -L. -lfuntzioa
gcc pi_test.c -o pi_test_dinamikoa -L. -lfuntzioa
