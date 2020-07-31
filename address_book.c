/* address_book.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DATA {
	char name[32];
	char tel[32];
	char address[64];
}MYDATA, *LPMYDATA;


int menu();
int data_input();
int data_output();

int main() {
	int select_No, loopend = 0;

	MYDATA mydata[10];
	LPMYDATA lpMydata = mydata;

	while (1) {
		select_No = menu();

		switch (select_No) {
		case 1:
			data_input(lpMydata);
			break;
		case 2:
			data_output(lpMydata);
			break;
		default :
			loopend = 1;
			break;
		}
		if (loopend)
			break;
	}
	return 0;
}

int menu() {
	char ret[8];

	printf("*****MENU*****\n");
	printf("1: Data Input\n");
	printf("2: Data Output\n");
	printf("0: End\n");
	printf("**************\n");
	printf("--->");
	gets(ret);

	return atoi(ret);
}

int data_input(LPMYDATA lpData) {
	char strno[8];
	int no;

	printf("Which data do you want to input?(0-9)\n");
	gets(strno);
	if (strno[0] < '0' || strno[0] > '9') {
		printf("Invalid input\n");
		return -1;
	}
	strno[1] = '\0';
	no = atoi(strno);

	printf("Name---");
	gets((lpData + no)->name);
	printf("Tel---");
	gets((lpData + no)->tel);
	printf("Address---");
	gets((lpData + no)->address);

	return 0;
}

int data_output(LPMYDATA lpData) {
	char strno[8];
	int no;

	printf("Which data do you want to read?(0-9)\n");
	gets(strno);
	if (strno[0] < '0' || strno[0] > '9') {
		printf("Invalid input\n");
		return -1;
	}
	strno[1] = '\0';
	no = atoi(strno);

	if (!strcmp(lpData->name, "")) {
		printf("No Data\n");
		return -1;
	}
	printf("Name--- %s\n", (lpData + no)->name);
	printf("Tel--- %s\n", (lpData + no)->tel);
	printf("Address--- %s\n", (lpData + no)->address);

	return 0;
}