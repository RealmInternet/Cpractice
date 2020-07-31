/* address_book_file.c */

#define FNAME "meibo.txt"
#define RECORDLEN 88

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DATA {
	char name[32];
	int age;
	char sex[4];
	char address[64];
	struct DATA *next;
}MyData_t;

MyData_t *head = NULL;
MyData_t *tail = NULL;

MyData_t *plst[32];

MyData_t *createNode(void);
struct DATA * node_input(MyData_t *);

int menu();
int myread();
int mywrite();
int myrewrite();
int mysearch(char *);
int myupdate(char *);

char *format = "%-15s %-3d %-2s %-63s\n";

int main() {
	int menuno;
	/*���j���[*/
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
		case 3:
			myrewrite();
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
		/*���j���[�̕\��*/
		printf("*******************\n");
		printf("1: Data Input(New Data)\n");
		printf("2: Data Output\n");
		printf("3: Data Rewrite\n");
		printf("0: End\n");
		printf("*******************\n");
		/*���[�U�[�̑I�����󂯎���ĕԂ�*/
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

	/*�t�@�C���I�[�v��*/
	/*�V�K�̓��݂͂̂��l�����āA���̏ꍇ�͒ǉ����[�h���g�p����B*/
	/*�����ŃI�t�Z�b�g��EOF�܂œ��B���Ȃ������Ƃ��̏�����g�ݍ��ނ�����*/

	fp = fopen(FNAME, "a");
	if (fp == NULL) {
		perror("couldn't open the file\n");
		return -1;
	}

	/*���͂̓ǂݎ��A�t�@�C���ւ̏�������*/
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
		
		/*�������݃G���[�̏���*/
		if (fprintf(fp, format, name, age, sex, address) < 0) {
			perror("Writing error occured.\n");
			break;
		}

		/*�����̌J��Ԃ��̊m�F*/
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

	/*�ǂݍ��݂̊֐�*/

	yesno[0] = 'Y';

	while(yesno[0] == 'y' || yesno[0] == 'Y'){
		printf("The target name--");
		fgets(search, sizeof(search), stdin);
		search[strlen(search) - 1] = '\0';

		/*�����֐��ɑΏۂ̕������n��*/
		int result = mysearch(search);

		/*�����̌J��Ԃ��̊m�F*/
		printf("Do you want to continue to search?(y/n)");
		fgets(yesno, sizeof(yesno), stdin);
	}
	return 0;
}

