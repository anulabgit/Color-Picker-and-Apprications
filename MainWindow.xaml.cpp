#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::App4::implementation
{
    MainWindow::MainWindow()
    {
        InitializeComponent();
    }

    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }
}

float px(100), py(100); // 마우스 위치
bool isDrawing = false; // 드래그 상태
winrt::Windows::Foundation::Point startPoint; // 선의 시작점
std::vector<winrt::Windows::Foundation::Point> points; // 선의 점들

using namespace Microsoft::Graphics::Canvas::UI::Xaml; // CanvasControl
struct winrt::Windows::UI::Color mYcol = winrt::Microsoft::UI::Colors::Green();

void winrt::App4::implementation::MainWindow::CanvasControl_Draw(winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasControl const& sender, winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasDrawEventArgs const& args)
{
    CanvasControl canvas = sender.as<CanvasControl>();

    // 선 그리기
    if (points.size() > 1) {
        for (size_t i = 1; i < points.size(); i++) {
            args.DrawingSession().DrawLine(points[i - 1], points[i], mYcol, 2);
        }
    }

    // 마지막 점에 원 그리기
    args.DrawingSession().DrawEllipse(px, py, 5, 5, mYcol, 8);
}

void winrt::App4::implementation::MainWindow::CanvasControl_PointerPressed_1(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
    isDrawing = true; // 드래그 시작
    startPoint = e.GetCurrentPoint(sender.as<CanvasControl>()).Position();
    points.push_back(startPoint);
}

void winrt::App4::implementation::MainWindow::CanvasControl_PointerMoved(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
    CanvasControl canvas = sender.as<CanvasControl>();
    if (isDrawing) {
        px = e.GetCurrentPoint(canvas).Position().X;
        py = e.GetCurrentPoint(canvas).Position().Y;
        points.push_back(winrt::Windows::Foundation::Point(px, py));
        canvas.Invalidate(); // 캔버스 다시 그리기
    }
}

void winrt::App4::implementation::MainWindow::CanvasControl_PointerReleased_1(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
    isDrawing = false; // 드래그 종료
}

void winrt::App4::implementation::MainWindow::ColorPicker_ColorChanged(winrt::Microsoft::UI::Xaml::Controls::ColorPicker const& sender, winrt::Microsoft::UI::Xaml::Controls::ColorChangedEventArgs const& args)
{
    mYcol = args.NewColor();
    points.clear(); // 색상 변경 시 선점 초기화
}

