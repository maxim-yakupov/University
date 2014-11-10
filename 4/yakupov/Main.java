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

        if (a[0] != '0' ||     //00
                a[1] != '2' || //01
                a[2] != '1' || //10
                a[3] != '3') { //11
            success = false;
        }

        char[] b = new char[8];
        b[0] = '0';
        b[1] = '1';
        b[2] = '2';
        b[3] = '3';
        b[4] = '4';
        b[5] = '5';
        b[6] = '6';
        b[7] = '7';

        bitReverse(b);

        if (b[0] != '0' ||     //000
                b[1] != '4' || //001
                b[2] != '2' || //010
                b[3] != '6' || //011
                b[4] != '1' || //100
                b[5] != '5' || //101
                b[6] != '3' || //110
                b[7] != '7') { //111
            success = false;
        }

        char[] c = new char[16];
        c[0] = '0';
        c[1] = '1';
        c[2] = '2';
        c[3] = '3';
        c[4] = '4';
        c[5] = '5';
        c[6] = '6';
        c[7] = '7';
        c[8] = '8';
        c[9] = '9';
        c[10] = 'a';
        c[11] = 'b';
        c[12] = 'c';
        c[13] = 'd';
        c[14] = 'e';
        c[15] = 'f';

        bitReverse(c);

        if (c[0] != '0' ||      //0000
                c[1] != '8' ||  //0001
                c[2] != '4' ||  //0010
                c[3] != 'c' ||  //0011
                c[4] != '2' ||  //0100
                c[5] != 'a' ||  //0101
                c[6] != '6' ||  //0110
                c[7] != 'e' ||  //0111
                c[8] != '1' ||  //1000
                c[9] != '9' ||  //1001
                c[10] != '5' || //1010
                c[11] != 'd' || //1011
                c[12] != '3' || //1100
                c[13] != 'b' || //1101
                c[14] != '7' || //1110
                c[15] != 'f') { //1111
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
     * Swaps array[a1a2...an] and array[ana(n-1)...a1]
     * @param array Array, which we changing
     */
    private static void bitReverse(char[] array) {
        //n - number of bits for code element's index
        int n = (int) (
                Math.log((double) array.length)
                /
                Math.log(2.0)
        );
        for (int i = 0; i < array.length; i++) {
            int j = 0;
            int curBit;
            for (int k = 0; k < n; k++) {
                curBit = 0;
                if ((i&((int) Math.pow(2.0, ((double) k)))) != 0) {
                    curBit = 1;
                }
                j = j * 2 + curBit;
            }
            //for not swapping back
            if (i < j) {
                swap(array, i, j);
            }
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