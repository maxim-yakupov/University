package yakupov;

import java.io.*;
import java.lang.Math;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) throws IOException {
        System.out.println(test_bitReverse() ? "Test passed" : "Test FAILED");

        System.out.println("[**************************************]\n" +
                "result will be shown on screen & written in 'output.txt'\n" +
                "enter source(1 - console, 0 - from file)");

        BufferedReader buffered_reader = new BufferedReader(
                new InputStreamReader(System.in)
        );

        char ch = readOneSymbol(buffered_reader);

        try {
            buffered_reader.readLine(); // avoid reading extra symbols in string
        } catch (IOException e) {
            System.err.println("skipping problem");
        }

        if (ch == '1') {
            System.out.println("[********--------input---------********]");
            Scanner sc = new Scanner(System.in);
            int k = sc.nextInt();
            char[] array = new char[(int) Math.pow(((double) 2), ((double) k))];
            readArrayOfSymbols(array, buffered_reader);
            makeThings(array);
        } else if (ch == '0') {
            try {
                System.out.print("write file name: ");

                String path = buffered_reader.readLine();
                try {
                    FileReader ifr = new FileReader(path);
                    buffered_reader = new BufferedReader(ifr);

                    int k = new Scanner(buffered_reader.readLine()).nextInt();

                    char[] array = new char[(int) Math.pow(((double) 2), k)];
                    readArrayOfSymbols(array, buffered_reader);

                    System.out.println("{********-------opened---------********}");
                    System.out.println(path);
                    System.out.println("{********--------output--------********}");
                    System.out.println(array);
                    makeThings(array);
                } catch (FileNotFoundException e) {
                    System.err.println(path + ":file not found");
                }
            } catch (IOException e) {
                System.err.println("Somethings goes wrong with file opening");
            }
        }
        System.out.println("\n[**************************************]");
    }

    /**
     * Makes bit-reverse swap and prints result
     * @param a Array, which we changing
     */
    private static void makeThings(char[] a) {
        System.out.println("[********--bit-reverse-output--********]");
        //
        PrintStream stdOut = System.out;
        PrintStream pstr = null;
        try {
            pstr = new PrintStream(
                    new FileOutputStream(
                            System.getProperty("user.dir") + File.separatorChar + "output.txt")
            );
        } catch (FileNotFoundException e) {
            System.out.println("output file trouble");
        }

        bitReverse(a); //!!! that's what we should do
        if (pstr != null) {
            System.setOut(pstr);
            System.out.print(a);
            System.setOut(stdOut);
        }
        System.out.print(a);
    }

    /**
     * Test
     * @return 'true' if passed, 'false' if failed
     */
    private static boolean test_bitReverse() {
        boolean success = true;
        char[] a = new char[4];
        a[0] = '0';
        a[1] = '1';
        a[2] = '2';
        a[3] = '3';

        bitReverse(a);

        if (a[0] != '3' || a[1] != '2' || a[2] != '1' || a[3] != '0') {
            success = false;
        }
        return success;
    }

    /**
     * Swaps array[i] and array[j]
     * @param array Array, in which we making swap
     * @param i First element
     * @param j Second element
     */
    private static void swap(char[] array, int i, int j) {
        char temporary = array[i];
        array[i] = array[j];
        array[j] = temporary;
    }

    /**
     * Swaps array[i] and array[~i]
     * @param array Array, which we changing
     */
    private static void bitReverse(char[] array) {
        for (int i = 0; i < array.length / 2; i++) {
            int j = ~i&(array.length - 1);
            swap(array, i, j);
        }
    }

    /**
     * Reads one symbol from buffered_reader
     * @param buffered_reader Buffered reader of input stream
     * @return One symbol from buffered_reader
     */
    private static char readOneSymbol(BufferedReader buffered_reader) {
        char ch;
        try {
            ch = ((char) buffered_reader.read());
        } catch (IOException e) {
            ch = '~';
            System.out.println("Some problem occurs");
            System.exit(-111);
        }
        return ch;
    }

    /**
     * Reads string into list until '  ' occurs
     * @param array Array, in which we read
     * @param buffered_reader BufferedReader of input stream
     */
    private static void readArrayOfSymbols(char[] array, BufferedReader buffered_reader) {
        char ch = readOneSymbol(buffered_reader);
        int i = 0;
        while (ch != '\n' && ch != ((char) -1)) {
            array[i] = ch;
            ch = readOneSymbol(buffered_reader);
            i++;
        }
    }
}