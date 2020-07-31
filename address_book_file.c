/* address_book_file.c */

#define FNAME "meibo.txt"
#define RECORDLEN 88

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int menu();
int myread();
int mywrite();
int myrewrite();
int mysearch(char *);

char *format = "%-15s %-3d %-2s %-63s\n";

int main() {
	int menuno;

	while (1) {
		menuno = menu();
		switch (menuno) {
		case 0:
			break;
		case 1:
			mywrite();
			break;
		case 2:
			myread();
			break;
		default:
			printf("Invalid access\n");
			break;
		}
		if (!menuno)
			break;
	}

	return 0;
}

int menu() {
	char ret[8];

	while (1) {
		printf("*******************\n");
		printf("1: Data Input\n");
		printf("2: Data Output\n");
		printf("0: End\n");
		printf("*******************\n");
		printf("choise->");
		fgets(ret, sizeof(ret), stdin);
		ret[1] = '\0';
		if (ret[0] < '0' || ret[0] > '3') {
			printf("Invalid number\n");
			continue;
		}
		return atoi(ret);
	}
}

int mywrite() {
	FILE *fp;
	char name[16], sex[4], address[64], buffer[8];
	int age;

	fp = fopen(FNAME, "a");
	if (fp == NULL) {
		perror("couldn't open the file\n");
		return -1;
	}

	while (1) {
		printf("Name---");
		fgets(name, sizeof(name), stdin);
		name[strlen(name) - 1] = '\0';
		printf("Age---");
		fgets(buffer, sizeof(buffer), stdin);
		age = atoi(buffer);
		printf("Sex(M/F)---");
		fgets(sex, sizeof(sex), stdin);
		sex[strlen(sex) - 1] = '\0';
		printf("Adress---");
		fgets(address, sizeof(address), stdin);
		address[strlen(address) - 1] = '\0';

		if (fprintf(fp, format, name, age, sex, address) < 0) {
			perror("Writing error occured.\n");
			break;
		}
		printf("Do you want to continue to write?(y/n):");
		fgets(buffer, sizeof(buffer), stdin);
		if (buffer[0] == 'n' || buffer[0] == 'N')
			break;
	}

	fclose(fp);
	return 0;
}

int myread() {
	char search[16], yesno[8];

	yesno[0] = 'Y';

	while(yesno[0] == 'y' || yesno[0] == 'Y'){
		printf("The target name--");
		fgets(search, sizeof(search), stdin);
		search[strlen(search) - 1] = '\0';
		int result = mysearch(search);
		printf("Do you want to continue to search?(y/n)");
		fgets(yesno, sizeof(yesno), stdin);
	}
	return 0;
}

int mysearch(char *target) {
	FILE *fp;
	char name[16], sex[4], address[64], buffer[8];
	int no = 0, age;

	fp = fopen(FNAME, "r");

	if (fp == NULL) {
		perror("The file could not opened\n");
		return -1;
	}


	while (1) {

		fseek(fp, RECORDLEN * no++, SEEK_SET);
		
		if (fscanf(fp, "%s", name) == EOF) {
			break;
		}

		if (strstr(name, target) != NULL) {
			fscanf(fp, "%d", &age);
			fscanf(fp, "%s", sex);
			fscanf(fp, "%s", address);
			printf("Name: %s\n", name);
			printf("Age: %d\n", age);
			printf("Sex: %s\n", sex);
			printf("Address: %s\n", address);
			printf("----------------------\n");
			break;
		}
	}

	fclose(fp);
	no--;
	return no;
}
