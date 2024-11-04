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

float px(100), py(100); // ���콺 ��ġ
bool isDrawing = false; // �巡�� ����
winrt::Windows::Foundation::Point startPoint; // ���� ������
std::vector<winrt::Windows::Foundation::Point> points; // ���� ����

using namespace Microsoft::Graphics::Canvas::UI::Xaml; // CanvasControl
struct winrt::Windows::UI::Color mYcol = winrt::Microsoft::UI::Colors::Green();

void winrt::App4::implementation::MainWindow::CanvasControl_Draw(winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasControl const& sender, winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasDrawEventArgs const& args)
{
    CanvasControl canvas = sender.as<CanvasControl>();

    // �� �׸���
    if (points.size() > 1) {
        for (size_t i = 1; i < points.size(); i++) {
            args.DrawingSession().DrawLine(points[i - 1], points[i], mYcol, 2);
        }
    }

    // ������ ���� �� �׸���
    args.DrawingSession().DrawEllipse(px, py, 5, 5, mYcol, 8);
}

void winrt::App4::implementation::MainWindow::CanvasControl_PointerPressed_1(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
    isDrawing = true; // �巡�� ����
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
        canvas.Invalidate(); // ĵ���� �ٽ� �׸���
    }
}

void winrt::App4::implementation::MainWindow::CanvasControl_PointerReleased_1(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
    isDrawing = false; // �巡�� ����
}

void winrt::App4::implementation::MainWindow::ColorPicker_ColorChanged(winrt::Microsoft::UI::Xaml::Controls::ColorPicker const& sender, winrt::Microsoft::UI::Xaml::Controls::ColorChangedEventArgs const& args)
{
    mYcol = args.NewColor();
    points.clear(); // ���� ���� �� ���� �ʱ�ȭ
}

