/*********************************************************
****************By  2013/7/18
****************Author: carm
**********************************************************/

#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<time.h>
#include<stdlib.h>
#define WIDTH  20
#define MINE 9
int row;
int col;												 //  row,col Ϊ�к���
int x0;
int y0;                                                  // x0,y0,Ϊ�������
int m_maxx;
int m_maxy;                                              //  m_maxx,m_maxy Ϊ�������
struct node
{
	int flag;
	int data;
}** mine;
int m_num;                                                //����
int mcount;
int count;
//char s[5];
void draw_a_box(int x1,int y1,int x2,int y2,int type);   /* draw a box */
void  draw_mine_map();                                   //draw mine region
void initSystem();                                       // init system
void closeSystem();                                      //close system
void count_x0y0();                                       //gain x0,y0 point
void draw_head_bar();                               
void malloc_Array2();                                    //���붯̬�ڴ棨��ά���飩
void playGame();
void enterLeftMouse();                                   //����������
void enterRightMouse();                                  //����Ҽ�����
void set_mines();                                        //set mines
void drawMine();                                         //draw mine
void print_num(int i,int j);                             
void print_mine_num(int m,int n);                        //ͳ����Χ������ 
void setEmpty(int x,int y);                              //���������ÿ�
void draw_a_flag(int x,int y);                           //������
void draw_a_interrogation(int i,int j);                  //���ʺ�
void show_minemap();                                     //��ʾ�������ֵ������������ã�
void you_win();                                          //ʤ��
void you_lose();                                         //ʧ��
void print_X(int i,int j);                               //��־��������
void draw_a_smile_face();                                //Ц��
void replay_game();                                      //���¿�ʼ


void show_rest_mine()
{
	char s[5]={0};
	//char c=(char)count+48;
	draw_a_box(x0+10,y0-60,x0+60,y0-34,0);
	sprintf(s,"%d",mcount);
	setbkmode(TRANSPARENT);
	outtextxy(x0+10+20,y0-60+5,s);
	
}
void show_minemap() //��ʾ�������ֵ�����
{
  int i,j;
  
  for(i=0;i<row;++i)
	  for(j=0;j<col;++j)
	  {
	   print_num(i,j);
	  }
}
void draw_a_smile_face()   //��Ц��
{
	setcolor(YELLOW);
	fillcircle( ( x0+x0+col*(WIDTH+1) )/2, y0-47 ,13);
	setfillstyle(SOLID_FILL);
    setfillcolor(LIGHTMAGENTA);
	floodfill( (x0+x0+col*(WIDTH+1) )/2, y0-47 ,YELLOW);
	line( (x0+x0+col*(WIDTH+1) )/2-8,y0-50,(x0+x0+col*(WIDTH+1) )/2-4,y0-50);
	line( (x0+x0+col*(WIDTH+1) )/2+5,y0-50,(x0+x0+col*(WIDTH+1) )/2+9,y0-50);
	line( (x0+x0+col*(WIDTH+1) )/2-2,y0-43,(x0+x0+col*(WIDTH+1) )/2+2,y0-43);
}
void draw_head_bar()
{
	int mwidth,mhight;

  mwidth=col*(WIDTH+1)-1;
  mhight=row*(WIDTH+1)-1;

  
	draw_a_box(x0-4,y0-62,x0+mwidth+2,y0+mhight+2,1);		//����
	draw_a_box(x0-2,y0-62,x0+mwidth+2,y0-32,1);				//������ʱ����
    draw_a_box(x0-2,y0-32,x0+mwidth+2,y0-2,1);				//�ȼ�ѡ����

	draw_a_box(x0+10,y0-30,x0+60,y0-4,1);					//�м�
		setbkmode(TRANSPARENT);
	    outtextxy(x0+10 +10,y0-30 +5,"�м�");                                                                        

    draw_a_box(x0+mwidth-60,y0-30,x0+mwidth-10,y0-4,1);		//�߼�
		setbkmode(TRANSPARENT);
	    outtextxy(x0+mwidth-60 +10,y0-30 +5,"�߼�"); 
	
	draw_a_box(x0+10,y0-60,x0+60,y0-34,0);					//��ʾʣ������
    draw_a_box(x0+mwidth-60,y0-60,x0+mwidth-10,y0-34,0);    //��ʾʱ��
  
	draw_a_smile_face();                                    //��Ц��
}

