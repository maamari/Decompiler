#!/bin/sh

echo "Testing C++ implementation"
echo "--------------------------"
g++ aSimpleDecompiler.cpp -o decompiler
echo "Working..."
echo ""
sleep 2

echo "Test case 1 – Simple operations: 1+2*3"
echo "PUSH 1
PUSH 2
PUSH 3
MUL
ADD
END" | ./decompiler
echo "Expected: ((3*2)+1) = 7"
echo ""

echo "Test case 2 – Simple operations: 1+2*3"
echo "PUSH 2
PUSH 3
MUL
PUSH 1
ADD
END" | ./decompiler
echo "Expected: (1+(3*2)) = 7"
echo ""

echo "Test case 3 – Simple operations: 2*x+1"
echo "PUSH 2
MUL
PUSH 1
ADD" | ./decompiler
echo "Expected: (1+(x*2)) = 1+2*x"
echo ""

echo "Test case 4 – Double digits"
echo "PUSH 10
PUSH 20
ADD
END" | ./decompiler
echo "Expected: (20+10) = 30"
echo ""

echo "Test case 5 – Many variables"
echo "ADD
ADD
ADD
ADD
ADD
MUL
MUL
ADD
END" | ./decompiler
echo "Expected: (f+(e*(d*(c+(b+(a+(z+(x+y)))))))) = f+e*d*c+e*d*b+e*d*a+e*d*z+e*d*x+e*d*y"
echo ""

echo "Test case 6 – Swapping"
echo "PUSH 1
PUSH 2
SWAP
PUSH 3
MUL
ADD
END" | ./decompiler
echo "Expected: ((3*1)+2) = 5"
echo ""

echo "Test case 7 – Lower-case, Swap"
echo "push 1
push 2
swap
push 3
mul
add
end" | ./decompiler
echo "Expected: ((3*1)+2) = 5"
echo ""

echo "Test case 8 – Pushing letters"
echo "push A
push B
swap
push C
mul
add
end" | ./decompiler
echo "Expected: Error then (z+(x+y)) = z+x*y"
echo ""

echo "Test case 9 – No end"
echo "start" | ./decompiler
echo "Expected: Error"
echo ""

echo "Test case 10 – Multiple commands one line"
echo "PUSH 1 ADD MUL
 END" | ./decompiler
echo "Expected: Error"
echo ""

echo "Test case 11 – No input"
echo "END" | ./decompiler
echo "Expected: Nothing"
echo ""

echo "Test case 12 – Negatives: 1-2"
echo "PUSH 2
PUSH 1
SUB
END" | ./decompiler
echo "Expected: (1-2) = -1"
echo ""

################################################################

echo "Test case 1 – Simple operations: 1+2*3"
echo "PUSH 1
PUSH 2
PUSH 3
MUL
ADD
END" | java DecompilerDriver
echo "Expected: ((3*2)+1)"
echo ""

echo "Test case 2 – Simple operations: 1+2*3"
echo "PUSH 2
PUSH 3
MUL
PUSH 1
ADD
END" | java DecompilerDriver
echo "Expected: (1+(3*2))"
echo ""

echo "Test case 3 – Simple operations: 2*x+1"
echo "PUSH 2
MUL
PUSH 1
ADD" | java DecompilerDriver
echo "Expected: (1+(x*2))"
echo ""

echo "Test case 4 – Double digits"
echo "PUSH 10
PUSH 20
ADD
END" | java DecompilerDriver
echo "Expected: (20+10)"
echo ""

echo "Test case 5 – Many variables"
echo "ADD
ADD
ADD
ADD
ADD
MUL
MUL
ADD
END" | java DecompilerDriver
echo "Expected: (f+(e*(d*(c+(b+(a+(z+(x+y))))))))"
echo ""

echo "Test case 6 – Swapping"
echo "PUSH 1
PUSH 2
SWAP
PUSH 3
MUL
ADD
END" | java DecompilerDriver
echo "Expected: ((3*1)+2)"
echo ""

echo "Test case 7 – Lower-case, Swap"
echo "push 1
push 2
swap
push 3
mul
add
end" | java DecompilerDriver
echo "Expected: ((3*1)+2)"
echo ""

echo "Test case 8 – Pushing letters"
echo "push A
push B
swap
push C
mul
add
end" | java DecompilerDriver
echo "Expected: Error then (z+(x+y))"
echo ""

echo "Test case 9 – No end"
echo "start" | java DecompilerDriver
echo "Expected: Error"
echo ""

echo "Test case 10 – Multiple commands one line"
echo "PUSH 1 ADD MUL
END" | java DecompilerDriver
echo "Expected: Error"
echo ""

echo "Test case 11 – No input"
echo "END" | java DecompilerDriver
echo "Expected: Nothing"
echo ""

echo "Test case 12 – Negatives: 1-2"
echo "PUSH 2
PUSH 1
SUB
END" | java DecompilerDriver
echo "Expected: (1-2)"
echo ""