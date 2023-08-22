#define _CRT_SECURE_NO_WARNINGS
# include <math.h>
# include <graphics.h>
# include <time.h>
# include <string>

static HWND hOut;						// ����

// ����һ���ṹ�壬��
struct Node1
{
	int num;							// ���
	int num_transverse;					// ��������ֵ
	int num_portrait;					// ��������ֵ
	int num_other;						// ��������ֵ
	int num_father;						// �����
};
Node1 box[200001];						// Ԥ�ƽ��

// ����һ���ṹ�壬��ʱ���
struct Node2
{
	int num_transverse;					// ��������ֵ
	int num_portrait;					// ��������ֵ
	int num_other;						// ��������ֵ
};

// ����һ���ṹ�壬��ť
struct Node3
{
	int posx1, posy1, posx2, posy2;		// ����
};

// ����һ����
class Gary
{
public:
	void carry();						// ������
	void initialization();				// ��ʼ��
	void move();						// �������ӽǺ���
	void draw_scene(int num_box);		// ���ƽ��溯��
	void create();						// ���ɺ���
	void decode();						// ���뺯��
	void code();						// ���뺯��
	void check(int a, int b, int c);	// ����ظ�����
	void single_space(int mode);		// �����ƶ�����
	void double_space();				// ˫���ƶ�����
	void over();						// �����жϺ���
	void game();						// ��Ϸ����
	void solve();						// ��⺯��

	int exit_carry;						// ��ѭ�������Ʋ���
	int exit_move;						// ��ʼ������Ʋ���
	int num_double[31];					// �������ݴ���
	int num_step;						// ������
	int num_eat;						// ��������Ȳ���
	int num_start;						// ���������
	int num_over;						// ����յ����
	int num_mod;						// ��Ϸģʽ
	int box_transverse[6];				// ����
	int box_portrait[6];				// ����
	int box_big;						// ���
	int box_space[2];					// �ո�
	int num_transverse;					// ��������
	int num_portrait;					// ��������
	int pan[30];						// ������Ϣ
	double num_flag;					// �������ϵ��
	double num_flag1;					// �������ϵ��
	IMAGE* img_transverse;				// ���ͼƬ
	IMAGE* img_portrait;				// �ݿ�ͼƬ
	IMAGE* img_small;					// С��ͼƬ
	IMAGE* img_big;						// ���ͼƬ
	IMAGE* img_space;					// �ո�ͼƬ
	ExMessage m;						// ��궨��
	Node2 eat[200];						// ��ʱ��Ž��
	Node3 box_button[20];				// ��ť��Ԥ��
};

