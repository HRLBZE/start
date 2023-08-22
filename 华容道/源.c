#define _CRT_SECURE_NO_WARNINGS
# include <math.h>
# include <graphics.h>
# include <time.h>
# include <string>

static HWND hOut;						// 画布

// 定义一个结构体，树
struct Node1
{
	int num;							// 编号
	int num_transverse;					// 横向特征值
	int num_portrait;					// 纵向特征值
	int num_other;						// 其他特征值
	int num_father;						// 父结点
};
Node1 box[200001];						// 预制结点

// 定义一个结构体，临时存放
struct Node2
{
	int num_transverse;					// 横向特征值
	int num_portrait;					// 纵向特征值
	int num_other;						// 其他特征值
};

// 定义一个结构体，按钮
struct Node3
{
	int posx1, posy1, posx2, posy2;		// 坐标
};

// 定义一个类
class Gary
{
public:
	void carry();						// 主进程
	void initialization();				// 初始化
	void move();						// 窗口主视角函数
	void draw_scene(int num_box);		// 绘制界面函数
	void create();						// 生成函数
	void decode();						// 解码函数
	void code();						// 编码函数
	void check(int a, int b, int c);	// 检测重复函数
	void single_space(int mode);		// 单格移动函数
	void double_space();				// 双哥移动函数
	void over();						// 结束判断函数
	void game();						// 游戏函数
	void solve();						// 求解函数

	int exit_carry;						// 主循函数控制参数
	int exit_move;						// 开始界面控制参数
	int num_double[31];					// 辅助数据存入
	int num_step;						// 树层数
	int num_eat;						// 求解链长度参数
	int num_start;						// 求解起点参数
	int num_over;						// 求解终点参数
	int num_mod;						// 游戏模式
	int box_transverse[6];				// 横向
	int box_portrait[6];				// 纵向
	int box_big;						// 大格
	int box_space[2];					// 空格
	int num_transverse;					// 横向数量
	int num_portrait;					// 纵向数量
	int pan[30];						// 棋盘信息
	double num_flag;					// 树结点标记系数
	double num_flag1;					// 树结点标记系数
	IMAGE* img_transverse;				// 横块图片
	IMAGE* img_portrait;				// 纵块图片
	IMAGE* img_small;					// 小块图片
	IMAGE* img_big;						// 大块图片
	IMAGE* img_space;					// 空格图片
	ExMessage m;						// 鼠标定义
	Node2 eat[200];						// 临时存放结点
	Node3 box_button[20];				// 按钮，预制
};

// 场景绘制函数
void Gary::draw_scene(int num_box)
{
	int i, j;
	// 横向
	for (i = 0; i < num_transverse; i++)
	{
		box_transverse[i] = (eat[num_box].num_transverse & (num_double[i * 5 + 5] - num_double[i * 5])) / num_double[i * 5];
	}
	// 纵向
	for (i = 0; i < num_portrait; i++)
	{
		box_portrait[i] = (eat[num_box].num_portrait & (num_double[i * 5 + 5] - num_double[i * 5])) / num_double[i * 5];
	}
	// 大格
	box_big = (eat[num_box].num_other & (num_double[21] - num_double[16])) / num_double[16];
	// 空格
	box_space[0] = (eat[num_box].num_other & (num_double[13] - num_double[8])) / num_double[8];
	box_space[1] = (eat[num_box].num_other & (num_double[5] - num_double[0]));
	// 初始化
	for (i = 0; i < 20; i++)
	{
		pan[i] = -1;
	}
	// 横向
	for (i = 0; i < num_transverse; i++)
	{
		pan[box_transverse[i]] = 2;
		pan[box_transverse[i] + 1] = 5;
	}
	// 纵向
	for (i = 0; i < num_portrait; i++)
	{
		pan[box_portrait[i]] = 3;
		pan[box_portrait[i] + 4] = 5;

	}
	// 大格
	pan[box_big] = 1;
	pan[box_big + 1] = 5;
	pan[box_big + 4] = 5;
	pan[box_big + 5] = 5;
	// 空格
	pan[box_space[0]] = 0;
	pan[box_space[1]] = 0;
	// 小块
	for (j = 0; j < 20; j++)
	{
		if (pan[j] == -1)
		{
			pan[j] = 4;
		}
	}
	// 背景绘制
	setbkcolor(RGB(136, 192, 160));
	cleardevice();
	// 棋盘绘制
	setlinestyle(PS_SOLID, 3);
	setfillcolor(RGB(73, 130, 120));
	setlinecolor(RGB(168, 226, 195));
	fillroundrect(20, 15, 25 + 102 * 4, 30 + 102 * 5, 30, 30);
	for (i = 0; i < 20; i++)
	{
		// 根据格子类型绘制
		switch (pan[i])
		{
		case 0:putimage(25 + i % 4 * 102, 25 + i / 4 * 102, img_space); break;
		case 1:putimage(25 + i % 4 * 102, 25 + i / 4 * 102, img_big); break;
		case 2:putimage(25 + i % 4 * 102, 25 + i / 4 * 102, img_transverse); break;
		case 3:putimage(25 + i % 4 * 102, 25 + i / 4 * 102, img_portrait); break;
		case 4:putimage(25 + i % 4 * 102, 25 + i / 4 * 102, img_small); break;
		default:break;
		}
		// 出口绘制
		if (pan[i] == 0 && (i == 13 || i == 14 || i == 17 || i == 18))
		{
			setlinecolor(RGB(230, 230, 230));
			setlinestyle(PS_SOLID, 10);
			setfillcolor(RGB(112, 180, 167));
			fillcircle(25 + 51 + i % 4 * 102, 25 + 51 + i / 4 * 102, 20);
			setlinecolor(RGB(168, 226, 195));
			setfillcolor(RGB(73, 130, 120));
			setlinestyle(PS_SOLID, 3);
		}
	}

	// 按钮绘制
	TCHAR s[25];
	setlinecolor(RGB(155, 195, 230));
	setfillcolor(RGB(80, 189, 222));
	settextcolor(RGB(230, 230, 230));
	settextstyle(30, 20, _T("Times New Roman"));
	setbkcolor(RGB(80, 189, 222));
	// 标准棋盘按钮
	for (i = 0; i < 12; i++)
	{
		fillroundrect(box_button[i].posx1, box_button[i].posy1, box_button[i].posx2, box_button[i].posy2, 20, 20);
		_stprintf_s(s, _T("%d"), i);
		outtextxy(box_button[i].posx1 + 13 - 11 * (i / 10), box_button[i].posy1 + 10, s);
	}
	// 其他按钮
	settextstyle(100, 100, _T("Webdings"));
	settextcolor(RGB(73, 130, 120));
	setbkmode(TRANSPARENT);
	// 播放，求解
	outtextxy(102 - 50, 580 - 30, 0x34);
	// 重置，恢复初始盘面
	outtextxy(214 - 50, 580 - 30, 0x33);
	// 刷新，随机盘面按钮
	outtextxy(326 - 50, 580 - 30, 0x71);
	// 恢复填充
	setbkmode(OPAQUE);
	settextcolor(RGB(230, 230, 230));
	settextstyle(30, 20, _T("宋体"));
	setbkcolor(RGB(136, 192, 160));
	outtextxy(102 - 50, 655, _T("求解"));
	outtextxy(214 - 50, 655, _T("恢复"));
	outtextxy(326 - 50, 655, _T("刷新"));

	FlushBatchDraw();
}

