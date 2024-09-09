// Aplicacao.cpp (Roland Teodorowitsch; 17 maio 2023)

#include <iostream>
#include <fstream>
#include "Aplicacao.hpp"

vector<string> Aplicacao::splitCSV(string linhaCSV, char separador)
{
   vector<string> res;
   char c;
   string campo = "";
   for (int i = 0; i < linhaCSV.size(); ++i)
   {
      c = linhaCSV.at(i);
      if (c == separador)
      {
         res.push_back(campo);
         campo = "";
      }
      else
         campo.append(1, c);
   }
   res.push_back(campo);
   return res;
}

//--------------------------------------------------------

//construtor
Aplicacao::Aplicacao()
{
   partida = nullptr;
}

//destrutor
Aplicacao::~Aplicacao()
{
   delete partida;
   for (int i = 0; i < paises.size(); i++)
   {
      delete paises[i];
   }
   paises.clear();
   for (int i = 0; i < arbitros.size(); i++)
   {
      delete arbitros[i];
   }
   arbitros.clear();
   for (int i = 0; i < tecnicos.size(); i++)
   {
      delete tecnicos[i];
   }
   tecnicos.clear();
   for (int i = 0; i < jogadores.size(); i++)
   {
      delete jogadores[i];
   }
   jogadores.clear();
}

//carrega os tecnicos
bool Aplicacao::carregaTecnicos(string nomeArquivo)
{
   for (int i = 0; i < tecnicos.size(); i++)
   {
      delete tecnicos[i];
   } //esvazia o vector de tecnicos
   tecnicos.clear();
   ifstream f(nomeArquivo); //abre o arquivo
   if (!f.is_open()) //se o arquivo não abrir, retorna falso
   {
      return false;
   }
   string linha; //string que receba a linha do arquivo
   while (getline(f, linha)) //enquanto há linhas
   {
      vector<string> campos = splitCSV(linha, ';'); // vector campos usado para separar os ';' do arquivo
      if (campos.size() != 4) //se o tamanho de campos for maior que esperado, fecha o arquivo
      {
         f.close();
         return false;
      }
      Pais *selecao = obtemPais(campos[0]); //coloca o valor no campo 0 do arquivo no ponteiro seleção
      string nome = campos[1]; //coloca o valor no campo 1 em nome
      Data data(campos[2]); //coloca o valor no campo 2 em data
      Pais *pais = obtemPais(campos[3]); //coloca o valor no campo 3 em pais
      Tecnico *novotecnico = new Tecnico(selecao, nome, data, pais); //cria um novo tecnico com as variaveis anteriores
      tecnicos.push_back(novotecnico); //insere o novo tecnico no vector de tecnicos
   }
   f.close();
   return true;
}

//imprime os tecnicos
void Aplicacao::mostraTecnicos()
{
   for (int i = 0; i < tecnicos.size(); i++)
   {
      cout << tecnicos[i]->str() << endl; //imprime os tecnicos em ordem de entrada
   }
}

//ordena os tecnicos
void Aplicacao::ordenaTecnicos()
{
   for (int i = 0; i < tecnicos.size() - 1; i++) 
   {
      int menor = i; //int menor recebe o valor de i
      for (int a = i + 1; a < tecnicos.size(); a++)
      {
         if (tecnicos[a]->obtemNome() < tecnicos[menor]->obtemNome()) //se o nome com index a for menor que o menor nome
         {
            menor = a; //o novo menor vira a
         }
      }
      if (menor != i) //se o valor de menor for diferente do valor de index
      {
         Tecnico *temp = tecnicos[menor]; //troca os valores de menor com o valor de index
         tecnicos[menor] = tecnicos[i];
         tecnicos[i] = temp;
      }
   }
}

