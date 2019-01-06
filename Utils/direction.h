
#ifndef ZHT_UTILS_DIRECTION_H
#define ZHT_UTILS_DIRECTION_H

#ifndef WIN32
#include <unistd.h>
#endif
#include <string.h>
#include <iostream>
#include <math.h>

typedef struct AB_point
{
	int x;
	int y;
	int dis;

}AB_point;
typedef struct map_point
{
	uint8_t status;
	uint8_t quality;
	uint8_t spare1;
	uint8_t spare2;
}MapPoints;
//mode:		1		
//			2			
class Draw_line
{
public:
	Draw_line(MapPoints snake_map_point[][1024]);
	~Draw_line();
	int run_this_line(int x1, int y1, int x2, int y2, int mode);
	int get_first_P(AB_point* p);
	int get_line(AB_point* tmp_line);
	int get_first_line(AB_point* tmp_line);

private:

	AB_point PA;
	AB_point PB;
	AB_point first_P;
	AB_point line[2000];
	MapPoints map[1024][1024];
	int line_count = 0;
	int first_line_count = 0;
	int cut_line(int Ax, int Ay, int Bx, int By);

};


class Draw_direction
{
public:
	Draw_direction(MapPoints snake_map_point[][1024]);
	~Draw_direction();
	int run_this_direction(int x1, int y1, int x2, int y2);
	int get_line_circle(AB_point* tmp_line);
	int get_line_left(AB_point* tmp_line);
	int get_line_right(AB_point* tmp_line);
	int get_left_count();
	int get_right_count();
private:
	static char left_direction_buf[256];
	static char right_direction_buf[256];
	AB_point start_P;
	AB_point end_P;
	AB_point turn_P;
	AB_point line_circle[2000];
	AB_point line_left[2000];
	AB_point line_right[2000];
	MapPoints map[1024][1024];
	int circle_count = 0;
	int left_count = 0;
	int right_count = 0;
	int circle_flag = 0;
	int draw_circle();
	int turn_left_line();
	int turn_right_line();
	int small_turn(int direction);
	int cut_circle(AB_point* P1, AB_point* P2);
};






#endif//ZHT_UTILS_DIRECTION_H