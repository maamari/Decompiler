#include <bits/stdc++.h>
using namespace std;

//class stack created
class Stack {
public:
    Stack() {} //initializing empty stack;
    stack <string> arr;

    int count=0;
    void push(string x);
    string Pop();
    void operationHelper(string operation);
    void add();
    void sub();
    void mul();
    void swap();
    void expression();
};

//convert string to int
int string_to_int(string s) {
    stringstream geek(s);
    int x = 0;
    geek >> x;
    return x;
}

//print the stack
void Stack::expression() {
    cout << arr.top() << endl;
}

// add the top 2 elements in the stack, if less than 2 elements present create a variable and use it
void Stack::operationHelper(string operation) {
    int size = arr.size();

    if (size >= 2) {
        int last = string_to_int(arr.top()); //take top element from the stack
        arr.pop(); //remove top element
        int s_last = string_to_int(arr.top()); //take new top element
        arr.pop();  //remove top element

        if (operation == "+"){
            string stri = to_string(last + s_last);
            arr.push(stri); //push sum of top two element into the stack
        } else if (operation == "-"){
            string stri = to_string(last - s_last);
            arr.push(stri); //push sum of top two element into the stack
        } else if (operation == "*"){
            string stri = to_string(last * s_last);
            arr.push(stri); //push sum of top two element into the stack
        }
    }

    //if only one element present
    else if (size == 1) {
        string last = arr.top();
        arr.pop();
        arr.push("(x" + to_string(count) + operation + last + ")");
        count++;
    }

    //if no element present
    else {
        arr.push("(x" + to_string(count) + operation + "x" + to_string(count+1) + ")");
        count+=2;
    }
}

// add the top 2 elements in the stack, if less than 2 elements present create a variable and use it
void Stack::add() {
    operationHelper("+");
}

// Subtract the top 2 elements in the stack, if less than 2 elements present create a variable and use it
void Stack::sub() {
    operationHelper("-");
}

// multiply the top 2 elements in the stack, if less than 2 elements present create a variable and use it
void Stack::mul() {
    operationHelper("*");
}

//swap top two element
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
    Stack s;
    s = Stack();

    cout << "Enter operation name: " << endl;
    cout << "  PUSH <N>: Push an integer, N, to the stack" << endl;
    cout << "  ADD: Add values from the stack" << endl;
    cout << "  SUB: Subtract values from the stack" << endl;
    cout << "  MUL: Multiply values from the stack" << endl;
    cout << "  SWAP: Swap values from the stack" << endl;
    cout << "  END: Enter END when finished with commands\n" << endl;

    string op;
    while (cin >> op) {
        int val;
        for (auto &c: op) c = toupper(c);

        if (op == "ADD") {
            s.add();
        } else if (op == "SUB") {
            s.sub();
        } else if (op == "MUL") {
            s.mul();
        } else if (op == "SWAP") {
            s.swap();
        } else if (op == "END") {
            break;
        } else if (op == "PUSH") {
            cin >> val;
            if (cin.fail()) {
                cin.clear();
                cout << "Requested PUSH with non-integer value. Please call PUSH followed by an integer (ex: PUSH 2).\n"
                     << endl;
            } else {
                s.arr.push(to_string(val));
            }
        } else {
            cout << "Keyword not recognized. Please request either: PUSH <N>, ADD, SUB, MUL, SWAP, or END.\n" << endl;
        }
    }
    s.expression();
}
