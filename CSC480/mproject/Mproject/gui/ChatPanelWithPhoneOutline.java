package Mproject.gui;
import javax.swing.*;
import java.awt.*;
import java.awt.geom.RoundRectangle2D;
import java.util.ArrayList;
import java.util.HashMap;

import Mproject.client.Client;
import Mproject.message.*;
import Mproject.util.UserInfo;

public class ChatPanelWithPhoneOutline extends JPanel {
    private ArrayList<MessageBubble> messages = new ArrayList<>();
    private JTextField messageField;
    private JButton sendButton;
    private Box.Filler verticalFiller;
    private String conversationName;
    private ArrayList<Integer> recipients;
    private int groupID;
    Client client;
    private HashMap<Integer, ArrayList<Message>> msglist;

    public ChatPanelWithPhoneOutline(String ConversationName, ArrayList<Integer> Recipients, int gID, Client client, HashMap<Integer, ArrayList<Message>> msgList) {
	msglist = msgList;
    	this.client = client;

	recipients = Recipients;
	conversationName = ConversationName;
	groupID = gID;
        setLayout(null); // Use null layout for custom positioning of components
        setBackground(Color.WHITE); // Background outside the phone outline
        setPreferredSize(new Dimension(400, 600)); // Set the preferred size of the phone

        // Message display panel
        JPanel messageDisplay = new JPanel();
        messageDisplay.setLayout(new BoxLayout(messageDisplay, BoxLayout.Y_AXIS));
        messageDisplay.setBackground(Color.WHITE);

        // Add a flexible filler to push unused space below the messages
        verticalFiller = new Box.Filler(
                new Dimension(1, 1), // Minimum size
                new Dimension(1, Integer.MAX_VALUE), // Preferred size
                new Dimension(1, Integer.MAX_VALUE) // Maximum size
        );

        messageDisplay.add(verticalFiller);
	ProcessMsg proc = new ProcessMsg(msglist.get(gID), this, messageDisplay, client.userid());
	proc.start();

        JScrollPane scrollPane = new JScrollPane(messageDisplay);
        scrollPane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_NEVER);
        scrollPane.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);

        // Remove the border of the scroll pane
        scrollPane.setBorder(BorderFactory.createEmptyBorder());
        // Position and size of the scroll pane
        scrollPane.setBounds(20, 20, 360, 500);

        // Input panel
        JPanel inputPanel = new JPanel(new BorderLayout());
        inputPanel.setBounds(20, 530, 360, 50); // Position and size of the input area
        messageField = new JTextField();
        sendButton = new JButton("Send");
        inputPanel.add(messageField, BorderLayout.CENTER);
        inputPanel.add(sendButton, BorderLayout.EAST);

        sendButton.addActionListener(e -> {
            String text = messageField.getText().trim();
            if (!text.isEmpty()) {
		if(client == null) {
			System.err.println("null client");
		} else {
			client.send(new TextMessage(text, client.userId(), recipients, groupID));
		}
                addMessage(text, true, messageDisplay);
                messageField.setText("");
            }
        });

        add(scrollPane);
        add(inputPanel);

        // For demonstration: Add a received message
        addMessage("Welcome to the chat! Here's a longer message to demonstrate wrapping.", false, messageDisplay);
    }

    private void addMessage(String text, boolean isSent, JPanel messageDisplay) {
        // Remove the vertical filler temporarily
        messageDisplay.remove(verticalFiller);

        // Add padding between messages
        if (!messages.isEmpty()) {
            messageDisplay.add(Box.createVerticalStrut(10)); // Add 10px vertical padding
        }

        // Create a new MessageBubble
        MessageBubble bubble = new MessageBubble(text, isSent);

        // Add the bubble to the display
        messages.add(bubble);
        messageDisplay.add(bubble);

        // Re-add the flexible filler at the bottom
        messageDisplay.add(verticalFiller);

        // Revalidate and repaint to update the UI
        messageDisplay.revalidate();
        messageDisplay.repaint();
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        Graphics2D g2d = (Graphics2D) g;

        int outlineX = 10;
        int outlineY = 10;
        int outlineWidth = getWidth() - 20;
        int outlineHeight = getHeight() - 20;

        // Create a rounded rectangle shape for the phone outline
        RoundRectangle2D roundedRect = new RoundRectangle2D.Double(
                outlineX, outlineY, outlineWidth, outlineHeight, 50, 50);

        // Draw phone outline
        g2d.setColor(Color.BLACK);
        g2d.setStroke(new BasicStroke(10));
        g2d.draw(roundedRect);

        // Fill the phone area with white
        g2d.setColor(Color.WHITE);
        g2d.fill(roundedRect);
    }

    private static class MessageBubble extends JPanel {
        private static final int PADDING = 10;
        private static final int ARC_WIDTH = 20;
        private static final int ARC_HEIGHT = 20;

        public MessageBubble(String message, boolean isSent) {
            setLayout(new BorderLayout());
            setOpaque(false);
	    String alignment = isSent ? "right" : "left";
            // Configure label for text content
            JLabel label = new JLabel("<html><div style='width: 240px; text-align: " + "left" + "; overflow-wrap: break-word;'>" + message + "</div></html>");
            label.setForeground(isSent ? Color.WHITE : Color.BLACK);
            label.setFont(new Font("Arial", Font.PLAIN, 16));
            label.setBorder(BorderFactory.createEmptyBorder(PADDING, PADDING, PADDING, PADDING));

            setBackground(isSent ? new Color(0, 122, 255) : new Color(240, 240, 240)); // Blue for sent, gray for received
            add(label, BorderLayout.CENTER);
        }

        @Override
        protected void paintComponent(Graphics g) {
            Graphics2D g2d = (Graphics2D) g.create();
            g2d.setColor(getBackground());
            g2d.fillRoundRect(0, 0, getWidth(), getHeight(), ARC_WIDTH, ARC_HEIGHT);
            g2d.dispose();
            super.paintComponent(g);
        }

        @Override
        public Dimension getPreferredSize() {
            Component label = getComponent(0); // Get the label component
            Dimension labelSize = label.getPreferredSize();

            // Bubble size is label size + padding
            return new Dimension(labelSize.width + 2 * PADDING, labelSize.height + 2 * PADDING);
        }
    }

    public static void main(String[] args) {
	/*
        JFrame frame = new JFrame("Chat Panel with Phone Outline");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	ArrayList<Integer> recipients = null;

        ChatPanelWithPhoneOutline chatPanel = new ChatPanelWithPhoneOutline("TEST", recipients);
        frame.add(chatPanel);

        frame.pack(); // Adjust frame to fit preferred size
        frame.setLocationRelativeTo(null); // Center on screen
        frame.setVisible(true);
	*/
    }


    private class ProcessMsg extends Thread {
	ArrayList<Message> msglist;
	ChatPanelWithPhoneOutline cpan;
	JPanel msgdisplay;
	int uid;

	public ProcessMsg(ArrayList<Message> msgList, ChatPanelWithPhoneOutline c, JPanel msgDisp, int uId) {
		msglist = msgList;
		cpan = c;
		msgdisplay = msgDisp;
		uid = uId;
	}

    	@Override
	public void run() {
		

    // private void addMessage(String text, boolean isSent, JPanel messageDisplay) {
		while(true) {
			if(!msglist.isEmpty()) {
				TextMessage tm = (TextMessage)msglist.get(0);
				if(tm.userid() != uid) {
					UserInfo test = new UserInfo();
					String txt = "<b>" + test.getUsername(tm.userid()) + ":</b> ";
					txt += tm.getText();
					cpan.addMessage(txt, false, msgdisplay);
				}
				msglist.remove(0);
			} else {
				try {
					sleep(200);
				} catch (Exception e) { 
				}
			}
		}
	
	};
    }
}

