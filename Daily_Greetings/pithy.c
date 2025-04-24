#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BSIZE 256

int main()
{
	const char filename[] = "pithy.txt";
	FILE *fp;
	char buffer[BSIZE];
	int items;
	int allocLength;
	char *entry;
	char **list;
	int sayings;
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
	printf("items : %d\n", items);	
	srand((unsigned int)time(NULL));
	sayings = rand() % items;
	printf("%s", list[sayings]);

	return 0;
}
