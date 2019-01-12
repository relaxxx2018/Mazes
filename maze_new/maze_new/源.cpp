#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define M 8   //行数  
#define N 8     //列数  
#define MaxSize    100     //栈最多元素个数  


struct maze {
	int i;      //路径横坐标  
	int j;      //路径纵坐标  
	int di;     //方向   
}Stack[MaxSize], Path[MaxSize];      //定义栈和存放最短路径的数组  
int top = -1;     //栈顶指针  
int count = 1;    //路径数计数  
int minlen = MaxSize;     //最短路径长度 


int x = 450,y = 25;//老鼠初始位置信息
int b[20][20];//新的地图的二位数组
int c[20][20];//最短路径数组

char d[20][20] = { 0 };//接受txt文件信息的字符串数组
int n[20][20] = { 0 };//接受字符数组转换之后的结果
IMAGE img[4];//创建图像文件
LOGFONT f;//创建字体格式对象
clock_t start, end;


void hint_Msg(TCHAR s[])
{
	outtextxy(120, 180, s);
	line(120, 235, 380, 235);
}
void time()
{
	int i, j;
	TCHAR s[10];
	for (i = 9; i > 0; i--)
	{
		_stprintf_s(s, _T("%d"), i);
		outtextxy(710, 330, s);
		for (j = 9; j > 0; j--)
		{
			_stprintf_s(s, _T("%d"), j);
			outtextxy(725, 330, s);
			Sleep(1000);
			putimage(725, 335, &img[1]);
		}
		Sleep(1000);
		putimage(710, 335, &img[1]);

	}
	fflush(stdout);
}
//提示功能
void hint()
{
	setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE | PS_JOIN_ROUND, 5);
	line(80, 70, 420, 70);
	line(80, 70, 80, 330);
	line(420, 70, 420, 330);
	line(80, 330, 420, 330);
	outtextxy(150, 75, _T("游戏说明："));
	outtextxy(90, 110, _T("1.当老鼠在移动时,"));
	outtextxy(140, 145, _T("按esc键退出~"));
	outtextxy(90, 180, _T("2.当绘制地图完成时"));
	outtextxy(140, 215, _T("按鼠标右键键退出~"));
	outtextxy(90, 250, _T("3.开始游戏后计时!"));
	outtextxy(140, 285, _T("时间60秒，自己掐表吧！"));
}
//清屏
void Sweep(int n) {
	int x1 = 0, y1 = 0;
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			putimage(x1, y1, &img[n]);
			putimage(x1, 500 - y1, &img[n]);
			x1 += 25;
		}
		x1 = 0;
		y1 += 25;
		Sleep(20);
	}
}
//地图打印功能
void print(int a[][20],int n)//输入需要打印的地图数组  填充图片编号
{
	int x = 0, y = 0;
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (a[i][j] == 0 )
			{
				putimage(x, y, &img[n]);
				x += 25;
				Sleep(10);
				
			}
			else if (a[i][j] == 1 )
			{
				putimage(x, y, &img[1]);
				x += 25;
				Sleep(10);
			}
		}
		Sleep(10);
		x = 0;
		y += 25;
	}
	
}
//最短路径路线打印
void print_Path(int c[][20])
{
	int x = 0, y = 0;
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (c[i][j] == 0)
			{
				putimage(x, y, &img[2]);
				x += 25;
				Sleep(50);
			}
			else
			{
				x += 25;
			}
		}
		Sleep(20);
		x = 0;
		y += 25;
	}
}
//控制老鼠移动
void move(int a[][20])
{
	char c;
	int xx, yy;//老鼠二位数组坐标信息
	
	do
	{
		c = _getch();
		xx = x / 25;
		yy = y / 25;
		if (c == 27)
		{
			break;
		}
		else if ((c == 'a' || c == 'A') && (a[yy][xx - 1] == 0))//左
		{
			putimage(x - 25, y + 0, &img[2]);
			putimage(x, y, &img[0]);
			x = x - 25;

		}
		else if ((c == 'w' || c == 'W') && (a[yy - 1][xx] == 0 || a[yy - 1][xx] == 48))//上
		{
			putimage(x, y - 25, &img[2]);
			putimage(x, y, &img[0]);
			y = y - 25;

		}									
		else if ((c == 's' || c == 'S') && (a[yy + 1][xx] == 0 ))//下
		{
			putimage(x, y + 25, &img[2]);
			putimage(x, y, &img[0]);
			y = y + 25;
	
		}
		else if ((c == 'd' || c == 'D') && (a[yy][xx + 1] == 0 || a[yy][xx + 1] == 0))//右
		{
			putimage(x + 25, y + 0, &img[2]);
			putimage(x, y, &img[0]);
			x = x + 25;
		}
		else if(x == 25 && y == 450)
		{
			Sweep(2);
			break;
		}
		
		
	} while (true);
}
//边框以及文字
void draw()
{
	
	outtextxy(585, 130, _T("3.绘制地图"));
	outtextxy(585, 180, _T("4.绘制完成"));
	outtextxy(585, 80, _T("2.输出地图"));
	outtextxy(585, 30, _T("1.开始游戏"));
	outtextxy(585, 230, _T("5.最短路径"));
	outtextxy(585, 280, _T("6.输入地图"));
	outtextxy(585, 330, _T("7.计时功能"));
	

	//分隔线
	line(505, 0, 505, 500);
	//绘制Start边框
	/*line(580, 28, 710, 28);
	line(580, 58, 710, 58);
	line(580, 28, 580, 58);
	line(710, 28, 710, 58);
	//绘制OutPut边框
	line(580, 78, 710, 78);
	line(580, 108, 710, 108);
	line(580, 78, 580, 108);
	line(710, 78, 710, 108);
	//绘制Draw a map 边框
	line(580, 128, 710, 128);
	line(580, 158, 710, 158);
	line(580, 128, 580, 158);
	line(710, 128, 710, 158);
	//绘制Completed 边框
	line(580, 178, 710, 178);
	line(580, 208, 710, 208);
	line(580, 178, 580, 208);
	line(710, 178, 710, 208);
	//绘制Shortest Path边框
	line(580, 228, 710, 228);
	line(580, 258, 710, 258);
	line(580, 228, 580, 258);
	line(710, 228, 710, 258);
	//绘制Input map边框
	line(580, 278, 710, 278);
	line(580, 308, 710, 308);
	line(580, 278, 580, 308);
	line(710, 278, 710, 308);*/
	
}
//绘制新的地图
void fill()
{
	MOUSEMSG m;
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			b[i][j] = 1;
		}
	}
	putimage(25, 450, &img[0]);
	putimage(450, 25, &img[2]);
	while (true)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (m.x <= 500 && m.y <= 500)
			{
				if (((m.x) / 25) * 25 != 475 && ((m.y) / 25) * 25 !=0 && ((m.y) / 25) * 25 != 475 && ((m.x) / 25) * 25 != 0)
				{
					putimage(((m.x) / 25) * 25, ((m.y) / 25) * 25, &img[0]);
				}
				b[(m.y) / 25][(m.x) / 25] = 0;
			}
			else if ((m.x >= 580 && m.x <= 760) && (m.y >= 178 && m.y <= 208))
			{
				Sweep(1);
				print(b, 0);
				putimage(450, 25, &img[2]);//
				putimage(25, 450, &img[0]);
				b[1][18] = 0;
				b[18][1] = 0;
				start = clock();
				move(b);
				end = clock();
				if ((((double)end - start) / CLK_TCK)>60)
				{
					f.lfHeight = 50;
					settextstyle(&f);
					Sweep(1);
					hint_Msg(_T("时间超时！！！"));
				}
				else
				{
					f.lfHeight = 50;
					settextstyle(&f);
					Sweep(1);
					hint_Msg(_T("游戏完成！！！"));
				}
				break;
			}
			
		}
		else if(m.uMsg == WM_RBUTTONDOWN)
		{
			break;
		}
	}
}
//寻找最短路径（栈）
void Shortest_Path(int a[][20]) { 
	int i, j, di, find, k;
	top++;
	Stack[top].i = 1; 
	Stack[top].j = 18; 
	Stack[top].di = -1;
	a[1][18] = -1;  //初始结点进栈
	while (top>-1) //栈不空时循环
	{      
		i = Stack[top].i; 
		j = Stack[top].j; 
		di = Stack[top].di;
		if (i == 18 && j == 1)  //找到了出口，输出路径
		{      
			if (top + 1 < minlen)  //比较输出最短路径
			{      
				for (k = 0; k <= top; k++)
					Path[k] = Stack[k];
				minlen = top + 1;
			}
			a[Stack[top].i][Stack[top].j] = 0;   //让该位置变为其他路径的可走结点
			top--;
			i = Stack[top].i; 
			j = Stack[top].j; 
			di = Stack[top].di;//栈顶出栈
		}
		find = 0;
		while (di<4 && find == 0) //找下一个可走结点
		{     
			di++;
			switch (di) 
			{
				case 0:i = Stack[top].i - 1; j = Stack[top].j; break;   //上面
				case 1:i = Stack[top].i; j = Stack[top].j + 1; break;   //右边
				case 2:i = Stack[top].i + 1; j = Stack[top].j; break;   //下面
				case 3:i = Stack[top].i; j = Stack[top].j - 1; break;   //左边
			}
			if (a[i][j] == 0)
				find = 1;
		}
		if (find == 1) //找到了下一个可走结点
		{      
			Stack[top].di = di;   //修改原栈顶元素的di值
			top++;      //下一个可走结点进栈
			Stack[top].i = i;
			Stack[top].j = j;
			Stack[top].di = -1;
			a[i][j] = -1;        //避免重复走到该结点
		}
		else 
		{
			a[Stack[top].i][Stack[top].j] = 0;   //让该位置变为其他路径的可走结点
			top--;
		}
	}
	
	for (int i = 0; i < 20; i++)
	{
		for (int  j = 0; j < 20; j++)
		{
			c[i][j] = 1;
		}
	}
	for (k = 0; k<minlen; k++) {
		c[Path[k].i][Path[k].j] = 0;
	}
} 

