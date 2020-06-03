#include <bits/stdc++.h>

using namespace std;

class Stack {
public:
    Stack() {}
    stack < string > stck;

    void operationHelper(string operation);
    void add();
    void sub();
    void mul();
    void swap();
    string expression();
    void simplify();

    int varCounter = 0; // Counter for variable names (x0, x1, etc.)
    string alphabet[26] = { "x","y","z","a","b","c","d","e","f","g","h","i",
                            "j","k","l","m","n","o","p","q","r",
                            "s","t","u","v","w"};
};

// Convert string to int
int string_to_int(string str) {
    stringstream geek(str);
    int integer = 0;
    geek >> integer;
    return integer;
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
        if (string_to_int(firstTerm) && string_to_int(secondTerm)) {
            int firstTermINT = string_to_int(firstTerm);
            int secondTermINT = string_to_int(secondTerm);
            if (operation == "+") {
                string output = to_string(firstTermINT + secondTermINT);
                stck.push(output);
            } else if (operation == "-") {
                string output = to_string(firstTermINT - secondTermINT);
                stck.push(output);
            } else if (operation == "*") {
                string output = to_string(firstTermINT * secondTermINT);
                stck.push(output);
            }
        }
        // If one element is not an int
        else {
            stck.push("(" + firstTerm + operation + secondTerm + ")");
        }
    }

    // Only one element on stack
    else if (stackSize == 1) {
        string firstTerm = stck.top();
        stck.pop();
        stck.push("(" + alphabet[varCounter] + operation + firstTerm + ")");
        varCounter++;
    }

    // No terms on stack
    else {
        stck.push("(" + alphabet[varCounter] + operation + alphabet[varCounter + 1] + ")");
        varCounter += 2;
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
    if (stck.size() >= 2) {
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

// Print the top of the stack
string Stack::expression() {
    return stck.top();
}

void Stack::simplify() {
    string str = expression();
    int len = str.length();

    // resultant string of max length equal
    // to length of input string
    char* res = new char(2*len);
    int index = 0, i = 0;

    // create empty stack
    stack<int> s;
    stack<char> g;
    s.push(0);

    while (i < len) {
        if (str[i] == '+') {
            // cout<<"++++ "<<endl;
            // If top is 1, flip the operator
            if (s.top() == 1)
                res[index++] = '-';

            // If top is 0, append the same operator
            if (s.top() == 0)
                res[index++] = '+';

        } else if (str[i] == '-') {
            // cout<<"----  "<<endl;
            if (s.top() == 1)
                res[index++] = '+';
            else if (s.top() == 0)
                res[index++] = '-';
        }
        else if(str[i]=='*'){
            if(str[i+1]=='('){
                g.push('X');
                int temp=index-1;
                while(temp>=0&&res[temp]!='+'&&res[temp]!='-'){
                    // cout<<"inserting into stack g size -- "<<g.size()<<endl;
                    g.push(res[temp]);
                    temp--;
                }
                index=temp+1;
            }
            else{
                //character ignore the *
                res[index++]='*';
            }
        }
        else if (str[i] == '(' && i == 0){
            //Do nothing
        }
        else if (str[i] == '(' && i > 0) {
            if (str[i - 1] == '-') {
                // x is opposite to the top of stack
                int x = (s.top() == 1) ? 0 : 1;
                s.push(x);
            }

                // push value equal to top of the stack
            else if (str[i - 1] == '+')
                s.push(s.top());
        }

            // If closing parentheses pop the stack once
        else if (str[i] == ')'){
            s.pop();
            //take care of g stack
            while(!g.empty()&&g.top()!='X'){
                g.pop();
            }
            if(!g.empty()&&g.top()=='X'){
                g.pop();
            }
        }
            // copy the character to the result
        else{
            if(i-1>=0&&!(str[i-1]>='x'&&str[i-1]<='x')){
                queue<char> f;
                while(!g.empty()&&g.top()!='X'){
                    ///cout<<"hello  "<<g.top()<<endl;
                    f.push(g.top());
                    g.pop();
                }
                while(!f.empty()){
                    res[index++]=f.front();
                    g.push(f.front());
                    f.pop();
                }
            }
            res[index++] = str[i];
            // cout<<"wohoo"<<endl;
        }
        i++;
    }
    res[index]='\0';
    int y=0;
    while(res[y]!=0){
        if(y>0){
            bool currentAlphabetic = (res[y] >= 'a' && res[y] <= 'z');
            bool previousAlphabetic = (res[y - 1] >= 'a' && res[y - 1] <= 'z');
            bool currentNumeric = isdigit(res[y]);
            bool previousNumeric = isdigit(res[y - 1]);
            if ((currentAlphabetic && (previousAlphabetic || previousNumeric)) ||
               ((currentNumeric && previousAlphabetic))){
                for (int j = index; j >= y; j--) {
                    res[j + 1] = res[j];
                }
                res[y] = '*';
                index++;
            }
        }
        y++;
    }
    cout << res << endl;
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

    string inputLine, input; // Input line, operation
    vector < std::string > inputs; // Split up input line
    while (getline(cin, inputLine)) { // While there is input to grab

        inputs.clear();
        stringstream ss(inputLine);

        // Split up line and push into inputs vector
        while (ss >> input)
            inputs.push_back(input);

        // Capitalize input
        for (auto & c: inputs[0]) c = toupper(c);

        /* Check that input is valid:
         * There should not be more than one input per line
         * unless the user is pushing, in which case there
         * should only be two arguments, the second being
         * the value to push */
        int numberOfInputs = inputs.size();
        if (numberOfInputs > 1) {
            // If not PUSH or more than 2 operations, print error message
            if (numberOfInputs > 2 || inputs[0] != "PUSH") {
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
    if (s.stck.size() > 0) {
        cout << s.expression() << endl;
//        s.simplify();
    }
}
