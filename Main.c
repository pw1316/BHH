#include<graphics.h>
#include<stdio.h>
#include<dos.h>

#define UP 0x4800
#define DOWN 0x5000
#define LEFT 0x4B00
#define RIGHT 0x4D00
#define ESC 0x011B
#define ENTER 0x1C0D
#define BACKSPACE 0x0E08

#define BAR_WIDTH 125 
#define BAR_HEIGHT 50
#define RECIPENUM 30 //������ 
#define HELP_H 22 //�׿�� 
#define HELP_W 800 //�׿�� 

int curid=-1;
void *help; //����׿������� 

struct profile {
		char name[11];
   		char gender[2];
   		char age[3];
   		char height[4];
   		char weight[4];
   		int recoder; // ��¼���� ��ƽ��
   		double energy;
   		double procnt;
	};
struct menu{
	int recipeID;
	char name[70];
	int energy;//kcal
	int procnt;//�����ʣ�
} load[100];

void readmenu();
void pw_background();//������ 
void pw_homepage();//����ҳ
void recode(int index);
void pw_homebar3(); //show recipe
void pw_homebar0();//My info +change
void pw_homebar4();//change profile
void pw_homebar2();
struct profile* readfile (int userid);
void newfile(int userid);

char* input(int x,int y,int max);

int main(){
	FILE *fp;
	int driver=DETECT,mode=VESA_800x600x8bit;
//	int maini;//readmenu
	initgraph(&driver,&mode,"PW");
	readmenu();
////readmenu
//	fp=fopen("recipes","r");
//	for (maini=0;maini<RECIPENUM;maini++){
//		fscanf(fp,"%d\n%s\n%d\n%d\n",&((load+maini)->recipeID),(load+maini)->name,&((load+maini)->energy),&((load+maini)->procnt));
//	}//�����в�Ʒ��ȡ
	fclose(fp);
	pw_background();
	pw_homepage();
	return 0;
}

void pw_background(){
	PIC *title;
	
	setfillstyle(SOLID_FILL,BLUE);
	bar(0,0,799,577);
	setfillstyle(SOLID_FILL,DARKGRAY);
	bar(0,578,799,599);

	setcolor(WHITE);
	title=get_ttf_text_pic("My Health","font\\msyhbd.ttc",60); 
	draw_picture(200,50,title);
	destroy_picture(title);
	
	outtextxy(8,582,"Roll up(UP,LEFT) Roll down(DOWN,RIGHT) Confirm(ENTER)");
}

