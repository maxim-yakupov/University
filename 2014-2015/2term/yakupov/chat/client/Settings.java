package yakupov.chat.client;

/**
 * Structure for keeping client's settings
 */
public class Settings {

    private String ip;
    private int port;
    private String name;

    public Settings(String ip, int port, String name) {
        setIp(ip);
        setPort(port);
        setName(name);
    }

    public String getIp() {
        return ip;
    }

    public void setIp(String ip) {
        this.ip = ip;
    }

    public int getPort() {
        return port;
    }

    public void setPort(int port) {
        this.port = port;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
}