void count_x0y0()                                           //ȷ��ԭ��
{
	x0=(m_maxx-(WIDTH+1)*col+1)/2;	
	y0=(m_maxy-(WIDTH+1)*row+1)/2;	
}
void  draw_mine_map()                                       //����
{   int i,j,x,y;
    count_x0y0();
	draw_head_bar();
	y=y0;
	for(i=0;i<row;++i)
	{   
		x=x0;
		for(j=0;j<col;++j)
		{
				draw_a_box(x,y,x+WIDTH,y+WIDTH,1);
				x+=WIDTH+1;
		}
		y+=WIDTH+1;
	}


}
void draw_a_box(int x1,int y1,int x2,int y2,int type)        //draw a box 
{
  setcolor(WHITE);
  rectangle(x1,y1,x2,y2);
  setfillstyle(SOLID_FILL);
  setfillcolor(LIGHTGRAY);
  floodfill((x1+x2)/2,(y1+y2)/2,WHITE);

  if (type==1) setcolor(WHITE);
  else         setcolor(DARKGRAY);

  line(x1,y1,x2,y1);
  line(x1,y1,x1,y2);
  line(x1+1,y1+1,x2-1,y1+1);
  line(x1+1,y1+1,x1+1,y2-1);

  if (type==1) setcolor(DARKGRAY);
  else         setcolor(WHITE);

  line(x1,y2,x2,y2);
  line(x2,y1,x2,y2);
  line(x1-1,y2-1,x2-1,y2-1);
  line(x2-1,y1+1,x2-1,y2-1);
}

