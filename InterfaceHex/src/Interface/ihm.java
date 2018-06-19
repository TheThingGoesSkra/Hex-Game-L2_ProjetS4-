package Interface;

import java.awt.Frame;
import java.awt.Point;
import java.awt.Polygon;
import java.awt.Rectangle;
import java.awt.TextArea;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

import Interface.AffGrille;

public class ihm extends JPanel{
		
	private int n; 
	public int numero;
	public int j=1;
	public int dc=-1;
	private int rep;
	public int IA;
	private int IAjoue;
	public ArrayList<Integer> listepion2 = new ArrayList<Integer>();
	
	public ihm(int nb, int c){
		
		this.n=nb;
	    ArrayList<JPanel> listepion = new ArrayList<JPanel>();

	    
	    IAjoue=InterfaceAvecC.get_plat_IA();
		   
	    test_ia();

			
			this.addMouseListener(new MouseAdapter(){
				public void mouseClicked(MouseEvent arg0) {
					super.mouseClicked(arg0);
					Polygon p1=AffGrille.getPolygon(0, 0, 26);
					Rectangle r=p1.getBounds();
					initMenus(arg0);
					int buttonDown = arg0.getButton();
					if (buttonDown==MouseEvent.BUTTON1 && IA==0){
					if (numero!=-1 && !listepion2.contains(numero)){
					if (j==1){
						Pionb pb=new Pionb();
						if(dc!=-1){
							remove(listepion.get(listepion.size()-1));
							listepion2.remove(listepion2.size()-1);
							}
						add(pb);
						listepion.add(pb);
						dc=numero;
						listepion2.add(dc);
						pb.setOpaque(false);
						pb.setVisible(true);
						pb.setBounds((int)((((numero%n))*r.width+(r.width/2)*(numero/(n)))+(r.getWidth()/6)), (int)((numero/(n))*26*1.5+(r.getHeight()/5))+1, 30, 30);	    
					}
					else if (j==2){
    					Pion p=new Pion();
    					if(dc!=-1){
							remove(listepion.get(listepion.size()-1));
							listepion2.remove(listepion2.size()-1);
							}
				        add(p);
				        dc=numero;
						listepion.add(p);
						listepion2.add(dc);
						p.setOpaque(false);
						p.setVisible(true);
						p.setBounds((int)((((numero%n))*r.width+(r.width/2)*(numero/(n)))+(r.getWidth()/6)), (int)((numero/(n))*26*1.5+(r.getHeight()/5))+1, 30, 30);
					}}}
					if (buttonDown==MouseEvent.BUTTON3 && IA==0){
						if (j==1){
							if (dc!=-1){
								InterfaceAvecC.jouer_coup( dc/n, dc%n, 1);
								j=2;
								dc=-1;
								if (InterfaceAvecC.a_gagne()==1){
									 int dialogButton = JOptionPane.YES_NO_OPTION;
										int i = JOptionPane.showConfirmDialog (null, "Voulez-vous recommencer la partie ? ","Le joueur 1 a gagné",dialogButton);
										if(i==0){ 
						                	InterfaceAvecC.init_plateau(n);
						                	InterfaceAvecC.init_ia(IAjoue, 0);
						                	removeAll();
						                	listepion2.removeAll(listepion2);
						                	repaint();
						                	j=1;
						                	dc=-1;
						                	IAjoue=InterfaceAvecC.get_plat_IA();
						            	    test_ia();
										}
										else{
											JFrame win=new Acceuil();
						                	SwingUtilities.getWindowAncestor(getParent()).dispose();
											win.setSize(800,450);
					    					win.setVisible(true);
										}
									}	
								else if(IAjoue==2){
									IA=2;
									int num=InterfaceAvecC.jouer_ia(IA);
					        		afficher_pion(num,IA);
					        		if (InterfaceAvecC.a_gagne()==2){
										 int dialogButton = JOptionPane.YES_NO_OPTION;
										int i = JOptionPane.showConfirmDialog (null, "Voulez-vous recommencer la partie ? ","Le joueur 2 a gagné",dialogButton);
										if(i==0){ 
						                	InterfaceAvecC.init_plateau(n);
						                	InterfaceAvecC.init_ia(IAjoue, 0);
						                	removeAll();
						                	listepion2.removeAll(listepion2);
						                	repaint();
						                	j=1;
						                	dc=-1;
						                	IAjoue=InterfaceAvecC.get_plat_IA();
						            	    test_ia();
										}
										else{
											JFrame win=new Acceuil();
						                	SwingUtilities.getWindowAncestor(getParent()).dispose();
											win.setSize(800,450);
					    					win.setVisible(true);
										}
									}
									j=1;
									IA=0;}
							}		
						}
						else if (j==2){
							if (dc!=-1){
								InterfaceAvecC.jouer_coup( dc/n, dc%n, 2);
								j=1;
								dc=-1;
								if (InterfaceAvecC.a_gagne()==2){
										int dialogButton = JOptionPane.YES_NO_OPTION;
										int i = JOptionPane.showConfirmDialog (null, "Voulez-vous recommencer la partie ? ","Le joueur 2 a gagné",dialogButton);
										if(i==0){ 
						                	InterfaceAvecC.init_plateau(n);
						                	InterfaceAvecC.init_ia(IAjoue, 0);
						                	removeAll();
						                	listepion2.removeAll(listepion2);
						                	repaint();
						                	j=1;
						                	dc=-1;
						                	IAjoue=InterfaceAvecC.get_plat_IA();
						            	    test_ia();
									}
										else{
											JFrame win=new Acceuil();
						                	SwingUtilities.getWindowAncestor(getParent()).dispose();
											win.setSize(800,450);
					    					win.setVisible(true);
										}
								}								
								else if(IAjoue==1){
									IA=1;
									int num=InterfaceAvecC.jouer_ia(IA);
					        		afficher_pion(num,IA);
									if (InterfaceAvecC.a_gagne()==1){
										int dialogButton = JOptionPane.YES_NO_OPTION;
										int i = JOptionPane.showConfirmDialog (null,  "Voulez-vous recommencer la partie ? ","Le joueur 1 a gagné",dialogButton);
										if(i==0){ 
											InterfaceAvecC.init_plateau(n);
						                	InterfaceAvecC.init_ia(IAjoue, 0);
						                	removeAll();
						                	listepion2.removeAll(listepion2);
						                	repaint();
						                	j=1;
						                	dc=-1;
						                	IAjoue=InterfaceAvecC.get_plat_IA();
						            	    test_ia();
										}	else{
											JFrame win=new Acceuil();
						                	SwingUtilities.getWindowAncestor(getParent()).dispose();
											win.setSize(800,450);
					    					win.setVisible(true);
										}
									}
					        		j=2;
									IA=0;}
							}
						}
					}
					setVisible(true);
					
					}});
			
		    if (c==1){
		    	init_plat();
		    }
	}
	
	
		public void initMenus(MouseEvent arg0){
			Point pt;
			pt=getMousePosition();
			int buttonDown = arg0.getButton();
			if (buttonDown==MouseEvent.BUTTON1){
				if((pt.getX()>n*60 && pt.getX()<n*60+50 && pt.getY()>15+n*40 && pt.getY()<15+n*40+50)){
					 int dialogButton = JOptionPane.YES_NO_OPTION;
		                int i = JOptionPane.showConfirmDialog (null, "Etes-vous sur de vouloir quitter ? ","Attention",dialogButton);
		                if(i==0){ 
		                	JFrame win=new Acceuil();
		                	SwingUtilities.windowForComponent(this).dispose();
		    				win.setSize(800,450);
		    				win.setVisible(true);
		                }
				}
				if((pt.getX()>n*60-70 && pt.getX()<n*60+50-70 && pt.getY()>15+n*40 && pt.getY()<15+n*40+50)){
					 int dialogButton = JOptionPane.YES_NO_OPTION;
		                int i= JOptionPane.showConfirmDialog (null, "Voulez-vous recommencer la partie ? ","Attention",dialogButton);
		                if(i==0){ 
		                	InterfaceAvecC.init_plateau(n);
		                	InterfaceAvecC.init_ia(IAjoue, 0);
		                	removeAll();
		                	listepion2.removeAll(listepion2);
		                	repaint();
		                	j=1;
		                	dc=-1;
		                	IAjoue=InterfaceAvecC.get_plat_IA();
		            	    test_ia();
		                    dc=-1;
		                }
		        }
				if((pt.getX()>n*60-128 && pt.getX()<n*60+50-128 && pt.getY()>15+n*40 && pt.getY()<15+n*40+50)){
					JFileChooser filechoose = new JFileChooser();
					// CrÃ©er un JFileChooser
					filechoose.setCurrentDirectory(new File(".")); // Le rÃ©pertoire
					String approve = new String("ENREGISTRER");
					int resultatEnregistrer = filechoose.showDialog(filechoose,approve); // Pour afficher le JFileChooser...
					if (resultatEnregistrer == JFileChooser.APPROVE_OPTION) 
					   { String monFichier= new String(filechoose.getSelectedFile().toString());
					// RÃ©cupÃ©rer le nom du fichier qu'il a spÃ©cifiÃ©
					if(monFichier.endsWith(".txt")|| monFichier.endsWith(".TXT")) {;}
					// Si ce nom de fichier finit par .txt ou .TXT, ne rien faire et passer Ã 
					else 
					   monFichier = monFichier+ ".txt";
					// Sinon renommer le fichier pour qu'il porte l'extension .txt
					InterfaceAvecC.sauvegarde(monFichier); 
				}}
			}}
		
