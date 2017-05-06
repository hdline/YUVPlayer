#if !defined(AFX_MBINFODLG_H__06E4523D_E149_4B00_A40B_08907B00880A__INCLUDED_)
#define AFX_MBINFODLG_H__06E4523D_E149_4B00_A40B_08907B00880A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MBInfoDlg.h : header file
//

#include "define.h"
#include "YUVPlayer.h"

/////////////////////////////////////////////////////////////////////////////
// CMBInfoDlg dialog

class CMBInfoDlg : public CDialog
{
// Construction
public:
    CMBInfoDlg(CWnd *pParent = NULL);   // standard constructor

    uint8   u8LumaPointNumX;        //++ ����ˮƽ������Ҫ��ʾ�ĵ���
    uint8   u8LumaPointNumY;        //++ ���ȴ�ֱ������Ҫ��ʾ�ĵ���
    uint8   u8ChroPointNumX;        //++ ɫ��ˮƽ������Ҫ��ʾ�ĵ���
    uint8   u8ChroPointNumY;        //++ ɫ�ȴ�ֱ������Ҫ��ʾ�ĵ���
    uint16  pixelValue[26][17];     //++ �������ֵ
    int32   s32GridWidth;           //++ ��Ԫ����
    int32   s32GridHeight;          //++ ��Ԫ��߶�
    int32   s32PixTableX;           //++ ��񶥵�����
    int32   s32PixTableY;           //++ ��񶥵�����
    CString gridValue[26][17];      //++ �������ֵ
    CRect   gridRect[26][17];       //++ ��Ԫ��
    CFont   talbeFont;
    CRect   oldRect;            //++ ��ѡ�����ص�����
    CRect   newRect;            //++ ��ѡ�����ص�����
    CWnd    *pParentWnd;

    void    create_window(CWnd *pWnd);
    void    draw_pixel_table();
    void    clean_mark();

// Dialog Data
    //{{AFX_DATA(CMBInfoDlg)
    enum { IDD = IDD_MBINFO_DIALOG };
    CString m_sMBInfo;
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CMBInfoDlg)
public:
    virtual BOOL PreTranslateMessage(MSG *pMsg);
protected:
    virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CMBInfoDlg)
    afx_msg void OnPaint();
    afx_msg void OnClose();
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    uint8   u8ShowMark;         //++ �Ƿ���ʾѡ�����ص���
    uint8   u8ValueMode;        //++ ����ֵ�Ƿ���ʮ�����Ʒ�ʽ��ʾ
    int32   s32MarkGridX;       //++ ��ѡ�����ص������
    int32   s32MarkGridY;       //++ ��ѡ�����ص������

    void    initial();
    void    get_grid_value();
    void    draw_pixel_value();
    void    draw_mark(CRect &currRect);
    void    mark_selected_pixel();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MBINFODLG_H__06E4523D_E149_4B00_A40B_08907B00880A__INCLUDED_)
