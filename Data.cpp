#include "Data.hpp"
#include <sstream>
#include <iostream>

using namespace std;

//construtor
Data::Data(int dia, int mes, int ano) {
    this->dia = dia;
    this->mes = mes;
    this->ano = ano;
}

//construtor se o parametro for uma string
Data::Data(string s)
{
    stringstream ss; //cria o stringstream
    ss << s[0] << s[1]; //insere os primeiros dois valores da string no stringstream (dia)
    dia = stoi(ss.str()); //converte a string para inteiro e coloca na variavel dia
    ss.str(""); //reseta o stringstream
    ss << s[3] << s[4]; // insere os valores nas posições 3 e 4 da string (mes); isso pula o caracter "/" da string
    mes = stoi(ss.str()); //converte a string para inteiro e coloca na variavel mes
    ss.str(""); //reseta o stringstream
    ss << s[6] << s[7] << s[8] << s[9]; //insere os valores nas posições 6-9 no stringstream (ano) 
    ano = stoi(ss.str()); //converte esse valor para inteiro e coloca na variavel ano
}

//destrutor
Data::~Data() {}

//getter e setter
int Data::obtemDia() const {
    return dia;
}

int Data::obtemMes() const {
    return mes;
}

int Data::obtemAno() const {
    return ano;
}

void Data::defineDia(int d) { dia = d; }
void Data::defineMes(int m) { mes = m; }
void Data::defineAno(int a) { ano = a; }
void Data::defineData(int d, int m, int a) {
    dia = d;
    mes = m;
    ano = a;
}

//imprime a data no formato adequado
string Data::str() const {
    stringstream ss;
    if (dia < 10 && mes < 10) {
         ss << "0" << dia << "/"
            << "0" << mes << "/" << ano;
         return ss.str();
    } else if (dia < 10) {
        ss << "0" << dia << "/" << mes << "/" << ano;
        return ss.str();
    } else if (mes < 10) {
        ss << dia << "/" << "0" << mes << "/" << ano;
        return ss.str();
    } else {
        ss << dia << "/" << mes << "/" << ano;
    }
    return ss.str();
}

//sobrecarga de operadores
bool Data::operator<(const Data &d) const {
    if (ano < d.ano) {
        return true;
    } 
    if (mes < d.mes) {
        return true;
    } 
    if (dia < d.dia) {
        return true;
    }
    return false;
}

bool Data::operator>(const Data &d) const {
    if (ano > d.ano) {
        return true;
    } 
    if (mes > d.mes) {
        return true;
    } 
    if (dia > d.dia) {
        return true;
    }
    return false;
}

bool Data::operator==(const Data &d) const {
    return (d.dia == dia && d.mes == mes && d.ano == ano);
}

bool Data::operator!=(const Data &d) const {
    return (d.dia != dia || d.mes || mes && d.ano || ano);
}

bool Data::operator<=(const Data &d) const {
    if (ano <= d.ano) {
        return true;
    } 
    if (mes <= d.mes) {
        return true;
    } 
    if (dia <= d.dia) {
        return true;
    }
    return false;
}

bool Data::operator>=(const Data &d) const {
    if (ano >= d.ano) {
        return true;
    } 
    if (mes >= d.mes) {
        return true;
    } 
    if (dia >= d.dia) {
        return true;
    }
    return false;
}

ostream &operator<<(ostream &out, const Data &d) {
    out << d.dia << "/" << d.mes << "/" << d.ano;
    return out;
}