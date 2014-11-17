package yakupov;

import java.io.*;
import java.util.Map;
import java.util.TreeMap;

public class Main {

    /**
     * Counts quantity of each word in text
     * @param strReader BufferedReader of input text
     * @param log 'true' if want to see logs,
     *            'false' if not
     * @return Map of words(word - quantity)
     * @throws IOException If something wrong with reading
     */
    public static Map<String, Integer> countWords(BufferedReader strReader, boolean log) throws IOException {
        char ch = (char) strReader.read();
        if (log) {
            System.out.println("-----------text------------");
            System.out.print(ch);
        }
        Map<String, Integer> map = new TreeMap<String, Integer>();
        StringBuilder str = new StringBuilder("");
        while (strReader.ready()) {
            if ((((int) ch) >= ((int) 'a')) &&
                    (((int) ch) <= ((int) 'z')) ||
                    (((int) ch) >= ((int) 'A')) &&
                            (((int) ch) <= ((int) 'Z'))
                    ) {
                str.append(ch);
            } else if (!str.toString().equals("")) {
                if (!map.containsKey(str.toString())) {
                    map.put(str.toString(), 1);
                } else {
                    map.put(str.toString(), map.get(str.toString()) + 1);
                }
                str = new StringBuilder("");
            }
            if (ch == '\0') break;//
            ch = (char) strReader.read();
            if (log) {
                System.out.print(ch);
            }
        }
        if (log) {
            System.out.println();
            System.out.println("--------end-of-text--------");
            for(String key: map.keySet()) {
                System.out.println(key + " - " + map.get(key));
            }
        }

        return map;
    }

    public static void main(String[] args) throws IOException {
        System.out.println(test() ? "Test PASSED" : "Test FAILED");

        BufferedReader strReader = new BufferedReader(
                                        new InputStreamReader(
                                            new FileInputStream(
                                                    new File("input.txt")
                                            )
                                        )
        );

        countWords(strReader, true);

        strReader.close();
    }

    public static boolean test() throws IOException {
        Map<String, Integer> map = countWords(new BufferedReader(new StringReader("qwe qwe ewe\0")), false);
        return (map.size() == 2 &&
                map.get("qwe") == 2 &&
                map.get("ewe") == 1);
    }
}
