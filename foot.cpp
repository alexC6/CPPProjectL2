/**
 * Fichier : foot.cpp -> code source des fonctions du programme principal
 * Auteur  : Alexandre COULAIS - 2020
 */

#include "foot.h"

void fileFinder(const std::string &path, std::vector<std::string> &filesList, const std::regex &filePattern) {
    DIR *directory = opendir(path.c_str());
    dirent *direntStruct;
    std::string fileName;

    if (directory != NULL) {
        while ((direntStruct = readdir(directory))) {
            fileName = direntStruct->d_name;
            if (std::regex_match(fileName, filePattern)) {
                filesList.push_back(path + "/" + fileName);
            }
        }
    } else {
        std::cerr << "Erreur lors de la lecture du repertoire " << path << std::endl;

        exit(EXIT_FAILURE);
    }

    closedir(directory);
}

void fileProcessing(std::ifstream &file, const std::regex &linePattern, std::vector<Equipe> &teamsList, const std::string &filePath) {
    Match buffer(teamsList);
    std::string line;
            
    while (std::getline(file, line)) {
        if (std::regex_match(line, linePattern)) {
            buffer << line;
        } else {
            std::cerr << "Erreur de format de ligne detecte" << std::endl;
            std::cerr << "\tLigne : " << line << std::endl;
            std::cerr << "\tFichier : " << filePath << std::endl;
        }
    }

    file.close();
}

bool pointSort(Equipe &firstTeam, Equipe &secondTeam) {
    return firstTeam.getPoints() > secondTeam.getPoints();
}

bool victorySort(Equipe &firstTeam, Equipe &secondTeam) {
    return firstTeam.getVictory() > secondTeam.getVictory();
}

bool defeatSort(Equipe &firstTeam, Equipe &secondTeam) {
    return firstTeam.getDefeat() < secondTeam.getDefeat();
}

bool drawSort(Equipe &firstTeam, Equipe &secondTeam) {
    return firstTeam.getDraw() < secondTeam.getDraw();
}

bool attackSort(Equipe &firstTeam, Equipe &secondTeam) {
    return firstTeam.getGoalWin() > secondTeam.getGoalWin();
}

bool defenseSort(Equipe &firstTeam, Equipe &secondTeam) {
    return firstTeam.getGoalDefeat() < secondTeam.getGoalDefeat();
}

bool goalAveSort(Equipe &firstTeam, Equipe &secondTeam) {
    return firstTeam.getGoalAve() > secondTeam.getGoalAve();
}

bool pointCmp(Equipe &firstTeam, Equipe &secondTeam) {
    return firstTeam.getPoints() == secondTeam.getPoints();
}

bool victoryCmp(Equipe &firstTeam, Equipe &secondTeam) {
    return firstTeam.getVictory() == secondTeam.getVictory();
}

bool defeatCmp(Equipe &firstTeam, Equipe &secondTeam) {
    return firstTeam.getDefeat() == secondTeam.getDefeat();
}

bool drawCmp(Equipe &firstTeam, Equipe &secondTeam) {
    return firstTeam.getDraw() == secondTeam.getDraw();
}

bool attackCmp(Equipe &firstTeam, Equipe &secondTeam) {
    return firstTeam.getGoalWin() == secondTeam.getGoalWin();
}

bool defenseCmp(Equipe &firstTeam, Equipe &secondTeam) {
    return firstTeam.getGoalDefeat() == secondTeam.getGoalDefeat();
}

bool goalAveCmp(Equipe &firstTeam, Equipe &secondTeam) {
    return firstTeam.getGoalAve() == secondTeam.getGoalAve();
}

bool goalSort(const Joueur *firstPlayer, const Joueur *secondPlayer) {
    return firstPlayer->getGoal() > secondPlayer->getGoal();
}

bool goalByMatchSort(const Joueur *firstPlayer, const Joueur *secondPlayer) {
    return firstPlayer->getGoalByMatch() > secondPlayer->getGoalByMatch();
}

bool goalCmp(const Joueur *firstPlayer, const Joueur *secondPlayer) {
    return firstPlayer->getGoal() == secondPlayer->getGoal();
}

bool goalByMatchCmp(const Joueur *firstPlayer, const Joueur *secondPlayer) {
    return firstPlayer->getGoalByMatch() == secondPlayer->getGoalByMatch();
}

void defineRankingF(
    const std::string &rankingTeams,
    sortTeamsF_t &sortTeamsFunc,
    cmpTeamsF_t &cmpTeamsFunc,
    const std::string &rankingPlayers,
    sortPlayersF_t &sortPlayersFunc,
    cmpPlayersF_t &cmpPlayersFunc
) {
    if (rankingTeams == "points") {
        sortTeamsFunc = &pointSort;
        cmpTeamsFunc = &pointCmp;
    } else if (rankingTeams == "victoires") {
        sortTeamsFunc = &victorySort;
        cmpTeamsFunc = &victoryCmp;
    } else if (rankingTeams == "defaites") {
        sortTeamsFunc = &defeatSort;
        cmpTeamsFunc = &defeatCmp;
    } else if (rankingTeams == "nuls") {
        sortTeamsFunc = &drawSort;
        cmpTeamsFunc = &drawCmp;
    } else if (rankingTeams == "attaque") {
        sortTeamsFunc = &attackSort;
        cmpTeamsFunc = &attackCmp;
    } else if (rankingTeams == "defense") {
        sortTeamsFunc = &defenseSort;
        cmpTeamsFunc = &defenseCmp;
    } else {
        sortTeamsFunc = &goalAveSort;
        cmpTeamsFunc = &goalAveCmp;
    }

    if (rankingPlayers == "buts") {
        sortPlayersFunc = &goalSort;
        cmpPlayersFunc = &goalCmp;
    } else {
        sortPlayersFunc = &goalByMatchSort;
        cmpPlayersFunc = &goalByMatchCmp;
    }
}