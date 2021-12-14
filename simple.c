// u can compile this with : 
//gcc -fno-pic -static -fno-builtin -fno-omit-frame-pointer simple.c

int main(int argc, char** argv){
	int x = 5;
	int y = 13;
	return x + y;
}

/*
gcc -c -fno-pic -static -fno-builtin -fno-omit-frame-pointer test1.c
ld -N -e main -Ttext 0 -o test1 test1.o

*/
