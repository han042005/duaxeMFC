#include "pch.h"
#include "xe.h"
#include "vector"

// Constructor mặc định
xe::xe() : Hcn(), mauxe(RGB(255, 255, 255)), tocdo() {}

// Constructor với tham số
xe::xe(int x1, int y1, int x2, int y2, COLORREF mauxe, int tocdo)
    : Hcn(x1, y1, x2, y2), mauxe(mauxe), tocdo(tocdo) {
}

// Phương thức setX di chuyển xe và kiểm tra phạm vi của đường đua
void xe::setX(int newX1, int newX2, int roadLeft, int roadRight)
{
    if (newX1 >= roadLeft && newX2 <= roadRight) {
        x1 = newX1;
        x2 = newX2;
    }
}

// Getter cho x1
int xe::getX1() const { return x1; }

// Getter cho x2
int xe::getX2() const { return x2; }

// Setter cho màu xe
void xe::setmauxe(COLORREF mauxe) {
    this->mauxe = mauxe;
}

// Setter cho tốc độ xe
void xe::settocdo(int tocdo) {
    if (tocdo > 0) {  // Đảm bảo tốc độ dương
        this->tocdo = tocdo / 2;  // Giảm tốc độ đi 2 lần
    }
    else {
        this->tocdo = tocdo;  // Tốc độ âm hoặc bằng 0 giữ nguyên
    }
}

// Phương thức vẽ xe
void xe::drawPaint(CPaintDC* pdc)
{
    CBrush brush(mauxe);  // Tạo brush với màu xe
    CBrush* oldBrush = pdc->SelectObject(&brush);
    /* pdc->Rectangle(x1, y1, x2, y2); */ // Vẽ hình chữ nhật (xe)
    pdc->SelectObject(oldBrush);

    // Kiểm tra xem hình ảnh đã được tải chưa
    if (m_image.IsNull()) {
        // Tải hình ảnh nếu chưa tải
        m_image.Load(_T("C:\\Users\\ADMIN\\Downloads\\Remove-bg.ai_1732717256696.png")); // Cập nhật đường dẫn đến ảnh
    }

    int width = x2 - x1;  // Chiều rộng của xe (theo Hcn)
    int height = y2 - y1; // Chiều cao của xe (theo Hcn)

    // Vẽ hình ảnh lên cửa sổ
    m_image.Draw(pdc->m_hDC, x1, y1, width, height);  // Vẽ hình ảnh với vị trí (x1, y1)
}


// Phương thức di chuyển xe tự động theo chiều dọc
void xe::move()
{
    y1 -= tocdo / 2;  // Di chuyển xe lên 
    y2 -= tocdo / 2;

    // Nếu xe đi ra ngoài màn hình, đưa xe về lại đầu màn hình
    if (y1 < 500) {  // Giả sử chiều cao màn hình là 600px
        y1 = 400;  // Đưa xe trở lại từ trên cùng
        y2 = y1 + 50;  // Cập nhật chiều dài xe
    }
}