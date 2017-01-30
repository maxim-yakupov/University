package yakupov.irc.client;

public class ConsoleInputProcessor extends InputProcessor {
    private Client client = null;

    public ConsoleInputProcessor(Client client) {
        super(System.in);
        this.client = client;
    }

    @Override
    public void process(String incomeMessage) {
        if (incomeMessage.equalsIgnoreCase(">>q")) {
            System.out.println("ConsoleProcessor] disconnecting client...");
            client.disconnect();
        } else if (incomeMessage.equalsIgnoreCase(">>r")) {
            System.out.println("ConsoleProcessor] reconnecting client...");
            client.reconnect();
        } else {
            Message message = new Message(
                    client.getUser().nickname,
                    Constants.Commands.PRIVMSG,
                    client.getChannel() + " :" + incomeMessage);
            client.send(message);
            consolePrint(message);
        }
    }

    private void consolePrint(Message message) {
        System.out.println(
                Constants.Colors.BLUE + "ConsoleProcessor]   " +
                        message.toString() +
                        Constants.Colors.NORMAL_MODE);
    }
}