int mysearch(char *target) {
	FILE *fp;
	char name[16], sex[4], address[64], buffer[8];
	int no = 0, age;

	/*�����֐��A�߂�l�Ƀt�@�C���̐擪�A�h���X����ړI�̈ʒu�ɑ΂���Œ蒷�̃I�t�Z�b�g��Ԃ�*/
	
	/*�t�@�C���I�[�v��*/
	fp = fopen(FNAME, "r");

	if (fp == NULL) {
		perror("The file could not opened\n");
		return -1;
	}


	while (1) {

		/*�t�@�C���|�C���^�[���Œ蒷������������*/
		fseek(fp, RECORDLEN * no++, SEEK_SET);
		
		if (fscanf(fp, "%s", name) == EOF) {
			break;
		}

		/*�����ړI�̕�����ƃt�@�C���|�C���^�[�������Œ蒷�̒��ɑ��݂���name����v�����ꍇ�ɂ́A�����\������B*/
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

	/*�t�@�C���N���[�Y*/
	fclose(fp);
	/*�ړI�̃t�@�C���|�C���^�[�ɑ΂���I�t�Z�b�g�����킹��*/
	no--;
	return no;
}

int myrewrite() {
	char shusei[16], yesno[8];
	int no = 0, age, find = 0;

	/*�ď������ݗp�̊֐�*/

	yesno[0] = 'y';

	while(yesno[0] == 'y' || yesno[0] == 'Y'){
		printf("The name whoes data should be changed---");
		fgets(shusei, sizeof(shusei), stdin);
		shusei[strlen(shusei) - 1] = '\0';


		/*�I�t�Z�b�g���󂯎���Ă����ɂ���Œ蒷�̃f�[�^�̍X�V*/
		int result = myupdate(shusei);

		/*�����̌J��Ԃ��̊m�F*/
		printf("Do you want to continue to rewrite?(y/n)");
		fgets(yesno, sizeof(yesno), stdin);
	}
	return 0;
}

int myupdate(char *target) {
	FILE *fp;
	MyData_t *current, *newNodePos;
	char name[16], sex[4], address[64], buffer[8], shusei[8], ret[8];
	int age, case_no = 1;

	/*�I�t�Z�b�g���󂯎��t�@�C���|�C���^�[��ړI�̂Ƃ���܂ňړ������A�����ɂ���Œ蒷�f�[�^���X�V����֐�*/

	/*�t�@�C���I�[�v��*/
	fp = fopen(FNAME, "r");
	if (fp == NULL) {
		perror("The file could not opened\n");
		return -1;
	}

	while (fp != EOF) {
		/*�V�����\���̗̂̈���m��*/
		newNodePos = createNode();

		/*�t�@�C�����炻�ꂼ��̃f�[�^��ǂݍ���*/
		fscanf(fp, "%s", name);
		fscanf(fp, "%d", &age);
		fscanf(fp, "%s", sex);
		fscanf(fp, "%s", address);

		/*newNodePos�ɂ��ꂼ��������*/
		newNodePos->name = name;
		newNodePos->age = age;
		newNodePos->sex = sex;
		newNodePos->address = address;


		/*�擪�̏ꍇ�ɂ�head��tail�ɍ�������\���̂̃A�h���X��n��*/
		if ((head == NULL) && (tail == NULL)) {
			head = newNodePos;
			tail = newNodePos;
		}�@else {
			tail = newNodePos;				//tail����������\���̂̃A�h���X�ɂ���
		}

		tail->next = NULL;					//tail�̎��̃A�h���X��NULL�ɂ��Ă���


	}

	while(1) {
		if (case_no == 0)
			break;
		/*���j���[�̕\��*/
		printf("Would you like to chage this data? Which componet do you want to change?\n");
		printf("*******************\n");
		printf("1: Name\n");
		printf("2: Age\n");
		printf("3: Sex\n");
		printf("4: Address\n");
		printf("0: No\n");
		printf("*******************\n");
		printf("choise->");			//���͑���̎󂯎��
		fgets(ret, sizeof(ret), stdin);
		ret[1] = '\0';
		case_no = atoi(ret);

		/*�󂯎�������͑���ɂ��������āA�w�肳�ꂽ�v�f���X�V*/
		switch (case_no) {
		case 1:
			/*���͂̎󂯎��*/
			printf("Name---");
			fgets(name, sizeof(name), stdin);
			name[strlen(name) - 1] = '\0';
			printf("Inputed name: %s\n", name);
			/*�G���[�����Ə�������*/
			if (fprintf(fp, format, name, age, sex, address) < 0) {
				perror("Writing error occured.\n");
				break;
			}
			break;
		case 2:
			/*���͂̎󂯎��*/
			printf("Age---");
			fgets(buffer, sizeof(buffer), stdin);
			buffer[strlen(buffer) - 1] = '\0';
			age = atoi(buffer);
			printf("Inputed Age: %d\n", age);
			/*�G���[�����Ə�������*/
			if (fprintf(fp, format, name, age, sex, address) < 0) {
				perror("Writing error occured.\n");
				break;
			}
			break;
		case 3:
			/*���͂̎󂯎��*/
			printf("Sex---");
			fgets(sex, sizeof(sex), stdin);
			sex[strlen(sex) - 1] = '\0';
			printf("Inputed sex: %s\n", sex);
			/*�G���[�����Ə�������*/
			if (fprintf(fp, format, name, age, sex, address) < 0) {
				perror("Writing error occured.\n");
				break;
			}
			break;
		case 4:
			/*���͂̎󂯎��*/
			printf("Address---");
			fgets(address, sizeof(address), stdin);
			address[strlen(address) - 1] = '\0';
			printf("Inputed address: %s\n", address);
			/*�G���[�����Ə�������*/
			if (fprintf(fp, format, name, age, sex, address) < 0) {
				perror("Writing error occured.\n");
				break;
			}
			break;
		case 0:
			printf("End of rewrite\n");
		default:
			printf("Invalid access\n");
			break;
		}
	}
	fclose(fp);
	return 0;
}

MyData_t *createNode(void) {
	MyData_t *newNodePos;

	/*�\���̗̂̈�̊m�ۂ�����*/
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
	}
	else {
		tail->next = newNodePos;
		tail = newNodePos;
	}

	tail->next = NULL;

	int i = 0;
	current = head;

	while (1) {
		if (current->next != NULL) {
			plst[i] = current;
			current = current->next;
			i++;
		}
		else {
			break;
		}
	}

	printf("New node is added\n");

	return newNodePos;
}