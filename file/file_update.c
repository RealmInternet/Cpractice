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
int myupdate(int );

char *format = "%-15s %-3d %-2s %-63s\n";

int main() {
	int menuno;
	/*�e�֐��̌Ăяo��*/
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
	char input_name[16], name[16], sex[4], address[64], buffer[8];
	int age, no = 0;

	/*�t�@�C���I�[�v��*/
	/*�V�K�̓��݂͂̂��l�����āA���̏ꍇ�͒ǉ����[�h���g�p����B*/

	fp = fopen(FNAME, "a");
	if (fp == NULL) {
		perror("couldn't open the file\n");
		return -1;
	}

	/*���͂̓ǂݎ��A�t�@�C���ւ̏�������*/
	while (1) {
		printf("Name---");
		fgets(input_name, sizeof(input_name), stdin);
		input_name[strlen(input_name) - 1] = '\0';

		/*���O����͂��邱�ƂŁA����܂łɂ��̐l�����͂���Ă��Ȃ����m�F*/
		while (1) {
			/*�������͕����񂪃f�[�^�ɔ������ꂽ�ꍇ�́A�ҏW���[�h�����߂�*/
			if (strstr(name, input_name) == NULL) {
				printf("The data exists.\n");
				printf("If you want to access this data, please use '3: Data Rewrite' mode.\n");
				return 0;
			}
		}

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
		if (fprintf(fp, format, input_name, age, sex, address) < 0) {
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

		/*�����֐��ɑΏۂ̕������n���B�I�t�Z�b�g���L��*/
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

		/*�����p�̃I�t�Z�b�g�̎擾*/
		int offset = mysearch(shusei);

		/*�I�t�Z�b�g���󂯎���Ă����ɂ���Œ蒷�̃f�[�^�̍X�V*/
		int result = myupdate(offset);

		/*�����̌J��Ԃ��̊m�F*/
		printf("Do you want to continue to rewrite?(y/n)");
		fgets(yesno, sizeof(yesno), stdin);
	}
	return 0;
}

int myupdate(int offset) {
	FILE *fp;
	char name[16], sex[4], address[64], buffer[8], shusei[8], ret[8];
	int age, case_no = 1;

	/*�I�t�Z�b�g���󂯎��t�@�C���|�C���^�[��ړI�̂Ƃ���܂ňړ������A�����ɂ���Œ蒷�f�[�^���X�V����֐�*/

	/*�t�@�C���I�[�v��*/
	fp = fopen(FNAME, "r+");
	if (fp == NULL) {
		perror("The file could not opened\n");
		return -1;
	}

	/*�󂯎�����I�t�Z�b�g�Ɋ�Â��āA�t�@�C���|�C���^�[���ړ�������*/
	fseek(fp, RECORDLEN * offset, SEEK_SET);

	/*���ۂɂ��ꂼ����̂ɃA�N�Z�X���Ċm�F*/
	if (fscanf(fp, "%s", name) == EOF) {
		printf("file access error\n");
		return 0;
	}

	if (fscanf(fp, "%d", &age) == EOF) {
		printf("file access error\n");
		return 0;
	}
	if (fscanf(fp, "%s", sex) == EOF) {
		printf("file access error\n");
		return 0;
	}
	if (fscanf(fp, "%s", address) == EOF) {
		printf("file access error\n");
		return 0;
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

			/*�G���[�����Ə�������*/
			fseek(fp, RECORDLEN * offset, SEEK_SET);
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

			/*�G���[�����Ə�������*/
			fseek(fp, RECORDLEN * offset, SEEK_SET);
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

			/*�G���[�����Ə�������*/
			fseek(fp, RECORDLEN * offset, SEEK_SET);
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

			/*�G���[�����Ə�������*/
			fseek(fp, RECORDLEN * offset, SEEK_SET);
			if (fprintf(fp, format, name, age, sex, address) < 0) {
				perror("Writing error occured.\n");
				break;
			}
			break;

		case 0:
			break;

		default:
			printf("Invalid access\n");
			break;
		}
	}
	fclose(fp);
	return 0;
}
