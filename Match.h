/**
 * Fichier : Match.h -> declaration de la classe Match
 * Auteur  : Alexandre COULAIS - 2020
 */

#ifndef DEF_MATCH
#define DEF_MATCH

#include <regex>

#include "Equipe.h"
#include "Joueur.h"

class Match {
    int scoreA, scoreB;
    std::string teamA, teamB;
    std::vector<Equipe>::iterator teamAIt, teamBIt;
    std::vector<Equipe> *teamsList = nullptr;

    public:
        /**
         * Constructeur Match
         * @param teams liste globale des equipes existantes
         */
        Match(std::vector<Equipe> &teams);
        Match(const Match &) = delete;

        // Operateurs
        Match &operator=(const Match &) = delete;

        /**
         * Operateur << surcharge pour permettre le traitement
         * d'une chaine de caractere par une simple operation
         * @param lineToProcess donnees a traiter
         */
        void operator<<(std::string &lineToProcess);

    private:
        // Traitement des donnees
    
        /**
         * Traitement des equipes
         * Utilisation des donnees temporaires d'un match pour
         * mettre a jour les donnees reelles du programme
         */
        void _teamsProcessing();

        /**
         * Traitement des joueurs
         * Utilisation des donnees temporaires d'un match pour
         * mettre a jour les donnees reelles du programme associees aux equipes
         * La fonction necessite en parametre la chaine de caractere correspondant
         * au match en cours de traitement
         * @param argsList joueurs a traiter
         */
        void _playersProcessing(std::string &argsList);
};

#endif