void drawMine(int i,int j)         //����
{
    int x=i*(WIDTH+1)+x0;
	int y=j*(WIDTH+1)+y0;
  draw_a_box(x,y,x+WIDTH,y+WIDTH,0);
  setcolor(BLACK);
  circle(x+WIDTH/2,y+WIDTH/2,WIDTH/3);
  setfillstyle(SOLID_FILL);
  setfillcolor(BLACK);
  floodfill(x+WIDTH/2,y+WIDTH/2,BLACK);	
}
void print_mine_num(int m,int n)    //ͳ����Χ����
{
	if(m-1>=0&&n-1>=0&&m+1<col&&n+1<row)
	{   
		if(mine[m-1][n-1].data!=MINE)
		    mine[m-1][n-1].data++;
		if(mine[m+1][n+1].data!=MINE)
			mine[m+1][n+1].data++;
		if(mine[m][n-1].data!=MINE)
			mine[m][n-1].data++;
		if(mine[m][n+1].data!=MINE)
			mine[m][n+1].data++;
		if(mine[m-1][n].data!=MINE)
			mine[m-1][n].data++;
		if(mine[m+1][n].data!=MINE)
			mine[m+1][n].data++;
		if(mine[m-1][n+1].data!=MINE)
			mine[m-1][n+1].data++;
		if(mine[m+1][n-1].data!=MINE)
			mine[m+1][n-1].data++;
	}

	if(m-1<0&&n-1<0)
	{
		if(mine[m][n+1].data!=MINE)
			mine[m][n+1].data++;
		if(mine[m+1][n+1].data!=MINE)
			mine[m+1][n+1].data++;
		if(mine[m+1][n].data!=MINE)
			mine[m+1][n].data++;
	}

	if( m-1<0&&n+1==col)
	{
		if(mine[m][n-1].data!=MINE)
			mine[m][n-1].data++;
		if(mine[m+1][n-1].data!=MINE)
			mine[m+1][n-1].data++;
		if(mine[m+1][n].data!=MINE)
			mine[m+1][n].data++;
	}

	if(n-1<0&&m+1==row)
	{
		if(mine[m][n+1].data!=MINE)
			mine[m][n+1].data++;
		if(mine[m-1][n+1].data!=MINE)
			mine[m-1][n+1].data++;
		if(mine[m-1][n].data!=MINE)
			mine[m-1][n].data++;
	}

	if(m+1==col&&n+1==row)
	{
		if(mine[m-1][n-1].data!=MINE)
			mine[m-1][n-1].data++;
		if(mine[m-1][n].data!=MINE)
			mine[m-1][n].data++;
		if(mine[m][n-1].data!=MINE)
			mine[m][n-1].data++;
	}
	
	if(m-1<0&&n-1>=0&&n+1<col)
	{
		if(mine[m][n-1].data!=MINE)
			mine[m][n-1].data++;
		if(mine[m][n+1].data!=MINE)
			mine[m][n+1].data++;
		if(mine[m+1][n].data!=MINE)
			mine[m+1][n].data++;
		if(mine[m+1][n-1].data!=MINE)
			mine[m+1][n-1].data++;
		if(mine[m+1][n+1].data!=MINE)
			mine[m+1][n+1].data++;
	}
	
	if(n-1<0&&m-1>=0&&m+1<row)
	{
		if(mine[m-1][n].data!=MINE)
			mine[m-1][n].data++;
		if(mine[m+1][n].data!=MINE)
			mine[m+1][n].data++;
		if(mine[m][n+1].data!=MINE)
			mine[m][n+1].data++;
		if(mine[m-1][n+1].data!=MINE)
			mine[m-1][n+1].data++;
		if(mine[m+1][n+1].data!=MINE)
			mine[m+1][n+1].data++;
	}
	
	if(n+1>=col&&m-1>=0&&m+1<row)
	{
		if(mine[m-1][n].data!=MINE)
			mine[m-1][n].data++;
		if(mine[m+1][n].data!=MINE)
			mine[m+1][n].data++;
		if(mine[m-1][n-1].data!=MINE)
			mine[m-1][n-1].data++;
		if(mine[m+1][n-1].data!=MINE)
			mine[m+1][n-1].data++;
		if(mine[m][n-1].data!=MINE)
			mine[m][n-1].data++;
	}

	if(m+1>=row&&n-1>=0&&n+1<col)
	{
		if(mine[m][n-1].data!=MINE)
			mine[m][n-1].data++;
		if(mine[m][n+1].data!=MINE)
			mine[m][n+1].data++;
		if(mine[m-1][n-1].data!=MINE)
			mine[m-1][n-1].data++;
		if(mine[m-1][n+1].data!=MINE)
			mine[m-1][n+1].data++;
		if(mine[m-1][n].data!=MINE)
			mine[m-1][n].data++;
	}

	
	
}
void set_mines()                    //����
{
	int m=0,n=0;
	int count=0;
	srand((unsigned)time(0));      //�������Ϊ�����±�
	int nnum=row*col;
	while(count<m_num)
	{
		m=rand()%row;
        n=rand()%row;
		if(mine[m][n].data!=MINE)
			
		{
			mine[m][n].data=MINE;
			print_mine_num(m,n);
			count++;
		}
	}
}
void draw_a_flag (int i,int j)            //������
{
	int x=x0+i*(WIDTH+1);
	int y=y0+j*(WIDTH+1);
		mcount--;
		show_rest_mine();
	setlinecolor(RED);
	setlinestyle(PS_SOLID,5);
	line(x+5,y+3,x+18,y+3);
	line(x+5,y+3,x+5,y+18);
	line(x+18,y+3,x+5,y+12);
	setfillcolor(RED);
	floodfill(x+6,y+4,RED);
	
}
void draw_a_interrogation(int i,int j)  //��ʾ�ʺ�
{  
	draw_a_box(i,j,i+WIDTH,j+WIDTH,1);
	setbkmode(TRANSPARENT);
	outtextxy(i+5,j+5,'?');
	mcount++;
	show_rest_mine();
}
void enterRightMouse(MOUSEMSG msg)      //����Ҽ�����
{
	int i,j,x,y;
	i=(msg.x-x0)/(WIDTH+1);
	j=(msg.y-y0)/(WIDTH+1);
	if(msg.x>x0&&msg.x<x0+(WIDTH+1)*col&&msg.y>y0&&msg.y<y0+row*(WIDTH+1)&&mine[i][j].flag!=10)
	{  
		  x=x0+i*(WIDTH+1);
	      y=y0+j*(WIDTH+1);
	
		  mine[i][j].flag++;
	
	}  
	if(mine[i][j].flag!=10)
	{
	    if(mine[i][j].flag%3==1)
	    {
			draw_a_flag(i,j);
			count--;
		}
		
		if(mine[i][j].flag%3==2)
		{
				count++;
			draw_a_interrogation(x,y);
		}
		if(mine[i][j].flag%3==0)
		{
			draw_a_box(x,y,x+WIDTH,y+WIDTH,1);
			mine[i][j].flag=0;
		}
	}

	if(mine[i][j].data==9&&mine[i][j].flag==1&&count==0)
		you_win();
    
}
void you_lose()                                      // ���you lose!
{
	setfont(40,20,"����");
	settextcolor(RED);
	outtextxy(m_maxx/2-20-65, m_maxy/2-20,"you lose!");
	for(int i=0;i<row;++i)
		for(int j=0;j<col;++j)
			if(mine[i][j].data==0)
				mine[i][j].flag=10;
	
} 

