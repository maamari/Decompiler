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
    void combinationHelper(vector<string> &currentStr, int firstIntIndex, string operation);
    vector<string> parenthesesHelper(vector<string> currentStr, int openParenIndex, string operation);
    string simplify();

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

//  Combines like terms within the already "simplified" expression
void Stack::combinationHelper(vector<string> &currentStr, int firstIntIndex, string operation) {
    // First multiplicative ints
    int combinedTerms = stoi(currentStr[firstIntIndex]);
    // Indexer for this loop
    int indexer = firstIntIndex+1;

    // Loop through string and combine all multiplicative terms
    while(indexer < currentStr.size()) {
        bool deletionFlag = false;
        bool currentIsDigit = isdigit(currentStr[indexer][0]);
        bool prevIsMult = (currentStr[indexer-1] == "*");
        bool prevIsAddSub = ((currentStr[indexer-1] == "+") || (currentStr[indexer-1] == "-"));
        bool atEnd = (indexer == (currentStr.size()-1));

        // If multiplication and the current char is an int and the previous term
        // is multiplication and we're not multiplying by 1
        if(operation == "*" && currentIsDigit && prevIsMult && currentStr[indexer] != "1") {
            combinedTerms *= stoi(currentStr[indexer]);
            currentStr.erase(currentStr.begin() + indexer);
            currentStr.erase(currentStr.begin() + indexer-1);
            deletionFlag = true;
        }

        // If current value is preceded by +/- and we're at the end or the next value
        // is not * -> valid term -> add to the sum
        else if(operation == "+-" && currentIsDigit && prevIsAddSub && (atEnd || currentStr[indexer+1] != "*")) {
            if(currentStr[indexer-1] == "+")
                combinedTerms += stoi(currentStr[indexer]);
            if(currentStr[indexer-1] == "-")
                combinedTerms -= stoi(currentStr[indexer]);
            currentStr.erase(currentStr.begin() + indexer-1);
            currentStr.erase(currentStr.begin() + indexer-1);
            deletionFlag = true;
        }

        currentStr[firstIntIndex] = to_string(combinedTerms);
        indexer++;
        if(deletionFlag)
            indexer -= 2;
    }
}

//  Takes care of parenthesis, namely focused on correctly carrying out
//  cases in which parentheses are preceded by "-" or "*"
vector<string> Stack::parenthesesHelper(vector<string> currentStr, int openParenIndex, string operation) {
    int tempIndex = openParenIndex+2;
    // Until we reach the close paren
    while(currentStr[tempIndex] != ")") {
        // Switch the operator sign if "-(...)"
        if(operation == "-" && (currentStr[tempIndex] == "+" || currentStr[tempIndex] == "-")) {
            if(currentStr[tempIndex] == "+")
                currentStr[tempIndex] = "-";
            else if(currentStr[tempIndex] == "-")
                currentStr[tempIndex] = "+";
            tempIndex++;
        }

        // Multiply the term before the * with the term after the operator if "*(...)"
        else if(operation == "*" && (currentStr[tempIndex] == "+" || currentStr[tempIndex] == "-")) {
            currentStr.insert(currentStr.begin() + tempIndex+1, "*");
            currentStr.insert(currentStr.begin() + tempIndex+1, currentStr[openParenIndex-2]);
        }
        tempIndex++;
    }

    return currentStr;
}

