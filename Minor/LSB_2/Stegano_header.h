#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Encode.c"


//reading size of image file
int size_of_image(FILE *fp1);

//Entering Secret Message to file
void secret_text(FILE *fp2);

//Size Of The Secret Message
int secret_text_size(FILE *fp2);

//bits of text file
int get_bit(char byte, int bit);

//encription of message
void stega_encrypt(FILE *fp1, FILE *fp2, FILE *fp3);

//Encription For Strings
void string_encrypt(char *str,FILE *fp1, FILE *fp3);

//Encription For Numbers
void size_encrypt(int num,FILE *fp1, FILE *fp3);

