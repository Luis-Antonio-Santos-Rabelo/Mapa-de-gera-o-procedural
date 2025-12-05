#pragma once

#include "../sequencia/matriz.h"
#include "../sequencia/sequencia.h"
#include <cstdlib>
#include <limits>
#include <string>
#include <sstream>
#include <fstream>


struct Pixel{
  unsigned char r, g, b;
};


class Imagem {
  Matriz<Pixel> img;
  int lin, col;


  public:
    Imagem() : lin(1), col(1), img(Matriz(1, 1, (Pixel){0, 0, 0})) {}

    Imagem(int colunas, int linhas) : col(colunas), lin(linhas), img(Matriz(linhas, colunas, (Pixel){0,0,0})) {}
    
    bool lerPPM(std::string path) {
      std::ifstream reader(path);
    
      if (!reader.is_open()) {
        std::cerr << "Erro abrindo arquivo: " << path << "\n";
        return false;
      }

      std::string header;
      int maxVal;

      reader >> header;
      if (header != "P3") {
        std::cerr << "Formato de arquivo invalido(nao e P3)" << "\n";
        return false;
      }

    reader >> col >> lin;

    reader >> maxVal; 

    img.atribuir(Matriz<Pixel>(lin, col, {0, 0, 0}));

    for(int i = 0; i < lin; i++) {
        for (int j = 0; j < col; j++) {
            if (reader.eof()) break; 

            Pixel tmpPixel;
            int r, g, b;

            reader >> r >> g >> b;

            tmpPixel.r = (unsigned char)r;
            tmpPixel.g = (unsigned char)g;
            tmpPixel.b = (unsigned char)b;
            
            img.mudarValor(i, j, tmpPixel);
        }
    }  
    
    reader.close();
    return true;
    }

    bool salvarPPM(std::string fileName) {
      std::string tmp;
      tmp.append("P3");
      tmp.append("\n" + std::to_string(col) + " " + std::to_string(lin) + "\n" + "255" + "\n");

      for (int i = 0; i < lin; i++) {
        for (int j = 0; j < col; j++) {
          tmp.append(std::to_string(img.getValor(i, j).r) + " " + std::to_string(img.getValor(i, j).g) + " " + std::to_string(img.getValor(i, j).b));
          tmp.append("\n");
        }
        
      }
      
        std::ofstream file;
        file.open(fileName);
        if (!file.is_open()) {
          std::cout << "Erro de abertura";
          return false;
        }

        file << tmp;
        file.close();

        return true;
    }
    

    int obterLargura() {
      return col;
    }
        
    int obterAltura() {
      return lin;
    }

    Pixel& operator()(int coluna, int linha) {
      return img.getRef(linha, coluna);
    }    

};