// �������ƺ���
void Gary::draw_scene(int num_box)
{
	int i, j;
	// ����
	for (i = 0; i < num_transverse; i++)
	{
		box_transverse[i] = (eat[num_box].num_transverse & (num_double[i * 5 + 5] - num_double[i * 5])) / num_double[i * 5];
	}
	// ����
	for (i = 0; i < num_portrait; i++)
	{
		box_portrait[i] = (eat[num_box].num_portrait & (num_double[i * 5 + 5] - num_double[i * 5])) / num_double[i * 5];
	}
	// ���
	box_big = (eat[num_box].num_other & (num_double[21] - num_double[16])) / num_double[16];
	// �ո�
	box_space[0] = (eat[num_box].num_other & (num_double[13] - num_double[8])) / num_double[8];
	box_space[1] = (eat[num_box].num_other & (num_double[5] - num_double[0]));
	// ��ʼ��
	for (i = 0; i < 20; i++)
	{
		pan[i] = -1;
	}
	// ����
	for (i = 0; i < num_transverse; i++)
	{
		pan[box_transverse[i]] = 2;
		pan[box_transverse[i] + 1] = 5;
	}
	// ����
	for (i = 0; i < num_portrait; i++)
	{
		pan[box_portrait[i]] = 3;
		pan[box_portrait[i] + 4] = 5;

	}
	// ���
	pan[box_big] = 1;
	pan[box_big + 1] = 5;
	pan[box_big + 4] = 5;
	pan[box_big + 5] = 5;
	// �ո�
	pan[box_space[0]] = 0;
	pan[box_space[1]] = 0;
	// С��
	for (j = 0; j < 20; j++)
	{
		if (pan[j] == -1)
		{
			pan[j] = 4;
		}
	}
	// ��������
	setbkcolor(RGB(136, 192, 160));
	cleardevice();
	// ���̻���
	setlinestyle(PS_SOLID, 3);
	setfillcolor(RGB(73, 130, 120));
	setlinecolor(RGB(168, 226, 195));
	fillroundrect(20, 15, 25 + 102 * 4, 30 + 102 * 5, 30, 30);
	for (i = 0; i < 20; i++)
	{
		// ���ݸ������ͻ���
		switch (pan[i])
		{
		case 0:putimage(25 + i % 4 * 102, 25 + i / 4 * 102, img_space); break;
		case 1:putimage(25 + i % 4 * 102, 25 + i / 4 * 102, img_big); break;
		case 2:putimage(25 + i % 4 * 102, 25 + i / 4 * 102, img_transverse); break;
		case 3:putimage(25 + i % 4 * 102, 25 + i / 4 * 102, img_portrait); break;
		case 4:putimage(25 + i % 4 * 102, 25 + i / 4 * 102, img_small); break;
		default:break;
		}
		// ���ڻ���
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

	// ��ť����
	TCHAR s[25];
	setlinecolor(RGB(155, 195, 230));
	setfillcolor(RGB(80, 189, 222));
	settextcolor(RGB(230, 230, 230));
	settextstyle(30, 20, _T("Times New Roman"));
	setbkcolor(RGB(80, 189, 222));
	// ��׼���̰�ť
	for (i = 0; i < 12; i++)
	{
		fillroundrect(box_button[i].posx1, box_button[i].posy1, box_button[i].posx2, box_button[i].posy2, 20, 20);
		_stprintf_s(s, _T("%d"), i);
		outtextxy(box_button[i].posx1 + 13 - 11 * (i / 10), box_button[i].posy1 + 10, s);
	}
	// ������ť
	settextstyle(100, 100, _T("Webdings"));
	settextcolor(RGB(73, 130, 120));
	setbkmode(TRANSPARENT);
	// ���ţ����
	outtextxy(102 - 50, 580 - 30, 0x34);
	// ���ã��ָ���ʼ����
	outtextxy(214 - 50, 580 - 30, 0x33);
	// ˢ�£�������水ť
	outtextxy(326 - 50, 580 - 30, 0x71);
	// �ָ����
	setbkmode(OPAQUE);
	settextcolor(RGB(230, 230, 230));
	settextstyle(30, 20, _T("����"));
	setbkcolor(RGB(136, 192, 160));
	outtextxy(102 - 50, 655, _T("���"));
	outtextxy(214 - 50, 655, _T("�ָ�"));
	outtextxy(326 - 50, 655, _T("ˢ��"));

	FlushBatchDraw();
}

// ����
void Gary::decode()
{
	int i;
	// ��������ֵ������
	// ����
	for (i = 0; i < num_transverse; i++)
	{
		box_transverse[i] = (box[int(num_flag)].num_transverse & (num_double[i * 5 + 5] - num_double[i * 5])) / num_double[i * 5];
	}
	// ����
	for (i = 0; i < num_portrait; i++)
	{
		box_portrait[i] = (box[int(num_flag)].num_portrait & (num_double[i * 5 + 5] - num_double[i * 5])) / num_double[i * 5];
	}
	// ���
	box_big = (box[int(num_flag)].num_other & (num_double[21] - num_double[16])) / num_double[16];
	// �ո�
	box_space[0] = (box[int(num_flag)].num_other & (num_double[13] - num_double[8])) / num_double[8];
	box_space[1] = (box[int(num_flag)].num_other & (num_double[5] - num_double[0]));
}

// ����ظ�����
void Gary::check(int a, int b, int c)
{
	int k, t;
	// ȫ�ּ��
	k = 0;
	for (t = int(num_flag1 - 1); t >= 0; t--)
	{
		if (box[t].num_transverse == a && box[t].num_portrait == b && box[t].num_other == c) { k = 1; break; }
	}
	// ���ظ��������ӽ��
	if (k == 0)
	{
		// ����ֵ¼�룬�����¼��
		box[int(num_flag1)].num_transverse = a;
		box[int(num_flag1)].num_portrait = b;
		box[int(num_flag1)].num_other = c;
		box[int(num_flag1)].num_father = int(num_flag);
		// ���
		box[int(num_flag1)].num = box[box[int(num_flag1)].num_father].num + 1;
		// ����
		if (box[int(num_flag1)].num > num_step)
		{
			// �Ӳ�
			num_step = box[int(num_flag1)].num;
			// ����������
			setlinecolor(RGB(155, 195, 230));
			setfillcolor(RGB(155, 195, 230));
			fillroundrect(50, 640, int(70.0 + 330.0 * double(num_eat + num_step) / 120.0), 650, 20, 20);
			FlushBatchDraw();
		}
		// ��Ǽ�һ
		num_flag1++;
	}
}


// ���ո��ƶ�����
void Gary::single_space(int mode)
{
	int i, j, k;
	int a, b, c;
	int t;
	// �ո��ȡ
	i = box_big;
	j = (mode == 0 ? box_space[0] : box_space[1]);
	k = (mode == 0 ? box_space[1] : box_space[0]);
	// �ո�
	// �ϣ����Ǵ�飬������һ���ո񣬲������ϲ⣬���Ǻ�飩
	if (j - 4 != i + 4 && j - 4 != i + 5 && j - 4 != k && j > 3)
	{
		for (t = 0; t < num_transverse; t++)
		{
			if (j - 4 == box_transverse[t] || j - 4 == box_transverse[t] + 1)break;
		}
		// ���Ǻ��
		if (t == num_transverse)
		{
			for (t = 0; t < num_portrait; t++)
			{
				if (j - 4 == box_portrait[t] + 4)break;
			}
			a = box[int(num_flag)].num_transverse;
			// �����ݿ�
			if (t == num_portrait)
			{
				b = box[int(num_flag)].num_portrait;
				c = (mode == 0 ? (i * num_double[16] + (j - 4) * num_double[8] + k * num_double[0]) : (i * num_double[16] + k * num_double[8] + (j - 4) * num_double[0]));
			}
			// ��
			else
			{
				b = box[int(num_flag)].num_portrait + 4 * num_double[t * 5];
				c = (mode == 0 ? (i * num_double[16] + (j - 8) * num_double[8] + k * num_double[0]) : (i * num_double[16] + k * num_double[8] + (j - 8) * num_double[0]));
			}
			check(a, b, c);
		}
	}
	// �£����Ǵ�飬������һ���ո񣬲������²⣬���Ǻ�飩
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
			// �����ݿ�
			if (t == num_portrait)
			{
				b = box[int(num_flag)].num_portrait;
				c = (mode == 0 ? (i * num_double[16] + (j + 4) * num_double[8] + k * num_double[0]) : (i * num_double[16] + k * num_double[8] + (j + 4) * num_double[0]));
			}
			// ��
			else
			{
				b = box[int(num_flag)].num_portrait - 4 * num_double[t * 5];
				c = (mode == 0 ? (i * num_double[16] + (j + 8) * num_double[8] + k * num_double[0]) : (i * num_double[16] + k * num_double[8] + (j + 8) * num_double[0]));
			}
			check(a, b, c);
		}
	}
	// �󣨲��Ǵ�飬������һ���ո񣬲�������⣬�����ݿ飩
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
			// ���Ǻ��
			if (t == num_transverse)
			{
				a = box[int(num_flag)].num_transverse;
				c = (mode == 0 ? (i * num_double[16] + (j - 1) * num_double[8] + k * num_double[0]) : (i * num_double[16] + k * num_double[8] + (j - 1) * num_double[0]));
			}
			// �Ǻ��
			else
			{
				a = box[int(num_flag)].num_transverse + 1 * num_double[t * 5];
				c = (mode == 0 ? (i * num_double[16] + (j - 2) * num_double[8] + k * num_double[0]) : (i * num_double[16] + k * num_double[8] + (j - 2) * num_double[0]));
			}
			check(a, b, c);
		}
	}
	// �ң����Ǵ�飬������һ���ո񣬲������Ҳ⣬�����ݿ飩
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
			// ���Ǻ��
			if (t == num_transverse)
			{
				a = box[int(num_flag)].num_transverse;
				c = (mode == 0 ? (i * num_double[16] + (j + 1) * num_double[8] + k * num_double[0]) : (i * num_double[16] + k * num_double[8] + (j + 1) * num_double[0]));
			}
			// �Ǻ��
			else
			{
				a = box[int(num_flag)].num_transverse - 1 * num_double[t * 5];
				c = (mode == 0 ? (i * num_double[16] + (j + 2) * num_double[8] + k * num_double[0]) : (i * num_double[16] + k * num_double[8] + (j + 2) * num_double[0]));
			}
			check(a, b, c);
		}
	}
}

