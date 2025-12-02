#include <iostream>
#include <string>
#include <sstream>
#include "../sequencia/sequencia.h"

using namespace std;

bool processarEntrada() {
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
    cout << "help | mostra comandos disponíveis\n";
    cout << "ping | pong!\n";
    cout << "exit | sai do programa\n";

  } else if (comandos[0] == "exit") {
    return false;
    
  } else if  (comandos[0] == "ping") {
    
    cout << "pong!\n";
  }

  return true;
}

int main() {
  bool running = true;
  string lastInput = "";
  
  while(running) {
    cout << "Oi essa é a Procedural-Shell!" << "\n";
    cout << "Atualmente essas são suas especificações de geração: \n";
    running = processarEntrada();
  }
}




