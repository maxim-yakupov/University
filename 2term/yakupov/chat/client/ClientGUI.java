package yakupov.chat.client;

import yakupov.chat.common.Message;

import javax.swing.*;
import java.awt.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

/**
 * Class of client's GUI
 */
public class ClientGUI {

    private final Client client;
    private JFrame frame;
    private JButton button;
    private JTextArea displayArea;
    private JTextField typingArea;

    /**
     * Constructor of client's GUI
     * @param client Client-parent
     */
    public ClientGUI(final Client client) {
        this.client = client;
        initComponents();
        SwingUtilities.invokeLater(this::setGUI);
    }

    /**
     * Places components and adds listeners
     */
    private void setGUI() {
        frame.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
        addComponentsToPane();
        frame.pack();
        addListenersToComponents();
        frame.setVisible(true);
    }

    /**
     * Initialised components
     */
    private void initComponents() {
        frame = new JFrame("Chat | user: " + client.getSettings().getName());
        button = new JButton("Clear(history stays)");
        typingArea = new JTextField(20);
        displayArea = new JTextArea();
    }

    /**
     * Places components on content pane
     */
    private void addComponentsToPane() {
        displayArea.setEditable(false);
        JScrollPane scrollPane = new JScrollPane(displayArea);
        scrollPane.setPreferredSize(new Dimension(375, 125));

        frame.add(typingArea, BorderLayout.PAGE_START);
        frame.add(scrollPane, BorderLayout.CENTER);
        frame.add(button, BorderLayout.PAGE_END);
    }

    /**
     * Adds listeners to components
     */
    private void addListenersToComponents() {
        button.addActionListener(e -> {
            displaySetText("", false);
            typeAreaSetText("");
        });
        typingArea.addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                int keyCode = e.getKeyCode();
                String text = typeAreaGetText();
                if (KeyEvent.getKeyText(keyCode).equals("Enter")
                        && !text.equals("")
                        ) {
                    Message msg = new Message(client.getSettings().getName(), Message.Codes.MSG, text);
                    displaySetText(msg + "\n", true);
                    typeAreaSetText("");
                    System.out.println(msg);//////
                    client.sendMessage(msg);
                }
            }
        });
        frame.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                client.stop();
            }
        });
    }

    /**
     * Shows message on screen
     * @param msg Message
     */
    public void showNewMessageAsync(Message msg) {
        displaySetText(msg.toString() + "\n", true);
    }

    /**
     * Stops GUI
     */
    public void stop() {
        frame.dispose();
    }

    /**
     * Prints text in messages area
     * @param str text
     * @param append <ul>
     *               <li>if 'true' - append mode</li>
     *               <li>if 'false' - replace mode</li>
     *               </ul>
     */
    private void displaySetText(final String str, final boolean append) {
        SwingUtilities.invokeLater(() -> {
            if (append) {
//                    displayArea.append(str);//adds message on top
                displayArea.setText(displayArea.getText() + str);//adds message at bottom
            } else {
                displayArea.setText(str);
            }
        });
    }

    /**
     * Set text in editable area
     * @param str text
     */
    private void typeAreaSetText(final String str) {
        SwingUtilities.invokeLater(() -> typingArea.setText(str));
    }

    /**
     * Returns text from editable area
     * @return text
     */
    private String typeAreaGetText() {
        return typingArea.getText();
    }
}