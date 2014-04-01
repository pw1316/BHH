#include <stdio.h>
//结构内容等待修改
struct profile {
		char name[10];
   		int num;
   		int score;
	};
//userid为用户编号，生成save%d.sav作为标记 | user为结构指针用于传递读取or写入的信息
void readfile (int userid,struct profile *user){
	FILE *fp;
	struct profile reada[10];
	char c;
	char a[10];
	int n=0;
	sprintf(a,"save%d.sav",userid);
	fp=fopen(a,"r");
    fscanf(fp,"%s %d %d\n",user->name,&(user->num),&(user->score));
	fclose(fp);
}
void writefile (int userid, struct profile *user){
	FILE *fp;
	char a[10];
	int n,i;
	sprintf(a,"save%d.sav",userid);
	fp=fopen(a,"w");
    fprintf(fp,"%s %d %d\n",user->name,user->num,user->score);
    fclose(fp);
}
//新建一个覆盖原来的user
void newfile (int userid){
	FILE *fp;
	char a[10];
	sprintf(a,"save%d.sav",userid);
	fp=fopen(a,"w");
	int x=0;
	fprintf(fp, "%s %d %d\n",a,x,x);
	fclose(fp);
}








//test 将test2写入文件 再读入test1中 再输出
int testmain(){
	char a[2];
	struct profile test2={"test2",1,100},test1={"\0",0,0};
	struct profile *p,*q;
	p=&test2;
	q=&test1;
	newfile(0);
	writefile(0,p);
	readfile(0,q);
	printf("%s %d %d\n",test1.name,test1.num,test1.score);
	gets(a);
    return 0;
}
