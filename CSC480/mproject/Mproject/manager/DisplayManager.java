package Mproject.manager;

import javax.swing.*;
import java.awt.*;

public class DisplayManager{
	private static DisplayManager mgr;
	private static JFrame window;
	private static JPanel panel;
	private static CardLayout cl;
	private static String hello = "HELLO";

	private DisplayManager(){
		window = new JFrame(); // todo set values
		cl = new CardLayout();
		panel = new JPanel(cl);
	}

	public static DisplayManager getInstance(){
		if (mgr==null){
			mgr = new DisplayManager();
		}
		return mgr;
	}

	public void show(){
		window.add(panel);
		window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		window.pack();
		window.setVisible(true);
	}

	public void add(JPanel p, String pname){
		panel.add(p, pname);
	}

	public void set(String pname){
		cl.show(panel, pname);
	}

	public void sayhello() {
		System.out.println(hello);
	}

}
