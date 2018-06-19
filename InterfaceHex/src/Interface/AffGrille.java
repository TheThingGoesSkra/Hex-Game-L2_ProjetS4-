package Interface;

import java.awt.BasicStroke;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.FlowLayout;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Point;
import java.awt.Polygon;
import java.awt.Rectangle;
import java.awt.TextArea;
import java.awt.Window;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;
import java.awt.event.WindowEvent;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.FilterWriter;
import java.io.IOException;
import java.net.URL;
import java.util.ArrayList;

import javax.swing.Icon;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;
	
		class AffGrille extends JPanel{
		
			
		// Classe personnelle qui crée une grile hexagonale.
			final static int cote=26; // Ceci définit la taille du côté d'un polygone
			private int numero=0; // Retien le n° du polygone sur lequel est la souris
			private Polygon pol;
			private int n;
			private ihm i;
			private int dc=-1;
			private JLabel ph = new JLabel("<html><span style=color:#000000>C'est au joueur blanc de jouer !</span></html>");
			private JLabel ph2 = new JLabel("<html><span style=color:#000000>C'est au joueur noir de jouer !</span></html>");
			private Triangle t=new Triangle();
			
		public AffGrille(int nb, int c){
				
				//JLabel dc = new JLabel("<html><span style=color:#000000>Coordonées du dernier coup joué : ("+(numero%n)+","+(numero/n)+")</span></html>");
				
				/*add(dc);
				setLayout(null);
				dc.setBounds(0, 20+40*n, 200, 30); 
				dc.setOpaque(false);*/					
					setLayout(null);
					
					init_ihm(nb,c);
					
					this.n=nb; 				
					ph.setBounds(0, 20+40*n, 200, 50); 
					ph.setOpaque(true);
					ph.setBackground(Color.GRAY);
					ph2.setBounds(0, 20+40*n, 200, 50);
					
					JLabel Icone1=new JLabel();
					Icone1.setIcon(new javax.swing.ImageIcon(getClass().getResource("2435.PNG")));
			        JLabel Icone2=new JLabel();
					Icone2.setIcon(new javax.swing.ImageIcon(getClass().getResource("reset.PNG")));
			        JLabel Icone3=new JLabel();
					Icone3.setIcon(new javax.swing.ImageIcon(getClass().getResource("Sauvegarder.PNG")));
		       
				 	add(Icone1);
			        Icone1.setVisible(true);
			        Icone1.setBounds(nb*60, 12+15+nb*40, 50, 50);
			        add(Icone2);
			        Icone2.setVisible(true);
			        Icone2.setBounds(nb*60-70, 10+19+nb*40, 60, 50);
			        add(Icone3);
			        Icone3.setVisible(true);
			        Icone3.setBounds(nb*60-128, 10-205+nb*40, 50, 500);
			        
			        t.taille=this.n;
					setLayout(null);
					add(t);
					t.setOpaque(false);
					t.setBounds(0, 0, 1500, 1500);
				
    			this.setBackground(Color.GRAY); // Crée une instance de la classe privée AffGrille	
    			this.addMouseMotionListener(new MouseMotionListener(){
    				Polygon p;
    				public void mouseDragged(MouseEvent arg0) {
    					// TODO Auto-generated method stub
    				}
    				public void mouseMoved(MouseEvent arg0) {
    					p=pol;
    					if(!p.contains(arg0.getPoint())){
    						repaint();
    					}
    				}});// Repeind jpJeu lorsque la souris se déplace
    			
    			
			}
			
			public void init_ihm(int nb,int c){
				i=new ihm(nb, c);
    			add(i);
				i.setBounds(0,0,1500,1500);
				i.setVisible(true);
				i.setOpaque(false);
			}

			public void paint(Graphics arg0) {
				super.paint(arg0);
				int j2=i.j;
				dc=i.dc;
				
				if(j2==1)
					add(ph);
				if(j2!=1)
					remove(ph);
				add(ph2);

					
				Polygon p2=getPolygon(0, 0, cote); // Crée un hexagone
				Rectangle r=p2.getBounds(); // Récupère le plus petit rectangle // aux bord de la fenêtre dans lequel l'hexagone peut s'inscrire
				Point hovered=null;
				arg0.setColor(Color.black);
				Graphics2D g2d;
				int nb=this.n;
				
				g2d=(Graphics2D) arg0;
				BasicStroke bs1=new BasicStroke(1);// Permet de fixer l'épaisseur du trait dans la suite
				BasicStroke bs3=new BasicStroke(3);// Idem
				
				g2d.setStroke(bs1);
				

				int j=0;
				i.numero=-1;

				
				for(int l=0;l<nb;l=l+2){// Remarquer le "+2" car la grille est constituée de 2 sous grilles (les lignes impaires sont décallées)
					for(int c=j;c<nb+j;c++){
						Point p;
						p=getMousePosition();
						Polygon poly=getPolygon(c*r.width, (int)(l*cote*1.5),cote);
						if(p!=null && poly.contains(p)){
							hovered=new Point(c*r.width, (int)(l*cote*1.5));
							numero=l*nb+c-j;
							i.numero=numero;
							pol=poly;
						}
						g2d.draw(poly);
					}
					j++;
				}
				
				j=0;
				for(int l=1;l<nb;l=l+2){
					for(int c=j;c<nb+j;c++)
					{
						Point p;
						p=getMousePosition();
						Polygon poly=getPolygon(c*r.width+r.width/2,  (int)(l*cote*1.5+0.5),cote);
						arg0.setColor(Color.black);
						if(p!=null && poly.contains(p)){
							hovered=new Point(c*r.width+r.width/2,  (int)(l*cote*1.5+0.5));
							numero=l*nb+c-j;
							i.numero=numero;
							pol=poly;
						}
						g2d.draw(poly);
					}
					j++;
				}
				
				if(hovered!=null && !i.listepion2.contains(i.numero)){
					arg0.setColor(Color.red);
					g2d.setStroke(bs3);
					Polygon p=getPolygon(hovered.x, hovered.y,cote);
					g2d.draw(p);
				}
				
				if(dc!=-1){
					arg0.setColor(Color.blue);
					g2d.setStroke(bs1);
					Polygon p=getPolygon((dc%nb)*r.width+(dc/nb)*r.width/2, (int)((dc/nb)*cote*1.5+0.5),cote);
					g2d.draw(p);
				}		
			    
				repaint();
				//invalidate();
			}

				
			
			public Polygon getPolHover(){
				return pol;
			}

			public static Polygon getPolygon(int x,int y,int cote){// Forme le polygone
				int haut=cote/2;
				int larg=(int)(cote*(Math.sqrt(3)/2));
				Polygon p=new Polygon();
				p.addPoint(x,y+haut);// /
				p.addPoint(x+larg,y); // \
				p.addPoint(x+2*larg,y+haut);// |
				p.addPoint(x+2*larg,y+(int)(1.5*cote)); // /
				p.addPoint(x+larg,y+2*cote);// \
				p.addPoint(x,y+(int)(1.5*cote));//
				return p;
			}
			
			public static Polygon getCarre(){// Forme un carré pour les boutons
				Polygon p=new Polygon();
				p.addPoint(0,0);
				p.addPoint(0,50); 
				p.addPoint(50,50);
				p.addPoint(50,0); 
				return p;
			}
		}

