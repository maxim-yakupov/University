package yakupov;

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {

    public static long timer(Matrix m1, Matrix m2, boolean tr) {
        long st, en;
        st = System.nanoTime();
        if (tr) Matrix.multiTransp(m1, m2);
        else    Matrix.multi(m1, m2);//----
        en = System.nanoTime();
        return en-st;
    }

    public static void writeMatrix(Matrix m, PrintWriter myPrintWriter) {
        for (int i = 0; i < m.getH(); i++) {
            for (int j = 0; j < m.getW(); j++) {
                myPrintWriter.print(m.get(i, j) + " ");
            }
            myPrintWriter.println();
        }
        myPrintWriter.println();
    }

    public static void main(String[] args) throws IOException {
        Scanner myScanner = new Scanner(new File("input.txt"));
        PrintWriter myPrintWriter = new PrintWriter(new File("output.txt"));

        int n = myScanner.nextInt();
        Matrix m1 = new Matrix(n, n);
        Matrix m2 = new Matrix(n, n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++){
                m1.set(i, j, myScanner.nextDouble());
            }
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++){
                m2.set(i, j, myScanner.nextDouble());
            }
        System.out.println("First run: " + timer(m1, m2, false) + "ns");

        writeMatrix(Matrix.multi(m1, m2), myPrintWriter);

//        m1.tranponent();
        m2.tranponent();

        System.out.println("Second run: " + timer(m1, m2, true) + "ns");

        writeMatrix(Matrix.multiTransp(m1, m2), myPrintWriter);

        myPrintWriter.close();
    }
}
