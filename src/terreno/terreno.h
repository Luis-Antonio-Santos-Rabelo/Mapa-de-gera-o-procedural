#include "../sequencia/matriz.h"
#include "../sequencia/sequencia.h"
#include <cmath>
#include <cstdlib>


class Terreno {
  Matriz<int> alturas;
  int seed;
  int limiteRNG = 20;
  float rugosidade = 0.5;
  


  int rng(int lin, int col) {
    std::srand((unsigned int)(seed + lin * obterLargura() + col));
    return ((std::rand() % (2 * limiteRNG))) - limiteRNG;
    
  }

  void diamond(int p[2], int contador) {
    
    int passo = obterLargura() / std::pow(2, contador);
    int deslocamento = rng(p[0], p[1]) * rugosidade;
    int sum = alturas.getRef(p[0] - passo, p[1] - passo);
    sum += alturas.getRef(p[0] + passo, p[1] - passo);
    sum += alturas.getRef(p[0] - passo, p[1] + passo);
    sum += alturas.getRef(p[0] + passo, p[1] + passo);

    alturas.mudarValor(p[0], p[1], (sum/4) + deslocamento);
    
  }

  void square(int p[2], int contador) {
    int passo = obterLargura() / std::pow(2, contador);
    int size = this->obterLargura();
    
    //if (passo == 0) return;

    int tamanhoAmostra = 0;

    int sum = 0;

    int deslocamento = rng(p[0], p[1]) * rugosidade;

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
        
    alturas.mudarValor(p[0], p[1], (sum/tamanhoAmostra) + deslocamento);

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

    int np1[2] = {ponto[0] + meioPasso, ponto[1] + meioPasso};
    int np2[2] = {ponto[0] + meioPasso, ponto[1] - meioPasso};
    int np3[2] = {ponto[0] - meioPasso, ponto[1] + meioPasso};
    int np4[2] = {ponto[0] - meioPasso, ponto[1] - meioPasso};

    rugosidade = rugosidade / 2;

    
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

    Terreno(int exp, int semente) {
      int lado;
      if (exp == 0) lado = 1;
      else lado = std::pow(2, exp) + 1;
      alturas = Matriz(lado, lado, 0);
      seed = semente;
    }
    

    void genCantos() {
      int size = obterLargura();
      std::srand((unsigned int)(seed + 0 * obterLargura() + 0));
      int val1 = ((std::rand() % (2 * limiteRNG * 4))) - (limiteRNG*2);

      std::srand((unsigned int)(seed + 0 * size + (size-1)));
      int val2 = ((std::rand() % (2 * limiteRNG * 4))) - (limiteRNG*2);

      std::srand((unsigned int)(seed + (size-1) * size + 0));
      int val3 = ((std::rand() % (2 * limiteRNG * 4))) - (limiteRNG*2);


      std::srand((unsigned int)(seed + (size-1) * size + (size-1)));
      int val4 = ((std::rand() % (2 * limiteRNG * 4))) - (limiteRNG*2);

      alturas.getRef(0,0) = val1;
      alturas.getRef(0,size-1) = val2;      
      alturas.getRef(size-1,0) = val3;
      alturas.getRef(size-1,size-1) = val4;
        
    }

    void geraTerreno() {
      int p[2] = {obterLargura() / 2, obterProfundidade() / 2};
      this->diamondSquare(p, 0);
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

      rugosidade = rugosidade / 2;
    
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
