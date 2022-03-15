#include<stdio.h>
#include<stdlib.h>
#define line "-----------------------------------"
#define teafile "teachers.txt"

typedef struct info_of_teachers
{
    int num;//��ʦ���
    char name[20];//����
}tea;
typedef struct node_of_linkedList
{
	tea data;
	struct node_of_linkedList *next;
}node;
tea input()
{
	tea person;
	printf("������: ");
	scanf("%d",&person.num);
	printf("��������: ");
	scanf("%s",person.name);
	return person;
}
void output(tea person)
{
	printf(line);
	printf("\n��ʦ���: %d\n",person.num);
	printf("��ʦ����: %s\n",person.name);
	printf(line);
	printf("\n");
}
node *createList()//�������� 
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
		printf("����Ϊ��\n");
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
		printf("��Ų�����");
	}
}
void readInfo(node *headNode)
{
	FILE *fp;tea person;
	fp=fopen(teafile,"r");
	if(!fp){
		printf("�ļ���ʧ��");
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
		printf("�ļ�д��ʧ��");
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
	printf("������\n"); 
}
void move(node *headNode)
{
	int num;
	printf("�����ɾ�����:");
	scanf("%d",&num);
	deleteNode(headNode,num);
}
void serch(node *headNode)
{
	int num;
	printf("��������ұ��:");
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
	printf("\n��ѡ����:\n1.���ӽ�ʦ��Ϣ\n2.ɾ����ʦ��Ϣ\n3.���ҽ�ʦ��Ϣ\n4.������ʦ��Ϣ\n");
	printf(line);
	printf("\n������ѡ��:",&c);
	scanf("%d",&c); 
	switch(c)
	{
		case 1:append(list);break;
		case 2:move(list);break;
		case 3:serch(list);break;
		case 4:printList(list);break;
		default:printf("��������\n"); 
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
		printf("�Ƿ������(1.�� 2.��):");
		scanf("%d",&c);
		if(c==1){
			printf("�����������\n");
			continue; 
		}
		else{
			printf("�����˳�");
			break;
		}
	}
	system("pause"); 
	return 0;
}




