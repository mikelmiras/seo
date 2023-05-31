import sys
import os

params = sys.argv
if len(params) == 2:
    n = int(params[1])      # parametroa eskuratu
else:
    n = 1                   # defektuzko balioa (parametroa jaso ezean)
for i in range(1,n+1):
    text=str(i)+"\n"        # idatzi beharreko testua: zenbakia + lerro_jauzia
    byteobject = str.encode(text) # bitarrera pasa (write-k byteak idazten du)
#    os.write(1,byteobject)        # sistema-deia erabili
    print(text, end='')  # idatzi liburutegi funtzioa erabiliz