// ˫�ո��ƶ�����
void Gary::double_space()
{
	int i, j, k, t, a, b, c;
	// ��ȡ
	i = box_big;
	j = box_space[0];
	k = box_space[1];
	// ����ƶ�
	// ��
	if (i > 3 && ((i - 4 == k && i - 3 == j) || (i - 4 == j && i - 3 == k)))
	{
		a = box[int(num_flag)].num_transverse;
		b = box[int(num_flag)].num_portrait;
		c = (i - 4) * num_double[16] + (j + 8) * num_double[8] + (k + 8) * num_double[0];
		check(a, b, c);
	}
	// ��
	if (i < 12 && ((i + 8 == k && i + 9 == j) || (i + 8 == j && i + 9 == k)))
	{
		a = box[int(num_flag)].num_transverse;
		b = box[int(num_flag)].num_portrait;
		c = (i + 4) * num_double[16] + (j - 8) * num_double[8] + (k - 8) * num_double[0];
		check(a, b, c);
	}
	// ��
	if (i % 4 > 0 && ((i - 1 == k && i + 3 == j) || (i - 1 == j && i + 3 == k)))
	{
		a = box[int(num_flag)].num_transverse;
		b = box[int(num_flag)].num_portrait;
		c = (i - 1) * num_double[16] + (j + 2) * num_double[8] + (k + 2) * num_double[0];
		check(a, b, c);
	}
	// ��
	if (i % 4 < 2 && ((i + 2 == k && i + 6 == j) || (i + 2 == j && i + 6 == k)))
	{
		a = box[int(num_flag)].num_transverse;
		b = box[int(num_flag)].num_portrait;
		c = (i + 1) * num_double[16] + (j - 2) * num_double[8] + (k - 2) * num_double[0];
		check(a, b, c);
	}

	// ���
	for (t = 0; t < num_transverse; t++)
	{
		i = box_transverse[t];
		// ��
		if (i > 3 && ((i - 4 == k && i - 3 == j) || (i - 4 == j && i - 3 == k)))
		{
			a = box[int(num_flag)].num_transverse - 4 * num_double[t * 5];
			b = box[int(num_flag)].num_portrait;
			c = box_big * num_double[16] + (j + 4) * num_double[8] + (k + 4) * num_double[0];
			check(a, b, c);
		}
		// ��
		if (i < 16 && ((i + 4 == k && i + 5 == j) || (i + 4 == j && i + 5 == k)))
		{
			a = box[int(num_flag)].num_transverse + 4 * num_double[t * 5];
			b = box[int(num_flag)].num_portrait;
			c = box_big * num_double[16] + (j - 4) * num_double[8] + (k - 4) * num_double[0];
			check(a, b, c);
		}
	}

	// �ݿ�
	for (t = 0; t < num_portrait; t++)
	{
		i = box_portrait[t];
		// ��
		if (i % 4 > 0 && ((i - 1 == k && i + 3 == j) || (i - 1 == j && i + 3 == k)))
		{
			a = box[int(num_flag)].num_transverse;
			b = box[int(num_flag)].num_portrait - 1 * num_double[t * 5];
			c = box_big * num_double[16] + (j + 1) * num_double[8] + (k + 1) * num_double[0];
			check(a, b, c);
		}
		// ��
		if (i % 4 < 3 && ((i + 1 == k && i + 5 == j) || (i + 1 == j && i + 5 == k)))
		{
			a = box[int(num_flag)].num_transverse;
			b = box[int(num_flag)].num_portrait + 1 * num_double[t * 5];
			c = box_big * num_double[16] + (j - 1) * num_double[8] + (k - 1) * num_double[0];
			check(a, b, c);
		}
	}
}

