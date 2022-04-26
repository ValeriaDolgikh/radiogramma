#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE_NAME  128
#define MAX_SIZE_PHONE 112
#define ERROR_FILE_OPEN -1
#define NUMBER_OF_LEADERS 7

typedef struct
{
	char name[MAX_SIZE_NAME];
	char phone[MAX_SIZE_PHONE];
} Persone;

void print_leaders (int num, const Persone* const p_leaders);
int read_leaders(int num, Persone* p_leaders);

int main()
{
	Persone leaders[NUMBER_OF_LEADERS];
	Persone* p_leaders = leaders;
	
	int is_read = read_leaders(NUMBER_OF_LEADERS, p_leaders);	
	if(is_read == ERROR_FILE_OPEN)
	{
		printf("Error opening file");
		return ERROR_FILE_OPEN;
	}
	

	print_leaders(NUMBER_OF_LEADERS, p_leaders);
	
	return 0;
}

void print_leaders (int num, const Persone* const p_leaders)
{
	for (unsigned int i = 0; i < num; i++)
	{
		printf("%s ", p_leaders[i].name);
		printf("%s\n", p_leaders[i].phone);
	}
	
}

int read_leaders(int num, Persone* p_leaders)
{
	FILE *my_file = NULL;
	my_file = fopen("C:/Users/UserPC/Desktop/c++/radiogramma/radiogramma.dat", "rb");

	if (my_file == NULL)
	{
        return ERROR_FILE_OPEN;
    }
    
    int pos = 0;
    
	for (unsigned int i = 0; i < NUMBER_OF_LEADERS; i++)
	{
		fseek(my_file, pos, SEEK_SET);
		fread(&p_leaders[i], sizeof(Persone), 1, my_file);
		pos = ftell(my_file);
	}

	fclose(my_file);
	return 0;
}