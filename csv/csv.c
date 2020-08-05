/* csv.c */

/*
This program does these functions.
1. Reading the data from csv file.
2. Input those data which to array of structs.
3. Edit or just output the data of those array.
4. Save those changes to  csv file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FNAME "meibo.csv"

char *format = "%d,%s,%d,%s\n";

typedef struct Record {
	//ID
	int idx;
	//Name
	char name[32];
	//TEL number
	int tel;
	//address of the person
	char address[64];
	// Next Address
	struct Record *next;
} Record_t ;

Record_t *head = NULL;
Record_t *tail = NULL;

int menu();
Record_t* createNode(void);
Record_t* node_input();
void node_output(void);
void insertNodeToList(void);
void deleteNodeFromList(void);
void editNodeFromList(void);
void printList(void);
void sortNode(void);
int compare(const Record_t*, const Record_t*);
Record_t* sort(Record_t*);
void printNode(char s[32]);
void setRecord(char* str);
void resetRecord(FILE* fp);

int main() {
	int menu_no, loopend = 0;
	char str[255];
	Record_t record[255];
	Record_t* sorted[255];
	
	int i = 0, size;
	// fopen(�t�@�C����, �I�v�V����)�Ńt�@�C�����J���܂�
	FILE* fpr = fopen(FNAME, "r");
	
	// �t�@�C�����J���Ȃ��ꍇ�AFILE�̃|�C���^��NULL�ɂȂ�܂�
	if (fpr == NULL) {
		puts("Failed to open");
		return EXIT_FAILURE;
	}


	// fgets(�ǂݍ��ރo�b�t�@, �o�b�t�@�̃T�C�Y, FILE�̃|�C���^)�ň�s���ǂݍ��݂܂�
	while (fgets(str, 255, fpr)) {
		// �ǂݍ��񂾓��e�����̂܂܏o��
		// �|�C���g�P �ǂݍ��񂾃e�L�X�g���A�������č\���̂̔z��ɐݒ肵�܂��B
		// Record�\���̂Ƀf�[�^��ݒ�
		setRecord(str);
	}

	// �t�@�C�����N���[�Y
	fclose(fpr);

	// �o�͗p�|�C���^�z���Record�̃|�C���^�����ׂĐݒ肷��
	for (i = 0; i < size; i++) {
		sorted[i] = &record[i];
	}

	/*�e�֐��̌Ăяo��*/
	while (1) {
		menu_no = menu();

		switch (menu_no) {
		case 1:
			node_input();
			break;
		case 2:
			node_output();
			break;
		case 3:
			insertNodeToList();
			break;
		case 4:
			deleteNodeFromList();
			break;
		case 5:
			editNodeFromList();
			break;
		case 6:
			printList();
			break;
		case 7:
			sortNode();
			break;
		default:
			loopend = 1;
			break;
		}
		if (loopend)
			break;
	}

	//return EXIT_SUCCESS;

	// fopen(�t�@�C����, �I�v�V����)�Ńt�@�C�����J���܂��B����͏㏑���ł���B
	FILE* fpw = fopen(FNAME, "w");
	
	//�\���̂���t�@�C���ɑ΂��ď������݂��s���B


	resetRecord(fpw);


	// �t�@�C�����N���[�Y
	fclose(fpw);

	return EXIT_SUCCESS;
}

int menu() {
	char ret[8];

	while (1) {
		/*���j���[�̕\��*/
		printf("*****MENU*****\n");
		printf("1: Data Input\n");
		printf("2: Data Output\n");
		printf("3: Data Insertion\n");
		printf("4: Data Delete\n");
		printf("5: Data Edition\n");
		printf("6: ALL List\n");
		printf("7: Sort By ID\n");
		printf("0: End\n");
		printf("**************\n");
		/*���[�U�[�̑I�����󂯎���ĕԂ�*/
		printf("choise->");
		fgets(ret, sizeof(ret), stdin);
		ret[1] = '\0';
		if (ret[0] < '0' || ret[0] > '7') {
			printf("Invalid number\n");
			continue;
		}
		return atoi(ret);
	}
}



// CSV�t�@�C������ǂݍ��񂾕������Record_t�\���̂ɐݒ肵�܂�
void setRecord(char* str) {
	Record_t *current, *newNodePos;
	int i = 0, j = 1;
	// �ŏ���","��T��
	char* pStr = strtok(&str[i], ",");
	while (pStr) {
		newNodePos = createNode();
		while (j) {
			switch (i) {
			case 0:
				// �C���f�b�N�X
				newNodePos->idx = atoi(pStr);
				i++;
				break;
			case 1:
				// Name
				strcpy(newNodePos->name, pStr);
				i++;
				break;
			case 2:
				// Tel Num
				newNodePos->tel = atoi(pStr);
				i++;
				break;
			case 3:
				// Address
				pStr[strlen(pStr) - 1] = '\0';
				strcpy(newNodePos->address, pStr);
				i++;
				break;
			default:
				continue;
			}
			
			// ","��T��
			pStr = strtok(NULL, ",");
			if (pStr == NULL) {
				// ","���Ȃ��ꍇ�A�Ō��"��T��
				pStr = strtok(NULL, "\n");
				j = (int) NULL;
				continue;
			}
		}
		
		//���̃m�[�h�ɂȂ����߂̏���
		if ((head == NULL) && (tail == NULL)) {
			head = newNodePos;
			tail = newNodePos;
		}
		else {
			tail->next = newNodePos;
			tail = newNodePos;
		}

		tail->next = NULL;

		int i = 0;
		current = head;
		
		break;
	}

}


