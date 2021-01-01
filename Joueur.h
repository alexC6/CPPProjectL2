/**
 * Fichier : Joueur.h -> declaration de la classe Joueur
 * Auteur  : Alexandre COULAIS - 2020
 */

#ifndef DEF_JOUEUR
#define DEF_JOUEUR

#include <iomanip>
#include <iostream>

class Joueur {
    int goalNbr;
    float matchNbr;
    std::string name;
    std::string team;

    public:
        /**
         * Constructeur Joueur
         * @param playerName    nom du nouveau joueur
         * @param curTeam       nom de l'equipe appelant la creation d'un joueur
         */
        Joueur(const std::string &playerName, const std::string &curTeam);

        // Operateurs
        /**
         * Permettre la comparaison entre un joueur et une chaine de caracteres
         * @param other nom du joueur a comparer
         * @return      vrai ou faux
         */
        bool operator==(const std::string &other) const;
        friend std::ostream &operator<<(std::ostream &flow, const Joueur &player);

        // Accesseurs
        int getGoal() const;
        float getGoalByMatch() const;
        std::string getName() const;
        std::string getTeam() const;

        // Mutateurs
        void addGoal();

        /**
         * Modifie le nombre de match en fonction de la somme calculee par l'equipe
         * @param matchCounter somme des victoires, defaites et matchs nuls de l'equipe
         */
        void setMatch(float matchCounter);
};

#endif