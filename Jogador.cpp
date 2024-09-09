// Jogador.cpp (Roland Teodorowitsch; 17 maio 2023)

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include "Jogador.hpp"

//--------------------------------------------------

//construtor
Jogador::Jogador(Pais *p, int num, posicao_t pos, string n, Data &d) : Pessoa(n, d, p) {
    numero = num;
    posicao = pos;
}

//destrutor
Jogador::~Jogador() {}

//getter e setter
int Jogador::obtemNumero() const {
    return numero;
}

posicao_t Jogador::obtemPosicao() const {
    return posicao;
}

void Jogador::defineNumero(int n) {
    numero = n;
}

void Jogador::definePosicao(posicao_t pos) {
    posicao = pos;
}

//str que imprime as informações do jogador
string Jogador::str() const {
    stringstream ss;
    ss << "[" << pais->obtemSigla() << "|" << obtemNumero() << "|" << posicao_t2string(posicao) << "]"
       << " " << nome << ","
       << " " << nascimento->str();
    return ss.str();
}

//--------------------------------------------------

posicao_t string2posicao_t(string s) {
    if (s == "GK") return GK;
    else if (s == "DF") return DF;
    else if (s == "MF") return MF;
    else if (s == "FW") return FW;
    else {
        cerr << "string \"" << s << "\" para posicao_t INVÁLIDA!" << endl;
        exit(1);
    }
}

string posicao_t2string(posicao_t p) {
    switch(p) {
          case GK: return "GK";
          case DF: return "DF";
          case MF: return "MF";
          case FW: return "FW";
    }
    return "??";
}

