#include<graphics.h>

#define UP 0x4800
#define DOWN 0x5000
#define LEFT 0x4B00
#define RIGHT 0x4D00
#define ESC 0x011B
#define ENTER 0x1C0D

#define BAR_WIDTH 250
#define BAR_HEIGHT 50

int num[10][10],upalpha[26][10],lowalpha[26][10];		//���֣���ĸ�ĵ���洢���� 

/**************************************************/
/*����Ļ�ϴ�ӡһ���ַ�                            */
/*������ p ��ӡ�����Ͻǵ�ĵ�ַ��text[] Ҫ��ӡ����*/ 
/*����ֵ����                                      */
/**************************************************/ 
void pwprint(char *p,int text[]){			//���ײ����� 
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

/**************************************************/
/*�����ַ��ĵ���                                  */
/*��������                                        */ 
/*����ֵ����                                      */
/**************************************************/ 
void pwchar(){
	num[0][0]=0x7E;
	num[0][1]=0x46;
	num[0][2]=num[0][3]=num[0][4]=0x4A;
	num[0][5]=num[0][6]=num[0][7]=0x52;
	num[0][8]=0x62;
	num[0][9]=0x7E;

} 

/*----------------------------------�������---------------------------------------*/
void pwbackground(){
	int i;
	char *p;
	for(i=0;i<462400;i++){
		*(_vp+i)=BLUE;
    }
	for(i=462400;i<480000;i++){
	    *(_vp+i)=0x1A;
	}
	pwprint(_vp+463205,num[0]);
	pwprint(_vp+463221,num[0]);
}
/*----------------------------------------------------------------------------------*/ 


/*----------------------------------��ҳ���----------------------------------------*/
void pwhomepage(){
	struct Pos{
		int x;
		int y;
	};//��ʾλ��
	int key;//���µļ�
	void *tmp_bar,*tmp_h_bar;//�洢��ʱ���飬getimage��
	int index=0;//����������
	struct Pos pos[10]={{275,240},{275,330},{275,420},{275,510}};//������λ��
	
	/*����getimage�ռ�*/
	tmp_bar=malloc(imagesize(pos[0].x,pos[0].y,pos[0].x+BAR_WIDTH-1,pos[0].y+BAR_HEIGHT-1));
	tmp_h_bar=malloc(imagesize(pos[0].x,pos[0].y,pos[0].x+BAR_WIDTH-1,pos[0].y+BAR_HEIGHT-1));
	
	/*�õ���������*/
	setfillstyle(SOLID_FILL,RED);
	bar(pos[0].x,pos[0].y,pos[0].x+BAR_WIDTH-1,pos[0].y+BAR_HEIGHT-1);
	getimage(pos[0].x,pos[0].y,pos[0].x+BAR_WIDTH-1,pos[0].y+BAR_HEIGHT-1,tmp_h_bar);
	
	/*����������*/ 
	setfillstyle(SOLID_FILL,0x1A);
	bar(pos[0].x,pos[0].y,pos[0].x+BAR_WIDTH-1,pos[0].y+BAR_HEIGHT-1);
	bar(pos[1].x,pos[1].y,pos[1].x+BAR_WIDTH-1,pos[1].y+BAR_HEIGHT-1);
	bar(pos[2].x,pos[2].y,pos[2].x+BAR_WIDTH-1,pos[2].y+BAR_HEIGHT-1);
	bar(pos[3].x,pos[3].y,pos[3].x+BAR_WIDTH-1,pos[3].y+BAR_HEIGHT-1);
	
	/*�������*/ 
	setcolor(WHITE);
	outtextxy(pos[1].x+20,pos[1].y+BAR_HEIGHT/5*2,"SBSBSB");
	outtextxy(pos[2].x+20,pos[2].y+BAR_HEIGHT/5*2,"SBSBSB");
	outtextxy(pos[3].x+20,pos[3].y+BAR_HEIGHT/5*2,"SBSBSB");
	
	/*�õ���������*/ 
	getimage(pos[0].x,pos[0].y,pos[0].x+BAR_WIDTH-1,pos[0].y+BAR_HEIGHT-1,tmp_bar);
	
	/*���������鼰������*/ 
	putimage(pos[0].x,pos[0].y,tmp_h_bar,COPY_PUT);
	setcolor(YELLOW);
	outtextxy(pos[0].x+20,pos[0].y+BAR_HEIGHT/5*2,"SBSBSB");
	
	/*ѭ����������*/ 
	while(1)
		if(bioskey(1)!=0){
			key=bioskey(0);
			if(key==UP&&index!=0){
				putimage(pos[index].x,pos[index].y,tmp_bar,COPY_PUT);
				setcolor(WHITE);
				outtextxy(pos[index].x+20,pos[index].y+BAR_HEIGHT/5*2,"SBSBSB");
				index--;
				putimage(pos[index].x,pos[index].y,tmp_h_bar,COPY_PUT);
				setcolor(YELLOW);
				outtextxy(pos[index].x+20,pos[index].y+BAR_HEIGHT/5*2,"SBSBSB");
				setfillstyle(SOLID_FILL,BLUE);
				bar(100,100,200,200);
			}//�����ϼ� 
			else if(key==DOWN&&index!=3){
				putimage(pos[index].x,pos[index].y,tmp_bar,COPY_PUT);
				setcolor(WHITE);
				outtextxy(pos[index].x+20,pos[index].y+BAR_HEIGHT/5*2,"SBSBSB");
				index++;
				putimage(pos[index].x,pos[index].y,tmp_h_bar,COPY_PUT);
				setcolor(YELLOW);
				outtextxy(pos[index].x+20,pos[index].y+BAR_HEIGHT/5*2,"SBSBSB");
				setfillstyle(SOLID_FILL,BLUE);
				bar(100,100,200,200);
			}//�����¼� 
			else if(key==0x011B){
				return;
			}//����ESC 
			else if(key==ENTER){
				setcolor(WHITE);
				outtextxy(100,100,"YOU");
			}//���»س� 
			else printf("%x\n",key);//���԰������� 
		}
} 
/*----------------------------------------------------------------------------------*/ 


int main(){
	int driver=DETECT,mode=VESA_800x600x8bit;
	initgraph(&driver,&mode,"PW");
	pwchar();
	pwbackground();
	pwhomepage();
	return 0;
}
