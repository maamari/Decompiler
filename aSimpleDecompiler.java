import java.util.*;
import java.io.*;
import java.lang.*;

class Decompiler {
    Stack < String > arr = new Stack < String > ();
    Decompiler() {}

    void operationHelper(String operation) {
        int size = arr.size();
        //size >=2
        if (size >= 2) {
            int last = Integer.parseInt(arr.peek()); //take top element from the stack
            arr.pop();
            int s_last = Integer.parseInt(arr.peek()); //take new top element
            arr.pop(); //remove top element
            String stri = Integer.toString(last + s_last);
            arr.push(stri); //push sum of top two element into the stack
        }
        //if only one element present
        else if (size == 1) {
            String last = arr.peek();
            arr.pop();
            arr.push("(x" + Integer.toString(size) + "+" + last + ")");
        }
        //if no element present
        else {
            arr.push("(x" + Integer.toString(size) + "+" + "x" + Integer.toString(size + 1) + ")");
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
        String first = arr.peek();
        arr.pop();
        String second = arr.peek();
        arr.pop();
        arr.push(first);
        arr.push(second);
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
        System.out.println("  PUSH: Push an integer, N, to the stack");
        System.out.println("  ADD: Add values from the stack");
        System.out.println("  SUB: Subtract values from the stack");
        System.out.println("  MUL: Multiply values from the stack");
        System.out.println("  SWAP: Swap values from the stack");
        System.out.println("  END: Enter END when finished with commands\n");

        while (true) {
            String op = sc.nextLine();
            if (op.equals("PUSH")) {
                System.out.print("  Enter value to be pushed: ");
                String val = sc.nextLine();
                s.arr.push(val);
            } else if (op.equals("ADD")) {
                s.add();
            } else if (op.equals("SUB")) {
                s.sub();
            } else if (op.equals("MUL")) {
                s.mul();
            } else if (op.equals("SWAP")) {
                s.swap();
            } else if (op.equals("END")) {
                break;
            }
        }
        s.expression();
    }
}
