#include "Stegano_header.h"

int main(int argc,char *argv[])
{
    int i;
    char *argv_2,*argv_3,*argv_4;

    switch(argc)
    {
	case 8 :	if(!strcmp(argv[1],"-E"))
			    for (i = 2; i < 8; i++)
			    {
				if (!strcmp(argv[i],"-i"))
				    argv_2 = argv[i+1];

				if (!strcmp(argv[i],"-s"))
				    argv_3 = argv[i+1];

				if (!strcmp(argv[i],"-o"))
				    argv_4 = argv[i+1];
			    }			    
			    Encoding(argv_2, argv_3, argv_4);
			    break;
	
	default : 
		printf("\tError !!\n\n");
		printf("\n\t\tFor encoding type the command==> \t./a.out -E -i <input.bmp> -s <secret.txt> -o <output.bmp>\n\n");
    }	
    return 0;
}

