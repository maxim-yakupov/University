package yakupov.irc;

import yakupov.irc.client.Client;

public class Main {
    public static void main(String[] args) {
	    Client client = new Client("irc.freenode.org", 6667);
	    if (args.length > 0 && (args[0].equalsIgnoreCase("--debug") || args[0].equalsIgnoreCase("-d"))) {
	        client.setIsDebugEnabled(true);
        }
        if (client.connect()) {
            System.out.println("Connected to the server: " + client.endpoint());
        } else {
            System.out.println("Failed to connect to the server: " + client.endpoint());
        }
        client.joinChannel("#spbnet");
        while (client.getActiveState()) {
            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        client.disconnect();
    }
}
