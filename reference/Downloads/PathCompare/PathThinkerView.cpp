// PathThinkerView.cpp : implementation of the CPathThinkerView class
//

#include "stdafx.h"
#include "PathThinker.h"

#include "PathThinkerDoc.h"
#include "PathThinkerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

tagColor color[13] = {
	{255, 255, 255},	// cell_state_none,
	{126, 126, 126},	// cell_state_balk,
	{0, 255, 0},		// cell_state_origin,
	{255, 0, 0},		// cell_state_target,
	{176, 224, 230},	// cell_state_close,
	{0, 255, 127},		// cell_state_open,
	{255, 165, 0},		// cell_state_path,
	{255, 69, 0},		// cell_state_check,
	{255, 215, 0},		// cell_state_next,
};

/////////////////////////////////////////////////////////////////////////////
// CPathThinkerView

IMPLEMENT_DYNCREATE(CPathThinkerView, CView)

BEGIN_MESSAGE_MAP(CPathThinkerView, CView)
	//{{AFX_MSG_MAP(CPathThinkerView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
		ON_WM_CREATE()
		ON_WM_DESTROY()
		ON_WM_SIZE()
		
		ON_WM_LBUTTONDOWN()
		ON_WM_LBUTTONUP()
		
		ON_COMMAND(ID_EDIT_BLAK, OnCmdBalk)
		ON_COMMAND(ID_EDIT_CLEAR, OnCmdClear)
		ON_COMMAND(ID_EDIT_ORIGIN, OnCmdOrigin)
		ON_COMMAND(ID_EDIT_TARGET, OnCmdTarget)
		ON_COMMAND(ID_COMMAND_START, OnCmdFind)
		
		ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPathThinkerView construction/destruction

CPathThinkerView::CPathThinkerView()
{
	// TODO: add construction code here

}

CPathThinkerView::~CPathThinkerView()
{
}

BOOL CPathThinkerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPathThinkerView drawing

void CPathThinkerView::OnDraw(CDC* pDC)
{
	CPathThinkerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	DrawMapCellBorders(pDC, m_ClientPixel.x, m_ClientPixel.y);
	DrawMapCellContents(pDC, m_ClientPixel.x, m_ClientPixel.y);
}

/////////////////////////////////////////////////////////////////////////////
// CPathThinkerView diagnostics

#ifdef _DEBUG
void CPathThinkerView::AssertValid() const
{
	CView::AssertValid();
}

void CPathThinkerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPathThinkerDoc* CPathThinkerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPathThinkerDoc)));
	return (CPathThinkerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPathThinkerView message handlers


int CPathThinkerView::OnCreate(LPCREATESTRUCT lpcs)
{
	if (CView::OnCreate(lpcs) == -1)
	{
		return -1;
	}
	CPathThinkerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	m_CommandState = cmd_state_balk;
	for (int i = 0; i < CELL_NUM; i++)
	{
		for (int j = 0; j < CELL_NUM; j++)
		{
			pDoc->Cells[i][j].Init(j, i);
		}
	}

	return 0;
}

void CPathThinkerView::OnDestroy()
{
	CView::OnDestroy();
}

void CPathThinkerView::OnSize(UINT nType, int cx, int cy)
{
	if (cx == 0) return;

	CView::OnSize(nType, cx, cy);
	CPathThinkerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CPoint aspect;
	aspect.x = cx;
	aspect.y = cy;
	
	m_ClientPixel = aspect;

	m_CellX = (cx - BLANK_WIDTH) / CELL_NUM;
	m_CellY = (cy - BLANK_WIDTH) / CELL_NUM;
	
	m_BeginX = BLANK_WIDTH / 2;
	m_BeginY = BLANK_HEIGHT / 2;

	m_slope = (m_CellY * 1.0) / (m_CellX * 1.0);
}

void CPathThinkerView::OnCmdBalk() 
{
	// TODO: Add your command handler code here
	CPathThinkerDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	m_CommandState = cmd_state_balk;	
}

void CPathThinkerView::OnCmdClear() 
{
	// TODO: Add your command handler code here
	CPathThinkerDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->ResetCells();
	m_CommandState = cmd_state_balk;

	Invalidate();
}

void CPathThinkerView::OnCmdOrigin() 
{
	// TODO: Add your command handler code here
	CPathThinkerDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	m_CommandState = cmd_state_origin;	
}

void CPathThinkerView::OnCmdTarget() 
{
	// TODO: Add your command handler code here
	CPathThinkerDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	m_CommandState = cmd_state_target;	
}

void CPathThinkerView::OnCmdFind() 
{
	// TODO: Add your command handler code here
	CPathThinkerDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	m_CommandState = cmd_state_find;	
	pDoc->StartFind();
}

/////////////////////////////////////////////////////////////////////////////
// CPathFinderView message handlers

void CPathThinkerView::DrawMapCellBorders(CDC* pDC, int cx, int cy)
{
	COLORREF penColor=RGB(192, 192, 192);
	CPen* pOldPen;
	CPen* pNewPen;
	pNewPen = new CPen(PS_SOLID, 1, penColor);
	pOldPen = pDC->SelectObject(pNewPen);

	CPoint src;
	CPoint dest;
	src.x = m_BeginX;
	src.y = m_BeginY;
	dest.x = src.x;
	dest.y = src.y + m_CellY * (CELL_NUM);
	int i = 0;
	for (i = 0; i <= CELL_NUM; i++)
	{
		pDC->MoveTo(src);
		pDC->LineTo(dest);

		src.x += m_CellX;
		dest.x += m_CellX;
	}

	src.x = m_BeginX;
	src.y = m_BeginY;
	dest.x = src.x + m_CellX * (CELL_NUM);
	dest.y = src.y;
	for (i = 0; i <= CELL_NUM; i++)
	{
		pDC->MoveTo(src);
		pDC->LineTo(dest);
		
		src.y += m_CellY;
		dest.y += m_CellY;
	}

	pDC->SelectObject(pOldPen);
	delete pNewPen;
}

void CPathThinkerView::DrawMapCellContents(CDC* pDC, int cx, int cy)
{
	CPathThinkerDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CBrush* pOldBrush;
	CBrush* pNewBrush;

	LOGFONT logfont;
	CFont cfont;
	memset(&logfont, 0, sizeof(LOGFONT));
	logfont.lfHeight = m_CellY * 7 / 10;
	logfont.lfCharSet = ANSI_CHARSET;
	cfont.CreateFontIndirect(&logfont);
	CFont* pOldFont = pDC->SelectObject(&cfont);
	pDC->SetBkMode(TRANSPARENT);

	int row = 0;
	int col = 0;
	for (row = 0; row < CELL_NUM; row++)
	{
		for (col = 0; col < CELL_NUM; col++)
		{
			pNewBrush = new CBrush;
			Cell& cell = pDoc->Cells[row][col];
			int s = cell.s;
			int x1 = m_BeginX + col * m_CellX;
			int y1 = m_BeginY + row * m_CellY;
			
			BOOL result = FALSE;
			result = pNewBrush->CreateSolidBrush(RGB(color[s].r, color[s].g, color[s].b));
			if (result)
			{
				pOldBrush = pDC->SelectObject(pNewBrush);
				pDC->Rectangle(x1, y1, x1 + m_CellX, y1 + m_CellY);
				pDC->SelectObject(pOldBrush);

				if (cell.s == cell_state_origin || cell.s == cell_state_close || cell.s == cell_state_open
					|| cell.s == cell_state_path || (cell.s == cell_state_target && cell.g != 0))
				{
					char str[16];
					sprintf(str, "%d", cell.g);
					pDC->TextOut(x1+2, y1+2, str);
				}
			}
			delete pNewBrush;
		}
	}
	pDC->SelectObject(pOldFont);

}

void CPathThinkerView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CView::OnLButtonDown(nFlags, point);
	CPathThinkerDoc* pDoc = GetDocument();

	switch (m_CommandState)
	{
	case cmd_state_balk:
		m_BeginPoint = point;
		break;
	case cmd_state_origin:
		m_BeginPoint = point;
		break;
	case cmd_state_target:
		m_BeginPoint = point;
		break;
	}
}

void CPathThinkerView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CView::OnLButtonUp(nFlags, point);
	CPathThinkerDoc* pDoc = GetDocument();

	switch (m_CommandState)
	{
	case cmd_state_balk:
		m_EndPoint = point;
		PutBalk();
		break;
	case cmd_state_origin:
		m_EndPoint = point;
		PutOrigin();
		break;
	case cmd_state_target:
		m_EndPoint = point;
		PutTarget();
		break;
	}
}


void CPathThinkerView::PutBalk()
{
	CPathThinkerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	std::list<Cell> cells;
	bool hasOverCell = GetAllOverCells(m_BeginPoint, m_EndPoint, cells);
	if (hasOverCell)
	{
		std::list<Cell>::iterator it = cells.begin();
		for(; it != cells.end(); it++)
		{
			Cell& cell = *it;
			pDoc->Cells[cell.y][cell.x].s = cell_state_balk;
		}
	}
	Invalidate();
}

