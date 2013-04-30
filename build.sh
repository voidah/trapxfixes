rm -f *.so
g++ -fPIC -c *.cc
g++ -shared -o trapxfixes.so *.o
rm -f *.o
