// Evento.cpp (Roland Teodorowitsch; 22 maio 2023)

#include <iostream>
#include <sstream>
#include "Evento.hpp"
#include "Pais.hpp"

//-----------------------------------------------------

//construtor
Evento::Evento(int m, Jogador *j, evento_t e) {
     minuto = m;
     jogador = j;
     evento = e;
}

//destrutor
Evento::~Evento() {}

//getter e setter
int Evento::obtemMinuto() const {
     return minuto;
}
Jogador *Evento::obtemJogador() const {
     return jogador;
}
evento_t Evento::obtemEvento() const {
     return evento;
}
void Evento::defineMinuto(int m) { minuto = m; }
void Evento::defineJogador(Jogador *j) { jogador = j; }
void Evento::defineEvento(evento_t e) { evento = e; }

//sobrecarga de operadores
bool Evento::operator<(const Evento &e) const {
     return minuto < e.minuto;
}
ostream &operator<<(ostream &out, const Evento &e) {
     out << e.str();
     return out;
}

//-----------------------------------------------------

string Evento::str() const {
  stringstream ss;
  Pais *p = jogador->obtemPais();
  ss << minuto << ": [" << p->obtemSigla() << "] " << jogador->obtemNumero() << " " << jogador->obtemNome();
  switch (evento) {
         case ENTRADA:
              if (minuto == 0)
                 ss << " foi escalado.";
              else
                 ss << " entrou em campo.";
              break;
         case SAIDA:
              ss << " foi substituído.";
              break;
         case GOL:
              ss << " fez gol.";
              break;
         case AMARELO:
              ss << " recebeu cartão amarelo.";
              break;
         case VERMELHO:
              ss << " recebeu cartão vermelho.";
              break;
         default:
              ss << "EVENTO INVÁLIDO...";
  }
  return ss.str();
}

evento_t string2evento_t(string s) {
    if (s == "E") return ENTRADA;
    else if (s == "S") return SAIDA;
    else if (s == "G") return GOL;
    else if (s == "A") return AMARELO;
    else if (s == "V") return VERMELHO;
    else {
        cerr << "string \"" << s << "\" para evento_t INVÁLIDA!" << endl;
        exit(1);
    }
}

string evento_t2string(evento_t e) {
    switch(e) {
          case ENTRADA: return "E";
          case SAIDA: return "S";
          case GOL: return "G";
          case AMARELO: return "A";
          case VERMELHO: return "V";
    }
    return "?";
}


