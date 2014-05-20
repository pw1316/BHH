#include <stdio.h>
//结构内容等待修改
struct profile {
		char name[10];
   		int num;
   		int score;
	};
//菜品结构
struct menu{
	int recipeID;
	char name[70];
	int energy;//kcal
	int procnt;//蛋白质？
} load[100];
int recipenum=2;//NEW! 记录菜品总数！
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
	int x=0;
	sprintf(a,"save%d.sav",userid);
	fp=fopen(a,"w");
	fprintf(fp, "%s %d %d\n",a,x,x);
	fclose(fp);
}

//test 将test2写入文件 再读入test1中 再输出
int main(){
	int i,x=0;
	char a[100];
	char *ap=a;
//	FILE *fp;
//	fp=fopen("recipes","r");
//	fscanf(fp,"%d %s",&x,ap);
//	printf("%d \n%s\n", x,ap);
//以下为使用方法
	FILE *fp;
	fp=fopen("recipes","r");
	for (i=0;i<recipenum;i++){
		fscanf(fp,"%d\n%s\n%d\n%d\n",&((load+i)->recipeID),(load+i)->name,&((load+i)->energy),&((load+i)->procnt));
	}//把所有菜品读取
	fclose(fp);
	for (i=0;i<recipenum;i++)
	printf("%d \n%s \n%d \n%d\n",load[i].recipeID,load[i].name,load[i].energy,load[i].procnt);//测试输出
}
