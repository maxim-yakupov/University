package yakupov.irc.client;

import java.io.IOException;
import java.net.*;
import java.util.HashMap;


public class Client {
    private boolean isDebugEnabled = false;

    public void setIsDebugEnabled(boolean enabled) {
        this.isDebugEnabled = enabled;
    }

    public boolean getIsDebugEnabled() {
        return isDebugEnabled;
    }

    private boolean isActive = false;
    private boolean isReconnecting = false;
    private String host = "localhost";
    private int port = 6667;
    private Socket socket = null;
    private SocketInputProcessor socketInputProcessor = null;
    private ConsoleInputProcessor consoleInputProcessor = null;
    private User user = new User("qponBot", "Maxim Yakupov's bot");
    private String channel = null;
    public HashMap<String, FunctionalInterface> handlers = new HashMap<>();

    public Client(String host, int port) {
        this.host = host;
        this.port = port;
    }

    public boolean getActiveState() {
        return isActive || isReconnecting;
    }

    public String getChannel() {
        return channel;
    }

    public User getUser() {
        return user;
    }

    public void setUser(User user) {
        this.user = user;
    }

    public boolean reconnect() {
        isReconnecting = true;
        disconnect();
        connect();
        if (channel != null) {
            joinChannel(channel);
        }
        isReconnecting = false;
        return isActive;
    }

    public boolean connect() {
        try {
            socket = new Socket(host, port);
            socketInputProcessor = new SocketInputProcessor(
                    socket.getInputStream(),
                    this);
            socketInputProcessor.setDaemon(true);
            socketInputProcessor.start();

            consoleInputProcessor = new ConsoleInputProcessor(this);
            consoleInputProcessor.setDaemon(true);
            consoleInputProcessor.start();

            socket.setSoTimeout(0);

            isActive = true;

            send(new Message(
                    Constants.Commands.NICK,
                    user.nickname));
            send(new Message(
                    Constants.Commands.USER,
                    user.nickname + " localhost " + host + " :" + user.realname));
        } catch (IOException e) {
            e.printStackTrace();
            isActive = false;
        }
        return true;
    }

    public boolean send(Message message) {
        try {
            socket.getOutputStream().write(
                    message.serialize()
            );
            return true;
        } catch (IOException e) {
            e.printStackTrace();
            return false;
        }
    }

    public boolean joinChannel(String channel) {
        this.channel = channel;
        return send(new Message(Constants.Commands.JOIN, getChannel()));
    }

    public void disconnect() {
        if (!isActive) return;
        try {
            send(new Message(Constants.Commands.QUIT, "Bye"));
            consoleInputProcessor.teardown();
            socketInputProcessor.teardown();
            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            isActive = false;
        }
    }

    public String endpoint() {
        return host + ':' + port;
    }
}
