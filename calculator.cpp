#include <iostream>
#include <iomanip>
#include <limits>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

// ==================== ANSI 颜色 ====================

const std::string RESET   = "\033[0m";
const std::string BOLD    = "\033[1m";

const std::string CYAN    = "\033[36m";
const std::string GREEN   = "\033[32m";
const std::string YELLOW  = "\033[33m";
const std::string RED     = "\033[31m";
const std::string BLUE    = "\033[34m";
const std::string GRAY    = "\033[90m";

// ==================== 终端控制 ====================

// 清屏并移动光标到左上角
void clearScreen()
{
    std::cout << "\033[2J\033[H";
}

// Windows 开启 ANSI 转义序列支持
void enableANSI()
{
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    if (hOut != INVALID_HANDLE_VALUE)
    {
        DWORD mode = 0;

        if (GetConsoleMode(hOut, &mode))
        {
            mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, mode);
        }
    }
#endif
}

// ==================== UI ====================

void drawHeader()
{
    std::cout
        << CYAN
        << "╔══════════════════════════════════════════════╗\n"
        << "║                                              ║\n"
        << "║            " << BOLD << "SIMPLE CALCULATOR" << RESET << CYAN
        << "                 ║\n"
        << "║              Terminal Edition                ║\n"
        << "║                                              ║\n"
        << "╚══════════════════════════════════════════════╝\n"
        << RESET;
}

void drawMenu()
{
    std::cout
        << "\n"
        << BLUE
        << "┌──────────────────────────────────────────────┐\n"
        << "│  " << BOLD << "OPERATIONS" << RESET << BLUE
        << "                                  │\n"
        << "├──────────────────────────────────────────────┤\n"
        << "│                                              │\n"
        << "│       " << GREEN << "[ + ]" << BLUE << "  Addition"
        << "                       │\n"
        << "│       " << GREEN << "[ - ]" << BLUE << "  Subtraction"
        << "                    │\n"
        << "│       " << GREEN << "[ * ]" << BLUE << "  Multiplication"
        << "                 │\n"
        << "│       " << GREEN << "[ / ]" << BLUE << "  Division"
        << "                       │\n"
        << "│                                              │\n"
        << "├──────────────────────────────────────────────┤\n"
        << "│  " << YELLOW << "[ C ] Clear"
        << "            [ Q ] Quit" << BLUE
        << "             │\n"
        << "└──────────────────────────────────────────────┘\n"
        << RESET;
}

void drawInputBox()
{
    std::cout
        << "\n"
        << GRAY
        << "┌──────────────────────────────────────────────┐\n"
        << "│ Enter an expression                          │\n"
        << "│ Example:  10 + 20                            │\n"
        << "└──────────────────────────────────────────────┘\n"
        << RESET
        << "\n"
        << CYAN << "  > " << RESET;
}

void showResult(double a, char op, double b, double result)
{
    std::cout
        << "\n"
        << GREEN
        << "┌──────────────────────────────────────────────┐\n"
        << "│ " << BOLD << "RESULT" << RESET << GREEN
        << "                                       │\n"
        << "├──────────────────────────────────────────────┤\n"
        << RESET;

    std::cout << "\n"
              << "        "
              << YELLOW << a << RESET
              << "  " << CYAN << op << RESET
              << "  " << YELLOW << b << RESET
              << "  =  "
              << GREEN << BOLD << result << RESET
              << "\n\n";

    std::cout
        << GREEN
        << "└──────────────────────────────────────────────┘\n"
        << RESET;
}

void showError(const std::string& message)
{
    std::cout
        << "\n"
        << RED
        << "┌──────────────────────────────────────────────┐\n"
        << "│ ERROR                                        │\n"
        << "└──────────────────────────────────────────────┘\n"
        << RESET
        << RED << "  " << message << RESET << "\n";
}

// ==================== 主程序 ====================

int main()
{
    enableANSI();

    while (true)
    {
        clearScreen();

        drawHeader();
        drawMenu();
        drawInputBox();

        // 先读取第一个输入
        std::string firstInput;

        if (!(std::cin >> firstInput))
        {
            break;
        }

        // Q / q 退出
        if (firstInput == "q" || firstInput == "Q")
        {
            clearScreen();

            std::cout
                << "\n"
                << CYAN
                << "╔══════════════════════════════════════════════╗\n"
                << "║                                              ║\n"
                << "║            Thanks for using!                 ║\n"
                << "║                 Goodbye!                     ║\n"
                << "║                                              ║\n"
                << "╚══════════════════════════════════════════════╝\n"
                << RESET;

            return 0;
        }

        // C / c 清屏
        if (firstInput == "c" || firstInput == "C")
        {
            continue;
        }

        double a;

        try
        {
            size_t pos;
            a = std::stod(firstInput, &pos);

            // 防止 "123abc" 这种输入
            if (pos != firstInput.length())
            {
                throw std::invalid_argument("Invalid number");
            }
        }
        catch (...)
        {
            showError("Invalid first number.");

            std::cout << "\nPress Enter to continue...";

            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );

            std::cin.get();
            continue;
        }

        char op;
        double b;

        if (!(std::cin >> op >> b))
        {
            showError("Invalid expression.");

            std::cin.clear();

            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );

            std::cout << "\nPress Enter to continue...";
            std::cin.get();

            continue;
        }

        double result = 0;
        bool success = true;

        switch (op)
        {
            case '+':
                result = a + b;
                break;

            case '-':
                result = a - b;
                break;

            case '*':
                result = a * b;
                break;

            case '/':
                if (b == 0)
                {
                    showError("Division by zero is not allowed.");
                    success = false;
                }
                else
                {
                    result = a / b;
                }
                break;

            default:
                showError(
                    std::string("Unsupported operator: ") + op
                );
                success = false;
                break;
        }

        if (success)
        {
            showResult(a, op, b, result);
        }

        // 清掉当前输入行剩余内容
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n'
        );

        std::cout
            << "\n"
            << GRAY
            << "Press Enter to calculate again..."
            << RESET;

        std::cin.get();
    }

    return 0;
}