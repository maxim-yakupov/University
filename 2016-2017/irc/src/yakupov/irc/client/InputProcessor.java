package yakupov.irc.client;

import java.io.InputStream;
import java.util.Scanner;

public abstract class InputProcessor extends Thread {
    private Scanner scanner;

    protected InputProcessor(InputStream in) {
        this.scanner = new Scanner(in);
    }

    public void run() {
        while (scanner.hasNextLine()) {
            try {
                process(scanner.nextLine());
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    public abstract void process(String incomeMessage);

    public void teardown() {
        scanner.close();
        stop();
    }
}
