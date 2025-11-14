

#include <iostream>


template<typename T>
class Sequencia {
  int capacidade;
  int tamanho;
  T *dados;

  void ajustaCapacidade() {
    capacidade++;
    capacidade *= 2;
    T *novo = new T[capacidade];
    for (int i = 0; i < tamanho; i++) {
      novo[i] = dados[i];
    }
    delete[] dados;
    dados = novo;
   }

public:
  ~Sequencia() {
    delete[] dados;
  }

  Sequencia(int cap = 2) : capacidade(cap), tamanho(0) {
    dados = new T[capacidade];
  }

  int obterTamanho() {
    return tamanho;
  }

  void adicionar(T valor) {
    if (tamanho < capacidade){
      dados[tamanho] = valor;
      tamanho++;
      
    } else {
      ajustaCapacidade();
      adicionar(valor);
    }
  }

  T& operator[](int index) {
    if (index < tamanho && index >= 0) {
      return dados[index];
    }
    else {
      return dados[0];
    }
  } 

  void removerUltimo() {
    if (tamanho <= 0) {
      std::cout << "Error, tamanho menor que 1";
    } else {
      tamanho--;
    }
  }
  
};
