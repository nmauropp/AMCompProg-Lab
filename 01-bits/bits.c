/*
 * Primeiro laboratório de Computadores e Programação
 *
 * A ideia do laboratório é mostrar ao aluno outras formas de fazer as operações
 * que ele já está acostumado a fazer, mas de formas diferentes.
 * Criamos esse desafio com o objetivo de fazê-lo pensar em diferentes formas de se
 * atingir o mesmo resultado. Num cenário real, saber quais instruções são melhor
 * otimizadas pelo compilador pode ajudar muito a perfomance de um programa.
 *
 * O aluno deverá usar apenas um subset de operações de C para realizar o que
 * for pedido no enunciado.
 *
 * Todas as operações permitidas serão especificadas em cada questão.
 * Não está permitido o uso de if-else, for, while, switch, etc.
 *
 * Forma de avaliação:
 *      - Quantas operações o aluno utlizou para realizar a tarefa (se está dentro da quantidade aceitável)
 *      - Explicação do código -- deverá ser o mais claro possível,
 *          imaginando que qualquer pessoa sem conhecimento prévio da
 *          matéria consiga entender o que foi feito, em detalhes.
 *      - As resoluções com menos operações do que a do monitor terão bonificação.
 *
 * Assinatura da dupla:
 *      Aluno 1: Álvaro de Carvalho Alves
 *      DRE 1: 118183211
 *
 *      Aluno 2: Mauro Victor de Araújo Nascimento
 *      DRE 2: 118090256
 *
 *      versão do GCC utilizada: 9.3.0
 *
 *
 */

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#include <stdio.h>
#include <stdint.h>

/* Número não é zero
 *      Permitido:
 *          Operações: ~ & ^ | ! << >>
 *
 *      Número máximo de operações: 3
 *      Monitor: 2
 *
 *      Retorna 1 se x é diferente 0, retorna 0 caso contrário
 *
 *      Exemplo:
 *          naoEhZero(0) -> 0
 *          naoEhZero(7) -> 1
 */
int32_t naoEhZero(int32_t x) {
    /*
      O operador ! transforma tudo que é 0 em 1 e tudo que é diferente de 0 em 0
      Ou seja, quando usamos esse operador uma vez, ele irá retornar 1 somente quando a entrada for 0
      Como queremos que ele retorne 1 quando a entrada não é zero, podemos usar o operador novamente, invertendo o resultado final
    */

    return !!x;
}

/* Número é par ou não
 *      Permitido:
 *          Operações: ~ & ^ | ! << >>
 *
 *      Número máximo de operações: 3
 *      Monitor: 2
 *
 *      Retorna 1 se x é par, retorna 0 caso contrário
 *
 *      Exemplo:
 *          ehPar(0) -> 1
 *          ehPar(2) -> 1
 *          ehPar(7) -> 0
 */
int32_t ehPar(int32_t x) {

	/* Para esta função foi necessário o uso de dois operadores. 

	Primeiramente o "&" operador AND, que visualiza os bits dos valores passados. 
	Quando comparamos dois valores, esse operador retorna os bits que aparecem 
	nestes dois valores comparados. Dessa forma, ao colocarmos "x & 1" nós testamos
	se o "1" está presente no bit menos significativo de "x". 

	Essa operação retornará 1 se x por ímpar, e 0 se x for par. Logo, para seguir
	o comando da questão, precisamos inverter os valores, e por isso utilizamos 
	o operador "!", que inverterá o "1" para "0" e o "0" para "1". Desse modo, 
	teremos a função retornando 1 se x é par, e 0 caso contrário.*/
    return !(x & 1);
}

/*
 * Módulo 8
 *      Permitido:
 *          Operações: ~ & ^ | ! << >>
 *
 *      Número máximo de operações: 3
 *      Monitor: 1
 *
 *      Retorna x % 8
 *
 *      Exemplo:
 *          mod8(1) -> 1
 *          mod8(7) -> 7
 *          mod8(10) -> 2
 */
