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
  Terreno ter(2);
  ter(0, 0) = 3;
  ter(0, 4) = 5;
  ter(4, 0) = 3;
  ter(4, 4) = 5;
  int ponto[2] = {2, 2};
   
  ter.diamond(ponto, 1);

  CHECK(ter(2, 2) == 4);
  
}


// Você precisará criar testes adicionais para cobrir os métodos privados da classe.
// Por exemplo, você pode criar testes para os métodos das etapas Square e Diamond
// Você pode torná-los públicos temporariamente para fins de teste ou usar técnicas como "friend testing".
