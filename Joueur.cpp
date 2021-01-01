/**
 * Fichier : Joueur.cpp -> code source de la classe Joueur
 * Auteur  : Alexandre COULAIS - 2020
 */

#include "Joueur.h"
//#include "Equipe.h"

Joueur::Joueur(const std::string &playerName, const std::string &curTeam) {
    this->goalNbr = 1;
    this->name = playerName;
    this->team = curTeam;
}

bool Joueur::operator==(const std::string &other) const {
    return this->name == other;
}

int Joueur::getGoal() const {
    return this->goalNbr;
}

float Joueur::getGoalByMatch() const {
    return static_cast<float>(this->goalNbr) / this->matchNbr;
}

std::string Joueur::getName() const {
    return this->name;
}

std::string Joueur::getTeam() const {
    return this->team;
}

std::ostream &operator<<(std::ostream &flow, const Joueur &player) {
    flow << std::left << std::setw(20) << player.name << " | ";
    flow << std::left << std::setw(20) << player.team << " | ";
    flow << std::left << std::setw(4) << player.goalNbr << " | ";
    flow << std::left << std::setw(10) << std::setprecision(3) << player.getGoalByMatch() << " |" << std::endl;

    return flow;
}

void Joueur::addGoal() {
    this->goalNbr++;
}

void Joueur::setMatch(float matchCounter) {
    this->matchNbr = matchCounter;
}