#include<graphics.h>

#define UP 0x4800
#define DOWN 0x5000
#define LEFT 0x4B00
#define RIGHT 0x4D00
#define ESC 0x011B
#define ENTER 0x1C0D
#define BACKSPACE 0x0E08

#define BAR_WIDTH 250
#define BAR_HEIGHT 50

int num[10][10],upalpha[26][10],lowalpha[26][10];		//数字，字母的点阵存储数组 
int curid=-1;
int userid[100],numid=0;
struct profile {
		char name[10];
   		int num;
   		int score;
	};

void pw_char();//初始化点阵方案 
void pw_print(char *p,int text[]); //在p位置打印text 
void pw_background();//画背景 
void pw_title();
void pw_homepage();//画主页 
void pw_myinfo();//画信息 
void pw_newid();
void pw_resetid();

int main(){
	int driver=DETECT,mode=VESA_800x600x8bit;
	int i;
	for(i=0;i<100;i++) userid[i]=0;
	initgraph(&driver,&mode,"PW");
	pw_char();
	pw_background();
	//pw_title();
	pw_homepage();
	return 0;
}


void pw_print(char *p,int text[]){
	int i,j;
	char *tmp;
	for(i=0;i<10;i++){
		for(j=7;j>0;j--){
			if(text[i]&(1<<j)){
				tmp=p+i*2*800+(4-j)*2;
				*tmp=*(tmp+1)=*(tmp+800)=*(tmp+801)=0xFF;
			}
		}
	}
}

void pw_char(){
	num[0][0]=0x7E;
	num[0][1]=0x46;
	num[0][2]=num[0][3]=num[0][4]=0x4A;
	num[0][5]=num[0][6]=num[0][7]=0x52;
	num[0][8]=0x62;
	num[0][9]=0x7E;

} 

void pw_background(){
	int i,j;
	char *p;
	void *wel;
	for(i=0;i<462400;i++){
		*(_vp+i)=BLUE;
    }
	for(i=462400;i<480000;i++){
	    *(_vp+i)=DARKGRAY;
	}
	pw_print(_vp+463205,num[0]);
	pw_print(_vp+463221,num[0]);
}

void pw_title(){
	FILE *fp=fopen("PIC.DAT","r");
	char *p=_vp+30*800+175;
	char c1,c2,num;
	int i,j;
	for(i=0;i<150;i++){
		for(j=0;j<450;j++){
			num=0;
			fscanf(fp,"%c%c",&c1,&c2);
			if(c1>='a'&&c1<='z'){
				num+=16*(c1-'a'+10);
			}
			else num+=16*(c1-'0');
			if(c2>='a'&&c2<='z'){
				num+=(c2-'a'+10);
			}
			else num+=(c2-'0');
			if(num==0xff){
				*(p+i*800+j)=WHITE;
			}
		}
		fscanf(fp,"\n");
	}
	fclose(fp);
}

