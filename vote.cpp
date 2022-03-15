#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<memory.h>
#include<string.h>
#include<math.h>
#define nums 6
#define votemax 3
#define votemin 1
#define days 3
#define stufile "students.txt"
#define teafile "teachers.txt"
#define day1file "day1.txt"
#define day2file "day2.txt"
#define day3file "day3.txt"
#define datefile "date.txt"
#define line "---------------------------------------------"

typedef struct date_of_vote
{
	int year;
	int month;
	int day;
}date;//��������
date getDate()//��ȡ��ǰ���� 
{
	date Date;
	time_t timep,Tim;
    struct tm *p;
    time(&timep);
    p=localtime(&timep);
    Date.year=1900+p->tm_year;
    Date.month=1+p->tm_mon;
    Date.day=p->tm_mday;
    return Date;
}
int setDay()
{
	FILE *fp;date Days[3],preDate;
	preDate=getDate();
	int Year=preDate.year;
	int Month=preDate.month;
	int Day=preDate.day; 
    fp=fopen(datefile,"r");
	if(!fp){
		printf("���ڶ�ȡʧ��\n");
		return 0; 
	}
	int i=0;
	printf("ͶƱ����: "); 
	while(fscanf(fp,"%d\t%d\t%d\n",&Days[i].year,&Days[i].month,&Days[i].day)!=EOF)
	{
		printf("%d-%d-%d ",Days[i].year,Days[i].month,Days[i].day); 
		i++;
	}
	printf("\n��ǰ����: %d-%d-%d ",Year,Month,Day);
	for(int i=0;i<days;i++)
		if(Days[i].day==Day&&Days[i].month==Month&&Days[i].year==Year)
		{
			printf("��ǰ�ǵ�%d��ͶƱ\n",i+1);
			return i+1;
		}
	if(i==days){
		printf("����ͶƱʱ����\n"); 
		return 0;
	}
	fclose(fp);
	printf("\n");
}
int currentDay=setDay();
typedef struct recode_of_vote
{
    int teachers[nums];//��ʦ�б�
    int c;//����Ƿ���Ͷ
}rec;
typedef struct info_of_student
{
    int num;//ѧ�����
    char name[20], edu[50];//������ѧУ����
    rec recode;//�����ͶƱ��¼
}stu;
typedef struct node_of_linkedList
{
	stu data;
	struct node_of_linkedList *next;
}node;
typedef struct info_of_teachers
{
    int num;//��ʦ���
    char name[20];//����
    int poll;//��Ʊ�� 
}tea;
node *createList()//�������� 
{
	node *headNode;
	headNode=(node*)malloc(sizeof(node));
	headNode->next=NULL;
	return headNode;
}
node *createNode(stu newData)
{
	node *newNode;
	newNode=(node*)malloc(sizeof(node));
	if(!newNode){
		printf("�ڴ治��\n"); 
	}
	newNode->data=newData;
	return newNode;
}
void insertNode(node *headNode,stu newData)
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

node* vote(node *stuNode,int m)
{
	stuNode->data.recode.teachers[m-1]++;
	return stuNode;
}
node* empty(node *stuNode)//��սڵ�����
{
	memset(stuNode->data.recode.teachers,0,sizeof(stuNode->data.recode.teachers));
	return stuNode;
}
node* deal(node *list)
{
	node *stuNode;int num,n,m,c;
	printf("����ѧ��:");
	scanf("%d",&num);
	stuNode=serchNode(list,num);
	if(!stuNode){
		printf("ѧ�Ų�����\n");
		return list; 
	}
	if(strcmp(stuNode->data.edu,"MKU")){
		printf("ֻ����ָ��ԺУѧ��ͶƱ\n");
		return list;
	}
	if(stuNode->data.recode.c){
		printf("�����������ͶƱ\n"); 
		return list; 
	}
	printf("�����뱾��ͶƱ��: ");
	scanf("%d",&n);
	if(n<votemin||n>votemax){
		printf("Υ��ͶƱ�����Զ��˳�\n");
		stuNode=empty(stuNode);
		return list;
	}
	for(int i=0;i<n;i++)
	{
		printf("������Ͷ���: ");
		scanf("%d",&m);
		if(m<1||m>nums){
			printf("�������󣬱���ͶƱ���ϣ�������ͶƱ\n");
			stuNode=empty(stuNode);
		}
		stuNode=vote(stuNode,m);
	}
	for(int i=0;i<nums;i++)
		if(stuNode->data.recode.teachers[i]>1)
		{
			stuNode=empty(stuNode);
			printf("�ظ�ͶƱ����Ʊ���ϣ�������ͶƱ\n");
			return list;	
		}
	printf("�Ƿ�ȷ��ѡ��(1.�� 2.��):");
	scanf("%d",&c);
	if(c==1){
		stuNode->data.recode.c=1;//�����Ͷ 
		printf("����ͶƱ��Ч�����ɳ��أ������޸�\n"); 
	}
	else{
		printf("����ͶƱ��Ч��������ͶƱ");
		stuNode=empty(stuNode);
	}
	printf(line);
	printf("\n");
	return list;
}
void start(node **lists)
{
	if(!currentDay){
		printf("����ͶƱʱ���ڣ��޷�����ͶƱ\n");
		return; 
	} 
	printf("��ʼͶƱ����(����ͶһƱ������Ͷ��Ʊ��ÿ����ѡ��ֻ�ܱ�ͶһƱ)\n");
	lists[currentDay-1]=deal(lists[currentDay-1]);
}

