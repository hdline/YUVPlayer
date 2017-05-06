// MBInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MBInfoDlg.h"
#include "YUVPlayerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMBInfoDlg dialog


CMBInfoDlg::CMBInfoDlg(CWnd *pParent /*=NULL*/)
    : CDialog(CMBInfoDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CMBInfoDlg)
    m_sMBInfo = _T("");
    //}}AFX_DATA_INIT
}


void CMBInfoDlg::DoDataExchange(CDataExchange *pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CMBInfoDlg)
    DDX_Text(pDX, IDC_MB_INFO, m_sMBInfo);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMBInfoDlg, CDialog)
    //{{AFX_MSG_MAP(CMBInfoDlg)
    ON_WM_PAINT()
    ON_WM_CLOSE()
    ON_WM_MOUSEMOVE()
    ON_WM_LBUTTONDOWN()
    ON_WM_RBUTTONDOWN()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMBInfoDlg message handlers

void CMBInfoDlg::initial()
{
    s32MarkGridX         = 0;
    s32MarkGridY         = 0;
    u8ShowMark           = FALSE;
    u8ValueMode          = OCT_MODE;
    s32GridWidth         = 24;
    s32GridHeight        = 13;
    s32PixTableX         = 3;
    s32PixTableY         = 90;
    m_sMBInfo            = _T("");
    oldRect.SetRect(-100, -100, -100, -100);
    //++ �������ر��ʹ�õ�����
    VERIFY(talbeFont.CreateFont(13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Arial"));
}

void CMBInfoDlg::OnPaint()
{
    CPaintDC dc(this); // device context for painting

    // TODO: Add your message handler code here
    CChildDlg   *pCurrImage  = (CChildDlg *)pParentWnd;


    SetWindowText("�����Ϣ - " + pCurrImage->fileName);
    //++ ��ֹ���ڱ��ڵ��󣬴����ϵ����ݶ�ʧ
    draw_pixel_table();
    oldRect.SetRect(-100, -100, -100, -100);
    // Do not call CDialog::OnPaint() for painting messages
}

void CMBInfoDlg::create_window(CWnd *pWnd)
{
    int32   i;
    int32   j;


    pParentWnd   = pWnd;
    Create(IDD_MBINFO_DIALOG, pParentWnd);
    initial();

    //---- �������ر����ο�λ�� ----
    //++ ����ˮƽ��ͷ��Ԫ��
    gridRect[0][0].left      = s32PixTableX;
    gridRect[0][0].top       = s32PixTableY;
    gridRect[0][0].right     = s32PixTableX + s32GridWidth + 1;
    gridRect[0][0].bottom    = s32PixTableY + s32GridHeight + 1;
    for (i = 1; i < 17; i++) {
        gridRect[0][i].left      = gridRect[0][i - 1].left + s32GridWidth;
        gridRect[0][i].top       = gridRect[0][i - 1].top;
        gridRect[0][i].right     = gridRect[0][i - 1].right + s32GridWidth;
        gridRect[0][i].bottom    = gridRect[0][i - 1].bottom;
    }

    for (j = 1; j < 17; j ++) {
        //++ ���ȴ�ֱ��ͷ��Ԫ��
        gridRect[j][0].left      = gridRect[j - 1][0].left;
        gridRect[j][0].top       = gridRect[j - 1][0].top + s32GridHeight;
        gridRect[j][0].right     = gridRect[j - 1][0].right;
        gridRect[j][0].bottom    = gridRect[j - 1][0].bottom + s32GridHeight;

        //++ �������ص�Ԫ��
        for (i = 1; i < 17; i++) {
            gridRect[j][i].left      = gridRect[j][i - 1].left + s32GridWidth;
            gridRect[j][i].top       = gridRect[j][i - 1].top;
            gridRect[j][i].right     = gridRect[j][i - 1].right + s32GridWidth;
            gridRect[j][i].bottom    = gridRect[j][i - 1].bottom;
        }
    }

    //++ ɫ��ˮƽ��ͷ��Ԫ��
    for (i = 0; i < 17; i++) {
        gridRect[17][i].left     = gridRect[16][i].left;
        gridRect[17][i].top      = gridRect[16][i].top + (s32GridHeight << 1);
        gridRect[17][i].right    = gridRect[16][i].right;
        gridRect[17][i].bottom   = gridRect[16][i].bottom + (s32GridHeight << 1);
    }

    for (j = 18; j < 26; j ++) {
        //++ ɫ�ȴ�ֱ��ͷ��Ԫ��
        gridRect[j][0].left      = gridRect[j - 1][0].left;
        gridRect[j][0].top       = gridRect[j - 1][0].top + s32GridHeight;
        gridRect[j][0].right     = gridRect[j - 1][0].right;
        gridRect[j][0].bottom    = gridRect[j - 1][0].bottom + s32GridHeight;

        //++ ɫ�����ص�Ԫ��
        for (i = 1; i < 17; i++) {
            gridRect[j][i].left      = gridRect[j][i - 1].left + s32GridWidth;
            gridRect[j][i].top       = gridRect[j][i - 1].top;
            gridRect[j][i].right     = gridRect[j][i - 1].right + s32GridWidth;
            gridRect[j][i].bottom    = gridRect[j][i - 1].bottom;
        }
    }
}

void CMBInfoDlg::draw_pixel_table()
{
    int32       i;
    int32       j;
    uint32      u32DrawFormat    = DT_CENTER | DT_VCENTER | DT_NOCLIP;
    CClientDC   currDC(this);


    //++ ѡ������
    currDC.SelectObject(&talbeFont);
    //++ �������ֱ���͸��
    currDC.SetBkMode(TRANSPARENT);
    //++ ѡ���ɫ�ޱ߿��
    CPen    whitePen;
    whitePen.CreatePen(PS_NULL, 1, RGB(255, 255, 255));
    currDC.SelectObject(&whitePen);
    //========== ���Ʊ�ͷ ==========
    //++ ����������ɫ
    currDC.SetTextColor(RGB(0, 0, 255));
    currDC.DrawText("Y" , &(gridRect[0 ][0]), u32DrawFormat);
    currDC.DrawText("UV", &(gridRect[17][0]), u32DrawFormat);
    //++ ����������ɫ
    currDC.SetTextColor(RGB(255, 0, 0));

    for (i = 1; i < 17; i ++) {
        //---------- ����ˮƽ��ͷ ----------
        gridValue[0][i].Format("%d", i - 1);
        currDC.DrawText(gridValue[0][i], &(gridRect[0][i]), u32DrawFormat);
        //---------- ɫ��ˮƽ��ͷ ----------
        gridValue[17][i].Format("%d", (i - 1) % 8);
        currDC.DrawText(gridValue[17][i], &(gridRect[17][i]), u32DrawFormat);
    }
    //---------- ���ȴ�ֱ��ͷ ----------
    for (j = 1; j < 17; j ++) {
        gridValue[j][0].Format("%d", j - 1);
        currDC.DrawText(gridValue[j][0], &(gridRect[j][0]), u32DrawFormat);
    }
    //---------- ɫ�ȴ�ֱ��ͷ ----------
    for (j = 18; j < 26; j ++) {
        gridValue[j][0].Format("%d", j - 18);
        currDC.DrawText(gridValue[j][0], &(gridRect[j][0]), u32DrawFormat);
    }

    draw_pixel_value();

    whitePen.DeleteObject();
}

void CMBInfoDlg::get_grid_value()
{
    int32   i;
    int32   j;
    CString textFormat;


    if (u8ValueMode == HEX_MODE) {
        textFormat   = "x%X";   //++ ��ʾʮ������ֵ
    } else {
        textFormat   = "%d";    //++ ��ʾʮ����ֵ
    }

    for (i = 1; i < 17; i ++) {
        for (j = 1; j < 17; j ++) {
            gridValue[j][i].Format("");
        }
        for (j = 18; j < 26; j ++) {
            gridValue[j][i].Format("");
        }
    }
    for (j = 1; j < 1 + u8LumaPointNumY; j ++) {
        for (i = 1; i < 1 + u8LumaPointNumX; i ++) {
            gridValue[j][i].Format(textFormat, pixelValue[j][i]);
        }
    }
    for (j = 18; j < 18 + u8ChroPointNumY; j ++) {
        for (i = 1; i < 1 + u8ChroPointNumX; i ++) {
            gridValue[j][i].Format(textFormat, pixelValue[j][i]);
        }

        for (i = 9; i < 9 + u8ChroPointNumX; i ++) {
            gridValue[j][i].Format(textFormat, pixelValue[j][i]);
        }
    }
}

void CMBInfoDlg::draw_pixel_value()
{
    int32       i;
    int32       j;
    uint32      u32DrawFormat    = DT_CENTER | DT_VCENTER | DT_NOCLIP;
    CClientDC   currDC(this);

    get_grid_value();

    //++ ѡ������
    currDC.SelectObject(&talbeFont);
    //++ �������ֱ���͸��
    currDC.SetBkMode(TRANSPARENT);

    //========== �������ر�� ==========
    //++ ����������ɫ
    currDC.SetTextColor(RGB(0, 0, 0));
    //++ ѡ���ɫʵ�߱�
    CPen    grayPen;
    grayPen.CreatePen(PS_SOLID, 1, RGB(192, 192, 192));
    currDC.SelectObject(&grayPen);

    for (i = 1; i < 17; i ++) {
        for (j = 1; j < 17; j ++) {
            currDC.Rectangle(gridRect[j][i]);
            currDC.DrawText(gridValue[j][i], &(gridRect[j][i]), u32DrawFormat);
        }

        for (j = 18; j < 26; j ++) {
            currDC.Rectangle(gridRect[j][i]);
            currDC.DrawText(gridValue[j][i], &(gridRect[j][i]), u32DrawFormat);
        }
    }

    //========== ���ֽ��� ==========
    //++ ѡ���ɫ���߱�
    CPen    redPen;
    CRect   boderRect;
    redPen.CreatePen(PS_DOT, 1, RGB(255, 0, 0));
    currDC.SelectObject(&redPen);

    currDC.MoveTo(gridRect[0][1].left, gridRect[1][0].top);
    currDC.LineTo(gridRect[0][16].right - 1, gridRect[1][0].top);
    currDC.LineTo(gridRect[0][16].right - 1, gridRect[16][16].bottom - 1);
    currDC.LineTo(gridRect[16][1].left, gridRect[16][16].bottom - 1);
    currDC.LineTo(gridRect[0][1].left, gridRect[1][0].top);

    currDC.MoveTo(gridRect[18][1].left, gridRect[18][0].top);
    currDC.LineTo(gridRect[18][16].right - 1, gridRect[18][0].top);
    currDC.LineTo(gridRect[18][16].right - 1, gridRect[25][16].bottom - 1);
    currDC.LineTo(gridRect[25][1].left, gridRect[25][16].bottom - 1);
    currDC.LineTo(gridRect[18][1].left, gridRect[18][0].top);

    currDC.MoveTo(gridRect[18][9].left, gridRect[18][9].top);
    currDC.LineTo(gridRect[25][9].left, gridRect[25][9].bottom);

    redPen.DeleteObject();
    grayPen.DeleteObject();
}

void CMBInfoDlg::draw_mark(CRect &currRect)
{
    CClientDC   currDC(this);


    //++ ѡ���ɫʵ�߱�
    CPen    redPen;
    redPen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
    currDC.SelectObject(&redPen);
    currDC.SetROP2(R2_NOTXORPEN);

    //++ ��ǵ�Ԫ��
    currDC.MoveTo(currRect.left, currRect.top);
    currDC.LineTo(currRect.right - 1, currRect.top);
    currDC.LineTo(currRect.right - 1, currRect.bottom - 1);
    currDC.LineTo(currRect.left, currRect.bottom - 1);
    currDC.LineTo(currRect.left, currRect.top);

    //++ ��ʮ����
    int32   s32MarkLineX     = currRect.left + (s32GridWidth >> 1);
    int32   s32MarkLineY     = currRect.top + (s32GridHeight >> 1);

    currDC.MoveTo(s32MarkLineX, s32PixTableY);
    currDC.LineTo(s32MarkLineX, currRect.top);
    currDC.MoveTo(s32MarkLineX, currRect.bottom);
    currDC.LineTo(s32MarkLineX, gridRect[25][16].bottom);
    currDC.MoveTo(s32PixTableX, s32MarkLineY);
    currDC.LineTo(currRect.left, s32MarkLineY);
    currDC.MoveTo(currRect.right, s32MarkLineY);
    currDC.LineTo(gridRect[25][16].right, s32MarkLineY);

    redPen.DeleteObject();
}

void CMBInfoDlg::mark_selected_pixel()
{
    //++ ������ʷѡ�����ص�
    draw_mark(oldRect);
    //++ ��ǵ�ǰѡ�����ص�
    draw_mark(newRect);

    oldRect     = newRect;
}

void CMBInfoDlg::clean_mark()
{
    draw_mark(oldRect);

    oldRect.SetRect(-100, -100, -100, -100);
    newRect.SetRect(-100, -100, -100, -100);
}

void CMBInfoDlg::OnMouseMove(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    if (u8ShowMark == TRUE) {
        if ((point.x > gridRect[0][0].right) && (point.x < gridRect[0][16].right - 1)
            && (((point.y > gridRect[0][0].bottom) && (point.y < (gridRect[16][0].bottom - 1)))
                || ((point.y > gridRect[17][0].bottom) && (point.y < (gridRect[25][0].bottom - 1))))) {
            int32   s32CurrGridX     = (point.x - s32PixTableX) / s32GridWidth;
            int32   s32CurrGridY     = (point.y - s32PixTableY) / s32GridHeight;

            if (point.y > gridRect[17][0].bottom) {
                s32CurrGridY    -= 1;
            }

            if ((s32CurrGridX != s32MarkGridX) || (s32CurrGridY != s32MarkGridY)) {
                CYUVPlayerDlg   *pMainDlg    = (CYUVPlayerDlg *)(AfxGetMainWnd());

                newRect.left     = gridRect[s32CurrGridY][s32CurrGridX].left;
                newRect.right    = gridRect[s32CurrGridY][s32CurrGridX].right;
                newRect.top  = gridRect[s32CurrGridY][s32CurrGridX].top;
                newRect.bottom   = gridRect[s32CurrGridY][s32CurrGridX].bottom;

                if (pMainDlg->u8PlayMode == COMP_MODE) {
                    if (pMainDlg->pImage[0] != NULL) {
                        pMainDlg->pImage[0]->MBInfoDlg.u8ShowMark       = u8ShowMark;
                        pMainDlg->pImage[0]->MBInfoDlg.s32MarkGridX     = s32CurrGridX;
                        pMainDlg->pImage[0]->MBInfoDlg.s32MarkGridY     = s32CurrGridY;
                        pMainDlg->pImage[0]->MBInfoDlg.newRect          = newRect;

                        pMainDlg->pImage[0]->MBInfoDlg.mark_selected_pixel();
                    }
                    if (pMainDlg->pImage[1] != NULL) {
                        pMainDlg->pImage[1]->MBInfoDlg.u8ShowMark       = u8ShowMark;
                        pMainDlg->pImage[1]->MBInfoDlg.s32MarkGridX     = s32CurrGridX;
                        pMainDlg->pImage[1]->MBInfoDlg.s32MarkGridY     = s32CurrGridY;
                        pMainDlg->pImage[1]->MBInfoDlg.newRect          = newRect;

                        pMainDlg->pImage[1]->MBInfoDlg.mark_selected_pixel();
                    }
                    if (pMainDlg->bShowDiffPic == TRUE) {
                        pMainDlg->diffPic.MBInfoDlg.u8ShowMark      = u8ShowMark;
                        pMainDlg->diffPic.MBInfoDlg.s32MarkGridX    = s32CurrGridX;
                        pMainDlg->diffPic.MBInfoDlg.s32MarkGridY    = s32CurrGridY;
                        pMainDlg->diffPic.MBInfoDlg.newRect         = newRect;

                        pMainDlg->diffPic.MBInfoDlg.mark_selected_pixel();
                    }
                } else {
                    s32MarkGridX     = s32CurrGridX;
                    s32MarkGridY     = s32CurrGridY;

                    mark_selected_pixel();
                }
            }
        }
    }

    CDialog::OnMouseMove(nFlags, point);
}

void CMBInfoDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default

    if ((point.x > gridRect[0][0].right) && (point.x < gridRect[0][16].right - 1)
        && (((point.y > gridRect[0][0].bottom) && (point.y < (gridRect[16][0].bottom - 1)))
            || ((point.y > gridRect[17][0].bottom) && (point.y < (gridRect[25][0].bottom - 1))))) {
        u8ShowMark   = !u8ShowMark;

        int32   s32CurrGridX     = (point.x - s32PixTableX) / s32GridWidth;
        int32   s32CurrGridY     = (point.y - s32PixTableY) / s32GridHeight;

        if (u8ShowMark == TRUE) {
            if (point.y > gridRect[17][0].bottom) {
                s32CurrGridY    -= 1;
            }

            CYUVPlayerDlg   *pMainDlg    = (CYUVPlayerDlg *)(AfxGetMainWnd());

            newRect.left     = gridRect[s32CurrGridY][s32CurrGridX].left;
            newRect.right    = gridRect[s32CurrGridY][s32CurrGridX].right;
            newRect.top      = gridRect[s32CurrGridY][s32CurrGridX].top;
            newRect.bottom   = gridRect[s32CurrGridY][s32CurrGridX].bottom;

            //++ ���ѡ�����ص�
            if (pMainDlg->u8PlayMode == COMP_MODE) {
                if (pMainDlg->pImage[0] != NULL) {
                    pMainDlg->pImage[0]->MBInfoDlg.u8ShowMark       = u8ShowMark;
                    pMainDlg->pImage[0]->MBInfoDlg.s32MarkGridX     = s32CurrGridX;
                    pMainDlg->pImage[0]->MBInfoDlg.s32MarkGridY     = s32CurrGridY;
                    pMainDlg->pImage[0]->MBInfoDlg.newRect          = newRect;

                    pMainDlg->pImage[0]->MBInfoDlg.mark_selected_pixel();
                }
                if (pMainDlg->pImage[1] != NULL) {
                    pMainDlg->pImage[1]->MBInfoDlg.u8ShowMark       = u8ShowMark;
                    pMainDlg->pImage[1]->MBInfoDlg.s32MarkGridX     = s32CurrGridX;
                    pMainDlg->pImage[1]->MBInfoDlg.s32MarkGridY     = s32CurrGridY;
                    pMainDlg->pImage[1]->MBInfoDlg.newRect          = newRect;

                    pMainDlg->pImage[1]->MBInfoDlg.mark_selected_pixel();
                }
                if (pMainDlg->bShowDiffPic == TRUE) {
                    pMainDlg->diffPic.MBInfoDlg.u8ShowMark      = u8ShowMark;
                    pMainDlg->diffPic.MBInfoDlg.s32MarkGridX    = s32CurrGridX;
                    pMainDlg->diffPic.MBInfoDlg.s32MarkGridY    = s32CurrGridY;
                    pMainDlg->diffPic.MBInfoDlg.newRect         = newRect;

                    pMainDlg->diffPic.MBInfoDlg.mark_selected_pixel();
                }
            } else {
                s32MarkGridX     = s32CurrGridX;
                s32MarkGridY     = s32CurrGridY;

                mark_selected_pixel();
            }
        } else {
            //++ ������ʷѡ�����ص���
            CYUVPlayerDlg   *pMainDlg    = (CYUVPlayerDlg *)(AfxGetMainWnd());

            if (pMainDlg->u8PlayMode == COMP_MODE) {
                if (pMainDlg->pImage[0] != NULL) {
                    pMainDlg->pImage[0]->MBInfoDlg.u8ShowMark    = u8ShowMark;
                    pMainDlg->pImage[0]->MBInfoDlg.clean_mark();
                }
                if (pMainDlg->pImage[1] != NULL) {
                    pMainDlg->pImage[1]->MBInfoDlg.u8ShowMark    = u8ShowMark;
                    pMainDlg->pImage[1]->MBInfoDlg.clean_mark();
                }
                if (pMainDlg->bShowDiffPic == TRUE) {
                    pMainDlg->diffPic.MBInfoDlg.u8ShowMark   = u8ShowMark;
                    pMainDlg->diffPic.MBInfoDlg.clean_mark();
                }
            } else {
                clean_mark();
            }
        }
    }

    CDialog::OnLButtonDown(nFlags, point);
}

void CMBInfoDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    CYUVPlayerDlg   *pMainDlg    = (CYUVPlayerDlg *)(AfxGetMainWnd());


    //++ ������ʷѡ�����ص���
    clean_mark();

    u8ValueMode  = !u8ValueMode;
    if (pMainDlg->u8PlayMode == COMP_MODE) {
        if (pMainDlg->pImage[0] != NULL) {
            pMainDlg->pImage[0]->MBInfoDlg.u8ValueMode   = u8ValueMode;
            pMainDlg->pImage[0]->MBInfoDlg.draw_pixel_value();
        }
        if (pMainDlg->pImage[1] != NULL) {
            pMainDlg->pImage[1]->MBInfoDlg.u8ValueMode   = u8ValueMode;
            pMainDlg->pImage[1]->MBInfoDlg.draw_pixel_value();
        }
        if (pMainDlg->bShowDiffPic == TRUE) {
            pMainDlg->diffPic.MBInfoDlg.u8ValueMode  = u8ValueMode;
            pMainDlg->diffPic.MBInfoDlg.draw_pixel_value();
        }
    } else {
        draw_pixel_value();
    }

    CDialog::OnRButtonDown(nFlags, point);
}

