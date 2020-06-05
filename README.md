# A Simple Decompiler
## Karime Maamari
<br>

This repository contains a simple, stack-based decompiler. The implementation is provided in three languages: Python (jupyter-notebook), Java, and C++. While all three files operate in a similar manner, there are simplifiers in both the Python (jupyter-notebook) and C++ implementations but *not* in the Java implementation. 

---
### Running the code:

#### Jupyter-notebook
Before running the notebook, first make sure that you have jupyter installed on your system<br>
```pip install jupyter```


And then open the notebook<br>
```jupyter-notebook aSimpleDecompiler.ipynb```
   
Run the "Decompiler class" and "Input handler" cells by simultaneously pressing SHIFT and ENTER. After you run the "Input handler" cell, you will be prompted for an input. Please follow the format explained below in the *Input format* section.

#### C++
To run the C++ file, execute the following (replacing g++ with your given compiler):<br>
```
g++ aSimpleDecompiler.cpp -o decompiler
./decompiler
```
And enter your inputs line-by-line as explained below in the *Input format* section.

#### Java
To run the Java file, execute the following:<br>
```
javac aSimpleDecompiler.java
java DecompilerDriver.class
```
And enter your inputs line-by-line as demonstrated below.

#### Input format
Irrespective of which file you run, the input takes the following commands (entered line-by-line):
```
PUSH <N>  # Pushes the given integer, N, onto the stack
ADD       # Pops the two top values from the stack, adds them, and pushes the result
SUB       # Pops the two top values from the stack, *subtracts* them, and pushes the result
MUL       # Pops the two top values from the stack, *multiplies* them, and pushes the result
SWAP      # Swaps the top two numbers from the stack
END       # Ends the input stream and returns output
```
For example, inputting the following set of commands
```
PUSH 1
PUSH 2
PUSH 3
MUL
ADD
END
```
Will push the expression ((3*2)+1) to the top of the stack. Then the simplifier (currently implemented in the jupyter-notebook and C++) can simplify the expression at the top of the stack (in this case to 7).

---
### Test cases:

#### Jupyter-notebook
Test cases for the notebook are provided at the end of the notebook in the "Test cases" section.

#### C++, Java
The C++ and Java files can be tested with the shell scipt, testCases.sh. To run these cases, execute:<br>
```bash testCases.sh```


For each case you will see the result followed by the expected outcome. <br>
For example: <br>
```
5
Expected: 5
```

<br>

