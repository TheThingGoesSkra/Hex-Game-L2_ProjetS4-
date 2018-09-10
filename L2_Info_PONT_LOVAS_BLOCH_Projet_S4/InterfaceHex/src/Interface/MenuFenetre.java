package Interface;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JOptionPane;

public class MenuFenetre extends java.awt.MenuBar {


public MenuItem menuQuitter, menuCharger, menuPrincipal, menuNouveau, menuApropos, menuRegles, menuSauvegarder;

public MenuFenetre() {
Menu menuOptions = new Menu(" Options ");
menuNouveau = new MenuItem(" Nouveau ");
menuCharger = new MenuItem(" Charger ");
menuSauvegarder = new MenuItem(" Sauvegarder ");
menuPrincipal = new MenuItem(" Menu principal ");
menuQuitter = new MenuItem(" Quitter ");
menuOptions.add(menuNouveau);
menuOptions.addSeparator();
menuOptions.add(menuCharger);
menuOptions.addSeparator();
menuOptions.add(menuSauvegarder);
menuOptions.addSeparator();
menuOptions.add(menuPrincipal);
menuOptions.addSeparator();
menuOptions.add(menuQuitter);
Menu menuAide = new Menu(" Aide ");
menuApropos = new MenuItem(" A propos ");
menuRegles = new MenuItem(" Regles ");
menuRegles.addActionListener(new ActionListener(){

	public void actionPerformed(ActionEvent e) {
		JOptionPane.showMessageDialog(null, "<html><b>Nombre de joueurs : 2</html></b> 2"+"\n \nLe plateau du jeu de Hex est compose de cases hexagonales formant un losange.\n La taille du plateau peut varier (habituellement 6x6, 9x9 ou 11x11). Deux cotes opposees du \nlosange sont noirs, les deux autres sont blancs."
+"\n \n Le joueur blanc commence. Les joueurs jouent chacun leur tour. A chaque tour, \n le joueur place un pion de sa couleur sur une case libre du plateau. Le premier joueur qui \n reussit a relier ses deux bords par un chemin de pions continus de sa couleur a gagne. \n Il ne peut y avoir qu'un pion par case. Les pions poses le sont definitivement, ils ne  \n peuvent etre ni retires, ni deplaces."
,"Regles", 1);
	}
	
});
menuApropos.addActionListener(new ActionListener(){

	public void actionPerformed(ActionEvent e) {
		JOptionPane.showMessageDialog(null, "<html><b>Le jeu de HEX pour Windows.</b></html> \n<html><b>Version</b> 1.0</html> \n<html><b>Deniere mise a  jour instalable :</b> 1.0</html>"
				+ "\n\n© 2017 Universitée Paul-Sabatier. Copyleft."
				+"\n\nAvertissement : ce logiciel est protege par la Loi relative aux droits d'auteurs et aux \ndroits voisins dans la société de l'information. Un logiciel sous copyleft est un logiciel dont \nles conditions de distribution interdisent aux nouveaux distributeurs d'ajouter des restrictions \nsupplementaires lorsqu'ils redistribuent ou modifient le logiciel. "
				+"\nAuteurs : Lovas Bence, Pont Matthieu et Bloch Tom"
				,"A propos", 1);
	}
	
});
menuAide.add(menuRegles);
menuAide.add(menuApropos);

add(menuOptions);
setHelpMenu(menuAide);
}

}