void pw_homepage(){
	struct Pos{
		int x;
		int y;
	};//��ʾλ��
	int key;//���µļ�
	void *tmp_bar,*tmp_h_bar;//�洢��ʱ���飬getimage��
	int index=0;//����������
	struct Pos pos[5]={{80,210},{80,280},{80,350},{80,420},{80,490}};//������λ��
	char *text[5]={"My Info","My Eating","Food","Recipe","Change Profile"};//�������ϴ�ӡ����Ϣ 
	
	/*����getimage�ռ�*/
	tmp_bar=malloc(imagesize(pos[0].x,pos[0].y,pos[0].x+BAR_WIDTH-1,pos[0].y+BAR_HEIGHT-1));
	tmp_h_bar=malloc(imagesize(pos[0].x,pos[0].y,pos[0].x+BAR_WIDTH-1,pos[0].y+BAR_HEIGHT-1));
	
	/*�õ���������*/
	setfillstyle(SOLID_FILL,RED);
	bar(pos[0].x,pos[0].y,pos[0].x+BAR_WIDTH-1,pos[0].y+BAR_HEIGHT-1);
	getimage(pos[0].x,pos[0].y,pos[0].x+BAR_WIDTH-1,pos[0].y+BAR_HEIGHT-1,tmp_h_bar);
	
	/*�õ���������*/ 
	setfillstyle(SOLID_FILL,DARKGRAY);
	bar(pos[0].x,pos[0].y,pos[0].x+BAR_WIDTH-1,pos[0].y+BAR_HEIGHT-1);
	getimage(pos[0].x,pos[0].y,pos[0].x+BAR_WIDTH-1,pos[0].y+BAR_HEIGHT-1,tmp_bar);
	
	/*�����鼰��*/ 
	putimage(pos[0].x,pos[0].y,tmp_h_bar,COPY_PUT);
	putimage(pos[1].x,pos[1].y,tmp_bar,COPY_PUT);
	putimage(pos[2].x,pos[2].y,tmp_bar,COPY_PUT);
	putimage(pos[3].x,pos[3].y,tmp_bar,COPY_PUT);
	putimage(pos[4].x,pos[4].y,tmp_bar,COPY_PUT);
	setcolor(YELLOW);
	outtextxy(pos[0].x+8,pos[0].y+BAR_HEIGHT*11/30,text[0]);
	setcolor(WHITE);
	outtextxy(pos[1].x+8,pos[1].y+BAR_HEIGHT*11/30,text[1]);
	outtextxy(pos[2].x+8,pos[2].y+BAR_HEIGHT*11/30,text[2]);
	outtextxy(pos[3].x+8,pos[3].y+BAR_HEIGHT*11/30,text[3]);
	outtextxy(pos[4].x+8,pos[4].y+BAR_HEIGHT*11/30,text[4]);
	
	/*ѭ����������*/ 
	while(1)
		if(bioskey(1)!=0){
			key=bioskey(0);
			if((key==UP||key==LEFT)&&index!=0){
				putimage(pos[index].x,pos[index].y,tmp_bar,COPY_PUT);
				setcolor(WHITE);
				outtextxy(pos[index].x+8,pos[index].y+BAR_HEIGHT*11/30,text[index]);
				index--;
				putimage(pos[index].x,pos[index].y,tmp_h_bar,COPY_PUT);
				setcolor(YELLOW);
				outtextxy(pos[index].x+8,pos[index].y+BAR_HEIGHT*11/30,text[index]);
			}//�����ϼ� 
			else if((key==DOWN||key==RIGHT)&&index!=4){
				putimage(pos[index].x,pos[index].y,tmp_bar,COPY_PUT);
				setcolor(WHITE);
				outtextxy(pos[index].x+8,pos[index].y+BAR_HEIGHT*11/30,text[index]);
				index++;
				putimage(pos[index].x,pos[index].y,tmp_h_bar,COPY_PUT);
				setcolor(YELLOW);
				outtextxy(pos[index].x+8,pos[index].y+BAR_HEIGHT*11/30,text[index]);
			}//�����¼� 
			else if(key==0x011B){
				return;
			}//����ESC 
			else if(key==ENTER){
				if(index==0) pw_homebar0();
				if(index==4) pw_homebar4();
				if(index==3) pw_homebar3();
				if(index==2) pw_homebar2();
			}//���»س�
			else printf("%x\n",key);//���԰������� 
		}
}

