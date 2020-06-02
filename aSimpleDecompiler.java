import java.util.*;
import java.io.*;
import java.lang.*;

class Decompiler {
    Stack < String > arr = new Stack < String > ();
    Decompiler() {}
    int count = 0;  // Counter for variable names (x0, x1, etc.)

    void operationHelper(String operation) {
        int size = arr.size();

        // Normal operation between two elements
        if (size >= 2) {
            String firstTerm = arr.peek(); // Take top element from the stack
            arr.pop();  // Pop top element off the stack
            String secondTerm = arr.peek(); // Repeat
            arr.pop();

			// Check whether both elements are ints
            try {
                int firstTermINT = Integer.parseInt(firstTerm); 
                int secondTermINT = Integer.parseInt(secondTerm); 
                if (operation.equals("+")){
                    String output = Integer.toString(firstTermINT + secondTermINT);
                    arr.push(output);
                } else if (operation.equals("-")) {
                    String output = Integer.toString(firstTermINT - secondTermINT);
                    arr.push(output);
                } else if (operation.equals("*")) {
                    String output = Integer.toString(firstTermINT * secondTermINT);
                    arr.push(output);
                }
            } 
			// If one element is not an int (ex: 1+(x0*2))
			catch (Exception e){  
                arr.push("("+firstTerm+operation+secondTerm+")"); 
            }
        }

        // Only one term on stack
        else if (size == 1) {
            String firstTerm = arr.peek();
            arr.pop();
            arr.push("(x" + Integer.toString(count) + operation + firstTerm + ")");
            count++;
        }

        // No terms on stack
        else {
            arr.push("(x" + Integer.toString(count) + operation + "x" + Integer.toString(count+1) + ")");
            count+=2;
        }
    }
    // Add elements onto stack
    void add() {
        operationHelper("+");
    }
    // Subtract elements onto stack
    void sub() {
        operationHelper("-");
    }
    // Multiply elements onto stack
    void mul() {
        operationHelper("*");
    }

    // If two elements are on the stack, swap them
    void swap() {
        if (arr.size()>=2){
            String first = arr.peek();
            arr.pop();
            String second = arr.peek();
            arr.pop();
            arr.push(first);
            arr.push(second);
        } else {
            System.out.println("Stack not large enough for swap.\n");
        }
    }

    // Prints the top item in the stack
    void expression() {
        Collections.reverse(arr);
        System.out.println(arr.peek());
    }
}

// Driver code
class DecompilerDriver {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Decompiler s = new Decompiler();

        System.out.println("Enter operation name:");
        System.out.println("  PUSH <N>: Push an integer, N, to the stack");
        System.out.println("  ADD: Add values from the stack");
        System.out.println("  SUB: Subtract values from the stack");
        System.out.println("  MUL: Multiply values from the stack");
        System.out.println("  SWAP: Swap values from the stack");
        System.out.println("  END: Enter END when finished with commands\n");

        while (true) {
            String[] inputs;

            // Check that an input exists
            try {
                String input = sc.nextLine();
                inputs = input.split(" ");
            } catch (Exception noMoreInput) {
                break;
            }

            // If more than two inputs are provided, print error message
            if (inputs.length > 2) {
                System.out.println("Please use one command per line (ex: PUSH 2)\n");
                continue;
            }

            // Capitalize input
			inputs[0] = inputs[0].toUpperCase();

            // Check input against various cases
            if (inputs[0].equals("ADD")) {
                s.add();
            } else if (inputs[0].equals("SUB")) {
                s.sub();
            } else if (inputs[0].equals("MUL")) {
                s.mul();
            } else if (inputs[0].equals("SWAP")) {
                s.swap();
            } else if (inputs[0].equals("END")) {
                break;
            } else if (inputs[0].equals("PUSH")) {
                try {
                    Integer.parseInt(inputs[1]);
                    // If PUSH without value
                    try {
                        s.arr.push(inputs[1]);
                    } catch (Exception noPushValue) {
                        System.out.println("Requested PUSH without value. Please call PUSH followed by an integer (ex: PUSH 2).\n");
                    }
                // If PUSH with non-int value
                } catch (Exception pushValueNotInt) {
					System.out.println("Requested PUSH value is not of integer type. Please call PUSH followed by an integer (ex: PUSH 2).\n");
                }
            // If unrecognized operation is provided
            } else {
				System.out.println("Keyword not recognized. Please request either: PUSH <N>, ADD, SUB, MUL, SWAP, or END.\n");
			}
        }
        // If something lives on the stack, output it
        if (s.arr.size()>0)
            s.expression();
    }
}
