#include "pch.h"
#include "framework.h"
#include "duaxeMFC.h"
#include "ChildView.h"
#include "ChuongngaiVat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Constructor khởi tạo đối tượng xe1, d1, obstacle
CChildView::CChildView()
    : xe1(120, 200, 150, 250, RGB(255, 0, 0), 5), // Khởi tạo xe
    d1(0, 100, 400, 700),                     // Khởi tạo đường đua
    obstacle(150, 120, 200, 150),         // Khởi tạo chướng ngại vật
    gameComplete(false)
{
   
    d1.addObstacle(ChuongngaiVat(rand() % (400 - 50), 100, rand() % (400 - 50) + 50, 150));
    d1.addObstacle(ChuongngaiVat(rand() % (400 - 50), 200, rand() % (400 - 50) + 50, 250));
    d1.addObstacle(ChuongngaiVat(rand() % (400 - 50), 300, rand() % (400 - 50) + 50, 350));
    d1.addObstacle(ChuongngaiVat(rand() % (400 - 50), 400, rand() % (400 - 50) + 50, 450));
    d1.addObstacle(ChuongngaiVat(rand() % (400 - 50), 500, rand() % (400 - 50) + 50, 550));
    d1.addObstacle(ChuongngaiVat(rand() % (400 - 50), 600, rand() % (400 - 50) + 50, 650));
    
}                      // Trạng thái game mặc định là chưa hoàn thành

CChildView::~CChildView() {}

BEGIN_MESSAGE_MAP(CChildView, CWnd)
    ON_WM_PAINT()
    ON_WM_TIMER()
    ON_WM_KEYDOWN()
    ON_WM_SETFOCUS()
    ON_WM_CREATE()
END_MESSAGE_MAP()

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) {
    if (!CWnd::PreCreateWindow(cs))
        return FALSE;

    cs.dwExStyle |= WS_EX_CLIENTEDGE;
    cs.style &= ~WS_BORDER;
    cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
        ::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), nullptr);

    return TRUE;
}

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct) {
    if (CWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    SetFocus();
    SetTimer(1, 50, nullptr); // Bắt đầu Timer (50ms/frame)
    return 0;
}

void CChildView::OnPaint() {
    CPaintDC dc(this);

    // Nếu game hoàn thành, vẽ nền hình chữ nhật
    if (gameComplete) {
        // Vẽ nền hình chữ nhật 
        CBrush backgroundBrush(RGB(169, 169, 169)); // Màu nền đường đua 
        CBrush* oldBrush = dc.SelectObject(&backgroundBrush);

        // Vẽ hình chữ nhật làm nền 
        dc.Rectangle(d1.getX1(), d1.getY1(), d1.getX2(), d1.getY2());

        // Vẽ hình ảnh vào nền
        CImage image;
        HRESULT hr = image.Load(_T("C:\\Users\\ADMIN\\Downloads\\synthwave_pixelart_by_radiantsdreams_df3ghr6-pre.jpg")); 
        if (SUCCEEDED(hr)) {
            // Vẽ hình ảnh vào cửa sổ
            image.Draw(dc.m_hDC, d1.getX1(), d1.getY1(), d1.getX2() - d1.getX1(), d1.getY2() - d1.getY1());
        }

        // Vẽ hình ảnh "Game Over" 
        CImage gameOverImage;
        hr = gameOverImage.Load(_T("C:\\Users\\ADMIN\\Downloads\\fb700da38b6873f.png")); 
        if (SUCCEEDED(hr)) {
            // Điều chỉnh kích thước hình ảnh
            int imageWidth = gameOverImage.GetWidth() / 2;  // Giảm kích thước hình ảnh
            int imageHeight = gameOverImage.GetHeight() / 2; // Giảm kích thước hình ảnh

            // Di chuyển hình ảnh 
            int yOffset = 110; // Giá trị di chuyển xuống 

            // Vẽ hình ảnh vào cửa sổ, căn giữa trong vùng và di chuyển xuống dưới
            gameOverImage.Draw(dc.m_hDC,
                (d1.getX1() + d1.getX2()) / 2 - imageWidth / 2,
                (d1.getY1() + d1.getY2()) / 2 - imageHeight / 2 + yOffset, // Thêm yOffset để di chuyển xuống
                imageWidth, imageHeight);
        }


        // Khôi phục lại cọ nền
        dc.SelectObject(oldBrush);

        return;
    }

    // Nếu game chưa kết thúc, tiếp tục vẽ đường đua và các đối tượng
    // Vẽ đường đua
    d1.draw(&dc);

    // Vẽ các chướng ngại vật
    const std::vector<ChuongngaiVat>& obstacles = d1.getObstacles(); // Lấy danh sách chướng ngại vật
    for (const auto& obstacle : obstacles) {
        obstacle.draw(&dc);  // Vẽ từng chướng ngại vật
    }

    // Vẽ xe
    xe1.drawPaint(&dc);  // Vẽ xe
}

void CChildView::OnTimer(UINT_PTR nIDEvent) {
    if (nIDEvent == 1 && !gameComplete) {
        xe1.move(); // Gọi phương thức move() của xe để di chuyển tự động
        d1.scroll(5); // Cuộn đường đua

        // Kiểm tra va chạm với từng chướng ngại vật
        const std::vector<ChuongngaiVat>& obstacles = d1.getObstacles(); // Lấy danh sách chướng ngại vật
        for (const auto& obstacle : obstacles) {
            if (obstacle.checkCollision(xe1.getX1(), xe1.getY1(), xe1.getX2(), xe1.getY2())) {
                gameComplete = true; // Dừng trò chơi khi va chạm xảy ra
                KillTimer(1); // Dừng Timer
                Invalidate(); // Vẽ lại cửa sổ
                return;  // Dừng kiểm tra va chạm khi game đã kết thúc
            }
        }

        // Kiểm tra nếu xe đi hết đường đua
        if (d1.isComplete()) {
            gameComplete = true;
            KillTimer(1); // Dừng Timer khi game hoàn thành
        }

        Invalidate(); // Vẽ lại cửa sổ sau mỗi khung hình
    }

    CWnd::OnTimer(nIDEvent);

    
}

void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
    if (gameComplete) return; // Nếu game đã kết thúc, không xử lý phím

    int roadLeft = 0;
    int roadRight = 400;

    switch (nChar) {
    case VK_LEFT: // Nhấn phím mũi tên trái
        xe1.setX(xe1.getX1() - 10, xe1.getX2() - 10, roadLeft, roadRight); // Di chuyển xe sang trái
        break;
    case VK_RIGHT: // Nhấn phím mũi tên phải
        xe1.setX(xe1.getX1() + 10, xe1.getX2() + 10, roadLeft, roadRight); // Di chuyển xe sang phải
        break;
    }

   

    Invalidate(); // Vẽ lại cửa sổ
    CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
   

        
  }


void CChildView::OnSetFocus(CWnd* pOldWnd) {
    CWnd::OnSetFocus(pOldWnd);
} 