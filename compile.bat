gcc.exe -c main.c -o main.o
gcc.exe -c drawdigit.c -o drawdigit.o
gcc.exe -c updatedigit.c -o updatedigit.o
windres.exe -i resource.rc --input-format=rc -o CounterResource.res -O coff 
gcc.exe main.o drawdigit.o updatedigit.o CounterResource.res -o Counter.exe -static-libgcc -mwindows