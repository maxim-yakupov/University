package yakupov;

import java.io.*;
import yakupov.list.SLList;
import yakupov.list.WrongIndexException;

public class Main {

    public static void main(String[] args) {
        try {
            System.out.println(test_reverseList() ? "Test passed" : "Test FAILED");
        } catch (WrongIndexException e) {
            System.err.println("WrongIndexException in test_reverseList()");
        }

        SLList list = new SLList();
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
            System.err.println("skipping problem");
        }

        if (ch == '1') {
            System.out.println("[********--------input---------********]");
            readListOfSymbols(list, buffered_reader);
        } else if (ch == '0') {
            try {
                System.out.print("write file name: ");

                String path = buffered_reader.readLine();
                try {
                    readListOfSymbols(list, new BufferedReader(
                            new InputStreamReader(
                                    new FileInputStream(path)
                            )
                    ));
                    System.out.println("{********-------opened---------********}");
                    System.out.println(path);
                    System.out.println("{********--------output--------********}");
                    list.print();

                    System.out.println();
                } catch (FileNotFoundException e) {
                    System.err.println(path + ":file not found");
                }
            } catch (IOException e) {
                System.err.println("Somethings goes wrong with file opening");
            }

        }
        if (!list.isNull()) {
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

            reverseList(list); //!!! that's what we should do
            if (pstr != null) {
                System.setOut(pstr);
                list.print();
                System.setOut(stdOut);
            }
            list.print();
        }
        System.out.println("\n[**************************************]");
    }

    /**
     * Test
     */
    private static boolean test_reverseList() throws WrongIndexException {
        boolean success = true;
        SLList list = new SLList();
        list.insert('0');
        list.insert('1');
        list.insert('2');
        list.insert('3');
        list.insert('4');

        reverseList(list);

        for (int i = 0; i < list.getLength(); i++) {
            if (list.value(i) != ((char) ((int) '0') + 4 - i)) {
                success = false;
                break;
            }
        }
        return success;
    }

    /**
     * Reverses list
     * @param list List, which we turn over
     */
    private static void reverseList(SLList list) {
        for (int i = 1; i < list.getLength(); i++) {
            try {
                list.insertInBeginning(list.value(i));
                list.remove(i + 1);
            } catch (WrongIndexException e){
                System.err.println("WrongIndexException in reverseList()");
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
     * @param list List, in which we read
     * @param buffered_reader BufferedReader of input stream
     */
    private static void readListOfSymbols(SLList list, BufferedReader buffered_reader) {
        char ch = readOneSymbol(buffered_reader);
        while (ch != '\n' && ch != ((char) -1)) {
            list.insert(ch);
            ch = readOneSymbol(buffered_reader);
        }
    }
}
