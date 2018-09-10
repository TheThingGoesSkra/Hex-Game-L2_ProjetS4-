/*package Interface;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Point;
import java.awt.Polygon;

import javax.swing.JPanel;

public class Triangle extends JPanel { 
	  
	  public int taille;
	  
		
	  public void paint(Graphics arg0){                
			  super.paint(arg0); 
			  
			  for (int i=-1; i<this.taille-1; i++){
			  
				  Point p1 = new Point ( 23+(i*44)+42, 0); 
				  Point p2 = new Point ( 23+(i*44)+21, 13); 
				  Point p3 = new Point ( 23+(i*44)+0, 0);

				  int [] x = { p1.x , p2.x , p3.x }; 
				  int [] y = { p1.y , p2.y , p3.y };

				  Polygon p = new Polygon ( x , y, 3 ) ; 
				  arg0.setColor(Color.white);
				  arg0.fillPolygon(p);
			  }
			  for (int i=0; i<this.taille-1; i++){
				  
				  Point p1 = new Point ( 23+22*(taille-1)+44*i+21, 40+39*(taille-1)); 
				  Point p2 = new Point ( 23+22*(taille-1)+44*i-15, 39+39*(taille-1)+14+8); 
				  Point p3 = new Point ( 23+22*(taille-1)+44*i+44+14, 39+39*(taille-1)+14+8);

				  int [] x = { p1.x , p2.x , p3.x }; 
				  int [] y = { p1.y , p2.y , p3.y };

				  Polygon p = new Polygon ( x , y, 3 ) ; 
				  arg0.setColor(Color.white);
				  arg0.fillPolygon(p);
			  }
			  
			  for (int i=-1; i<this.taille-1; i++){
				  
				  Point p1 = new Point ( taille*44+i*22+1, i*39-5); 
				  Point p2 = new Point ( taille*44+i*22+1, 11+i*39+28); 
				  Point p3 = new Point ( taille*44+i*22+39, 11+i*39+51);

				  int [] x = { p1.x , p2.x , p3.x }; 
				  int [] y = { p1.y , p2.y , p3.y };

				  Polygon p = new Polygon ( x , y, 3 ) ; 
				  arg0.setColor(Color.black);
				  arg0.fillPolygon(p);
			  }
			  
			  for (int i=0; i<this.taille-1; i++){
				  
				  Point p1 = new Point ( -17+i*22, 30+i*39); 
				  Point p2 = new Point ( 22+i*22, 40+i*39+58); 
				  Point p3 = new Point ( 22+i*22, 40+i*39+12);

				  int [] x = { p1.x , p2.x , p3.x }; 
				  int [] y = { p1.y , p2.y , p3.y };

				  Polygon p = new Polygon ( x , y, 3 ) ; 
				  arg0.setColor(Color.black);
				  arg0.fillPolygon(p);
			  }
			  
			
				  Point p1 = new Point ( 22+(taille-2)*22, 40+(taille-2)*39+58); 
				  Point p3 = new Point ( 23+22*(taille-1)+2, 39+39*(taille-1)+12); 
				  Point p2 = new Point ( 23+22*(taille-1)-15, 39+39*(taille-1)+14+8); 
				  Point p4 = new Point ( 22+(taille-2)*22, 40+(taille-2)*39+35); 
				 
				  int [] x = { p1.x , p2.x , p3.x , p4.x}; 
				  int [] y = { p1.y , p2.y , p3.y , p4.y };
				  
				  Polygon pl = new Polygon ( x , y, 4 ) ; 
				  arg0.setColor(Color.black);
				  arg0.fillPolygon(pl);
	*/			  
				/*  Point p5 = new Point ( 22+(taille-2)*22, 40+(taille-2)*39+58); 
				  Point p6 = new Point ( 23+22*(taille-1)-15, 39+39*(taille-1)+14+8); 
				  Point p7 = new Point ( 23+22*(taille-1)-15, 39+39*(taille-1)+14+8); 
				  Point p8 = new Point ( 22+(taille-2)*22, 40+(taille-2)*39+35); 
				 
				  int [] x2 = { p5.x , p6.x , p7.x , p8.x }; 
				  int [] y2 = { p5.y , p6.y , p7.y , p8.y };
				  
				  Polygon pl2 = new Polygon ( x2 , y2, 4 ) ; 
				  arg0.setColor(Color.black);
				  arg0.fillPolygon(pl2);*/
				  
			  
	  
	/*  
	  }
}
*/