// �����жϺ���
void Gary::over()
{
	// ����ƶ�������յ����
	if ((box[int(num_flag)].num_other & 0xff0000) / num_double[16] == num_over || num_flag1 < num_flag)
	{
		num_start = 1;
	}
}

// ���뺯��
void Gary::code()
{
	int i, j, k;
	// ����
	decode();
	// �������
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
	// �ݿ�����
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
	// �ո�����
	if (box_space[0] > box_space[1])
	{
		k = box_space[0];
		box_space[0] = box_space[1];
		box_space[1] = k;
	}
	// ����
	box[int(num_flag)].num_transverse = 0;
	box[int(num_flag)].num_portrait = 0;

	for (i = 0; i < 6; i++)
	{
		box[int(num_flag)].num_transverse += box_transverse[i] * num_double[i * 5];
		box[int(num_flag)].num_portrait += box_portrait[i] * num_double[i * 5];
	}
	box[int(num_flag)].num_other = box_big * num_double[16] + box_space[0] * num_double[8] + box_space[1] * num_double[0];

}

// ���ɺ���
void Gary::create()
{
	// ���̳�״̬����
	// ����
	box[0].num_transverse = 0;
	// ����
	box[0].num_portrait = 0;
	// ��׼����
	// ���̲���
	switch (num_mod)
	{
	case 0:
	{
			  // ���
			  box_big = 1;
			  // ���
			  box_transverse[0] = 9;
			  num_transverse = 1;
			  // �ݸ�
			  box_portrait[0] = 0;
			  box_portrait[1] = 3;
			  box_portrait[2] = 8;
			  box_portrait[3] = 11;
			  num_portrait = 4;
			  // �ո�
			  box_space[0] = 17;
			  box_space[1] = 18;
			  break;
	}
	case 1:
	{
			  // ���
			  box_big = 1;
			  // ���
			  box_transverse[0] = 9;
			  num_transverse = 1;
			  // �ݸ�
			  box_portrait[0] = 0;
			  box_portrait[1] = 3;
			  box_portrait[2] = 12;
			  box_portrait[3] = 15;
			  num_portrait = 4;
			  // �ո�
			  box_space[0] = 17;
			  box_space[1] = 18;
			  break;
	}
	case 2:
	{
			  // ���
			  box_big = 1;
			  // ���
			  box_transverse[0] = 9;
			  num_transverse = 1;
			  // �ݸ�
			  box_portrait[0] = 0;
			  box_portrait[1] = 8;
			  box_portrait[2] = 13;
			  box_portrait[3] = 14;
			  num_portrait = 4;
			  // �ո�
			  box_space[0] = 16;
			  box_space[1] = 19;
			  break;
	}
	case 3:
	{
			  // ���
			  box_big = 1;
			  // ���
			  box_transverse[0] = 13;
			  num_transverse = 1;
			  // �ݸ�
			  box_portrait[0] = 0;
			  box_portrait[1] = 3;
			  box_portrait[2] = 12;
			  box_portrait[3] = 15;
			  num_portrait = 4;
			  // �ո�
			  box_space[0] = 17;
			  box_space[1] = 18;
			  break;
	}
	case 4:
	{
			  // ���
			  box_big = 1;
			  // ���
			  box_transverse[0] = 17;
			  num_transverse = 1;
			  // �ݸ�
			  box_portrait[0] = 0;
			  box_portrait[1] = 3;
			  box_portrait[2] = 9;
			  box_portrait[3] = 10;
			  num_portrait = 4;
			  // �ո�
			  box_space[0] = 8;
			  box_space[1] = 11;
			  break;
	}
	case 5:
	{
			  // ���
			  box_big = 1;
			  // ���
			  box_transverse[0] = 9;
			  num_transverse = 1;
			  // �ݸ�
			  box_portrait[0] = 8;
			  box_portrait[1] = 11;
			  box_portrait[2] = 13;
			  box_portrait[3] = 14;
			  num_portrait = 4;
			  // �ո�
			  box_space[0] = 16;
			  box_space[1] = 19;
			  break;
	}
	case 6:
	{
			  // ���
			  box_big = 1;
			  // ���
			  box_transverse[0] = 10;
			  num_transverse = 1;
			  // �ݸ�
			  box_portrait[0] = 0;
			  box_portrait[1] = 3;
			  box_portrait[2] = 12;
			  box_portrait[3] = 13;
			  num_portrait = 4;
			  // �ո�
			  box_space[0] = 18;
			  box_space[1] = 19;
			  break;
	}
	case 7:
	{
			  // ���
			  box_big = 1;
			  // ���
			  box_transverse[0] = 9;
			  num_transverse = 1;
			  // �ݸ�
			  box_portrait[0] = 4;
			  box_portrait[1] = 7;
			  box_portrait[2] = 12;
			  box_portrait[3] = 15;
			  num_portrait = 4;
			  // �ո�
			  box_space[0] = 17;
			  box_space[1] = 18;
			  break;
	}
	case 8:
	{
			  // ���
			  box_big = 0;
			  // ���
			  box_transverse[0] = 8;
			  num_transverse = 1;
			  // �ݸ�
			  box_portrait[0] = 2;
			  box_portrait[1] = 3;
			  box_portrait[2] = 12;
			  box_portrait[3] = 13;
			  num_portrait = 4;
			  // �ո�
			  box_space[0] = 18;
			  box_space[1] = 19;
			  break;
	}
	case 9:
	{
			  // ���
			  box_big = 5;
			  // ���
			  box_transverse[0] = 13;
			  num_transverse = 1;
			  // �ݸ�
			  box_portrait[0] = 0;
			  box_portrait[1] = 3;
			  box_portrait[2] = 8;
			  box_portrait[3] = 11;
			  num_portrait = 4;
			  // �ո�
			  box_space[0] = 18;
			  box_space[1] = 19;
			  break;
	}
	case 10:
	{
			   // ���
			   box_big = 5;
			   // ���
			   box_transverse[0] = 1;
			   num_transverse = 1;
			   // �ݸ�
			   box_portrait[0] = 12;
			   box_portrait[1] = 13;
			   box_portrait[2] = 14;
			   box_portrait[3] = 15;
			   num_portrait = 4;
			   // �ո�
			   box_space[0] = 0;
			   box_space[1] = 3;
			   break;
	}
	case 11:
	{
			   // ���
			   box_big = 5;
			   // ���
			   box_transverse[0] = 13;
			   num_transverse = 1;
			   // �ݸ�
			   box_portrait[0] = 0;
			   box_portrait[1] = 3;
			   box_portrait[2] = 11;
			   box_portrait[3] = 12;
			   num_portrait = 4;
			   // �ո�
			   box_space[0] = 17;
			   box_space[1] = 18;
			   break;
	}
	default:break;
	}

	int i, j, k, t;
	// �������
	if (num_mod == 12)
	{
		// ��ʼ��
		for (i = 0; i < 20; i++)
		{
			pan[i] = 0;
		}

		// �������
		box_big = rand() % 3;
		pan[box_big] = 1;
		pan[box_big + 1] = 5;
		pan[box_big + 4] = 6;
		pan[box_big + 5] = 7;

		// �������
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

		// �ݿ�����
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

		// �ո�����
		box_space[0] = 17;
		while (pan[box_space[0]] != 0)
		{
			box_space[0] = rand() % 20;
		}
		pan[box_space[0]] = 4;
		// �ո�
		box_space[1] = 18;
		while (pan[box_space[1]] != 0)
		{
			box_space[1] = rand() % 20;
		}
		pan[box_space[1]] = 4;
		// С������
		for (k = 0; k < 20; k++)
		{
			if (pan[k] == 4) { pan[k] = 0; }
			else if (pan[k] == 0) { pan[k] = 4; }
		}
	}
	// ����
	for (i = 0; i < 6; i++)
	{
		box[0].num_transverse += box_transverse[i] * num_double[i * 5];
		box[0].num_portrait += box_portrait[i] * num_double[i * 5];
	}
	box[0].num_other = box_big * num_double[16] + box_space[0] * num_double[8] + box_space[1] * num_double[0];
	box[0].num_father = -1;
	// �������ʼ��
	eat[0].num_transverse = box[0].num_transverse;
	eat[0].num_portrait = box[0].num_portrait;
	eat[0].num_other = box[0].num_other;

}