int32_t mod8(int32_t x) {
    /*
      Para achar o módulo, podemos dividir o número por 8 e pegar o resto da divisão
      Ou seja, escrever x = 8 * quociente + resto
      Se x é positivo, podemos escrever x = 2^31 * d31 + ... + 2^3 * d3 + 2^2 * d2 + 2^1 * d1 + 2^0 * d0
      Onde d31...d0 são os bits do número
      Podemos colocar o 8 em evidência e reescrever x = 8 * (2^28 * d31 + ... + 2^0 * d3) + 2^2 * d2 + 2^1 * d1 + 2^0 * d0
      Ou seja, o resto da divisão por 8 só considerará os últimos 3 bits do número
      Portanto, podemos ignorar todos os outros bits, aplicando uma máscara 0b0...0111 que zerará todos os primeiros bits do número

      Se x for negativo, representado em complemento a dois, podemos escrever como x = -2^31 * d31 + ... + 2^3 * d3 + 2^2 * d2 + 2^1 * d1 + 2^0 * d0
      E de maneira análoga a anterior, conseguir o módulo usando a mesma máscara
    */
	
    return x & 0x7;
}

/* Número positivo ou não
 *      Permitido:
 *          Operações: ~ & ^ | ! << >>
 *
 *      Número máximo de operações: 5
 *      Monitor: 2
 *
 *      Retorna 1 se número é positivo, 0 caso contrário
 *
 *      Exemplo:
 *          ehPositivo(878) -> 1
 *          ehPositivo(-343) -> 0
 */
int32_t ehPositivo(int32_t x) {
	/* Para saber se o número é positivo ou não, podemos utilizar seus bits, uma vez que
	o bit mais significativo de um número binário representa seu sinal. Quando o número for
	positivo, o bit de sinal será "0", e caso contrário, o bit de sinal será "1".

	Portanto, utilizaremos o operador ">>" para fazer um deslocamento à direita em 31 casas,
	para que consigamos obter o bit mais significativo.
	Quando isso acontecer, os números negativos serão retornados como "-1", e os demais números
	serão retornados como "0". 

	Para que consigamos retornar 1 quando o número for positivo e 0 caso contrário, precisamos
	do operador "!", que transformará o "-1" em "0" e o "0" em "1". Assim, conseguimos 
	o resultado desejado.*/
	return !(x>>31);
    
}

/* Negativo sem -
 *      Permitido:
 *          Operações: ~ & ^ | ! << >> +
 *
 *      Número máximo de operações: 5
 *      Monitor: 2
 *
 *      Retorna -x
 *
 *      Exemplo:
 *          negativo(1) -> -1
 *          negativo(42) -> -42
 */
int32_t negativo(int32_t x) {
    /*
      O algoritmo para encontrar o negativo de um número consiste em inverter os bits dele e somar um
      Isso pode ser executado diretamente pelo operador ~ que inverterá todos os bits e depois somando 1 ao resultado

      O algoritmo funciona da seguinte forma:
      O complemento a dois em 32 bits deve ser calculado subtraindo o número de 2^32
      Porém essa operação é mais fácil de ser feita se subtrairmos o número de 2^32 - 1 e depois somarmos 1
      Pois subtrair um número binário de 32 bits de 2^32 - 1 é equivalente a inverter todos os seus bits
    */

    return ~x + 1;
}

/* Implementação do & usando bitwise
 *      Permitido:
 *          Operações: ~ ^ | ! << >>
 *
 *      Número máximo de operações: 7
 *      Monitor: 4
 *
 *      Retorna x & y
 *
 *      Exemplo:
 *          bitwiseAnd(1, 2) -> 0
 *              01 & 10 -> 00
 *          bitwiseAnd(3, 11) -> 3
 *              11 & 1011 -> 0011
 */
