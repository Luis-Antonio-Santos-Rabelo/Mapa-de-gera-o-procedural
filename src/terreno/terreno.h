#include "../sequencia/matriz.h"
#include "../sequencia/sequencia.h"
#include <cmath>


class Terreno {
  Matriz<int> alturas;
  int seed;

  void diamond(int p[2], int contador) {
    
    int passo = obterLargura() / std::pow(2, contador);
    //if (passo == 0) return;
    int sum = alturas.getRef(p[0] - passo, p[1] - passo);
    sum += alturas.getRef(p[0] + passo, p[1] - passo);
    sum += alturas.getRef(p[0] - passo, p[1] + passo);
    sum += alturas.getRef(p[0] + passo, p[1] + passo);

    alturas.mudarValor(p[0], p[1], sum/4);
    
  }

  void square(int p[2], int contador) {
    int passo = obterLargura() / std::pow(2, contador);
    int size = this->obterLargura();
    
    //if (passo == 0) return;

    int tamanhoAmostra = 0;

    int sum = 0;

    if (p[1] - passo >= 0) {
      tamanhoAmostra++;
      sum += alturas.getRef(p[0], p[1] - passo);
    }

    if (p[1] + passo < size) {
      tamanhoAmostra++;
      sum += alturas.getRef(p[0], p[1] + passo);
    }

    if (p[0] - passo >= 0) {
      tamanhoAmostra++;
      sum += alturas.getRef(p[0] - passo, p[1]);
    }

    if (p[0] + passo < size) {
      tamanhoAmostra++;
      sum += alturas.getRef(p[0] + passo, p[1]);
    }
        
    alturas.mudarValor(p[0], p[1], sum/tamanhoAmostra);

  }


  void diamondSquare(int ponto[2], int contador) {
    int size = alturas.getLinhas();
    int nCounter = contador + 1;
    int passo = size / std::pow(2, nCounter);
    if (passo == 0) return;
    
    int meioPasso = passo / 2;
    
    
    diamond(ponto, nCounter);

    int p1[2] = {ponto[0] + passo, ponto[1]};
    int p2[2] = {ponto[0], ponto[1] - passo};
    int p3[2] = {ponto[0], ponto[1] + passo};
    int p4[2] = {ponto[0] - passo, ponto[1]};
    
    square(p1, nCounter);
    square(p2, nCounter);
    square(p3, nCounter);
    square(p4, nCounter);

    //if (meioPasso == 0) return;


    int np1[2] = {ponto[0] + meioPasso, ponto[1] + meioPasso};
    int np2[2] = {ponto[0] + meioPasso, ponto[1] - meioPasso};
    int np3[2] = {ponto[0] - meioPasso, ponto[1] + meioPasso};
    int np4[2] = {ponto[0] - meioPasso, ponto[1] - meioPasso};
    
    diamondSquare(np1, nCounter);
    diamondSquare(np2, nCounter);
    diamondSquare(np3, nCounter);
    diamondSquare(np4, nCounter);
    
  }
  
  public:
    Terreno(int exp) {
      int lado;
      if (exp == 0) lado = 1;
      else lado = std::pow(2, exp) + 1;
      alturas = Matriz(lado, lado, 0);
      seed = time(0);
    }

    void genCantos() {
      
    }


    void diamondTest(int p[2], int contador) {

      int passo = obterLargura() / std::pow(2, contador);
      int sum = alturas.getRef(p[0] - passo, p[1] - passo);
      sum += alturas.getRef(p[0] + passo, p[1] - passo);
      sum += alturas.getRef(p[0] - passo, p[1] + passo);
      sum += alturas.getRef(p[0] + passo, p[1] + passo);

      alturas.mudarValor(p[0], p[1], sum/4);
      
    }

    void squareTest(int p[2], int contador) {
      int passo = obterLargura() / std::pow(2, contador);
      int size = this->obterLargura();
    
      int tamanhoAmostra = 0;
      int sum = 0;

      if (p[1] - passo >= 0) {
        tamanhoAmostra++;
        sum += alturas.getRef(p[0], p[1] - passo);
      }

      if (p[1] + passo < size) {
        tamanhoAmostra++;
        sum += alturas.getRef(p[0], p[1] + passo);
      }

      if (p[0] - passo >= 0) {
        tamanhoAmostra++;
        sum += alturas.getRef(p[0] - passo, p[1]);
      }

      if (p[0] + passo < size) {
        tamanhoAmostra++;
        sum += alturas.getRef(p[0] + passo, p[1]);
      }
        
      alturas.mudarValor(p[0], p[1], sum/tamanhoAmostra);
      
    }

    void diamondSquareTest(int ponto[2], int contador) {
      int size = alturas.getLinhas();
      int nCounter = contador + 1;
      int passo = size / std::pow(2, nCounter);

      if (passo == 0) return;
    
      int meioPasso = passo / 2;
    
    
      diamondTest(ponto, nCounter);

      int p1[2] = {ponto[0] + passo, ponto[1]};
      int p2[2] = {ponto[0], ponto[1] - passo};
      int p3[2] = {ponto[0], ponto[1] + passo};
      int p4[2] = {ponto[0] - passo, ponto[1]};
    
      squareTest(p1, nCounter);
      squareTest(p2, nCounter);
      squareTest(p3, nCounter);
      squareTest(p4, nCounter);


      int np1[2] = {ponto[0] + meioPasso, ponto[1] + meioPasso};
      int np2[2] = {ponto[0] + meioPasso, ponto[1] - meioPasso};
      int np3[2] = {ponto[0] - meioPasso, ponto[1] + meioPasso};
      int np4[2] = {ponto[0] - meioPasso, ponto[1] - meioPasso};
    
      diamondSquareTest(np1, nCounter);
      diamondSquareTest(np2, nCounter);
      diamondSquareTest(np3, nCounter);
      diamondSquareTest(np4, nCounter);
    
  }
    
    

    int obterLargura() { return alturas.getColunas();}
    int obterProfundidade() {return alturas.getLinhas();}

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
  
  
};