void rank(tea* candi)
{
	tea show[nums];
	for(int i=0;i<nums;i++)
	show[i]=candi[i];
	for(int i=0;i<nums;i++)
	for(int j=i;j<nums;j++)
	{
		if(show[i].poll<show[j].poll)
		{
			tea temp;
			temp=show[i];
			show[i]=show[j];
			show[j]=temp;
		}
	}
	for(int i=0;i<nums;i++)
	{
		printf("NO.%d ���: 0%d ����: %s Ʊ��: %d",i+1,show[i].num,show[i].name,show[i].poll);
		printf("\n");
	}
	printf("\n");
}
rec unfold(int num)//��ʮ������չ��Ϊ�������ٴ������� 
{
	rec recode;int len=nums;
	while(num){
		recode.teachers[--len]=num%2;
		num=num/2;
	}
	recode.c=1;
	return recode;
}
int compress(rec recode)//������ת��Ϊ��������ѹ����ʮ���� 
{
	int c=-1,num=0;
	for(int i=nums-1;i>=0;i--)
	{
		num+=recode.teachers[i]*(int)pow(2,(++c));
	}
	return num;
}
node* initList(node *headNode)//�״γ�ʼ������ 
{
	FILE *fp;stu person;
	fp=fopen(stufile,"r");
	if(!fp){
		printf("�ļ���ʧ��\n");
		return NULL;
	}
	while((fscanf(fp,"%d\t%s\t%s\n",&person.num,person.name,person.edu))!=EOF)
	{
		person.recode.c=0;
		memset(person.recode.teachers,0,sizeof(person.recode.teachers));
		insertNode(headNode,person);
	}
	fclose(fp);
	return headNode;
}
node* readInfo(node *headNode,int day)
{//�Ӽ�¼�ļ��ж����¼��Ϣ�ڶ��γ�ʼ������ 
	FILE *fp;rec recode;int res,num;node *p;
	if(day==1) fp=fopen(day1file,"r");
	if(day==2) fp=fopen(day2file,"r");
	if(day==3) fp=fopen(day3file,"r");
	if(!fp){
		printf("�ļ���ʧ��\n");
		return NULL; 
	}
	while(fscanf(fp,"%d\t%d\n",&num,&res)!=EOF)
	{
		p=serchNode(headNode,num);
		recode=unfold(res); 
		p->data.recode=recode;
	}
	fclose(fp);
	return headNode;
}

