#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include<conio.h>
# define LEN sizeof(struct Goods)

struct Goods {
char num[10];  /*����*/
char name[20]; /*��Ʒ����*/
char price[10];  /*�۸�*/


struct Goods *next;
};

char filename[30];//ȫ�ֱ�������������Ҫ�򿪵��ļ�����

/*��������*/
struct Goods *Creat(int n) {
	void menu_print_in(void);
	struct Goods *head;
	struct Goods *p1, *p2;

	system("cls");
	for(int i=1;i<n+1;i++) {
		p1 = (struct Goods*)malloc(LEN);
		
		printf("\t\t��������Ʒ����:");
		scanf("%s",p1->num);
		printf("\t\t��������Ʒ��:");
		scanf("%s",p1->name);
		printf("\t\t��������Ʒ�۸�:");
		scanf("%s",p1->price);
		p1->next = NULL;
		if(i==1) {
			head = p2 = p1;
		}
		else {
			p2->next = p1;
			p2 = p1;
		}
	}
	return(head);
}

/*���ݴ���(wbֻд)*/
void WriteData_wb(struct Goods *head) {
	FILE *fp;
	struct Goods *p;
	if((fp = fopen(filename, "wb"))==NULL)
	printf("\a error! Can not open the file!");
	p = head;
	while(p!=NULL) {
		if(fwrite(p,LEN,1,fp)!=1) {
			printf("д�����ݳ���\n");
			fclose(fp);
			return;
		}
		p=p->next;
	}
	fclose(fp);
}

/*���ݴ���(ab׷��)*/
void WriteData_ab(struct Goods *head) {
	FILE *fp;
	struct Goods *p;
	if((fp = fopen(filename, "ab"))==NULL)
	printf("\a error! Can not open the file!");
	p = head;
	while(p!=NULL) {
	if(fwrite(p,LEN,1,fp)!=1) {
			printf("д�����ݳ���\n");
			fclose(fp);
			return;
		}
		p=p->next;
	}
	fclose(fp);
}


/*��ȡ����*/
/*��ȡ�����ļ����浽������ ������ָ�������ͷָ��*/
struct Goods *ReadData(void) {
	struct Goods *head = NULL;
	struct Goods *p1, *p2;//s = p1;p = p2;

	FILE *fp;
	if((fp=fopen(filename,"rb+"))==NULL)
	{
		printf("���ļ�����\n");
		exit(0);
	}
	while(!feof(fp)) {
		if((p1=(struct Goods*)malloc(LEN))==NULL){
			printf("�ڴ��������\n");
			fclose(fp);
			exit(0);
		}
		if(fread(p1,LEN,1,fp)!=1){
			free(p1);
			break;
		}
		if(head==NULL)
		head=p2=p1;
		else{
			p2->next=p1;
			p2=p1;
		}
	}
	fclose(fp);
	return (head);
}

/*��1��ȫ����ѯ*/
void Print_inquire_all(void) {
	void menu_print_out(void);
	struct Goods *pt;
	pt = ReadData();
	menu_print_out();
	do {
		printf("%-10s%6s%8s\n",
		pt->name,pt->num,pt->price);
		pt = pt->next;
	}while(pt!=NULL);
	printf("\n\n");
}


/*��2����Ʒ����ѯ*/
int Print_inquire_name() {
	void menu_print_out(void);
	struct Goods *pt;
	char str_name[20];
	printf("����������Ҫ��ѯ������:");
	scanf("%s", str_name);
	pt = ReadData();
	menu_print_out();
	do {
		if(strcmp(pt->name,str_name)==0) {
			printf("%-10s%6s%8s\n",
			pt->name,pt->num,pt->price);
			printf("\n\n");
			return 0;
		}
		pt = pt->next;
	}while(pt!=NULL);
	printf("���ݿ���û�д洢��Ҫ��ѯ�����ݣ�\n");
	printf("\n\n");
	return 0;
}



/*��1���޸�����֮ɾ����¼*/
int Delete() {
	struct Goods *pt1, *pt2, *head;
	char str_num[20];
	printf("\n����������Ҫɾ������Ʒ��Ϣ:");
	scanf("%s", str_num);
	pt1 = ReadData();
	pt2 = pt1->next;
	head = pt1;
	while(pt2!=NULL) {
		if(strcmp(pt1->num,str_num)==0) {
			WriteData_wb(pt2);
		}
		else if(strcmp(pt2->num,str_num)==0) {
			pt1->next = pt2->next;
			WriteData_wb(head);
		}
		pt2 = pt2->next;
		pt1 = pt1->next;
	}
	if(pt2!=NULL)
	printf("���ݿ���û�д洢��Ҫɾ�������ݣ�\n");
	printf("\n\n");
	return 0;
}

