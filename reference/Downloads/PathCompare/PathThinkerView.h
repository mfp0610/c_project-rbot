// PathThinkerView.h : interface of the CPathThinkerView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PATHTHINKERVIEW_H__1E72162C_D116_457F_9BA5_F1C6494D53C9__INCLUDED_)
#define AFX_PATHTHINKERVIEW_H__1E72162C_D116_457F_9BA5_F1C6494D53C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <list>

enum CommandState
{
	cmd_state_none,
	cmd_state_balk,
	cmd_state_origin,
	cmd_state_target,
	cmd_state_find,
};

struct tagColor
{
	int r, g, b;
};


class CPathThinkerView : public CView
{
protected: // create from serialization only
	CPathThinkerView();
	DECLARE_DYNCREATE(CPathThinkerView)

// Attributes
public:
	CPathThinkerDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPathThinkerView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPathThinkerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	
protected:
	void DrawMapCellBorders(CDC* pDC, int cx, int cy);
	void DrawMapCellContents(CDC* pDC, int cx, int cy);
	
protected:
	CClientDC*		pClientDC;
	CPoint			m_ClientPixel;
	
	int				m_CellX;
	int				m_CellY;	
	int				m_BeginX;
	int				m_BeginY;
	float			m_slope;
	
	CommandState	m_CommandState;
	CPoint			m_BeginPoint;
	CPoint			m_EndPoint;
	
	CWinThread*		pThread;
	
private:
	void			PutBalk();
	void			PutOrigin();
	void			PutTarget();
	
	bool			GetOverCell(CPoint p, Cell& cell);
	bool			GetAllOverCells(CPoint p1, CPoint p2, std::list<Cell>& cells);
	


// Generated message map functions
protected:
	//{{AFX_MSG(CPathThinkerView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	afx_msg int OnCreate(LPCREATESTRUCT lpcs);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
	afx_msg void OnCmdBalk();
	afx_msg void OnCmdClear();
	afx_msg void OnCmdOrigin();
	afx_msg void OnCmdTarget();
	afx_msg void OnCmdFind();
	
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PathThinkerView.cpp
inline CPathThinkerDoc* CPathThinkerView::GetDocument()
   { return (CPathThinkerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PATHTHINKERVIEW_H__1E72162C_D116_457F_9BA5_F1C6494D53C9__INCLUDED_)
