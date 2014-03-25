#include<graphics.h>

#define UP 0x4800
#define DOWN 0x5000
#define LEFT 0x4B00
#define RIGHT 0x4D00
#define ESC 0x011B

int num[10][10],upalpha[26][10],lowalpha[26][10];		//数字，字母的点阵存储数组 

/**************************************************/
/*在屏幕上打印一个字符                            */
/*参数： p 打印字左上角点的地址，text[] 要打印的字*/ 
/*返回值：无                                      */
/**************************************************/ 
void pwprint(char *p,int text[]){			//画底部的字 
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
/*设置字符的点阵                                  */
/*参数：无                                        */ 
/*返回值：无                                      */
/**************************************************/ 
void pwchar(){
	num[0][0]=0x7E;
	num[0][1]=0x46;
	num[0][2]=num[0][3]=num[0][4]=0x4A;
	num[0][5]=num[0][6]=num[0][7]=0x52;
	num[0][8]=0x62;
	num[0][9]=0x7E;

} 

/*----------------------------------背景相关---------------------------------------*/
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


/*----------------------------------主页相关----------------------------------------*/

void pwhomepage(){
	int key;
	void *tmp_bar,*tmp_h_bar;
	char *up=_vp+50*800+200;
	char *down=_vp+200*800+200;
	char *mid=up;
	
	tmp_bar=malloc(40501);
	tmp_h_bar=malloc(40501);
	setfillstyle(SOLID_FILL,RED);
	bar(200,50,600,150);
	getimage(200,50,600,150,tmp_h_bar);
	setfillstyle(SOLID_FILL,0x1A);
	bar(200,50,600,150);
	bar(200,200,600,300);
	getimage(200,50,600,150,tmp_bar);
	
	putimage(200,50,tmp_h_bar,COPY_PUT);
	while(1)
		if(bioskey(1)!=0){
			key=bioskey(0);
			if(key==0x4800&&mid==down){
				mid=up;
				putimage(200,50,tmp_h_bar,COPY_PUT);
				putimage(200,200,tmp_bar,COPY_PUT);
			}
			else if(key==0x5000&&mid==up){
				mid=down;
				putimage(200,50,tmp_bar,COPY_PUT);
				putimage(200,200,tmp_h_bar,COPY_PUT);
			}
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
