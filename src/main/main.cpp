#include <iostream>
#include <string>
#include <sstream>
#include "../sequencia/sequencia.h"
#include "../imagem/imagem.h"
#include "../terreno/terreno.h"
#include "../paleta/paleta.h"

using namespace std;

bool processarEntrada(string& paleta, int& expo) {
  string input;
  Sequencia<string> comandos(5);    

  std:getline(cin, input);
  stringstream stream(input);
  
  string tmp;

  while (stream >> tmp) {
    comandos.adicionar(tmp);
  }
  


  if(comandos[0] == "help") {
    cout << "Comandos disponíveis:\n\n";
    cout << "help                        | mostra comandos disponíveis\n";
    cout << "ping                        | pong!\n";
    cout << "exit                        | sai do programa\n";
    cout << "tamanho [expoente]          | muda o expoente para a geração do terreno\n";
    cout << "paleta [nome_da_paleta.hex] | muda a paleta usada\n";
    cout << "gen                         | gera o terreno\n";
    cout << "genquad                     | gera terreno quadriculado\n";

  } else if (comandos[0] == "exit") {
    return false;
    
  } else if  (comandos[0] == "ping") {
    
    cout << "pong!\n";
  } else if (comandos[0] == "test") {
    Terreno t(expo);
    t.genCantos(90);
    t.geraTerreno();
    t.normalizaTerreno();
    Imagem img = t.escalaDeCinzas();
    img.salvarPPM("teste_main.ppm");

    cout << "Mapa pronto\n";
    
    
  } else if (comandos[0] == "paleta") {
    if(comandos[1] != "paleta") {
      paleta = comandos[1];

    }
  } else if (comandos[0] == "gen") {
    Terreno t(expo, time(0), 0.7f);
    t.genCantos(120);
    t.geraTerreno();
    t.normalizaTerreno();
    Paleta palet(paleta);
    Imagem img = t.converterParaImagemColorida(palet);
    img.salvarPPM("terrenoGerado.ppm");
    cout << "Mapa criado\n";
    t.testRNG();
    
  } else if(comandos[0] == "tamanho") {
    if(comandos.obterTamanho() > 1) expo = stoi(comandos[1]);
  }

  return true;
}

int main() {
  bool running = true;
  string lastInput = "";
  Paleta paleta("cores.hex");
  string nomePaleta = "cores.hex";
  int expo = 9;
  
  while(running) {
    int size = pow(2, expo) + 1;
    paleta = Paleta(nomePaleta);

    cout << "Oi essa é a Procedural-Shell!" << "\n";
    cout << "Atualmente essas são suas especificações de geração: \n";
    cout << "Tamanho imagem: " << size << "x" << size << "\n";
    cout << "Paleta: " << nomePaleta << "\n";
    running = processarEntrada(nomePaleta, expo);
  }
}
