#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define BSIZE 300

int main(int argc, char *argv[])
{
	time_t now;
	struct tm *clock;
	char time_string[64];
	const char filename[] = "/home/gaurav-palariya/Documents/git_hub/Projects/Daily_Greetings/pithy.txt";
	FILE *fp;
	char buffer[BSIZE];
	int items;
	int allocLength;
	char *entry;
	char **list;
	int sayings;

	time(&now);
	clock = localtime(&now);

	strftime(time_string, 64, "Today is %A, %B %d, %Y%nIt is %r%n", clock);
	fp = fopen(filename, "r");
	if(fp == NULL)
	{
		fprintf(stderr, "Unable to open file %s\n", filename);
		exit(1);
	}
	
	items = 0;
	allocLength = 100;
	list = malloc(sizeof(char *) * allocLength);
	if(list == NULL) 
	{
		fprintf(stderr, "Unable to allocate memory\n");
		exit(1);
	}

	while((fgets(buffer, BSIZE, fp)) != NULL) {
		entry = malloc(sizeof(char) * BSIZE);
		if(entry == NULL) {
			fprintf(stderr, "Unable to allocate memory\n");
			exit(1);
		}

		strcpy(entry, buffer);
		if(items == allocLength) {
			allocLength += 100;
			list = realloc(list, sizeof(char *) * allocLength);
			if(list == NULL)
			{
				fprintf(stderr, "Unable to allocate memory\n");
				exit(1);
			}
		}

		list[items++] = entry;
	}
	srand((unsigned int)time(NULL));
	sayings = rand() % items;

	printf("Greetings");
	if(argc > 1)
		printf(", %s", argv[1]);
	printf("!\n%s", time_string);
	printf("%s", list[sayings]);
	return 0;
}
		