// 解码
void Gary::decode()
{
	int i;
	// 根据特征值画棋面
	// 横向
	for (i = 0; i < num_transverse; i++)
	{
		box_transverse[i] = (box[int(num_flag)].num_transverse & (num_double[i * 5 + 5] - num_double[i * 5])) / num_double[i * 5];
	}
	// 纵向
	for (i = 0; i < num_portrait; i++)
	{
		box_portrait[i] = (box[int(num_flag)].num_portrait & (num_double[i * 5 + 5] - num_double[i * 5])) / num_double[i * 5];
	}
	// 大格
	box_big = (box[int(num_flag)].num_other & (num_double[21] - num_double[16])) / num_double[16];
	// 空格
	box_space[0] = (box[int(num_flag)].num_other & (num_double[13] - num_double[8])) / num_double[8];
	box_space[1] = (box[int(num_flag)].num_other & (num_double[5] - num_double[0]));
}

// 检查重复函数
void Gary::check(int a, int b, int c)
{
	int k, t;
	// 全局检测
	k = 0;
	for (t = int(num_flag1 - 1); t >= 0; t--)
	{
		if (box[t].num_transverse == a && box[t].num_portrait == b && box[t].num_other == c) { k = 1; break; }
	}
	// 不重复则生成子结点
	if (k == 0)
	{
		// 特征值录入，父结点录入
		box[int(num_flag1)].num_transverse = a;
		box[int(num_flag1)].num_portrait = b;
		box[int(num_flag1)].num_other = c;
		box[int(num_flag1)].num_father = int(num_flag);
		// 编号
		box[int(num_flag1)].num = box[box[int(num_flag1)].num_father].num + 1;
		// 层数
		if (box[int(num_flag1)].num > num_step)
		{
			// 加层
			num_step = box[int(num_flag1)].num;
			// 进度条绘制
			setlinecolor(RGB(155, 195, 230));
			setfillcolor(RGB(155, 195, 230));
			fillroundrect(50, 640, int(70.0 + 330.0 * double(num_eat + num_step) / 120.0), 650, 20, 20);
			FlushBatchDraw();
		}
		// 标记加一
		num_flag1++;
	}
}


