/**
 * Fichier : Equipe.cpp -> code source de la classe Equipe
 * Auteur  : Alexandre COULAIS - 2020
 */

#include "Equipe.h"

Equipe::Equipe(const std::string &teamName, int scoreWin, int scoreDefeat) {
    this->defeat = 0;
    this->draw = 0;
    this->goalDefeat = scoreDefeat;
    this->goalWin = scoreWin;
    this->name = teamName;
    this->victory = 0;

    _setDefeatVictory(scoreDefeat, scoreWin);
}

bool Equipe::operator==(const std::string &otherName) const {
    return this->name == otherName;
}

std::ostream &operator<<(std::ostream &flow, const Equipe &team) {
    flow << std::left << std::setw(20) << team.name << " | ";
    flow << std::left << std::setw(6) << team.getPoints() << " | ";
    flow << std::left << std::setw(9) << team.victory << " | ";
    flow << std::left << std::setw(8) << team.defeat << " | ";
    flow << std::left << std::setw(4) << team.draw << " | ";
    flow << std::left << std::setw(8) << team.goalWin << " | ";
    flow << std::left << std::setw(8) << team.goalDefeat << " | ";
    flow << std::left << std::setw(7) << team.getGoalAve() << " |" << std::endl;

    return flow;
}

int Equipe::getDefeat() const {
    return this->defeat;
}

int Equipe::getDraw() const {
    return this->draw;
}

int Equipe::getGoalAve() const {
    return this->goalWin - this->getGoalDefeat();
}

int Equipe::getGoalDefeat() const {
    return this->goalDefeat;
}

int Equipe::getGoalWin() const {
    return this->goalWin;
}

int Equipe::getMatchNbr() const {
    return this->defeat + this->draw + this->victory;
}

std::string Equipe::getName() const {
    return this->name;
}

void Equipe::getPlayers(std::vector<const Joueur *> &globalPlayersList) const {
    unsigned int i;

    for (i = 0; i < playersList.size(); i++) {
        globalPlayersList.push_back(&playersList[i]);
    }
}

int Equipe::getPoints() const {
    return this->draw + this->victory * 3;
}

int Equipe::getVictory() const {
    return this->victory;
}

void Equipe::setGoal(int scoreWin, int scoreDefeat) {
    this->goalDefeat += scoreDefeat;
    this->goalWin += scoreWin;

    _setDefeatVictory(scoreWin, scoreDefeat);
}

void Equipe::setPlayer(const std::string &playerName) {
    unsigned int i;
    std::vector<Joueur>::iterator playersListIt;

    playersListIt = std::find(this->playersList.begin(), this->playersList.end(), playerName);

    if (playersListIt != this->playersList.end()) {
        playersListIt->addGoal();
    } else {
        this->playersList.push_back(Joueur(playerName, this->name));
    }

    for (i = 0; i < this->playersList.size(); i++) {
        this->playersList[i].setMatch(this->getMatchNbr());
    }
}

void Equipe::_setDefeatVictory(int scoreWin, int scoreDefeat) {
    if (scoreDefeat > scoreWin) {
        this->defeat++;
    } else if (scoreDefeat < scoreWin) {
        this->victory++;
    } else {
        this->draw++;
    }
}