// ��⺯��
void Gary::solve()
{
	int i, j, k;

	// ����������
	setlinecolor(RGB(155, 195, 230));
	setfillcolor(RGB(73, 130, 120));
	fillroundrect(50, 640, 400, 650, 20, 20);
	FlushBatchDraw();

	// ��ʼ��
	box[0].num_transverse = eat[num_eat].num_transverse;
	box[0].num_portrait = eat[num_eat].num_portrait;
	box[0].num_other = eat[num_eat].num_other;

	// ������ʼ��
	num_step = 0;
	num_flag = 0;
	num_flag1 = 1;
	// ����
	code();
	num_start = 0;
	while (num_start == 0)
	{
		// ����
		decode();
		// ���������
		// ˫�ո��ƶ�
		double_space();
		// ���ո��ƶ�
		single_space(0);
		single_space(1);
		// �������һ
		num_flag++;
		// ����
		code();
		// �����жϺ���
		over();
		// ��������޽��ж�
		if (num_flag >= num_flag1 || (num_mod == 12 && (num_flag1 > 100000 || num_step > 100)))
		{
			num_start = 2;
			exit_move = 1;
		}
	}

	// ͳ�Ʋ���
	k = 0;
	for (i = int(num_flag); box[i].num_father >= 0; i = box[i].num_father)
	{
		k++;
	}
	j = k;
	// �������¼��
	for (i = int(num_flag); k > 0; i = box[i].num_father)
	{
		eat[num_eat + k].num_transverse = box[i].num_transverse;
		eat[num_eat + k].num_portrait = box[i].num_portrait;
		eat[num_eat + k].num_other = box[i].num_other;
		k--;
	}
	// ��������Ȳ�������
	num_eat += j;
}

