
// StudyMfcView.cpp: CStudyMfcView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "StudyMfc.h"
#endif

#include "StudyMfcDoc.h"
#include "StudyMfcView.h"
#include "CDevice.h"
#include "CTextureMgr.h"
#include "MainFrm.h"
#include "CTerrain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HWND	g_hWnd;

// CStudyMfcView

IMPLEMENT_DYNCREATE(CStudyMfcView, CScrollView)

BEGIN_MESSAGE_MAP(CStudyMfcView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN() //좌클릭 활성화
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CStudyMfcView 생성/소멸

CStudyMfcView::CStudyMfcView() noexcept:m_pDevice(CDevice::Get_Instance()), m_pTerrain(nullptr)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CStudyMfcView::~CStudyMfcView()
{
}

void CStudyMfcView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	SetScrollSizes(MM_TEXT, CSize(TILECX * TILEX, TILECY * TILEY / 2));

	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();

	RECT rcWnd{};
	pMainFrm->GetWindowRect(&rcWnd); //전체 윈도우 크기 (창, 테두리, 메뉴, 타이틀 바 모두 포함)
	SetRect(&rcWnd, 0, 0, rcWnd.right - rcWnd.left, rcWnd.bottom - rcWnd.top);

	RECT rcMainView{};
	GetClientRect(&rcMainView);
	float	fRowFrm = float(rcWnd.right - rcMainView.right);
	float	fColFrm = float(rcWnd.bottom - rcMainView.bottom);

	pMainFrm->SetWindowPos(nullptr,	
		0,
		0,
		int(WINCX + fRowFrm),
		int(WINCY + fColFrm),
		SWP_NOZORDER); 

	g_hWnd = m_hWnd;

	if (FAILED(CDevice::Get_Instance()->Init_Device()))
	{
		AfxMessageBox(L"Init_Device Create Failed");
		return;
	}

	m_pTerrain = new CTerrain;
	if (FAILED(m_pTerrain->Initialize()))
	{
		AfxMessageBox(L"m_pTerrain Create Failed");
		return;
	}
	m_pTerrain->Set_MainView(this);
}

void CStudyMfcView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CScrollView::OnLButtonDown(nFlags, point);
	m_pTerrain->Tile_Change(D3DXVECTOR3(float(point.x), float(point.y), 0.f), 0);
	Invalidate(false);
}

void CStudyMfcView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CScrollView::OnMouseMove(nFlags, point);

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		m_pTerrain->Tile_Change(D3DXVECTOR3(float(point.x) + GetScrollPos(0),
			float(point.y) + GetScrollPos(1),
			0.f), 0);
		Invalidate(FALSE);

		//CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(GetParentFrame());
		//CMiniView* pMiniView = dynamic_cast<CMiniView*>(pMainFrm->m_SecondSplitter.GetPane(0, 0));

		//pMiniView->Invalidate(FALSE);
	}
}

// CStudyMfcView 그리기

void CStudyMfcView::OnDraw(CDC* /*pDC*/)
{
	CStudyMfcDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	m_pDevice->Render_Begin();
	m_pTerrain->Render();
	m_pDevice->Render_End();

}

void CStudyMfcView::OnDestroy()
{
	CScrollView::OnDestroy();
	Safe_Delete(m_pTerrain);
	CTextureMgr::Destroy_Instance();
	m_pDevice->Destroy_Instance();
}

#pragma region 생략
BOOL CStudyMfcView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}


// CStudyMfcView 인쇄

BOOL CStudyMfcView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CStudyMfcView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CStudyMfcView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CStudyMfcView 진단

#ifdef _DEBUG
void CStudyMfcView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CStudyMfcView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}


CStudyMfcDoc* CStudyMfcView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStudyMfcDoc)));
	return (CStudyMfcDoc*)m_pDocument;
}
#endif //_DEBUG


// CStudyMfcView 메시지 처리기
#pragma endregion