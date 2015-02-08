package yakupov;

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Random;
import java.util.Scanner;

public class Main {

    public static boolean test() {
        boolean success = true;
        //multiplying test
        Matrix m1 = new Matrix(2, 3);
        m1.set(0, 0, 1);
        m1.set(0, 1, 2);
        m1.set(0, 2, 3);
        m1.set(1, 0, 4);
        m1.set(1, 1, 5);
        m1.set(1, 2, 6);
        Matrix m2 = new Matrix(3, 1);
        m2.set(0, 0, 1);
        m2.set(1, 0, 2);
        m2.set(2, 0, 3);
        Matrix mm = Matrix.multi(m1, m2);
        if (mm.get(0, 0) != 14.0 ||
                mm.get(1, 0) != 32.0) {
            success = false;
        }
        //transponent multiplying test
        m1 = new Matrix(2, 2);
        m1.set(0, 0, 1);
        m1.set(0, 1, 2);
        m1.set(1, 0, 3);
        m1.set(1, 1, 4);
        m2 = new Matrix(2, 2);
        m2.set(0, 0, 1);
        m2.set(0, 1, 2);
        m2.set(1, 0, 3);
        m2.set(1, 1, 4);
        m2.tranponent();
        mm = Matrix.multiSecondTransp(m1, m2);
        if (mm.get(0, 0) != 7.0 ||
                mm.get(0, 1) != 10.0 ||
                mm.get(1, 0) != 15.0 ||
                mm.get(1, 1) != 22.0) {
            success = false;
        }
        m2.tranponent();
        if (mm.equals(Matrix.multi(m1, m2))) success = false;
        return success;
    }

    public static void genTests() {
        for (int n = 5; n < 1100; n *= 2) {
            Random rnd = new Random(System.nanoTime());
            long st, en;
            Matrix m = new Matrix(n, n);
            Matrix m1 = new Matrix(n, n);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    m.set(i, j, rnd.nextDouble());
                    m1.set(i, j, rnd.nextDouble());
                }
            }
            System.out.print(n + ") ");
            st = System.nanoTime();
            Matrix.multi(m, m1);
            en = System.nanoTime();
            System.out.print((en - st) + " ");
            m1.tranponent();
            st = System.nanoTime();
            Matrix.multiSecondTransp(m, m1);
            en = System.nanoTime();
            System.out.print((en - st) + "\n");
        }
    }

    /**
     * Returns time of execution of multiplying of 2 matrixes
     * @param m1 First matrix
     * @param m2 Second matrix
     * @param tr 'true' if second matrix is transponented
     *           'false' if not
     * @return Time of execution of multiplying
     */
    public static long timer(Matrix m1, Matrix m2, boolean tr) {
        long st, en;
        st = System.nanoTime();
        if (tr) {
            Matrix.multiSecondTransp(m1, m2);
        }
        else {
            Matrix.multi(m1, m2);
        }
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
        System.out.println(test() ? "Test PASSED" : "Test FAILED");

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

        myPrintWriter.println("Ordinary multiplying result");
        writeMatrix(Matrix.multi(m1, m2), myPrintWriter);

        m2.tranponent();

        System.out.println("Second run: " + timer(m1, m2, true) + "ns");

        myPrintWriter.println("Result of multiplying with second matrix previously transponented");
        writeMatrix(Matrix.multiSecondTransp(m1, m2), myPrintWriter);

        myPrintWriter.println("If matrixes are equal, all is OK");

        myPrintWriter.close();
        genTests();
    }
}
