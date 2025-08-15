#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Register the window class.
    const char CLASS_NAME[]  = "Sample Window Class";

    WNDCLASS wc = { };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        "Calculator",                   // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent window
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
        );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

#define IDC_DISPLAY 100
#define IDC_BUTTON_0 101
#define IDC_BUTTON_1 102
#define IDC_BUTTON_2 103
#define IDC_BUTTON_3 104
#define IDC_BUTTON_4 105
#define IDC_BUTTON_5 106
#define IDC_BUTTON_6 107
#define IDC_BUTTON_7 108
#define IDC_BUTTON_8 109
#define IDC_BUTTON_9 110
#define IDC_BUTTON_ADD 111
#define IDC_BUTTON_SUB 112
#define IDC_BUTTON_MUL 113
#define IDC_BUTTON_DIV 114
#define IDC_BUTTON_EQL 115
#define IDC_BUTTON_CLR 116
#define IDC_BUTTON_DOT 117

#include <string>
#include <sstream>

// Global variables for calculator logic
static double operand1 = 0;
static double operand2 = 0;
static char op = 0;
static bool new_input = true;

void OnNumberClick(HWND hwnd, int number)
{
    HWND hDisplay = GetDlgItem(hwnd, IDC_DISPLAY);
    char buffer[256];
    GetWindowText(hDisplay, buffer, 256);
    std::string text(buffer);

    if (new_input)
    {
        text = "";
        new_input = false;
    }

    if (text == "0")
    {
        text = "";
    }

    text += std::to_string(number);
    SetWindowText(hDisplay, text.c_str());
}

void OnOperatorClick(HWND hwnd, char new_op)
{
    HWND hDisplay = GetDlgItem(hwnd, IDC_DISPLAY);
    char buffer[256];
    GetWindowText(hDisplay, buffer, 256);
    operand1 = std::stod(buffer);
    op = new_op;
    new_input = true;
}

void OnEqualsClick(HWND hwnd)
{
    HWND hDisplay = GetDlgItem(hwnd, IDC_DISPLAY);
    char buffer[256];
    GetWindowText(hDisplay, buffer, 256);
    operand2 = std::stod(buffer);

    double result = 0;
    if (op == '+')
    {
        result = operand1 + operand2;
    }
    else if (op == '-')
    {
        result = operand1 - operand2;
    }
    else if (op == '*')
    {
        result = operand1 * operand2;
    }
    else if (op == '/')
    {
        if (operand2 != 0)
        {
            result = operand1 / operand2;
        }
        else
        {
            MessageBox(hwnd, "Cannot divide by zero", "Error", MB_OK);
            return;
        }
    }

    std::stringstream ss;
    ss << result;
    SetWindowText(hDisplay, ss.str().c_str());
    new_input = true;
}

void OnClearClick(HWND hwnd)
{
    HWND hDisplay = GetDlgItem(hwnd, IDC_DISPLAY);
    SetWindowText(hDisplay, "0");
    operand1 = 0;
    operand2 = 0;
    op = 0;
    new_input = true;
}

