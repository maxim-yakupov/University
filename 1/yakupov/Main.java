package yakupov;

import java.io.*;

public class Main {

    public static void main(String[] args) {
        System.out.println(test_reverseString() ? "Test passed" : "Test FAILED");

        StringBuilder str = new StringBuilder();
        System.out.println("[**************************************]\n" +
                "result will be shown on screen & written in 'output.txt'\n" +
                "enter source(1 - console, 0 - from file)");

        BufferedReader buffered_reader = new BufferedReader(
                new InputStreamReader(System.in)
        );

        char ch = readOneSymbol(buffered_reader);

        try {
            /**
             * @deprecated Tried to avoid of reading extra 'line-ending symbols', but it depends on OS.
             * So this code
             * <code>System.out.println("skipped:" + buffered_reader.skip(1)); // avoid reading extra '\n'</code>
             * can be improved by using constant variable.
             */
            //System.out.println("skipped:" + buffered_reader.skip(1)); // avoid reading extra '\n'
            buffered_reader.readLine(); // avoid reading extra symbols in string
        } catch (IOException e) {
            System.out.println("skipping problem");
        }

        if (ch == '1') {
            System.out.println("[********--------input---------********]");
            readListOfSymbols(str, buffered_reader);
        } else if (ch == '0') {
            try {
                System.out.print("write file name: ");

                String path = buffered_reader.readLine();
                try {
                    readListOfSymbols(str, new BufferedReader(
                            new InputStreamReader(
                                    new FileInputStream(path)
                            )
                    ));
                    System.out.println("{********-------opened---------********}");
                    System.out.println(path);
                    System.out.println("{********--------output--------********}");
                    System.out.println(str.toString());

                    System.out.println();
                } catch (FileNotFoundException e) {
                    System.out.println(path + ":file not found");
                }
            } catch (IOException e) {
                System.out.println("Somethings goes wrong with file opening");
            }

        }
        if (str.length() != 0) {
            System.out.println("[********----reverse-output----********]");
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

            reverseString(str);

            if (pstr != null) {
                System.setOut(pstr);
                System.out.print(str.toString());
                System.setOut(stdOut);
            }
            System.out.print(str.toString());

        }
        System.out.println("\n[**************************************]");
    }

    /**
     * Test
     * @return 'true' if passed, 'false' if failed
     */
    private static boolean test_reverseString() {
        boolean success = true;
        StringBuilder str = new StringBuilder("123456789");

        reverseString(str);

        for (int i = 0; i < str.length(); i++) {
            if (str.toString().charAt(i) != ((char) ((int) '0') + 9 - i)) {
                success = false;
                break;
            }
        }
        return success;
    }

    /**
     * Reverses string 'str'
     * @param str String for reverse
     */
    private static void reverseString(StringBuilder str) {
        str.reverse();
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
     * @param str String, in which we read
     * @param buffered_reader BufferedReader of input stream
     */
    private static void readListOfSymbols(StringBuilder str, BufferedReader buffered_reader) {
        char ch = readOneSymbol(buffered_reader);
        while (true) {
            if (ch == ' ') {
                char temp = readOneSymbol(buffered_reader);
                if (temp == ' ') {
                    break;
                }
                str.append(ch);
                ch = temp;
            }
            str.append(ch);
            ch = readOneSymbol(buffered_reader);
        }
    }
}
