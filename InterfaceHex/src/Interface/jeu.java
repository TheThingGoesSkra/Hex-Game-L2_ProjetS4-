package Interface;

import java.awt.BasicStroke;
import java.awt.BorderLayout;
import java.awt.CheckboxMenuItem;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Frame;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Menu;
import java.awt.MenuBar;
import java.awt.MenuItem;
import java.awt.Point;
import java.awt.Polygon;
import java.awt.Rectangle;
import java.awt.event.KeyListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;
import java.util.Scanner;
import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.RootPaneContainer;
import javax.swing.SwingConstants;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import java.awt.MenuBar;

public class jeu extends Frame{
	
	public static void main(String[] args) {
		
		JFrame win=new JFrame(); // Crée la fenetre principale
		win.setTitle("HEX");
		win.setSize(1000, 750);// Redimensionne la fenetre			
		win.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);// Permet de quiter l'application à la fermeture de la fenêtre
		win.setLocationRelativeTo(null);
		win.setVisible(true);// Affiche la fenetre
		//win.setLayout(new BorderLayout());
		//JPanel container = new JPanel(); 
		//JTextField jtf = new JTextField("");
		//JLabel label = new JLabel("Veuillez saisir les coordonnées du coup:");
		JPanel jpBase=(JPanel) win.getContentPane(); // Récupère le conteneur de la fenêtre
		win.setContentPane(jpBase); 
		//MenuFenetre m = new MenuFenetre();
	    //swin.setMenuBar(m);
	    //container.setBackground(Color.white);
	    //container.setLayout(new BorderLayout());	    
	    //Font police = new Font("Arial", Font.BOLD, 14);
	    //jtf.setFont(police);
	    //jtf.setPreferredSize(new Dimension(150, 30));
	    //jtf.setForeground(Color.BLUE);
	    //label.setBounds(10, 20, 10, 10);
	    //jpBase.add(label);
	    //label.setBounds(10, 10, 10, 10);
	    //jpBase.add(jtf, BorderLayout.SOUTH);
		
	    
		final AffGrille jpJeu=new AffGrille(6, 0);
		
		jpBase.add(jpJeu);// Ajoute le composant à la fenêtre
		win.setVisible(true);// Affiche la fenetre
	}


}