// ��ʼ������
void Gary::initialization()
{
	int i, j;
	// ������ӳ�ʼ��
	srand((unsigned)time(NULL));
	// �Զ����������ʼ��
	num_start = 0;
	// ϵ����ʼ��
	j = 1;
	for (i = 0; i < 31; i++)
	{
		num_double[i] = j;
		j *= 2;
	}
	// ��Ϸģʽ��ʼ��
	num_mod = 0;
	// ������س�ʼ��
	// �ո����
	img_space = new IMAGE(100, 100);
	// ��ʼ����������
	SetWorkingImage(img_space);
	setbkcolor(RGB(73, 130, 120));
	cleardevice();
	// ����
	setfillcolor(RGB(112, 180, 167));
	solidroundrect(0 + 5, 0 + 5, 100 - 5, 100 - 5, 30, 30);
	SetWorkingImage();

	// ������
	img_transverse = new IMAGE(200, 100);
	// ��ʼ����������
	SetWorkingImage(img_transverse);
	setbkcolor(RGB(73, 130, 120));
	cleardevice();
	// ����
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

	// �ݿ����
	img_portrait = new IMAGE(100, 200);
	// ��ʼ����������
	SetWorkingImage(img_portrait);
	setbkcolor(RGB(73, 130, 120));
	cleardevice();
	// ����
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

	// С�����
	img_small = new IMAGE(100, 100);
	// ��ʼ����������
	SetWorkingImage(img_small);
	setbkcolor(RGB(73, 130, 120));
	cleardevice();
	// ����
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

	// ������
	img_big = new IMAGE(200, 200);
	// ��ʼ����������
	SetWorkingImage(img_big);
	setbkcolor(RGB(73, 130, 120));
	cleardevice();
	// ����
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
	// ����
	fillpolygon(pts, 6);
	pts[0].x = 100;	pts[0].y = 125 - 60;
	pts[1].x = 125;	pts[1].y = 100 - 60;
	pts[2].x = 150;	pts[2].y = 100 - 60;
	pts[3].x = 100;	pts[3].y = 150 - 60;
	pts[4].x = 50;	pts[4].y = 100 - 60;
	pts[5].x = 75;	pts[5].y = 100 - 60;
	// ����
	fillpolygon(pts, 6);
	SetWorkingImage();

	// ��ť��ʼ��
	for (i = 0; i < 12; i++)
	{
		box_button[i].posx1 = 458 + i % 2 * 70;
		box_button[i].posy1 = 40 + i / 2 * 100;
		box_button[i].posx2 = 508 + i % 2 * 70;
		box_button[i].posy2 = 90 + i / 2 * 100;
	}

	// ���̳�ʼ��
	create();

	// ���̳�ʼ��
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

	// ���Ƴ�ʼ
	draw_scene(0);

}

