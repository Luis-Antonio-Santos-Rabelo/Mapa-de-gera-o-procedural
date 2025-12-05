#pragma once

#include "../sequencia/matriz.h"
#include "../sequencia/sequencia.h"
#include "../imagem/imagem.h"
#include "../paleta/paleta.h"
#include <cmath>
#include <cstdlib>


class Terreno {
  Matriz<int> alturas;
  int expoente;
  int seed;
  int limiteRNG = 60;
  float rugosidade = 0.5;
  


  int rng(int lin, int col) {
    std::srand((unsigned int)(seed + lin * obterLargura() + col));
    return (((std::rand() % (2 * limiteRNG))) - limiteRNG);
    
  }

  bool dentro(int x, int y) {
    return (x >= 0 && x < alturas.getColunas() && y >= 0 && y < alturas.getLinhas());
  }
  
  public:
    Terreno(int exp) {
      int lado;
      if (exp == 0) lado = 1;
      else lado = std::pow(2, exp) + 1;
      alturas = Matriz(lado, lado, 0);
      seed = time(0);
      expoente = exp;
    }

    Terreno(int exp, int semente, float rug) {
      int lado;
      if (exp == 0) lado = 1;
      else lado = std::pow(2, exp) + 1;
      alturas = Matriz(lado, lado, 0);
      seed = semente;
      rugosidade = rug;
      expoente = exp;
    }    

    void genCantos(int limites) {
      int size = obterLargura();
      std::srand((unsigned int)(seed + 0 * obterLargura() + 0));
      int val1 = ((std::rand() % (2 * limites * 4))) - (limites*4);

      std::srand((unsigned int)(seed + 0 * size + (size-1)));
      int val2 = ((std::rand() % (2 * limites * 4))) - (limites*4);

      std::srand((unsigned int)(seed + (size-1) * size + 0));
      int val3 = ((std::rand() % (2 * limites * 4))) - (limites*4);


      std::srand((unsigned int)(seed + (size-1) * size + (size-1)));
      int val4 = ((std::rand() % (2 * limites * 4))) - (limites*4);

      alturas.getRef(0,0) = val1;
      alturas.getRef(0,size-1) = val2;      
      alturas.getRef(size-1,0) = val3;
      alturas.getRef(size-1,size-1) = val4;
        
    }

    void geraTerreno() {
      int size = obterLargura();
      int passo = size - 1;
      float rug = 1.0f;

      while (passo > 1) {
        int meioPasso = passo / 2;
        //rug = rug * rugosidade;

        //Diamond aqui
        for (int i = 0; i < size - 1; i += passo) {
          for (int j = 0; j < size - 1; j += passo) {
            
            int v1 = alturas.getValor(i, j);                 
            int v2 = alturas.getValor(i + passo, j);         
            int v3 = alturas.getValor(i, j + passo);         
            int v4 = alturas.getValor(i + passo, j + passo); 

            int media = (v1 + v2 + v3 + v4) / 4;
            
            alturas.mudarValor(i + meioPasso, j + meioPasso, media + rng(i, j) * rug);

          }
        }

        //Square aqui
        for (int i = 0; i < size; i += meioPasso) {
            for (int j = (i + meioPasso) % passo; j < size; j += passo) {
                
                int sum = 0;
                int tamanhoAmostra = 0;

                if (dentro(i, j - meioPasso)) { sum += alturas.getValor(i, j - meioPasso); tamanhoAmostra++; }
                
                if (dentro(i, j + meioPasso)) { sum += alturas.getValor(i, j + meioPasso); tamanhoAmostra++; }
                
                if (dentro(i - meioPasso, j)) { sum += alturas.getValor(i - meioPasso, j); tamanhoAmostra++; }
                
                if (dentro(i + meioPasso, j)) { sum += alturas.getValor(i + meioPasso, j); tamanhoAmostra++; }

                int media = sum / tamanhoAmostra;
                alturas.mudarValor(i, j, media + rng(i, j) * rug);
            }
        }

        passo /= 2;
        rug = rug * rugosidade;
      }
    }

    int obterLargura() { return alturas.getColunas();}
    int obterProfundidade() {return alturas.getLinhas();}
    int obterExpoente() {return expoente;}

    int& operator()(int col, int lin) {
      return alturas.getRef(col, lin);
    }

    void print() {
      for(int i = 0; i < alturas.getLinhas(); i++) {
        for(int j = 0; j < alturas.getColunas(); j++) {
          std::cout << alturas.getValor(i, j) << " ";
        }   
        std::cout << "\n";
      }  
      
    }

    void normalizaTerreno() {
      int min = std::numeric_limits<int>::max();
      int max = std::numeric_limits<int>::lowest();
      
      for (int i = 0; i < this->obterLargura(); i++) {
        for(int j = 0; j < this->obterProfundidade(); j++) {
          int tmp  = (*this)(i , j);
          if (tmp < min) min = tmp;
          if (tmp > max) max = tmp;
        }
      }

      for (int i = 0; i < this->obterLargura(); i++) {
        for(int j = 0; j < this->obterProfundidade(); j++) {
            int tmp = (*this)(i, j);
            int valor;

            if (max - min != 0) {
                valor = 0 + (tmp - min) * (255 - 0) / (max - min);
            } else {
                valor = (0 + 255) / 2;
            }

            (*this)(i, j) =  valor;
        }
      }
    }  

    Imagem escalaDeCinzas() {
      Imagem img = Imagem(obterLargura(), obterProfundidade());
      for (int i = 0; i < obterLargura(); i++) {
        for(int j = 0; j < obterProfundidade(); j++) {
          unsigned char tmp  = (unsigned char)(*this)(i , j);

          Pixel cinza  = {tmp, tmp, tmp};
          img(i, j) = cinza;     
          
        }
      }
      return img;
    }  

    Imagem converterParaImagemColorida(Paleta& paleta) {
      int min = std::numeric_limits<int>::max();
      int max = std::numeric_limits<int>::lowest();
      
      for (int i = 0; i < alturas.getLinhas(); i++) {
        for (int j = 0; j < alturas.getColunas(); j++) {
          int val = alturas.getValor(i, j);
          if (val < min) min = val;
          if (val > max) max = val;
        }
      }

      Imagem img(alturas.getColunas(), alturas.getLinhas());

      int range = max - min;
      int maxIndicePaleta = paleta.obterTamanho() - 1;

      for (int i = 0; i < alturas.getLinhas(); i++) {
        for (int j = 0; j < alturas.getColunas(); j++) {
          
          int alturaAtual = alturas.getValor(i, j);
          int indice;

          if (range == 0) {
              indice = 0; 
          } else {
              indice = (int)(((long)(alturaAtual - min) * maxIndicePaleta) / range);
          }

          if (indice < 0) indice = 0;
          if (indice > maxIndicePaleta) indice = maxIndicePaleta;

          Cor tmp = paleta.obterCor(indice); 
          
          img(j, i) = {tmp.r, tmp.g, tmp.b}; 
        }
      }

      return img;
    }



    void testRNG() {
     std::cout << rng(1, 2) << " " << rng(2, 3) << "\n";
    }
  
};