void pw_homebar0(){
	void *old=malloc(800*600);
	int line=220;
	struct profile* user;
	int key;
	char a[50];
	char s[50];
	char *del,delvalid[]="Invalid!";
	FILE *fdel;
	
	getimage(0,0,799,599,old);
	setfillstyle(SOLID_FILL,DARKGRAY);
	bar(440,210,700,529);
	bar(0,578,799,599);
	
	if(curid==-1){
		setcolor(WHITE);
		outtextxy(460,220,"No Information Yet");
		outtextxy(460,240,"\"Press Any Key To Continue\"");
		bioskey(0);
		putimage(0,0,old,COPY_PUT);
		return;
	}
	else{
		setcolor(WHITE);
		outtextxy(8,582,"Back(Bcs) ChangeInfo(c) DeleteUser(d)");
		user=readfile(curid);
		sprintf(a,"Name:%s",user->name);outtextxy(460,line,a);line+=20;
		sprintf(a,"Gender:%s",user->gender);outtextxy(460,line,a);line+=20;
		sprintf(a,"Age:%s",user->age);outtextxy(460,line,a);line+=20;
		sprintf(a,"Height:%scm",user->height);outtextxy(460,line,a);line+=20;
		sprintf(a,"Weight:%skg",user->weight);outtextxy(460,line,a);line+=20;
		while(1)
		if(bioskey(1)!=0){
			key=bioskey(0);
			if(key==0x2E63){//c
				setfillstyle(SOLID_FILL,DARKGRAY);
				bar(440,210,700,529);
				newfile(curid);
				line=220;	
				setfillstyle(SOLID_FILL,DARKGRAY);
				bar(440,210,700,529);
				setcolor(WHITE);
				outtextxy(460,line,"DONE!");line+=20;
				strcpy(s,"Your Info Has Been Changed");
				outtextxy(460,line,s);line+=20;
				outtextxy(460,line,"\"Press Any Key To Continue\"");line+=20;
				bioskey(0);
				setfillstyle(SOLID_FILL,DARKGRAY);
				bar(440,210,700,529);
				line=220;
				user=readfile(curid);
				setcolor(WHITE);
				sprintf(a,"Name:%s",user->name);outtextxy(460,line,a);line+=20;
				sprintf(a,"Gender:%s",user->gender);outtextxy(460,line,a);line+=20;
				sprintf(a,"Age:%s",user->age);outtextxy(460,line,a);line+=20;
				sprintf(a,"Height:%scm",user->height);outtextxy(460,line,a);line+=20;
				sprintf(a,"Weight:%skg",user->weight);outtextxy(460,line,a);line+=20;
			}
			else if(key==0x2064){//d
				setfillstyle(SOLID_FILL,DARKGRAY);
				bar(440,210,700,529);
				line=220;
				setcolor(WHITE);
				outtextxy(460,line,"Delete Your Current Id?(Y/N)");line+=20;
				pwpwpw:
				del=input(460,line,1);
				if(del[0]=='Y'){
					setfillstyle(SOLID_FILL,DARKGRAY);
					bar(600,line,680,line+12);
					bar(480,line,500,line+12);
					sprintf(a,"save\\save%d.sav",curid);
					fdel=fopen(a,"w");
					fprintf(fdel,"null");
					fclose(fdel);
					curid=-1;
					putimage(0,0,old,COPY_PUT);
					return;
				}
				else if(del[0]!='N'){
					setcolor(WHITE);
					outtextxy(600,line,delvalid);
					setfillstyle(SOLID_FILL,DARKGRAY);
					bar(460,line,500,line+12);
					goto pwpwpw;
				}
				else{
					setfillstyle(SOLID_FILL,DARKGRAY);
					bar(440,210,700,529);
					line=220;
					user=readfile(curid);
					setcolor(WHITE);
					sprintf(a,"Name:%s",user->name);outtextxy(460,line,a);line+=20;
					sprintf(a,"Gender:%s",user->gender);outtextxy(460,line,a);line+=20;
					sprintf(a,"Age:%s",user->age);outtextxy(460,line,a);line+=20;
					sprintf(a,"Height:%scm",user->height);outtextxy(460,line,a);line+=20;
					sprintf(a,"Weight:%skg",user->weight);outtextxy(460,line,a);line+=20;
				}
			}
			else if(key==BACKSPACE){
				putimage(0,0,old,COPY_PUT);
				return;
			}//����ESC 
		}
	}
}

void pw_homebar3(){
	void *old;
	int index=1,key;
	int posx=90,posy=40;
	char a[50];
	PIC *name;
	old=malloc(800*600);
	getimage(0,0,799,599,old);
	sprintf(a,"pic\\%d.bmp",index);
	load_8bit_bmp(posx,posy,a);
	setcolor(RED);
	name=get_ttf_text_pic(load->name,"font\\msyhbd.ttc",20); 
	draw_picture(300,400,name);
	destroy_picture(name);
	while(1)
	if(bioskey(1)!=0){
		key=bioskey(0);
		if((key==UP||key==LEFT)&&index!=1){
			index--;
			sprintf(a,"pic\\%d.bmp",index);
			load_8bit_bmp(posx,posy,a);
			setcolor(RED);
			name=get_ttf_text_pic((load+index-1)->name,"font\\msyhbd.ttc",20); 
			draw_picture(300,400,name);
			destroy_picture(name);
		}//�����ϼ� 
		else if((key==DOWN||key==RIGHT)&&index!=RECIPENUM){
			index++;
			sprintf(a,"pic\\%d.bmp",index);
			load_8bit_bmp(posx,posy,a);
			setcolor(RED);
			name=get_ttf_text_pic((load+index-1)->name,"font\\msyhbd.ttc",20); 
			draw_picture(300,400,name);
			destroy_picture(name);
		}//�����¼� 
		else if(key==0x011B){
			putimage(0,0,old,COPY_PUT);
			return;
		}//����ESC 
	}
}

