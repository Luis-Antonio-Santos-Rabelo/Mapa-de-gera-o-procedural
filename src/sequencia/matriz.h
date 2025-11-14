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
};



