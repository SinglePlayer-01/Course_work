#include "MainWindow.h"

// Собитійно-орієнтовна функція для створення моделі поведірки ввікна
LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    // Реагування на зміну розміра вікна
    case WM_SIZE:
        GetClientRect(m_hwnd, &clientRect);
        rc_platform.left = platform_x_1;
        rc_platform.top = clientRect.bottom - platform_y_1;
        rc_platform.right = platform_x_2;
        rc_platform.bottom = clientRect.bottom;
        return 0;


    // Переміщення платформи при реагуванні на кнопки <- ->
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
        SetTimer(m_hwnd, 1, 16, NULL); // Таймер для обновления анимации
        GetClientRect(m_hwnd, &clientRect);
        break;
    case WM_TIMER:
        // Обновление координат шарика
        ballX += ballSpeedX;
        ballY += ballSpeedY;

        // Проверка столкновения с границами окна
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


        // Перерисовка окна
        InvalidateRect(m_hwnd, NULL, TRUE);
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(m_hwnd, &ps);

        // Рисование шарика
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