void pw_homebar4(){
	int line=220;
	int id=0,key,index=0;
	char s[50],idd[4];
	char a[50];
	struct profile* user;
	setfillstyle(SOLID_FILL,DARKGRAY);
	bar(440,210,700,529);
	
	setcolor(WHITE);
	outtextxy(460,line,"What Is Your Id?");line+=20;
	strcpy(idd,input(460,line,10));line+=20;
	while(idd[index]!=0){
		id=id*10+idd[index]-48;
		index++;
	}
	
	if(readfile(id)==NULL||readfile(id)!=NULL&&strcmp(readfile(id)->name,"null")==0){
		outtextxy(460,line,"This Id Does Not Exist");line+=20;
		outtextxy(460,line,"Now Creating A New One...");line+=20;
		outtextxy(460,line,"\"Press Any Key To Continue\"");line+=20;
		bioskey(0);
		setfillstyle(SOLID_FILL,DARKGRAY);
		bar(440,210,700,529);
		
		curid=id;
		newfile(id);
		line=220;	
		setfillstyle(SOLID_FILL,DARKGRAY);
		bar(440,210,700,529);
		setcolor(WHITE);
		outtextxy(460,line,"DONE!");line+=20;
		strcpy(s,"Please Remember your Id : ");
		strcat(s,idd);
		outtextxy(460,line,s);line+=20;
		outtextxy(460,line,"\"Press Any Key To Continue\"");line+=20;
		bioskey(0);
		setfillstyle(SOLID_FILL,BLUE);
		bar(440,210,700,529);
		return;
	}
	else{
		curid=id;
	}
	
	setfillstyle(SOLID_FILL,DARKGRAY);
	bar(440,210,700,529);
	setcolor(WHITE);
	line=220;
	strcpy(s,"Welcome! ");
	strcat(s,readfile(curid)->name);
	strcat(s,"!");
	outtextxy(460,line,s);line+=20;
	outtextxy(460,line,"\"Press Any Key To Continue\"");line+=20;
	bioskey(0);
	setfillstyle(SOLID_FILL,BLUE);
	bar(440,210,700,529);
	return;
}

/*----------------------------------------------------------------------------*/

struct profile* readfile (int userid){
	FILE *fp;
	struct profile* user;
	char c;
	char a[20];
	int n=0;
	sprintf(a,"save\\save%d.sav",userid);
	fp=fopen(a,"r");
	if(fp==NULL){
		return NULL; 
	}
	else{
		fscanf(fp,"%s%s%s%s%s\n",user->name,user->gender,user->age,user->height,user->weight);
		fclose(fp);
		return user;
	}
}

