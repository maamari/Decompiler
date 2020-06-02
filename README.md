# A Simple Decompiler
## Karime Maamari
<br>

This repository contains a simple stack-based decompiler. The implementation is provided in three languages: Python (jupyter-notebook), Java, and C++. All three files operate in a similar manner and pass the same test cases. 

---
### Running the code:

#### Jupyter-notebook
To run the notebook, first make sure that you have jupyter installed on your system<br>
```pip install jupyter```


And then run the notebook<br>
```jupyter-notebook aSimpleDecompiler.ipynb```
   
Go to the cell titled "The input handler" and enter your inputs line-by-line as demonstrated below.

#### C++
To run the C++ file, execute the following (replacing g++ with your given compiler):<br>
```
g++ aSimpleDecompiler.cpp -o decompiler
./decompiler
```
And enter your inputs line-by-line as demonstrated below.

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
Will yield an output of 7

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

