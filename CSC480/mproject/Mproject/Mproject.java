package Mproject;

import javax.swing.*;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.CardLayout;

import Mproject.gui.PhoneGUI;
import Mproject.client.*;
import Mproject.manager.DisplayManager;

public class Mproject {
	public static void main(String[] args) {
		System.out.println("Main");
		DisplayManager mgr = DisplayManager.getInstance();
		PhoneGUI launcher = new PhoneGUI();
		mgr.add(launcher, "launcher");
		mgr.show();
		
/*
		JFrame window = new JFrame();
		CardLayout cl = new CardLayout();
		JPanel display = new JPanel(cl);
		PhoneGUI launcher = new PhoneGUI(display);
		// Client client = new Client();

		display.add(launcher, "launcher");
		window.add(display);
		window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		// window.setLocationRelativeTo(null);
		window.pack();
		window.setVisible(true);


		while(!launcher.loginComplete()) {
		}

		// cl.previous(display);
		cl.last(display);

*/
	}


}