void CPathThinkerView::PutOrigin()
{
	CPathThinkerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	Cell cell;
	bool hasOverCell = GetOverCell(m_EndPoint, cell);
	if (hasOverCell)
	{
		pDoc->Cells[cell.y][cell.x].s = cell_state_origin;
		if (pDoc->Origin.s == cell_state_origin)
		{
			pDoc->Cells[pDoc->Origin.y][pDoc->Origin.x].s = cell_state_none;
		}
		pDoc->Origin.x = cell.x;
		pDoc->Origin.y = cell.y;
		pDoc->Origin.s = cell_state_origin;
	}
	Invalidate();
}

void CPathThinkerView::PutTarget()
{
	CPathThinkerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	Cell cell;
	bool hasOverCell = GetOverCell(m_EndPoint, cell);
	if (hasOverCell)
	{
		pDoc->Cells[cell.y][cell.x].s = cell_state_target;
		if (pDoc->Target.s == cell_state_target)
		{
			pDoc->Cells[pDoc->Target.y][pDoc->Target.x].s = cell_state_none;
		}
		pDoc->Target.x = cell.x;
		pDoc->Target.y = cell.y;
		pDoc->Target.s = cell_state_target;
	}
	Invalidate();
}

bool CPathThinkerView::GetOverCell(CPoint p, Cell& cell)
{
	if (p.x <= m_BeginX || p.x >= m_BeginX + m_CellX * CELL_NUM
		|| p.y <= m_BeginY || p.y >= m_BeginY + m_CellY * CELL_NUM)
	{
		return false;
	}

	int row = (p.y - m_BeginY) / m_CellY;
	int col = (p.x - m_BeginX) / m_CellX;
	cell.x = col;
	cell.y = row;
	return true;
}

bool CPathThinkerView::GetAllOverCells(CPoint p1, CPoint p2, std::list<Cell>& cells)
{
	if (p1.x <= m_BeginX || p1.x >= m_BeginX + m_CellX * CELL_NUM
		|| p1.y <= m_BeginY || p1.y >= m_BeginY + m_CellY * CELL_NUM)
	{
		return false;
	}
	
	if (p2.x < p1.x)
	{
		CPoint temp = p1;
		p1 = p2;
		p2 = temp;
	}

	int row = (p1.y - m_BeginY) / m_CellY;
	int col = (p1.x - m_BeginX) / m_CellX;
	Cell cell(col, row);
	cells.push_back(cell);

	int h = 0;
	if (p2.x > p1.x)
		h = 1;

	int v = 0;
	if (p2.y > p1.y)
		v = 1;
	else if (p2.y < p1.y)
		v = -1;

	if (h == 0)
	{
		if (v >= 0)
		{
			for (int y = m_BeginY+(m_CellY*(row+1)); y < p2.y; y += m_CellY)
			{
				row++;
				cell.Init(col, row);
				cells.push_back(cell);
			}
		}
		else
		{
			for (int y = m_BeginY+(m_CellY*(row)); y > p2.y; y -= m_CellY)
			{
				row--;
				cell.Init(col, row);
				cells.push_back(cell);
			}
		}
	}
	else if (v == 0)
	{
		for (int x = m_BeginX+(m_CellX*(col+1)); x < p2.x; x += m_CellX)
		{
			col++;
			cell.Init(col, row);
			cells.push_back(cell);
		}
	}
	else
	{
		float slope = (p2.y - p1.y) * 1.0 / (p2.x - p1.x);
		if (v > 0)
		{
			int checkX = m_BeginX + m_CellX * (col + 1);
			int checkY = m_BeginY + m_CellY * (row + 1);
			while (checkX < p2.x || checkY < p2.y)
			{
				float slope2 = (checkY - p1.y) * 1.0 / (checkX - p1.x);
				if (slope2 > slope)
				{
					col++;
				}
				else if (slope2 < slope)
				{
					row++;
				}
				else
				{
					col++;
					row++;
				}
				cell.Init(col, row);
				cells.push_back(cell);
				
				checkX = m_BeginX + m_CellX * (col + 1);
				checkY = m_BeginY + m_CellY * (row + 1);
			}
		}
		else
		{
			int checkX = m_BeginX + m_CellX * (col + 1);
			int checkY = m_BeginY + m_CellY * row;
			while (checkX < p2.x || checkY > p2.y)
			{
				float slope2 = (checkY - p1.y) * 1.0 / (checkX - p1.x);
				if (slope2 > slope)
				{
					row--;
				}
				else if (slope2 < slope)
				{
					col++;
				}
				else
				{
					col++;
					row--;
				}
				cell.Init(col, row);
				cells.push_back(cell);
				
				checkX = m_BeginX + m_CellX * (col + 1);
				checkY = m_BeginY + m_CellY * row;
			}
		}
	}
	return true;
}
