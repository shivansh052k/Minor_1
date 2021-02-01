//reading size of image file
int size_of_image(FILE *fp1)
{
	int width, height;

	fseek(fp1, 0x12, SEEK_SET);	
	fread(&width, sizeof(int), 1, fp1);	
	fread(&height, sizeof(int), 1, fp1);	
	printf("Size of the input image is %d x %d \n", width, height);
	fseek(fp1, 0L, SEEK_SET);

	return ((width * height * 3) / 8);
}
//Entering Secret Message to file
void secret_text(FILE *fp2)
{
	char ch;
	while ((ch = getchar())!=EOF)
	{
		putc(ch,fp2);	//puts secret text to file
	}
}

//Size Of The Secret Message
int secret_text_size(FILE *fp2)
{
	int size_txt;
	fseek(fp2, 0L, SEEK_END);
	size_txt = ftell(fp2);
	fseek(fp2, 0L, SEEK_SET);
	return size_txt;
}

//bits of text file
int get_bit(char byte, int bit)
{
	return ((byte >> 8 - bit) & 1);
}

//encription of message
void stega_encrypt(FILE *fp1, FILE *fp2, FILE *fp3)
{
	//temp var for one byte from file and msg
	char file_buff = 0, msg_buff = 0, ch;	
	
	int i;
	int bit_msg;
	while((msg_buff = fgetc(fp2)) != EOF)
	{
		for(i = 1; i <= 8; i++)
		{
			file_buff = fgetc(fp1);

			int file_byte_lsb = (file_buff & 1);

			bit_msg = get_bit(msg_buff, i);

			if(file_byte_lsb == bit_msg)
			{
				fputc(file_buff, fp3);
			}
			else
			{
				if(file_byte_lsb == 0)
					file_buff = (file_buff | 1);
				else
					file_buff = (file_buff ^ 1);

				fputc(file_buff, fp3);
			}
		}
	}

	/*copying rest of data */
	while(!feof(fp1))
	{
		char tmp_cpy = fgetc(fp1);
		fputc(tmp_cpy,fp3);

	}

	if(msg_buff == EOF)
		printf("\nEncryption is Successfull\n");
	else
		printf("\nEncryption is Failed\n");
}
//Encription For Strings
void string_encrypt(char *str,FILE *fp1, FILE *fp3)
{

	char file_buff, msg_buff;	//temp var for one byte from file and msg
	int i, j = 0;
	int bit_msg;
	while((msg_buff = str[j]) != '\0')
	{
		for(i = 1; i <= 8; i++)
		{
			file_buff = fgetc(fp1);

			int file_byte_lsb = (file_buff & 1);

			bit_msg = get_bit(msg_buff, i);

			if(file_byte_lsb == bit_msg)
			{
				fputc(file_buff, fp3);
			}
			else
			{
				if(file_byte_lsb == 0)
					file_buff = (file_buff | 1);
				else
					file_buff = (file_buff ^ 1);

				fputc(file_buff, fp3);
			}
		}
		j++;
	}
}
//Encription For Numbers
void size_encrypt(int num,FILE *fp1, FILE *fp3)
{

	char file_buff;	
	int i, j = 0;
	int bit_msg;

	for(i = 1; i <= 8; i++)
	{
		file_buff = fgetc(fp1);

		int file_byte_lsb = (file_buff & 1);

		bit_msg = get_bit(num, i);

		if(file_byte_lsb == bit_msg)
		{
			fputc(file_buff, fp3);
		}
		else
		{
			if(file_byte_lsb == 0)
				file_buff = (file_buff | 1);
			else
				file_buff = (file_buff ^ 1);

			fputc(file_buff, fp3);
		}
	}

}

int Encoding(char *argv_2,char *argv_3,char *argv_4)
{
	FILE *fp1, *fp2, *fp3;

	//opening Image File
	if((fp1 = fopen(argv_2, "r+")) == NULL) 
	{
		printf("Could not open file %s.\n\n", argv_2);
		return 1;
	}

	int size_image = size_of_image(fp1);
	printf("Total %d Charecters can be stored in %s.\n", size_image, argv_2);

	//opening secret text file
	fp2 = fopen(argv_3, "w+");

	//Entering secret text to file
	printf("Enter the text and Press CTRL + D To Stop : \t");
	secret_text(fp2);

	int size_txt = secret_text_size(fp2);
	printf("\nSize of the entered Message is ==> %d\n", size_txt);

	//Comparing Image Size With Text
	if(size_image < size_txt)
	{
		printf("\n***Size of Message is larger then allowed size***\n");
		return 1;
	}

	//opening destination file
	fp3 = fopen(argv_4, "w+");
	if (fp3== NULL) 
	{
		fprintf(stderr, "Unable to give output file %s\n",argv_4);
		exit(1);
	}
	
	//copying 54 header file
	int i, c = 0;
	char tmp_cpy;
	//Beginning of the file
	rewind(fp1);	
	for(i = 0;i < 54; i++)
	{
		tmp_cpy = fgetc(fp1);
		fputc(tmp_cpy,fp3);
		c++;
	}
	
	//Encryption for Message
	size_encrypt(size_txt,fp1,fp3);
	stega_encrypt(fp1,fp2,fp3);

	/*Clean up before exit */
	fclose(fp1);	
	fclose(fp2);
	fclose(fp3);

	return 0;

}
