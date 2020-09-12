// PathThinkerDoc.cpp : implementation of the CPathThinkerDoc class
//

#include "stdafx.h"
#include "PathThinker.h"

#include "PathThinkerDoc.h"
#include "MapUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_DIRECTION	4

#define FIND_MODE 3 // 1 a*, 2 a* direct, 3 b*
#define FIND_MINIST 5

#define SLEEP_MOMENT 1

struct tagAround
{
	int x, y;
};

tagAround Around[MAX_DIRECTION] = {
	{0, 1}, 
	{-1, 0}, 
	{0, -1}, 
	{1, 0},
};

int BranchAround[branch_dir_count][MAX_DIRECTION] = {
	{ 0, 1, 2, 3, },
	{ 0, 3, 2, 1, },
	{ 0, 1, 2, 3, },
};

UINT ThreadFunc(LPVOID lpParam)
{
	CPathThinkerDoc* pDoc = (CPathThinkerDoc*)lpParam;
	ASSERT_VALID(pDoc);
//	pDoc->FindPath_AStar();
// 	pDoc->FindPath_AStar_Direct();
	pDoc->FindPath_BStar();
// 	pDoc->FindPath();
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CPathThinkerDoc

IMPLEMENT_DYNCREATE(CPathThinkerDoc, CDocument)

BEGIN_MESSAGE_MAP(CPathThinkerDoc, CDocument)
	//{{AFX_MSG_MAP(CPathThinkerDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPathThinkerDoc construction/destruction

CPathThinkerDoc::CPathThinkerDoc()
{
	// TODO: add one-time construction code here

}

CPathThinkerDoc::~CPathThinkerDoc()
{
}

BOOL CPathThinkerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPathThinkerDoc serialization

void CPathThinkerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << Origin.s << Origin.x << Origin.y;
		ar << Target.s << Target.x << Target.y;
		for (int i = 0; i < CELL_NUM; i++)
		{
			for (int j = 0; j < CELL_NUM; j++)
			{
				ar << Cells[i][j].s;
			}
		}
	}
	else
	{
		// TODO: add loading code here
		ar >> Origin.s >> Origin.x >> Origin.y;
		ar >> Target.s >> Target.x >> Target.y;
		for (int i = 0; i < CELL_NUM; i++)
		{
			for (int j = 0; j < CELL_NUM; j++)
			{
				Cells[i][j].Init(j, i);
				ar >> Cells[i][j].s;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPathThinkerDoc diagnostics

#ifdef _DEBUG
void CPathThinkerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPathThinkerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPathThinkerDoc commands

void CPathThinkerDoc::ResetCells()
{
	for (int i = 0; i < CELL_NUM; i++)
	{
		for (int j = 0; j < CELL_NUM; j++)
		{
			Cells[i][j].Reset();
		}
	}
	Origin.Reset();
	Target.Reset();
}

void CPathThinkerDoc::ClearPath()
{
	for (int i = 0; i < CELL_NUM; i++)
	{
		for (int j = 0; j < CELL_NUM; j++)
		{
			if (Cells[i][j].s != cell_state_balk 
				&& Cells[i][j].s != cell_state_origin 
				&& Cells[i][j].s != cell_state_target)
			{
				Cells[i][j].Reset();
			}
			else
			{
				Cells[i][j].Init(j, i, Cells[i][j].s);
			}
		}
	}
	Origin.Init(Origin.x, Origin.y, Origin.s);
	Target.Init(Target.x, Target.y, Target.s);
}

void CPathThinkerDoc::StartFind(void)
{
	AfxBeginThread(ThreadFunc, this);
	UpdateAllViews(NULL);
}

bool CPathThinkerDoc::FindPath_AStar()
{
	std::list<Cell> opened;
	
	Cell& firstCell = Cells[Origin.y][Origin.x];
	firstCell.h = abs(Target.x - firstCell.x) + abs(Target.y - firstCell.y);
	
	opened.push_back(firstCell);
	opened.sort();
	
	std::list<Cell>::iterator pfirst = opened.begin();
	while (pfirst != opened.end())
	{
		Cell& currentTemp = *pfirst;
		Cell& currentCell = Cells[currentTemp.y][currentTemp.x];
		if (currentCell.s != cell_state_origin)
		{
			currentCell.s = cell_state_check;
		}
		for (int i = 0; i < MAX_DIRECTION; i++)
		{
			int nextX = currentCell.x + Around[i].x;
			int nextY = currentCell.y + Around[i].y;
			if (nextY < 0 || nextY >= CELL_NUM || nextX < 0 || nextX >= CELL_NUM)
			{
				Cells[currentCell.y][currentCell.x].s = cell_state_close;
				continue;
			}
			
			Cell& nextCell = Cells[nextY][nextX];
			if (nextCell.x == Target.x && nextCell.y == Target.y)
			{
				nextCell.px = currentCell.x;
				nextCell.py = currentCell.y;
				nextCell.g = currentCell.g + 1;
				
				nextCell.h = 0;
				
				BuildPath();
				UpdateView();
				return true;
			}
			
			if (nextCell.s == cell_state_none
				|| (nextCell.s == cell_state_close && (currentCell.g + 1) < nextCell.g)
				|| (nextCell.s == cell_state_open && (currentCell.g + 1) < nextCell.g))
			{
				nextCell.s = cell_state_next;
				UpdateView();
				SleepMoment();
				nextCell.px = currentCell.x;
				nextCell.py = currentCell.y;
				
				nextCell.g = currentCell.g + 1;
				
				nextCell.h = (abs(Target.x - nextCell.x) + abs(Target.y - nextCell.y));
				
				nextCell.s = cell_state_open;
				opened.push_back(nextCell);
			}			
		}
		if (currentCell.s != cell_state_origin)
		{
			currentCell.s = cell_state_close;
		}
		opened.erase(pfirst);
		opened.sort();
		pfirst = opened.begin();
	}
	
	return false;	
}

bool CPathThinkerDoc::FindPath_AStar_Direct()
{
	std::list<Cell> opened;
	
	Cell& firstCell = Cells[Origin.y][Origin.x];
	firstCell.h = abs(Target.x - firstCell.x) + abs(Target.y - firstCell.y);
	
	opened.push_back(firstCell);
	opened.sort();
	
	std::list<Cell>::iterator pfirst = opened.begin();
	while (pfirst != opened.end())
	{
		Cell& currentTemp = *pfirst;
		Cell& currentCell = Cells[currentTemp.y][currentTemp.x];
		if (currentCell.s != cell_state_origin)
		{
			currentCell.s = cell_state_check;
		}
		for (int i = 0; i < MAX_DIRECTION; i++)
		{
			int nextX = currentCell.x + Around[i].x;
			int nextY = currentCell.y + Around[i].y;
			if (nextY < 0 || nextY >= CELL_NUM || nextX < 0 || nextX >= CELL_NUM)
			{
				Cells[currentCell.y][currentCell.x].s = cell_state_close;
				continue;
			}
			
			Cell& nextCell = Cells[nextY][nextX];
			if (nextCell.x == Target.x && nextCell.y == Target.y)
			{
				nextCell.px = currentCell.x;
				nextCell.py = currentCell.y;
				nextCell.g = currentCell.g + 1;
				
				nextCell.h = 0;
				
				BuildPath();
				UpdateView();
				return true;
			}
			
			if (nextCell.s == cell_state_none
				|| (nextCell.s == cell_state_close && (currentCell.g + 1) < nextCell.g)
				|| (nextCell.s == cell_state_open && (currentCell.g + 1) < nextCell.g))
			{
				nextCell.s = cell_state_next;
				UpdateView();
				SleepMoment();
				nextCell.px = currentCell.x;
				nextCell.py = currentCell.y;
				
				nextCell.g = currentCell.g + 1;
				
				nextCell.h = (abs(Target.x - nextCell.x) + abs(Target.y - nextCell.y));
				nextCell.dir = g_GetDirDiff(currentCell.x, currentCell.y, Target.x, Target.y, nextCell.x, nextCell.y);
				
				nextCell.s = cell_state_open;
				opened.push_back(nextCell);
			}			
		}
		if (currentCell.s != cell_state_origin)
		{
			currentCell.s = cell_state_close;
		}
		opened.erase(pfirst);
		opened.sort();
		pfirst = opened.begin();
	}
	
	return false;	
}

bool CPathThinkerDoc::FindPath_BStar()
{
	std::list<Cell> opened;
	std::list<Cell> backup;
	
	Cell& firstCell = Cells[Origin.y][Origin.x];
	
	opened.push_back(firstCell);
	opened.sort();
	
	std::list<Cell>::iterator iter = NULL;
	while (opened.size() > 0)
	{
		for (iter = opened.begin(); iter != opened.end(); iter++)
		{
			Cell nextCell;
			Cell currentCell = *iter;
			if (currentCell.s != cell_state_origin)
			{
				Cells[currentCell.y][currentCell.x].s = cell_state_check;
			}

			// 自由节点，向着目标前进
			if (currentCell.branch == branch_dir_none)
			{
				// 找到目标方向
				int dir = 0;
				int nextX = 0;
				int nextY = 0;
				for (dir = 0; dir < MAX_DIRECTION; dir++)
				{
					nextX = currentCell.x + Around[dir].x;
					nextY = currentCell.y + Around[dir].y;
					if (nextY < 0 || nextY >= CELL_NUM || nextX < 0 || nextX >= CELL_NUM)
					{
						Cells[currentCell.y][currentCell.x].s = cell_state_close;
						continue;
					}

					int dirDiff = g_GetDirDiff(currentCell.x, currentCell.y, Target.x, Target.y, nextX, nextY);
					if (dirDiff <= 8)
					{
						nextCell = Cells[nextY][nextX];
						break;
					}
				}

				if (nextCell.x == Target.x && nextCell.y == Target.y)
				{
					// 目标方向就是目标坐标
					nextCell.px = currentCell.x;
					nextCell.py = currentCell.y;
					nextCell.g = currentCell.g + 1;
					
					Cells[nextY][nextX] = nextCell;

					BuildPath();
					UpdateView();
					return true;
				}
				else if (nextCell.s == cell_state_none)
				{
					// 目标方向可以前进
					Cells[nextY][nextX].s = cell_state_next;
					nextCell.s = cell_state_next;
					UpdateView();
					SleepMoment();

					nextCell.px = currentCell.x;
					nextCell.py = currentCell.y;				
					nextCell.g = currentCell.g + 1;				
					nextCell.s = cell_state_open;

					Cells[nextY][nextX] = nextCell;

					backup.push_back(nextCell);
				}
				else if (nextCell.s == cell_state_close)
				{
					Cells[currentCell.y][currentCell.x].s = cell_state_close;
					continue;
				}
				else if (nextCell.s == cell_state_open)
				{
					Cells[currentCell.y][currentCell.x].s = cell_state_close;
					continue;
				}
				else if (nextCell.s == cell_state_balk)
				{
					// 碰到阻挡，分出两个叉
					Cell left, right;

					// 左分支
					bool cancel = false;
					int testdir = 0;
					for (testdir = 0; testdir < 4; testdir++)
					{
						if (BranchAround[branch_dir_left][testdir] == dir)
						{
							break;
						}
					}
					int count = 0;
					for (testdir = testdir+1, count = 0; count < 3; testdir++, count++)
					{
						if (testdir == 4) testdir = 0;
						nextX = currentCell.x + Around[BranchAround[branch_dir_left][testdir]].x;
						nextY = currentCell.y + Around[BranchAround[branch_dir_left][testdir]].y;
						if (nextY < 0 || nextY >= CELL_NUM || nextX < 0 || nextX >= CELL_NUM)
						{
							cancel = true;
							break;
						}

						left = Cells[nextY][nextX];
						if (left.s != cell_state_balk)
						{
							break;
						}

					}
					if (cancel == false)
					{
						left.branch = branch_dir_left;
						left.dir = BranchAround[branch_dir_left][testdir];
						
						if (left.s == cell_state_none)
						{
							left.px = currentCell.x;
							left.py = currentCell.y;
							left.g = currentCell.g + 1;				
						}
						else if (left.s == cell_state_close)
						{
							if (left.branch == branch_dir_right && (left.x == currentCell.px && left.y == currentCell.py))
							{
								cancel = true; 
							}
							else if (left.g > currentCell.g + 1)
							{
								left.px = currentCell.x;
								left.py = currentCell.y;
								left.g = currentCell.g + 1;
							}
						}
						else if (left.s == cell_state_open)
						{
							if (left.g > currentCell.g + 1)
							{
								left.px = currentCell.x;
								left.py = currentCell.y;
								left.g = currentCell.g + 1;
							}
						}
						if (cancel == false)
						{
							left.reel = count + 1;
							left.s = cell_state_next;
							Cells[nextY][nextX].s = cell_state_next;

							int angle = g_GetDirAngle(Origin.x, Origin.y, nextX, nextY, nextCell.x, nextCell.y);
							angle = angle > 32 ? (64 - angle) : -angle;
							left.angle = angle;
							
							UpdateView();
							SleepMoment();
							
							left.s = cell_state_open;
							Cells[nextY][nextX] = left;
							backup.push_back(left);
						}
					}

					// 右分支
					cancel = false;
					for (testdir = 0; testdir < 4; testdir++)
					{
						if (BranchAround[branch_dir_right][testdir] == dir)
						{
							break;
						}
					}
					for (testdir = testdir + 1, count = 0; count < 3; count++, testdir++)
					{
						if (testdir == 4) testdir = 0;
						nextX = currentCell.x + Around[BranchAround[branch_dir_right][testdir]].x;
						nextY = currentCell.y + Around[BranchAround[branch_dir_right][testdir]].y;
						if (nextY < 0 || nextY >= CELL_NUM || nextX < 0 || nextX >= CELL_NUM)
						{
							cancel = true;
							break;
						}
						
						right = Cells[nextY][nextX];
						if (right.s != cell_state_balk)
						{
							break;
						}
						
					}
					if (cancel == false)
					{
						right.branch = branch_dir_right;
						right.dir = BranchAround[branch_dir_right][testdir];
						
						if (right.s == cell_state_none)
						{
							right.px = currentCell.x;
							right.py = currentCell.y;
							right.g = currentCell.g + 1;				
						}
						else if (right.s == cell_state_close)
						{
							if (right.branch == branch_dir_left && (right.x == currentCell.px && right.y == currentCell.py))
							{
								cancel = true; 
							}
							else if (right.g > currentCell.g + 1)
							{
								right.px = currentCell.x;
								right.py = currentCell.y;
								right.g = currentCell.g + 1;
							}
						}
						else if (right.s == cell_state_open)
						{
							if (right.g > currentCell.g + 1)
							{
								right.px = currentCell.x;
								right.py = currentCell.y;
								right.g = currentCell.g + 1;				
							}
						}
						if (cancel == false)
						{
							right.reel = count + 1;
							right.s = cell_state_next;
							Cells[nextY][nextX].s = cell_state_next;
							
							int angle = g_GetDirAngle(Origin.x, Origin.y, nextX, nextY, nextCell.x, nextCell.y);
							angle = angle > 32 ? (angle - 64) : angle;
							right.angle = angle;

							UpdateView();
							SleepMoment();
							
							right.s = cell_state_open;
							Cells[nextY][nextX] = right;						
							backup.push_back(right);
						}
					}
				}
			}
			else  // currentCell.stick != branch_dir_none 攀爬节点
			{
				int nextX = 0;
				int nextY = 0;
				Cell nextCell;
				// 非自由节点，沿着障碍爬
				if (currentCell.branch == branch_dir_left)        //左分支，靠右攀爬
				{
					int dir = 0;
					for (dir = 0; dir < 4; dir++)
					{
						if (BranchAround[branch_dir_left][dir] == currentCell.dir)
						{
							break;
						}
					}
					dir += 2 + 1;
					if (dir >= 4) dir -= 4;
					for (int count = 0; count < 4; count++,dir++)
					{
						if (dir >= 4) dir -= 4;
						int nextdir = BranchAround[branch_dir_left][dir];
						nextX = currentCell.x + Around[nextdir].x;
						nextY = currentCell.y + Around[nextdir].y;
						if (nextY < 0 || nextY >= CELL_NUM || nextX < 0 || nextX >= CELL_NUM)
						{
							break;
						}
						
						nextCell = Cells[nextY][nextX];
						if (nextCell.s != cell_state_balk)
						{
							if (nextCell.x == Target.x && nextCell.y == Target.y)
							{
								nextCell.px = currentCell.x;
								nextCell.py = currentCell.y;
								nextCell.g = currentCell.g + 1;
								
								Cells[nextY][nextX] = nextCell;
								
								BuildPath();
								UpdateView();
								return true;
							}
							else if (nextCell.s == cell_state_none)
							{
								nextCell.px = currentCell.x;
								nextCell.py = currentCell.y;
								nextCell.g = currentCell.g + 1;				
							}
							else if (nextCell.s == cell_state_close)
							{
								if (nextCell.branch == branch_dir_right && (nextCell.x == currentCell.px && nextCell.y == currentCell.py)
									&& nextCell.dir != nextdir)
								{
									break;
								}
								else if (nextCell.branch == branch_dir_left && nextCell.dir == nextdir)
								{
									break;
								}
								else if (nextCell.branch == branch_dir_none && nextCell.g > currentCell.g)
								{
									break;
								}
								else if (nextCell.g > currentCell.g + 1)
								{
									nextCell.px = currentCell.x;
									nextCell.py = currentCell.y;
									nextCell.g = currentCell.g + 1;				
								}
							}
							else if (nextCell.s == cell_state_open)
							{
								if (nextCell.branch == branch_dir_left && nextCell.dir == nextdir)
								{
									break;
								}
								else if (nextCell.g > currentCell.g + 1)
								{
									nextCell.px = currentCell.x;
									nextCell.py = currentCell.y;
									nextCell.g = currentCell.g + 1;				
								}
							}

							nextCell.s = cell_state_next;
							Cells[nextY][nextX].s = cell_state_next;
							
							UpdateView();
							SleepMoment();
							
							int reelAdd = count - 1;
							nextCell.reel = currentCell.reel + reelAdd;
							if (nextCell.reel < 0)
								nextCell.reel = 0;
							
							nextCell.s = cell_state_open;
							Cells[nextY][nextX] = nextCell;
							
							int angle = g_GetDirAngle(Origin.x, Origin.y, nextX, nextY, currentCell.x, currentCell.y);
							angle = angle > 32 ? (64 - angle) : -angle;
							nextCell.angle = currentCell.angle + angle;
							if (nextCell.angle >= 64)
							{
								nextCell.angle -= 64;
								nextCell.reel -= 4;
							}
							
							if (nextCell.reel > 0)
							{
								nextCell.branch = branch_dir_left;
								nextCell.dir = nextdir;
							}
							else
							{
								nextCell.branch = branch_dir_none;
								nextCell.dir = -1;
								nextCell.angle = 0;
							}
							
							Cells[nextY][nextX] = nextCell;						
							backup.push_back(nextCell);
							break;
						}
					}
				}
				else  // currentCell.stick != branch_dir_left   //右分支，靠左攀爬
				{
					int dir = 0;
					for (dir = 0; dir < 4; dir++)
					{
						if (BranchAround[branch_dir_right][dir] == currentCell.dir)
						{
							break;
						}
					}
					dir += 2 + 1;
					if (dir >= 4) dir -= 4;
					for (int count = 0; count < 4; count++,dir++)
					{
						if (dir >= 4) dir -= 4;
						int nextdir = BranchAround[branch_dir_right][dir];
						nextX = currentCell.x + Around[nextdir].x;
						nextY = currentCell.y + Around[nextdir].y;
						if (nextY < 0 || nextY >= CELL_NUM || nextX < 0 || nextX >= CELL_NUM)
						{
							break;
						}
						
						nextCell = Cells[nextY][nextX];
						if (nextCell.s != cell_state_balk)
						{
							if (nextCell.x == Target.x && nextCell.y == Target.y)
							{
								// 目标方向就是目标坐标
								nextCell.px = currentCell.x;
								nextCell.py = currentCell.y;
								nextCell.g = currentCell.g + 1;
								
								Cells[nextY][nextX] = nextCell;
								
								BuildPath();
								UpdateView();
								return true;
							}
							else if (nextCell.s == cell_state_none)
							{
								nextCell.px = currentCell.x;
								nextCell.py = currentCell.y;
								nextCell.g = currentCell.g + 1;				
							}
							else if (nextCell.s == cell_state_close)
							{
								if (nextCell.branch == branch_dir_left && (nextCell.x == currentCell.px && nextCell.y == currentCell.py)
									&& nextCell.dir != nextdir)
								{
									break;
								}
								else if (nextCell.branch == branch_dir_right && nextCell.dir == nextdir)
								{
									break;
								}
								else if (nextCell.branch == branch_dir_none && nextCell.g > currentCell.g)
								{
									break;
								}
								else if (nextCell.g > currentCell.g + 1)
								{
									nextCell.px = currentCell.x;
									nextCell.py = currentCell.y;
									nextCell.g = currentCell.g + 1;				
								}
							}
							else if (nextCell.s == cell_state_open)
							{
								if (nextCell.branch == branch_dir_right && nextCell.dir == nextdir)
								{
									break;
								}
								else if (nextCell.g > currentCell.g + 1)
								{
									nextCell.px = currentCell.x;
									nextCell.py = currentCell.y;
									nextCell.g = currentCell.g + 1;				
								}
							}

							nextCell.s = cell_state_next;
							Cells[nextY][nextX].s = cell_state_next;
							
							UpdateView();
							SleepMoment();
							
							int reelAdd = count - 1;
							nextCell.reel = currentCell.reel + reelAdd;
							if (nextCell.reel < 0)
								nextCell.reel = 0;

							nextCell.s = cell_state_open;
							Cells[nextY][nextX] = nextCell;

							
							int angle = g_GetDirAngle(Origin.x, Origin.y, nextX, nextY, currentCell.x, currentCell.y);
							angle = angle > 32 ? (angle - 64) : angle;
							nextCell.angle = currentCell.angle + angle;
							if (nextCell.angle >= 64)
							{
								nextCell.angle -= 64;
								nextCell.reel -= 4;
							}

							if (nextCell.reel > 0)
							{
								nextCell.branch = branch_dir_right;
								nextCell.dir = nextdir;
							}
							else
							{
								nextCell.branch = branch_dir_none;
								nextCell.dir = -1;
								nextCell.angle = 0;
							}
							
							Cells[nextY][nextX] = nextCell;
							backup.push_back(nextCell);
							break;
						} // if (nextCell.s != cell_state_balk)
					} // for (int n = 0; n < 3; n++,dir++)
				} // else currentCell.stickdir != branch_dir_left
			} // else currentCell.stick != branch_dir_none
			if (Cells[currentCell.y][currentCell.x].s != cell_state_origin)
			{
				Cells[currentCell.y][currentCell.x].s = cell_state_close;
			}
		}
		opened.clear();
		opened.splice(opened.end(), backup);
	}
	UpdateView();
	return false;	
}

bool CPathThinkerDoc::BuildPath()
{
	Cell* pCurrent = &Cells[Target.y][Target.x];
	while (pCurrent->px >= 0 && pCurrent->px < CELL_NUM
		&& pCurrent->py >= 0 && pCurrent->py < CELL_NUM)
	{
		if (pCurrent->x == Origin.x && pCurrent->y == Origin.y)
		{
			return true;
		}
		if (pCurrent->s != cell_state_target && pCurrent->s != cell_state_origin)
		{
			pCurrent->s = cell_state_path;
		}
		pCurrent = &Cells[pCurrent->py][pCurrent->px];
	}
	return false;
}

void CPathThinkerDoc::SleepMoment()
{
#if SLEEP_MOMENT==1
	Sleep(SLEEP_SECOND);
#endif
}

void CPathThinkerDoc::UpdateView()
{
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		pView->Invalidate(TRUE);
	}
}

void CPathThinkerDoc::UpdateView2()
{
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		pView->Invalidate(TRUE);
	}
}

void CPathThinkerDoc::FindPath()
{
	time_t ttime;
	time_t ttime2;
	char szTime[32] = {0};
	int count = 0;
	time( &ttime );
	time( &ttime2 );
	tm* localTime = localtime( &ttime );
	strftime(szTime, 256, "%Y-%m-%d %H:%M:%S", localTime);

#if FIND_MODE==1
	FILE *fLog = fopen("pathcompare_astar.txt", "a+b");
#else
#if FIND_MODE==2
	FILE *fLog = fopen("pathcompare_astar_direct.txt", "a+b");
#else
	FILE *fLog = fopen("pathcompare_bstar.txt", "a+b");
#endif
#endif

	if(fLog) 
	{
		bool ret = false;
		char szBuf[256];		
		sprintf( szBuf, "%s %s\n", szTime, "begin..." );
		fwrite( szBuf, 1, strlen(szBuf), fLog );
		while (ttime2 - ttime < FIND_MINIST)
		{
			ClearPath();
#if FIND_MODE==1
			ret = FindPath_AStar();
#else
#if FIND_MODE==2
			ret = FindPath_AStar_Direct();
#else
			ret = FindPath_BStar();
#endif
#endif
			count++;
			time( &ttime2 );
			localTime = localtime( &ttime2 );
		}
		UpdateView2();
		localTime = localtime( &ttime2 );
		strftime(szTime, 256, "%Y-%m-%d %H:%M:%S", localTime);
		sprintf( szBuf, "%s end. count:%d result:%d\n\n\n", szTime, count, ret );
		fwrite( szBuf, 1, strlen(szBuf), fLog );
		fclose(fLog);
	}
}