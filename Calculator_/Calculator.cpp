#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

int main() {
    double a, b;
    char op;
    std::string input;

    std::cout << "Simple Calculator (type 'exit' to quit)\n";

    do {
        std::cout <<"\nEnter: ";
        std::getline(std::cin, input);

        if (input == "exit" || input == "quit") {
            break;
        }

        if (input.empty()) {
            continue;
        }

        std::istringstream iss(input);

        if (!(iss >> a >> op >> b) || !iss.eof()) {
            std::cout << "Invalid input!\n";
            continue;
        }
        std::cout << "\033[A";

        switch (op) {
            case '+':
                std::cout << "Answer is: " << std::fixed << std::setprecision(2) << a + b << '\n';
                break;
            case '*':
                std::cout << "Answer is: " << std::fixed << std::setprecision(2) << a * b << '\n';
                break;
            case '/':
                if (b == 0) {
                    std::cout << "You can't divide by 0!\n";
                } else {
                    std::cout << "Answer is: " << std::fixed << std::setprecision(2) << a / b << '\n';
                }
                break;
            case '-':
                std::cout << "Answer is: " << std::fixed << std::setprecision(2) << a - b << '\n';
                break;
            default:
                std::cout << "Invalid operator!\n";
        }
    } while (true);

    return 0;
}