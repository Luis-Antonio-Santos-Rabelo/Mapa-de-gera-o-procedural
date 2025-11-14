template<typename T>


class Matriz{
    int lin, col;
    T padrao;
    T *dados;
    public:
        Matriz(int max_lin, int max_col, T padrao){
            lin = max_lin;
            col = max_col;
            this->padrao = padrao;
            dados = new T[lin * col];
            for(int i = 0; i < max_lin; i++){
                for(int j = 0; j < max_col; j++){
                    dados[i * col + j] = padrao;
                    
                }
            }
        }

        Matriz(T padrao) : lin(1), col(1), padrao(padrao) {
            dados = new T[1];
            
        }   

        ~Matriz() {
            delete[] dados;
        }


        T getValue(int linha, int coluna) {
            if (linha < lin && coluna < col) {
                return dados[linha * col + coluna];    
            }
            return padrao;
        }
};



