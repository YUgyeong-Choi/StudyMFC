
// StudyMfcView.h: CStudyMfcView 클래스의 인터페이스
//

#pragma once
#include "CDevice.h"

class CTerrain;
class CStudyMfcDoc;
class CStudyMfcView : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CStudyMfcView() noexcept;
	DECLARE_DYNCREATE(CStudyMfcView)

// 특성입니다.
public:
	CStudyMfcDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CStudyMfcView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();


private:
	CDevice* m_pDevice;
	CTerrain* m_pTerrain;
public:
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // StudyMfcView.cpp의 디버그 버전
inline CStudyMfcDoc* CStudyMfcView::GetDocument() const
   { return reinterpret_cast<CStudyMfcDoc*>(m_pDocument); }
#endif

