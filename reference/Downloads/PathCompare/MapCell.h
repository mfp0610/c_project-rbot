
#ifndef _Map_Cell_H
#define _Map_Cell_H

#define CELL_NUM		(50)
#define BLANK_WIDTH		(30)
#define BLANK_HEIGHT	(30)

enum CellState
{
	cell_state_none,
	cell_state_balk,
	cell_state_origin,
	cell_state_target,
	cell_state_close,
	cell_state_open,
	cell_state_path,
	cell_state_check,
	cell_state_next,
};

enum enBranchDirect
{
	branch_dir_none,
	branch_dir_left,
	branch_dir_right,
	branch_dir_count,
};

class Cell
{
public:
	Cell() : x(0),y(0),s(cell_state_none),g(0),h(0),px(-1),py(-1),branch(0),dir(-1),reel(0),angle(0)
	{
	}

	Cell(int nx, int ny) : x(nx),y(ny),s(cell_state_none),g(0),h(0),px(-1),py(-1),branch(0),dir(-1),reel(0),angle(0)
	{
	}
	
	void Init(int nx, int ny, int ns = cell_state_none, int ng = 0, int nh = 0)
	{
		x = nx;
		y = ny;
		s = ns;
		g = ng;
		h = nh;
		branch = 0;
		dir = -1;
		reel = 0;
		angle = 0;
	}
	
	void Reset()
	{
		s = cell_state_none;
		g = 0;
		h = 0;
		px = -1;
		py = -1;
		branch = 0;
		dir = -1;
		reel = 0;
		angle = 0;
	}
	
	bool operator< (Cell o)
	{
		if ((g + h) == (o.g + o.h))
			if (dir < o.dir)
				return true;
			else
				return false;
		else if ((g + h) < (o.g + o.h))
			return true;
		else
			return false;
	}
	
public:
	int			s;
	int			x;
	int			y;
	int			g;						// 实际值
	int			h;						// 期望值
	int			px;						// Prev Point
	int			py;						// Prev Point
	int			branch;					// Stick Direction
	int			dir;					// Stick Direction
	int			reel;					// 卷曲度
	int			angle;

};

#endif