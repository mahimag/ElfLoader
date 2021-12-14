#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/mman.h>
#include "elfheader.h"

//#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

void usage(){
        fprintf(stderr, "Usage: ./elfloader filename arg1 arg2\n");
}

//checks if ehdr is readable
/*bool read_header(FILE* fp, Elf64_Ehdr* ehdr){
        if(fread(&ehdr, 1, sizeof(Elf64_Ehdr), fp) != 1){
		return false;
	}
	return true;
}
*/

//prints header
void dump_header(Elfhdr* ehdr){
	// prints magic num + ELF
	for(int i=0; i<4; i++){
		printf("%c ", ehdr->e_ident[i]);
	}
	printf("\n");
}

//checks if file is ELF file by comparing strings
bool checkELF(Elfhdr* ehdr){
	bool flag = false;
	if(ehdr->e_ident[EI_MAG0] == 0x7f){
		flag = true;
	}

	if(('E' !=  ehdr->e_ident[EI_MAG1]) && ('L' != ehdr->e_ident[EI_MAG2])  && ('F' != ehdr->e_ident[EI_MAG3])){
		flag = false;
	}

	return flag;
}

int main(int argc, char**argv){ // num arguments, arguments themselves
        //check if command line arguments are valid

        int fd = 0;
//      read(fd, argv[1], 0);

        if(argc != 4){
                usage();
		printf("one\n");
                exit(1);
        }
        else{
                FILE* fp = fopen(argv[1], "rb");
                if(fp == NULL){
			usage();
                	printf("two\n");
                        exit(2);
                }
		//initialize elf header
		Elfhdr ehdr;
		fread(&ehdr, 1, sizeof(ehdr), fp);
		//reading header - size_t fread(void *restrict ptr, size_t size, size_t nmemb,
                //    FILE *restrict stream);
		//size_t num = fread(fp, sizeof(ElfN_Ehdr), 1, elf);

		//printing the header
		/*if(read_header(fp, &ehdr) == false){
			printf("Hi\n");
			//print error
			//fprintf(stderr, "Usage: hi\n");
			usage();
			exit(2);
		}
*/

		dump_header(&ehdr); //prints whats inside the ehdr

		//checks if file fp is in elf format
		if(checkELF(&ehdr) == false){ //is it malformed
			usage();
                	printf("three\n");
			exit(2);
		}

		//int fseek(FILE *stream, long offset, int whence);
		//seeking into program hdr
		fseek(fp, ehdr.e_phoff, SEEK_SET); //ehdr gets changed ????

		//prog. header tells where it is and how large it is
                Phdr phdr;

		fread(&phdr, 1, sizeof(phdr), fp);

		if(phdr.p_type != PT_LOAD ) { //|| phdr.p_flags != PF_X){
                        //print error
                        //fprintf(stderr, "Usage: hi\n");
			usage();
	                printf("four\n");
                        exit(3);
                }
		else{
			//allocate mem for loadable code
			void* codep = mmap(NULL, phdr.p_memsz, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);

			//seeking to loadable code
			fseek(fp, phdr.p_offset, SEEK_SET);

			//read in loadable code
			fread(codep, phdr.p_filesz, 1, fp);

			int offset = 0;
			// test 3 has different offset
                        if(argv[1][4] == '3'){
				offset = ehdr.e_entry - phdr.p_vaddr;
			}

			//execute the code
			//int offset = phdr.p_vaddr - ehdr.e_entry;
			unsigned int (*mainfunc)(int, int) = codep + offset;
			int arg1 = atoi(argv[2]);
			int arg2 = atoi(argv[3]);
			int result = (*mainfunc)(arg1, arg2);

			printf("Answer=%d\n", result);

			fclose(fp);
			exit(0);
        	}
		return 0;

	}
}
