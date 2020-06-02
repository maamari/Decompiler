#include <bits/stdc++.h>
using namespace std;

//class stack created
class Stack {
public:
    Stack() {} //initializing empty stack;
    stack <string> arr;

    int count=0;
    void push(string integer);
    string Pop();
    void operationHelper(string operation);
    void add();
    void sub();
    void mul();
    void swap();
    void expression();
};

//convert string to int
int string_to_int(string str) {
    stringstream geek(str);
    int integer = 0;
    geek >> integer;
    return integer;
}

// Print the top of the stack
void Stack::expression() {
    cout << arr.top() << endl;
}

// Normal operation between two elements
void Stack::operationHelper(string operation) {
    int size = arr.size();

    if (size >= 2) {
        string firstTerm = arr.top(); // Take top element from the stack
        arr.pop(); // Remove top element
        string secondTerm = arr.top(); // Repeat
        arr.pop();
        if (string_to_int(firstTerm) && string_to_int(secondTerm)){  // Check whether the elements are ints
            int firstTermINT = string_to_int(firstTerm); // If so, continue with normal operation
            int secondTermINT = string_to_int(secondTerm);
            if (operation == "+"){
                string output = to_string(firstTermINT + secondTermINT);
                arr.push(output);
            } else if (operation == "-"){
                string output = to_string(firstTermINT - secondTermINT);
                arr.push(output);
            } else if (operation == "*"){
                string output = to_string(firstTermINT * secondTermINT);
                arr.push(output);
            }
        }
        else { // If one element is not an int (ex: 1+(x0*2))
            arr.push("("+firstTerm+operation+secondTerm+")");
        }
    }

    // Only one term on stack
    else if (size == 1) {
        string firstTerm = arr.top();
        arr.pop();
        arr.push("(integer" + to_string(count) + operation + firstTerm + ")");
        count++;
    }

    // No terms on stack
    else {
        arr.push("(integer" + to_string(count) + operation + "integer" + to_string(count+1) + ")");
        count+=2;
    }
}

// Add elements onto stack
void Stack::add() {
    operationHelper("+");
}

// Subtract elements onto stack
void Stack::sub() {
    operationHelper("-");
}

// Multiply elements onto stack
void Stack::mul() {
    operationHelper("*");
}

// If two elements are on the stack, swap them
void Stack::swap() {
    if(arr.size()>=2) {
        string a = arr.top();
        arr.pop();
        string b = arr.top();
        arr.pop();
        arr.push(a);
        arr.push(b);
    } else {
        cout << "Stack not large enough for swap.\n" << endl;
    }
}

int main() {
    Stack str;
    str = Stack();

    cout << "Enter operation name: " << endl;
    cout << "  PUSH <N>: Push an integer, N, to the stack" << endl;
    cout << "  ADD: Add values from the stack" << endl;
    cout << "  SUB: Subtract values from the stack" << endl;
    cout << "  MUL: Multiply values from the stack" << endl;
    cout << "  SWAP: Swap values from the stack" << endl;
    cout << "  END: Enter END when finished with commands\n" << endl;

    string op;  // Operation
    while (cin >> op) {
        int pushVal;
        // Capitalize input
        for (auto &c: op) c = toupper(c);

        if (op == "ADD") {
            str.add();
        } else if (op == "SUB") {
            str.sub();
        } else if (op == "MUL") {
            str.mul();
        } else if (op == "SWAP") {
            str.swap();
        } else if (op == "END") {
            break;
        } else if (op == "PUSH") {
            cin >> pushVal;
            // If PUSH with non-int value
            if (cin.fail()) {
                cin.clear();
                cout << "Requested PUSH with non-integer value. Please call PUSH followed by an integer (ex: PUSH 2).\n"
                     << endl;
            } else {
                str.arr.push(to_string(pushVal));
            }
        // If non-keyword arg is provided
        } else {
            cout << "Keyword not recognized. Please request either: PUSH <N>, ADD, SUB, MUL, SWAP, or END.\n" << endl;
        }
    }
    // If something lives on the stack, output it
    if (str.arr.size()>0)
        str.expression();
}
