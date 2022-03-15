#include <stdio.h>  
#include <time.h>  
#include <stdlib.h>
#include <string.h>
#define timefile "date.txt"
typedef struct date_of_vote
{
	int year;
	int month;
	int day;
}date;
date tom(date today,int *m)
{
	date t;
	if(today.month==12&&today.day==31)
	{//跨年 
		t.year=today.year+1;
		t.day=1;t.month=1;
	}
	else if(today.day==m[today.month])//跨月 
	{
		t.day=1;
		t.year=today.year;
		t.month=today.month+1; 
	}
	else{
		t.day=today.day+1;
		t.month=today.month;
		t.year=today.year;
	}
	return t;
}
int run(int year)
{
	if((year%4==0&&year%100!=0)||year%400==0)
		return 1;
	return 0;
}
int main(void)
{
	int year,day,month,months[13]; 
	months[1]=months[3]=months[5]=months[7]=months[8]=months[10]=months[12]=31;
	months[4]=months[6]=months[9]=months[11]=30;
	months[2]=28;
	printf("设定投票开始日期\n");
	printf("输入年:");
	scanf("%d",&year);
	if(run(year)){
		months[2]=29;
	}
	printf("输入月:");
	scanf("%d",&month);
	if(month<1||month>12){
		printf("输入错误");
		return 0;
	}
	printf("输入日:");
	scanf("%d",&day);
	if(day>months[month]||day<0)
	{
		printf("输入错误");
		return 0;
	}
	date day1={year,month,day},day2,day3;
	day2=tom(day1,months);
	day3=tom(day2,months);
	printf("日期设定成功\n"); 
	printf("允许投票日期分别是:\n");
	printf("%d-%d-%d\n",day1.year,day1.month,day1.day);
	printf("%d-%d-%d\n",day2.year,day2.month,day2.day);
	printf("%d-%d-%d\n",day3.year,day3.month,day3.day);
	FILE *fp;
	fp=fopen(timefile,"w");
	fprintf(fp,"%d\t%d\t%d\n",day1.year,day1.month,day1.day);
	fprintf(fp,"%d\t%d\t%d\n",day2.year,day2.month,day2.day);
	fprintf(fp,"%d\t%d\t%d\n",day3.year,day3.month,day3.day);
	system("pause");
	return 0;
}
