//分析饮食
struct profile {
		char name[11];
   		char gender[2];
   		char age[3];
   		char height[4];
   		char weight[4];
   		int recoder; // 记录次数 算平均
   		double energy;
   		double procnt;
	};
//记录
void pw_homebar2(){
		struct Pos{
		int x;
		int y;
	};//表示位置
	int key;//按下的键
	void *tmp_bar,*tmp_h_bar;//存储临时方块，getimage用
	int index=0;//高亮方块编号
	struct Pos pos[5]={{300,200},{300,280},{300,350},{300,420},{300,490}};//各方块位置
	char *text[5]={"Not eat","Some vegs","Many vegs","Some meat","Lots of meat"};//各方块上打印的信息 
	
	/*分配getimage空间*/
	tmp_bar=malloc(imagesize(pos[0].x,pos[0].y,pos[0].x+251-1,pos[0].y+BAR_HEIGHT-1));
	tmp_h_bar=malloc(imagesize(pos[0].x,pos[0].y,pos[0].x+251-1,pos[0].y+BAR_HEIGHT-1));
	
	/*得到高亮方块*/
	setfillstyle(SOLID_FILL,RED);
	bar(pos[0].x,pos[0].y,pos[0].x+251-1,pos[0].y+BAR_HEIGHT-1);
	getimage(pos[0].x,pos[0].y,pos[0].x+251-1,pos[0].y+BAR_HEIGHT-1,tmp_h_bar);
	
	/*得到低亮方块*/ 
	setfillstyle(SOLID_FILL,DARKGRAY);
	bar(pos[0].x,pos[0].y,pos[0].x+251-1,pos[0].y+BAR_HEIGHT-1);
	getimage(pos[0].x,pos[0].y,pos[0].x+251-1,pos[0].y+BAR_HEIGHT-1,tmp_bar);
	
	/*画方块及字*/ 
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
	
	/*循环键盘输入*/ 
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
			}//按下上键 
			else if((key==DOWN||key==RIGHT)&&index!=4){
				putimage(pos[index].x,pos[index].y,tmp_bar,COPY_PUT);
				setcolor(WHITE);
				outtextxy(pos[index].x+8,pos[index].y+BAR_HEIGHT*11/30,text[index]);
				index++;
				putimage(pos[index].x,pos[index].y,tmp_h_bar,COPY_PUT);
				setcolor(YELLOW);
				outtextxy(pos[index].x+8,pos[index].y+BAR_HEIGHT*11/30,text[index]);
			}//按下下键 
			else if(key==0x011B){
				return;
			}//按下ESC 
			else if(key==ENTER){
				if(index==0) pw_homebar0();
				if(index==4) pw_homebar4();
				if(index==3) pw_homebar3();
			}//按下回车
			else printf("%x\n",key);//测试按键的码 
		}
}
}