void resetRecord(FILE* fp) {
	Record_t *current;
	int idx, tel;
	if ((head == NULL) && (tail == NULL)) {
		printf("The list is empty\n");
		return;
	}
	current = head;

	while (1) {
		idx = (int)current->idx;
		tel = (int)current->tel;

		fprintf(fp, format, idx, current->name, tel, current->address);
		
		printf("ID:%4d Name:%8s TEL:%-8d Address:%-32s\n", idx, current->name, tel, current->address);		
		if (current->next != NULL) {
			current = current->next;
		}
		else {
			printf("This is whole of the list\n");
			break;
		}
	}
}


// CSV�t�@�C���o��
void output(FILE* fp, struct Record** out, int size) {
	int i;

	for (i = 0; i < size; i++) {
		// �|�C���g�R �J���}��؂�̕�������쐬���ďo�͂��܂�
		fprintf(fp, format, out[i]->idx, out[i]->name, out[i]->tel, out[i]->address);
		
		printf("ID:%4d Name:%8s TEL:%-8d Address:%-32s\n", out[i]->idx, out[i]->name, out[i]->tel, out[i]->address);
	}
}

// �V�����\���̂����܂��B
Record_t *createNode(void) {
	Record_t *newNodePos;

	newNodePos = (Record_t *)malloc(sizeof(Record_t));

	return newNodePos;
}

// �\���̂̃��X�g�ɐV�����m�[�h��ǉ����܂��B
Record_t * node_input() {
	Record_t *current, *newNodePos;
	int inputId, inputTel;
	char inputName[16], inputAddress[32], buffer[16];

	newNodePos = createNode();

	printf("ID---");
	fgets(buffer, sizeof(buffer), stdin);
	inputId = atoi(buffer);
	newNodePos->idx = inputId;


	printf("Name---");
	fgets(inputName, sizeof(inputName), stdin);
	inputName[strlen(inputName) - 1] = '\0';
	strcpy(newNodePos->name, inputName);

	printf("Tel---");
	fgets(buffer, sizeof(buffer), stdin);
	inputTel = atoi(buffer);
	newNodePos->tel = inputTel;

	printf("Address---");
	fgets(inputAddress, sizeof(inputAddress), stdin);
	inputAddress[strlen(inputAddress) - 1] = '\0';
	strcpy(newNodePos->address, inputAddress);

	if ((head == NULL) && (tail == NULL)) {
		head = newNodePos;
		tail = newNodePos;
	}
	else {
		tail->next = newNodePos;
		tail = newNodePos;
	}

	tail->next = NULL;

	int i = 0;
	current = head;

	printf("New node is added\n");

	return newNodePos;
}

void node_output(void) {
	Record_t *current;
	char targetName[20];

	if ((head == NULL) && (tail == NULL)) {
		printf("The list is empty\n");
		return;
	}

	printf("Input the name which you want to search\n");
	fgets(targetName, sizeof(targetName), stdin);
	targetName[strlen(targetName) - 1] = '\0';

	printNode(targetName);

	return;
}

void insertNodeToList(void) {
	char insertTargetName[20] = "";
	Record_t *current, *temp, *newNodePos;

	printf("Input the privious name of the node which you want to insert\n");
	printf("The new node would be added after the node which you instruct\n");
	fgets(insertTargetName, sizeof(insertTargetName), stdin);
	insertTargetName[strlen(insertTargetName) - 1] = '\0';

	current = head;

	while (current != NULL) {
		if (strcmp(current->name, insertTargetName) == 0) {
			printf("The node was found.\n");
			break;
		}
		else {
			current = current->next;
		}
	}

	if (current == NULL) {
		printf("The node is not found.\n");
		return;
	}

	printf("Before input\n");

	newNodePos = node_input(current);

	printf("After input\n");

	temp = current->next;
	current->next = newNodePos;
	newNodePos->next = temp;

	printf("After swap\n");

	printf("After plist\n");

	printf("New Node is inputed\n");
}

