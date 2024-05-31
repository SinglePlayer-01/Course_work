#include "MainWindow.h"

// ��������-�������� ������� ��� ��������� ����� �������� �����
LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    // ���������� �� ���� ������ ����
    case WM_SIZE:
        GetClientRect(m_hwnd, &clientRect);
        rc_platform.left = platform_x_1;
        rc_platform.top = clientRect.bottom - platform_y_1;
        rc_platform.right = platform_x_2;
        rc_platform.bottom = clientRect.bottom;
        return 0;


    // ���������� ��������� ��� ��������� �� ������ <- ->
    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_LEFT:
        {
            platform_x_1 -= 50;
            platform_x_2 -= 50;
            rc_platform.left = platform_x_1;
            rc_platform.top = clientRect.bottom - platform_y_1;
            rc_platform.right = platform_x_2;
            rc_platform.bottom = clientRect.bottom;
            InvalidateRect(m_hwnd, NULL, TRUE);
        }
        break;
        case VK_RIGHT:
        {
            platform_x_1 += 50;
            platform_x_2 += 50;
            rc_platform.left = platform_x_1;
            rc_platform.top = clientRect.bottom - platform_y_1;
            rc_platform.right = platform_x_2;
            rc_platform.bottom = clientRect.bottom;
            InvalidateRect(m_hwnd, NULL, TRUE);

        }
        break;
        }
        return 0;
    }

    case WM_CREATE:
        SetTimer(m_hwnd, 1, 16, NULL); // ������ ��� ���������� ��������
        GetClientRect(m_hwnd, &clientRect);
        break;
    case WM_TIMER:
        // ���������� ��������� ������
        ballX += ballSpeedX;
        ballY += ballSpeedY;

        // �������� ������������ � ��������� ����
        GetClientRect(m_hwnd, &clientRect);
        if (ballX - ballRadius < 0 || ballX + ballRadius > clientRect.right)
        {
            ballSpeedX = -ballSpeedX;
        }
        if (ballY - ballRadius < 0 || ballY + ballRadius > clientRect.bottom)
        {
            ballSpeedY = -ballSpeedY;
        }

        if (rc_platform.left <= ballX && ballX <= rc_platform.right && ballY + ballRadius > clientRect.bottom - 20) ballSpeedY = -ballSpeedY;


        // ����������� ����
        InvalidateRect(m_hwnd, NULL, TRUE);
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(m_hwnd, &ps);

        // ��������� ������
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 5));
        FillRect(hdc, &rc_platform, (HBRUSH)(COLOR_WINDOW + 9));
        Ellipse(hdc, ballX - ballRadius, ballY - ballRadius, ballX + ballRadius, ballY + ballRadius);

        EndPaint(m_hwnd, &ps);
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
    }
    return 0;
}