/**
 * Fichier : foot.h -> fichier d'entete du programme principal
 * Auteur  : Alexandre COULAIS - 2020
 */

#include <climits>
#include <cstring>
#include <dirent.h>
#include <fstream>
#include <unistd.h>

#include "Match.h"

#define USAGE() { \
            printf("Usage : %s -d <repertoire> [-j <buts|buts/match>] [-e <points|victoires|defaites|nuls|attaque|defense|goalaverage>] [-n <nombre_positif>]\n", argv[0]); \
            exit(EXIT_FAILURE); \
        }

typedef bool(*sortTeamsF_t)(Equipe &, Equipe &);
typedef bool(*cmpTeamsF_t)(Equipe &, Equipe &);
typedef bool(*sortPlayersF_t)(const Joueur *, const Joueur *);
typedef bool(*cmpPlayersF_t)(const Joueur *, const Joueur *);

/**
 * Lister les fichiers dans un repertoire et les inserer dans un vecteur
 * @param path          chemin du repertoire a parcourir
 * @param filesList     vecteur de chemins de fichier a remplir
 * @param filePattern   regex pour le format du nom des fichiers
 */
void fileFinder(const std::string &path, std::vector<std::string> &filesList, const std::regex &filePattern);

/**
 * Traitement de chaque ligne d'un fichier
 * @param file          flux vers le fichier a lire
 * @param linePattern   regex pour le format des lignes a traiter
 * @param teamsList     liste globale des equipes
 * @param filePath      nom du fichier en cours de traitement
 */
void fileProcessing(std::ifstream &file, const std::regex &linePattern, std::vector<Equipe> &teamsList, const std::string &filePath);

/**
 * Fonctions pour le classement du vecteur des equipes
 * @param firstTeam     premiere equipe a comparer
 * @param secondTeam    seconde equipe a comparer
 * @return              resultat de la comparaison sous forme de booleen
 */
bool pointSort(Equipe &firstTeam, Equipe &secondTeam);
bool victorySort(Equipe &firstTeam, Equipe &secondTeam);
bool defeatSort(Equipe &firstTeam, Equipe &secondTeam);
bool drawSort(Equipe &firstTeam, Equipe &secondTeam);
bool attackSort(Equipe &firstTeam, Equipe &secondTeam);
bool defenseSort(Equipe &firstTeam, Equipe &secondTeam);
bool goalAveSort(Equipe &firstTeam, Equipe &secondTeam);

/**
 * Fonctions pour comparer les equipes a l'affichage
 * @param firstTeam     premiere equipe a comparer
 * @param secondTeam    seconde equipe a comparer
 * @return              resultat de la comparaison sous forme de booleen
 */
bool pointCmp(Equipe &firstTeam, Equipe &secondTeam);
bool victoryCmp(Equipe &firstTeam, Equipe &secondTeam);
bool defeatCmp(Equipe &firstTeam, Equipe &secondTeam);
bool drawCmp(Equipe &firstTeam, Equipe &secondTeam);
bool attackCmp(Equipe &firstTeam, Equipe &secondTeam);
bool defenseCmp(Equipe &firstTeam, Equipe &secondTeam);
bool goalAveCmp(Equipe &firstTeam, Equipe &secondTeam);

/**
 * Fonctions pour le classement du vecteur des joueurs
 * @param firstPlayer   premier joueur a comparer
 * @param secondPlayer  second joueur a comparer
 * @return              resultat de la comparaison sous forme de booleen
 */
bool goalSort(const Joueur *firstPlayer, const Joueur *secondPlayer);
bool goalByMatchSort(const Joueur *firstPlayer, const Joueur *secondPlayer);

/**
 * Fonctions pour comparer les joueurs a l'affichage
 * @param firstPlayer   premier joueur a comparer
 * @param secondPlayer  second joueur a comparer
 * @return              resultat de la comparaison sous forme de booleen
 */
bool goalCmp(const Joueur *firstPlayer, const Joueur *secondPlayer);
bool goalByMatchCmp(const Joueur *firstPlayer, const Joueur *secondPlayer);

/**
 * Fonction pour definir les fonctions de classement et de comparaison
 * a l'affichage des joueurs et des equipes
 * @param rankingTeams      critere de classement des equipes
 * @param sortTeamsFunc     pointeur sur fonction de classement des equipes
 * @param cmpTeamsFunc      pointeur sur fonction de comparaison des equipes
 * @param rankingPlayers    critere de classement des joueurs
 * @param sortPlayersFunc   pointeur sur fonction de classement des joueurs
 * @param cmpPlayersFunc    pointeur sur fonction de comparaison de joueurs
 */
void defineRankingF(
    const std::string &rankingTeams,
    sortTeamsF_t &sortTeamsFunc,
    cmpTeamsF_t &cmpTeamsFunc,
    const std::string &rankingPlayers,
    sortPlayersF_t &sortPlayersFunc,
    cmpPlayersF_t &cmpPlayersFunc
);