//输出当前数组
void OutPut(int a[][20])
{
	FILE* fp;
	fp = fopen("C:\\Users\\admin\\Desktop\\课程设计\\maze_map_output.txt", "w");
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			fprintf(fp, "%d", a[i][j]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
}
//txt文件中读取地图信息
void InPut()
{
	FILE* fp;
	fp = fopen("C:\\Users\\admin\\Desktop\\课程设计\\maze_map_input.txt", "r");
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			fscanf(fp, "%c", &d[i][j]);
		}
		fscanf(fp, "\n");
	}
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			n[i][j]  = ((int)d[i][j] - 48) ;
		}
	}

	fclose(fp);
}
void main()
{
	MOUSEMSG m;
	initgraph(809, 500);
	setbkcolor(RGB(77,77,77));
	cleardevice();

	setlinecolor(WHITE);
	setlinestyle(PS_DASH | PS_ENDCAP_SQUARE | PS_JOIN_ROUND, 5);

	gettextstyle(&f);
	f.lfHeight = 30;
	f.lfWidth = 0;
	_tcscpy_s(f.lfFaceName, _T("造字工房童心常规体"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);

	//地图数组
	int a[20][20] ={
		//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 
		{ 1,1,1,1,1,1,1,1,1,1,1, 1, 1, 1, 1, 1 ,1, 1, 1, 1 },//0
		{ 1,0,0,0,0,0,0,1,0,0,0, 0, 0, 0, 0, 0 ,0, 1, 0, 1 },//1
		{ 1,0,1,1,1,0,1,1,0,1,1, 1, 0, 1, 1, 1 ,1, 1, 0, 1 },//2
		{ 1,0,1,0,1,0,1,0,0,1,0, 1, 0, 0, 0, 0 ,0, 0, 0, 1 },//3
		{ 1,0,1,0,1,0,1,1,0,1,0, 1, 1, 1, 1, 1 ,0, 1, 1, 1 },//4
		{ 1,0,1,0,1,0,1,1,0,1,0, 0, 0, 0, 0, 1 ,0, 0, 0, 1 },//5
		{ 1,0,1,0,0,0,0,1,0,1,1, 1, 1, 1, 0, 1 ,1, 1, 0, 1 },//6
		{ 1,0,1,1,1,1,0,1,0,1,0, 0, 0, 1, 0, 1 ,0, 0, 0, 1 },//7
		{ 1,0,0,0,0,1,0,1,0,0,0, 1, 0, 1, 0, 1 ,1, 1, 1, 1 },//8
		{ 1,0,1,1,1,1,1,1,1,1,1, 1, 0, 1, 0, 0 ,0, 1, 0, 1 },//9
		{ 1,0,1,0,0,0,0,0,0,0,0, 0, 0, 1, 0, 1 ,1, 1, 0, 1 },//10
		{ 1,0,1,0,1,0,1,1,1,1,1, 1, 0, 1, 0, 1 ,0, 0, 0, 1 },//11
		{ 1,0,0,0,1,0,0,0,0,0,1, 1, 1, 1, 0, 1 ,0, 1, 1, 1 },//12
		{ 1,0,1,0,1,1,1,1,1,1,1, 0, 0, 0, 0, 0 ,0, 1, 0, 1 },//13
		{ 1,0,1,0,0,0,0,0,0,1,0, 0, 1, 1, 1, 0 ,1, 1, 0, 1 },//14
		{ 1,1,1,1,1,1,1,1,0,1,1, 0, 1, 0, 1, 0 ,1, 1, 0, 1 },//15
		{ 1,0,0,0,0,0,0,0,0,0,1, 0, 1, 0, 1, 0 ,1, 0, 0, 1 },//16
		{ 1,1,1,1,1,0,1,1,1,1,1, 0, 1, 0, 1, 1 ,1, 0, 1, 1 },//17
		{ 1,0,0,0,0,0,1,0,0,0,0, 0, 0, 0, 0, 0 ,0, 0, 0, 1 },//18
		{ 1,1,1,1,1,1,1,1,1,1,1, 1, 1, 1, 1, 1 ,1, 1, 1, 1 },//19
	};
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>这里图片的位置需要更改>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	loadimage(&img[1], _T("C:\\Users\\admin\\Desktop\\课程设计\\墙.jpg"));//7 7 7
	loadimage(&img[0], _T("C:\\Users\\admin\\Desktop\\课程设计\\路.jpg"));//254 255 255
	loadimage(&img[2], _T("C:\\Users\\admin\\Desktop\\课程设计\\老鼠.jpg"));
	loadimage(&img[3], _T("C:\\Users\\admin\\Desktop\\课程设计\\出口.jpg"));
	draw();
	hint();
	
	while (true)
	{
		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:
			//输出当前游戏数组
			if ((m.y <= 108 && m.y >= 78) && (m.x >= 595 && m.x <= 710))
			{
				OutPut(a);
				f.lfHeight = 50;
				settextstyle(&f);
				Sweep(1);
				TCHAR s[] = _T("输出成功！！！");
				outtextxy(120, 180, s);
				line(120, 235, 380, 235);
				break;
			}
			//开始游戏
			else if ((m.y <= 58 && m.y >= 28) && (m.x >= 595 && m.x <= 710))
			{
				print(a, 0);
				putimage(450, 25, &img[2]);//设定老鼠的位置
				putimage(25, 450, &img[2]);//设定出口的位置
				//time();
				start = clock();
				move(a);
				end = clock();
				if ((((double)end-start) / CLK_TCK)>10)
				{
					f.lfHeight = 50;
					settextstyle(&f);
					Sweep(1);
					TCHAR s[] = _T("时间超时！！！");
					outtextxy(120, 180, s);
					line(120, 235, 380, 235);
					Sleep(3000);
					break;
				}
			}
			//绘制地图+绘制完成
			else if ((m.y <= 158 && m.y >= 128) && (m.x >= 595 && m.x <= 710))
			{
				Sweep(1);//初始化地图，绘制地图
				fill();
				break;
			}
			//最短路径
			else if ((m.y <= 258 && m.y >= 228) && (m.x >= 580 && m.x <= 760))
			{
				Sweep(1);
				Shortest_Path(a);
				print(a, 0);
				print_Path(c);
				putimage(450, 25, &img[2]);
				putimage(25, 450, &img[2]);
			}
			else if ((m.y <= 308 && m.y >= 278) && (m.x >= 595 && m.x <= 710))
			{
				Sweep(2);
				InPut();
				print(n, 0);
			}
			break;
		}
	}
}
/*void main1()
{
	int a[20][20] = {
		//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 
		{ 1,1,1,1,1,1,1,1,1,1,1, 1, 1, 1, 1, 1 ,1, 1, 1, 1 },//0
		{ 1,0,0,0,0,0,0,1,0,0,0, 0, 0, 0, 0, 0 ,0, 1, 0, 1 },//1
		{ 1,0,1,1,1,0,1,1,0,1,1, 1, 0, 1, 1, 1 ,1, 1, 0, 1 },//2
		{ 1,0,1,0,1,0,1,0,0,1,0, 1, 0, 0, 0, 0 ,0, 0, 0, 1 },//3
		{ 1,0,1,0,1,0,1,1,0,1,0, 1, 1, 1, 1, 1 ,0, 1, 1, 1 },//4
		{ 1,0,1,0,1,0,1,1,0,1,0, 0, 0, 0, 0, 1 ,0, 0, 0, 1 },//5
		{ 1,0,1,0,0,0,0,1,0,1,1, 1, 1, 1, 0, 1 ,1, 1, 0, 1 },//6
		{ 1,0,1,1,1,1,0,1,0,1,0, 0, 0, 1, 0, 1 ,0, 0, 0, 1 },//7
		{ 1,0,0,0,0,1,0,1,0,0,0, 1, 0, 1, 0, 1 ,1, 1, 1, 1 },//8
		{ 1,0,1,1,1,1,1,1,1,1,1, 1, 0, 1, 0, 0 ,0, 1, 0, 1 },//9
		{ 1,0,1,0,0,0,0,0,0,0,0, 0, 0, 1, 0, 1 ,1, 1, 0, 1 },//10
		{ 1,0,1,0,1,0,1,1,1,1,1, 1, 0, 1, 0, 1 ,0, 0, 0, 1 },//11
		{ 1,0,0,0,1,0,0,0,0,0,1, 1, 1, 1, 0, 1 ,0, 1, 1, 1 },//12
		{ 1,0,1,0,1,1,1,1,1,1,1, 0, 0, 0, 0, 0 ,0, 1, 0, 1 },//13
		{ 1,0,1,0,0,0,0,0,0,1,0, 0, 1, 1, 1, 0 ,1, 1, 0, 1 },//14
		{ 1,1,1,1,1,1,1,1,0,1,1, 0, 1, 0, 1, 0 ,1, 1, 0, 1 },//15
		{ 1,0,0,0,0,0,0,0,0,0,1, 0, 1, 0, 1, 0 ,1, 0, 0, 1 },//16
		{ 1,1,1,1,1,0,1,1,1,1,1, 0, 1, 0, 1, 1 ,1, 0, 1, 1 },//17
		{ 1,0,0,0,0,0,1,0,0,0,0, 0, 0, 0, 0, 0 ,0, 0, 0, 1 },//18
		{ 1,1,1,1,1,1,1,1,1,1,1, 1, 1, 1, 1, 1 ,1, 1, 1, 1 },//19
	};
	
	Shortest_Path(a);
	for (int k = 0; k<minlen; k++) {
		//c[Path[k].i][Path[k].j] = 0;
		printf("%d %d,", Path[k].i, Path[k].j);
	}
	printf("\n");
	printf("%d\n", minlen);
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			printf("%d", c[i][j]);
		}
		printf("\n");
	}
	getchar();

}*/