/*��2���޸�����֮�޸ļ�¼*/
int Amend() {
	void menu_print_in(void);
	struct Goods *pt1, *pt2, *head;
	char str_num[20];
	printf("����������Ҫ�޸ĵ���Ʒ��Ϣ:");
	scanf("%s", str_num);
	pt1 = ReadData();
	pt2 = pt1->next;
	head = pt1;
	while(pt2!=NULL) {
		if(strcmp(pt1->num,str_num)==0) {
			
			printf("\t\t��������Ʒ����:");
			scanf("%s",pt1->num);
			printf("\t\t��������Ʒ��:");
			scanf("%s",pt1->name);
			printf("\t\t��������Ʒ�۸�:");
			scanf("%s",pt1->price);
			WriteData_wb(head);
		}
		else if(strcmp(pt2->num,str_num)==0) {
			
			printf("\t\t��������Ʒ����:");
			scanf("%s",pt2->num);
			printf("\t\t��������Ʒ��:");
			scanf("%s",pt2->name);
			printf("\t\t��������Ʒ�۸�:");
			scanf("%s",pt2->price);
			WriteData_wb(head);
		}
		pt2 = pt2->next;
		pt1 = pt1->next;
	}
	if(pt2!=NULL)
	printf("���ݿ���û�д洢��Ҫɾ�������ݣ�\n");
	return 0;
}

/*��3���޸�����֮��������*/
int Neaten() {
	struct Goods *first;
	struct Goods *tail;
	struct Goods *p_min;
	struct Goods *min;
	struct Goods *p;
	struct Goods *head;
		head = ReadData();
	first = NULL;
	while(head!=NULL) {
		for(p=head,min=head; p->next!=NULL; p=p->next) {
			if(strcmp(p->next->num,min->num)<0) {
				p_min = p;
				min = p->next;
			}
		}
		if(first==NULL) {
			first = min;
			tail = min;
		}
		else {
			tail->next = min;
			tail = min;
		}
		if(min==head) {
			head = head->next;
		}
		else {
			p_min->next = min->next;
		}
	}
	if(first!=NULL) {
		tail->next = NULL;
	}
	head = first;

	WriteData_wb(head);
	return 0;
}

/*����д�����ݵ�����*/
int Creat_num(void) {
	printf("\n�����������˴�Ҫ��ӵ����ݸ���:");
	int n;
	if(scanf("%d", &n)!=1) {
		printf("\a error!");
	}
	return n;
}

/*ѡ��Ҫ�򿪵��ļ�*/
int File_name() {
	printf("\n������������Ҫ�򿪵��ļ�:");
	if(scanf("%s", filename)!=1)
	printf("\a error!");
	return 0;
}

/*���˵�*/
void menu(void) {
	void menu_add(void);
	void menu_inquire(void);
	void menu_amend(void);
	printf("              ��������������������            \n");
	printf("����������������     ���ﳵ     �ǩ�������������\n");
	printf("��            ��������������������            ��\n");
	printf("��   ��1�������Ʒ           ��3���޸�����    ��\n");
	printf("��                                            ��\n");
	printf("��   ��2����ѯ��Ʒ           ��4���˳�ϵͳ    ��\n");
	printf("��                                            ��\n");
	printf("��һһһһһһһһһһһһһһһһһһһһһһ��\n");
	printf("��                                  ���ﳵv1.0��\n");
	printf("������������������������������������������������\n");
	printf("�������빦��ǰ����Ž�����Ӧ�Ĺ���:");

	int a = 0;
	a = getchar();

	while(a!='1'&&a!='2'&&a!='3'&&a!='4') {
		printf("error! please input the right number!\n");
		putchar('\a');
		getchar();
		printf("�����������빦��ǰ����Ž�����Ӧ�Ĺ���:");
		a = getchar();
	}
	switch(a) {
		case '1': File_name();menu_add();
		break;
		case '2': File_name();menu_inquire();
		break;
		case '3': File_name();menu_amend();
		break;
		case '4': exit(0);
		break;
	}
	getchar();
}

/*�����˵�֮�������*/
void menu_add(void) {
	system("cls");
	getchar();
	printf("              ��������������������              \n");
	printf("����������������  ������ݷ�ʽ  �ǩ�������������\n");
	printf("��            ��������������������            ��\n");
	printf("�� ��1���½��ļ� ��2���������� ��3�����ز˵�  ��\n");
	printf("��                                            ��\n");
	printf("��һһһһһһһһһһһһһһһһһһһһһһ��\n");
	printf("��                                  ���ﳵv1.0��\n");
	printf("������������������������������������������������\n");
	printf("�������빦��ǰ����Ž�����Ӧ�Ĺ���:");

	int a = 0;
	a = getchar();

	while(a!='1'&&a!='2'&&a!='3') {
		printf("error! please input the right number!\n");
		putchar('\a');
		getchar();
		printf("�����������빦��ǰ����Ž�����Ӧ�Ĺ���:");
		a = getchar();
	}
	switch(a) {
		case '1': WriteData_wb(Creat(Creat_num()));
		 printf("\n���½��ļ��ɹ��������ѳɹ������\n");
			 system("pause");
		 system("cls");
		 menu_add();
		break;
		case '2': WriteData_ab(Creat(Creat_num()));
			 printf("\n�������ѳɹ���ӡ�\n");
			 system("pause");
		 system("cls");
		 menu_add();
		break;
		case '3': system("cls");
		 getchar();
		 menu();
		break;
	}
}