		private void afficher_pion(int k, int couleur){
			Polygon p1=AffGrille.getPolygon(0, 0, 26);
			Rectangle r=p1.getBounds();
			if (couleur==1){
				Pionb pb=new Pionb();
				add(pb);
				listepion2.add(k);
				pb.setOpaque(false);
				pb.setVisible(true);
				pb.setBounds((int)((((k%n))*r.width+(r.width/2)*(k/(n)))+(r.getWidth()/6)), (int)((k/(n))*26*1.5+(r.getHeight()/5))+1, 30, 30);	    
			}
			if (couleur==2){
				Pion pb=new Pion();
				add(pb);
				listepion2.add(k);
				pb.setOpaque(false);
				pb.setVisible(true);
				pb.setBounds((int)((((k%n))*r.width+(r.width/2)*(k/(n)))+(r.getWidth()/6)), (int)((k/(n))*26*1.5+(r.getHeight()/5))+1, 30, 30);
			}    
		}
		
		private void init_plat(){
			setLayout(null);
			int valeur=0;
			int k;
			for (int i=0; i<n; i++){
				for (int l=0; l<n; l++){
				valeur=InterfaceAvecC.get_case(i,l);
					if (valeur==1){
						k=i*n+l;
						afficher_pion(k,valeur);
					}
					if (valeur==2){
						k=i*n+l;
						afficher_pion(k,valeur);
					}
				}
			}
		    j=InterfaceAvecC.get_va_jouer();
		}
		
		private void test_ia(){
        if(IAjoue==3){
  			int num;
        	this.addMouseListener(new MouseAdapter(){
				public void mouseClicked(MouseEvent arg0) {
					initMenus(arg0); }});
        	while(InterfaceAvecC.a_gagne()==0){
        		num=InterfaceAvecC.jouer_ia(1);
        		afficher_pion(num,1);
        		num=InterfaceAvecC.jouer_ia(2);
        		afficher_pion(num,2);
        	}}
				
        else if (IAjoue==1 && j==1){
        	setLayout(null);
        	IA=1;
        	int num=InterfaceAvecC.jouer_ia(1);
        	afficher_pion(num,1);
        	j=2;
        	IA=0;
        }}

}
