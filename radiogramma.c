#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TOTAL_SYMBOLS		1680
#define NUMBER_OF_LEADERS   7
#define SIZE_OF_RECORD_IN_SYMBOLS   (TOTAL_SYMBOLS/NUMBER_OF_LEADERS) //240
#define MAX_SIZE_UP_PHONE   11

#ifndef SIZE_OF_CHAR
	#define SIZE_OF_CHAR  8
#endif

#define TOTAL_LETTERS       (TOTAL_SYMBOLS/SIZE_OF_CHAR) //210
#define MAX_SIZE_PHONE      (SIZE_OF_CHAR * MAX_SIZE_UP_PHONE)  //88
#define MAX_SIZE_NAME       (SIZE_OF_RECORD_IN_SYMBOLS - MAX_SIZE_PHONE) //152

#define MAX_SIZE_UP_NAME    (MAX_SIZE_NAME/SIZE_OF_CHAR) //19

#define ERROR_FILE_OPEN     -1

#define ASCII_OFFSET        48

typedef struct
{
	char up_name[MAX_SIZE_UP_NAME];
	char up_phone[MAX_SIZE_UP_PHONE];
} Persone;

int read_leaders(char* all_simbols);
void c_to_bin(char* all_simbols);
char to_digit(char c);
void bin_to_ASCII(const char* const all_simbols, char* simbols_in_ASCII);
int power (int base, int degree);
void put_simbols_in_struct(const char* const simbols_in_ASCII, Persone* p_leaders);
void print_leaders (int num, const Persone* const p_leaders);

int main()
{
	char simbols[TOTAL_SYMBOLS];
	char* all_simbols = simbols;

	char ASCII_simb[TOTAL_LETTERS];
	char* simbols_in_ASCII = ASCII_simb;

	int is_read = read_leaders(all_simbols);	
	if(is_read == ERROR_FILE_OPEN)
	{
		printf("Error opening file");
		return ERROR_FILE_OPEN;
	}

	c_to_bin(all_simbols);

	Persone leaders[NUMBER_OF_LEADERS];
	Persone* p_leaders = leaders;
	
	bin_to_ASCII(all_simbols, simbols_in_ASCII);
	put_simbols_in_struct(simbols_in_ASCII, p_leaders);
	
	print_leaders(NUMBER_OF_LEADERS, p_leaders);
	
	return 0;
}

int read_leaders(char* all_simbols)
{
	FILE *my_file = NULL;
	my_file = fopen("C:/Users/UserPC/Desktop/c++/rd/radiogramma/data.dat", "r");
	
	if (my_file == NULL)
	{
        return ERROR_FILE_OPEN;
    }
    
    int fread_res = fread(all_simbols, sizeof(char), TOTAL_SYMBOLS, my_file);
	fclose(my_file);
	return 0;
}

void c_to_bin(char* all_simbols)
{
	for(unsigned int i = 0; i < TOTAL_SYMBOLS; i++)
	{
		all_simbols[i] = to_digit(all_simbols[i]);
	}
}

char to_digit (char c)
{
	return (c - ASCII_OFFSET);
}

void bin_to_ASCII(const char* const all_simbols, char* simbols_in_ASCII)
{
	int max = SIZE_OF_CHAR;
    int min = 0;

   	for(unsigned int i = 0; i < TOTAL_LETTERS; i++)
	{
		simbols_in_ASCII[i] = 0;
		for(unsigned int j = max; j > min; j--)
		{
			simbols_in_ASCII[i] += all_simbols[j - 1] * power(2, max - j);
		}
		max += SIZE_OF_CHAR;
   		min += SIZE_OF_CHAR;
	}
}

int power (int base, int degree)
{
	int new_base = 1;
	for (unsigned int i = 0; i < degree; i++)
	{
		new_base *= base;
	}
	return new_base;
}

void put_simbols_in_struct(const char* const simbols_in_ASCII, Persone* p_leaders)
{
	int min = 0;
	int max = MAX_SIZE_UP_NAME;

	for (unsigned int n = 0; n < NUMBER_OF_LEADERS; n++)
	{
		for (unsigned int i = min; i < max; i++)
		{
			p_leaders[n].up_name[i] = simbols_in_ASCII[i];
			printf("%c", p_leaders[n].up_name[i]);
		}
		for (unsigned int i = max; i < (max + MAX_SIZE_UP_PHONE); i++)
		{
			p_leaders[n].up_phone[i] = simbols_in_ASCII[i];
			printf("%c", p_leaders[n].up_phone[i]);	
		}
		min = max + MAX_SIZE_UP_PHONE;
		max = min + MAX_SIZE_UP_NAME;
		printf("\n");
	}
}

void print_leaders (int num, const Persone* const p_leaders)
{
	
}