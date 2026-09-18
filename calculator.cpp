#include <iostream>

int main() {
    double a, b;
    char op;

    std::cout << "=== Simple Calculator ===\n";
    std::cout << "Enter expression (e.g. 10 + 20): ";

    if (!(std::cin >> a >> op >> b)) {
        std::cerr << "Invalid input.\n";
        return 1;
    }

    double result = 0;

    switch (op) {
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
            if (b == 0) {
                std::cerr << "Error: Division by zero.\n";
                return 1;
            }
            result = a / b;
            break;

        default:
            std::cerr << "Error: Unsupported operator '" << op << "'.\n";
            return 1;
    }

    std::cout << "Result: " << result << '\n';

    std::cout << "Press Enter to exit...";
    std::cin.ignore();
    std::cin.get();

    return 0;
}
