// Partida.cpp (Roland Teodorowitsch; 17 maio 2023)

#include <iostream>
#include <sstream>
#include "Partida.hpp"

//------------------------------------------------------

//construtor
Partida::Partida(Data &d, string e, Pais *s1, Pais *s2, int m) {
  dia = new Data(d);
  estadio = e;
  selecao1 = s1;
  selecao2 = s2;
  minutos = m;
}

//destrutor
Partida::~Partida() {
  delete dia;
  for (int i = 0; i < eventos.size(); i++) {
    delete eventos[i];
  }
  eventos.clear();
}

//getter e setter
Data *Partida::obtemDia() const
{
  return dia;
}
string Partida::obtemEstadio() const {
  return estadio;
}
Pais *Partida::obtemSelecao1() const {
  return selecao1;
}
Pais *Partida::obtemSelecao2() const {
  return selecao2;
}
int Partida::obtemMinutos() const {
  return minutos;
}
void Partida::defineDia(Data &d) { *dia = d; }
void Partida::defineEstadio(string e) { estadio = e; }
void Partida::defineSelecao1(Pais *s1) { selecao1 = s1; }
void Partida::defineSelecao2(Pais *s2) { selecao1 = s2; }
void Partida::defineMinutos(int m) { minutos = m; }

//adiciona evento
void Partida::adicionaEvento(int m, Jogador *j, evento_t e) {
  Evento *temp = new Evento(m, j, e); //cria um novo evento temporário chamado temp com os parametros recebidos
  eventos.push_back(temp); //insere temp no final da lista de eventos
}

//recebe o evento na posicao i
Evento *Partida::obtemEvento(int i) const {
  if ((i >= 0) && (i < eventos.size())) { //se o indice for valido
    return eventos[i]; //retorna o evento na posicao i
  } else
    return nullptr; //retorna nulo se indice for invalido
}

//retorna o tamanho da lista de eventos
int Partida::obtemNumEventos() const {
  return eventos.size(); 
}

//------------------------------------------------------

string Partida::str() const {
  stringstream ss;
  ss << *dia << ", " << estadio << ": ";
  ss << selecao1->obtemNome() << " [" << selecao1->obtemSigla() << "] X ";
  ss << "[" << selecao2->obtemSigla() << "] " << selecao2->obtemNome();
  ss << " (" << minutos << " minutos de jogo)" << endl;
  for (int i=0; i<eventos.size(); ++i)
      ss << *eventos[i] << endl;
  return ss.str();
}
