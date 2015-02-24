package yakupov.chat.common;

import java.io.Serializable;
import java.text.SimpleDateFormat;

/**
 * Container for messages, which will be sent between client and server
 */
public class Message implements Serializable, Comparable {

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Message message = (Message) o;

        if (time != message.time) return false;
        if (code != message.code) return false;
        if (!sender.equals(message.sender)) return false;
        if (str != null ? !str.equals(message.str) : message.str != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = code.hashCode();
        result = 31 * result + (str != null ? str.hashCode() : 0);
        result = 31 * result + sender.hashCode();
        result = 31 * result + (int) (time ^ (time >>> 32));
        return result;
    }

    public enum Codes {
        INIT,
        MSG,
        EXIT
    }

    private Codes code;
    private String str;
    private String sender;
    private long time;

    public Message(String sender, Codes code, String str) {
        this.sender = sender;
        this.code = code;
        this.str = str;
        this.time = System.currentTimeMillis();
    }

    /**
     * Returns name of user, who sent message
     * @return Nick-name
     */
    public String getSender() {
        return this.sender;
    }

    /**
     * Returns type of message
     * @return Code of type
     */
    public Codes getCode() {
        return this.code;
    }

    /**
     * Returns text of message
     * @return Text
     */
    public String getStr() {
        return this.str;
    }

    /**
     * Returns time of sending in milliseconds
     * @return Time of sending
     */
    public long getTime() {
        return time;
    }

    @Override
    public String toString() {
        if (code == Codes.EXIT) {
            return "EXIT CODE";
        } else if (code == Codes.INIT) {
            return getStr();
        } else if (code == Codes.MSG) {
            return "{" + new SimpleDateFormat("HH:mm:ss").format(getTime()) + "}" + "[" + getSender() + "]: " + getStr();
        } else {
            return "<<wrong format>>";
        }
    }

    @Override
    public int compareTo(Object o) {
        Message other = (Message) o;
        return (this.time < other.getTime() ? -1 : (this.time == other.getTime() ? 0 : 1));
    }
}