void you_win()                                       //���you win!
{
	setfont(40,20,"����");
	settextcolor(GREEN);
    outtextxy(m_maxx/2-20-65, m_maxy/2-20,"you win!");
}

void gameOver()                                       //��Ϸ��������
{
	for(int i=0;i<row;++i)
		for(int j=0;j<col;++j)
		{
			if(mine[i][j].data!=-1&& mine[i][j].flag==0&&mine[i][j].data!=0)
			{
					int a=i*(WIDTH+1)+x0;
	                int b=j*(WIDTH+1)+y0;
					draw_a_box(a,b,a+WIDTH,b+WIDTH,0);
					print_num(i,j);
				 mine[i][j].flag=10;
			}
			if(mine[i][j].data==MINE)
				drawMine(i,j);
		}
 you_lose();
}
void print_num(int i,int j)                           //��������ʾ����Ϸ��Ļ
{   
	int x=i*(WIDTH+1)+x0+5;
	int y=j*(WIDTH+1)+y0+5;
	//sprintf_s(c,"%d",mine[i][j].data);
	char s=(char)mine[i][j].data+48;
	setbkmode(TRANSPARENT);
	if(mine[i][j].data!=0&&mine[i][j].data!=9)
	outtextxy(x,y,s);
	
}
void setEmpty(int x,int y)                             //��Χ������
{
	int a=x*(WIDTH+1)+x0;
	int b=y*(WIDTH+1)+y0;
	if(mine[x][y].data==0&&mine[x][y].flag==0)
	{    
		draw_a_box(a,b,a+WIDTH,b+WIDTH,0);
		 mine[x][y].data=-1;	
		 mine[x][y].flag=10;
		for(int i=x-1;i<=x+1;++i)
			for(int j=y-1;j<=y+1;++j)
			{
				if(i<0||i>=row||j<0||j>=col)
				continue;
				if(mine[i][j].data>0&&mine[i][j].flag==0)
				{
					print_num(i,j);
					mine[i][j].flag=10;
				}
				if(mine[i][j].data==0)
					setEmpty(i,j);
			}
		
	}
}
void print_X(int i,int j)                               //��־ �����ĵ���
{
	int a=i*(WIDTH+1)+x0;
	int b=j*(WIDTH+1)+y0;
	setcolor(RED);
	setlinestyle(PS_SOLID, NULL, 3);
	line(a+5,b+5,a+WIDTH-5,b+WIDTH-5);
	line(a+WIDTH-5,b+5,a+5,b+WIDTH-5);
}
void enterLeftMouse(MOUSEMSG msg)                       //����������
{

	if(msg.x>x0 && msg.x<(x0+ col*(WIDTH+1)-1 ) && msg.y>y0 && msg.y<(y0+row*(WIDTH+1)-1 ) )    //��Ϸ���������	
	{    
		int i=(msg.x-x0)/(WIDTH+1);
		int j=(msg.y-y0)/(WIDTH+1);
		if(mine[i][j].flag==0)
		{
		   print_num(i,j);
			if(mine[i][j].data==MINE)
			{
				gameOver();
				print_X(i,j);                          //���ñ�־ ����Ǵ�������
			}
			if(mine[i][j].data==0)
				setEmpty(i,j);
		}
	}
	if(msg.x>(x0+x0+col*(WIDTH+1) )/2-13 && msg.x<(x0+x0+col*(WIDTH+1) )/2+13 && msg.y>y0-47-13 && msg.y<y0-47+13)   //���¿�ʼ
	{
		if(mine!=NULL)
			free(mine);
		 row=9;
		 col=9;
	     m_num=10;
		 replay_game();
	}
	if(msg.x>x0+10 && msg.x<x0+60 && msg.y>y0-30 && msg.y<y0-4)                                                      //�м���Ϸ
	{
		if(mine!=NULL)
			free(mine);
		row=16;
		col=16;
		m_num=40;
		replay_game();
	
	}
	if(msg.x>x0+(col*(WIDTH+1)-1)-60 && msg.x<x0+(col*(WIDTH+1)-1)-10 && msg.y>y0-30 && msg.y<y0-4)                  //�߼���Ϸ
	{
		if(mine!=NULL)
			free(mine);
		row=20;
		col=20;
		m_num=88;
		replay_game();
	}
}
void playGame()                                                                                                      //��Ϸ��ʼ
{
	MOUSEMSG msg;
	
	while(TRUE)
	{
		msg=GetMouseMsg();
		switch(msg.uMsg)
		{
		    case WM_LBUTTONDOWN: enterLeftMouse(msg);  break;
			case WM_RBUTTONDOWN: enterRightMouse(msg); break;
		}
	}

}
/*
void show_mine_num()
{
	sprintf(s,"%d",count);
	setbkmode(TRANSPARENT);
	outtextxy(x0+10+20,y0-60+5,s);
}
*/
void replay_game()    //����
{
	
	initSystem();
	draw_mine_map();
	//show_mine_num();
	show_rest_mine();
	set_mines();
   // show_minemap();  //��⺯��
	playGame();
}
void main()          //������
{
	row=9;
	col=9;
	m_num=10;
	replay_game();
	_getch();
	closeSystem();
}
void malloc_Array2() //��̬�����ڴ�
{    int r=row;
	int size=sizeof(struct node);
	int pointsize=sizeof(struct node *);
	mine=(struct node **)malloc(pointsize*row+size*row*col);
	if(mine!=NULL)
	{
		memset(mine,0,pointsize*row+size*row*col);
		struct node *head=(struct node*)( (int)mine+pointsize*row );
		while(r--)
		{
			mine[r]=(struct node *)( (int)head+size*r*col );
		}
	}
}
void initSystem()  //��ʼ��
{
	int gdrive=DETECT,gmode;
	initgraph(&gdrive,&gmode,"");
	mcount=m_num;
	m_maxx=getmaxx();
	m_maxy=getmaxy();
	malloc_Array2();
	for(int i=0;i<row;++i)
		for(int j=0;j<col;++j)
		{
			mine[i][j].data=0;
			mine[i][j].flag=0;
		}
	
}

void closeSystem() 
{
	closegraph();
	if(mine!=NULL)
		free(mine);
}