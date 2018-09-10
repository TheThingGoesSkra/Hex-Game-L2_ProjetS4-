package Interface;

import java.awt.Color;
import java.awt.Graphics;
import javax.swing.JPanel;

public class Pion extends JPanel { 
  
  public void paint(Graphics arg0){                
      super.paint(arg0);
      arg0.setColor(Color.black);
	  arg0.fillOval(0, 0, this.getWidth(), this.getHeight());
  }       
}