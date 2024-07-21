
// GrayScaleImageProcessingRC4View.cpp: CGrayScaleImageProcessingRC4View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "GrayScaleImageProcessingRC4.h"
#endif

#include "GrayScaleImageProcessingRC4Doc.h"
#include "GrayScaleImageProcessingRC4View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGrayScaleImageProcessingRC4View

IMPLEMENT_DYNCREATE(CGrayScaleImageProcessingRC4View, CView)

BEGIN_MESSAGE_MAP(CGrayScaleImageProcessingRC4View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CGrayScaleImageProcessingRC4View 생성/소멸

CGrayScaleImageProcessingRC4View::CGrayScaleImageProcessingRC4View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CGrayScaleImageProcessingRC4View::~CGrayScaleImageProcessingRC4View()
{
}

BOOL CGrayScaleImageProcessingRC4View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CGrayScaleImageProcessingRC4View 그리기

void CGrayScaleImageProcessingRC4View::OnDraw(CDC* /*pDC*/)
{
	CGrayScaleImageProcessingRC4Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CGrayScaleImageProcessingRC4View 인쇄

BOOL CGrayScaleImageProcessingRC4View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CGrayScaleImageProcessingRC4View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CGrayScaleImageProcessingRC4View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CGrayScaleImageProcessingRC4View 진단

#ifdef _DEBUG
void CGrayScaleImageProcessingRC4View::AssertValid() const
{
	CView::AssertValid();
}

void CGrayScaleImageProcessingRC4View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGrayScaleImageProcessingRC4Doc* CGrayScaleImageProcessingRC4View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGrayScaleImageProcessingRC4Doc)));
	return (CGrayScaleImageProcessingRC4Doc*)m_pDocument;
}
#endif //_DEBUG


// CGrayScaleImageProcessingRC4View 메시지 처리기