int32_t bitwiseAnd(int32_t x, int32_t y) {
	/* Para obter o resultado esperado desta função, é necessário utilizarmos um operador
	que compare valores. Contudo, comparar os valores de "x" e "y" com operadores "|" ou "^" 
	por si só não nos traria o resultado esperado. 

	Desejamos a operação AND "&", e, baseado no Teorema de De Morgan, existe uma relação desta com a operação OR "|", quando complementamos suas variáveis.
	Portanto, faz sentido que usemos a operação OR com o complemento nas variáveis. 

	Enquanto o operador AND repete o valor "1" quando ele está presente nos bits dos dois números comparados, o operador
	OR repete o valor "1" simplesmente por ele estar presente no bit de pelo menos um dos dois números comparados.

	Por isso, iremos complementar os valores recebidos, invertendo-os, utilizando o operador "~"
	em cada um, além de realizar uma operação OR, obtendo: (~x | ~y). Contudo, ainda não será suficiente.

	Adicionado a isso, por se tratar de uma operação contrária, precisaremos complementar o produto
	da operação OR. Dessa maneira, teremos: ~(~x | ~y). Assim obtendo o resultado final.
	*/

    return ~(~x | ~y);
}

/* Igual sem ==
 *      Permitido:
 *          Operações: ~ & ^ | << >> ! +
 *
 *      Número máximo de operações: 3
 *      Monitor: 2
 *
 *      Retorna 1 se x == y, 0 caso contrário
 *
 *      Exemplo:
 *          ehIgual(10, 10) -> 1
 *          ehIgual(16, 8) -> 0
 */
int32_t ehIgual(int32_t x, int32_t y) {
    /*
      A operação xor irá retornar 1 quando os bits são diferentes e zero quando os bits são iguais
      Fazendo essa operação bit a bit, quando os números forem identicos, todos seus bits serão iguais, portanto o resultado será zero
      Se os números são diferentes, o resultado da operação bit a bit uma coisa qualquer diferente de ehZero

      Então usamos o ! para transformar o 0 em 1 e o que for diferente de 0 em 0
      Dessa forma, retornamos 1 quando os números forem iguais e 0 quando diferentes
    */

    return !(x ^ y);
}

/*
 * Multiplicação por 7
 *      Permitido:
 *          Operações: << >> | ! & + -
 *
 *      Número máximo de operações: 4
 *      Monitor: 2
 *
 *      Retorna x multiplicado por 7
 *
 *      Exemplo:
 *          mult7(7) -> 49
 */
int32_t mult7(int32_t x) {
	/* Tendo em vista que desejamos realizar uma multiplicação, podemos utilizar o operador
	"<<" deslocamento à esquerda, uma vez que, se usado no "x", por exemplo, ele pode
	multiplicar o número por múltiplos de 2 (2, 4, 8, 16, 32, 64...), uma vez que esse operador
	move o número para um valor mais significativo.

	Exemplificando: se usarmos x<<1 , ele moverá o "x" em 1 casa à esquerda. É importante
	lembrar que, assim como quando convertemos de binário para decimais, 
	cada casa é considerada, com o "2" elevado ao número correspondente. 
	Então, sabendo que "2 elevado a 1" é igual a 2, teremos o valor x multiplicado por 2.

	No entanto, como dito anteriormente, o operador "<<" permite que multipliquemos por
	múltiplos de 2. Como desejamos multiplicar por 7, não seria possível executar a função
	somente com a operação "<<", uma vez que não conseguiríamos o 7 com o incremento do expoente de 2 (2, 4, 8, 16...).
	Devido a isso, alcançamos o 7 de outra maneira. 

	Sabendo que uma multiplicação por 7 pode ser compreendida como uma soma do mesmo número
	7 vezes, podemos multiplicar o "x" por um número maior, e subtrair o valor que ultrapassa nosso objetivo. 
	Exemplo: Se queremos obter o resultado da multiplicação de "7 por 2",
	podemos multiplicar "8 por 2", e teremos como resultado 16. Ou seja, 16 é igual à soma de oito números com valor 2.
	Sendo assim, se tirarmos um número de valor 2 desse resultado, obteremos a soma de 7 números com valor 2. 
	16 - 2 = 14 (resultado da multiplicação de 7 por 2).

	Assim, uma boa opção é utilizar (x<<3)-x, pois "2 elevado a 3" é igual a 8, o que fará nosso
	número ser multiplicado por 8, e subtrair x, que fará com que encontremos nossa multiplicação por 7.
	*/
    return (x<<3)-x;
}

