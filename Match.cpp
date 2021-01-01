/**
 * Fichier : Match.cpp -> code source de la classe Match
 * Auteur  : Alexandre COULAIS - 2020
 */

#include "Match.h"

Match::Match(std::vector<Equipe> &teams) {
    teamsList = &teams;
}

void Match::operator<<(std::string &lineToProcess) {
    const std::regex teamScorePattern("(^[a-zA-Z-]+):([a-zA-Z-]+)([0-9]+)-([0-9]+)");
    std::smatch result;

    lineToProcess = std::regex_replace(lineToProcess, std::regex("\\s"), "");

    if (std::regex_search(lineToProcess, result, teamScorePattern)) {
        this->teamA = result[1];
        this->teamB = result[2];
        this->scoreA = stoi(result[3]);
        this->scoreB = stoi(result[4]);

        this->_teamsProcessing();
        this->_playersProcessing(lineToProcess);
    }
}

void Match::_teamsProcessing() {
    std::vector<Equipe>::iterator teamsListIt;

    teamsListIt = std::find(this->teamsList->begin(), this->teamsList->end(), this->teamA);

    if (teamsListIt != this->teamsList->end()) {
        teamsListIt->setGoal(this->scoreA, this->scoreB);
        teamAIt = teamsListIt;
    } else {
        this->teamsList->push_back(Equipe(this->teamA, this->scoreA, this->scoreB));
        teamAIt = std::prev(this->teamsList->end());
    }

    teamsListIt = std::find(this->teamsList->begin(), this->teamsList->end(), this->teamB);

    if (teamsListIt != this->teamsList->end()) {
        teamsListIt->setGoal(this->scoreB, this->scoreA);
        teamBIt = teamsListIt;
    } else {
        this->teamsList->push_back(Equipe(this->teamB, this->scoreB, this->scoreA));
        teamBIt = std::prev(this->teamsList->end());
    }
}

void Match::_playersProcessing(std::string &argsList) {
    int i;
    std::smatch result;
    std::sregex_iterator regexIt, sentinelIt;
    std::vector<Joueur>::iterator playersListIt;
    const std::regex playersPattern("([A-Z-]+\\.[a-zA-Z-']+)([0-9]+)");

    for (i = 1, regexIt = std::sregex_iterator(argsList.begin(), argsList.end(), playersPattern); regexIt != sentinelIt;  i++, regexIt++) {
        result = *regexIt;
        std::string playerName = result[1];

        if (i <= scoreA) {
            teamAIt->setPlayer(playerName);
        } else {
            teamBIt->setPlayer(playerName);
        }
    }
}