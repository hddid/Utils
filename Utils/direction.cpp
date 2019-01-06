#include "direction.h"
/*
////class Draw_line
*/
inline int get_dis_x1x2(int x1, int y1, int x2, int y2)
{
	return (int)sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

//升序排列点

static int asc_sort_point(const void *a, const void *b)
{
	return (*(AB_point *)a).dis > (*(AB_point *)b).dis ? 1 : -1;
}

Draw_line::Draw_line(MapPoints snake_map_point[][1024])
{
	memset(line, 0, sizeof(line));
	memset(map, 0, sizeof(map));
	memset(&PA, 0, sizeof(AB_point));
	memset(&PB, 0, sizeof(AB_point));
	memset(&first_P, 0, sizeof(AB_point));

	int i = 0;
	for (i = 0; i<1024; ++i) {
		memcpy(&map[i], &snake_map_point[i], 1024 * sizeof(uint32_t));
	}
}

Draw_line::~Draw_line()
{

}


int Draw_line::run_this_line(int x1, int y1, int x2, int y2, int mode)
{
	PA.x = x1;
	PA.y = y1;
	PB.x = x2;
	PB.y = y2;

	line[0].x = x1;
	line[0].y = y1;
	line[0].dis = 0;
	line_count = 1;
	int i = 0;
	cut_line(x1, y1, x2, y2);
	qsort(line, line_count, sizeof(AB_point), asc_sort_point);
	if (mode == 1)
	{
		for (i = 0; i<line_count; ++i) {
			if ((map[line[i].y][line[i].x].status & 0x0F) == 0x03) {//高4位有计数则遇到了障碍点
				first_line_count = i + 1;
				first_P.x = line[i - 1].x;
				first_P.y = line[i - 1].y;
				first_P.dis = line[i - 1].dis;
				break;
			}
		}
	}
	else if (mode == 2)
	{
		for (i = 0; i<line_count; ++i)
		{
			//if(i>1){// it is important can changed
			if (i>2)
			{
				if ((map[line[i].y][line[i].x].status & 0x0F) == 0x0E || \
					(map[line[i].y - 1][line[i].x].status & 0x0F) == 0x0E || \
					(map[line[i].y - 1][line[i].x + 1].status & 0x0F) == 0x0E || \
					(map[line[i].y][line[i].x + 1].status & 0x0F) == 0x0E || \
					(map[line[i].y + 1][line[i].x + 1].status & 0x0F) == 0x0E || \
					(map[line[i].y + 1][line[i].x].status & 0x0F) == 0x0E || \
					(map[line[i].y + 1][line[i].x - 1].status & 0x0F) == 0x0E || \
					(map[line[i].y][line[i].x - 1].status & 0x0F) == 0x0E)
				{//撞到了辅助线
				 //printf("line_count=%d  i=%d\n",line_count,i);
					return 1;
				}
			}
		}
	}

	return 0;
}
int Draw_line::cut_line(int Ax, int Ay, int Bx, int By)
{
	if (Ax - Bx>1 || Ax - Bx<-1 || Ay - By>1 || Ay - By<-1) {
		//(map[(By+Ay)/2][(Bx+Ax)/2]&=0xF0)|=0x0E;
		line[line_count].x = (Bx + Ax) / 2;
		line[line_count].y = (By + Ay) / 2;
		line[line_count].dis = get_dis_x1x2(PA.x, PA.y, (Bx + Ax) / 2, (By + Ay) / 2);
		++line_count;
		cut_line(Ax, Ay, (Bx + Ax) / 2, (By + Ay) / 2);
		cut_line((Bx + Ax) / 2, (By + Ay) / 2, Bx, By);
	}
	return 0;
}




int Draw_line::get_line(AB_point* tmp_line)
{
	int i = 0;
	for (i = 0; i<line_count; ++i) {
		memcpy(&tmp_line[i], &line[i], sizeof(AB_point));
	}
	return line_count;
}


int Draw_line::get_first_line(AB_point* tmp_line)
{
	int i = 0;
	for (i = 0; i<first_line_count; ++i)
	{
		memcpy(&tmp_line[i], &line[i], sizeof(AB_point));
	}
	return first_line_count;
}

int Draw_line::get_first_P(AB_point* p)
{
	p->x = first_P.x;
	p->y = first_P.y;
	p->dis = first_P.dis;

	return 0;
}

/*
////class Draw_direction
*/


char Draw_direction::left_direction_buf[256] = \
{
	//0		1	2	3	4	5	6	7
	//8		9	10	11	12	13	14	15
	//16	17	18	19	20	21	22	23
	//24	25	26	27	28	29	30	31
	0, 7, 6, 6, 5, 5, 5, 5, \
		4, 4, 0, 0, 4, 4, 4, 4, \
		3, 0, 0, 0, 3, 0, 3, 0, \
		3, 0, 0, 0, 3, 0, 3, 3, \
		//32	33	34	35	36	37	38	39
		//40	41	42	43	44	45	46	47
		//48	49	50	51	52	53	54	55
		//56	57	58	59	60	61	62	63
		2, 0, 0, 0, 0, 0, 0, 0, \
		2, 0, 0, 0, 0, 0, 0, 0, \
		2, 0, 0, 0, 2, 0, 0, 0, \
		2, 0, 0, 0, 2, 0, 2, 0, \
		//64	65	66	67	68	69	70	71
		//72	73	74	75	76	77	78	79
		//80	81	82	83	84	85	86	87
		//88	89	90	91	92	93	94	95
		1, 7, 0, 6, 0, 0, 0, 0, \
		0, 0, 0, 0, 0, 0, 0, 0, \
		1, 0, 0, 0, 0, 0, 0, 0, \
		1, 0, 0, 0, 0, 0, 0, 0, \

		//96	97	98	99	100	101	102	103
		//104	105	106	107	108	109	110	111
		//112	113	114	115	116	117	118	119
		//120	121	122	123	124	125	126	127

		1, 7, 0, 0, 0, 0, 0, 0, \
		0, 0, 0, 0, 0, 0, 0, 0, \
		1, 0, 0, 0, 0, 0, 0, 0, \
		1, 0, 0, 0, 1, 0, 0, 0, \

		//128	129	130	131	132	133	134	135
		//136	137	138	139	140	141	142	143
		//144	145	146	147	148	149	150	151
		//152	153	154	155	156	157	158	159

		8, 7, 6, 6, 0, 5, 0, 5, \
		0, 0, 0, 0, 0, 0, 0, 4, \
		0, 0, 0, 0, 0, 0, 0, 0, \
		0, 0, 0, 0, 0, 0, 0, 0, \

		//160	161	162	163	164	165	166	167
		//168	169	170	171	172	173	174	175
		//176	177	178	179	180	181	182	183
		//184	185	186	187	188	189	190	191

		8, 0, 0, 0, 0, 0, 0, 0, \
		0, 0, 0, 0, 0, 0, 0, 0, \
		0, 0, 0, 0, 0, 0, 0, 0, \
		0, 0, 0, 0, 0, 0, 0, 0, \

		//		192	193	194	195	196	197	198	199
		//		200	201	202	203	204	205	206	207
		//		208	209	210	211	212	213	214	215
		//		216	217	218	219	220	221	222	223
		8, 7, 0, 6, 0, 0, 0, 5, \
		0, 0, 0, 0, 0, 0, 0, 0, \
		8, 0, 0, 0, 0, 0, 0, 0, \
		0, 0, 0, 0, 0, 0, 0, 0, \



		//224	225	226	227	228	229	230	231
		//232	233	234	235	236	237	238	239
		//240	241	242	243	244	245	246	247
		//248	249	250	251	252	253	254	255

		8, 7, 0, 6, 0, 0, 0, 0, \
		0, 0, 0, 0, 0, 0, 0, 0, \
		8, 7, 0, 0, 0, 0, 0, 0, \
		8, 0, 0, 0, 0, 0, 0, 0 \
};
char Draw_direction::right_direction_buf[256] = \
{
	//0		1	2	3	4	5	6	7
	//8		9	10	11	12	13	14	15
	//16	17	18	19	20	21	22	23
	//24	25	26	27	28	29	30	31
	0, 1, 8, 1, 7, 1, 8, 1, \
		6, 8, 0, 0, 7, 1, 8, 1, \
		5, 0, 0, 0, 7, 0, 8, 0, \
		6, 0, 0, 0, 7, 0, 8, 1, \
		//32	33	34	35	36	37	38	39
		//40	41	42	43	44	45	46	47
		//48	49	50	51	52	53	54	55
		//56	57	58	59	60	61	62	63

		4, 0, 0, 0, 0, 0, 0, 0, \
		6, 0, 0, 0, 0, 0, 0, 0, \
		5, 0, 0, 0, 7, 0, 0, 0, \
		6, 0, 0, 0, 7, 0, 8, 0, \

		//64	65	66	67	68	69	70	71
		//72	73	74	75	76	77	78	79
		//80	81	82	83	84	85	86	87
		//88	89	90	91	92	93	94	95
		3, 3, 0, 3, 0, 0, 0, 0, \
		0, 0, 0, 0, 0, 0, 0, 0, \
		5, 0, 0, 0, 0, 0, 0, 0, \
		6, 0, 0, 0, 0, 0, 0, 0, \


		//96	97	98	99	100	101	102	103
		//104	105	106	107	108	109	110	111
		//112	113	114	115	116	117	118	119
		//120	121	122	123	124	125	126	127

		4, 4, 0, 0, 0, 0, 0, 0, \
		0, 0, 0, 0, 0, 0, 0, 0, \
		5, 0, 0, 0, 0, 0, 0, 0, \
		6, 0, 0, 0, 7, 0, 0, 0, \

		//128	129	130	131	132	133	134	135
		//136	137	138	139	140	141	142	143
		//144	145	146	147	148	149	150	151
		//152	153	154	155	156	157	158	159

		2, 2, 2, 2, 0, 2, 0, 2, \
		0, 0, 0, 0, 0, 0, 0, 2, \
		0, 0, 0, 0, 0, 0, 0, 0, \
		0, 0, 0, 0, 0, 0, 0, 0, \

		//160	161	162	163	164	165	166	167
		//168	169	170	171	172	173	174	175
		//176	177	178	179	180	181	182	183
		//184	185	186	187	188	189	190	191



		4, 0, 0, 0, 0, 0, 0, 0, \
		0, 0, 0, 0, 0, 0, 0, 0, \
		0, 0, 0, 0, 0, 0, 0, 0, \
		0, 0, 0, 0, 0, 0, 0, 0, \

		//		192	193	194	195	196	197	198	199
		//		200	201	202	203	204	205	206	207
		//		208	209	210	211	212	213	214	215
		//		216	217	218	219	220	221	222	223
		3, 3, 0, 3, 0, 0, 0, 3, \
		0, 0, 0, 0, 0, 0, 0, 0, \
		5, 0, 0, 0, 0, 0, 0, 0, \
		0, 0, 0, 0, 0, 0, 0, 0, \



		//224	225	226	227	228	229	230	231
		//232	233	234	235	236	237	238	239
		//240	241	242	243	244	245	246	247
		//248	249	250	251	252	253	254	255

		4, 4, 0, 4, 0, 0, 0, 0, \
		0, 0, 0, 0, 0, 0, 0, 0, \
		5, 5, 0, 0, 0, 0, 0, 0, \
		6, 0, 0, 0, 0, 0, 0, 0 \
};


Draw_direction::Draw_direction(MapPoints snake_map_point[][1024])
{
	memset(line_circle, 0, sizeof(line_circle));
	memset(line_left, 0, sizeof(line_left));
	memset(line_right, 0, sizeof(line_right));
	memset(map, 0, sizeof(map));
	memset(&start_P, 0, sizeof(AB_point));
	memset(&end_P, 0, sizeof(AB_point));
	memset(&turn_P, 0, sizeof(AB_point));

	int i = 0;
	for (i = 0; i<1024; ++i)
	{
		memcpy(&map[i], &snake_map_point[i], 1024 * sizeof(uint32_t));
	}

}
Draw_direction::~Draw_direction()
{

}

int Draw_direction::run_this_direction(int x1, int y1, int x2, int y2)
{
	start_P.x = x1;
	start_P.y = y1;
	end_P.x = x2;
	end_P.y = y2;
	draw_circle();
	turn_left_line();
	turn_right_line();

	return 0;
}

int Draw_direction::small_turn(int direction)
{
	int turn_val = 0;
	if (turn_P.y>10 && turn_P.y<1012 && turn_P.x>10 && turn_P.x<1012)
	{
		if ((map[turn_P.y - 1][turn_P.x - 1].status & 0x0F) == 0x03)
		{
			turn_val += 128;
		}
		if ((map[turn_P.y - 1][turn_P.x].status & 0x0F) == 0x03)
		{
			turn_val += 64;
		}
		if ((map[turn_P.y - 1][turn_P.x + 1].status & 0x0F) == 0x03)
		{
			turn_val += 32;
		}
		if ((map[turn_P.y][turn_P.x + 1].status & 0x0F) == 0x03)
		{
			turn_val += 16;
		}
		if ((map[turn_P.y + 1][turn_P.x + 1].status & 0x0F) == 0x03)
		{
			turn_val += 8;
		}
		if ((map[turn_P.y + 1][turn_P.x].status & 0x0F) == 0x03)
		{
			turn_val += 4;
		}
		if ((map[turn_P.y + 1][turn_P.x - 1].status & 0x0F) == 0x03)
		{
			turn_val += 2;
		}
		if ((map[turn_P.y][turn_P.x - 1].status & 0x0F) == 0x03)
		{
			turn_val += 1;
		}
		if (direction == 0)
		{//沿着障碍画一圈（向左）


			if (1 == left_direction_buf[turn_val])
			{
				--turn_P.x; --turn_P.y;
			}
			else if (2 == left_direction_buf[turn_val])
			{
				--turn_P.y;
			}
			else if (3 == left_direction_buf[turn_val])
			{
				++turn_P.x; --turn_P.y;
			}
			else if (4 == left_direction_buf[turn_val])
			{
				++turn_P.x;
			}
			else if (5 == left_direction_buf[turn_val])
			{
				++turn_P.x; ++turn_P.y;
			}
			else if (6 == left_direction_buf[turn_val])
			{
				++turn_P.y;
			}
			else if (7 == left_direction_buf[turn_val])
			{
				--turn_P.x; ++turn_P.y;
			}
			else if (8 == left_direction_buf[turn_val])
			{
				--turn_P.x;
			}
			else if (0 == left_direction_buf[turn_val])
			{
				printf("it is end buf_val=%d val=%d px=%d py=%d\n", turn_val, left_direction_buf[turn_val], turn_P.x, turn_P.y);
				return 0;
			}

			//printf("circle line2:turn x=%d y=%d\n",line_circle[0].x,line_circle[0].y);

			(map[turn_P.y][turn_P.x].status &= 0xF0) |= 0x0E;//标记辅助线

			turn_P.dis = get_dis_x1x2(turn_P.x, turn_P.y, line_circle[0].x, line_circle[0].y);

			//printf("circle line2:turn_P x=%d y=%d  dis=%d\n",turn_P.x,turn_P.y,turn_P.dis);

			memcpy(&line_circle[circle_count], &turn_P, sizeof(AB_point));

			//printf("circle_count=%d  dis=%d x=%d y=%d\n",circle_count,line_circle[circle_count].dis,line_circle[circle_count].x,line_circle[circle_count].y);

			if (circle_count>5)
			{

				if (line_circle[circle_count].x == line_circle[0].x&&line_circle[circle_count].y == line_circle[0].y)
				{
					printf("A-B-circle is good\n");
					circle_flag = 1;
					return 2;
				}
				if (circle_count>1999)
				{
					printf("A-B-circle is out\n");
					return 2;
				}
			}
			++circle_count;

			return 1;

		}
		if (direction == 1)
		{
			//printf("buf_val=%d val=%d\n",turn_val,left_direction_buf[turn_val]);
			//printf("26-31  = %d %d %d %d %d\n",left_direction_buf[24],left_direction_buf[25],left_direction_buf[26],left_direction_buf[27],left_direction_buf[28]);
			if (1 == left_direction_buf[turn_val])
			{
				--turn_P.x; --turn_P.y;
			}
			else if (2 == left_direction_buf[turn_val])
			{
				--turn_P.y;
			}
			else if (3 == left_direction_buf[turn_val])
			{
				++turn_P.x; --turn_P.y;
			}
			else if (4 == left_direction_buf[turn_val])
			{
				++turn_P.x;
			}
			else if (5 == left_direction_buf[turn_val])
			{
				++turn_P.x; ++turn_P.y;
			}
			else if (6 == left_direction_buf[turn_val])
			{
				++turn_P.y;
			}
			else if (7 == left_direction_buf[turn_val])
			{
				--turn_P.x; ++turn_P.y;
			}
			else if (8 == left_direction_buf[turn_val])
			{
				--turn_P.x;
			}
			else if (0 == left_direction_buf[turn_val])
			{
				printf("it is end buf_val=%d val=%d px=%d py=%d\n", turn_val, left_direction_buf[turn_val], turn_P.x, turn_P.y);
				return 0;
			}
			memcpy(&line_left[left_count], &turn_P, sizeof(AB_point));

			if (left_count>8)
			{
				/*
				if((map[turn_P.y-1][turn_P.x-1].status&0x0F)==0x0E||\
				(map[turn_P.y-1][turn_P.x].status&0x0F)==0x0E||\
				(map[turn_P.y-1][turn_P.x+1].status&0x0F)==0x0E||\
				(map[turn_P.y][turn_P.x+1].status&0x0F)==0x0E||\
				(map[turn_P.y+1][turn_P.x+1].status&0x0F)==0x0E||\
				(map[turn_P.y+1][turn_P.x].status&0x0F)==0x0E||\
				(map[turn_P.y+1][turn_P.x-1].status&0x0F)==0x0E||\
				(map[turn_P.y][turn_P.x-1].status&0x0F)==0x0E)*/
				if (left_count>100)
				{
					//printf("A-B is good\n");
					return 2;
				}
			}
			++left_count;

			return 1;

		}
		if (direction == 2)
		{
			//printf("buf_val=%d val=%d\n",turn_val,right_direction_buf[turn_val]);
			if (1 == right_direction_buf[turn_val])
			{
				--turn_P.x; --turn_P.y;
			}
			else if (2 == right_direction_buf[turn_val])
			{
				--turn_P.y;
			}
			else if (3 == right_direction_buf[turn_val])
			{
				++turn_P.x; --turn_P.y;
			}
			else if (4 == right_direction_buf[turn_val])
			{
				++turn_P.x;
			}
			else if (5 == right_direction_buf[turn_val])
			{
				++turn_P.x; ++turn_P.y;
			}
			else if (6 == right_direction_buf[turn_val])
			{
				++turn_P.y;
			}
			else if (7 == right_direction_buf[turn_val])
			{
				--turn_P.x; ++turn_P.y;
			}
			else if (8 == right_direction_buf[turn_val])
			{
				--turn_P.x;
			}
			else if (0 == right_direction_buf[turn_val])
			{
				printf("it is end buf_val=%d val=%d px=%d py=%d\n", turn_val, right_direction_buf[turn_val], turn_P.x, turn_P.y);
				return 0;
			}
			memcpy(&line_right[right_count], &turn_P, sizeof(AB_point));
			++right_count;

			if (right_count>5)
			{
				if ((map[turn_P.y - 1][turn_P.x - 1].status & 0x0F) == 0x0E || \
					(map[turn_P.y - 1][turn_P.x].status & 0x0F) == 0x0E || \
					(map[turn_P.y - 1][turn_P.x + 1].status & 0x0F) == 0x0E || \
					(map[turn_P.y][turn_P.x + 1].status & 0x0F) == 0x0E || \
					(map[turn_P.y + 1][turn_P.x + 1].status & 0x0F) == 0x0E || \
					(map[turn_P.y + 1][turn_P.x].status & 0x0F) == 0x0E || \
					(map[turn_P.y + 1][turn_P.x - 1].status & 0x0F) == 0x0E || \
					(map[turn_P.y][turn_P.x - 1].status & 0x0F) == 0x0E)
				{

					//printf("A-B is good\n");
					return 2;
				}
			}
			return 1;

		}

	}
	printf("out the mapx=%d y=%d rcount=%d lcount=%d\n", turn_P.x, turn_P.y, right_count, left_count);
	return 0;
}

int Draw_direction::draw_circle()
{
	circle_flag = 0;
	memcpy(&line_circle[0], &start_P, sizeof(AB_point));
	memcpy(&turn_P, &start_P, sizeof(AB_point));
	//printf("circle:start x=%d y=%d\n",start_P.x,start_P.y);
	//printf("circle:turn x=%d y=%d\n",turn_P.x,turn_P.y);
	//printf("circle line:turn x=%d y=%d\n",line_circle[0].x,line_circle[0].y);
	(map[start_P.y][start_P.x].status &= 0xF0) |= 0x0E;
	++circle_count;
	while (1)
	{
		int ret = small_turn(0);
		if (0 == ret || 2 == ret)
		{
			break;
		}

	}
	return 0;
}

int connect_line(AB_point* P1, AB_point* P2)
{
	if (P1->x - P2->x>1 || P1->x - P2->x<-1 || P1->y - P2->y>1 || P1->y - P2->y<-1)
	{
		//(map[(By+Ay)/2][(Bx+Ax)/2]&=0xF0)|=0x0E;
		//		line[line_count].x=(Bx+Ax)/2;
		//		line[line_count].y=(By+Ay)/2;
		//		line[line_count].dis=get_dis_x1x2(PA.x,PA.y,(Bx+Ax)/2,(By+Ay)/2);
		//		++line_count;
		//		cut_line(Ax,Ay,(Bx+Ax)/2,(By+Ay)/2);
		//		cut_line((Bx+Ax)/2,(By+Ay)/2,Bx,By);	
	}
	return 0;
}

int Draw_direction::cut_circle(AB_point* P1, AB_point* P2)
{
	int t_x = P2->x - P1->x;
	int t_y = P2->y - P1->y;
	//int i=0;
	AB_point tmp_P;
	memcpy(&tmp_P, P2, sizeof(AB_point));

	if (t_x == 1 && t_y == 1)
	{
		while (1)
		{
			++tmp_P.x; ++tmp_P.y;
			if ((map[tmp_P.y][tmp_P.x].status & 0x0F) == 0x0E)
			{

			}
		}
	}
	return 0;
}

int Draw_direction::turn_left_line()
{
	memcpy(&line_left[0], &start_P, sizeof(AB_point));
	left_count = 1;
	AB_point tmp_line[2000];
	memset(tmp_line, 0, sizeof(tmp_line));
	Draw_line *goto_end = new Draw_line(map);
	int i = 0;
	if (circle_flag)
	{
		while (1)
		{
			memcpy(&line_left[left_count], &line_circle[left_count], sizeof(AB_point));
			if (0 == goto_end->run_this_line(line_circle[left_count].x, line_circle[left_count].y, end_P.x, end_P.y, 2))
			{
				for (i = 0; i<goto_end->get_line(tmp_line); ++i)
				{
					++left_count;
					memcpy(&line_left[left_count], &tmp_line[i + 1], sizeof(AB_point));
				}
				//printf("goto end ok\n\n");
				break;
			}


			if (++left_count>1999)
			{
				printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nleft_count>1999 is bad\ngoto_end is bad\ngoto_end is bad\ngoto_end is bad\ngoto_end is bad\n\n\n\n\n");
				break;
			}
		}
	}
	else
	{
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\ncircle_flag=0 is bad\ncircle is bad\ncircle is bad\ncircle is bad\ncircle is bad\n\n\n\n\n");
	}
	delete(goto_end);
	return 0;
}

int Draw_direction::turn_right_line()
{

	//	memcpy(&line_right[0],&start_P,sizeof(AB_point));
	//	memcpy(&turn_P,&start_P,sizeof(AB_point));
	//	++right_count;
	//	while(1){
	//		int ret=small_turn(2);
	//		if(0==ret||2==ret){
	//			break;
	//		}	
	//		
	//	}

	memcpy(&line_right[0], &start_P, sizeof(AB_point));
	right_count = 1;
	AB_point tmp_line[2000];
	memset(tmp_line, 0, sizeof(tmp_line));
	Draw_line *goto_end = new Draw_line(map);

	int i = 0;
	int ii = circle_count - 1;
	if (circle_flag)
	{
		while (1)
		{
			//memcpy(&turn_P,&line_circle[right_count-1],sizeof(AB_point));
			//printf("ii=%d\n",ii);

			memcpy(&line_right[right_count], &line_circle[--ii], sizeof(AB_point));
			if (0 == goto_end->run_this_line(line_right[right_count].x, line_right[right_count].y, end_P.x, end_P.y, 2))
			{
				for (i = 0; i<goto_end->get_line(tmp_line); ++i)
				{
					++right_count;
					memcpy(&line_right[right_count], &tmp_line[i + 1], sizeof(AB_point));
				}
				//printf("goto end ok\n\n");
				break;
			}
			if (++right_count>1999)
			{
				printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\ncircle is bad\ngoto_end is bad\ngoto_end is bad\ngoto_end is bad\ngoto_end is bad\n\n\n\n\n");
				break;
			}
		}
	}
	else
	{
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\ncircle is bad\ncircle is bad\ncircle is bad\ncircle is bad\ncircle is bad\n\n\n\n\n");
	}
	delete(goto_end);
	return 0;
}


int Draw_direction::get_line_circle(AB_point* tmp_line)
{
	int i = 0;
	for (i = 0; i<circle_count + 1; ++i)
	{
		memcpy(&tmp_line[i], &line_circle[i], sizeof(AB_point));
	}
	return circle_count + 1;
}


int Draw_direction::get_line_right(AB_point* tmp_line)
{
	int i = 0;
	for (i = 0; i<left_count; ++i)
	{
		memcpy(&tmp_line[i], &line_left[i], sizeof(AB_point));
	}
	return left_count;
}

int Draw_direction::get_line_left(AB_point* tmp_line)
{
	int i = 0;
	for (i = 0; i<right_count; ++i)
	{
		memcpy(&tmp_line[i], &line_right[i], sizeof(AB_point));
	}
	return right_count;
}
int Draw_direction::get_left_count()
{
	return right_count;
}
int Draw_direction::get_right_count()
{
	return left_count;
}