// 单空格移动函数
void Gary::single_space(int mode)
{
	int i, j, k;
	int a, b, c;
	int t;
	// 空格读取
	i = box_big;
	j = (mode == 0 ? box_space[0] : box_space[1]);
	k = (mode == 0 ? box_space[1] : box_space[0]);
	// 空格
	// 上（不是大块，不是另一个空格，不在最上测，不是横块）
	if (j - 4 != i + 4 && j - 4 != i + 5 && j - 4 != k && j > 3)
	{
		for (t = 0; t < num_transverse; t++)
		{
			if (j - 4 == box_transverse[t] || j - 4 == box_transverse[t] + 1)break;
		}
		// 不是横块
		if (t == num_transverse)
		{
			for (t = 0; t < num_portrait; t++)
			{
				if (j - 4 == box_portrait[t] + 4)break;
			}
			a = box[int(num_flag)].num_transverse;
			// 不是纵块
			if (t == num_portrait)
			{
				b = box[int(num_flag)].num_portrait;
				c = (mode == 0 ? (i * num_double[16] + (j - 4) * num_double[8] + k * num_double[0]) : (i * num_double[16] + k * num_double[8] + (j - 4) * num_double[0]));
			}
			// 是
			else
			{
				b = box[int(num_flag)].num_portrait + 4 * num_double[t * 5];
				c = (mode == 0 ? (i * num_double[16] + (j - 8) * num_double[8] + k * num_double[0]) : (i * num_double[16] + k * num_double[8] + (j - 8) * num_double[0]));
			}
			check(a, b, c);
		}
	}
	// 下（不是大块，不是另一个空格，不在最下测，不是横块）
	if (j + 4 != i && j + 4 != i + 1 && j + 4 != k && j < 16)
	{
		for (t = 0; t < num_transverse; t++)
		{
			if (j + 4 == box_transverse[t] || j + 4 == box_transverse[t] + 1)break;
		}
		if (t == num_transverse)
		{
			for (t = 0; t < num_portrait; t++)
			{
				if (j + 4 == box_portrait[t])break;
			}
			a = box[int(num_flag)].num_transverse;
			// 不是纵块
			if (t == num_portrait)
			{
				b = box[int(num_flag)].num_portrait;
				c = (mode == 0 ? (i * num_double[16] + (j + 4) * num_double[8] + k * num_double[0]) : (i * num_double[16] + k * num_double[8] + (j + 4) * num_double[0]));
			}
			// 是
			else
			{
				b = box[int(num_flag)].num_portrait - 4 * num_double[t * 5];
				c = (mode == 0 ? (i * num_double[16] + (j + 8) * num_double[8] + k * num_double[0]) : (i * num_double[16] + k * num_double[8] + (j + 8) * num_double[0]));
			}
			check(a, b, c);
		}
	}
	// 左（不是大块，不是另一个空格，不在最左测，不是纵块）
	if (j - 1 != i + 5 && j - 1 != i + 1 && j - 1 != k && j % 4 != 0)
	{
		for (t = 0; t < num_portrait; t++)
		{
			if (j - 1 == box_portrait[t] || j - 1 == box_portrait[t] + 4)break;
		}
		if (t == num_portrait)
		{
			for (t = 0; t < num_transverse; t++)
			{
				if (j - 1 == box_transverse[t] + 1)break;
			}
			b = box[int(num_flag)].num_portrait;
			// 不是横块
			if (t == num_transverse)
			{
				a = box[int(num_flag)].num_transverse;
				c = (mode == 0 ? (i * num_double[16] + (j - 1) * num_double[8] + k * num_double[0]) : (i * num_double[16] + k * num_double[8] + (j - 1) * num_double[0]));
			}
			// 是横块
			else
			{
				a = box[int(num_flag)].num_transverse + 1 * num_double[t * 5];
				c = (mode == 0 ? (i * num_double[16] + (j - 2) * num_double[8] + k * num_double[0]) : (i * num_double[16] + k * num_double[8] + (j - 2) * num_double[0]));
			}
			check(a, b, c);
		}
	}
	// 右（不是大块，不是另一个空格，不在最右测，不是纵块）
	if (j + 1 != i && j + 1 != i + 4 && j + 1 != k && j % 4 != 3)
	{
		for (t = 0; t < num_portrait; t++)
		{
			if (j + 1 == box_portrait[t] || j + 1 == box_portrait[t] + 4)break;
		}
		if (t == num_portrait)
		{
			for (t = 0; t < num_transverse; t++)
			{
				if (j + 1 == box_transverse[t])break;
			}
			b = box[int(num_flag)].num_portrait;
			// 不是横块
			if (t == num_transverse)
			{
				a = box[int(num_flag)].num_transverse;
				c = (mode == 0 ? (i * num_double[16] + (j + 1) * num_double[8] + k * num_double[0]) : (i * num_double[16] + k * num_double[8] + (j + 1) * num_double[0]));
			}
			// 是横块
			else
			{
				a = box[int(num_flag)].num_transverse - 1 * num_double[t * 5];
				c = (mode == 0 ? (i * num_double[16] + (j + 2) * num_double[8] + k * num_double[0]) : (i * num_double[16] + k * num_double[8] + (j + 2) * num_double[0]));
			}
			check(a, b, c);
		}
	}
}

// 双空格移动函数
void Gary::double_space()
{
	int i, j, k, t, a, b, c;
	// 读取
	i = box_big;
	j = box_space[0];
	k = box_space[1];
	// 大格移动
	// 上
	if (i > 3 && ((i - 4 == k && i - 3 == j) || (i - 4 == j && i - 3 == k)))
	{
		a = box[int(num_flag)].num_transverse;
		b = box[int(num_flag)].num_portrait;
		c = (i - 4) * num_double[16] + (j + 8) * num_double[8] + (k + 8) * num_double[0];
		check(a, b, c);
	}
	// 下
	if (i < 12 && ((i + 8 == k && i + 9 == j) || (i + 8 == j && i + 9 == k)))
	{
		a = box[int(num_flag)].num_transverse;
		b = box[int(num_flag)].num_portrait;
		c = (i + 4) * num_double[16] + (j - 8) * num_double[8] + (k - 8) * num_double[0];
		check(a, b, c);
	}
	// 左
	if (i % 4 > 0 && ((i - 1 == k && i + 3 == j) || (i - 1 == j && i + 3 == k)))
	{
		a = box[int(num_flag)].num_transverse;
		b = box[int(num_flag)].num_portrait;
		c = (i - 1) * num_double[16] + (j + 2) * num_double[8] + (k + 2) * num_double[0];
		check(a, b, c);
	}
	// 右
	if (i % 4 < 2 && ((i + 2 == k && i + 6 == j) || (i + 2 == j && i + 6 == k)))
	{
		a = box[int(num_flag)].num_transverse;
		b = box[int(num_flag)].num_portrait;
		c = (i + 1) * num_double[16] + (j - 2) * num_double[8] + (k - 2) * num_double[0];
		check(a, b, c);
	}

	// 横块
	for (t = 0; t < num_transverse; t++)
	{
		i = box_transverse[t];
		// 上
		if (i > 3 && ((i - 4 == k && i - 3 == j) || (i - 4 == j && i - 3 == k)))
		{
			a = box[int(num_flag)].num_transverse - 4 * num_double[t * 5];
			b = box[int(num_flag)].num_portrait;
			c = box_big * num_double[16] + (j + 4) * num_double[8] + (k + 4) * num_double[0];
			check(a, b, c);
		}
		// 下
		if (i < 16 && ((i + 4 == k && i + 5 == j) || (i + 4 == j && i + 5 == k)))
		{
			a = box[int(num_flag)].num_transverse + 4 * num_double[t * 5];
			b = box[int(num_flag)].num_portrait;
			c = box_big * num_double[16] + (j - 4) * num_double[8] + (k - 4) * num_double[0];
			check(a, b, c);
		}
	}

	// 纵块
	for (t = 0; t < num_portrait; t++)
	{
		i = box_portrait[t];
		// 左
		if (i % 4 > 0 && ((i - 1 == k && i + 3 == j) || (i - 1 == j && i + 3 == k)))
		{
			a = box[int(num_flag)].num_transverse;
			b = box[int(num_flag)].num_portrait - 1 * num_double[t * 5];
			c = box_big * num_double[16] + (j + 1) * num_double[8] + (k + 1) * num_double[0];
			check(a, b, c);
		}
		// 右
		if (i % 4 < 3 && ((i + 1 == k && i + 5 == j) || (i + 1 == j && i + 5 == k)))
		{
			a = box[int(num_flag)].num_transverse;
			b = box[int(num_flag)].num_portrait + 1 * num_double[t * 5];
			c = box_big * num_double[16] + (j - 1) * num_double[8] + (k - 1) * num_double[0];
			check(a, b, c);
		}
	}
}