void CMBInfoDlg::OnClose()
{
    // TODO: Add your message handler code here and/or call default
    CYUVPlayerDlg   *pMainDlg    = (CYUVPlayerDlg *)(AfxGetMainWnd());
    CDiffPicDlg     *pCurrWnd    = (CDiffPicDlg *)pParentWnd;


    ShowWindow(SW_HIDE);
    pMainDlg->bShowMBInfo       = FALSE;
    //++ �������ֵ��ͼ�񴰿��ϵĺ����
    pCurrWnd->s32ViewBlkX       = -100;
    pCurrWnd->s32ViewBlkY       = -100;
    pCurrWnd->s32PrevBlkX       = -100;
    pCurrWnd->s32PrevBlkY       = -100;
    pCurrWnd->Invalidate();
    pCurrWnd->UpdateWindow();
}

BOOL CMBInfoDlg::PreTranslateMessage(MSG *pMsg)
{
    // TODO: Add your specialized code here and/or call the base class
    if (pMsg->message == WM_KEYDOWN) { //++ �ж��Ƿ��а�������
        CYUVPlayerDlg   *pMainDlg    = (CYUVPlayerDlg *)(AfxGetMainWnd());

        switch (pMsg->wParam) {
        case VK_SPACE:
        case VK_HOME:
        case VK_PRIOR:
        case VK_NEXT:
        case VK_UP:
        case VK_DOWN:
        case VK_R:
            ::PostMessage(pMainDlg->m_hWnd, WM_MYMESSAGE_3, pMsg->message, pMsg->wParam);

            return TRUE;
            break;

        case VK_ESCAPE:
            pMainDlg->hide_MBinfo_dlg();
        case VK_RETURN:

            return TRUE;
            break;

        default:
            if ((pMsg->wParam >= VK_A) && (pMsg->wParam <= VK_Z)) {
                ::PostMessage(pMainDlg->m_hWnd, WM_MYMESSAGE_3, pMsg->message, pMsg->wParam);

                return TRUE;
            }

            break;
        }
    }

    return CDialog::PreTranslateMessage(pMsg);
}
