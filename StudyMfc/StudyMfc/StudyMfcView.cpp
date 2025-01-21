
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

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HWND	g_hWnd;

// CStudyMfcView

IMPLEMENT_DYNCREATE(CStudyMfcView, CView)

BEGIN_MESSAGE_MAP(CStudyMfcView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CStudyMfcView 생성/소멸

CStudyMfcView::CStudyMfcView() noexcept:m_pDevice(CDevice::Get_Instance())
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CStudyMfcView::~CStudyMfcView()
{
}

void CStudyMfcView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	g_hWnd = m_hWnd;

	if (FAILED(CDevice::Get_Instance()->Init_Device()))
	{
		AfxMessageBox(L"Init_Device Create Failed");
		return;
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
	m_pDevice->Render_End();
}

void CStudyMfcView::OnDestroy()
{
	CView::OnDestroy();
	m_pDevice->Destroy_Instance();
}

#pragma region 생략
BOOL CStudyMfcView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
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
	CView::AssertValid();
}

void CStudyMfcView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}


CStudyMfcDoc* CStudyMfcView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStudyMfcDoc)));
	return (CStudyMfcDoc*)m_pDocument;
}
#endif //_DEBUG


// CStudyMfcView 메시지 처리기
#pragma endregion