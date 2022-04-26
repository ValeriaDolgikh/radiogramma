#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TOTAL_SYMBOLS		1680
#define NUMBER_OF_LEADERS   7
#define SIZE_OF_RECORD_IN_SYMBOLS   (TOTAL_SYMBOLS/NUMBER_OF_LEADERS)
#define MAX_SIZE_UP_PHONE   11

#ifndef SIZE_OF_CHAR
	#define SIZE_OF_CHAR  8
#endif

#define MAX_SIZE_PHONE      (SIZE_OF_CHAR * MAX_SIZE_UP_PHONE)
#define MAX_SIZE_NAME       (SIZE_OF_RECORD_IN_SYMBOLS - MAX_SIZE_PHONE)

#define MAX_SIZE_UP_NAME    (MAX_SIZE_NAME/SIZE_OF_CHAR)

#define ERROR_FILE_OPEN     -1

#define ASCII_OFFSET        48

typedef struct
{
	char name[MAX_SIZE_NAME];
	char phone[MAX_SIZE_PHONE];
} Persone;

typedef struct
{
	char up_name[MAX_SIZE_UP_NAME];
	char up_phone[MAX_SIZE_UP_PHONE];
} up_Persone;

int read_leaders(char* all_simbols);
void c_to_bin(char* all_simbols);
char to_digit(char c);
void bin_to_ASCII(const char* const all_simbols, up_Persone* up_p_leaders);
int power (int base, int degree);
void print_leaders (int num, const up_Persone* const up_p_leaders);

int main()
{
	char simbols[TOTAL_SYMBOLS];
	char* all_simbols = simbols;

	int is_read = read_leaders(all_simbols);	
	if(is_read == ERROR_FILE_OPEN)
	{
		printf("Error opening file");
		return ERROR_FILE_OPEN;
	}

	for (unsigned int i = 0; i < TOTAL_SYMBOLS; i++)
	{
		//all_simbols[i] *= (-1);
		printf("%c ", all_simbols[i]);
	}

	c_to_bin(all_simbols);

	/*for (unsigned int i = 0; i < TOTAL_SYMBOLS; i++)
	{
		//all_simbols[i] *= (-1);
		printf("%d ", all_simbols[i]);
	}*/
	
	/*Persone leaders[NUMBER_OF_LEADERS];
	Persone* p_leaders = leaders;*/
	up_Persone up_leaders[NUMBER_OF_LEADERS];
	up_Persone* up_p_leaders = up_leaders;
	
	bin_to_ASCII(all_simbols, up_p_leaders);
	//print_leaders(NUMBER_OF_LEADERS, up_p_leaders);
	
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
    printf("FREAD = %d\n", fread_res);
    printf("sizeof char = %d\n", sizeof(char));
    printf("TOTAL_SYMBOLS = %d\n", TOTAL_SYMBOLS);
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

void bin_to_ASCII(const char* const all_simbols, up_Persone* up_p_leaders)
{
	for (unsigned int n = 0; n < NUMBER_OF_LEADERS; n++)
	{
		for(unsigned int j = 0; j < MAX_SIZE_UP_NAME; j++)
		{
			int max = SIZE_OF_CHAR;
    		int min = 0;
    		while (max <= MAX_SIZE_NAME)
    		{
    			for (unsigned int i = max; i > min; i--)
    			{
        			up_p_leaders[n].up_name[j] += all_simbols[i - 1] * power(2, max - i);
    			}
    			max += SIZE_OF_CHAR;
    			min += SIZE_OF_CHAR;
    		}
		}

		for(unsigned int j = 0; j < MAX_SIZE_UP_PHONE; j++)
		{
			int max = SIZE_OF_CHAR;
    		int min = 0;
    		while (max <= MAX_SIZE_PHONE)
    		{
    			for (unsigned int i = max; i > min; i--)
    			{
        			up_p_leaders[n].up_phone[j] += all_simbols[i -1] * power(2, max - i);
    			}
    			max += SIZE_OF_CHAR;
    			min += SIZE_OF_CHAR;
    		}
		}
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

void print_leaders (int num, const up_Persone* const up_p_leaders)
{
	/*for (unsigned int i = 0; i < num; i++)
	{
		printf("%s ", up_p_leaders[i].up_name);
		printf("%s\n", up_p_leaders[i].up_phone);
	}*/

	for (unsigned int i = 0; i < num; i++)
	{
		for (unsigned int j = 0; i < MAX_SIZE_UP_NAME; j++)
		{
			printf("%c", up_p_leaders[i].up_name[j]);
		}
		printf("   ");
		for (unsigned int j = 0; i < MAX_SIZE_UP_PHONE; j++)
		{
			printf("%c\n", up_p_leaders[i].up_phone[j]);
		}
	}
	
}