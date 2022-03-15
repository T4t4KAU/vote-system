#include<stdio.h>
#include<stdlib.h>
#define line "-----------------------------------"
#define teafile "teachers.txt"

typedef struct info_of_teachers
{
    int num;//教师编号
    char name[20];//姓名
}tea;
typedef struct node_of_linkedList
{
	tea data;
	struct node_of_linkedList *next;
}node;
tea input()
{
	tea person;
	printf("输入编号: ");
	scanf("%d",&person.num);
	printf("输入姓名: ");
	scanf("%s",person.name);
	return person;
}
void output(tea person)
{
	printf(line);
	printf("\n教师编号: %d\n",person.num);
	printf("教师姓名: %s\n",person.name);
	printf(line);
	printf("\n");
}
node *createList()//创建链表 
{
	node *headNode;
	headNode=(node*)malloc(sizeof(node));
	headNode->next=NULL;
	return headNode;
}
node *createNode(tea newData)
{
	node *newNode;
	newNode=(node*)malloc(sizeof(node));
	newNode->data=newData;
	newNode->next=NULL;
	return newNode;
}
void insertNode(node *headNode,tea newData)
{
	node *newNode;
	newNode=createNode(newData);
	newNode->next=headNode->next;
	headNode->next=newNode;
}
node *serchNode(node *headNode,int num)
{
	node *p;
	p=headNode->next;
	while(p){
		if(p->data.num==num)
			return p;
		p=p->next;
	}
	return NULL;
}
void deleteNode(node *headNode,int num)
{
	node *p,*q;
	p=headNode->next;
	q=headNode;
	if(p==NULL){
		printf("链表为空\n");
		return;
	}
	while(p){
		if(p->data.num==num)
		{
			q->next=p->next;
			free(p);
		}
		q=p;
		p=p->next;
	}
	if(p==NULL){
		printf("编号不存在");
	}
}
void readInfo(node *headNode)
{
	FILE *fp;tea person;
	fp=fopen(teafile,"r");
	if(!fp){
		printf("文件打开失败");
		return;
	}
	while(fscanf(fp,"%d\t%s\n",&person.num,person.name)!=EOF)
		insertNode(headNode,person);
	fclose(fp);		
}
void writeInfo(node *headNode)
{
	FILE *fp;node *p;
	p=headNode->next;
	fp=fopen(teafile,"w");
	if(!fp){
		printf("文件写入失败");
		return;
	}
	while(p){
		fprintf(fp,"%d\t%s\n",p->data.num,p->data.name);
		p=p->next;
	}
	fclose(fp);
}
void append(node *headNode)
{
	tea person;
	person=input();
	insertNode(headNode,person);
	printf("添加完成\n"); 
}
void move(node *headNode)
{
	int num;
	printf("输入待删除编号:");
	scanf("%d",&num);
	deleteNode(headNode,num);
}
void serch(node *headNode)
{
	int num;
	printf("输入待查找编号:");
	scanf("%d",&num);
	node *p=serchNode(headNode,num);
	output(p->data);
}
void printList(node *headNode)
{
	node *p;
	p=headNode->next;
	while(p){
		output(p->data);
		p=p->next;
	}
}
void menu(node *list)
{
	int c;
	printf(line);
	printf("\n请选择功能:\n1.增加教师信息\n2.删除教师信息\n3.查找教师信息\n4.遍历教师信息\n");
	printf(line);
	printf("\n请输入选择:",&c);
	scanf("%d",&c); 
	switch(c)
	{
		case 1:append(list);break;
		case 2:move(list);break;
		case 3:serch(list);break;
		case 4:printList(list);break;
		default:printf("输入有误\n"); 
	}
}
int main(void)
{
	int c;
	node *list=createList();
	readInfo(list);
	while(1)
	{
		menu(list);
		writeInfo(list);
		printf("是否继续？(1.是 2.否):");
		scanf("%d",&c);
		if(c==1){
			printf("程序继续运行\n");
			continue; 
		}
		else{
			printf("程序退出");
			break;
		}
	}
	system("pause"); 
	return 0;
}




