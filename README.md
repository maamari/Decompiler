# A Simple Decompiler
## Karime Maamari
<br>

This repository contains a simple stack-based decompiler. The implementation is provided in various languages, though the jupyter-notebook (aSimpleDecompiler.ipynb) is recommended.

---
### Running the code:

#### Jupyter-notebook
To run the notebook, first make sure that you have jupyter-notebook installed on your system<br>
```pip install jupyter```


And then run the notebook<br>
```jupyter-notebook aSimpleDecompiler.ipynb```
   
#### C++
To run the C++ file, execute the following (replacing g++ with your given compiler):<br>
```g++ aSimpleDecompiler.cpp -o decompiler```
```./decompiler```

#### Java
To run the Java file, execute the following:<br>
```javac aSimpleDecompiler.java```
```java DecompilerDriver.class```


### Test cases:

#### Jupyter-notebook
Test cases for the notebook are provided at the end of the notebook in the "Test cases" section.

#### C++, Java
The C++ and Java files can be tested with the shell scipt, testCases.sh. To run these cases, execute:<br>
```bash testCases.sh```


For each case you will see the result followed by the expected outcome. For example: <br>
```5```
```Expected: 5```


The details of each test case are commented throughout the script.

<br>

