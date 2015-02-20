package yakupov.chat.mode;

import yakupov.chat.client.Client;
import yakupov.chat.server.Server;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        System.out.println("(s)erver/(c)lient");
        while (true) {
            char answer = Character.toLowerCase(in.nextLine().charAt(0));
            if (answer == 's') {
                new Server();
                break;
            } else if (answer == 'c') {
                new Client()
                        .startMagic();
                break;
            } else {
                System.out.println("Incorrect input. Try again");
            }
        }
    }
}
