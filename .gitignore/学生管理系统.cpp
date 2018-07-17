#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include<conio.h>
# define LEN sizeof(struct Goods)
int	j=1;
struct Goods {
char num[10];  /*数量*/
char name[20]; /*商品名称*/
char price[10];  /*价格*/


struct Goods *next;
};

char filename[30];//全局变量，用来保存要打开的文件名字

/*生成链表*/
struct Goods *Creat(int n) {
	void menu_print_in(void);
	struct Goods *head;
	struct Goods *p1, *p2;

	system("cls");
	for(int i=1;i<n+1;i++) {
		p1 = (struct Goods*)malloc(LEN);
		
		printf("\t\t请输入商品个数:");
		scanf("%s",p1->num);
		printf("\t\t请输入商品名:");
		scanf("%s",p1->name);
		printf("\t\t请输入商品价格:");
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

/*数据存盘(wb只写)*/
void WriteData_wb(struct Goods *head) {
	FILE *fp;
	struct Goods *p;
	if((fp = fopen(filename, "wb"))==NULL)
	printf("\a error! Can not open the file!");
	p = head;
	while(p!=NULL) {
		if(fwrite(p,LEN,1,fp)!=1) {
			printf("写入数据出错\n");
			fclose(fp);
			return;
		}
		p=p->next;
	}
	fclose(fp);
}

/*数据存盘(ab追加)*/
void WriteData_ab(struct Goods *head) {
	FILE *fp;
	struct Goods *p;
	if((fp = fopen(filename, "ab"))==NULL)
	printf("\a error! Can not open the file!");
	p = head;
	while(p!=NULL) {
	if(fwrite(p,LEN,1,fp)!=1) {
			printf("写入数据出错\n");
			fclose(fp);
			return;
		}
		p=p->next;
	}
	fclose(fp);
}


/*读取数据*/
/*读取数据文件保存到链表中 ，返回指向此链表头指针*/
struct Goods *ReadData(void) {
	struct Goods *head = NULL;
	struct Goods *p1, *p2;//s = p1;p = p2;

	FILE *fp;
	if((fp=fopen(filename,"rb+"))==NULL)
	{
		printf("打开文件出错\n");
		exit(0);
	}
	while(!feof(fp)) {
		if((p1=(struct Goods*)malloc(LEN))==NULL){
			printf("内存申请出错\n");
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

/*【1】全量查询*/
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


/*【2】商品名查询*/
int Print_inquire_name() {
	void menu_print_out(void);
	struct Goods *pt;
	char str_name[20];
	printf("◎请输入您要查询的名称:");
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
	printf("数据库中没有存储您要查询的数据！\n");
	printf("\n\n");
	return 0;
}



/*【1】修改数据之删除记录*/
int Delete() {
	struct Goods *pt1, *pt2, *head;
	char str_num[20];
	printf("\n◎请输入您要删除的商品信息:");
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
	printf("数据库中没有存储您要删除的数据！\n");
	printf("\n\n");
	return 0;
}

/*【2】修改数据之修改记录*/
int Amend() {
	void menu_print_in(void);
	struct Goods *pt1, *pt2, *head;
	char str_num[20];
	printf("◎请输入您要修改的商品信息:");
	scanf("%s", str_num);
	pt1 = ReadData();
	pt2 = pt1->next;
	head = pt1;
	while(pt2!=NULL) {
		if(strcmp(pt1->num,str_num)==0) {
			
			printf("\t\t请输入商品个数:");
			scanf("%s",pt1->num);
			printf("\t\t请输入商品名:");
			scanf("%s",pt1->name);
			printf("\t\t请输入商品价格:");
			scanf("%s",pt1->price);
			WriteData_wb(head);
		}
		else if(strcmp(pt2->num,str_num)==0) {
			
			printf("\t\t请输入商品个数:");
			scanf("%s",pt2->num);
			printf("\t\t请输入商品名:");
			scanf("%s",pt2->name);
			printf("\t\t请输入商品价格:");
			scanf("%s",pt2->price);
			WriteData_wb(head);
		}
		pt2 = pt2->next;
		pt1 = pt1->next;
	}
	if(pt2!=NULL)
	printf("数据库中没有存储您要删除的数据！\n");
	return 0;
}

/*【3】修改数据之整理数据*/
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

/*输入写入数据的数量*/
int Creat_num(void) {
	printf("\n◎请输入您此次要添加的数据个数:");
	int n;
	if(scanf("%d", &n)!=1) {
		printf("\a error!");
	}
	return n;
}

/*选择将要打开的文件*/
int File_name() {
	printf("\n◎请输入您想要打开的文件:");
	if(scanf("%s", filename)!=1)
	printf("\a error!");
	return 0;
}

/*主菜单*/
void menu(void) {
	void menu_add(void);
	void menu_inquire(void);
	void menu_amend(void);
	printf("              ┏━━━━━━━━┓            \n");
	printf("┏━━━━━━┫     购物车     ┣━━━━━━┓\n");
	printf("┃            ┗━━━━━━━━┛            ┃\n");
	printf("┃   【1】添加商品           【3】修改数据    ┃\n");
	printf("┃                                            ┃\n");
	printf("┃   【2】查询商品           【4】退出系统    ┃\n");
	printf("┃                                            ┃\n");
	printf("┃一一一一一一一一一一一一一一一一一一一一一一┃\n");
	printf("┃                                  购物车v1.0┃\n");
	printf("┗━━━━━━━━━━━━━━━━━━━━━━┛\n");
	printf("◎请输入功能前的序号进入相应的工具:");

	int a = 0;
	a = getchar();

	while(a!='1'&&a!='2'&&a!='3'&&a!='4') {
		printf("error! please input the right number!\n");
		putchar('\a');
		getchar();
		printf("◎请重新输入功能前的序号进入相应的工具:");
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

/*二级菜单之添加数据*/
void menu_add(void) {
	system("cls");
	getchar();
	printf("              ┏━━━━━━━━┓              \n");
	printf("┏━━━━━━┫  添加数据方式  ┣━━━━━━┓\n");
	printf("┃            ┗━━━━━━━━┛            ┃\n");
	printf("┃ 【1】新建文件 【2】增添数据 【3】返回菜单  ┃\n");
	printf("┃                                            ┃\n");
	printf("┃一一一一一一一一一一一一一一一一一一一一一一┃\n");
	printf("┃                                  购物车v1.0┃\n");
	printf("┗━━━━━━━━━━━━━━━━━━━━━━┛\n");
	printf("◎请输入功能前的序号进入相应的工具:");

	int a = 0;
	a = getchar();

	while(a!='1'&&a!='2'&&a!='3') {
		printf("error! please input the right number!\n");
		putchar('\a');
		getchar();
		printf("◎请重新输入功能前的序号进入相应的工具:");
		a = getchar();
	}
	switch(a) {
		case '1': WriteData_wb(Creat(Creat_num()));
		 MessageBox(NULL,TEXT("新建文件成功"),TEXT("成功！"),MB_OK);
			 system("pause");
		 system("cls");
		 menu_add();
		break;
		case '2': WriteData_ab(Creat(Creat_num()));
			 MessageBox(NULL,TEXT("添加成功"),TEXT("成功！"),MB_OK);
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

/*二级菜单之查询数据*/
void menu_inquire(void) {
	system("cls");
	getchar();
	while(1) {
	system("cls");
	printf("              ┏━━━━━━━━┓              \n");
	printf("┏━━━━━━┫  查询数据方式  ┣━━━━━━┓\n");
	printf("┃            ┗━━━━━━━━┛            ┃\n");
	printf("┃   【1】全部查询 【2】名称查询 【3】返回菜单┃\n");
	printf("┃                                            ┃\n");
	printf("┃一一一一一一一一一一一一一一一一一一一一一一┃\n");
	printf("┃                                  购物车v1.0┃\n");
	printf("┗━━━━━━━━━━━━━━━━━━━━━━┛\n");
	printf("◎请输入功能前的序号进入相应的工具:");
	int a = 0;
	a = getchar();

	while(a!='1'&&a!='2'&&a!='3'&&a!='3'&&a!='4') {
			printf("error! please input the right number!\n");
			putchar('\a');
			getchar();
			printf("◎请重新输入功能前的序号进入相应的工具:");
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

/*二级菜单之修改数据*/
void menu_amend(void) {
	system("cls");
	getchar();
	while(1) {
	system("cls");
	printf("              ┏━━━━━━━━┓              \n");
	printf("┏━━━━━━┫  修改数据方式  ┣━━━━━━┓\n");
	printf("┃            ┗━━━━━━━━┛            ┃\n");
	printf("┃    【1】删除记录          【3】整理数据    ┃\n");
	printf("┃                                            ┃\n");
	printf("┃    【2】修改记录          【4】返回菜单    ┃n");
	printf("┃一一一一一一一一一一一一一一一一一一一一一一┃\n");
	printf("┃                                  购物车v1.0┃\n");
	printf("┗━━━━━━━━━━━━━━━━━━━━━━┛\n");
	printf("◎请输入功能前的序号进入相应的工具:");

	int a = 0;
	a = getchar();

	while(a!='1'&&a!='2'&&a!='3'&&a!='4') {
		printf("error! please input the right number!\n");
		putchar('\a');
		getchar();
		printf("◎请重新输入功能前的序号进入相应的工具:");
		a = getchar();
		}
		switch(a) {
			case '1': Delete();
			 printf("\n\n◎已成功删除指定数据◎\n");
			 system("pause");
			 getchar();
			break;
			case '2': Amend();
				 printf("\n\n◎已成功修改指定数据◎\n");
			 system("pause");
				 getchar();
			break;
			case '3': Neaten();
			 printf("\n\n◎数据已成功按照数量重新排列◎\n");
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

/*输入输出提示栏*/
void menu_print_in(void) {
	printf("-----------------------------------\n");
	printf("商品      数量     价格            \n");
	printf("-----------------------------------\n");
}
void menu_print_out(void) {
	printf("-----------------------------------\n");
	printf("商品      数量     价格            \n");
	printf("-----------------------------------\n");
}
//初始化界面
void InitFace()
{
	printf("\t\t*********************************************************\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t\t购物车系统\t\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t\t版本号：1.0\t\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t西南石油大学计科院物联网工程\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t邹佳良     \t肖安建\t\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t编写时间;   2018/7/12\t\t\t*\n");
	printf("\t\t*********************************************************\n");
	printf("\t\t");
	system("pause");//输入任意键继续
	system("cls");//清屏
}
//密码界面
void EnterPassword()
{
	int count=0,ch,i;
	char mima[100]={"000000\0'"};
	char input[100]={0};
	
	printf("\t\t*********************************************************\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t\t购物车系统\t\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t请输入六位密码进入系统：\t\t*\n");
	printf("\t\t请输入密码：");
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
		ch=getch();//从缓存区读取回车符
	}
	if(strcmp(mima,input)==0)
		{
			printf("\n");
			printf("\t\t密码正确!\n");
			printf("\t\t3秒后自动进入购物车!\n");
			Sleep(3000);//延长时间
		}
	else
	{
		j=j+1;
		char str[99]; 
		gets(str);
		MessageBox(NULL,TEXT("密码错误"),TEXT("警告"),MB_OK);
		if(j==4){
		MessageBox(NULL,TEXT("密码错误3次，3秒后自动退出"),TEXT("错误"),MB_OK);
		Sleep(3000);//延长时间
		exit(0);}
		else system("cls");EnterPassword();
	}
	system("cls");//清屏
	
}

/*主函数*/
int main(void) {
	//SetConsoleTitle(L"C++购物车系统");
	EnterPassword();
	InitFace();
	menu();
	return 0; 
}
