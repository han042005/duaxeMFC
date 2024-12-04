#pragma once
#include "Hcn.h"
#include "afxwin.h"
#include "atlimage.h"

class xe : public Hcn {
public:
    xe();
    xe(int x1, int y1, int x2, int y2, COLORREF mauxe, int tocdo);

    void setX(int newX1, int newX2, int roadLeft, int roadRight);  // Phương thức di chuyển xe và kiểm tra phạm vi
    int getX1() const;  // Getter cho x1
    int getX2() const;  // Getter cho x2
    void setmauxe(COLORREF mauxe);  // Setter cho màu xe
    void settocdo(int tocdo);  // Setter cho tốc độ di chuyển
    void drawPaint(CPaintDC* pdc); // Vẽ xe
    void move(); // Di chuyển xe tự động theo chiều dọc
    // Phương thức kiểm tra va chạm với các chướng ngại vật

private:
    COLORREF mauxe;
    int tocdo;  // Tốc độ di chuyển của xe
    CImage m_image;  // Đối tượng CImage để lưu trữ hình ảnh xe
};

