#include <iostream>

const int MAX_SIZE = 100;

struct Stack {
    double data[MAX_SIZE];
    int top = -1;

    void push(double value) {
        if (top < MAX_SIZE - 1) {
            data[++top] = value;
        }
        else {
            std::cerr << "ERROR" << std::endl;
        }
    }

    double pop() {
        if (top >= 0) {
            return data[top--];
        }
        else {
            std::cerr << "ERROR" << std::endl;
            return 0;
        }
    }

    bool isEmpty() const {
        return top == -1;
    }

    double peek() const {
        return top >= 0 ? data[top] : 0;
    }
};

int getPriority(char op) {
    return (op == '+' || op == '-') ? 1 : (op == '*' || op == '/') ? 2 : 0;
}

double performOperation(double a, double b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return b != 0 ? a / b : 0;
    default: return 0;
    }
}

int main() {
    std::cout << "Enter your expression (3+5*2): ";
    char expression[MAX_SIZE];
    std::cin >> expression;

    Stack nums, ops;

    for (int i = 0; expression[i] != '\0'; ++i) {
        char ch = expression[i];

        if (isdigit(ch)) {
            double num = 0;
            while (isdigit(expression[i])) {
                num = num * 10 + (expression[i] - '0');
                ++i;
            }
            nums.push(num);
            --i; 
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            while (!ops.isEmpty() && getPriority(ops.peek()) >= getPriority(ch)) {
                double b = nums.pop();
                double a = nums.pop();
                char op = static_cast<char>(ops.pop());
                nums.push(performOperation(a, b, op));
            }
            ops.push(ch);
        }
    }

    while (!ops.isEmpty()) {
        double b = nums.pop();
        double a = nums.pop();
        char op = static_cast<char>(ops.pop());
        nums.push(performOperation(a, b, op));
    }

    std::cout << "Result: " << nums.pop() << std::endl;
    return 0;
}
