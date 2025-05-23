package Mproject.gui;

import java.util.*;
import javax.swing.*;
import java.awt.event.*;
import java.awt.*;
import java.awt.geom.RoundRectangle2D;


import Mproject.util.BoolRef;
import Mproject.manager.DisplayManager;

public class PhoneGUI extends JPanel {

    private ImageIcon gifBackground;
    private ArrayList<JButton> appButtons = new ArrayList<JButton>();
    private JPanel applicationDisplay;
    private JPanel loginpanel;

    // TODO: fix the state management in this 
    BoolRef loginComplete;

    public boolean loginComplete() {
	    return loginComplete.get();
    }

    public JPanel getActiveDisplay() {
	    return applicationDisplay;

    }
    
    //public PhoneGUI(JPanel parent) {
    public PhoneGUI() {
	loginComplete = new BoolRef(false);
        gifBackground = new ImageIcon("assets/images/wallpaper.gif");
        setLayout(new GridLayout(4, 3)); // 4 rows and 3 columns
        setPreferredSize(new Dimension(400, 600));

        // fill in the rest of the app spaces (Jbuttons)
        for (int i = 1; i <= 12; i++) {
            JButton appButton = new JButton("App " + i);
            appButton.setFocusPainted(false);
            appButton.setContentAreaFilled(false); // Transparent background
            appButton.setBorderPainted(false); // No border
            appButton.setForeground(Color.WHITE); // Change text color if needed
	    appButtons.add(appButton);
            add(appButton);
        }

	// Change App Icon // ***Temp*** TODO make custom Icon Class
	ImageIcon originalIcon = new ImageIcon("assets/images/message_icon.png"); // Replace with your icon path
	// Resize the icon
	Image originalImage = originalIcon.getImage();
	Image resizedImage = originalImage.getScaledInstance(75, 75, Image.SCALE_SMOOTH); // Set desired width and height
	ImageIcon resizedIcon = new ImageIcon(resizedImage);

	JButton mchat = appButtons.get(0);
	mchat.setIcon(resizedIcon);
	mchat.setText("Message");
	// Set the text position below the icon
	mchat.setHorizontalTextPosition(SwingConstants.CENTER); // Center the text horizontally
	mchat.setVerticalTextPosition(SwingConstants.BOTTOM); // Place text below the icon
	mchat.setPreferredSize(new Dimension(150, 100));
	//mchat.addActionListener(new MchatButtonCallback(parent, loginComplete));
	mchat.addActionListener(new ActionListener(){
	    public void actionPerformed(ActionEvent e) {
		DisplayManager mgr = DisplayManager.getInstance();
		MessagePickerGUI messagePicker = new MessagePickerGUI(loginComplete);
		mgr.add(messagePicker, "messagePicker");
		mgr.set("messagePicker");
		messagePicker.showLogin();
	    }
	});
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
        RoundRectangle2D roundedRect = new RoundRectangle2D.Double(outlineX, outlineY,
									outlineWidth, outlineHeight, 30, 30);
        
        // Set the clipping area to the rounded rectangle
        g2d.setClip(roundedRect);

        // Draw background GIF
        g2d.drawImage(gifBackground.getImage(), 0, 0, getWidth(), getHeight(), this);

        // Reset the clipping area
        g2d.setClip(null);

        // Set the stroke thickness for the outline
        g2d.setStroke(new BasicStroke(5)); // Change the number to increase/decrease thickness

        // Draw phone outline
        g2d.setColor(Color.BLACK);
        g2d.draw(roundedRect); // Draw the outline
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("Phone GUI");
	JPanel p = new JPanel(new CardLayout());
        //PhoneGUI phoneGUI = new PhoneGUI(p);

        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        //frame.add(phoneGUI);
        frame.pack();
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
    }

    private class MchatButtonCallback implements ActionListener {
	    JPanel display;
	    CardLayout cl;
	    BoolRef logincomplete;
	    public MchatButtonCallback(JPanel parent, BoolRef loginComplete) {
		    logincomplete = loginComplete;
		    display = parent;
		    cl = (CardLayout)parent.getLayout();
	    }

	    @Override
	    public void actionPerformed(ActionEvent e) {
		    //MessagePickerGUI messagePicker = new MessagePickerGUI(display, loginComplete);
		    //display.add(messagePicker, "messagePicker");
		    cl.show(display, e.getActionCommand());
		    //messagePicker.showLogin();
	    }
    }

}