void initData(node **lists)//��ȫ��ʼ�� 
{
	for(int i=0;i<days;i++)
	{
		lists[i]=initList(lists[i]);
		lists[i]=readInfo(lists[i],i+1);
	}
}
void writeInfo(node **lists)//ֻ��д�뵱���Ӧ���ļ� 
{
	if(!currentDay){
		return;
	} 
	FILE *fp;stu person;
	node *headNode=lists[currentDay-1];
	node *p=headNode->next;
	if(currentDay==1) fp=fopen(day1file,"w");
	if(currentDay==2) fp=fopen(day2file,"w");
	if(currentDay==3) fp=fopen(day3file,"w");
	if(!fp){
		printf("д���ļ�ʧ��\n");
		return; 
	}
	while(p){
		person=p->data;
		if(person.recode.c)//��ͶƱ��¼��д���ļ� 
			fprintf(fp,"%d\t%d\n",person.num,compress(person.recode)); 
		p=p->next;
	}
	fclose(fp);
}
tea *initCandi()
{
	FILE *fp;
	tea *candis=(tea*)malloc(nums*sizeof(tea));
	fp=fopen(teafile,"r");
	if(!fp){
		printf("�ļ���ʧ��\n");
		return NULL;
	}
	int i=0;
	while(fscanf(fp,"%d\t%s\n",&candis[i].num,candis[i].name)!=EOF)
	{
		candis[i].poll=0;
		i++;
	}
	fclose(fp);
	return candis;
}
void output(stu person)
{
	printf(line);
	printf("\nѧ��: %d ����: %s\n",person.num,person.name);
	printf("����ԺУ: %s\n",person.edu);
	if(person.recode.c){
		printf("ͶƱ���: ��Ͷ\n");
		printf("��Ͷ���: "); 
		for(int i=0;i<nums;i++)
			if(person.recode.teachers[i])
			printf("%d ",i+1);
		printf("\n");
	}
	else
		printf("ͶƱ�����δͶ\n"); 
	printf(line);
	printf("\n"); 
}
void printList(node *headNode)
{
	node *p=headNode->next;
	while(p){
		output(p->data);
		p=p->next;
	}
 } 
void showCandi(node **lists)//չʾ��ѡ����Ϣ 
{ 
	tea *candis=initCandi();//��ʼ������ 
	for(int i=0;i<days;i++)
	{
		node *p=lists[i]->next;
		while(p){
			for(int j=0;j<nums;j++)
			{
				if(p->data.recode.teachers[j])
					candis[j].poll++;
			}
			p=p->next;
		}
	}
	for(int i=0;i<nums;i++)
	{	
		printf(line);
		printf("\n���:%d  ��ʦ���: %d ����: %s Ʊ��: %d\n",i+1,candis[i].num,candis[i].name,candis[i].poll);
		printf(line);
		printf("\n");
	}
	printf("\n");
	printf("�Ƿ���ʾ����?(1.�� 2.��)?: ");
	int c;scanf("%d",&c);
	if(c==1){
		printf("��������:\n");
		printf(line);
		printf("\n");
		rank(candis);
		printf(line);
		printf("\n");
	} 
}
void dayList(node **lists)
{
	int c;
	printf("����鿴����(1.��һ�� 2.�ڶ��� 3.������): ");
	scanf("%d",&c); 
	if(c>currentDay){
		printf("����ͶƱ��δ��ʼ\n");
		return; 
	}
	printList(lists[c-1]);
}
void serchInfo(node **lists)
{
	int num;
	printf("�������ѧ��: ");
	scanf("%d",&num);
	node *p=serchNode(lists[0],num);
	if(p==NULL){
		printf("ѧ�Ų�����\n");
		return;
	} 
	output(p->data);
}
void menu(node **lists)
{
	int c;
	printf(line);
	printf("\n1.��ʼͶƱ\n2.����ͶƱ\n3.�鿴��ѡ���������䵱ǰ��Ʊ���\n4.��ʾ����ѧ��ͶƱ���\n5.����ѧ����Ϣ\n");
	printf(line);
	printf("\n����ѡ��: ");
	scanf("%d",&c);
	switch(c)
	{
		case 1:start(lists);break;
		case 2:;break;
		case 3:showCandi(lists);break;
		case 4:dayList(lists);break;
		case 5:serchInfo(lists);break; 
		default:printf("������������������\n");
	}
}
int main(void)
{
	node *lists[days];
	for(int i=0;i<days;i++)
	lists[i]=createList();
	initData(lists);
	while(1){
		menu(lists);
		printf("\n�Ƿ����ʹ�ñ�����(1.�� 2.��):");
		int c;scanf("%d",&c);
		if(c==1){
			printf("��������\n");
			continue;
		}
		else{
			printf("�������"); 
			break;
		}
	}
	writeInfo(lists); 
	system("pause"); 
	return 0;
 } 
