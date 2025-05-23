package Mproject.gui;

import java.util.*;
import javax.swing.*;
import java.awt.*;
import java.awt.geom.RoundRectangle2D;

import java.awt.event.*;


import Mproject.util.BoolRef;
import Mproject.manager.DisplayManager;
import Mproject.client.Client;
import Mproject.util.MessageQueue;
import Mproject.message.*;

public class MessagePickerGUI extends JPanel {

    private ArrayList<JButton> appButtons = new ArrayList<JButton>();
    private Client client;
    BoolRef loginComplete;
    HashMap<Integer, ArrayList<Message>> messageLists = new HashMap<Integer, ArrayList<Message>>();


	public HashMap<Integer, ArrayList<Message> > getMessageLists() {
		return messageLists;
	}
	public void setClient(Client c) {
		client = c;
	}
	public Client getClient() {
		return client;
	}

    public MessagePickerGUI(BoolRef logincomplete) {
	//initialize the groupID map
	
	loginComplete = logincomplete;
        setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
        setPreferredSize(new Dimension(400, 600));
        setOpaque(false); // Make the panel transparent

        // Create a sub-panel for the buttons and title
        JPanel contentPanel = new JPanel();
        contentPanel.setLayout(new BoxLayout(contentPanel, BoxLayout.Y_AXIS));
        contentPanel.setOpaque(false); // Make the content panel transparent

        // Add title
        JLabel title = new JLabel("Messages");
        title.setFont(new Font("Arial", Font.BOLD, 24)); // Set font style and size
        title.setForeground(Color.BLACK); // Set title color
        title.setAlignmentX(0.1f); // Center the title
        contentPanel.add(Box.createRigidArea(new Dimension(0, 20))); // Space above title
        contentPanel.add(title);
        contentPanel.add(Box.createRigidArea(new Dimension(0, 10))); // Space between title and buttons

	    // add global chat box
            JButton appButton = new JButton("Global Chat");
            appButton.setFocusPainted(false);
            appButton.setContentAreaFilled(false); // Transparent background
            appButton.setBorderPainted(false); // No border
            appButton.setForeground(Color.BLACK); // Change text color if needed
            appButton.setAlignmentX(0.1f);

	    ArrayList<Message> globalMessageList = new ArrayList<Message>();
	    messageLists.put(1, globalMessageList);

	    appButton.addActionListener(new ConversationButtonPress("Global Chat", new ArrayList<Integer>(), 1, this));
            ImageIcon originalIcon = new ImageIcon("assets/images/profile_icon.png"); 
            Image originalImage = originalIcon.getImage();
            Image resizedImage = originalImage.getScaledInstance(50, 50, Image.SCALE_SMOOTH); // Resize icon
            appButton.setIcon(new ImageIcon(resizedImage));
            appButtons.add(appButton);
            contentPanel.add(appButton);
            contentPanel.add(Box.createRigidArea(new Dimension(0, 10))); // Add spacing between buttons


        // Add app icons (JButtons)
        for (int i = 2; i <= 5; i++) {
            appButton = new JButton("User Chat");
            appButton.setFocusPainted(false);
            appButton.setContentAreaFilled(false); // Transparent background
            appButton.setBorderPainted(false); // No border
            appButton.setForeground(Color.BLACK); // Change text color if needed
            appButton.setAlignmentX(0.1f);
	    // TODO: Actionlisteners for the buttons

            // Set the icon Replace with your icon path
            originalIcon = new ImageIcon("assets/images/profile_icon.png"); 
            originalImage = originalIcon.getImage();
            resizedImage = originalImage.getScaledInstance(50, 50, Image.SCALE_SMOOTH); // Resize icon
            appButton.setIcon(new ImageIcon(resizedImage));

            appButtons.add(appButton);
            contentPanel.add(appButton);
            contentPanel.add(Box.createRigidArea(new Dimension(0, 10))); // Add spacing between buttons
        }

        add(contentPanel); // Add content panel to the main panel
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        // Save the original graphics context
        Graphics2D g2d = (Graphics2D) g;
        int outlineX = 5;
        int outlineY = 5;
        int outlineWidth = getWidth() - 10;
        int outlineHeight = getHeight() - 10;

        // Create a rounded rectangle shape for the outline
        RoundRectangle2D roundedRect = new RoundRectangle2D.Double(outlineX, outlineY, outlineWidth, outlineHeight, 30, 30);

        // Set the stroke thickness for the outline
        g2d.setStroke(new BasicStroke(5)); // Change the number to increase/decrease thickness

        // Draw phone outline
        g2d.setColor(Color.BLACK);
        g2d.draw(roundedRect); // Draw the outline
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("Phone GUI");
	JPanel p = new JPanel(new CardLayout());
        //MessagePickerGUI pickerGUI = new MessagePickerGUI(p, new BoolRef(true));

        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        //frame.add(pickerGUI);
        frame.pack();
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
    }

    // show login and authenticate, will only return when authenication passes

	public void showLogin() {
		JPanel container = new JPanel();
		JPanel login = new ChatLogin(loginComplete, this);
		container.add(login);
		container.setSize(login.getLayout().minimumLayoutSize(container));
		//CardLayout cl = (CardLayout)displayPanel.getLayout();
		DisplayManager mgr = DisplayManager.getInstance();
		mgr.add(container, "login");
		mgr.set("login");
	}

	private class ConversationButtonPress implements ActionListener {
		private String cname;
		private ArrayList<Integer> recipients;
		private MessageQueue mq;
		private Client clientref;
		private int groupID;
		MessagePickerGUI mp;

		public ConversationButtonPress(String convoName, ArrayList<Integer> Recipients, int ID, MessagePickerGUI mpg) {
			cname = convoName;
			recipients = Recipients;
			groupID = ID;
			mp = mpg;
		}

		public void actionPerformed(ActionEvent e) {
			JPanel conversationPanel = new ChatPanelWithPhoneOutline(cname, recipients, groupID, mp.getClient(), mp.getMessageLists());
			DisplayManager.getInstance().add(conversationPanel, cname);
			DisplayManager.getInstance().set(cname);
		}
	}

}




