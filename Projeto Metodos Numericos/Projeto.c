#include <stdio.h>
#include <math.h>

// Função quadrática ax^2 + bx + c
float f(float a, float b, float c, float x) {
    return a * x * x + b * x + c;
}

// Derivada da função quadrática f'(x) = 2ax + b
float derivada_f(float a, float b, float x) {
    return 2 * a * x + b;
}

// Função do método da bisseção
float metodo_bisseccao(float a, float b, float c, float borda_direita, float borda_esquerda, float criterio_parada) {
    
    float x;
    int k = 0;  // Contador de iterações

    while (fabs(borda_direita - borda_esquerda) > criterio_parada) {

        x = (borda_direita + borda_esquerda) / 2;  // Ponto médio

        // Verifica se f(x) é suficientemente pequeno para parar
        if (fabs(f(a, b, c, x)) < criterio_parada) {
            break;  // Encontramos a raiz com a precisão desejada
        }

        // Decide em qual subintervalo a raiz está
        if (f(a, b, c, borda_esquerda) * f(a, b, c, x) < 0) {
            borda_direita = x;  // A raiz está no intervalo esquerdo
        } 
        else {
            borda_esquerda = x;  // A raiz está no intervalo direito
        }

        // Soma 1 ao numero de iterações
        k++;
    }
    printf("- METODO DA BISSECCAO\n");
    printf("Numero de iteracoes pelo metodo da bisseccao: k = %d\n", k);
    return x;
}


// Função da falsa posição
float metodo_falsa_posicao(float a, float b, float c, float borda_direita, float borda_esquerda, float criterio_parada) {
    
    float x;
    float f_esquerda, f_direita, f_x;  // 3 funções
    int k = 0;  // Contador de iterações

    f_esquerda = f(a, b, c, borda_esquerda);
    f_direita = f(a, b, c, borda_direita);

    while (fabs(borda_direita - borda_esquerda) > criterio_parada) {

        // Encontrar o ponto pela fórmula da falsa posição
        x = (borda_esquerda * f_direita - borda_direita * f_esquerda) / (f_direita - f_esquerda);
        f_x = f(a, b, c, x);

        // Verifica se f(x) é suficientemente pequeno para parar
        if (fabs(f_x) < criterio_parada) {
            break;  // Encontramos a raiz com a precisão desejada
        }

        // Decide em qual subintervalo a raiz está e atualiza os valores
        if (f_esquerda * f_x < 0) {
            borda_direita = x;
            f_direita = f_x;
        } else {
            borda_esquerda = x;
            f_esquerda = f_x;
        }

        k++;  // Incrementar o número de iterações
    }
    printf("- METODO DA FALSA POSICAO\n");
    printf("Numero de iteracoes pelo metodo da falsa posicao: k = %d\n", k);
    return x;
}

// Método de Newton-Raphson
float metodo_newton_raphson(float a, float b, float c, float chute_x, float criterio_parada) {
    float x = chute_x;
    int k = 0; // Contador de iterações

    while (fabs(f(a, b, c, x)) > criterio_parada) {
        // Atualiza o valor de x usando a fórmula de Newton-Raphson
        x = x - f(a, b, c, x) / derivada_f(a, b, x);

        k++; // Incrementar o número de iterações
    }
    printf("- METODO DE NEWTON RAPHSON\n");
    printf("Numero de iteracoes pelo metodo de Newton Raphson: k = %d\n", k);
    return x;
}


int main() {
    // Definindo variáveis1
    float a, b, c, criterio_parada = 0.001;
    float borda_direita = 50;
    float borda_esquerda = 0;
    float chute_x;

    printf("=====================================\nDescobrir quao distante a pipa cai.\n=====================================\n\n");

    printf("Criterio de parada: <= %.3f\n\n", criterio_parada);

    // Pedir do usuário os valores a, b, c
    printf("Insira o valor equivalente a quanto a pipa caiu (a): ");
    scanf("%f", &a);
    printf("Insira o valor da velocidade da pipa (b): ");
    scanf("%f", &b);
    printf("Insira o valor equivalente a altura inicial da pipa (c): ");
    scanf("%f", &c);
    printf("Insira o valor inicial de x a ser testado no metodo de Newton Raphson (chute_x): ");
    scanf("%f", &chute_x);

    // Garantir que 'a' seja negativo
    if (a > 0) {
        a = a * (-1);
    }

    // Verificar se há raiz no intervalo fornecido
    if (f(a, b, c, borda_esquerda) * f(a, b, c, borda_direita) > 0) {
        printf("Nao ha raiz nos valores fornecidos. Tente com outros.");
        return 0;
    }

    printf("\n===========\nRESOLUCAO:\n===========\n\n");

    // Chamar o método da bisseção
    float raiz_bisseccao = metodo_bisseccao(a, b, c, borda_direita, borda_esquerda, criterio_parada);
    raiz_bisseccao = fabs(raiz_bisseccao);
    printf("A pipa vai cair a uma distancia aproximada de: %.2f metros.\n", raiz_bisseccao);

    printf("\n");

    // Chamar o metodo da falsa posição
    float raiz_falsa_posicao = metodo_falsa_posicao(a, b, c, borda_direita, borda_esquerda, criterio_parada);
    raiz_falsa_posicao = fabs(raiz_falsa_posicao);
    printf("A pipa vai cair a uma distancia aproximada de: %.2f metros.\n", raiz_falsa_posicao);
    
    printf("\n");

    // Chamar o método de Newton-Raphson
    float raiz_newton_raphson = metodo_newton_raphson(a, b, c, chute_x, criterio_parada);
    raiz_newton_raphson = fabs(raiz_newton_raphson);
    printf("A pipa vai cair a uma distancia aproximada de: %.2f metros.\n", raiz_newton_raphson);

    return 0;
}