/*�����˵�֮��ѯ����*/
void menu_inquire(void) {
	system("cls");
	getchar();
	while(1) {
	system("cls");
	printf("              ��������������������              \n");
	printf("����������������  ��ѯ���ݷ�ʽ  �ǩ�������������\n");
	printf("��            ��������������������            ��\n");
	printf("��   ��1��ȫ����ѯ ��2�����Ʋ�ѯ ��3�����ز˵���\n");
	printf("��                                            ��\n");
	printf("��һһһһһһһһһһһһһһһһһһһһһһ��\n");
	printf("��                                  ���ﳵv1.0��\n");
	printf("������������������������������������������������\n");
	printf("�������빦��ǰ����Ž�����Ӧ�Ĺ���:");
	int a = 0;
	a = getchar();

	while(a!='1'&&a!='2'&&a!='3'&&a!='3'&&a!='4') {
			printf("error! please input the right number!\n");
			putchar('\a');
			getchar();
			printf("�����������빦��ǰ����Ž�����Ӧ�Ĺ���:��   ��\b\b");
			a = getchar();
		}
		switch(a) {
			case '1': Print_inquire_all();system("pause");getchar();
			break;
			case '2': Print_inquire_name();system("pause");getchar();
			break;
			case '3': system("cls");getchar();menu();
			break;
		}
	}
}

/*�����˵�֮�޸�����*/
void menu_amend(void) {
	system("cls");
	getchar();
	while(1) {
	system("cls");
	printf("              ��������������������              \n");
	printf("����������������  �޸����ݷ�ʽ  �ǩ�������������\n");
	printf("��            ��������������������            ��\n");
	printf("��    ��1��ɾ����¼          ��3����������    ��\n");
	printf("��                                            ��\n");
	printf("��    ��2���޸ļ�¼          ��4�����ز˵�    ��n");
	printf("��һһһһһһһһһһһһһһһһһһһһһһ��\n");
	printf("��                                  ���ﳵv1.0��\n");
	printf("������������������������������������������������\n");
	printf("�������빦��ǰ����Ž�����Ӧ�Ĺ���:��   ��\b\b");

	int a = 0;
	a = getchar();

	while(a!='1'&&a!='2'&&a!='3'&&a!='4') {
		printf("error! please input the right number!\n");
		putchar('\a');
		getchar();
		printf("�����������빦��ǰ����Ž�����Ӧ�Ĺ���:��   ��\b\b");
		a = getchar();
		}
		switch(a) {
			case '1': Delete();
			 printf("\n\n���ѳɹ�ɾ��ָ�����ݡ�\n");
			 system("pause");
			 getchar();
			break;
			case '2': Amend();
				 printf("\n\n���ѳɹ��޸�ָ�����ݡ�\n");
			 system("pause");
				 getchar();
			break;
			case '3': Neaten();
			 printf("\n\n�������ѳɹ�����ѧ���������С�\n");
			 system("pause");
			 getchar();
			break;
			case '4': system("cls");
			 getchar();
			 menu();
			break;
		}
	}
}

/*���������ʾ��*/
void menu_print_in(void) {
	printf("-----------------------------------\n");
	printf("��Ʒ      ����     �۸�            \n");
	printf("-----------------------------------\n");
}
void menu_print_out(void) {
	printf("-----------------------------------\n");
	printf("��Ʒ      ����     �۸�            \n");
	printf("-----------------------------------\n");
}
//��ʼ������
void InitFace()
{
	printf("\t\t*********************************************************\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t\t���ﳵϵͳ\t\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t\t�汾�ţ�1.0\t\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t����ʯ�ʹ�ѧ�ƿ�Ժ����������\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t�޼���     \tФ����\t\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t��дʱ��;   2018/7/12\t\t\t*\n");
	printf("\t\t*********************************************************\n");
	printf("\t\t");
	system("pause");//�������������
	system("cls");//����
}
//�������
void EnterPassword()
{
	int count=0,ch,i;
	char mima[100]={"000000\0'"};
	char input[100]={0};
	printf("\t\t*********************************************************\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t\t���ﳵϵͳ\t\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t��������λ�������ϵͳ��\t\t*\n");
	printf("\t\t���������룺");
	ch=getch();
	for(i=0;i<100;i++)
	{
		input[i]=ch;
		if(input[i]=='\r')
		{
			input[i]='\0';
			break;
		}
		else
			printf("*");
		ch=getch();//�ӻ�������ȡ�س���
	}
	if(strcmp(mima,input)==0)
		{
			printf("\n");
			printf("\t\t������ȷ!\n");
			printf("\t\t3����Զ����빺�ﳵ!\n");
			Sleep(3000);//�ӳ�ʱ��
		}
	else
	{
		char str[99]; 
        gets(str);
        MessageBox(NULL,TEXT("�������"),TEXT("����"),MB_OK);
		exit(0);
	}
	system("cls");//����

}

/*������*/
int main(void) {
	//SetConsoleTitle(L"C++���ﳵϵͳ");
	EnterPassword();
	InitFace();
	menu();
	return 0; 
}

