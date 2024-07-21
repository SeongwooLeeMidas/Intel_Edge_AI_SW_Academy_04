
// GrayScaleImapeProcessingRCDoc.cpp: CGrayScaleImapeProcessingRCDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "GrayScaleImapeProcessingRC.h"
#endif

#include "GrayScaleImapeProcessingRCDoc.h"

#include <propkey.h>
#include "ConstantDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CGrayScaleImapeProcessingRCDoc

IMPLEMENT_DYNCREATE(CGrayScaleImapeProcessingRCDoc, CDocument)

BEGIN_MESSAGE_MAP(CGrayScaleImapeProcessingRCDoc, CDocument)
END_MESSAGE_MAP()


// CGrayScaleImapeProcessingRCDoc 생성/소멸

CGrayScaleImapeProcessingRCDoc::CGrayScaleImapeProcessingRCDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CGrayScaleImapeProcessingRCDoc::~CGrayScaleImapeProcessingRCDoc()
{
}

BOOL CGrayScaleImapeProcessingRCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CGrayScaleImapeProcessingRCDoc serialization

void CGrayScaleImapeProcessingRCDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CGrayScaleImapeProcessingRCDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CGrayScaleImapeProcessingRCDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CGrayScaleImapeProcessingRCDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CGrayScaleImapeProcessingRCDoc 진단

#ifdef _DEBUG
void CGrayScaleImapeProcessingRCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGrayScaleImapeProcessingRCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGrayScaleImapeProcessingRCDoc 명령


unsigned char** CGrayScaleImapeProcessingRCDoc::OnMalloc2D(int h, int w, int initValue)
{
	// TODO: 여기에 구현 코드 추가.
	unsigned char** retMemory;
	retMemory = new unsigned char* [h];
	for (int i = 0; i < h; i++)
		retMemory[i] = new unsigned char[w];
	return retMemory;
}


void CGrayScaleImapeProcessingRCDoc::OnFree2D(unsigned char** memory, int h)
{
	// TODO: 여기에 구현 코드 추가.
	if (memory == NULL)
		return;
	for (int i = 0; i < h; i++)
		delete memory[i];
	delete memory;
}


BOOL CGrayScaleImapeProcessingRCDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	// 선택한 파일 열기
	CFile File;
	File.Open(lpszPathName, CFile::modeRead | CFile::typeBinary);
	
	// (수정) 2차원배열로사용하기위함- 정방형이미지만다룸.
	double fLength = (double)File.GetLength();
	double log2Value = log(sqrt(fLength)) / log(2.0);
	if (log2Value != (int)log2Value)
	{
		AfxMessageBox(L"정방향크기의 이미지만 지원함");
		return 0;
	}

	// 기존의 메모리는 모두 해제하고, 관련값 초기화.
	OnFree2D(m_inImage, m_inH);
	m_inImage = NULL;
	m_inH = m_inW = 0;
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;

	// (중요!) 입력 이미지 크기 결정 및 메모리 할당
	m_inH = m_inW = (long)sqrt(fLength);
	m_inImage = OnMalloc2D(m_inH, m_inW, 0); 
	
	// 메모리 할당
	for (int i = 0; i < m_inH; i++)
		File.Read(m_inImage[i], m_inW);
	File.Close();

	return TRUE;
}


void CGrayScaleImapeProcessingRCDoc::OnCloseDocument()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	// 기존의 메모리는 모두 해제하고, 관련값 초기화.
	OnFree2D(m_inImage, m_inH);
	m_inImage = NULL;
	m_inH = m_inW = 0;
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;

	CDocument::OnCloseDocument();
}


void CGrayScaleImapeProcessingRCDoc::OnEqualImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 여러 번 실행할 때, 출력 이미지 메모리 해제
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;

	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			m_outImage[i][k] = m_inImage[i][k];
		}
	}
}


void CGrayScaleImapeProcessingRCDoc::OnAddImage()
{
	// 대화 상자 먼저 띄우는게 좋음.
	CConstantDlg dlg;
	if (dlg.DoModal() !=IDOK)
		return 

	// TODO: 여기에 구현 코드 추가.
	// 여러 번 실행할 때, 출력 이미지 메모리 해제
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;

	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;

	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int value = (int)dlg.m_constant;

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (m_inImage[i][k] + value > 255)
				m_outImage[i][k] = 255;
			else if (m_inImage[i][k] + value < 0)
				m_outImage[i][k] = 0;
			else
				m_outImage[i][k] = m_inImage[i][k];
		}
	}
}

BOOL CGrayScaleImapeProcessingRCDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CFile File;
	CFileDialog SaveDlg(FALSE, L"raw", NULL, OFN_HIDEREADONLY);

	if (SaveDlg.DoModal() == IDOK)
	{
		File.Open(SaveDlg.GetPathName(), CFile::modeCreate | CFile::modeWrite);
		for (int i = 0; i < m_outH; i++)
			File.Write(m_outImage[i], m_outW);
		File.Close();
	}

	return true;
}
