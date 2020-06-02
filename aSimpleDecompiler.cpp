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
    int top;

    vector <string> arr;
    Stack() { top = -1; } //initializing empty stack;

    void push(string x);
    string Pop();
    int size_of_stack();
    bool isEmpty();
    void add();
    void sub();
    void mul();
    void expression();
};

void Stack::push(string x) {
    arr.push_back(x); //add the element into the array
    top++; //increase top by one;
}

string Stack::Pop() {
    if (top < 0) {
        cout << "Stack Underflow"; //if stack is empty
        return 0;
    }
    else {
        string x = arr[top];  //top element in the string
        arr.pop_back(); //remove the top element
        top--; //decrease the top value;
        return x;
    }
}

int Stack::size_of_stack() {
    return arr.size(); //current size of stack;
}

bool Stack::isEmpty() {
    return (top < 0);
}

// add the top 2 elements in the stack, if less than 2 elements present create a variable and use it 
void Stack::add() {
    int size = arr.size();
    //size >=2
    if (size >= 2) {
        int last = string_to_int(arr[top]); //take top element from the stack
        top--;
        arr.pop_back(); //remove top element
        int s_last = string_to_int(arr[top]); //take new top element
        top--;
        arr.pop_back();  //remove top element
        string stri = to_string(last + s_last);
        arr.push_back(stri); //push sum of top two element into the stack
        top++;
    }
        //if only one element present
    else if (size == 1) {
        string last = arr[top];
        arr.pop_back();
        arr.push_back("(x" + to_string(size) + "+" + last + ")");
    }
        //if no element present
    else {
        arr.push_back("(x" + to_string(size) + "+" + "x" + to_string(size + 1) + ")");
        top++;
    }

}

// Subtract the top 2 elements in the stack, if less than 2 elements present create a variable and use it
void Stack::sub() {
    int size = arr.size();
    if (size >= 2) {
        int last = string_to_int(arr[top]);
        top--;
        arr.pop_back();
        int s_last = string_to_int(arr[top]);
        top--;
        arr.pop_back();
        string stri = to_string(last - s_last);
        arr.push_back(stri);
        top++;
    } else if (size == 1) {
        string last = arr[top];
        arr.pop_back();
        arr.push_back("(x" + to_string(size) + "-" + last + ")");
    } else {
        arr.push_back("(x" + to_string(size) + "-" + "x" + to_string(size + 1) + ")");
        top++;
    }

}
// multiply the top 2 elements in the stack, if less than 2 elements present create a variable and use it 

void Stack::mul() {
    int size = arr.size();
    if (size >= 2) {
        int last = string_to_int(arr[top]);
        top--;
        arr.pop_back();
        int s_last = string_to_int(arr[top]);
        top--;
        arr.pop_back();
        string stri = to_string(last * s_last);
        arr.push_back(stri);
        top++;
    } else if (size == 1) {
        string last = arr[top];
        arr.pop_back();
        arr.push_back("(x" + to_string(size) + "*" + last + ")");

    } else {
        arr.push_back("(x" + to_string(size) + "*" + "x" + to_string(size + 1) + ")");
        top++;
    }
}

//swap top two element
void swap(Stack &s) {
    string a = s.Pop();
    string b = s.Pop();
    s.push(a);
    s.push(b);

}

//print the stack
void Stack::expression() {

    for (int i = arr.size(); i >= 0; i--) {
        cout << arr[i] << endl;
    }
}

int main() {
    Stack s;
    int n;
    string val;
    s = Stack();

    while (1) {
        cout << "Enter operation name:";
        string op;
        cin >> op;
        if (op == "PUSH") {
            cout << "Enter value to be pushed";
            cin >> val;
            s.push(val);
        } else if (op == "POP") {
            s.Pop();
        } else if (op == "ADD") {
            s.add();
        } else if (op == "SUB") {
            s.sub();
        } else if (op == "MUL") {
            s.mul();
        } else if (op == "SWAP") {
            swap(s);
        } else {
            break;
        }
    }
    if(s.size_of_stack()){
        s.expression();
    }
}