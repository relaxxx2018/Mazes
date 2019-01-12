#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define M 8   //����  
#define N 8     //����  
#define MaxSize    100     //ջ���Ԫ�ظ���  


struct maze {
	int i;      //·��������  
	int j;      //·��������  
	int di;     //����   
}Stack[MaxSize], Path[MaxSize];      //����ջ�ʹ�����·��������  
int top = -1;     //ջ��ָ��  
int count = 1;    //·��������  
int minlen = MaxSize;     //���·������ 


int x = 450,y = 25;//�����ʼλ����Ϣ
int b[20][20];//�µĵ�ͼ�Ķ�λ����
int c[20][20];//���·������

char d[20][20] = { 0 };//����txt�ļ���Ϣ���ַ�������
int n[20][20] = { 0 };//�����ַ�����ת��֮��Ľ��
IMAGE img[4];//����ͼ���ļ�
LOGFONT f;//���������ʽ����
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
//��ʾ����
void hint()
{
	setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE | PS_JOIN_ROUND, 5);
	line(80, 70, 420, 70);
	line(80, 70, 80, 330);
	line(420, 70, 420, 330);
	line(80, 330, 420, 330);
	outtextxy(150, 75, _T("��Ϸ˵����"));
	outtextxy(90, 110, _T("1.���������ƶ�ʱ,"));
	outtextxy(140, 145, _T("��esc���˳�~"));
	outtextxy(90, 180, _T("2.�����Ƶ�ͼ���ʱ"));
	outtextxy(140, 215, _T("������Ҽ����˳�~"));
	outtextxy(90, 250, _T("3.��ʼ��Ϸ���ʱ!"));
	outtextxy(140, 285, _T("ʱ��60�룬�Լ�����ɣ�"));
}
//����
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
//��ͼ��ӡ����
void print(int a[][20],int n)//������Ҫ��ӡ�ĵ�ͼ����  ���ͼƬ���
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
//���·��·�ߴ�ӡ
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
//���������ƶ�
void move(int a[][20])
{
	char c;
	int xx, yy;//�����λ����������Ϣ
	
	do
	{
		c = _getch();
		xx = x / 25;
		yy = y / 25;
		if (c == 27)
		{
			break;
		}
		else if ((c == 'a' || c == 'A') && (a[yy][xx - 1] == 0))//��
		{
			putimage(x - 25, y + 0, &img[2]);
			putimage(x, y, &img[0]);
			x = x - 25;

		}
		else if ((c == 'w' || c == 'W') && (a[yy - 1][xx] == 0 || a[yy - 1][xx] == 48))//��
		{
			putimage(x, y - 25, &img[2]);
			putimage(x, y, &img[0]);
			y = y - 25;

		}									
		else if ((c == 's' || c == 'S') && (a[yy + 1][xx] == 0 ))//��
		{
			putimage(x, y + 25, &img[2]);
			putimage(x, y, &img[0]);
			y = y + 25;
	
		}
		else if ((c == 'd' || c == 'D') && (a[yy][xx + 1] == 0 || a[yy][xx + 1] == 0))//��
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
//�߿��Լ�����
void draw()
{
	
	outtextxy(585, 130, _T("3.���Ƶ�ͼ"));
	outtextxy(585, 180, _T("4.�������"));
	outtextxy(585, 80, _T("2.�����ͼ"));
	outtextxy(585, 30, _T("1.��ʼ��Ϸ"));
	outtextxy(585, 230, _T("5.���·��"));
	outtextxy(585, 280, _T("6.�����ͼ"));
	outtextxy(585, 330, _T("7.��ʱ����"));
	

	//�ָ���
	line(505, 0, 505, 500);
	//����Start�߿�
	/*line(580, 28, 710, 28);
	line(580, 58, 710, 58);
	line(580, 28, 580, 58);
	line(710, 28, 710, 58);
	//����OutPut�߿�
	line(580, 78, 710, 78);
	line(580, 108, 710, 108);
	line(580, 78, 580, 108);
	line(710, 78, 710, 108);
	//����Draw a map �߿�
	line(580, 128, 710, 128);
	line(580, 158, 710, 158);
	line(580, 128, 580, 158);
	line(710, 128, 710, 158);
	//����Completed �߿�
	line(580, 178, 710, 178);
	line(580, 208, 710, 208);
	line(580, 178, 580, 208);
	line(710, 178, 710, 208);
	//����Shortest Path�߿�
	line(580, 228, 710, 228);
	line(580, 258, 710, 258);
	line(580, 228, 580, 258);
	line(710, 228, 710, 258);
	//����Input map�߿�
	line(580, 278, 710, 278);
	line(580, 308, 710, 308);
	line(580, 278, 580, 308);
	line(710, 278, 710, 308);*/
	
}
//�����µĵ�ͼ
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
					hint_Msg(_T("ʱ�䳬ʱ������"));
				}
				else
				{
					f.lfHeight = 50;
					settextstyle(&f);
					Sweep(1);
					hint_Msg(_T("��Ϸ��ɣ�����"));
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
//Ѱ�����·����ջ��
void Shortest_Path(int a[][20]) { 
	int i, j, di, find, k;
	top++;
	Stack[top].i = 1; 
	Stack[top].j = 18; 
	Stack[top].di = -1;
	a[1][18] = -1;  //��ʼ����ջ
	while (top>-1) //ջ����ʱѭ��
	{      
		i = Stack[top].i; 
		j = Stack[top].j; 
		di = Stack[top].di;
		if (i == 18 && j == 1)  //�ҵ��˳��ڣ����·��
		{      
			if (top + 1 < minlen)  //�Ƚ�������·��
			{      
				for (k = 0; k <= top; k++)
					Path[k] = Stack[k];
				minlen = top + 1;
			}
			a[Stack[top].i][Stack[top].j] = 0;   //�ø�λ�ñ�Ϊ����·���Ŀ��߽��
			top--;
			i = Stack[top].i; 
			j = Stack[top].j; 
			di = Stack[top].di;//ջ����ջ
		}
		find = 0;
		while (di<4 && find == 0) //����һ�����߽��
		{     
			di++;
			switch (di) 
			{
				case 0:i = Stack[top].i - 1; j = Stack[top].j; break;   //����
				case 1:i = Stack[top].i; j = Stack[top].j + 1; break;   //�ұ�
				case 2:i = Stack[top].i + 1; j = Stack[top].j; break;   //����
				case 3:i = Stack[top].i; j = Stack[top].j - 1; break;   //���
			}
			if (a[i][j] == 0)
				find = 1;
		}
		if (find == 1) //�ҵ�����һ�����߽��
		{      
			Stack[top].di = di;   //�޸�ԭջ��Ԫ�ص�diֵ
			top++;      //��һ�����߽���ջ
			Stack[top].i = i;
			Stack[top].j = j;
			Stack[top].di = -1;
			a[i][j] = -1;        //�����ظ��ߵ��ý��
		}
		else 
		{
			a[Stack[top].i][Stack[top].j] = 0;   //�ø�λ�ñ�Ϊ����·���Ŀ��߽��
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

//�����ǰ����
void OutPut(int a[][20])
{
	FILE* fp;
	fp = fopen("C:\\Users\\admin\\Desktop\\�γ����\\maze_map_output.txt", "w");
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
//txt�ļ��ж�ȡ��ͼ��Ϣ
void InPut()
{
	FILE* fp;
	fp = fopen("C:\\Users\\admin\\Desktop\\�γ����\\maze_map_input.txt", "r");
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
	_tcscpy_s(f.lfFaceName, _T("���ֹ���ͯ�ĳ�����"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);

	//��ͼ����
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
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>����ͼƬ��λ����Ҫ����>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	loadimage(&img[1], _T("C:\\Users\\admin\\Desktop\\�γ����\\ǽ.jpg"));//7 7 7
	loadimage(&img[0], _T("C:\\Users\\admin\\Desktop\\�γ����\\·.jpg"));//254 255 255
	loadimage(&img[2], _T("C:\\Users\\admin\\Desktop\\�γ����\\����.jpg"));
	loadimage(&img[3], _T("C:\\Users\\admin\\Desktop\\�γ����\\����.jpg"));
	draw();
	hint();
	
	while (true)
	{
		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:
			//�����ǰ��Ϸ����
			if ((m.y <= 108 && m.y >= 78) && (m.x >= 595 && m.x <= 710))
			{
				OutPut(a);
				f.lfHeight = 50;
				settextstyle(&f);
				Sweep(1);
				TCHAR s[] = _T("����ɹ�������");
				outtextxy(120, 180, s);
				line(120, 235, 380, 235);
				break;
			}
			//��ʼ��Ϸ
			else if ((m.y <= 58 && m.y >= 28) && (m.x >= 595 && m.x <= 710))
			{
				print(a, 0);
				putimage(450, 25, &img[2]);//�趨�����λ��
				putimage(25, 450, &img[2]);//�趨���ڵ�λ��
				//time();
				start = clock();
				move(a);
				end = clock();
				if ((((double)end-start) / CLK_TCK)>10)
				{
					f.lfHeight = 50;
					settextstyle(&f);
					Sweep(1);
					TCHAR s[] = _T("ʱ�䳬ʱ������");
					outtextxy(120, 180, s);
					line(120, 235, 380, 235);
					Sleep(3000);
					break;
				}
			}
			//���Ƶ�ͼ+�������
			else if ((m.y <= 158 && m.y >= 128) && (m.x >= 595 && m.x <= 710))
			{
				Sweep(1);//��ʼ����ͼ�����Ƶ�ͼ
				fill();
				break;
			}
			//���·��
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