/*
 * Bit na posição p do inteiro x
 *      Permitido:
 *          Operações bitwise: << >> | & + -
 *
 *      Número máximo de operações: 6
 *      Monitor: 2
 *
 *      Retorna o valor do bit na posição p no inteiro x
 *      Valor de retorno pode ser apenas 0 ou 1
 *
 *      p será um valor entre 0 e 31
 *
 *      Exemplo:
 *          23 em binário: 0   0 ... 0 1 0 1 1 1
 *               posições: 31 30 ... 5 4 3 2 1 0
 *
 *          bitEmP(23, 31) -> 0
 *          bitEmP(23, 5) -> 0
 *          bitEmP(23, 4) -> 1
 *          bitEmP(23, 3) -> 0
 *          bitEmP(23, 2) -> 1
 *          bitEmP(23, 1) -> 1
 *          bitEmP(23, 0) -> 1
 *
 */
int32_t bitEmP(int32_t x, uint8_t p) {
    /*
      Para executar essa operação, podemos deslocar todos os bits do número p vezes para a direita
      Isso fara com que o bit na posição p seja colocado na posição 0, se tornando o bit menos significativo

      Daí podemos aplicar uma máscara para ignorar todos os bits que não são esse menos significativo
    */
    return (x >> p) & 0x1;
}

/*
 * Byte na posição p do inteiro x
 *      Permitido:
 *          Operações: << >> | ! &
 *
 *      Número máximo de operações: 6
 *      Monitor: 3
 *
 *      Retorna o valor do bit na posição p no inteiro x
 *      Valor de retorno pode ser entre 0 e 0xFF
 *
 *      p será um valor entre 0 e 3
 *      0 retorna LSB
 *      3 retorna MSB
 *
 *      Exemplo:
 *          byteEmP(0x12345678, 0) -> 0x78
 *          byteEmP(0x12345678, 1) -> 0x56
 *          byteEmP(0x12345678, 2) -> 0x34
 *          byteEmP(0x12345678, 3) -> 0x12
 */
int32_t byteEmP(int32_t x, uint8_t p) {
	/*	Para esta função, considerando que separamos o número "x" em 4 partes (0, 1, 2 e 3),
	é importante compreendermos que, se tratando de um byte, cada byte possui 8 bits. 

	Dessa maneira, para que nosso número "p" se desloque entre os bytes, ele precisa andar
	8 bits a cada byte que desejamos. Ou seja, se queremos p=2, precisamos andar 2 * 8 bits = 16 bits.

	Para que esse caminho de 8 em 8 bits ocorra, precisamos multiplicar "p" por um valor que nos permita
	andar esse número de bits. No caso, se utilizarmos "p<<3", nosso "p" andará 3 casas para a esquerda,
	sendo multiplicado por "2 elevado a 3" = 8. Assim, nosso "p" andará por 8 bits seguindo a multiplicação
	que citamos no parágrafo acima.

	Visto que já conseguimos o valor necessário para o deslocamento, agora precisamos aplicá-lo ao número "x"
	que receberemos. Uma maneira de fazê-lo é com "x>>(p<<3)", pois com o operador ">>" o x será movido à direita,
	levando seus bits mais significativos para este lado. Dessa maneira conseguiremos manipular nossos bytes.

	Por fim, como é necessário que o valor de retorno da função esteja entre 0 e 0xFF, é necessário que
	filtremos os bytes, obtendo somente o que é do nosso interesse: o byte indicado pelo "p". Para isso,
	podemos utilizar a função "&" com um número de dois dígitos, para pegarmos somente os dois números que
	desejamos. Dessa maneira, faremos: "x>>(p<<3) & 0xFF", obtendo o resultado desejado pela função.
	*/
	return x>>(p<<3) & 0xFF;
}

