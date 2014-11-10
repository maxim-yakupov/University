package yakupov;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Map;
import java.util.TreeMap;

public class Main {

    public static void main(String[] args) throws IOException {
        InputStreamReader strReader = new InputStreamReader(
                new FileInputStream(
                        new File("input.txt")
                )
        );

        char ch = (char) strReader.read();
        System.out.println("-----------text------------");
        System.out.print(ch);
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
            ch = (char) strReader.read();
            System.out.print(ch);
        }
        System.out.println();
        System.out.println("--------end-of-text--------");
        for(String key: map.keySet()) {
            System.out.println(key + " - " + map.get(key));
        }
        strReader.close();
    }
}
