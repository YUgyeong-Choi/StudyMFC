// CUnitTool.cpp: 구현 파일
//

#include "pch.h"
#include "StudyMfc.h"
#include "afxdialogex.h"
#include "CUnitTool.h"


// CUnitTool 대화 상자

IMPLEMENT_DYNAMIC(CUnitTool, CDialog)

CUnitTool::CUnitTool(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CUnitTool, pParent)
{

}

CUnitTool::~CUnitTool()
{
}

void CUnitTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUnitTool, CDialog)
END_MESSAGE_MAP()


// CUnitTool 메시지 처리기
