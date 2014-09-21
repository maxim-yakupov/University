package yakupov;

import java.io.*;
import yakupov.list.List;

public class Main {

    public static void main(String[] args) {
        List list = new List();
        System.out.println("[**************************************]\n" +
                "enter source(1 - console, 0 - from file)");

        BufferedReader buffered_reader = new BufferedReader(
                new InputStreamReader(System.in)
        );

        char ch = readOneSymbol(buffered_reader);

        try {
            buffered_reader.skip(1); // avoid reading extra '\n'
        } catch (IOException e) {
            System.out.println("skip problem");
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

                    System.out.println("{********--------output--------********}");
                    list.print();

                    System.out.println();
                } catch (FileNotFoundException e) {
                    System.out.println(path + ":file not found");
                }
            } catch (IOException e) {
                System.out.println("Somethings goes wrong with file opening");
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
                System.out.println("output file not found!");
            }

            System.setOut(pstr);
            list.printReverse();
            System.setOut(stdOut);
            //
            list.printReverse();
        }
        System.out.println("\n[**************************************]");
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
    private static void readListOfSymbols(List list, BufferedReader buffered_reader) {
        char ch = readOneSymbol(buffered_reader);
        while (true) {
            if (ch == ' ') {
                char temp = readOneSymbol(buffered_reader);
                if (temp == ' ') {
                    break;
                }
                list.insert(ch);
                ch = temp;
            }
            list.insert(ch);
            ch = readOneSymbol(buffered_reader);
        }
    }
}
