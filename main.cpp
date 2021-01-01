/**
 * Fichier : main.cpp -> fichier principal du programme
 * Auteur  : Alexandre COULAIS - 2020
 */

#include "foot.h"

int main(int argc, char *argv[]) {
    // Verifiation du nombre minimal d'arguments
    if (argc < 3) {
        USAGE()
    }

    // Variables et constantes essentielles a la recuperation des arguments
    int opt;
    unsigned int n = 10, i;
    const char *optstring = "d:j:e:n:";
    std::string repertory, rankingPlayers = "", rankingTeams = "";
    const std::vector<std::string> eOptions = {"points", "victoires", "defaites", "nuls", "attaque", "defense", "goalaverage"};
    std::vector<std::string>::const_iterator startIt = eOptions.begin(), endIt = eOptions.end();

    // Recuperation des arguments de la ligne de commande
    while ((opt = getopt(argc, argv, optstring)) != -1) {
        switch (opt) {
            case 'd':
                repertory = optarg;
                break;
            case 'j':
                if (strcmp(optarg, "buts") == 0 || strcmp(optarg, "buts/match") == 0) {
                    rankingPlayers = optarg;
                } else {
                    USAGE()
                }
                break;
            case 'e':
                if (std::find(startIt, endIt, optarg) != endIt) {
                    rankingTeams = optarg;
                } else {  
                    USAGE()
                }
                break;
            case 'n':
                try {
                    n = std::stoi(optarg, nullptr, 10);

                    if (n == 0 || n > INT_MAX) {
                        USAGE()
                    }
                } catch (const std::invalid_argument &e) {
                    std::cerr << "Correction plantage : " << e.what() << std::endl;
                    std::cerr << "Remplace par n = 10 (par defaut)" << std::endl;
                }
                break;
            default:
                USAGE()
        }
    }

    // Variables necessaires a la recherche des fichiers
    std::vector<std::string> filesList;
    const std::regex filePattern("(J[0-9]+\\.{1}txt)");

    if (std::regex_search(repertory, filePattern)) {
        // Ajout du chemin saisi dans le vecteur des chemins
        filesList.push_back(repertory);
    } else {
        /**
         * Parcours des fichiers dans le repertoire et insertion des chemins dans un repertoire
         * et tri lexicographique de ces chemins
         */ 
        fileFinder(repertory, filesList, filePattern);
        std::sort(filesList.begin(), filesList.end());
    }

    // Variables necessaires a la lecture des fichiers et a la recuperation des informations
    std::vector<Equipe> teamsList;
    const std::regex linePattern("^ *[a-zA-Z-]+ *: *[a-zA-Z-]+ *[0-9]+ *- *[0-9]+ *(([a-zA-Z-]+ *\\. *[a-zA-Z-']+ *[0-9]+ *\\/?) *)*:? *(([a-zA-Z-]+ *\\. *[a-zA-Z-']+ *[0-9]+ *\\/?) *)*$");

    /**
     * Pour chaque chemin du vecteur filesList, recuperation ligne par ligne, si l'ouverture du fichier est reussie
     * de l'ensemble des informations par une regex qui verifie en premier la validite du format de la ligne
     * Si la ligne est valide, elle est envoyee au Match buffer qui s'occupe de traiter les informations de la ligne
     * Sinon, un message est affiche sur le flux d'erreur standard
     * Si le fichier n'a pas pu etre ouvert, un message est affiche sur le flux d'erreur standard et on envoie un signal d'abandon
     */
    for (std::string filePath : filesList) {
        std::ifstream file(filePath);

        if (file) {
            fileProcessing(file, linePattern, teamsList, filePath);
        } else {
            std::cerr << "Erreur a l'ouverture du fichier " << filePath << std::endl;

            exit(EXIT_FAILURE);
        }
    }

    /**
     * Declaration et definition des fonctions utilisees pour le classement des joueurs et des equipes
     * ainsi que pour la comparaison des joueurs et equipes a l'affichage
     */
    sortPlayersF_t sortPlayersFunc;
    cmpPlayersF_t cmpPlayersFunc;
    sortTeamsF_t sortTeamsFunc;
    cmpTeamsF_t cmpTeamsFunc;

    defineRankingF(rankingTeams, sortTeamsFunc, cmpTeamsFunc, rankingPlayers, sortPlayersFunc, cmpPlayersFunc);

    /**
     * Si l'ensemble des informations ont pu etre recuperees correctement on procede a l'affichage
     * Si rankingTeams n'est pas vide, on tri les informations selon le critere saisi au lancement du programme
     * Sinon on passe a la suite
     */
    if (rankingTeams != "") {
        std::sort(teamsList.begin(), teamsList.end(), sortTeamsFunc);

        std::cout << std::left << std::setw(20) << "Equipes" << " | ";
        std::cout << std::left << "Points" << " | ";
        std::cout << std::left << "Victoires" << " | ";
        std::cout << std::left << "Defaites" << " | ";
        std::cout << std::left << "Nuls" << " | ";
        std::cout << std::left << "Attaque" << " | ";
        std::cout << std::left << "Defense" << " | ";
        std::cout << std::left << "Average" << " |" << std::endl << std::endl;

        for (i = 0; i < n && i < teamsList.size(); i++) {
            std::cout << teamsList[i];
        }

        /**
         * On continue d'afficher les equipes tant que la suivante possede un critere
         * de classement egale a la derniere affichee (meme systeme plus bas pour les joueurs)
         */
        while (i < teamsList.size() && cmpTeamsFunc(teamsList[i-1], teamsList[i])) {
            std::cout << teamsList[i];
            i++;
        }
    }

    /**
     * Si rankingPlayers n'est pas vide
     * On recupere tous les joueurs dans un vecteur de pointeurs sur joueur pour faciliter le tri
     * Puis on tri les informations selon le critere saisi au lancement du programme
     * On fera attention a bien eliminer les joueurs CSC de chaque equipe
     */
    if (rankingPlayers != "") {
        std::vector<const Joueur *> playersList;
        std::regex CSCPattern("(CSC\\.[a-zA-Z-]+)");

        for (i = 0; i < teamsList.size(); i++) {
            teamsList[i].getPlayers(playersList);
        }

        std::sort(playersList.begin(), playersList.end(), sortPlayersFunc);

        std::cout << std::endl << std::left << std::setw(20) << "Joueurs" << " | ";
        std::cout << std::left << std::setw(20) << "Equipes" << " | ";
        std::cout << std::left << "Buts" << " | ";
        std::cout << std::left << "Buts/match" << " |" << std::endl << std::endl;

        for (i = 0; i < n && i < playersList.size(); i++) {
            if (!(std::regex_match(playersList[i]->getName(), CSCPattern))) {
                std::cout << *playersList[i];
            }
        }

        while (i < playersList.size() && cmpPlayersFunc(playersList[i-1], playersList[i])) {
            std::cout << *playersList[i];
            i++;
        }
    }

    return 0;
}