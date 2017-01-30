package yakupov.irc.client;

public class Message {
    public String msg = null;
    public Constants.Commands command = null;
    public String from = null;

    public Message(String from, Constants.Commands command, String message) {
        this.from = from;
        this.command = command;
        this.msg = message;
    }

    public Message(Constants.Commands command, String message) {
        this.from = null;
        this.command = command;
        this.msg = message;
    }

    public Message(String incomeMessage) {
        String[] splittedMsg = incomeMessage.split(" ");
        int currentIndex = 0;
        String firstToken = splittedMsg[currentIndex].split("!")[0];
        if (firstToken.charAt(0) == ':') {
            from = firstToken.substring(1, firstToken.length());
            currentIndex++;
        }
        try {
            command = Constants.Commands.valueOf(splittedMsg[currentIndex]);
        } catch (IllegalArgumentException e) {
            command = Constants.Commands.UNSUPPORTED;
        } finally {
            currentIndex++;
        }
        StringBuilder sb = new StringBuilder(splittedMsg[currentIndex++]);
        while (currentIndex < splittedMsg.length) {
            sb.append(" " + splittedMsg[currentIndex++]);
        }
        msg = sb.toString();
    }

    @Override
    public String toString() {
        return ((from == null ? "" : ":" + from + " ") + command.toString() + " " + msg);
    }

    public byte[] serialize() {
        return (toString() + "\r\n").getBytes();
    }
}