/*
 * Negação lógica sem !
 *      Permitido:
 *          Operações: << >> | & +
 *
 *      Número máximo de operações: 15
 *      Monitor: 5
 *
 *      Retorna 1 se x == 0, retorna 0 caso contrário
 *
 *      Exemplo:
 *          negacaoLogica(0) -> 1
 *          negacaoLogica(37) -> 0
 *
 */
int32_t negacaoLogica(int32_t x) {
    /*
      Para negar o número lógicamente precisamos retornar 0 quando ele for diferente de 0 e 1 quando for igual a zero

      Para isso, podemos aproveitar do operador de deslocamento a direita, que preenche todos os bits deslocados com 1 se o número for negativo
      Com isso, para números negativos, iremos preencher todos os bits dele com 1, se deslocarmos 31 vezes

      Caso o número não seja negativo, podemos calcular o complemento a dois dele, o tornando negativo

      Se o número for 0, tanto ele quanto o complemento a 2 dele será 0

      Dessa forma, para todo número que não seja 0, quando fizermos (x | (~x + 1)) o bit mais significativo prevalecerá como 1
      Pois entre x e (~x + 1) algum será negativo
      Se o número for 0, o bit mais significativo prevalecerá sendo 0

      Então podemos deslocar esse bit mais significativo até o menos significativo usando a operação >> 31

      Até esse momento, se x = 0, o resultado parcial será 0. Se x != 0, o resultado parcial será - 2^31

      Para chegar ao resultado final, podemos somar 1. Então, se o resultado parcial for zero, o resultado final será 1
      Já se o resultado parcial for -2^31, forçaremos um overflow e o resultado final será 0
    */

    return ((x | (~x + 1)) >> 31) + 1;
}

void teste(int32_t saida, int32_t esperado) {
    static uint8_t test_number = 0;
    test_number++;
    if(saida == esperado)
        printf(ANSI_COLOR_GREEN "PASSOU! Saída: %-10d\t Esperado: %-10d\n" ANSI_COLOR_RESET,
            saida, esperado);

    else
        printf(ANSI_COLOR_RED "%d: FALHOU! Saída: %-10d\t Esperado: %-10d\n" ANSI_COLOR_RESET,
            test_number, saida, esperado);
}

