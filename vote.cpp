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
}date;//日期类型
date getDate()//获取当前日期 
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
		printf("日期读取失败\n");
		return 0; 
	}
	int i=0;
	printf("投票期限: "); 
	while(fscanf(fp,"%d\t%d\t%d\n",&Days[i].year,&Days[i].month,&Days[i].day)!=EOF)
	{
		printf("%d-%d-%d ",Days[i].year,Days[i].month,Days[i].day); 
		i++;
	}
	printf("\n当前日期: %d-%d-%d ",Year,Month,Day);
	for(int i=0;i<days;i++)
		if(Days[i].day==Day&&Days[i].month==Month&&Days[i].year==Year)
		{
			printf("当前是第%d天投票\n",i+1);
			return i+1;
		}
	if(i==days){
		printf("不在投票时间内\n"); 
		return 0;
	}
	fclose(fp);
	printf("\n");
}
int currentDay=setDay();
typedef struct recode_of_vote
{
    int teachers[nums];//教师列表
    int c;//标记是否已投
}rec;
typedef struct info_of_student
{
    int num;//学生编号
    char name[20], edu[50];//姓名和学校名称
    rec recode;//当天的投票纪录
}stu;
typedef struct node_of_linkedList
{
	stu data;
	struct node_of_linkedList *next;
}node;
typedef struct info_of_teachers
{
    int num;//教师编号
    char name[20];//姓名
    int poll;//得票数 
}tea;
node *createList()//创建链表 
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
		printf("内存不足\n"); 
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
node* empty(node *stuNode)//清空节点数据
{
	memset(stuNode->data.recode.teachers,0,sizeof(stuNode->data.recode.teachers));
	return stuNode;
}
node* deal(node *list)
{
	node *stuNode;int num,n,m,c;
	printf("输入学号:");
	scanf("%d",&num);
	stuNode=serchNode(list,num);
	if(!stuNode){
		printf("学号不存在\n");
		return list; 
	}
	if(strcmp(stuNode->data.edu,"MKU")){
		printf("只允许指定院校学生投票\n");
		return list;
	}
	if(stuNode->data.recode.c){
		printf("当日请勿二次投票\n"); 
		return list; 
	}
	printf("请输入本次投票数: ");
	scanf("%d",&n);
	if(n<votemin||n>votemax){
		printf("违反投票规则，自动退出\n");
		stuNode=empty(stuNode);
		return list;
	}
	for(int i=0;i<n;i++)
	{
		printf("输入所投序号: ");
		scanf("%d",&m);
		if(m<1||m>nums){
			printf("输入有误，本次投票作废，请重新投票\n");
			stuNode=empty(stuNode);
		}
		stuNode=vote(stuNode,m);
	}
	for(int i=0;i<nums;i++)
		if(stuNode->data.recode.teachers[i]>1)
		{
			stuNode=empty(stuNode);
			printf("重复投票，本票作废，请重新投票\n");
			return list;	
		}
	printf("是否确认选择？(1.是 2.否):");
	scanf("%d",&c);
	if(c==1){
		stuNode->data.recode.c=1;//标记已投 
		printf("本次投票生效，不可撤回，不可修改\n"); 
	}
	else{
		printf("本次投票无效，请重新投票");
		stuNode=empty(stuNode);
	}
	printf(line);
	printf("\n");
	return list;
}
void start(node **lists)
{
	if(!currentDay){
		printf("不在投票时间内，无法进行投票\n");
		return; 
	} 
	printf("开始投票环节(至少投一票，至多投三票，每个候选人只能被投一票)\n");
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
		printf("NO.%d 编号: 0%d 姓名: %s 票数: %d",i+1,show[i].num,show[i].name,show[i].poll);
		printf("\n");
	}
	printf("\n");
}
rec unfold(int num)//将十进制数展开为二进制再存入数组 
{
	rec recode;int len=nums;
	while(num){
		recode.teachers[--len]=num%2;
		num=num/2;
	}
	recode.c=1;
	return recode;
}
int compress(rec recode)//将数组转化为二进制再压缩成十进制 
{
	int c=-1,num=0;
	for(int i=nums-1;i>=0;i--)
	{
		num+=recode.teachers[i]*(int)pow(2,(++c));
	}
	return num;
}
node* initList(node *headNode)//首次初始化链表 
{
	FILE *fp;stu person;
	fp=fopen(stufile,"r");
	if(!fp){
		printf("文件打开失败\n");
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
{//从记录文件中读入记录信息第二次初始化链表 
	FILE *fp;rec recode;int res,num;node *p;
	if(day==1) fp=fopen(day1file,"r");
	if(day==2) fp=fopen(day2file,"r");
	if(day==3) fp=fopen(day3file,"r");
	if(!fp){
		printf("文件打开失败\n");
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

void initData(node **lists)//完全初始化 
{
	for(int i=0;i<days;i++)
	{
		lists[i]=initList(lists[i]);
		lists[i]=readInfo(lists[i],i+1);
	}
}
void writeInfo(node **lists)//只会写入当天对应的文件 
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
		printf("写入文件失败\n");
		return; 
	}
	while(p){
		person=p->data;
		if(person.recode.c)//有投票记录则写入文件 
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
		printf("文件打开失败\n");
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
	printf("\n学号: %d 姓名: %s\n",person.num,person.name);
	printf("所属院校: %s\n",person.edu);
	if(person.recode.c){
		printf("投票情况: 已投\n");
		printf("所投序号: "); 
		for(int i=0;i<nums;i++)
			if(person.recode.teachers[i])
			printf("%d ",i+1);
		printf("\n");
	}
	else
		printf("投票情况：未投\n"); 
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
void showCandi(node **lists)//展示候选人信息 
{ 
	tea *candis=initCandi();//初始化数组 
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
		printf("\n序号:%d  教师编号: %d 姓名: %s 票数: %d\n",i+1,candis[i].num,candis[i].name,candis[i].poll);
		printf(line);
		printf("\n");
	}
	printf("\n");
	printf("是否显示排名?(1.是 2.否)?: ");
	int c;scanf("%d",&c);
	if(c==1){
		printf("排名如下:\n");
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
	printf("输入查看天数(1.第一天 2.第二天 3.第三天): ");
	scanf("%d",&c); 
	if(c>currentDay){
		printf("该日投票还未开始\n");
		return; 
	}
	printList(lists[c-1]);
}
void serchInfo(node **lists)
{
	int num;
	printf("输入查找学号: ");
	scanf("%d",&num);
	node *p=serchNode(lists[0],num);
	if(p==NULL){
		printf("学号不存在\n");
		return;
	} 
	output(p->data);
}
void menu(node **lists)
{
	int c;
	printf(line);
	printf("\n1.开始投票\n2.结束投票\n3.查看候选人名单及其当前计票结果\n4.显示单日学生投票情况\n5.查找学生信息\n");
	printf(line);
	printf("\n输入选项: ");
	scanf("%d",&c);
	switch(c)
	{
		case 1:start(lists);break;
		case 2:;break;
		case 3:showCandi(lists);break;
		case 4:dayList(lists);break;
		case 5:serchInfo(lists);break; 
		default:printf("输入有误，请重新输入\n");
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
		printf("\n是否继续使用本程序？(1.是 2.否):");
		int c;scanf("%d",&c);
		if(c==1){
			printf("继续运行\n");
			continue;
		}
		else{
			printf("程序结束"); 
			break;
		}
	}
	writeInfo(lists); 
	system("pause"); 
	return 0;
 } 