string Stack::simplify() {
    // Take in unsimplified input from expression()
    string inputString = expression();

    // Covert it to a vector
    vector<string> stringVec;
    for(int i = 0; i < inputString.length(); i++) {
        string temp;
        temp += inputString[i];
        stringVec.push_back(temp);
    }
    // Combine two or more digits
    // Ex: ['(','1','2','+','1',')'] -> ['(','12','+','1',')']
    int index = 0;
    while(index < stringVec.size()) {
        while(index >= 0 && (index+1 < stringVec.size())
              && isdigit((int)stringVec[index][0]) &&
              isdigit((int)stringVec[index+1][0]))
        {
            stringVec[index] += stringVec[index+1];
            stringVec.erase(stringVec.begin() + index+1);
            index -= 1;
        }
        index += 1;
    }

    // While there are open parentheses
    while(find(stringVec.begin(), stringVec.end(), "(") != stringVec.end()) {
        // Flip the string so that and  find the first open paren index
        // Ex: Original string = "(a+(b+c))", Flipped = "))c+b(+a("
        auto rit = std::find(stringVec.rbegin(), stringVec.rend(), "(");
        int openParenIndex = std::distance(begin(stringVec), rit.base()) -1;

        // If we are dealing with "-(....)" case
        // Switch the operator sign if + or -
        if(openParenIndex > 0 && stringVec[openParenIndex-1] == "-")
            stringVec = parenthesesHelper(stringVec, openParenIndex, "-");

        // If we are dealing with *(...) case
        else if(openParenIndex > 0 && stringVec[openParenIndex-1] == "*")
            stringVec = parenthesesHelper(stringVec, openParenIndex, "*");

        // Delete parenthesis pairing
        stringVec.erase(stringVec.begin() + openParenIndex);
        auto it = std::find(stringVec.begin(), stringVec.end(), ")");
        stringVec.erase(it);
    }

    // Delete *1 cases
    index = 0;
    while(index < stringVec.size())
    {
        bool deletionFlag = false;
        // If current is a digit (necessary check for the next condition, otherwise error thrown)
        // and this digit is an int which is preceded by * -> delete the *1
        if(index > 0 && isdigit(stringVec[index][0]) &&
           stringVec[index] == "1" && stringVec[index-1] == "*")
        {
            stringVec.erase(stringVec.begin() + index);
            stringVec.erase(stringVec.begin() + index-1);
            deletionFlag = true;
        }
        index += 1;
        if(deletionFlag)
            index -= 2;
    }

    // Find first multiplicative integer
    bool multIntExists = false;
    int firstIntIndex = 0;
    index = 1;
    while(index < stringVec.size()) {
        // If previous index is int and next index yields *
        // Mark as first int
        if(index > 0 && isdigit(stringVec[index-1][0]) && stringVec[index] == "*") {
            firstIntIndex = index-1;
            multIntExists = true;
            break;
        }
        index++;
    }

    // Combine multiplicative ints
    if(multIntExists)
        combinationHelper(stringVec,firstIntIndex,"*");

    // Find first additive/subtractive int
    bool intExists = false;
    index = 0;
    while(index < stringVec.size()) {
        bool currentIsDigit = isdigit(stringVec[index][0]);
        bool nextIsOperator = ((index+1) < stringVec.size() && (stringVec[index+1] == "+" || stringVec[index+1] == "-"));
        bool previousWasOperator = (index >0 && (stringVec[index-1] == "+" || stringVec[index-1] == "-"));
        bool atBeginning = (index == 0);

        // If the current value is an int followed by an operator and it's either at the beginning
        // or preceded by an int, then that is the first int!
        if(currentIsDigit && nextIsOperator && (atBeginning || previousWasOperator)) {
            firstIntIndex = index;
            intExists = true;
            break;
        }
        index++;
    }

    // If we have additive/subtractive int
    if(intExists)
        combinationHelper(stringVec, firstIntIndex, "+-");

    // Delete +/- 0 cases
    index = 0;
    while(index < stringVec.size()) {
        int toDelete = 0;
        if(isdigit(stringVec[index][0])) {
            if(stoi(stringVec[index]) == 0) {
                bool atBeginning = (index == 0);
                bool atEnd = (index == (stringVec.size()-1));
                bool nextOperPos = false;
                bool nextOperNeg = false;
                if((index+1 < stringVec.size())) {
                    if(stringVec[index+1] == "+")
                        nextOperPos = true;
                    if(stringVec[index+1] == "-")
                        nextOperNeg = true;
                }
                bool prevIsOper = false;
                if(index > 0 && (stringVec[index-1] == "+" || stringVec[index-1] == "-"))
                    prevIsOper = true;

                // If "0+..."
                if(atBeginning && (nextOperPos || nextOperNeg)) {
                    stringVec.erase(stringVec.begin() + index);
                    toDelete++;
                    if(nextOperPos) {
                        stringVec.erase(stringVec.begin() + index);
                        toDelete++;
                    }
                }

                // If "...+0" or "...+0+..."
                else if((atEnd && prevIsOper) || (prevIsOper && (nextOperPos || nextOperNeg))) {
                    stringVec.erase(stringVec.begin() + index-1);
                    stringVec.erase(stringVec.begin() + index-1);
                    toDelete = 2;
                }
            }
        }
        index++;
        if(toDelete > 0)
            index -= toDelete;
    }

    // Purely aesthetic but make sure ints are at the beginning of products
    index = stringVec.size() - 2;
    while(index > 0) {
        bool currIsOper = (stringVec[index] == "*");
        bool nextIsInt = isdigit(stringVec[index+1][0]);
        bool prevIsNotInt = !isdigit(stringVec[index-1][0]);

        // If "var*int"
        if(currIsOper && nextIsInt && prevIsNotInt) {
            // Swap var and int positions
            string temp = stringVec[index-1];
            stringVec[index-1] = stringVec[index+1];
            stringVec[index+1] = temp;
        }
        index--;
    }

    string result;
    for(int i = 0; i < stringVec.size(); i++)
        result += stringVec[i];
    return result;
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
        } else if (inputs[0] == "PUSH" && inputs.size()>1) {
            s.stck.push(inputs[1]);
        }
        // If unrecognized operation is provided, print error message
        else {
            cout << "Keyword not recognized. Please request either: PUSH <N>, ADD, SUB, MUL, SWAP, or END.\n" << endl;
        }
    }

    // If something lives on the stack, output it
    cout << "Would you like the output simplified? (Enter Y|N): ";
    char simplifyQuery;
    cin >> simplifyQuery;
    if (toupper(simplifyQuery) == 'Y' &&  s.stck.size() > 0) {
        cout << s.simplify() << endl;
    }
    else if (toupper(simplifyQuery) == 'N' && s.stck.size() > 0) {
        cout << s.expression() << endl;
    }
    else if (s.stck.size() > 0) {
        cout << "Invalid entry.\n" << s.expression() << " = " << s.simplify() << endl;
    }
}