#include<graphics.h>

/*----------------------------------背景相关---------------------------------------*/
void draw_background_paint(char *p,int text[]){			//画底部的字 
	int i,j;
	char *tmp;
	for(i=0;i<8;i++){
		for(j=4;j>0;j--){
			if(text[i]&(1<<j)){
				tmp=p+i*2*800+(4-j)*2;
				*tmp=*(tmp+1)=*(tmp+800)=*(tmp+801)=0xFF;
			}
		}
	}
}

void draw_background(){
	int i;
	char *p;
	int text[20][8];					//F,H,e,l,p,E,x,i,t,S,a,v,A,n,d,1,9,0
	text[0][0]=text[0][3]=0x1F;
	text[0][1]=text[0][2]=text[0][4]=text[0][5]=text[0][6]=text[0][7]=0x10;
	
	text[15][0]=0x06;
	text[15][1]=0x0E;
	text[15][2]=text[15][3]=text[15][4]=text[15][5]=text[15][6]=0x02;
	text[15][7]=0x0F;
	//未完待续
	 
	for(i=0;i<464000;i++){
		*(_vp+i)=BLUE;
	}
	for(i=464000;i<480000;i++){
		*(_vp+i)=0x1A;
	}
	draw_background_paint(_vp+465602,text[0]);
}
/*----------------------------------------------------------------------------------*/ 


/*----------------------------------主页相关----------------------------------------*/
void draw_homepage(){
	
} 
/*----------------------------------------------------------------------------------*/ 


int main(){
	int driver=DETECT,mode=VESA_800x600x8bit;
	initgraph(&driver,&mode,"PW");
	draw_background();
	//return 0;
}
