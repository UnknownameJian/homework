#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<string.h>
#include "stdafx.h"
//宏定义
#define COUNT sizeof(Goods)
#define LEN sizeof(struct Goods)
int num;

struct Goods
{
	long GoodsNum;
	char GoodsName[10];
	int GoodsPrice;
	struct Goods *next;
};
struct Goods *headadd,*tailadd;
struct Goods *ReadfromFile(void);
void GoodsAdd();
struct Goods *GoodsAlter();
void InitFace();
struct Goods *GoodsDel();
void InitFace();
void GoodsDemand();
void GoodsDerive(struct Goods *tou);
void GoodsDerive_wb(struct Goods *tou);
void EnterPassword();
void EnterFace();

void main(int argc, char* argv[])
{
	headadd=tailadd=NULL;
	system("color 1f");
	EnterPassword();
	InitFace();
	EnterFace();
}
//商品信息录入
void GoodsAdd()
{
	
	char ichoose;
	struct Goods *p;
	struct Goods *pp;
	p=(struct Goods *)malloc(sizeof(struct Goods));//对链表进行内存空间申请
	if(p==NULL)
	{
		printf("\t\t空间分配失败!");
		exit(0);
	}
	printf("\t\t请输入商品个数:");
	scanf("%ld",&p->GoodsNum);
	printf("\t\t请输入商品名:");
	scanf("%s",&p->GoodsName);
	printf("\t\t请输入商品价格:");
	scanf("%d",&p->GoodsPrice);
	if(headadd==NULL)//如果链表为空，则head为头结点
	{
		headadd=tailadd=p;
		tailadd->next=NULL;
	}
	else
	{
		tailadd->next=p;
		tailadd=p;
		tailadd->next=NULL;
	}
	printf("\t\t添加商品信息成功!\n");
	printf("\t\t是否继续(Y\\N)!");
	getchar();
	scanf("%c",&ichoose);
	if(ichoose=='Y'||ichoose=='y')
	{
		GoodsAdd();
	}
	else if(ichoose=='N'||ichoose=='n')
	{
		for(pp=headadd;pp!=NULL;pp=pp->next)
	{
		printf("\t\t%s\t\t%ld\t\t%d\n",pp->GoodsName,pp->GoodsNum,pp->GoodsPrice);
	}
		GoodsDerive(headadd);
	}
	
}

//商品信息修改
struct Goods *GoodsAlter()
{
	headadd=ReadfromFile();
	char AlterName[10];
	struct Goods *pp;
	struct Goods *p;
	p=headadd;
	for(pp=headadd;pp!=NULL;pp=pp->next)
	{
		printf("\t\t%s\t\t%ld\t\t%d\n",pp->GoodsName,pp->GoodsNum,pp->GoodsPrice);
	}
	if(headadd==NULL)
	{
		printf("\t\t购物车为空!\n");
		return(headadd);
	}
	printf("\t\t请输入要修改的商品的名字:");
	scanf("%s",&AlterName);
	while(strcmp(AlterName,p->GoodsName)!=0&&p->next!=NULL)
	{
		p=p->next;
	}
	if(strcmp(AlterName,p->GoodsName)==0)
	{
		printf("\t\t输入修改的商品名字:");
		scanf("%s",p->GoodsName);
		printf("\t\t输入修改后的价格:");
		scanf("%d",&p->GoodsPrice);
		printf("\t\t输入数量:");
		scanf("%ld",&p->GoodsNum);
		printf("修改成功!");
		GoodsDerive_wb(headadd);
	}
	else
	{
		printf("\t\t输入有误!\n");
	}
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
	printf("\t\t*\t\t邹佳良     \t肖安建\t\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t西南石油大学计科院物联网工程\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
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
		printf("\n");
		printf("\t\t密码错误!\n");
		printf("\t\t3秒后自动退出!\n");
		Sleep(3000);//延长时间
		exit(0);
	}
	system("cls");//清屏

}
//商品删除
struct Goods *GoodsDel()
{
	headadd=ReadfromFile();
	char DelName;
	struct Goods *p=headadd,*pr=headadd,*pp;
	for(pp=headadd;pp!=NULL;pp=pp->next)
	{
		printf("\t\t%s\t\t%ld\t\t%d\n",pp->GoodsName,pp->GoodsNum,pp->GoodsPrice);
	}
	if(headadd==NULL)
	{
		printf("\t\t无可删除商品\n");
		return(headadd);
	}
	printf("\t\t请输入要删除的商品名称:");
	scanf("%s",&DelName);
	while(strcmp(&DelName,p->GoodsName)!=0&&p->next!=NULL)
	{
		pr=p;
		p=p->next;
	}
	if(strcmp(&DelName,p->GoodsName)==0)
	{
		if(p==headadd)
		{
			headadd=p->next;
			printf("\t\t删除成功\n");
			GoodsDerive_wb(headadd);
		}
		else
		{
			pr->next=p->next;
			printf("删除成功!\n");
			GoodsDerive_wb(headadd);
		}
		free(p);
	}
	else
	{
		printf("输入的商品名称有错误!\n");
	}
}
//购物车信息查询
void GoodsDemand()
{
	struct Goods *node;
	node=ReadfromFile();
	
	//system("cls");
	printf("\t\t*********************************************************\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t\t购物车信息查询\t\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*********************************************************\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t商品名称\t商品个数\t商品价格\n");
	//for(node=head;node!=NULL;node=node->next)
	do
	{
		printf("\t\t%s\t\t%ld\t\t%d\n",node->GoodsName,node->GoodsNum,node->GoodsPrice);
		node=node->next;
	}while(node!=NULL);
}