// 结束判断函数
void Gary::over()
{
	// 大格移动至求解终点参数
	if ((box[int(num_flag)].num_other & 0xff0000) / num_double[16] == num_over || num_flag1 < num_flag)
	{
		num_start = 1;
	}
}

// 编码函数
void Gary::code()
{
	int i, j, k;
	// 解码
	decode();
	// 横块排序
	for (i = 0; i < num_transverse - 1; i++)
	{
		for (j = num_transverse - 1; j > i; j--)
		{
			if (box_transverse[j] > box_transverse[j - 1])
			{
				k = box_transverse[j];
				box_transverse[j] = box_transverse[j - 1];
				box_transverse[j - 1] = k;
			}
		}
	}
	// 纵块排序
	for (i = 0; i < num_portrait - 1; i++)
	{
		for (j = num_portrait - 1; j > i; j--)
		{
			if (box_portrait[j] > box_portrait[j - 1])
			{
				k = box_portrait[j];
				box_portrait[j] = box_portrait[j - 1];
				box_portrait[j - 1] = k;
			}
		}
	}
	// 空格排序
	if (box_space[0] > box_space[1])
	{
		k = box_space[0];
		box_space[0] = box_space[1];
		box_space[1] = k;
	}
	// 编码
	box[int(num_flag)].num_transverse = 0;
	box[int(num_flag)].num_portrait = 0;

	for (i = 0; i < 6; i++)
	{
		box[int(num_flag)].num_transverse += box_transverse[i] * num_double[i * 5];
		box[int(num_flag)].num_portrait += box_portrait[i] * num_double[i * 5];
	}
	box[int(num_flag)].num_other = box_big * num_double[16] + box_space[0] * num_double[8] + box_space[1] * num_double[0];

}

