package yakupov.irc.client;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;

import java.io.IOException;

public class Magic {
    public static void showSome(Client client) throws IOException {
        Document doc = Jsoup.connect("http://baneks.ru/random").get();
        Element select = doc.select(".anek-view article p").first();
        String anek = select.text();
        System.out.println("ANEK:]" + "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
        client.send(
                new Message(Constants.Commands.PRIVMSG,
                        client.getChannel() +
                                " :" + "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓"));
        int begIndex = 0;
        while(begIndex < anek.length()) {
            int endIndex = begIndex + 120;
            endIndex = endIndex > anek.length() ? anek.length() : endIndex;
            System.out.println("ANEK:]" + anek.substring(begIndex, endIndex));
            client.send(
                    new Message(Constants.Commands.PRIVMSG,
                            client.getChannel() +
                                    " :" + anek.substring(begIndex, endIndex)));
            begIndex = endIndex;
        }
        System.out.println("ANEK:]" + "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
        client.send(
                new Message(Constants.Commands.PRIVMSG,
                        client.getChannel() +
                                " :" + "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"));
    }
}