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
	int n=0;
	fp=fopen("save.dat","r");
	if(fp==NULL) return 0;
    while(!feof(fp)) {
       fscanf(fp, "%s %d %d ", reada[n].name,&reada[n].num,&reada[n].score);
       n++;
       }
	
	fclose(fp);
	if (userid<=n)
    *user = reada[userid];
    else
    	return 0;
    return 1;
}
void writefile (int userid, struct profile *user){
	FILE *fp;
	struct profile writea[11];
	char c;
	int n,i;
	for(n=0;readfile(n,writea + n);n++);
	writea[userid]=*user;
	fp=fopen("save.dat","w");
    for(i=0; i < n-1; i++) 
      fprintf(fp, "%s %d %d\n", writea[i].name,writea[i].num,writea[i].score);
    fclose(fp);
}
int newfile (){
	FILE *fp;
	fp=fopen("save.dat","w");
	char a[]="id";
	int x=0;
	fprintf(fp, "%s %d %d\n",a,x,x);
	fclose(fp);
}
int zmjtestmain(){
	char a[2];
	struct profile test2={"test2",1,100},test1={"\0",0,0};
	struct profile *p,*q;
	p=&test2;
	q=&test1;
	newfile();
	writefile(0,p);
	readfile(0,q);
	printf("%s %d %d\n",test1.name,test1.num,test1.score);
	gets(a);
    return 0;
}