void deleteNodeFromList(void) {
	char deleteTargetName[20] = "";
	Record_t *current, *prev;

	printf("Input the node name which you want to delete.\n");
	fgets(deleteTargetName, sizeof(deleteTargetName), stdin);
	deleteTargetName[strlen(deleteTargetName) - 1] = '\0';

	current = head;
	prev = NULL;

	while (current != NULL) {
		if (strcmp(current->name, deleteTargetName) == 0) {
			printf("The node was found\n");
			break;
		}
		else {
			prev = current;
			current = current->next;
		}
	}

	if (current == NULL) {
		printf("No node is found\n");
		return;
	}

	if (current == head) {
		head = current->next;

		free(current);
	}
	else {
		prev->next = current->next;

		free(current);
	}

	printf("Successfully deleted\n");
}

void editNodeFromList(void) {
	char editTargetName[20] = "";
	Record_t *current, *temp, *newNodePos;

	int inputId, inputTel;
	char inputName[20], buffer[8], inputAddress[32];

	printf("Input the name of the node which you want to edit\n");
	fgets(editTargetName, sizeof(editTargetName), stdin);
	editTargetName[strlen(editTargetName) - 1] = '\0';

	current = head;


	while (current != NULL) {
		if (strcmp(current->name, editTargetName) == 0) {
			printf("The node was found.\n");
			break;
		}
		else {
			current = current->next;
		}
	}

	if (current == NULL) {
		printf("The node is not found.\n");
		return;
	}

	printf("ID---");
	fgets(buffer, sizeof(buffer), stdin);
	inputId = atoi(buffer);
	current->idx = inputId;


	printf("Name---");
	fgets(inputName, sizeof(inputName), stdin);
	inputName[strlen(inputName) - 1] = '\0';
	strcpy(current->name, inputName);

	printf("TEL---");
	fgets(buffer, sizeof(buffer), stdin);
	inputTel = atoi(buffer);
	current->tel = inputTel;

	printf("Address---");
	fgets(inputAddress, sizeof(inputAddress), stdin);
	inputAddress[strlen(inputAddress) - 1] = '\0';
	strcpy(current->address, inputAddress);


	printf("The Node is edited\n");
}

void printList(void) {
	Record_t *current;
	if ((head == NULL) && (tail == NULL)) {
		printf("The list is empty\n");
		return;
	}
	current = head;
	printf("----------------------------------\n");
	while (1) {
		printf("ID--- %d\n", current->idx);
		printf("Name--- %s\n", current->name);
		printf("TEL--- %d\n", current->tel);
		printf("Address--- %s\n", current->address);
		printf("----------------------------------\n");
		if (current->next != NULL) {
			current = current->next;
		}
		else {
			printf("This is whole of the list\n");
			break;
		}
	}
}

void printNode(char s[32]) {
	Record_t *current;
	current = head;

	while (current != NULL) {
		if (strcmp(current->name, s) == 0) {
			printf("The node was found.\n");
			break;
		}
		else {
			current = current->next;
		}
	}

	if (current == NULL) {
		printf("The node is not found\n");
		return;
	}

	printf("-----------------------------\n");
	printf("ID--- %d\n", current->idx);
	printf("Name--- %s\n", current->name);
	printf("TEL--- %d\n", current->tel);
	printf("Address--- %s\n", current->address);
	printf("-----------------------------\n");

}

void sortNode(void) {
	Record_t *current = head;

	head = sort(current);

}

int compare(const Record_t* d1, const Record_t* d2) {
	if (d1->idx != d2->idx) {
		return d1->idx > d2->idx ? 1 : -1;
	}
	return 0;
}

Record_t* sort(Record_t* head) {
	Record_t *list1, *list2, **next;
	/* 0�܂���1�̏ꍇ�A���� */
	if (head == NULL || head->next == NULL) return head;
	/* ���X�g�𒆉���2�ɕ������� */
	list1 = list2 = head;
	while (1) {
		list2 = list2->next;
		if (list2 != NULL) list2 = list2->next;
		if (list2 == NULL) {
			/* list1��2�{�i��list2���Ō�܂ōs�����̂ŁAlist1���^�񒆂ɂ���͂� */
			list2 = list1->next; /* �㔼�����̈ʒu��ۑ����� */
			list1->next = NULL; /* ���X�g��ؒf���� */
			list1 = head; /* �O�������̈ʒu��ۑ����� */
			break;
		}
		else {
			list1 = list1->next;
		}
	}
	/* ���ꂼ����\�[�g���� */
	list1 = sort(list1);
	list2 = sort(list2);
	/* �}�[�W���� */
	head = NULL;
	next = &head;
	while (list1 != NULL || list2 != NULL) {
		if (list2 == NULL) {
			/* list2����ɂȂ����̂ŁAlist1�̎c��̕�����A������ */
			*next = list1;
			break;
		}
		else if (list1 == NULL) {
			/* list1����ɂȂ����̂ŁAlist2�̎c��̕�����A������ */
			*next = list2;
			break;
		}
		else {
			/* �����Ƀ\�[�g����̂ŁA�������������o�� */
			if (compare(list1, list2) <= 0) {
				*next = list1;
				list1 = list1->next;
			}
			else {
				*next = list2;
				list2 = list2->next;
			}
			next = &(*next)->next;
			*next = NULL;
		}
	}
	return head;
}
