package Interface;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Rectangle;

import javax.swing.JPanel;

public class Pionb extends JPanel {
	
	  public void paint(Graphics arg0){                
		  super.paint(arg0);
	      arg0.setColor(Color.white);
	      arg0.fillOval(0, 0, this.getWidth(), this.getHeight());
	  } 
}
