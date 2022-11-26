#ifndef JEU_H
#define JEU_H


class Jeu
{
    //Singleton
    static Jeu* jeu;
    Jeu();
    ~Jeu();
    Jeu(const Jeu&)=delete;
    Jeu& operator=(const Jeu&)=delete;
    //Attribus
    list<Joueur> joueurs;
    int joueursActif;
    list<Carte> cartesEnJeu;
    Marche marche;
    //Méthode pour l'initialisation du jeu
    void initialiserCartes();
    void initialiserJoueurs();
    //Méthode pour un tour de jeu
    int lancerDes() const;
    void activerCartesBleues(int nbDes) const; //Voir si il faut un const
    void activerCartesVertes(int nbDes) const;
    void activerCartesRouges(int nbDes) const;
    void activerCartesViolettes(int nbDes) const;
    void achat();
    bool vérifierVictoire();
public:
    static Jeu& getJeu();
    static void libererJeu();

    void genererPartie();
    void boucledeJeu();
    void joueurSuivant();

};

#endif // JEU_H