// 生成函数
void Gary::create()
{
	// 棋盘初状态储存
	// 横向
	box[0].num_transverse = 0;
	// 纵向
	box[0].num_portrait = 0;
	// 标准棋盘
	// 棋盘参数
	switch (num_mod)
	{
	case 0:
	{
			  // 大格
			  box_big = 1;
			  // 横格
			  box_transverse[0] = 9;
			  num_transverse = 1;
			  // 纵格
			  box_portrait[0] = 0;
			  box_portrait[1] = 3;
			  box_portrait[2] = 8;
			  box_portrait[3] = 11;
			  num_portrait = 4;
			  // 空格
			  box_space[0] = 17;
			  box_space[1] = 18;
			  break;
	}
	case 1:
	{
			  // 大格
			  box_big = 1;
			  // 横格
			  box_transverse[0] = 9;
			  num_transverse = 1;
			  // 纵格
			  box_portrait[0] = 0;
			  box_portrait[1] = 3;
			  box_portrait[2] = 12;
			  box_portrait[3] = 15;
			  num_portrait = 4;
			  // 空格
			  box_space[0] = 17;
			  box_space[1] = 18;
			  break;
	}
	case 2:
	{
			  // 大格
			  box_big = 1;
			  // 横格
			  box_transverse[0] = 9;
			  num_transverse = 1;
			  // 纵格
			  box_portrait[0] = 0;
			  box_portrait[1] = 8;
			  box_portrait[2] = 13;
			  box_portrait[3] = 14;
			  num_portrait = 4;
			  // 空格
			  box_space[0] = 16;
			  box_space[1] = 19;
			  break;
	}
	case 3:
	{
			  // 大格
			  box_big = 1;
			  // 横格
			  box_transverse[0] = 13;
			  num_transverse = 1;
			  // 纵格
			  box_portrait[0] = 0;
			  box_portrait[1] = 3;
			  box_portrait[2] = 12;
			  box_portrait[3] = 15;
			  num_portrait = 4;
			  // 空格
			  box_space[0] = 17;
			  box_space[1] = 18;
			  break;
	}
	case 4:
	{
			  // 大格
			  box_big = 1;
			  // 横格
			  box_transverse[0] = 17;
			  num_transverse = 1;
			  // 纵格
			  box_portrait[0] = 0;
			  box_portrait[1] = 3;
			  box_portrait[2] = 9;
			  box_portrait[3] = 10;
			  num_portrait = 4;
			  // 空格
			  box_space[0] = 8;
			  box_space[1] = 11;
			  break;
	}
	case 5:
	{
			  // 大格
			  box_big = 1;
			  // 横格
			  box_transverse[0] = 9;
			  num_transverse = 1;
			  // 纵格
			  box_portrait[0] = 8;
			  box_portrait[1] = 11;
			  box_portrait[2] = 13;
			  box_portrait[3] = 14;
			  num_portrait = 4;
			  // 空格
			  box_space[0] = 16;
			  box_space[1] = 19;
			  break;
	}
	case 6:
	{
			  // 大格
			  box_big = 1;
			  // 横格
			  box_transverse[0] = 10;
			  num_transverse = 1;
			  // 纵格
			  box_portrait[0] = 0;
			  box_portrait[1] = 3;
			  box_portrait[2] = 12;
			  box_portrait[3] = 13;
			  num_portrait = 4;
			  // 空格
			  box_space[0] = 18;
			  box_space[1] = 19;
			  break;
	}
	case 7:
	{
			  // 大格
			  box_big = 1;
			  // 横格
			  box_transverse[0] = 9;
			  num_transverse = 1;
			  // 纵格
			  box_portrait[0] = 4;
			  box_portrait[1] = 7;
			  box_portrait[2] = 12;
			  box_portrait[3] = 15;
			  num_portrait = 4;
			  // 空格
			  box_space[0] = 17;
			  box_space[1] = 18;
			  break;
	}
	case 8:
	{
			  // 大格
			  box_big = 0;
			  // 横格
			  box_transverse[0] = 8;
			  num_transverse = 1;
			  // 纵格
			  box_portrait[0] = 2;
			  box_portrait[1] = 3;
			  box_portrait[2] = 12;
			  box_portrait[3] = 13;
			  num_portrait = 4;
			  // 空格
			  box_space[0] = 18;
			  box_space[1] = 19;
			  break;
	}
	case 9:
	{
			  // 大格
			  box_big = 5;
			  // 横格
			  box_transverse[0] = 13;
			  num_transverse = 1;
			  // 纵格
			  box_portrait[0] = 0;
			  box_portrait[1] = 3;
			  box_portrait[2] = 8;
			  box_portrait[3] = 11;
			  num_portrait = 4;
			  // 空格
			  box_space[0] = 18;
			  box_space[1] = 19;
			  break;
	}
	case 10:
	{
			   // 大格
			   box_big = 5;
			   // 横格
			   box_transverse[0] = 1;
			   num_transverse = 1;
			   // 纵格
			   box_portrait[0] = 12;
			   box_portrait[1] = 13;
			   box_portrait[2] = 14;
			   box_portrait[3] = 15;
			   num_portrait = 4;
			   // 空格
			   box_space[0] = 0;
			   box_space[1] = 3;
			   break;
	}
	case 11:
	{
			   // 大格
			   box_big = 5;
			   // 横格
			   box_transverse[0] = 13;
			   num_transverse = 1;
			   // 纵格
			   box_portrait[0] = 0;
			   box_portrait[1] = 3;
			   box_portrait[2] = 11;
			   box_portrait[3] = 12;
			   num_portrait = 4;
			   // 空格
			   box_space[0] = 17;
			   box_space[1] = 18;
			   break;
	}
	default:break;
	}

	int i, j, k, t;
	// 随机棋盘
	if (num_mod == 12)
	{
		// 初始化
		for (i = 0; i < 20; i++)
		{
			pan[i] = 0;
		}

		// 大格生成
		box_big = rand() % 3;
		pan[box_big] = 1;
		pan[box_big + 1] = 5;
		pan[box_big + 4] = 6;
		pan[box_big + 5] = 7;

		// 横块生成
		i = rand() % 2 + 2;
		k = 19;
		for (j = 0; j < i; j++)
		{
			while (k > 18 || k % 4 > 2 || pan[k] != 0 || pan[k + 1] != 0)
			{
				k = rand() % 19;
			}
			box_transverse[j] = k;
			pan[k] = 2;
			pan[k + 1] = 8;
		}
		num_transverse = i;

		// 纵块生成
		t = rand() % 2 + 1;
		k = 19;
		for (j = 0; j < t; j++)
		{
			while (k > 15 || k / 4 > 3 || pan[k] != 0 || pan[k + 4] != 0)
			{
				k = rand() % 16;
			}
			box_portrait[j] = k;
			pan[k] = 3;
			pan[k + 4] = 9;
		}
		num_portrait = t;

		// 空格生成
		box_space[0] = 17;
		while (pan[box_space[0]] != 0)
		{
			box_space[0] = rand() % 20;
		}
		pan[box_space[0]] = 4;
		// 空格
		box_space[1] = 18;
		while (pan[box_space[1]] != 0)
		{
			box_space[1] = rand() % 20;
		}
		pan[box_space[1]] = 4;
		// 小块生成
		for (k = 0; k < 20; k++)
		{
			if (pan[k] == 4) { pan[k] = 0; }
			else if (pan[k] == 0) { pan[k] = 4; }
		}
	}
	// 编码
	for (i = 0; i < 6; i++)
	{
		box[0].num_transverse += box_transverse[i] * num_double[i * 5];
		box[0].num_portrait += box_portrait[i] * num_double[i * 5];
	}
	box[0].num_other = box_big * num_double[16] + box_space[0] * num_double[8] + box_space[1] * num_double[0];
	box[0].num_father = -1;
	// 求解链初始化
	eat[0].num_transverse = box[0].num_transverse;
	eat[0].num_portrait = box[0].num_portrait;
	eat[0].num_other = box[0].num_other;

}

// 求解函数
void Gary::solve()
{
	int i, j, k;

	// 进度条绘制
	setlinecolor(RGB(155, 195, 230));
	setfillcolor(RGB(73, 130, 120));
	fillroundrect(50, 640, 400, 650, 20, 20);
	FlushBatchDraw();

	// 初始化
	box[0].num_transverse = eat[num_eat].num_transverse;
	box[0].num_portrait = eat[num_eat].num_portrait;
	box[0].num_other = eat[num_eat].num_other;

	// 参数初始化
	num_step = 0;
	num_flag = 0;
	num_flag1 = 1;
	// 编码
	code();
	num_start = 0;
	while (num_start == 0)
	{
		// 解码
		decode();
		// 两情况大类
		// 双空格移动
		double_space();
		// 单空格移动
		single_space(0);
		single_space(1);
		// 标记数加一
		num_flag++;
		// 编码
		code();
		// 结束判断函数
		over();
		// 随机盘面无解判断
		if (num_flag >= num_flag1 || (num_mod == 12 && (num_flag1 > 100000 || num_step > 100)))
		{
			num_start = 2;
			exit_move = 1;
		}
	}

	// 统计步数
	k = 0;
	for (i = int(num_flag); box[i].num_father >= 0; i = box[i].num_father)
	{
		k++;
	}
	j = k;
	// 解题过程录入
	for (i = int(num_flag); k > 0; i = box[i].num_father)
	{
		eat[num_eat + k].num_transverse = box[i].num_transverse;
		eat[num_eat + k].num_portrait = box[i].num_portrait;
		eat[num_eat + k].num_other = box[i].num_other;
		k--;
	}
	// 求解链长度参数更新
	num_eat += j;
}