void OnDotClick(HWND hwnd)
{
    HWND hDisplay = GetDlgItem(hwnd, IDC_DISPLAY);
    char buffer[256];
    GetWindowText(hDisplay, buffer, 256);
    std::string text(buffer);

    if (new_input)
    {
        text = "0";
        new_input = false;
    }

    if (text.find('.') == std::string::npos)
    {
        text += ".";
        SetWindowText(hDisplay, text.c_str());
    }
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        {
            // Create display
            CreateWindow("EDIT", "0", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_RIGHT, 10, 10, 220, 30, hwnd, (HMENU)IDC_DISPLAY, NULL, NULL);

            // Create number buttons
            CreateWindow("BUTTON", "7", WS_VISIBLE | WS_CHILD, 10, 50, 50, 50, hwnd, (HMENU)IDC_BUTTON_7, NULL, NULL);
            CreateWindow("BUTTON", "8", WS_VISIBLE | WS_CHILD, 70, 50, 50, 50, hwnd, (HMENU)IDC_BUTTON_8, NULL, NULL);
            CreateWindow("BUTTON", "9", WS_VISIBLE | WS_CHILD, 130, 50, 50, 50, hwnd, (HMENU)IDC_BUTTON_9, NULL, NULL);
            CreateWindow("BUTTON", "4", WS_VISIBLE | WS_CHILD, 10, 110, 50, 50, hwnd, (HMENU)IDC_BUTTON_4, NULL, NULL);
            CreateWindow("BUTTON", "5", WS_VISIBLE | WS_CHILD, 70, 110, 50, 50, hwnd, (HMENU)IDC_BUTTON_5, NULL, NULL);
            CreateWindow("BUTTON", "6", WS_VISIBLE | WS_CHILD, 130, 110, 50, 50, hwnd, (HMENU)IDC_BUTTON_6, NULL, NULL);
            CreateWindow("BUTTON", "1", WS_VISIBLE | WS_CHILD, 10, 170, 50, 50, hwnd, (HMENU)IDC_BUTTON_1, NULL, NULL);
            CreateWindow("BUTTON", "2", WS_VISIBLE | WS_CHILD, 70, 170, 50, 50, hwnd, (HMENU)IDC_BUTTON_2, NULL, NULL);
            CreateWindow("BUTTON", "3", WS_VISIBLE | WS_CHILD, 130, 170, 50, 50, hwnd, (HMENU)IDC_BUTTON_3, NULL, NULL);
            CreateWindow("BUTTON", "0", WS_VISIBLE | WS_CHILD, 10, 230, 110, 50, hwnd, (HMENU)IDC_BUTTON_0, NULL, NULL);

            // Create operator buttons
            CreateWindow("BUTTON", "+", WS_VISIBLE | WS_CHILD, 190, 50, 50, 50, hwnd, (HMENU)IDC_BUTTON_ADD, NULL, NULL);
            CreateWindow("BUTTON", "-", WS_VISIBLE | WS_CHILD, 190, 110, 50, 50, hwnd, (HMENU)IDC_BUTTON_SUB, NULL, NULL);
            CreateWindow("BUTTON", "*", WS_VISIBLE | WS_CHILD, 190, 170, 50, 50, hwnd, (HMENU)IDC_BUTTON_MUL, NULL, NULL);
            CreateWindow("BUTTON", "/", WS_VISIBLE | WS_CHILD, 190, 230, 50, 50, hwnd, (HMENU)IDC_BUTTON_DIV, NULL, NULL);

            // Create other buttons
            CreateWindow("BUTTON", ".", WS_VISIBLE | WS_CHILD, 130, 230, 50, 50, hwnd, (HMENU)IDC_BUTTON_DOT, NULL, NULL);
            CreateWindow("BUTTON", "C", WS_VISIBLE | WS_CHILD, 10, 290, 110, 50, hwnd, (HMENU)IDC_BUTTON_CLR, NULL, NULL);
            CreateWindow("BUTTON", "=", WS_VISIBLE | WS_CHILD, 130, 290, 110, 50, hwnd, (HMENU)IDC_BUTTON_EQL, NULL, NULL);
        }
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            switch (wmId)
            {
            case IDC_BUTTON_0: OnNumberClick(hwnd, 0); break;
            case IDC_BUTTON_1: OnNumberClick(hwnd, 1); break;
            case IDC_BUTTON_2: OnNumberClick(hwnd, 2); break;
            case IDC_BUTTON_3: OnNumberClick(hwnd, 3); break;
            case IDC_BUTTON_4: OnNumberClick(hwnd, 4); break;
            case IDC_BUTTON_5: OnNumberClick(hwnd, 5); break;
            case IDC_BUTTON_6: OnNumberClick(hwnd, 6); break;
            case IDC_BUTTON_7: OnNumberClick(hwnd, 7); break;
            case IDC_BUTTON_8: OnNumberClick(hwnd, 8); break;
            case IDC_BUTTON_9: OnNumberClick(hwnd, 9); break;
            case IDC_BUTTON_ADD: OnOperatorClick(hwnd, '+'); break;
            case IDC_BUTTON_SUB: OnOperatorClick(hwnd, '-'); break;
            case IDC_BUTTON_MUL: OnOperatorClick(hwnd, '*'); break;
            case IDC_BUTTON_DIV: OnOperatorClick(hwnd, '/'); break;
            case IDC_BUTTON_EQL: OnEqualsClick(hwnd); break;
            case IDC_BUTTON_CLR: OnClearClick(hwnd); break;
            case IDC_BUTTON_DOT: OnDotClick(hwnd); break;
            }
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // All painting occurs here, between BeginPaint and EndPaint.
            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));

            EndPaint(hwnd, &ps);
        }
        return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