void pw_homepage(){
	struct Pos{
		int x;
		int y;
	};//表示位置
	int key;//按下的键
	void *tmp_bar,*tmp_h_bar;//存储临时方块，getimage用
	int index=0;//高亮方块编号
	struct Pos pos[10]={{80,210},{80,300},{80,390},{80,480}};//各方块位置
	char *text[10]={"My Info","New Id","Food List","RESET ID"};//各方块上打印的信息 
	
	/*分配getimage空间*/
	tmp_bar=malloc(imagesize(pos[0].x,pos[0].y,pos[0].x+BAR_WIDTH-1,pos[0].y+BAR_HEIGHT-1));
	tmp_h_bar=malloc(imagesize(pos[0].x,pos[0].y,pos[0].x+BAR_WIDTH-1,pos[0].y+BAR_HEIGHT-1));
	
	/*得到高亮方块*/
	setfillstyle(SOLID_FILL,RED);
	bar(pos[0].x,pos[0].y,pos[0].x+BAR_WIDTH-1,pos[0].y+BAR_HEIGHT-1);
	getimage(pos[0].x,pos[0].y,pos[0].x+BAR_WIDTH-1,pos[0].y+BAR_HEIGHT-1,tmp_h_bar);
	setcolor(YELLOW);
	
	/*得到低亮方块*/ 
	setfillstyle(SOLID_FILL,DARKGRAY);
	bar(pos[0].x,pos[0].y,pos[0].x+BAR_WIDTH-1,pos[0].y+BAR_HEIGHT-1);
	getimage(pos[0].x,pos[0].y,pos[0].x+BAR_WIDTH-1,pos[0].y+BAR_HEIGHT-1,tmp_bar);
	setcolor(WHITE);
	
	/*画方块及字*/ 
	putimage(pos[0].x,pos[0].y,tmp_h_bar,COPY_PUT);
	putimage(pos[1].x,pos[1].y,tmp_bar,COPY_PUT);
	putimage(pos[2].x,pos[2].y,tmp_bar,COPY_PUT);
	putimage(pos[3].x,pos[3].y,tmp_bar,COPY_PUT);
	setcolor(YELLOW);
	outtextxy(pos[0].x+20,pos[0].y+BAR_HEIGHT*11/30,text[0]);
	setcolor(WHITE);
	outtextxy(pos[1].x+20,pos[1].y+BAR_HEIGHT*11/30,text[1]);
	outtextxy(pos[2].x+20,pos[2].y+BAR_HEIGHT*11/30,text[2]);
	outtextxy(pos[3].x+20,pos[3].y+BAR_HEIGHT*11/30,text[3]);
	
	/*循环键盘输入*/ 
	while(1)
		if(bioskey(1)!=0){
			key=bioskey(0);
			if(key==UP&&index!=0){
				putimage(pos[index].x,pos[index].y,tmp_bar,COPY_PUT);
				setcolor(WHITE);
				outtextxy(pos[index].x+20,pos[index].y+BAR_HEIGHT*11/30,text[index]);
				index--;
				putimage(pos[index].x,pos[index].y,tmp_h_bar,COPY_PUT);
				setcolor(YELLOW);
				outtextxy(pos[index].x+20,pos[index].y+BAR_HEIGHT*11/30,text[index]);
				setfillstyle(SOLID_FILL,BLUE);
				bar(100,100,200,200);
			}//按下上键 
			else if(key==DOWN&&index!=3){
				putimage(pos[index].x,pos[index].y,tmp_bar,COPY_PUT);
				setcolor(WHITE);
				outtextxy(pos[index].x+20,pos[index].y+BAR_HEIGHT*11/30,text[index]);
				index++;
				putimage(pos[index].x,pos[index].y,tmp_h_bar,COPY_PUT);
				setcolor(YELLOW);
				outtextxy(pos[index].x+20,pos[index].y+BAR_HEIGHT*11/30,text[index]);
				setfillstyle(SOLID_FILL,BLUE);
				bar(100,100,200,200);
			}//按下下键 
			else if(key==0x011B){
				return;
			}//按下ESC 
			else if(key==ENTER){
				if(index==1){
					pw_newid();
				}
				else if(index==3){
					pw_resetid();
				}
				else{
					setcolor(WHITE);
					outtextxy(100,100,"YOU,Stop!");
				}
			}//按下回车
			else printf("%x\n",key);//测试按键的码 
		}
}

void pw_resetid(){
	int i;
	FILE *fp=fopen("save.dat","w");
	fprintf(fp,"ID Name Num Score\n");
	for(i=0;i<100;i++) userid[i]=0;
	numid=0;
	fclose(fp);
}

void pw_newid(){
	FILE *fp;
	int key,pos=520;
	char c;
	char s[2],ss[11];
	int index=0;
	int id;
	s[1]=0;
	ss[index]=0;
	setfillstyle(SOLID_FILL,DARKGRAY);
	bar(440,210,700,529);
	
	randomize();
	id=random(100);
	while(userid[id]&&numid<100) id=random(100);
	if(numid>=100){
		setcolor(WHITE);
		outtextxy(475,220,"Can't Create More!");
		return;
	}
	
	curid=id;
	userid[id]=1;
	numid++;
	fp=fopen("save.dat","a");
	fprintf(fp,"%d ",id);
	setcolor(WHITE);
	outtextxy(475,220,"NAME:");
	while(1){
		if(bioskey(1)!=0){
			key=bioskey(0);
			if(key==ENTER){
				fprintf(fp,"%s ",ss);
				break;
			}
			else if(key==0x0e08){
				if(pos>520){
					pos-=8;
					setfillstyle(SOLID_FILL,DARKGRAY);
					bar(pos,220,pos+8,231);
					index--;
					ss[index]=0;
				}
			}
			else if(key==ESC) return;
			else if(index<10){
				c=key&0xFF;
				s[0]=c;
				outtextxy(pos,220,s);
				ss[index]=c;
				index++;
				ss[index]=0;
				pos+=8;
			}
		}
	}
	index=0;ss[index]=0;
	pos=512;
	outtextxy(475,240,"NUM:");
	while(1){
		if(bioskey(1)!=0){
			key=bioskey(0);
			if(key==ENTER){
				fprintf(fp,"%s ",ss);
				break;
			}
			else if(key==0x0e08){
				if(pos>512){
					pos-=8;
					setfillstyle(SOLID_FILL,DARKGRAY);
					bar(pos,240,pos+8,251);
					index--;
					ss[index]=0;
				}
			}
			else if(key==ESC) return;
			else if(index<10){
				c=key&0xFF;
				s[0]=c;
				outtextxy(pos,240,s);
				ss[index]=c;
				index++;
				ss[index]=0;
				pos+=8;
			}
		}
	}
	fprintf(fp,"\n");
	outtextxy(475,260,"DONE!");
	fclose(fp);
}

void pw_myinfo(){
	FILE *fp=fopen("SAVE.DAT","r");
	
	fclose(fp);
}
