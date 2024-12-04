#pragma once
#include "Duongdua.h"      
#include "Xe.h"             
#include "ChuongngaiVat.h"  

class CChildView : public CWnd {
public:
    CChildView();  // Constructor khởi tạo đối tượng

protected:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs); // Phương thức tạo cửa sổ, điều chỉnh các thuộc tính của cửa sổ

public:
    virtual ~CChildView(); // Destructor

protected:
    afx_msg void OnPaint();  // Phương thức vẽ các đối tượng (đường đua, xe, chướng ngại vật)
    afx_msg void OnTimer(UINT_PTR nIDEvent); // Xử lý sự kiện timer, cập nhật game
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags); // Xử lý sự kiện bàn phím
    afx_msg void OnSetFocus(CWnd* pOldWnd); // Xử lý khi cửa sổ nhận được tiêu điểm
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct); // Xử lý khi cửa sổ được tạo
    DECLARE_MESSAGE_MAP() 
private:
    Duongdua d1;                // Đối tượng đường đua
    xe xe1;                      // Đối tượng xe
    ChuongngaiVat obstacle;      // Đối tượng chướng ngại vật
    bool gameComplete;          // Biến trạng thái game
    int obstaclesCleared;   // Số chướng ngại vật đã vượt qua
    float scrollSpeed;      // Tốc độ cuộn chướng ngại vật
};