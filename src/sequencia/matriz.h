#pragma once

#include <algorithm>
#include <new>


template<typename T>
class Matriz{
    int lin, col;
    T padrao;
    T *dados;
    public:
        Matriz(int max_lin, int max_col, T padrao) : lin(max_lin), col(max_col){
            this->padrao = padrao;
            dados = new T[lin * col];
            for(int i = 0; i < max_lin * max_col; i++){
                    dados[i] = padrao;
            }
        }

        Matriz() : lin(1), col(1), padrao() {
            dados = new T[1];
        }   

        ~Matriz() {
            delete[] dados;
        }

        void atribuir(Matriz<T> outra) {
            lin = outra.lin;
            col = outra.col;
            delete[] dados;
            dados = new T[lin * col];
            for(int i = 0; i < lin * col; i++) {
                dados[i] = outra.dados[i];    
            }
            
            
        }

        
        //Operador de cópia, necessário para poder retornar de uma função
        Matriz(const Matriz& outra) : lin(outra.lin), col(outra.col), padrao(outra.padrao) {
            dados = new T[lin * col];
            for(int i = 0; i < lin * col; i++) {
                dados[i] = outra.dados[i];
            }
        }
        

        Matriz<T>& operator=(const Matriz<T>& outra) {
            if (this == &outra) {
                return *this;
            }

            lin = outra.lin;
            col = outra.col;
            delete[] dados;
            dados = new T[lin * col];
            for(int i = 0; i < lin * col; i++) {
                dados[i] = outra.dados[i];    
            }

            return *this;
            
        }


        T getValor(int linha, int coluna) {
            if (linha < lin && coluna < col) {
                return dados[linha * col + coluna];    
            }
            return padrao;
        }

        bool mudarValor(int linha, int coluna, T val){
             if(linha < lin && coluna  < col) {
                 dados[linha * col + coluna] = val;
                 return true;
             }
             return false;
        }

        void mudarTamanho(int linha, int coluna) {
            T *novo = new T[linha * coluna];
            for (int i = 0; i < lin; i++) {
              if (i > linha)
                break;
              for (int j = 0; j < col; j++) {
                if (j > coluna)
                  break;
                novo[i * coluna + j] = dados[i * col + j];
              }
            }
            delete[] dados;
            lin = linha;
            col = coluna;
            dados = novo;
            
        }

        T& getRef(int linha, int coluna) {
            return dados[linha * col + coluna];
        }

        int getLinhas() {return lin;}
        int getColunas() {return col;}
};