void newfile (int userid){
	FILE *fp;
	char a[50];
	char ss[11];
	int line=220;
	char valid[]="Invalid!";
	
	ss[0]=0;
	sprintf(a,"save\\save%d.sav",userid);
	fp=fopen(a,"w");
	
	setcolor(WHITE);
	
	outtextxy(460,line,"NAME:");line+=20;
	strcpy(ss,input(480,line,10));
	while(strcmp(ss,"null")==0||ss[0]>=48&&ss[0]<=57){
		setcolor(WHITE);
		outtextxy(600,line,valid);
		setfillstyle(SOLID_FILL,DARKGRAY);
		bar(480,line,560,line+12);
		strcpy(ss,input(480,line,10));
	}
	setfillstyle(SOLID_FILL,DARKGRAY);
	bar(600,line,680,line+12);
	fprintf(fp,"%s ",ss);line+=20;
	
	outtextxy(460,line,"GENDER:");line+=20;
	strcpy(ss,input(480,line,1));
	while(ss[0]!='M'&&ss[0]!='F'){
		setcolor(WHITE);
		outtextxy(600,line,valid);
		setfillstyle(SOLID_FILL,DARKGRAY);
		bar(480,line,488,line+12);
		strcpy(ss,input(480,line,1));
	}
	setfillstyle(SOLID_FILL,DARKGRAY);
	bar(600,line,680,line+12);
	fprintf(fp,"%s ",ss);line+=20;
	
	outtextxy(460,line,"AGE:");line+=20;
	strcpy(ss,input(480,line,2));
	while(ss[0]<48||ss[0]>57||ss[1]<48||ss[1]>57){
		setcolor(WHITE);
		outtextxy(600,line,valid);
		setfillstyle(SOLID_FILL,DARKGRAY);
		bar(480,line,500,line+12);
		strcpy(ss,input(480,line,2));
	}
	setfillstyle(SOLID_FILL,DARKGRAY);
	bar(600,line,680,line+12);
	fprintf(fp,"%s ",ss);line+=20;
	
	outtextxy(460,line,"HEIGHT:");line+=20;
	strcpy(ss,input(480,line,3));
	while(ss[0]<48||ss[0]>57||ss[1]<48||ss[1]>57||ss[2]<48||ss[2]>57){
		setcolor(WHITE);
		outtextxy(600,line,valid);
		setfillstyle(SOLID_FILL,DARKGRAY);
		bar(480,line,500,line+12);
		strcpy(ss,input(480,line,3));
	}
	setfillstyle(SOLID_FILL,DARKGRAY);
	bar(600,line,680,line+12);
	fprintf(fp,"%s ",ss);line+=20;
	
	outtextxy(460,line,"WEIGHT:");line+=20;
	strcpy(ss,input(480,line,3));
	while(ss[0]<48||ss[0]>57||ss[1]<48||ss[1]>57||ss[2]<48||ss[2]>57){
		setcolor(WHITE);
		outtextxy(600,line,valid);
		setfillstyle(SOLID_FILL,DARKGRAY);
		bar(480,line,500,line+12);
		strcpy(ss,input(480,line,3));
	}
	setfillstyle(SOLID_FILL,DARKGRAY);
	bar(600,line,680,line+12);
	fprintf(fp,"%s",ss);line+=20;
	
	fclose(fp);
}

//void writefile (int userid, struct profile *user){
//	FILE *fp;
//	char a[20];
//	int n,i;
//	sprintf(a,"save%d.sav",userid);
//	fp=fopen(a,"w");
//    fprintf(fp,"%s %s %s\n",user->name,user->num,user->score);
//    fclose(fp);
//}

char* input(int x,int y,int max){
	char c;
	char s[2],ss[11];
	int index=0;
	int key,pos=x;
	int line=y;
	s[1]=0;
	ss[index]=0;
	
	while(1){
		if(bioskey(1)!=0){
			key=bioskey(0);
			if(key==ENTER){
				return ss;
			}
			else if(key==BACKSPACE){
				if(pos>x){
					pos-=8;
					setfillstyle(SOLID_FILL,DARKGRAY);
					bar(pos,line,pos+8,line+13);
					index--;
					ss[index]=0;
				}
			}
			else if(index<max){
				c=key&0xFF;
				s[0]=c;
				outtextxy(pos,line,s);
				ss[index]=c;
				index++;
				ss[index]=0;
				pos+=8;
			}
		}
	}
}

