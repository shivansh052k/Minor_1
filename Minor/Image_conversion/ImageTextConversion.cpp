#include <stdio.h>
#include <string>
#include <bitset>
#include <iostream>
using namespace std;

char bytefromtext(unsigned char* text)
{   
    char result = 0;
    for(int i=0;i<8;i++)
    {
        if(text[i]=='1')
        {
            result |= (1 << (7-i));
        }
    }
    return result;
}

int main(int argc, char*argv[]){

FILE *ptr_bmp_in;
FILE *ptr_text_out;
int c;
int j=0;

ptr_bmp_in=fopen("linux.bmp","rb");
ptr_text_out=fopen("Text.txt","w");

if(!ptr_bmp_in)
{
    printf("Unable to open file\n");
    return 1;
}

while((c=fgetc(ptr_bmp_in)) != EOF)
    {
        for(int i=0;i<=7;i++)
        {
            if(c&(1<<(7-i)))
            {
                fputc('1',ptr_text_out);
            }
            else
            {
                fputc('0',ptr_text_out);
            }
        }
    }
	
    
    fclose(ptr_bmp_in);
    fclose(ptr_text_out);
    printf("Image to Binary Conversion Completed done\n");
    

  	string myString;
  	cout<<"Enter the String:\n";
  	cin>>myString;
	cout<<"Converted String to binary is:\n";
  	for (std::size_t i = 0; i < myString.size(); ++i)
  	{
      	cout<< bitset<8>(myString.c_str()[i])<< endl;
  	}

    return 0;
}