//商品信息导出到文件
void GoodsDerive(struct Goods *tou)
{
	struct Goods *p=tou;
	//char a[10]={"商品名称"},b[10]={"商品个数"},c[10]={"商品价格"},e[10]={"     "};
	FILE *fp;
	fp=fopen("商品信息.txt","ab");
	if(fp==NULL)
	{
		printf("请检查当前目录是否具有写入%s的功能","商品信息.txt");
	}
	//fprintf(fp,"%s\t\t\t%s\t\t\t%s\n",a,b,c);
	while(p!=NULL)
	{
		if(fwrite(p,LEN,1,fp)!=1)
		{
			printf("写入数据错误\n");
			fclose(fp);
			return;
		}
		p=p->next;
	}
	fclose(fp);
	printf("\t\t*********************************************************\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t\t商品信息导出\t\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*********************************************************\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t成功将数据保存到%s文件中\n","商品信息.txt");
}
void GoodsDerive_wb(struct Goods *tou)
{
	struct Goods *p=tou;
	//char a[10]={"商品名称"},b[10]={"商品个数"},c[10]={"商品价格"},e[10]={"     "};
	FILE *fp;
	fp=fopen("商品信息.txt","wb");
	if(fp==NULL)
	{
		printf("请检查当前目录是否具有写入%s的功能","商品信息.txt");
	}
	//fprintf(fp,"%s\t\t\t%s\t\t\t%s\n",a,b,c);
	while(p!=NULL)
	{
		if(fwrite(p,LEN,1,fp)!=1)
		{
			printf("写入数据错误\n");
			fclose(fp);
			return;
		}
		p=p->next;
	}
	fclose(fp);
	printf("\t\t*********************************************************\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t\t商品信息导出\t\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*********************************************************\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t*\n");
	printf("\t\t成功将数据保存到%s文件中\n","商品信息.txt");
}

