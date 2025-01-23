// CMiniView.cpp: 구현 파일
//

#include "pch.h"
#include "StudyMfc.h"
#include "CMiniView.h"
#include "MainFrm.h"
#include "StudyMfcView.h"
#include "CTerrain.h"

// CMiniView

IMPLEMENT_DYNCREATE(CMiniView, CView)

CMiniView::CMiniView()
{

}

CMiniView::~CMiniView()
{
}

BEGIN_MESSAGE_MAP(CMiniView, CView)
END_MESSAGE_MAP()


// CMiniView 그리기

void CMiniView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.

	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CStudyMfcView* pView = dynamic_cast<CStudyMfcView*>(pMainFrm->m_MainSplitter.GetPane(0, 1));

	CTerrain* pTerrain = pView->m_pTerrain;

	CDevice::Get_Instance()->Render_Begin();

	pTerrain->Mini_Render();

	CDevice::Get_Instance()->Render_End(m_hWnd);
}


// CMiniView 진단

#ifdef _DEBUG
void CMiniView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CMiniView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMiniView 메시지 처리기
