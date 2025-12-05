#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"
#include "terreno.h"

TEST_CASE("Testa a criação de um terreno de uma única célula") {
  Terreno terreno(0); // 2^0 + 1 = 1
  CHECK(terreno.obterLargura() == 1);
  CHECK(terreno.obterProfundidade() == 1);
}

TEST_CASE("Testa a geração aleatória de altitudes") {
  Terreno terreno(2);
  CHECK(terreno.obterLargura() == 5);
  CHECK(terreno.obterProfundidade() == 5);
}

TEST_CASE("Testa o passo diamond") {
  Terreno terreno(2);
  terreno(0, 0) = 3;
  terreno(0, 4) = 5;
  terreno(4, 0) = 3;
  terreno(4, 4) = 5;
  int ponto[2] = {2, 2};
  
  CHECK(terreno(2, 2) == 4);
  
}

TEST_CASE("Testa o diamondSquare") {
  Terreno terreno(2);
  terreno(0, 0) = 4;
  terreno(0, 4) = 8;
  terreno(4, 0) = 4;
  terreno(4, 4) = 3;
  int ponto1[2] = {2, 2};

  
  terreno.geraTerreno();

  CHECK(terreno(1, 1) == 4);
    
}

TEST_CASE("Testa a geração de cantos") {
  Terreno terreno(3);
  terreno.genCantos(60);


  bool cantos = terreno(0, 0) != 0 || terreno(8, 0) != 0 || terreno(0, 8) != 0 || terreno(8,8) != 0;

  CHECK(cantos);
}

TEST_CASE("Testa a geração de cantos a partir de uma seed fixa") {
  Terreno terreno(3, 44, 0.5);
  terreno.genCantos(60);

  CHECK(terreno(0, 0) != 0);
  terreno.print();

}

TEST_CASE("Testa a geração aleatoria de cantos, mas manualmente") {
  Terreno terrain(3, 409, 0.5);
  terrain.genCantos(60);
  terrain.geraTerreno();

  terrain.print();

  CHECK(true); // Só pra ter certeza que não deu nenhum erro
  
}



// Você precisará criar testes adicionais para cobrir os métodos privados da classe.
// Por exemplo, você pode criar testes para os métodos das etapas Square e Diamond
// Você pode torná-los públicos temporariamente para fins de teste ou usar técnicas como "friend testing".
