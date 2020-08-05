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
	// fopen(ファイル名, オプション)でファイルを開きます
	FILE* fpr = fopen(FNAME, "r");
	
	// ファイルを開けない場合、FILEのポインタがNULLになります
	if (fpr == NULL) {
		puts("Failed to open");
		return EXIT_FAILURE;
	}


	// fgets(読み込むバッファ, バッファのサイズ, FILEのポインタ)で一行ずつ読み込みます
	while (fgets(str, 255, fpr)) {
		// 読み込んだ内容をそのまま出力
		// ポイント１ 読み込んだテキストを、分解して構造体の配列に設定します。
		// Record構造体にデータを設定
		setRecord(str);
	}

	// ファイルをクローズ
	fclose(fpr);

	// 出力用ポインタ配列にRecordのポインタをすべて設定する
	for (i = 0; i < size; i++) {
		sorted[i] = &record[i];
	}

	/*各関数の呼び出し*/
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

	// fopen(ファイル名, オプション)でファイルを開きます。今回は上書きである。
	FILE* fpw = fopen(FNAME, "w");
	
	//構造体からファイルに対して書き込みを行う。


	resetRecord(fpw);


	// ファイルをクローズ
	fclose(fpw);

	return EXIT_SUCCESS;
}

int menu() {
	char ret[8];

	while (1) {
		/*メニューの表示*/
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
		/*ユーザーの選択を受け取って返す*/
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



// CSVファイルから読み込んだ文字列をRecord_t構造体に設定します
void setRecord(char* str) {
	Record_t *current, *newNodePos;
	int i = 0, j = 1;
	// 最初の","を探す
	char* pStr = strtok(&str[i], ",");
	while (pStr) {
		newNodePos = createNode();
		while (j) {
			switch (i) {
			case 0:
				// インデックス
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
			
			// ","を探す
			pStr = strtok(NULL, ",");
			if (pStr == NULL) {
				// ","がない場合、最後の"を探す
				pStr = strtok(NULL, "\n");
				j = (int) NULL;
				continue;
			}
		}
		
		//次のノードにつなぐための処理
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


// CSVファイル出力
void output(FILE* fp, struct Record** out, int size) {
	int i;

	for (i = 0; i < size; i++) {
		// ポイント３ カンマ区切りの文字列を作成して出力します
		fprintf(fp, format, out[i]->idx, out[i]->name, out[i]->tel, out[i]->address);
		
		printf("ID:%4d Name:%8s TEL:%-8d Address:%-32s\n", out[i]->idx, out[i]->name, out[i]->tel, out[i]->address);
	}
}

// 新しい構造体を作ります。
Record_t *createNode(void) {
	Record_t *newNodePos;

	newNodePos = (Record_t *)malloc(sizeof(Record_t));

	return newNodePos;
}

// 構造体のリストに新しいノードを追加します。
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
