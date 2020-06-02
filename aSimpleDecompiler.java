import java.util.*;
import java.io.*;
import java.lang.*;

class Decompiler {
    Stack < String > arr = new Stack < String > ();
    Decompiler() {}
    int count = 0;

    void operationHelper(String operation) {
        int size = arr.size();
        //size >=2
        if (size >= 2) {
            int last = Integer.parseInt(arr.peek()); //take top element from the stack
            arr.pop();
            int s_last = Integer.parseInt(arr.peek()); //take new top element
            arr.pop(); //remove top element
            if (operation.equals("+")){
                String stri = Integer.toString(last + s_last);
                arr.push(stri);
            } else if (operation.equals("-")) {
                String stri = Integer.toString(last - s_last);
                arr.push(stri);
            } else if (operation.equals("*")) {
                String stri = Integer.toString(last * s_last);
                arr.push(stri);
            }
        }
        //if only one element present
        else if (size == 1) {
            String last = arr.peek();
            arr.pop();
            arr.push("(x" + Integer.toString(count) + operation + last + ")");
            count++;
        }
        //if no element present
        else {
            arr.push("(x" + Integer.toString(count) + operation + "x" + Integer.toString(count+1) + ")");
            count+=2;
        }
    }

    void add() {
        operationHelper("+");
    }
    void sub() {
        operationHelper("-");
    }
    void mul() {
        operationHelper("*");
    }
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
            String input = sc.nextLine();
			String[] inputs = input.split(" ");
			inputs[0] = inputs[0].toUpperCase();

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
                    try {
                        s.arr.push(inputs[1]);
                    } catch (Exception e) {
                        System.out.println("Requested PUSH without value. Please call PUSH followed by an integer (ex: PUSH 2).\n");
                    }
                } catch (Exception e) {
					System.out.println("Requested PUSH value is not of integer type. Please call PUSH followed by an integer (ex: PUSH 2).\n");
                }
            } else {
				System.out.println("Keyword not recognized. Please request either: PUSH <N>, ADD, SUB, MUL, SWAP, or END.\n");
			}
        }
        s.expression();
    }
}
