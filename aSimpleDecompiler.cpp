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

    int varCounter = 0; // Counter for variable names (x,y,z,a,b,...)
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
        stck.push("(" + firstTerm + operation + secondTerm + ")");
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
    /* IN CONSTRUCTION:
     * Attempting to use a different (stack-based)
     * algorithm than that employed in the
     * jupyter-notebook; however, current approach
     * is buggy.
     */

    // Take in unsimplified input from expression()
    string str = expression();
    int len = str.length();

    // Resultant string
    char* result = new char(2*len);
    int index = 0, i = 0;

    /* Flag for "...-(...)" cases
     * Ex: a-(b-c) = a-b+c */
    stack<int> subFlag;
    subFlag.push(0);

    /* Stack for "...*(...)" cases
     * Ex: a*(b-c) = a*b-a*c */
    deque<char> mulStack;

    while (i < len) {
        cout << "currently at " << str[i] << endl;

        // Skip initial opening parenthesis
        if (str[i] == '(' && i == 0){
            i++;
            continue;
        }

        // If infamous "-(...)" case, switch on subFlag
        // This will switch the sign of operations to follow
        else if (str[i] == '(' && i > 0) {
            if (str[i - 1] == '-') {
                int flagVal = (subFlag.top() == 1) ? 0 : 1;
                subFlag.push(flagVal);
            }
        }

        // Addition
        else if (str[i] == '+') {
            /* If subFlag flag is on, that means
             * we're currently within a "-(...)"
             * so switch sign */
            if (subFlag.top() == 1){
                result[index++] = '-';
                cout << "adding -" << endl;
            }
            // Otherwise, business as usual
            if (subFlag.top() == 0) {
                result[index++] = '+';
                cout << "adding +" << endl;
            }
        }

        // Subtraction
        else if (str[i] == '-') {
            /* If subFlag flag is on, that means
             * we're currently within a "-(...)"
             * so switch sign */
            if (subFlag.top() == 1) {
                result[index++] = '+';
                cout << "adding +" << endl;
            }
                // Otherwise business as usual
            else if (subFlag.top() == 0) {
                result[index++] = '-';
                cout << "adding -" << endl;
            }
        }

        // Multiplication
        else if(str[i]=='*'){
            // If we're in a "*(...)" case
            if(str[i+1]=='('){
                // Push the flag which tells us that we're in this debacle
                // This will be read as we are popping terms off the stack later
                mulStack.push_front('X');

                /* Create traverser to iterate backwards and add values
                 * to the multiplication stack, ignoring +/- operators */
                int reverseTraverser = index-1;
                while(reverseTraverser >= 0 && result[reverseTraverser]!='+' && result[reverseTraverser]!='-'){
                    mulStack.push_front(result[reverseTraverser]);
                    reverseTraverser--;
                }
                // Deep copy was used in reverseTraverser so reset the index iterator
                index=reverseTraverser+1;
            }

            // Otherwise business as usual
            else {
                result[index++]='*';
                cout << "adding *" << endl;
            }
        }

        // Closing parenthesis
        else if (str[i] == ')'){
            // Pop the current subtraction flag
            subFlag.pop();

            // Clean out the multiplication stack
            // 'X' flag tells us when this grouping is done
            while(!mulStack.empty() && mulStack.front()!='X'){
                mulStack.pop_front();
            }
            // Pop once more to get rid off the 'X' flag
            if(!mulStack.empty() && mulStack.front()=='X'){
                mulStack.pop_front();
            }
        }

        // Otherwise
        else {
            if (i-1>=0) {
                queue<char> reverseMul;
                // Push the multiplication stack to
                // 'X' flag tells us when this grouping is done
                deque<char> tempStack = mulStack;
                while(!tempStack.empty() && tempStack.front()!='X'){
                    cout << "adding from mulstack" << mulStack.front() << endl;
                    result[index++]=tempStack.front();
                    tempStack.pop_front();
                }
            }
            cout << "adding normally " << str[i] << endl;
            result[index++] = str[i];
        }
        i++;
    }
    result[index]='\0';
    int y=0;
    while(result[y]!=0){
        if(y>0){
            bool currentAlphabetic = (result[y] >= 'a' && result[y] <= 'z');
            bool previousAlphabetic = (result[y - 1] >= 'a' && result[y - 1] <= 'z');
            bool currentNumeric = isdigit(result[y]);
            bool previousNumeric = isdigit(result[y - 1]);
            if ((currentAlphabetic && (previousAlphabetic || previousNumeric)) ||
                ((currentNumeric && previousAlphabetic))){
                for (int j = index; j >= y; j--) {
                    result[j + 1] = result[j];
                }
                result[y] = '*';
                index++;
            }
        }
        y++;
    }
    cout << result << endl;
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