/* struct_list_sort.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct DATA{
	int id;
	char name[32];
	int tel;
	char address[64];
	struct DATA *next;
}DATA, MyData_t;

MyData_t *head = NULL;
MyData_t *tail = NULL;

MyData_t *plst[32];

MyData_t *createNode(void);
struct DATA * node_input(MyData_t *);
void node_output(void);
void insertNodeToList(void);
void deleteNodeFromList(void);
void editNodeFromList(void);
void printList(void);
void sortNode(void);
int compare(const MyData_t*, const MyData_t*);
MyData_t* sort(MyData_t*);
void printNode(char s[32]);


int menu();


int main(void) {
	int select_No, loopend = 0;

	while (1) {
		select_No = menu();

		switch (select_No) {
		case 1:
			node_input(NULL);
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
	printf("3: Data Insertion\n");
	printf("4: Data Delete\n");
	printf("5: Data Edition\n");
	printf("6: ALL List\n");
	printf("7: Sort By ID\n");
	printf("0: End\n");
	printf("**************\n");
	printf("--->");
	fgets(ret, sizeof(ret), stdin);
	ret[strlen(ret) - 1] = '\0';

	return atoi(ret);
}

MyData_t *createNode(void) {
	MyData_t *newNodePos;

	newNodePos = (MyData_t *)malloc(sizeof(MyData_t));

	return newNodePos;
}

struct DATA * node_input(MyData_t *newNodePos) {
	MyData_t *current, *temp; 
	int inputId, inputTel;
	char inputName[16], inputAddress[32], buffer[16];

	newNodePos = createNode();

	printf("ID---");
	fgets(buffer, sizeof(buffer), stdin);
	inputId = atoi(buffer);
	newNodePos->id = inputId;


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
	} else {
		tail->next = newNodePos;
		tail = newNodePos;
	}

	tail->next = NULL;

	int i = 0;
	current = head;
	/*
	while (1){
		if (current->next != NULL){
			plst[i] = current;
			current = current->next;
			i++;
		}else{
			break;
		}
	}
	*/
	printf("New node is added\n");

	return newNodePos;
}

void node_output(void) {
	MyData_t *current;
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
	MyData_t *current, *temp, *newNodePos;

	printf("Input the privious name of the node which you want to insert\n");
	printf("The new node would be added after the node which you instruct\n");
	fgets(insertTargetName, sizeof(insertTargetName), stdin);
	insertTargetName[strlen(insertTargetName) - 1] = '\0';

	current = head;

	while (current != NULL) {
		if (strcmp(current->name, insertTargetName) == 0) {
			printf("The node was found.\n");
			break;
		} else {
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
	MyData_t *current, *prev;

	printf("Input the node name which you want to delete.\n");
	fgets(deleteTargetName, sizeof(deleteTargetName), stdin);
	deleteTargetName[strlen(deleteTargetName) - 1] = '\0';

	current = head;
	prev = NULL;

	while (current != NULL) {
		if (strcmp(current->name, deleteTargetName) == 0) {
			printf("The node was found\n");
			break;
		}else {
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
	MyData_t *current, *temp, *newNodePos;

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
	current->id = inputId;


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
	MyData_t *current;
	if ((head == NULL) && (tail == NULL)){
		printf("The list is empty\n");
		return;
	}
	current = head;
	printf("----------------------------------\n");
	while (1) {
		printf("ID--- %d\n", current->id);
		printf("Name--- %s\n", current->name);
		printf("TEL--- %d\n", current->tel);
		printf("Address--- %s\n", current->address);
		printf("----------------------------------\n");
		if (current->next != NULL){
			current = current->next;
		} else {
			printf("This is whole of the list\n");
			break;
		}
	}
}

void printNode(char s[32]) {
	MyData_t *current;
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
	printf("ID--- %d\n", current->id);
	printf("Name--- %s\n", current->name);
	printf("TEL--- %d\n", current->tel);
	printf("Address--- %s\n", current->address);
	printf("-----------------------------\n");

}

void sortNode(void) {
	MyData_t *current = head;

	head = sort(current);

}

int compare(const MyData_t* d1, const MyData_t* d2) {
	if (d1->id != d2->id) {
		return d1->id > d2->id ? 1 : -1;
	}
	return 0;
}

MyData_t* sort(MyData_t* head) {
	MyData_t *list1, *list2, **next;
	/* 0個または1個の場合、自明 */
	if (head == NULL || head->next == NULL) return head;
	/* リストを中央で2個に分割する */
	list1 = list2 = head;
	while (1) {
		list2 = list2->next;
		if (list2 != NULL) list2 = list2->next;
		if (list2 == NULL) {
			/* list1の2倍進むlist2が最後まで行ったので、list1が真ん中にいるはず */
			list2 = list1->next; /* 後半部分の位置を保存する */
			list1->next = NULL; /* リストを切断する */
			list1 = head; /* 前半部分の位置を保存する */
			break;
		}
		else {
			list1 = list1->next;
		}
	}
	/* それぞれをソートする */
	list1 = sort(list1);
	list2 = sort(list2);
	/* マージする */
	head = NULL;
	next = &head;
	while (list1 != NULL || list2 != NULL) {
		if (list2 == NULL) {
			/* list2が空になったので、list1の残りの部分を連結する */
			*next = list1;
			break;
		}
		else if (list1 == NULL) {
			/* list1が空になったので、list2の残りの部分を連結する */
			*next = list2;
			break;
		}
		else {
			/* 昇順にソートするので、小さい方を取り出す */
			if (compare(list1, list2) <= 0){
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

/* https://dixq.net/forum/viewtopic.php?t=18710 */