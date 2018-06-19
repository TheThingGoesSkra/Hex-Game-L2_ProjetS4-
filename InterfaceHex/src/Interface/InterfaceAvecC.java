package Interface;

public class InterfaceAvecC {
	static {
		//System.loadLibrary("HexLib");
		System.load("D:/Matthieu/##Etude/#Licence_2eme_annee/S4/Projet_S4/InterfaceHex/src/Interface/HexLib.dll");
	}
	public static native void init_plateau(int n);
	public static native int get_case(int coordx, int coordy);
	public static native void jouer_coup(int coordx, int coordy,int valeur); //correspond a set_case
	public static native int get_plat_taille();
	public static native int get_va_jouer();
	public static native int a_gagne();
	public static native void init_ia(int joueur, int diff);
	public static native int get_plat_IA();
	public static native int jouer_ia(int joueur);
	public static native int sauvegarde(String nom);
	public static native int chargement(String nom);
	public static native void free_all();

	public static void main(String args []){
		InterfaceAvecC.init_plateau(4);
		InterfaceAvecC.init_ia(0,0);
		InterfaceAvecC.jouer_coup(0,0,2);
		InterfaceAvecC.jouer_coup(0,1,2);
		InterfaceAvecC.jouer_coup(0,2,2);
		InterfaceAvecC.jouer_coup(0,3,2);
		System.out.println(InterfaceAvecC.get_case(0,3));
		System.out.println(InterfaceAvecC.a_gagne());
	}
}
