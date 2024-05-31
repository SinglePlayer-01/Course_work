#pragma once

#include<Windows.h>
#include"BaseWindow.h"

// ������ ���������� ����
class MainWindow : public BaseWindow<MainWindow>
{
private:
	// ������ ����
	RECT clientRect;
	// ��������� ���
	int ballRadius = 20;
	int ballX = 100;
	int ballY = 100;
	int ballSpeedX = 5;
	int ballSpeedY = 5;

	// ��������� ���������
	int platform_x_1 = 0;
	int platform_x_2 = 100;
	int platform_y_1 = 20;
	int platform_y_2 = 0;
	RECT rc_platform;

public:
	PCWSTR ClassName() const { return L"MainWindow class"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