//mesma aplicação dos técnicos, mas para os jogadores
bool Aplicacao::carregaJogadores(string nomeArquivo)
{
   for (int i = 0; i < jogadores.size(); i++)
   {
      delete jogadores[i];
   }
   jogadores.clear();
   ifstream f(nomeArquivo);
   if (!f.is_open())
   {
      return false;
   }
   string linha;
   while (getline(f, linha))
   {
      vector<string> campos = splitCSV(linha, ';');
      if (campos.size() != 5)
      {
         f.close();
         return false;
      }
      Pais *pais = obtemPais(campos[0]);
      string numero = campos[1];
      string posicao = campos[2];
      string nome = campos[3];
      Data data(campos[4]);
      Jogador *novojogador = new Jogador(pais, stoi(numero), string2posicao_t(posicao), nome, data);
      jogadores.push_back(novojogador);
   }
   f.close();
   return true;
}

void Aplicacao::mostraJogadores()
{
   for (int i = 0; i < jogadores.size(); i++)
   {
      cout << jogadores[i]->str() << endl;
   }
}

void Aplicacao::ordenaJogadores()
{
   for (int i = 0; i < jogadores.size() - 1; i++)
   {
      int menor = i;
      for (int a = i + 1; a < jogadores.size(); a++)
      {
         if (jogadores[a]->obtemNome() < jogadores[menor]->obtemNome())
         {
            menor = a;
         }
      }
      if (menor != i)
      {
         Jogador *temp = jogadores[menor];
         jogadores[menor] = jogadores[i];
         jogadores[i] = temp;
      }
   }
}

//recebe um jogador pelo index e sigla passado por parametro
Jogador *Aplicacao::obtemJogador(string sigla, int numero)
{
   for (int i = 0; i < jogadores.size(); i++) //percorre o vector
   {
      if (jogadores[i]->obtemPais()->obtemSigla() == sigla && jogadores[i]->obtemNumero() == numero) //se a sigla e o numero passados for igual a sigla e o numero do jogador [i]
         return jogadores[i]; //retorna o jogador
   }
   return nullptr; //se não encontrou, retorna nullptr
}

void Aplicacao::mostraPartida()
{
   cout << partida->str(); //imprime a partida
}

void Aplicacao::mostraRelatorio()
{
   vector<Jogador *> jogador; // vector que armazena os jogadores
   vector<int> minuto_e;      // vector que armazena o minuto de entrada dos jogadores
   vector<int> minuto_s;      // vector que armazena o minuto de saida dos jogadores
   for (int i = 0; i < partida->obtemNumEventos(); i++) 
   { //enquanto o loop não acaba
      if (partida->obtemEvento(i)->obtemEvento() != ENTRADA)
      {
         continue; //se o evento não for um evento de entrada (o jogador ja foi visto), continua o loop
      }
      else
      {
         Jogador *temp = partida->obtemEvento(i)->obtemJogador(); //jogador temp recebe o jogador do evento i
         int entrada = 0, saida = partida->obtemMinutos(); //valores iniciais de entrada e saida, que armazenam os minutos de quando os jogadores entraram e sairam 
         for (int a = 0; a < partida->obtemNumEventos(); a++) //percorre a lista de eventos
         {
            if ((partida->obtemEvento(a)->obtemJogador() == temp) && (partida->obtemEvento(a)->obtemEvento() == ENTRADA))
            {
               entrada = partida->obtemEvento(a)->obtemMinuto(); //se o jogador do evento a for igual o jogador temp e o evento for de entrada, atualiza o valor de entrada
            }
            if ((partida->obtemEvento(a)->obtemJogador() == temp) && (partida->obtemEvento(a)->obtemEvento() == SAIDA))
            {
               saida = partida->obtemEvento(a)->obtemMinuto(); //se o jogador do evento a for igual o jogador temp e o evento for de saida, atualiza o valor de saida
            }
         }
         jogador.push_back(temp); //push back o jogador temp
         minuto_e.push_back(entrada); //push back o valor de entrada
         minuto_s.push_back(saida); //push back o valor de saida
      }
   }

   for (int i = 0; i < jogador.size(); i++)
   {
      cout << jogador[i]->str() << " ==> " << minuto_s[i] - minuto_e[i] << " minutos" << endl; // imprime os jogadores
   }
}
//--------------------------------------------------------

