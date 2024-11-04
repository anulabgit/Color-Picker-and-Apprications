# Color-Picker-and-Apprications
![스크린샷 2024-11-04 114231](https://github.com/user-attachments/assets/51ec5e84-df9c-41bc-9450-3b4b87927584)

#pragma once: 이 지시문은 헤더 파일이 여러 번 포함되는 것을 방지합니다.

#include "MainWindow.g.h": 자동 생성된 파일을 포함합니다. 이 파일은 XAML에서 정의된 UI 요소와 관련된 코드가 포함되어 있습니다.

using namespace: winrt::App4::implementation 네임스페이스를 사용하여 MainWindow 클래스를 정의합니다.

클래스 멤버 함수 선언:
- 생성자: MainWindow()는 클래스의 생성자입니다.
- 속성 관련 함수: MyProperty()와 MyProperty(int32_t value)는 속성을 설정하고 가져오는 함수입니다.
- 이벤트 핸들러: 각종 Pointer 이벤트 및 ColorPicker의 색상 변경 이벤트를 처리하는 함수들을 선언합니다.