// 初始化函数
void Gary::initialization()
{
	int i, j;
	// 随机种子初始化
	srand((unsigned)time(NULL));
	// 自动解题参数初始化
	num_start = 0;
	// 系数初始化
	j = 1;
	for (i = 0; i < 31; i++)
	{
		num_double[i] = j;
		j *= 2;
	}
	// 游戏模式初始化
	num_mod = 0;
	// 绘制相关初始化
	// 空格绘制
	img_space = new IMAGE(100, 100);
	// 初始化处理区域
	SetWorkingImage(img_space);
	setbkcolor(RGB(73, 130, 120));
	cleardevice();
	// 绘制
	setfillcolor(RGB(112, 180, 167));
	solidroundrect(0 + 5, 0 + 5, 100 - 5, 100 - 5, 30, 30);
	SetWorkingImage();

	// 横块绘制
	img_transverse = new IMAGE(200, 100);
	// 初始化处理区域
	SetWorkingImage(img_transverse);
	setbkcolor(RGB(73, 130, 120));
	cleardevice();
	// 绘制
	setfillcolor(RGB(174, 213, 111));
	solidroundrect(0, 0, 200, 100, 30, 30);
	setfillcolor(RGB(221, 245, 164));
	solidroundrect(5, 0, 195, 80, 20, 20);
	setfillcolor(RGB(152, 201, 95));
	solidroundrect(5, 80, 195, 100, 20, 20);
	setfillcolor(RGB(188, 242, 122));
	solidroundrect(5, 6, 189, 79, 15, 15);
	setfillcolor(RGB(153, 203, 96));
	solidcircle(22, 16, 4);
	solidcircle(178, 16, 4);
	solidcircle(22, 65, 4);
	solidcircle(178, 65, 4);
	SetWorkingImage();

	// 纵块绘制
	img_portrait = new IMAGE(100, 200);
	// 初始化处理区域
	SetWorkingImage(img_portrait);
	setbkcolor(RGB(73, 130, 120));
	cleardevice();
	// 绘制
	setfillcolor(RGB(75, 113, 179));
	solidroundrect(0, 0, 100, 200, 30, 30);
	setfillcolor(RGB(153, 188, 247));
	solidroundrect(5, 0, 95, 180, 20, 20);
	setfillcolor(RGB(64, 96, 151));
	solidroundrect(5, 180, 95, 200, 20, 20);
	setfillcolor(RGB(99, 147, 231));
	solidroundrect(5, 6, 89, 179, 15, 15);
	setfillcolor(RGB(73, 111, 180));
	solidcircle(22, 16, 4);
	solidcircle(78, 16, 4);
	solidcircle(22, 165, 4);
	solidcircle(78, 165, 4);
	SetWorkingImage();

	// 小块绘制
	img_small = new IMAGE(100, 100);
	// 初始化处理区域
	SetWorkingImage(img_small);
	setbkcolor(RGB(73, 130, 120));
	cleardevice();
	// 绘制
	setfillcolor(RGB(208, 174, 47));
	solidroundrect(0, 0, 100, 100, 30, 30);
	setfillcolor(RGB(254, 234, 158));
	solidroundrect(5, 0, 95, 80, 20, 20);
	setfillcolor(RGB(186, 145, 38));
	solidroundrect(5, 80, 95, 100, 20, 20);
	setfillcolor(RGB(254, 217, 81));
	solidroundrect(5, 6, 89, 79, 15, 15);
	setfillcolor(RGB(202, 168, 43));
	solidcircle(22, 16, 4);
	solidcircle(78, 16, 4);
	solidcircle(22, 65, 4);
	solidcircle(78, 65, 4);
	SetWorkingImage();

	// 大块绘制
	img_big = new IMAGE(200, 200);
	// 初始化处理区域
	SetWorkingImage(img_big);
	setbkcolor(RGB(73, 130, 120));
	cleardevice();
	// 绘制
	setfillcolor(RGB(215, 102, 65));
	solidroundrect(0, 0, 200, 200, 30, 30);
	setfillcolor(RGB(254, 195, 166));
	solidroundrect(5, 0, 195, 180, 20, 20);
	setfillcolor(RGB(194, 98, 62));
	solidroundrect(5, 180, 195, 200, 20, 20);
	setfillcolor(RGB(252, 153, 108));
	solidroundrect(5, 6, 189, 179, 15, 15);
	setfillcolor(RGB(210, 100, 60));
	solidcircle(22, 16, 4);
	solidcircle(178, 16, 4);
	solidcircle(22, 165, 4);
	solidcircle(178, 165, 4);
	POINT pts[20];
	setfillcolor(RGB(254, 195, 166));
	setlinecolor(RGB(254, 195, 166));
	pts[0].x = 100;	pts[0].y = 125;
	pts[1].x = 125;	pts[1].y = 100;
	pts[2].x = 150;	pts[2].y = 100;
	pts[3].x = 100;	pts[3].y = 150;
	pts[4].x = 50;	pts[4].y = 100;
	pts[5].x = 75;	pts[5].y = 100;
	// 绘制
	fillpolygon(pts, 6);
	pts[0].x = 100;	pts[0].y = 125 - 60;
	pts[1].x = 125;	pts[1].y = 100 - 60;
	pts[2].x = 150;	pts[2].y = 100 - 60;
	pts[3].x = 100;	pts[3].y = 150 - 60;
	pts[4].x = 50;	pts[4].y = 100 - 60;
	pts[5].x = 75;	pts[5].y = 100 - 60;
	// 绘制
	fillpolygon(pts, 6);
	SetWorkingImage();

	// 按钮初始化
	for (i = 0; i < 12; i++)
	{
		box_button[i].posx1 = 458 + i % 2 * 70;
		box_button[i].posy1 = 40 + i / 2 * 100;
		box_button[i].posx2 = 508 + i % 2 * 70;
		box_button[i].posy2 = 90 + i / 2 * 100;
	}

	// 棋盘初始化
	create();

	// 棋盘初始化
	for (i = 0; i < 20; i++)
	{
		switch (pan[i])
		{
		case 1: {pan[i + 1] = 5; pan[i + 4] = 6; pan[i + 5] = 7; break; }
		case 2: {pan[i + 1] = 8; break; }
		case 3: {pan[i + 4] = 9; break; }
		default:break;
		}
	}

	// 绘制初始
	draw_scene(0);

}

