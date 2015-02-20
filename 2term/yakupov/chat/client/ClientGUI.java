package yakupov.chat.client;

import javax.swing.*;
import java.awt.*;

public class ClientGUI extends JFrame {

    private Client client;
    private JTextArea displayArea = new JTextArea();
    private JTextField typingArea = new JTextField();

    public ClientGUI(final Client client) {
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                ClientGUI frame = new ClientGUI(client, "Chat | user: " + client.getName());
                frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                frame.addComponentsToPane();
                frame.pack();
                frame.setVisible(true);
            }
        });
    }

    private ClientGUI(Client client, String name) {
        super(name);
        this.client = client;
    }

    private void addComponentsToPane() {
        ClientGUIListeners control = new ClientGUIListeners(this, client);

        JButton button = new JButton("Clear(history stays)");
        button.addActionListener(control.getActionL());

        typingArea = new JTextField(20);
        typingArea.addKeyListener(control.getKeyL());

        displayArea = new JTextArea();
        displayArea.setEditable(false);
        JScrollPane scrollPane = new JScrollPane(displayArea);
        scrollPane.setPreferredSize(new Dimension(375, 125));

        getContentPane().add(typingArea, BorderLayout.PAGE_START);
        getContentPane().add(scrollPane, BorderLayout.CENTER);
        getContentPane().add(button, BorderLayout.PAGE_END);
    }

    public void displaySetText(String str, boolean append) {
        if (append) {
            displayArea.append(str);
        } else {
            displayArea.setText(str);
        }
    }

    public void typeAreaSetText(String str) {
        typingArea.setText(str);
    }

    public String typeAreaGetText() {
        return typingArea.getText();
    }
}