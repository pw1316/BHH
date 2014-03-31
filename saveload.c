#include <stdio.h>
struct profile {
		char name[10];
   		int num;
   		int score;
	};
int readfile (int userid,struct profile *user){
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
int newfile (int userid){
	FILE *fp;
	char a[10];
	sprintf(a,"save%d.sav",userid);
	fp=fopen(a,"w");
	int x=0;
	fprintf(fp, "%s %d %d\n",a,x,x);
	fclose(fp);
}
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
