package yakupov.irc.client;

import java.io.IOException;
import java.io.InputStream;

public class SocketInputProcessor extends InputProcessor {
    private Client client = null;

    public SocketInputProcessor(
            InputStream inputStream, Client client) {
        super(inputStream);
        this.client = client;
    }

    @Override
    public void process(String incomeMessage) {
        consolePrintRAW(incomeMessage);
        Message message = new Message(incomeMessage);
        consolePrint(message);
        if (message.command == Constants.Commands.PING) {
            client.send(
                    new Message(
                            Constants.Commands.PONG,
                            "Answer for PING"));
        } else if (message.command == Constants.Commands.PRIVMSG &&
                message.msg.contains("show some magic") &&
                message.msg.contains(client.getUser().nickname)) {
            try {
                Magic.showSome(client);
            } catch (IOException e) {
                System.out.println("Magic failed :c");
                e.printStackTrace();
            }
        }
    }

    private void consolePrintRAW(String rawString) {
        if (!client.getIsDebugEnabled()) return;
        System.out.println(
                Constants.Colors.RED + "SocketProcessor-RAW]" +
                        rawString +
                        Constants.Colors.NORMAL_MODE);
    }

    private void consolePrint(Message message) {
        System.out.println(
                Constants.Colors.GREEN + "SocketProcessor]    " +
                        message.toString() +
                        Constants.Colors.NORMAL_MODE);
    }
}