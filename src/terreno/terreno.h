#include "../sequencia/matriz.h"
#include "../sequencia/sequencia.h"
#include <cmath>

class Terreno {
  Matriz<int> alturas;

  public: void diamond(int p[2], int contador) {
    
    int passo = obterLargura() / std::pow(2, contador);
    if (passo == 0) return;
    int sum = alturas.getRef(p[0] - passo, p[1] - passo);
    sum += alturas.getRef(p[0] + passo, p[1] - passo);
    sum += alturas.getRef(p[0] - passo, p[1] + passo);
    sum += alturas.getRef(p[0] + passo, p[1] + passo);

    alturas.mudarValor(p[0], p[1], sum/4);
    //std::cout << "Valor é: " << sum/4;  
    
  }

  void square(int p[2], int contador) {
    int passo = obterLargura() / std::pow(2, contador) + 1;
    if (passo == 0) return;
    int sum = alturas.getRef(p[0], p[1] - passo);
    sum += alturas.getRef(p[0], p[1] + passo);
    sum += alturas.getRef(p[0] - passo, p[1]);
    sum += alturas.getRef(p[0] + passo, p[1]);
    
  }
  
  //public:
    Terreno(int exp) {
      int lado;
      if (exp == 0) lado = 1;
      else lado = std::pow(2, exp) + 1;
      alturas = Matriz(lado, lado, 0);
    }

    int obterLargura() { return alturas.getColunas();}
    int obterProfundidade() {return alturas.getLinhas();}

    int& operator()(int col, int lin) {
      return alturas.getRef(lin, col);
    }

    
  
  
};
