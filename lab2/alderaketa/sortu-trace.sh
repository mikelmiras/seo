# Trazen sorrera automatitzatzeko script-a(hiru programazio lengoaietan)
# Parametro bat jaso dezake; zenbat zenbaki idatzi behar duten
# Parametrorik jaso ezezean, behin baino ez da idazten.

KOP=1       # Segidaren bukaera: defektuzko balioa (1)
if [ $# -eq 1 ]
then
  KOP=$1    # Parametroa jasoz gero, jaso (zenbakia izan behar du!)
fi
# 'write' sistema-deien inguruko informazioa jasotzeko komandoa
STRACE_WRITE="/usr/bin/strace -f -e trace=write -qq -q"
# emaitza gordeko den fitxategien izenen patroia
KOPTEXT=$(printf "%08d\n" $KOP)

# Programazio lengoaia bakoitzeko:
# - Lortu exkuzioaren sistema-deiak (strace programa kop)
# - Idazten den balio segida (1 2 3 ... ) ez erakutsi pantailan (>/dev/null)
# - Eskuratu soilik irteera estandarrean idazten duten sistema-deiak (grep 'write(1')
# - Gorde emaitzak 'trace-kop-lengoia' patroia duen fitxategi batean
# programen irteera (1 2 ...) ez da interesgarria, beraz, /dev/null dispositibora
echo "C-ko programaren exekuzioa:"
komandoa="$STRACE_WRITE ./segida    $KOP 2>&1 >/dev/null | grep 'write(1' >trace-${KOPTEXT}-c"    # Java-rako
echo -e "\t- $komandoa"
bash -c "$komandoa"
echo -e "\t- Sortutako fitxategia: trace-${KOPTEXT}-c ($(wc -l trace-${KOPTEXT}-c | cut -d" " -f1) lerro)"

echo "Python-eko programaren exekuzioa:"
komandoa="$STRACE_WRITE python3 seguida.py $KOP 2>&1 >/dev/null | grep 'write(1' >trace-${KOPTEXT}-py"    # Python-rako
echo -e "\t- $komandoa"
bash -c "$komandoa"
echo -e "\t- Sortutako fitxategia: trace-${KOPTEXT}-py ($(wc -l trace-${KOPTEXT}-py | cut -d" " -f1) lerro)"

echo "Java-ko programaren exekuzioa:"
komandoa="$STRACE_WRITE java seguida $KOP 2>&1 >/dev/null | grep 'write(1' >trace-${KOPTEXT}-java"    # Java-rako
echo -e "\t- $komandoa"
bash -c "$komandoa"
echo -e "\t- Sortutako fitxategia: trace-${KOPTEXT}-java ($(wc -l trace-${KOPTEXT}-java | cut -d" " -f1) lerro)"
