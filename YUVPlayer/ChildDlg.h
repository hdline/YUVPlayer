#ifndef _CHILDDLG_H_
#define _CHILDDLG_H_


#include "define.h"
#include "MBInfoDlg.h"


class CChildDlg : public CDialog
{
public:
    CChildDlg(UINT nID, CWnd* pParent /*=NULL*/);

    int8	s8DlgIdx;
	uint8	bSizeChanged;	//++ ���ڴ�С�Ƿ�ı�
    uint8   u8SampleFormat;
    int32	s32MBXNum;		//++ һ�к�����
    int32	s32MBYNum;		//++ һ�к�����
    int32	s32MBXIdx;		//++ ��ǰ��������кţ�����ǰ��
    int32	s32MBYIdx;		//++ ��ǰ��������кţ�����ǰ��
    int32	s32ViewMBx;		//++ ��ʾ����ֵ�ĺ��Ķ������꣨����ǰ��
    int32	s32ViewMBy;		//++ ��ʾ����ֵ�ĺ��Ķ������꣨����ǰ��
    int32	s32ViewBlkX;	//++ ��ʾ����ֵ�ĺ��Ķ������꣨���ź�
    int32	s32ViewBlkY;	//++ ��ʾ����ֵ�ĺ��Ķ������꣨���ź�
	int32	s32ViewBlkW;
	int32	s32ViewBlkH;
    int32	s32PrevBlkX;		//++ ǰһ�����ָ��ĺ��Ķ������꣨���ź�
    int32	s32PrevBlkY;		//++ ǰһ�����ָ��ĺ��Ķ������꣨���ź�
	int32	s32PrevBlkW;
	int32	s32PrevBlkH;
    int32	s32CurrMBx;		//++ ��꾭���ĺ��Ķ������꣨����ǰ��
    int32	s32CurrMBy;		//++ ��꾭���ĺ��Ķ������꣨����ǰ��
    int32	s32CurrBlkX;	//++ ��꾭���ĺ��Ķ������꣨���ź�
    int32	s32CurrBlkY;	//++ ��꾭���ĺ��Ķ������꣨���ź�
	int32	s32CurrBlkW;
	int32	s32CurrBlkH;
    int32	s32Width;		//++ ͼ������ǰ�Ŀ��
    int32	s32Height;		//++ ͼ������ǰ�ĸ߶�
    int32	s32ZoomWidth;	//++ ͼ�����ź�Ŀ��
    int32	s32ZoomHeight;	//++ ͼ�����ź�ĸ߶�
    uint32	u32FrameSize;
    uint32	u32ChroPicSize;
    uint32	u32LumaPicSize;
    HANDLE	hloc;
    LPBITMAPINFO	BmpInfo;
    CMBInfoDlg		MBInfoDlg;
    PCRITICAL_SECTION pCriticalSection;
	/********************************************��******************************************/
    /*LPBYTE	pYUVBuff;
    LPBYTE	pRGBBuff;
    LPBYTE	pReadYUV[3];
    LPBYTE	pOrigYUV[3];
    LPBYTE	pMirrYUV[3];
    LPBYTE	pRotaYUV[3];
    LPBYTE	pDisplayLuma;
    LPBYTE	pDisplayChro;*/
	LPWORD	pYUVBuff;
	LPBYTE pRGBBuff;
	LPWORD pReadYUV[3];
	LPWORD pOrigYUV[3];
	LPWORD pMirrYUV[3];
	LPWORD pRotaYUV[3];
	LPWORD pDisplayLuma;
	LPWORD pDisplayChro;
    CString	fileName;
    CMenu	mouseMenu;
    CWnd	*pMainDlg;
    CMenu	*pSubMenu;
	CRect	wndRect; 
	CRect	newSizeRect; 
	CRect	oldSizeRect; 

    void	resize_window();
    void	get_pixel_value();
    void	set_bmp_parameter();
    void    enable_mbinfo_dlg();
    void    disable_mbinfo_dlg();
    void	remark_macroblock(CPaintDC *pDC);
    void	show_mouse_menu();
    void	mark_macroblock();
    void	show_macroblock_info();
    void	view_macroblock();
    void	color_space_convert(uint8 u8ImageMode);
	void	YV12_to_RGB24(uint16* pu8Y, uint16* pu8U, uint16* pu8V);
	void	YUY2_to_RGB24(uint16 *pu8RGBData, uint16 *pu8YUVData);
    void	set_image_mode(uint8 u8ImageMode);
    void	draw_dash_frame(CRect &rect);
	void	change_size(LPRECT pRect);
	void	change_location(LPRECT pRect);
	void	update_image();
    int32	malloc_memory();
    int32	show_image(CDC *pDC);
};


#endif