// ��Ϸ����
void Gary::game()
{
	int i, j, k;
	// ���ĸ�������
	i = (m.y - 25) / 102 * 4 + (m.x - 25) / 102;
	// �ǿո���
	if (pan[i] > 0)
	{
		// ���
		setfillcolor(WHITE);
		solidcircle(25 + 51 + i % 4 * 102, 25 + 51 + i / 4 * 102, 5);
		FlushBatchDraw();
		// ������������
		switch (pan[i])
		{
		case 5: {i = i - 1; break; }
		case 6: {i = i - 4; break; }
		case 7: {i = i - 5; break; }
		case 8: {i = i - 1; break; }
		case 9: {i = i - 4; break; }
		default:break;
		}
		// ���ƶ����ĸ��ո�����
		k = 0;
		while (k == 0)
		{
			// �����Ϣ
			if (peekmessage(&m, EM_MOUSE | EM_KEY))
			{
				// ��������ж�
				if (m.message == WM_LBUTTONDOWN)
				{
					// ���������̷�Χ
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
					// ���������̷�Χ
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
		// ����ո�ʱ��������
		if (k == 1)
		{
			switch (pan[i])
			{
				// ���
			case 1:
			{
					  // ��
					  if ((j == i - 3 || j == i - 4) && pan[i - 4] == 0 && pan[i - 3] == 0 && i / 4 > 0)
					  {
						  pan[i - 4] = 1;
						  pan[i + 4] = 0;
						  pan[i + 5] = 0;
					  }
					  // ��
					  else if ((j == i + 8 || j == i + 9) && pan[i + 8] == 0 && pan[i + 9] == 0 && i / 4 < 3)
					  {
						  pan[i + 4] = 1;
						  pan[i] = 0;
						  pan[i + 1] = 0;
					  }
					  // ��
					  else if ((j == i - 1 || j == i + 3) && pan[i - 1] == 0 && pan[i + 3] == 0 && i % 4 > 0)
					  {
						  pan[i - 1] = 1;
						  pan[i + 1] = 0;
						  pan[i + 5] = 0;
					  }
					  // ��
					  else if ((j == i + 2 || j == i + 6) && pan[i + 2] == 0 && pan[i + 6] == 0 && i % 4 < 2)
					  {
						  pan[i + 1] = 1;
						  pan[i] = 0;
						  pan[i + 4] = 0;
					  }
					  break;
			}
				// ���
			case 2:
			{
					  // ��
					  if ((j == i - 3 || j == i - 4) && pan[i - 4] == 0 && pan[i - 3] == 0 && i / 4 > 0)
					  {
						  pan[i - 4] = 2;
						  pan[i] = 0;
						  pan[i + 1] = 0;
					  }
					  // ��
					  else if ((j == i + 4 || j == i + 5) && pan[i + 4] == 0 && pan[i + 5] == 0 && i / 4 < 4)
					  {
						  pan[i + 4] = 2;
						  pan[i] = 0;
						  pan[i + 1] = 0;
					  }
					  // ��
					  else if (j == i - 1 && pan[i - 1] == 0 && i % 4 > 0)
					  {
						  pan[i - 1] = 2;
						  pan[i + 1] = 0;
					  }
					  // ��
					  else if (j == i + 2 && pan[i + 2] == 0 && i % 4 < 2)
					  {
						  pan[i + 1] = 2;
						  pan[i] = 0;
					  }
					  break;
			}
				// �ݸ�
			case 3:
			{
					  // ��
					  if (j == i - 4 && pan[i - 4] == 0 && i / 4 > 0)
					  {
						  pan[i - 4] = 3;
						  pan[i + 4] = 0;
					  }
					  // ��
					  else if (j == i + 8 && pan[i + 8] == 0 && i / 4 < 3)
					  {
						  pan[i + 4] = 3;
						  pan[i] = 0;
					  }
					  // ��
					  else if ((j == i - 1 || j == i + 3) && pan[i - 1] == 0 && pan[i + 3] == 0 && i % 4 > 0)
					  {
						  pan[i - 1] = 3;
						  pan[i] = 0;
						  pan[i + 4] = 0;
					  }
					  // ��
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
			// ���̱�׼��
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
		// ����
		// ��������
		setbkcolor(RGB(136, 192, 160));
		cleardevice();
		// ���̻���
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
			// ���ڻ���
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
		// ��ť����
		TCHAR s[25];
		setlinecolor(RGB(155, 195, 230));
		setfillcolor(RGB(80, 189, 222));
		settextcolor(RGB(230, 230, 230));
		settextstyle(30, 20, _T("Times New Roman"));
		setbkcolor(RGB(80, 189, 222));
		// ��׼���̰�ť
		for (i = 0; i < 12; i++)
		{
			fillroundrect(box_button[i].posx1, box_button[i].posy1, box_button[i].posx2, box_button[i].posy2, 20, 20);
			_stprintf_s(s, _T("%d"), i);
			outtextxy(box_button[i].posx1 + 13 - 12 * (i / 10), box_button[i].posy1 + 10, s);
		}
		// ������ť
		settextstyle(100, 100, _T("Webdings"));
		settextcolor(RGB(73, 130, 120));
		setbkmode(TRANSPARENT);
		outtextxy(102 - 50, 580 - 30, 0x34); // ���ţ����
		outtextxy(214 - 50, 580 - 30, 0x33); // ���ã��ָ���ʼ����
		outtextxy(326 - 50, 580 - 30, 0x71); // ˢ�£�������水ť
		// �ָ����
		setbkmode(OPAQUE);
		setbkmode(OPAQUE);
		settextcolor(RGB(230, 230, 230));
		settextstyle(30, 20, _T("����"));
		setbkcolor(RGB(136, 192, 160));
		outtextxy(102 - 50, 655, _T("���"));
		outtextxy(214 - 50, 655, _T("�ָ�"));
		outtextxy(326 - 50, 655, _T("ˢ��"));
		FlushBatchDraw();
		// �ɹ�����
		if (pan[13] == 1)
		{
			exit_move = 2;
		}
	}
}


// �������ӽǺ�������ȡ�û�����
void Gary::move()
{
	int k;
	exit_move = 0;
	while (exit_move == 0)
	{
		// �����Ϣ
		if (peekmessage(&m, EM_MOUSE | EM_KEY))
		{
			// ��������ж�
			if (m.message == WM_LBUTTONDOWN)
			{
				// ���������̷�Χ
				if (m.x > 20 && m.x < 433 && m.y>15 && m.y < 540)
				{
					// ��Ϸ����
					game();
				}
				// �������水ť
				else if (m.x > 458)
				{
					// �л�
					num_mod = (m.x - 458) / 70 + (m.y - 40) / 100 * 2;
					// ����
					create();
					// ����
					draw_scene(0);
				}
				// ��ʾ��ť
				else if (pow(double(m.x - 102), 2) + pow(double(m.y - 600), 2) < 2500)
				{
					// ��ʼ��
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
						// ���ƽ������
						for (k = 0; k <= num_eat; k++)
						{
							// ��������ֵ������
							draw_scene(k);
							Sleep(500);
						}
					}
				}
				// ���ð�ť
				else if (pow(double(m.x - 214), 2) + pow(double(m.y - 600), 2) < 2500)
				{
					// ��������ֵ������
					draw_scene(0);
					FlushBatchDraw();
				}
				// ˢ�°�ť
				else if (pow(double(m.x - 326), 2) + pow(double(m.y - 600), 2) < 2500)
				{
					// �л�
					num_mod = 12;
					// ����
					create();
					// ����
					draw_scene(0);
				}
				// ���������
				flushmessage();
			}
		}
	}
	// ������ʾ
	if (exit_move == 2)
	{
		MessageBox(hOut, _T("�ɹ��������ȷ����ˢ��"), _T("����С���ӵ�����"), MB_OK);
	}
	else if (exit_move == 1)
	{
		MessageBox(hOut, _T("�޽⣬���ȷ����ˢ��"), _T("����С���ӵ�����"), MB_OK);
	}
}

// ������
void Gary::carry()
{
	// ���ڶ���
	hOut = initgraph(600, 102 * 5 + 200);
	SetWindowText(hOut, _T("���ݵ�"));
	// ���̿���
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

// ������
int main(void)
{
	Gary G;
	G.carry();
	return 0;
}