void readmenu(){
	int i,x=0;
	char a[100];
	char *ap=a;
	//����Ϊʹ�÷���
	FILE *fp;
	fp=fopen("recipes","r");
	for (i=0;i<RECIPENUM;i++){
		fscanf(fp,"%d\n%s\n%d\n%d\n",&((load+i)->recipeID),(load+i)->name,&((load+i)->energy),&((load+i)->procnt));
	}//�����в�Ʒ��ȡ

	fclose(fp);
}
//
void pw_homebar2(){
		struct Pos{
		int x;
		int y;
	};//��ʾλ��
	void *old=malloc(800*600);
	int key;//���µļ�
	void *tmp_bar,*tmp_h_bar;//�洢��ʱ���飬getimage��
	int index=0;//����������
	struct Pos pos[5]={{300,200},{300,280},{300,350},{300,420},{300,490}};//������λ��
	char *text[5]={"Not eat","Some vegs","Many vegs","Some meat","Lots of meat"};//�������ϴ�ӡ����Ϣ 
	
	/*����getimage�ռ�*/
	tmp_bar=malloc(imagesize(pos[0].x,pos[0].y,pos[0].x+251-1,pos[0].y+BAR_HEIGHT-1));
	tmp_h_bar=malloc(imagesize(pos[0].x,pos[0].y,pos[0].x+251-1,pos[0].y+BAR_HEIGHT-1));
	getimage(0,0,799,599,old);
	/*�õ���������*/
	setfillstyle(SOLID_FILL,RED);
	bar(pos[0].x,pos[0].y,pos[0].x+251-1,pos[0].y+BAR_HEIGHT-1);
	getimage(pos[0].x,pos[0].y,pos[0].x+251-1,pos[0].y+BAR_HEIGHT-1,tmp_h_bar);
	
	/*�õ���������*/ 
	setfillstyle(SOLID_FILL,DARKGRAY);
	bar(pos[0].x,pos[0].y,pos[0].x+251-1,pos[0].y+BAR_HEIGHT-1);
	getimage(pos[0].x,pos[0].y,pos[0].x+251-1,pos[0].y+BAR_HEIGHT-1,tmp_bar);
	
	/*�����鼰��*/ 
	putimage(pos[0].x,pos[0].y,tmp_h_bar,COPY_PUT);
	putimage(pos[1].x,pos[1].y,tmp_bar,COPY_PUT);
	putimage(pos[2].x,pos[2].y,tmp_bar,COPY_PUT);
	putimage(pos[3].x,pos[3].y,tmp_bar,COPY_PUT);
	putimage(pos[4].x,pos[4].y,tmp_bar,COPY_PUT);
	setcolor(YELLOW);
	outtextxy(pos[0].x+8,pos[0].y+BAR_HEIGHT*11/30,text[0]);
	setcolor(WHITE);
	outtextxy(pos[1].x+8,pos[1].y+BAR_HEIGHT*11/30,text[1]);
	outtextxy(pos[2].x+8,pos[2].y+BAR_HEIGHT*11/30,text[2]);
	outtextxy(pos[3].x+8,pos[3].y+BAR_HEIGHT*11/30,text[3]);
	outtextxy(pos[4].x+8,pos[4].y+BAR_HEIGHT*11/30,text[4]);
	
	/*ѭ����������*/ 
	while(1)
		if(bioskey(1)!=0){
			key=bioskey(0);
			if((key==UP||key==LEFT)&&index!=0){
				putimage(pos[index].x,pos[index].y,tmp_bar,COPY_PUT);
				setcolor(WHITE);
				outtextxy(pos[index].x+8,pos[index].y+BAR_HEIGHT*11/30,text[index]);
				index--;
				putimage(pos[index].x,pos[index].y,tmp_h_bar,COPY_PUT);
				setcolor(YELLOW);
				outtextxy(pos[index].x+8,pos[index].y+BAR_HEIGHT*11/30,text[index]);
			}//�����ϼ� 
			else if((key==DOWN||key==RIGHT)&&index!=4){
				putimage(pos[index].x,pos[index].y,tmp_bar,COPY_PUT);
				setcolor(WHITE);
				outtextxy(pos[index].x+8,pos[index].y+BAR_HEIGHT*11/30,text[index]);
				index++;
				putimage(pos[index].x,pos[index].y,tmp_h_bar,COPY_PUT);
				setcolor(YELLOW);
				outtextxy(pos[index].x+8,pos[index].y+BAR_HEIGHT*11/30,text[index]);
			}//�����¼� 
			else if(key==0x011B){
				putimage(0,0,old,COPY_PUT);
				return;
			}//����ESC 
			else if(key==ENTER){
				recode(index);
			}//���»س�
		}
}

//ע�⣡�����������user���ݣ���Ϊû��read����ʱ����д
void recode(int index){
	int recoder;
	struct profile* user=readfile(curid); 
	int e=0,p=0;
	recoder=user->recoder; 
	user->recoder++;
	if (index==1) {
		e=500;
		p=19;
	}
	else if (index==2){
		e=700;
		p=30;
	}
	else if (index==3){
		e=1000;
		p=40;
	}
	else {e=1500;p=60;}


	user->energy=((user->energy * recoder) + e)/(recoder+1);
	user->procnt=((user->procnt * recoder) + p)/(recoder+1);
	return;
}
