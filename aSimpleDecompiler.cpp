#include <bits/stdc++.h>
using namespace std;

class Stack {
public:
    Stack() {}
    stack <string> stck;

    int varCounter=0; // Counter for variable names (x0, x1, etc.)
    void operationHelper(string operation);
    void add();
    void sub();
    void mul();
    void swap();
    void expression();
};

// Convert string to int
int string_to_int(string str) {
    stringstream geek(str);
    int integer = 0;
    geek >> integer;
    return integer;
}

// Print the top of the stack
void Stack::expression() {
    cout << stck.top() << endl;
}

void Stack::operationHelper(string operation) {
    int stackSize = stck.size();

	// Normal operation between two elements
    if (stackSize >= 2) {
        string firstTerm = stck.top(); // Take top element from the stack
        stck.pop(); // Remove top element
        string secondTerm = stck.top(); // Repeat
        stck.pop();
		
		// If both elements are ints
        if (string_to_int(firstTerm) && string_to_int(secondTerm)){  
            int firstTermINT = string_to_int(firstTerm);
            int secondTermINT = string_to_int(secondTerm);
            if (operation == "+"){
                string output = to_string(firstTermINT + secondTermINT);
                stck.push(output);
            } else if (operation == "-"){
                string output = to_string(firstTermINT - secondTermINT);
                stck.push(output);
            } else if (operation == "*"){
                string output = to_string(firstTermINT * secondTermINT);
                stck.push(output);
            }
        }
		// If one element is not an int
        else { 
            stck.push("("+firstTerm+operation+secondTerm+")");
        }
    }

    // Only one element on stack
    else if (stackSize == 1) {
        string firstTerm = stck.top();
        stck.pop();
        stck.push("(x" + to_string(varCounter) + operation + firstTerm + ")");
        varCounter++;
    }

    // No terms on stack
    else {
        stck.push("(x" + to_string(varCounter) + operation + "x" + to_string(varCounter+1) + ")");
        varCounter+=2;
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
    if(stck.size()>=2) {
        string a = stck.top();
        stck.pop();
        string b = stck.top();
        stck.pop();
        stck.push(a);
        stck.push(b);
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

    string inputLine, input;  // Input line, operation
    vector<std::string> inputs;  // Split up input line
    while (getline(cin, inputLine)) {  // While there is input to grab

        inputs.clear();
        stringstream ss(inputLine);

        // Split up line and push into inputs vector
        while(ss >> input)
            inputs.push_back(input);

        // Capitalize input
        for (auto &c: inputs[0]) c = toupper(c);

        /* Check that input is valid:
         * There should not be more than one input per line
         * unless the user is pushing, in which case there
         * should only be two arguments, the second being
         * the value to push */
        int numberOfInputs = inputs.size();
        if (numberOfInputs>1) {
            // If not PUSH or more than 2 operations, print error message
            if (numberOfInputs>2 || inputs[0]!="PUSH") {
                cout << "Please use one command per line (ex: PUSH 2)\n" << endl;
                continue;
            }
            // If PUSH value is invalid, print error message
            else if (!string_to_int(inputs[1])) {
                cout << "Requested PUSH with non-integer value. Please call PUSH followed by an integer (ex: PUSH 2).\n" << endl;
                continue;
            }
        }

        // Check user input against possible operations
        if (inputs[0] == "ADD") {
            s.add();
        } else if (inputs[0] == "SUB") {
            s.sub();
        } else if (inputs[0] == "MUL") {
            s.mul();
        } else if (inputs[0] == "SWAP") {
            s.swap();
        } else if (inputs[0] == "END") {
            break;
        } else if (inputs[0] == "PUSH") {
            s.stck.push(inputs[1]);
        }
        // If unrecognized operation is provided, print error message
        else {
            cout << "Keyword not recognized. Please request either: PUSH <N>, ADD, SUB, MUL, SWAP, or END.\n" << endl;
        }
    }

    // If something lives on the stack, output it
    if (s.stck.size()>0)
        s.expression();
}
