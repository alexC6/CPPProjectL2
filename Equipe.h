/**
 * Fichier : Equipe.h -> declaration de la classe Equipe
 * Auteur  : Alexandre COULAIS - 2020
 */

#ifndef DEF_EQUIPE
#define DEF_EQUIPE

#include <algorithm>
#include <vector>

#include "Joueur.h"

class Equipe {
    int defeat;
    int draw;
    int goalDefeat;
    int goalWin;
    std::string name;
    int victory;
    std::vector<Joueur> playersList;

    // Methodes publiques
    public:
        /**
         * Constructeur Equipe
         * @param teamName      nom de la nouvelle equipe
         * @param scoreWin      premier score gagnant de l'equipe
         * @param scoreDefeat   premier score perdant de l'equipe
         */
        Equipe(const std::string &teamName, int scoreWin, int scoreDefeat);

        // Operateurs
        /**
         * Permettre la comparaison entre une equipe et une chaine de caractere
         * @param otherName nom de l'equipe a comparer
         * @return          vrai ou faux
         */
        bool operator==(const std::string &otherName) const;
        friend std::ostream &operator<<(std::ostream &flow, const Equipe &team);

        // Accesseurs
        int getDefeat() const;
        int getDraw() const;
        int getGoalAve() const;
        int getGoalDefeat() const;
        int getGoalWin() const;
        int getMatchNbr() const;
        std::string getName() const;

        /**
         * Insere dans un vecteur passe en parametre un pointeur sur chacun de ses joueurs
         * @param globalPlayersList listes globale des joueurs
         */
        void getPlayers(std::vector<const Joueur *> &globalPlayersList) const;
        int getPoints() const;
        int getVictory() const;

        // Mutateurs
        /**
         * Ajouter les scores obtenus lors d'un match a l'equipe
         * @param scoreWin      score gagnant a ajouter
         * @param scoreDefeat   score perdant a ajouter
         */
        void setGoal(int scoreWin, int scoreDefeat);

        /**
         * Ajoute a l'equipe ou modifie le joueur dont le nom est passe en parametre
         * @param setPlayer nom du joueur a traiter
         */
        void setPlayer(const std::string &playerName);

    // Methodes privees
    private:
        /**
         * Ajoute une victoire, une defaite ou un match nul en fonction des scores passes en parametre
         * @param scoreWin      score gagnant lors du match
         * @param scoreDefeat   score perdant lors du match
         */
        void _setDefeatVictory(int scoreWin, int scoreDefeat);
};

#endif