package yakupov.chat.client;

import yakupov.chat.common.Message;

import java.util.Scanner;

/**
 * Class of chat's client
 */
public class Client {
    private Settings settings;
    private boolean stopped;
    private ClientGUI clientGUI;
    private Network network;

    /**
     * Constructor
     */
    public Client() {
        Scanner scan = new Scanner(System.in);
        System.out.println("Enter IP:");
        String ip = scan.nextLine();
        System.out.println("Enter port:");
        int port = Integer.parseInt(scan.nextLine());
        System.out.print("Enter your nick-name:");
        String enteredName = scan.nextLine();

        init(ip, port, enteredName);

        scan.close();
    }

    /**
     * Constructor
     * @param ip IP of server
     * @param port Port, which server listens
     * @param name Nick-name of user
     */
    public Client(String ip, int port, String name) {
        init(ip, port, name);
    }

    /**
     * Initialise and run client
     * @param ip IP of server
     * @param port Port, which server listens
     * @param name Nick-name of user
     */
    private void init(String ip, int port, String name) {
        this.settings = new Settings(ip, port, name);
        this.network = new Network(this);
        this.clientGUI = new ClientGUI(this);
        //
        new Thread(network::start).start();
    }

    /**
     * Returns client's settings
     * @return Settings
     */
    public Settings getSettings() {
        return settings;
    }

    /**
     * Returns status of client
     * @return <ul>
     *         <li>'true' - if client stopped</li>
     *         <li>'false' - if client works</li>
     *         <ul/>
     */
    public boolean isStopped() {
        return stopped;
    }

    /**
     * Stops client
     */
    public void stop() {
        this.stopped = true;
        network.stop();
        clientGUI.stop();
    }

    /**
     * Sends message to server
     * @param msg Message
     */
    public void sendMessage(Message msg) {
        network.sendAsync(msg);
    }

    /**
     * Shows received message
     * @param msg Message
     */
    public void receivedMessage(Message msg) {
        clientGUI.showNewMessageAsync(msg);
    }
}