bool Aplicacao::carregaPaises(string nomeArquivo)
{
   for (int i = 0; i < paises.size(); ++i)
      delete paises[i];
   paises.clear();
   ifstream f(nomeArquivo);
   if (!f.is_open())
      return false;
   string linhaCSV;
   while (getline(f, linhaCSV))
   {
      vector<string> campos = splitCSV(linhaCSV, ';');
      if (campos.size() != 3)
      {
         f.close();
         return false;
      }
      paises.push_back(new Pais(campos[0], campos[1], campos[2]));
   }
   f.close();
   return true;
}

void Aplicacao::mostraPaises()
{
   for (int i = 0; i < paises.size(); ++i)
      cout << paises[i]->str() << endl;
}

void Aplicacao::ordenaPaises()
{
   for (int i = 0; i < paises.size() - 1; ++i)
   {
      int men = i;
      for (int j = i + 1; j < paises.size(); ++j)
      {
         if (*paises[j] < *paises[men])
            men = j;
      }
      if (men != i)
      {
         Pais *aux = paises[men];
         paises[men] = paises[i];
         paises[i] = aux;
      }
   }
}

Pais *Aplicacao::obtemPais(string sigla)
{
   for (int i = 0; i < paises.size(); ++i)
   {
      if (paises[i]->obtemSigla() == sigla)
         return paises[i];
   }
   return nullptr;
}

bool Aplicacao::carregaArbitros(string nomeArquivo)
{
   for (int i = 0; i < arbitros.size(); ++i)
      delete arbitros[i];
   arbitros.clear();
   ifstream f(nomeArquivo);
   if (!f.is_open())
      return false;
   string linhaCSV;
   while (getline(f, linhaCSV))
   {
      vector<string> campos = splitCSV(linhaCSV, ';');
      if (campos.size() != 4)
      {
         f.close();
         return false;
      }
      Pais *p = obtemPais(campos[3]);
      Data d(campos[2]);
      arbitros.push_back(new Arbitro(stoi(campos[0]), campos[1], d, p));
   }
   f.close();
   return true;
}

void Aplicacao::mostraArbitros()
{
   for (int i = 0; i < arbitros.size(); ++i)
      cout << arbitros[i]->str() << endl;
}

void Aplicacao::ordenaArbitros()
{
   for (int i = 0; i < arbitros.size() - 1; ++i)
   {
      int men = i;
      for (int j = i + 1; j < arbitros.size(); ++j)
      {
         if (*arbitros[j] < *arbitros[men])
            men = j;
      }
      if (men != i)
      {
         Arbitro *aux = arbitros[men];
         arbitros[men] = arbitros[i];
         arbitros[i] = aux;
      }
   }
}

bool Aplicacao::carregaPartida(string nomeArquivo)
{
   ifstream f(nomeArquivo);
   if (!f.is_open())
      return false;
   string linhaCSV;
   if (getline(f, linhaCSV))
   {
      vector<string> campos = splitCSV(linhaCSV, ';');
      if (campos.size() != 5)
      {
         f.close();
         return false;
      }
      Data d(campos[0]);
      partida = new Partida(d, campos[1], obtemPais(campos[2]), obtemPais(campos[3]), stoi(campos[4]));
      while (getline(f, linhaCSV))
      {
         vector<string> camposEvento = splitCSV(linhaCSV, ';');
         if (camposEvento.size() != 4)
         {
            f.close();
            return false;
         }
         Jogador *j = obtemJogador(camposEvento[1], stoi(camposEvento[2]));
         partida->adicionaEvento(stoi(camposEvento[0]), j, string2evento_t(camposEvento[3]));
      }
   }
   f.close();
   return true;
}
