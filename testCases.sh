#!/bin/sh

echo "Testing C++ implementation"
echo "--------------------------"
g++ aSimpleDecompiler.cpp -o decompiler

# Test case 1: 1+2*3
echo "PUSH 1
PUSH 2
PUSH 3
MUL
ADD
END" | ./decompiler
echo "Expected: 7"
echo ""

# Test case 2: Double digits
echo "PUSH 10
PUSH 20
ADD
END" | ./decompiler
echo "Expected: 30"
echo ""

# Test case 3: Variables
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

# Test case 4: Swapping
echo "PUSH 1
PUSH 2
SWAP
PUSH 3
MUL
ADD
END" | ./decompiler
echo "Expected: 5"
echo ""

# Test case 5: Lower-case
echo "push 1
push 2
swap
push 3
mul
add
end" | ./decompiler
echo "Expected: 5"
echo ""

# Test case 6: Pushing letters
echo "push A
push B
swap
push C
mul
add
end" | ./decompiler
echo "Expected: Errors then (x2+(x0+x1))"
echo ""

# Test case 6: No END
echo "start" | ./decompiler
echo "Expected: Errors"
echo ""