// 游戏函数
void Gary::game()
{
	int i, j, k;
	// 点哪个格子了
	i = (m.y - 25) / 102 * 4 + (m.x - 25) / 102;
	// 非空格子
	if (pan[i] > 0)
	{
		// 标记
		setfillcolor(WHITE);
		solidcircle(25 + 51 + i % 4 * 102, 25 + 51 + i / 4 * 102, 5);
		FlushBatchDraw();
		// 分类讨论整理
		switch (pan[i])
		{
		case 5: {i = i - 1; break; }
		case 6: {i = i - 4; break; }
		case 7: {i = i - 5; break; }
		case 8: {i = i - 1; break; }
		case 9: {i = i - 4; break; }
		default:break;
		}
		// 又移动到哪个空格子了
		k = 0;
		while (k == 0)
		{
			// 鼠标信息
			if (peekmessage(&m, EM_MOUSE | EM_KEY))
			{
				// 左键单击判断
				if (m.message == WM_LBUTTONDOWN)
				{
					// 单击在棋盘范围
					if (m.x > 20 && m.x < 433 && m.y>15 && m.y < 540)
					{
						j = (m.y - 25) / 102 * 4 + (m.x - 25) / 102;
						if (pan[j] == 0)
						{
							k = 1;
						}
						else
						{
							k = 2;
						}
					}
				}
				else if (m.message == WM_MOUSEMOVE)
				{
					// 单击在棋盘范围
					if (m.x > 20 && m.x < 433 && m.y>15 && m.y < 540)
					{
						j = (m.y - 25) / 102 * 4 + (m.x - 25) / 102;
						if (pan[j] == 0)
						{
							k = 1;
						}
					}
				}
			}
		}
		// 点击空格时分类讨论
		if (k == 1)
		{
			switch (pan[i])
			{
				// 大格
			case 1:
			{
					  // 上
					  if ((j == i - 3 || j == i - 4) && pan[i - 4] == 0 && pan[i - 3] == 0 && i / 4 > 0)
					  {
						  pan[i - 4] = 1;
						  pan[i + 4] = 0;
						  pan[i + 5] = 0;
					  }
					  // 下
					  else if ((j == i + 8 || j == i + 9) && pan[i + 8] == 0 && pan[i + 9] == 0 && i / 4 < 3)
					  {
						  pan[i + 4] = 1;
						  pan[i] = 0;
						  pan[i + 1] = 0;
					  }
					  // 左
					  else if ((j == i - 1 || j == i + 3) && pan[i - 1] == 0 && pan[i + 3] == 0 && i % 4 > 0)
					  {
						  pan[i - 1] = 1;
						  pan[i + 1] = 0;
						  pan[i + 5] = 0;
					  }
					  // 右
					  else if ((j == i + 2 || j == i + 6) && pan[i + 2] == 0 && pan[i + 6] == 0 && i % 4 < 2)
					  {
						  pan[i + 1] = 1;
						  pan[i] = 0;
						  pan[i + 4] = 0;
					  }
					  break;
			}
				// 横格
			case 2:
			{
					  // 上
					  if ((j == i - 3 || j == i - 4) && pan[i - 4] == 0 && pan[i - 3] == 0 && i / 4 > 0)
					  {
						  pan[i - 4] = 2;
						  pan[i] = 0;
						  pan[i + 1] = 0;
					  }
					  // 下
					  else if ((j == i + 4 || j == i + 5) && pan[i + 4] == 0 && pan[i + 5] == 0 && i / 4 < 4)
					  {
						  pan[i + 4] = 2;
						  pan[i] = 0;
						  pan[i + 1] = 0;
					  }
					  // 左
					  else if (j == i - 1 && pan[i - 1] == 0 && i % 4 > 0)
					  {
						  pan[i - 1] = 2;
						  pan[i + 1] = 0;
					  }
					  // 右
					  else if (j == i + 2 && pan[i + 2] == 0 && i % 4 < 2)
					  {
						  pan[i + 1] = 2;
						  pan[i] = 0;
					  }
					  break;
			}
				// 纵格
			case 3:
			{
					  // 上
					  if (j == i - 4 && pan[i - 4] == 0 && i / 4 > 0)
					  {
						  pan[i - 4] = 3;
						  pan[i + 4] = 0;
					  }
					  // 下
					  else if (j == i + 8 && pan[i + 8] == 0 && i / 4 < 3)
					  {
						  pan[i + 4] = 3;
						  pan[i] = 0;
					  }
					  // 左
					  else if ((j == i - 1 || j == i + 3) && pan[i - 1] == 0 && pan[i + 3] == 0 && i % 4 > 0)
					  {
						  pan[i - 1] = 3;
						  pan[i] = 0;
						  pan[i + 4] = 0;
					  }
					  // 右
					  else if ((j == i + 1 || j == i + 5) && pan[i + 1] == 0 && pan[i + 5] == 0 && i % 4 < 3)
					  {
						  pan[i + 1] = 3;
						  pan[i] = 0;
						  pan[i + 4] = 0;
					  }
					  break;
			}
			case 4: {if ((j == i - 4 && i / 4 > 0) || (j == i - 1 && i % 4 > 0) || (j == i + 1 && i % 4 < 3) || (j == i + 4 && i / 4 < 4)) { pan[j] = 4; pan[i] = 0; }break; }
			default:break;
			}
			// 棋盘标准化
			for (i = 0; i < 20; i++)
			{
				switch (pan[i])
				{
				case 1: {pan[i + 1] = 5; pan[i + 4] = 6; pan[i + 5] = 7; break; }
				case 2: {pan[i + 1] = 8; break; }
				case 3: {pan[i + 4] = 9; break; }
				default:break;
				}
			}
		}
		// 绘制
		// 背景绘制
		setbkcolor(RGB(136, 192, 160));
		cleardevice();
		// 棋盘绘制
		setfillcolor(RGB(73, 130, 120));
		setlinecolor(RGB(168, 226, 195));
		fillroundrect(20, 15, 25 + 102 * 4, 30 + 102 * 5, 30, 30);
		for (i = 0; i < 20; i++)
		{
			switch (pan[i])
			{
			case 0:putimage(25 + i % 4 * 102, 25 + i / 4 * 102, img_space); break;
			case 1:putimage(25 + i % 4 * 102, 25 + i / 4 * 102, img_big); break;
			case 2:putimage(25 + i % 4 * 102, 25 + i / 4 * 102, img_transverse); break;
			case 3:putimage(25 + i % 4 * 102, 25 + i / 4 * 102, img_portrait); break;
			case 4:putimage(25 + i % 4 * 102, 25 + i / 4 * 102, img_small); break;
			default:break;
			}
			// 出口绘制
			if (pan[i] == 0 && (i == 13 || i == 14 || i == 17 || i == 18))
			{
				setlinecolor(RGB(230, 230, 230));
				setlinestyle(PS_SOLID, 10);
				setfillcolor(RGB(112, 180, 167));
				fillcircle(25 + 51 + i % 4 * 102, 25 + 51 + i / 4 * 102, 20);
				setlinecolor(RGB(168, 226, 195));
				setfillcolor(RGB(73, 130, 120));
				setlinestyle(PS_SOLID, 3);
			}
		}
		// 按钮绘制
		TCHAR s[25];
		setlinecolor(RGB(155, 195, 230));
		setfillcolor(RGB(80, 189, 222));
		settextcolor(RGB(230, 230, 230));
		settextstyle(30, 20, _T("Times New Roman"));
		setbkcolor(RGB(80, 189, 222));
		// 标准棋盘按钮
		for (i = 0; i < 12; i++)
		{
			fillroundrect(box_button[i].posx1, box_button[i].posy1, box_button[i].posx2, box_button[i].posy2, 20, 20);
			_stprintf_s(s, _T("%d"), i);
			outtextxy(box_button[i].posx1 + 13 - 12 * (i / 10), box_button[i].posy1 + 10, s);
		}
		// 其他按钮
		settextstyle(100, 100, _T("Webdings"));
		settextcolor(RGB(73, 130, 120));
		setbkmode(TRANSPARENT);
		outtextxy(102 - 50, 580 - 30, 0x34); // 播放，求解
		outtextxy(214 - 50, 580 - 30, 0x33); // 重置，恢复初始盘面
		outtextxy(326 - 50, 580 - 30, 0x71); // 刷新，随机盘面按钮
		// 恢复填充
		setbkmode(OPAQUE);
		setbkmode(OPAQUE);
		settextcolor(RGB(230, 230, 230));
		settextstyle(30, 20, _T("宋体"));
		setbkcolor(RGB(136, 192, 160));
		outtextxy(102 - 50, 655, _T("求解"));
		outtextxy(214 - 50, 655, _T("恢复"));
		outtextxy(326 - 50, 655, _T("刷新"));
		FlushBatchDraw();
		// 成功结束
		if (pan[13] == 1)
		{
			exit_move = 2;
		}
	}
}


