#include <bits/stdc++.h>

using namespace std;

//convert string to int
int string_to_int(string s) {
    stringstream geek(s);
    int x = 0;
    geek >> x;
    return x;
}

//class stack created
class Stack {
public:
    int top, count=0;

    stack <string> arr;
    Stack() { top = -1; } //initializing empty stack;

    void push(string x);
    string Pop();
    void operationHelper(string operation);
    void add();
    void sub();
    void mul();
    void expression();
};

void Stack::push(string x) {
    arr.push(x); //add the element into the array
    top++; //increase top by one;
}

string Stack::Pop() {
    if (top < 0) {
        cout << "Stack Underflow"; //if stack is empty
        return 0;
    }
    else {
        string x = arr.top();  //top element in the string
        arr.pop(); //remove the top element
        top--; //decrease the top value;
        return x;
    }
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
void swap(Stack &s) {
    string a = s.Pop();
    string b = s.Pop();
    s.push(a);
    s.push(b);
}

int main() {
    Stack s;
    int n;
    string val;
    s = Stack();

    cout << "Enter operation name: " << endl;
    cout << "  PUSH: Push an integer, N, to the stack" << endl;
    cout << "  ADD: Add values from the stack" << endl;
    cout << "  SUB: Subtract values from the stack" << endl;
    cout << "  MUL: Multiply values from the stack" << endl;
    cout << "  SWAP: Swap values from the stack" << endl;
    cout << "  END: Enter END when finished with commands\n" << endl;

    while (1) {
        string op;
        cin >> op;
        if (op == "PUSH") {
            cout << "Enter integer to be pushed: ";
            cin >> val;
            s.push(val);
        } else if (op == "ADD") {
            s.add();
        } else if (op == "SUB") {
            s.sub();
        } else if (op == "MUL") {
            s.mul();
        } else if (op == "SWAP") {
            swap(s);
        } else if (op == "END") {
            break;
        }
    }
    s.expression();
}