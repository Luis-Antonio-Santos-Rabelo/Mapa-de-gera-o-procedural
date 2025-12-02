#pragma once

#include "../sequencia/sequencia.h"
#include <cmath>
#include <fstream>
#include <string>
#include <iostream>

struct Cor {
  unsigned char r, g, b;
};

class Paleta {
  Sequencia<Cor> paletaInterna;
  int tamanho;

  unsigned char hexStringToInt(std::string input) {
    unsigned char sum = 0;
    
    for(int i = 0; i < input.size(); i++) {
      unsigned char c = input[i];
      unsigned char stepVal = (std::pow(16, (1 - i)));
      
      if (c > 47 && c < 58){
        sum += (c-48) * stepVal;
      
      } else if (c > 96 && c < 103) {
        sum += (c-87) * stepVal;
        
      }
    } 

    return sum;
  }

  public:
    Paleta() :tamanho(0), paletaInterna(Sequencia<Cor>(0)) {}

    Paleta(std::string path) {
      std::ifstream input;
      std::string tmpString = "";

      input.open(path);

      if(!input.is_open()) {
        std::cerr << "Erro abrindo o arquivo";
        tamanho = 0;
        
      } else {

        Sequencia<std::string> lineArray = Sequencia<std::string>(10);

        while (std::getline(input, tmpString)) {
          lineArray.adicionar(tmpString);
        }
      
        paletaInterna = Sequencia<Cor>(lineArray.obterTamanho());
      

        for (int i = 0; i < lineArray.obterTamanho(); i++) {
          Cor tmpC = Cor {
            hexStringToInt(lineArray[i].substr(1, 2)),
            hexStringToInt(lineArray[i].substr(3, 2)),
            hexStringToInt(lineArray[i].substr(5, 2)),
          };

          paletaInterna.adicionar(tmpC);     
        }

        tamanho = paletaInterna.obterTamanho();
      }
      input.close();
    }
    
    int obterTamanho(){
      return tamanho;
    };


    void adicionarCor(Cor cor) {
      paletaInterna.adicionar(cor);
      tamanho = paletaInterna.obterTamanho();
    }

    Cor obterCor(int index) {
      if (index > -1 && index < tamanho) {
        return paletaInterna[index];    
      }

      return Cor {0, 0, 0};
    
    }

    
    
    
};