// 窗口主视角函数，获取用户操作
void Gary::move()
{
	int k;
	exit_move = 0;
	while (exit_move == 0)
	{
		// 鼠标信息
		if (peekmessage(&m, EM_MOUSE | EM_KEY))
		{
			// 左键单击判断
			if (m.message == WM_LBUTTONDOWN)
			{
				// 单击在棋盘范围
				if (m.x > 20 && m.x < 433 && m.y>15 && m.y < 540)
				{
					// 游戏函数
					game();
				}
				// 经典盘面按钮
				else if (m.x > 458)
				{
					// 切换
					num_mod = (m.x - 458) / 70 + (m.y - 40) / 100 * 2;
					// 生成
					create();
					// 绘制
					draw_scene(0);
				}
				// 演示按钮
				else if (pow(double(m.x - 102), 2) + pow(double(m.y - 600), 2) < 2500)
				{
					// 初始化
					num_eat = 0;
					if (num_mod == 9 || num_mod == 11)
					{
						num_over = 8;
					}
					else
					{
						num_over = 9;
					}
					solve();
					num_over = 13;
					solve();
					if (exit_move == 0)
					{
						// 绘制解题过程
						for (k = 0; k <= num_eat; k++)
						{
							// 根据特征值画棋面
							draw_scene(k);
							Sleep(500);
						}
					}
				}
				// 重置按钮
				else if (pow(double(m.x - 214), 2) + pow(double(m.y - 600), 2) < 2500)
				{
					// 根据特征值画棋面
					draw_scene(0);
					FlushBatchDraw();
				}
				// 刷新按钮
				else if (pow(double(m.x - 326), 2) + pow(double(m.y - 600), 2) < 2500)
				{
					// 切换
					num_mod = 12;
					// 生成
					create();
					// 绘制
					draw_scene(0);
				}
				// 清空鼠标队列
				flushmessage();
			}
		}
	}
	// 结束提示
	if (exit_move == 2)
	{
		MessageBox(hOut, _T("成功啦，点击确定即刷新"), _T("来自小豆子的提醒"), MB_OK);
	}
	else if (exit_move == 1)
	{
		MessageBox(hOut, _T("无解，点击确定即刷新"), _T("来自小豆子的提醒"), MB_OK);
	}
}

// 主进程
void Gary::carry()
{
	// 窗口定义
	hOut = initgraph(600, 102 * 5 + 200);
	SetWindowText(hOut, _T("华容道"));
	// 进程控制
	exit_carry = 0;
	BeginBatchDraw();
	while (exit_carry == 0)
	{
		initialization();
		move();
	}
	EndBatchDraw();
	closegraph();
}

// 主函数
int main(void)
{
	Gary G;
	G.carry();
	return 0;
}