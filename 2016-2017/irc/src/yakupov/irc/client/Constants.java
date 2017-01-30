package yakupov.irc.client;

public class Constants {
    public enum Commands {
        JOIN, NICK, USER, QUIT,
        NOTICE, PRIVMSG,
        PING, PONG,
        // command just for mark commends
        // which I'm not currently process
        UNSUPPORTED
    }

    public static class Colors {
        public static String RED = "\033[31m";
        public static String GREEN = "\033[32m";
        public static String BLUE = "\033[34m";
        public static String NORMAL_MODE = "\033[0m";
        public static String INVERT_MODE = "\033[7m";

        public static String invertColors(String text) {
            return INVERT_MODE + text + NORMAL_MODE;
        }
    }
}