int main() {
    puts(ANSI_COLOR_BLUE "Primeiro lab - bits" ANSI_COLOR_RESET);
    puts("");

    puts("Teste: ehZero");
    teste(naoEhZero(0), 0);
    teste(naoEhZero(1), 1);
    teste(naoEhZero(1024), 1);
    teste(naoEhZero(-1), 1);
    teste(naoEhZero(-2), 1);
    teste(naoEhZero(-2147483648), 1);
    teste(naoEhZero(2147483647), 1);
    puts("");

    puts("Teste: ehPar");
    teste(ehPar(2), 1);
    teste(ehPar(1), 0);
    teste(ehPar(3), 0);
    teste(ehPar(13), 0);
    teste(ehPar(100), 1);
    teste(ehPar(125), 0);
    teste(ehPar(1024), 1);
    teste(ehPar(2019), 0);
    teste(ehPar(2020), 1);
    teste(ehPar(-1), 0);
    teste(ehPar(-27), 0);
    teste(ehPar(-1073741825), 0);
    teste(ehPar(1073741824), 1);
    teste(ehPar(2147483647), 0);
    teste(ehPar(-2147483648), 1);
    teste(ehPar(0), 1);
    puts("");

    puts("Teste: mod8");
    teste(mod8(0), 0);
    teste(mod8(4), 4);
    teste(mod8(7), 7);
    teste(mod8(8), 0);
    teste(mod8(-1), 7);
    teste(mod8(-8), 0);
    teste(mod8(2147483647), 7);
    teste(mod8(-2147483648), 0);
    puts("");

    puts("Teste: ehPositivo");
    teste(ehPositivo(-1), 0);
    teste(ehPositivo(1), 1);
    teste(ehPositivo(2037), 1);
    teste(ehPositivo(-2037), 0);
    teste(ehPositivo(-2147483648), 0);
    teste(ehPositivo(-2147483648/2), 0);
    teste(ehPositivo(2147483647), 1);
    puts("");

    puts("Teste: negativo");
    teste(negativo(0), 0);
    teste(negativo(1), -1);
    teste(negativo(-1), 1);
    teste(negativo(2147483647), -2147483647);
    teste(negativo(-2147483647), 2147483647);
    teste(negativo(-2147483648), 2147483648);
    puts("");

    puts("Teste: bitwiseAnd");
    teste(bitwiseAnd(1, 3), 1);
    teste(bitwiseAnd(-1, 0), 0);
    teste(bitwiseAnd(-1, 0x7FFFFFFF), 0x7FFFFFFF);
    teste(bitwiseAnd(0b0100, 0b1100), 0b0100);
    puts("");

    puts("Teste: ehIgual");
    teste(ehIgual(1,1), 1);
    teste(ehIgual(1,0), 0);
    teste(ehIgual(0,1), 0);
    teste(ehIgual(-1,1), 0);
    teste(ehIgual(-1,-1), 1);
    teste(ehIgual(2147483647,-1), 0);
    teste(ehIgual(2147483647,-2147483647), 0);
    teste(ehIgual(2147483647,-2147483648), 0);
    teste(ehIgual(2147483647,-2147483648), 0);
    puts("");

    puts("Teste: mult7");
    teste(mult7(1), 7);
    teste(mult7(7), 49);
    teste(mult7(3), 21);
    teste(mult7(-1), -7);
    teste(mult7(-306783378), -2147483646);
    teste(mult7(306783378), 2147483646);
    puts("");

    puts("Teste: bitEmP");
    teste(bitEmP(1, 0), 1);   //    b01 => retorna 1
    teste(bitEmP(1, 1), 0);   //    b01 => retorna 0
    teste(bitEmP(2, 0), 0);   //    b10 => retorna 0
    teste(bitEmP(2, 1), 1);   //    b10 => retorna 1
    teste(bitEmP(9, 2), 0);   //  b1001 => retorna 0
    teste(bitEmP(-4194305, 22), 0);
    teste(bitEmP(9, 3), 1);
    teste(bitEmP(16, 3), 0);
    teste(bitEmP(0x1 << 5, 4), 0);
    teste(bitEmP(0x1 << 31, 31), 1);
    teste(bitEmP(-1073741825, 30), 0);
    teste(bitEmP(-1073741825, 31), 1);
    puts("");

    puts("Teste: byteEmP");
    teste(byteEmP(0x766B, 1), 0x76);
    teste(byteEmP(0x766B, 0), 0x6B);
    teste(byteEmP(0x8420, 0), 0x20);
    teste(byteEmP(0x12345678, 3), 0x12);   // retorna 0x12
    teste(byteEmP(0x12345678, 2), 0x34);   // retorna 0x34
    teste(byteEmP(0x12345678, 1), 0x56);   // retorna 0x56
    teste(byteEmP(0x12345678, 0), 0x78);   // retorna 0x78
    teste(byteEmP(0x321, 1), 0x03);        // retorna 0x03
    teste(byteEmP(0x321, 0), 0x21);        // retorna 0x21
    puts("");

    puts("Teste: negacaoLogica");
    teste(negacaoLogica(0), 1);
    teste(negacaoLogica(1), 0);
    teste(negacaoLogica(-1), 0);
    teste(negacaoLogica(64), 0);
    teste(negacaoLogica(-64), 0);
    teste(negacaoLogica(2147483647), 0);
    teste(negacaoLogica(-2147483648), 0);
    puts("");
}
