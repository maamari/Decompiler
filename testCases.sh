#!/bin/sh

echo "Testing C++ implementation"
echo "--------------------------"
g++ aSimpleDecompiler.cpp -o decompiler
echo "Working..."
echo ""
sleep 1

echo "Test case 1: 1+2*3"
echo "PUSH 1
PUSH 2
PUSH 3
MUL
ADD
END" | ./decompiler
echo "Expected: 7"
echo ""

echo "Test case 2: 1+2*3"
echo "PUSH 2
PUSH 3
MUL
PUSH 1
ADD
END" | ./decompiler
echo "Expected: 7"
echo ""

echo "Test case 3: 2*x+1"
echo "PUSH 2
MUL
PUSH 1
ADD" | ./decompiler
echo "Expected: (1+(x0*2))"
echo ""

echo "Test case 4: Double digits"
echo "PUSH 10
PUSH 20
ADD
END" | ./decompiler
echo "Expected: 30"
echo ""

echo "Test case 5: Variables"
echo "ADD
ADD
ADD
ADD
ADD
MUL
MUL
ADD
END" | ./decompiler
echo "Expected: (x8+(x7*(x6*(x5+(x4+(x3+(x2+(x0+x1))))))))"
echo ""

echo "Test case 6: Swapping"
echo "PUSH 1
PUSH 2
SWAP
PUSH 3
MUL
ADD
END" | ./decompiler
echo "Expected: 5"
echo ""

echo "Test case 7: Lower-case"
echo "push 1
push 2
swap
push 3
mul
add
end" | ./decompiler
echo "Expected: 5"
echo ""

echo "Test case 8: Pushing letters"
echo "push A
push B
swap
push C
mul
add
end" | ./decompiler
echo "Expected: Error then (x2+(x0+x1))"
echo ""

echo "Test case 9: No END"
echo "start" | ./decompiler
echo "Expected: Error"
echo ""

echo "Test case 10: Multiple commands one line"
echo "PUSH 1 ADD MUL
 END" | ./decompiler
echo "Expected: (x1*(x0+1))"
echo ""

echo "Test case 11: No input, end"
echo "END" | ./decompiler
echo "Expected: Nothing"
echo ""

################################################################

echo ""
echo "Testing Java implementation"
echo "--------------------------"
javac aSimpleDecompiler.java
echo "Working..."
echo ""
sleep 2

echo "Test case 1: 1+2*3"
echo "PUSH 1
PUSH 2
PUSH 3
MUL
ADD
END" | java DecompilerDriver
echo "Expected: 7"
echo ""

echo "Test case 2: 1+2*3"
echo "PUSH 2
PUSH 3
MUL
PUSH 1
ADD
END" | java DecompilerDriver
echo "Expected: 7"
echo ""

echo "Test case 3: 2*x+1"
echo "PUSH 2
MUL
PUSH 1
ADD" | java DecompilerDriver
echo "Expected: (1+(x0*2))"
echo ""

echo "Test case 4: Double digits"
echo "PUSH 10
PUSH 20
ADD
END" | java DecompilerDriver
echo "Expected: 30"
echo ""

echo "Test case 5: Variables"
echo "ADD
ADD
ADD
ADD
ADD
MUL
MUL
ADD
END" | java DecompilerDriver
echo "Expected: (x8+(x7*(x6*(x5+(x4+(x3+(x2+(x0+x1))))))))"
echo ""

echo "Test case 6: Swapping"
echo "PUSH 1
PUSH 2
SWAP
PUSH 3
MUL
ADD
END" | java DecompilerDriver
echo "Expected: 5"
echo ""

echo "Test case 7: Lower-case"
echo "push 1
push 2
swap
push 3
mul
add
end" | java DecompilerDriver
echo "Expected: 5"
echo ""

echo "Test case 8: Pushing letters"
echo "push A
push B
swap
push C
mul
add
end" | java DecompilerDriver
echo "Expected: Error then (x2+(x0+x1))"
echo ""

echo "Test case 9: No END"
echo "start" | java DecompilerDriver
echo "Expected: Error"
echo ""

echo "Test case 10: Multiple commands one line"
echo "PUSH 1 ADD MUL
END" | java DecompilerDriver
echo "Expected: Error"
echo ""

echo "Test case 11: No input, end"
echo "END" | java DecompilerDriver
echo "Expected: Nothing"
echo ""