//进入界面
void EnterFace()
{
	char a;
	while(1)
	{
	printf("\t\t*********************************************************\n");
		printf("\t\t*\t\t\t\t\t\t\t*\n");
		printf("\t\t*\t\t\t\t\t\t\t*\n");
		printf("\t\t*\t\t\t购物车  \t\t\t*\n");
		printf("\t\t*\t\t\t\t\t\t\t*\n");
		printf("\t\t*\t\t\t\t\t\t\t*\n");
		printf("\t\t*\t\t1.商品信息添加\t\t\t\t*\n");
		printf("\t\t*\t\t2.商品信息删除\t\t\t\t*\n");
		printf("\t\t*\t\t3.商品信息修改\t\t\t\t*\n");
		printf("\t\t*\t\t4.商品信息查询\t\t\t\t*\n");
		printf("\t\t*\t\t5.商品信息导出\t\t\t\t*\n");
		printf("\t\t*\t\t6.退出系统\t\t\t\t*\n");
		printf("\t\t*\t\t\t\t\t\t\t*\n");
		printf("\t\t*\t\t\t\t\t\t\t*\n");
		printf("\t\t*\t\t西南石油大学计科院物联网工程\t\t*\n");
		printf("\t\t*\t\t\t\t\t\t\t*\n");
		printf("\t\t*\t\t\t\t\t\t\t*\n");
		printf("\t\t*********************************************************\n");
		printf("\t\t*\t\t\t\t\t\t\t*\n");
		printf("\t\t*\t\t\t\t\t\t\t*\n");
		printf("\t\t*请选择菜单1-4：");
		scanf("%d",&a);
				if(a==1)
		{
			system("cls");
			printf("\t\t*********************************************************\n");
			printf("\t\t*\t\t\t\t\t\t\t*\n");
			printf("\t\t*\t\t\t商品信息添加\t\t\t*\n");
			printf("\t\t*\t\t\t\t\t\t\t*\n");
			printf("\t\t*********************************************************\n");
			printf("\t\t*\t\t\t\t\t\t\t*\n");
			printf("\t\t*\t\t\t\t\t\t\t*\n");
			GoodsAdd();
			printf("\t\t");
			system("pause");
			system("cls");
		}
		else if (a == 2)
		{
			system("cls");
			printf("\t\t*********************************************************\n");
			printf("\t\t*\t\t\t\t\t\t\t*\n");
			printf("\t\t*\t\t\t商品信息删除\t\t\t*\n");
			printf("\t\t*\t\t\t\t\t\t\t*\n");
			printf("\t\t*********************************************************\n");
			printf("\t\t*\t\t\t\t\t\t\t*\n");
			printf("\t\t*\t\t\t\t\t\t\t*\n");
			printf("\t\t*\t\t\t\t\t\t\t*\n");
			printf("\t\t商品名称\t商品编号\t商品价格\n");
			GoodsDel();
			printf("\t\t");
			system("pause");
			system("cls");
		}
		else if (a == 3)
		{
			system("cls");
			printf("\t\t*********************************************************\n");
			printf("\t\t*\t\t\t\t\t\t\t*\n");
			printf("\t\t*\t\t\t商品信息修改\t\t\t*\n");
			printf("\t\t*\t\t\t\t\t\t\t*\n");
			printf("\t\t*********************************************************\n");
			printf("\t\t*\t\t\t\t\t\t\t*\n");
			printf("\t\t*\t\t\t\t\t\t\t*\n");
			printf("\t\t*\t\t\t\t\t\t\t*\n");
			printf("\t\t商品名称\t商品编号\t商品价格\n");
			GoodsAlter();
			printf("\t\t");
			system("pause");
			system("cls");
		}
		else if (a == 4)
		{
			system("cls");
			GoodsDemand();
			printf("\t\t");
			system("pause");
			system("cls");
		}
		/*else if(a==5)
		{
			system("cls");
			GoodsDerive(head);
			printf("\t\t");
			system("pause");
			system("cls");
		}*/
		else if(a==6)
		{
			printf("\t\t");
			exit(0);
		}
	}
}
//从文件中将信息读取
struct Goods *ReadfromFile(void)
{
	FILE *fp;
	struct Goods *tou=NULL;
	struct Goods *p1;
	struct Goods *p2;
	if((fp=fopen("商品信息.txt","rb+"))==NULL)
	{
		printf("读取失败\n");
		exit(0);
	}
	while(!feof(fp))
	{
		if((p1=(struct Goods*)malloc(LEN))==NULL){
			printf("内存申请错误\n");
			fclose(fp);
			exit(0);
		}
		if(fread(p1,LEN,1,fp)!=1){
			free(p1);
			break;
		}
		if(tou==NULL)
			tou=p2=p1;
		else{
			p2->next=p1;
			p2=p1;
		}
	}
	/*while(!feof(fp))
	{
		p1=head;
		fread(p1,LEN,1,fp);
		p2=p1->next;
	}*/
	fclose(fp);
	return (tou);
}
