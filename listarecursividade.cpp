#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pause_execution() {
    printf("\nPressione ENTER para continuar...\n");
    clear_buffer();
}

// ----------------------------------------------------------------------
// Ex. 01: Dada a função recursiva x(n)
// ----------------------------------------------------------------------

int x_recursiva(int n, int *contagem) {
    (*contagem)++;
    if (n < 0) return 0;
    if (n == 0) return 0;
    if (n == 1) return 1;
    if (n == 2) return 2;
    return x_recursiva(n - 1, contagem) + x_recursiva(n - 2, contagem) + x_recursiva(n - 3, contagem);
}

void exercicio_01() {
    int n = 6;
    int contagem_chamadas = 0;
    
    int resultado_x6 = x_recursiva(n, &contagem_chamadas);
    
    printf("a) O valor de x(%d) eh: %d\n", n, resultado_x6);
    printf("b) O total de chamadas recursivas para calcular x(%d) eh: %d\n", n, contagem_chamadas);
}

// ----------------------------------------------------------------------
// Ex. 03: FATORIAL (Versão Recursiva)
// ----------------------------------------------------------------------

long long fatorial_recursivo(int n) {
    if (n < 0) return -1;
    if (n == 0 || n == 1) {
        return 1;
    }
    return (long long)n * fatorial_recursivo(n - 1);
}

void exercicio_03() {
    int n;
    printf("Calculo de N! (Fatorial) - Versao Recursiva\n");
    printf("Digite o valor de N: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Entrada invalida. Digite um numero inteiro nao-negativo.\n");
        clear_buffer();
        return;
    }
    clear_buffer();

    long long resultado = fatorial_recursivo(n);
    if (resultado == -1) {
        printf("Fatorial nao definido para numeros negativos.\n");
    } else {
        printf("%d! = %lld\n", n, resultado);
    }
}

// ----------------------------------------------------------------------
// Ex. 05: Sequência de invocações de F(5) da função de Fibonacci recursiva
// ----------------------------------------------------------------------

int F_fibonacci_rastreio(int n, int profundidade) {
    for (int i = 0; i < profundidade; i++) {
        printf("  ");
    }
    printf("F(%d)\n", n);

    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    return F_fibonacci_rastreio(n - 1, profundidade + 1) + F_fibonacci_rastreio(n - 2, profundidade + 1);
}

void exercicio_05() {
    printf("Qual a sequencia de invocacoes da funcao provocada por F(5)?\n");
    printf("Sequencia de Invocacoes de F(5):\n");
    F_fibonacci_rastreio(5, 0);
}

// ----------------------------------------------------------------------
// Ex. 07: PRODUTO a*b (Versão Recursiva)
// ----------------------------------------------------------------------

int produto_recursivo(int a, int b) {
    if (a < 0 || b < 0) {
        return 0;
    }
    if (b == 0) {
        return 0;
    }
    return a + produto_recursivo(a, b - 1);
}

void exercicio_07() {
    int a, b;
    printf("Calculo do Produto a*b usando adicao - Versao Recursiva\n");
    printf("Digite o valor de a (nao-negativo): ");
    if (scanf("%d", &a) != 1 || a < 0) {
        printf("Entrada invalida.\n");
        clear_buffer();
        return;
    }
    printf("Digite o valor de b (nao-negativo): ");
    if (scanf("%d", &b) != 1 || b < 0) {
        printf("Entrada invalida.\n");
        clear_buffer();
        return;
    }
    clear_buffer();
    
    int resultado = produto_recursivo(a, b);
    printf("%d * %d = %d\n", a, b, resultado);
}

// ----------------------------------------------------------------------
// Ex. 09: EXPONENCIAÇÃO n^x (Versão Recursiva)
// ----------------------------------------------------------------------

double exponenciacao_recursiva(double n, int x) {
    if (x == 0) {
        return 1.0;
    }
    if (x > 0) {
        return n * exponenciacao_recursiva(n, x - 1);
    } else {
        return 1.0 / exponenciacao_recursiva(n, -x);
    }
}

void exercicio_09() {
    double n;
    int x;
    
    printf("Calculo de n^x - Versao Recursiva\n");
    printf("Digite a base n: ");
    if (scanf("%lf", &n) != 1) {
        printf("Entrada invalida.\n");
        clear_buffer();
        return;
    }
    printf("Digite o expoente x (inteiro): ");
    if (scanf("%d", &x) != 1) {
        printf("Entrada invalida.\n");
        clear_buffer();
        return;
    }
    clear_buffer();
    
    if (n == 0 && x < 0) {
        printf("Indefinido: 0 elevado a potencia negativa.\n");
        return;
    }
    
    double resultado = exponenciacao_recursiva(n, x);
    printf("%.2lf ^ %d = %.4lf\n", n, x, resultado);
}

// ----------------------------------------------------------------------
// Ex. 11: Inverter uma sequência de caracteres (String)
// ----------------------------------------------------------------------

void inverte_sequencia_recursiva(char *str, int inicio, int fim) {
    if (inicio >= fim) {
        return;
    }
    char temp = str[inicio];
    str[inicio] = str[fim];
    str[fim] = temp;
    
    inverte_sequencia_recursiva(str, inicio + 1, fim - 1);
}

void exercicio_11() {
    char sequencia[100];
    
    printf("Inverter uma sequencia de caracteres - Versao Recursiva\n");
    printf("Digite a sequencia de caracteres (max 99): ");
    if (scanf("%99s", sequencia) != 1) {
        printf("Entrada invalida.\n");
        clear_buffer();
        return;
    }
    clear_buffer();
    
    int len = strlen(sequencia);
    inverte_sequencia_recursiva(sequencia, 0, len - 1);
    
    printf("Sequencia invertida: %s\n", sequencia);
}

// ----------------------------------------------------------------------
// Ex. 13: Soma dos quadrados dos N primeiros números positivos
// ----------------------------------------------------------------------

int soma_quadrados_recursiva(int n) {
    if (n <= 0) {
        return 0;
    }
    return n * n + soma_quadrados_recursiva(n - 1);
}

void exercicio_13() {
    int n;
    printf("Soma dos quadrados dos N primeiros numeros positivos - Versao Recursiva\n");
    printf("Digite o valor de N: ");
    if (scanf("%d", &n) != 1 || n < 1) {
        printf("Entrada invalida. Digite um numero inteiro positivo.\n");
        clear_buffer();
        return;
    }
    clear_buffer();
    
    int resultado = soma_quadrados_recursiva(n);
    printf("A soma dos quadrados dos primeiros %d numeros positivos eh: %d\n", n, resultado);
}

// ----------------------------------------------------------------------
// Ex. 15: Máximo Divisor Comum (MDC)
// ----------------------------------------------------------------------

int mdc_recursivo(int x, int y) {
    if (x < 0) x = -x;
    if (y < 0) y = -y;
    
    if (y == 0) {
        return x;
    }
    
    if (x < y) {
        return mdc_recursivo(y, x);
    }
    
    return mdc_recursivo(y, x % y);
}

void exercicio_15() {
    int x, y;
    printf("Maximo Divisor Comum (MDC) - Versao Recursiva (Algoritmo de Euclides)\n");
    printf("Digite o primeiro numero inteiro (x): ");
    if (scanf("%d", &x) != 1) {
        printf("Entrada invalida.\n");
        clear_buffer();
        return;
    }
    printf("Digite o segundo numero inteiro (y): ");
    if (scanf("%d", &y) != 1) {
        printf("Entrada invalida.\n");
        clear_buffer();
        return;
    }
    clear_buffer();
    
    if (x == 0 && y == 0) {
        printf("O MDC de 0 e 0 eh indefinido.\n");
        return;
    }
    
    int resultado = mdc_recursivo(x, y);
    printf("MDC(%d, %d) = %d\n", x, y, resultado);
}

// ----------------------------------------------------------------------
// Ex. 17: Torre de Hanói
// ----------------------------------------------------------------------

void hanoi_recursivo(int n, char origem, char destino, char aux) {
    if (n == 1) {
        printf("Mover disco 1 de %c para %c\n", origem, destino);
        return;
    }
    hanoi_recursivo(n - 1, origem, aux, destino);
    printf("Mover disco %d de %c para %c\n", n, origem, destino);
    hanoi_recursivo(n - 1, aux, destino, origem);
}

void exercicio_17() {
    int n;
    printf("Problema da Torre de Hanoi - Versao Recursiva\n");
    printf("Digite o numero de discos: ");
    if (scanf("%d", &n) != 1 || n < 1) {
        printf("Entrada invalida. Digite um numero inteiro positivo.\n");
        clear_buffer();
        return;
    }
    clear_buffer();
    
    printf("Sequencia de movimentos para %d discos:\n", n);
    hanoi_recursivo(n, 'A', 'C', 'B');
}

// ----------------------------------------------------------------------
// Ex. 19: Soma dos elementos de um vetor por bisseção
// ----------------------------------------------------------------------

int soma_vetor_bissec(int v[], int i, int f) {
    if (i > f) {
        return 0;
    }
    if (i == f) {
        return v[i];
    }
    
    int meio = i + (f - i) / 2;
    return soma_vetor_bissec(v, i, meio) + soma_vetor_bissec(v, meio + 1, f);
}

void exercicio_19() {
    int vetor[] = {10, 20, 3, 7, 50, 15};
    int tamanho = sizeof(vetor) / sizeof(vetor[0]);
    
    printf("Soma dos elementos de um vetor por bissecao (Divisao e Conquista)\n");
    
    printf("Vetor: [");
    for (int i = 0; i < tamanho; i++) {
        printf("%d%s", vetor[i], (i < tamanho - 1 ? ", " : ""));
    }
    printf("]\n");

    int resultado = soma_vetor_bissec(vetor, 0, tamanho - 1);
    printf("A soma dos elementos eh: %d\n", resultado);
}

// ----------------------------------------------------------------------
// Ex. 21: Funções recursivas sobre vetor
// ----------------------------------------------------------------------

int min_vetor_recursivo(int v[], int i, int f) {
    if (i == f) {
        return v[i];
    }
    int meio = i + (f - i) / 2;
    int min_esq = min_vetor_recursivo(v, i, meio);
    int min_dir = min_vetor_recursivo(v, meio + 1, f);
    
    return (min_esq < min_dir) ? min_esq : min_dir;
}

int max_vetor_recursivo(int v[], int i, int f) {
    if (i == f) {
        return v[i];
    }
    int meio = i + (f - i) / 2;
    int max_esq = max_vetor_recursivo(v, i, meio);
    int max_dir = max_vetor_recursivo(v, meio + 1, f);
    
    return (max_esq > max_dir) ? max_esq : max_dir;
}

int soma_vetor_recursivo(int v[], int tamanho) {
    if (tamanho <= 0) {
        return 0;
    }
    return v[tamanho - 1] + soma_vetor_recursivo(v, tamanho - 1);
}

long long produto_vetor_recursivo(int v[], int tamanho) {
    if (tamanho <= 0) {
        return 1;
    }
    return (long long)v[tamanho - 1] * produto_vetor_recursivo(v, tamanho - 1);
}

double media_vetor_recursiva(int v[], int tamanho) {
    if (tamanho <= 0) {
        return 0.0;
    }
    int soma = soma_vetor_recursivo(v, tamanho);
    return (double)soma / tamanho;
}


void exercicio_21() {
    int vetor[] = {5, -1, 10, 2, 8};
    int tamanho = sizeof(vetor) / sizeof(vetor[0]);
    
    printf("Funcoes Recursivas sobre Vetor (Divisao e Conquista / Reducao):\n");
    
    printf("Vetor: [");
    for (int i = 0; i < tamanho; i++) {
        printf("%d%s", vetor[i], (i < tamanho - 1 ? ", " : ""));
    }
    printf("]\n");

    printf("a) Elemento minimo: %d\n", min_vetor_recursivo(vetor, 0, tamanho - 1));
    printf("b) Elemento maximo: %d\n", max_vetor_recursivo(vetor, 0, tamanho - 1));
    printf("c) Soma dos elementos (Reducao): %d\n", soma_vetor_recursivo(vetor, tamanho));
    printf("d) Produto dos elementos (Reducao): %lld\n", produto_vetor_recursivo(vetor, tamanho));
    printf("e) Media dos elementos (Reducao): %.2lf\n", media_vetor_recursiva(vetor, tamanho));
}

// ----------------------------------------------------------------------
// Ex. 23: Número máximo de chamadas recursivas (Busca Binária)
// ----------------------------------------------------------------------

void exercicio_23() {
    printf("Se um vetor contiver n elementos, qual o numero maximo de chamadas\n");
    printf("recursivas feitas pelo algoritmo de busca binaria?\n\n");
    printf("A busca binaria em um vetor de 'n' elementos divide o problema pela metade a cada passo.\n");
    printf("O numero maximo de chamadas (ou passos) e dado pela altura da arvore de recursao.\n");
    printf("Isso corresponde a funcao logaritmica, em base 2.\n");
    printf("Numero maximo de chamadas: aproximadamente $\\log_2(n) + 1$\n");
}

// ----------------------------------------------------------------------
// Ex. 25: Sequências de n dígitos binários sem '11'
// ----------------------------------------------------------------------


int seq_binaria_sem_11_recursiva(int n) {
    if (n == 0) return 1; // 1 sequencia (vazia)
    if (n == 1) return 2; // {0, 1}
    
    return seq_binaria_sem_11_recursiva(n - 1) + seq_binaria_sem_11_recursiva(n - 2);
}

void exercicio_25() {
    int n;
    printf("Numero de sequencias de n digitos binarios que nao contem '11' - Versao Recursiva\n");
    printf("Digite o valor de n: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Entrada invalida. Digite um numero inteiro nao-negativo.\n");
        clear_buffer();
        return;
    }
    clear_buffer();
    
    int resultado = seq_binaria_sem_11_recursiva(n);
    printf("O numero de sequencias validas de %d digitos eh: %d\n", n, resultado);
}

// ----------------------------------------------------------------------
// Ex. 27: Séries S e B
// ----------------------------------------------------------------------

int serie_S_recursiva(int n) {
    if (n == 1) {
        return 10;
    }
    return serie_S_recursiva(n - 1) + 10;
}

int serie_B_recursiva(int n) {
    if (n == 1) {
        return 1;
    }
    return serie_B_recursiva(n - 1) + n * n;
}

void exercicio_27() {
    int n;
    printf("Calculo de um termo qualquer das series S e B - Versao Recursiva\n");
    printf("Digite o valor de n (termo desejado): ");
    if (scanf("%d", &n) != 1 || n < 1) {
        printf("Entrada invalida. Digite um numero inteiro positivo (n >= 1).\n");
        clear_buffer();
        return;
    }
    clear_buffer();
    
    printf("a) S(%d) = %d\n", n, serie_S_recursiva(n));
    printf("b) B(%d) = %d\n", n, serie_B_recursiva(n));
}

// ----------------------------------------------------------------------
// Ex. 29: Converter um número natural para base binária
// ----------------------------------------------------------------------

void to_binary_recursivo(int n) {
    if (n > 1) {
        to_binary_recursivo(n / 2);
    }
    printf("%d", n % 2);
}

void exercicio_29() {
    int n;
    printf("Conversao de numero natural para base binaria - Versao Recursiva\n");
    printf("Digite um numero natural: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Entrada invalida. Digite um numero inteiro nao-negativo.\n");
        clear_buffer();
        return;
    }
    clear_buffer();
    
    if (n == 0) {
        printf("0\n");
    } else {
        printf("Em binario: ");
        to_binary_recursivo(n);
        printf("\n");
    }
}

// ----------------------------------------------------------------------
// Ex. 31: Imprimir todas as permutações dos números de 1 a n
// ----------------------------------------------------------------------

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void permutar_recursivo(int arr[], int inicio, int fim) {
    if (inicio == fim) {
        for (int i = 0; i <= fim; i++) {
            printf("%d", arr[i]);
        }
        printf("\n");
    } else {
        for (int i = inicio; i <= fim; i++) {
            swap(&arr[inicio], &arr[i]);
            permutar_recursivo(arr, inicio + 1, fim);
            swap(&arr[inicio], &arr[i]); // Backtrack
        }
    }
}

void exercicio_31() {
    int n;
    printf("Imprimir todas as permutacoes dos numeros de 1 a n - Versao Recursiva\n");
    printf("Digite o valor de n (1 a 9 para melhor visualizacao): ");
    if (scanf("%d", &n) != 1 || n < 1 || n > 9) {
        printf("Entrada invalida. Digite um numero inteiro entre 1 e 9.\n");
        clear_buffer();
        return;
    }
    clear_buffer();
    
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Erro de alocacao de memoria.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
    
    printf("Permutacoes de 1 a %d:\n", n);
    permutar_recursivo(arr, 0, n - 1);
    
    free(arr);
}

// ----------------------------------------------------------------------
// Ex. 33: Verificar se subvetor é palíndromo (v[i] a v[f])
// ----------------------------------------------------------------------

int is_palindromo_subvetor(int v[], int i, int f) {
    if (i >= f) {
        return 1;
    }
    if (v[i] != v[f]) {
        return 0;
    }
    return is_palindromo_subvetor(v, i + 1, f - 1);
}

void exercicio_33() {
    int vetor[] = {0, 0, 1, 2, 1, 0, 0, 9};
    int n = sizeof(vetor) / sizeof(vetor[0]);
    int i, f;

    printf("Verificar se subvetor v[i] a v[f] eh palindromo - Versao Recursiva\n");
    
    printf("Vetor: [");
    for (int k = 0; k < n; k++) {
        printf("%d%s", vetor[k], (k < n - 1 ? ", " : ""));
    }
    printf("]\n");

    printf("Digite o indice inicial (i) [0 a %d]: ", n - 1);
    if (scanf("%d", &i) != 1 || i < 0 || i >= n) {
        printf("Indice inicial invalido.\n");
        clear_buffer();
        return;
    }
    printf("Digite o indice final (f) [%d a %d]: ", i, n - 1);
    if (scanf("%d", &f) != 1 || f < i || f >= n) {
        printf("Indice final invalido.\n");
        clear_buffer();
        return;
    }
    clear_buffer();

    if (is_palindromo_subvetor(vetor, i, f)) {
        printf("O subvetor v[%d...%d] eh um palindromo.\n", i, f);
    } else {
        printf("O subvetor v[%d...%d] NAO eh um palindromo.\n", i, f);
    }
}

// ----------------------------------------------------------------------
// Ex. 35: Cálculo da Raiz Quadrada (Método de Newton)
// ----------------------------------------------------------------------

double raiz_recursiva(double n, double a, double e) {
    double a2 = a * a;
    if (fabs(a2 - n) < e) {
        return a;
    }
    double proxima_a = (a + n / a) / 2.0;
    printf("Aproximacao intermediaria: %.10lf\n", proxima_a);
    return raiz_recursiva(n, proxima_a, e);
}

void exercicio_35() {
    double n, a, e;
    
    printf("Calculo da Raiz Quadrada por Recursao (Metodo de Newton) - Versao Recursiva\n");
    printf("Digite o numero (N > 0): ");
    if (scanf("%lf", &n) != 1 || n <= 0) {
        printf("Entrada invalida. N deve ser positivo.\n");
        clear_buffer();
        return;
    }
    printf("Digite a aproximacao inicial (A): ");
    if (scanf("%lf", &a) != 1 || a <= 0) {
        printf("Entrada invalida. A deve ser positivo.\n");
        clear_buffer();
        return;
    }
    printf("Digite o erro admissivel (E > 0): ");
    if (scanf("%lf", &e) != 1 || e <= 0) {
        printf("Entrada invalida. E deve ser positivo.\n");
        clear_buffer();
        return;
    }
    clear_buffer();
    
    printf("Aproximacao inicial: %.10lf\n", a);
    double resultado = raiz_recursiva(n, a, e);
    printf("\nRaiz quadrada aproximada de %.2lf (erro < %.10lf): %.10lf\n", n, e, resultado);
}

// ----------------------------------------------------------------------
// Ex. 37: Validar Expressão Infixa (Simplificada)
// ----------------------------------------------------------------------


int is_variable(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

int is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int valida_expressao_recursiva(const char *expr, int i, int *fim_expr) {
    if (expr[i] == '\0') {
        *fim_expr = i;
        return 0; 
    }
    
 
    if (is_variable(expr[i])) {
        *fim_expr = i + 1;
        return 1;
    }
    

    if (expr[i] == '(') {
        
        int fim_a = -1;
        if (!valida_expressao_recursiva(expr, i + 1, &fim_a)) return 0;
        if (fim_a == -1) return 0;
        
       
        if (!is_operator(expr[fim_a])) return 0;
        int op_index = fim_a;
        
        
        int fim_b = -1;
        if (!valida_expressao_recursiva(expr, op_index + 1, &fim_b)) return 0;
        if (fim_b == -1) return 0;
        

        if (expr[fim_b] != ')') return 0;
        
        *fim_expr = fim_b + 1;
        return 1;
    }
    
    return 0;
}

void exercicio_37() {
    char expr[200];
    int fim_expr = -1;
    
    printf("Validar Expressao Aritmetica Infixa - Versao Recursiva\n");
    printf("Regras: variavel=A-Z/0-9; (a+b), (a-b), (a*b), (a/b)\n");
    printf("Digite a expressao (ex: ((A+B)*2)): ");
    if (scanf("%199s", expr) != 1) {
        printf("Entrada invalida.\n");
        clear_buffer();
        return;
    }
    clear_buffer();

    if (valida_expressao_recursiva(expr, 0, &fim_expr) && fim_expr == strlen(expr)) {
        printf("EXPRESSAO VALIDA\n");
    } else {
        printf("EXPRESSAO INVALIDA\n");
    }
}

// ----------------------------------------------------------------------
// Ex. 39: Imprimir os n primeiros números pares
// ----------------------------------------------------------------------

void imprime_pares_recursivo(int n) {
    if (n <= 0) {
        return;
    }
    imprime_pares_recursivo(n - 1);
    printf("%d ", 2 * n);
}

void exercicio_39() {
    int n;
    printf("Imprimir os n primeiros numeros pares - Versao Recursiva\n");
    printf("Digite o valor de n: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Entrada invalida. Digite um numero inteiro nao-negativo.\n");
        clear_buffer();
        return;
    }
    clear_buffer();
    
    if (n == 0) {
        printf("Nenhum par para imprimir.\n");
    } else {
        printf("Os primeiros %d numeros pares sao (2, 4, ...): ", n);
        imprime_pares_recursivo(n);
        printf("\n");
    }
}

// ----------------------------------------------------------------------
// Ex. 41: Subconjuntos de duas letras
// ----------------------------------------------------------------------

void subconjuntos_2_recursivo(const char *conjunto, int tamanho, int inicio, char subconjunto[]) {
    if (subconjunto[0] != '\0' && subconjunto[1] != '\0') {
        printf("[%c, %c], ", subconjunto[0], subconjunto[1]);
        return;
    }

    if (inicio >= tamanho) {
        return;
    }

    if (subconjunto[0] == '\0') {
        subconjunto[0] = conjunto[inicio];
        subconjuntos_2_recursivo(conjunto, tamanho, inicio + 1, subconjunto);
        subconjunto[0] = '\0'; 
    } else {
  
        subconjunto[1] = conjunto[inicio];
        subconjuntos_2_recursivo(conjunto, tamanho, inicio + 1, subconjunto);
        subconjunto[1] = '\0'; 
        

        subconjuntos_2_recursivo(conjunto, tamanho, inicio + 1, subconjunto);
    }
}

void subconjuntos_2_recursivo_simplificada(const char *conjunto, int tamanho, int indice_fixo, int inicio_comb) {
    if (indice_fixo >= tamanho - 1) {
        return;
    }
    
    if (inicio_comb >= tamanho) {

        subconjuntos_2_recursivo_simplificada(conjunto, tamanho, indice_fixo + 1, indice_fixo + 2);
        return;
    }

    printf("[%c, %c], ", conjunto[indice_fixo], conjunto[inicio_comb]);
    

    subconjuntos_2_recursivo_simplificada(conjunto, tamanho, indice_fixo, inicio_comb + 1);
}

void exercicio_41() {
    char conjunto[] = {'A', 'C', 'E', 'K'};
    int tamanho = sizeof(conjunto) / sizeof(conjunto[0]);
    
    printf("Listar todos os subconjuntos de duas letras - Versao Recursiva\n");
    printf("Conjunto: [A, C, E, K]\n");
    
    printf("Subconjuntos:\n");

    subconjuntos_2_recursivo_simplificada(conjunto, tamanho, 0, 1);
    printf("\n");
}

// ----------------------------------------------------------------------
// Ex. 43: Soma e Produto dos elementos de um vetor
// ----------------------------------------------------------------------

void exercicio_43() {
    int vetor[] = {4, 2, 5, 3};
    int tamanho = sizeof(vetor) / sizeof(vetor[0]);

    printf("Soma e Produto dos elementos de um vetor - Funcoes Recursivas\n");
    
    printf("Vetor: [");
    for (int i = 0; i < tamanho; i++) {
        printf("%d%s", vetor[i], (i < tamanho - 1 ? ", " : ""));
    }
    printf("]\n");

    int soma = soma_vetor_recursivo(vetor, tamanho);
    long long produto = produto_vetor_recursivo(vetor, tamanho);

    printf("Soma: %d\n", soma);
    printf("Produto: %lld\n", produto);
}

// ----------------------------------------------------------------------
// Ex. 45: Calcular o valor da série S = 1 + 1/1! + 1/2! + ... + 1/n!
// ----------------------------------------------------------------------

double termo_serie_45_recursivo(int n, double fatorial_anterior) {
    if (n == 0) {
        return 1.0;
    }
    
    if (n == 1) {
        return 1.0 + 1.0; 
    }

    double termo_anterior;
    if (n == 2) { 
        termo_anterior = 1.0 / fatorial_recursivo(n - 1);
    } else {

        return termo_serie_45_recursivo(n - 1, 0.0) + 1.0 / fatorial_recursivo(n);
    }
    
    return termo_serie_45_recursivo(n - 1, 0.0) + 1.0 / fatorial_recursivo(n);
}

double soma_serie_45_recursivo_aux(int n) {
    if (n == 0) {
        return 1.0;
    }
    return soma_serie_45_recursivo_aux(n - 1) + 1.0 / fatorial_recursivo(n);
}

void exercicio_45() {
    int n;
    printf("Calculo da Serie S = 1 + 1/1! + ... + 1/n! - Versao Recursiva\n");
    printf("Digite o valor de n (n > 0, max 12): ");
    if (scanf("%d", &n) != 1 || n < 1 || n > 12) { // 12! cabe em long long
        printf("Entrada invalida. Digite um numero inteiro entre 1 e 12.\n");
        clear_buffer();
        return;
    }
    clear_buffer();
    
    double resultado = soma_serie_45_recursivo_aux(n);
    printf("O valor da serie S para n=%d eh: %.10lf\n", n, resultado);
}

// ----------------------------------------------------------------------
// Ex. 47: Soma da série de valores do intervalo [i,j], com incremento k
// ----------------------------------------------------------------------

int somaSerie_recursiva(int i, int j, int k) {
    if (i > j) {
        return 0;
    }
    return i + somaSerie_recursiva(i + k, j, k);
}

void exercicio_47() {
    int i, j, k;
    printf("Soma da serie de valores do intervalo [i,j], com incremento k - Versao Recursiva\n");
    printf("Digite o valor inicial (i): ");
    if (scanf("%d", &i) != 1) {
        printf("Entrada invalida.\n");
        clear_buffer();
        return;
    }
    printf("Digite o valor final (j): ");
    if (scanf("%d", &j) != 1) {
        printf("Entrada invalida.\n");
        clear_buffer();
        return;
    }
    printf("Digite o incremento (k > 0): ");
    if (scanf("%d", &k) != 1 || k <= 0) {
        printf("Entrada invalida. K deve ser positivo.\n");
        clear_buffer();
        return;
    }
    clear_buffer();
    
    int resultado = somaSerie_recursiva(i, j, k);
    printf("A soma da serie de %d ate %d com incremento %d eh: %d\n", i, j, k, resultado);
}

// ----------------------------------------------------------------------
// Ex. 49: Ler e imprimir números até que seja negativo
// ----------------------------------------------------------------------

void le_imprime_recursivo() {
    int n;
    printf("Digite um numero (negativo para parar): ");
    if (scanf("%d", &n) != 1) {
        printf("Entrada invalida. Parando.\n");
        clear_buffer();
        return;
    }
    
    if (n < 0) {
        printf("Numero negativo detectado. Parando a funcao.\n");
        return;
    }
    
    printf("Lido: %d\n", n);
    le_imprime_recursivo();
}

void exercicio_49() {
    printf("Ler e imprimir numeros ate que seja negativo - Versao Recursiva\n");
    clear_buffer();
    le_imprime_recursivo();
    clear_buffer();
}

// ----------------------------------------------------------------------
// Ex. 51: Problema das N-Rainhas (5x5)
// ----------------------------------------------------------------------

#define N 5
int solucao_rainhas[N]; // solucao_rainhas[i] = coluna da rainha na linha i
int contador_solucoes = 0;

int eh_seguro(int linha, int coluna) {
    for (int i = 0; i < linha; i++) {
        // Verifica a coluna e as diagonais
        if (solucao_rainhas[i] == coluna || 
            solucao_rainhas[i] - i == coluna - linha || 
            solucao_rainhas[i] + i == coluna + linha) {
            return 0;
        }
    }
    return 1;
}

void imprime_solucao() {
    contador_solucoes++;
    printf("Solucao #%d:\n", contador_solucoes);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("| %c ", (solucao_rainhas[i] == j) ? 'R' : ' ');
        }
        printf("|\n");
    }
    printf("\n");
}

void rainhas_recursivo(int linha) {
    if (linha == N) {
        imprime_solucao();
        return;
    }
    
    for (int coluna = 0; coluna < N; coluna++) {
        if (eh_seguro(linha, coluna)) {
            solucao_rainhas[linha] = coluna;
            rainhas_recursivo(linha + 1);
        }
    }
}

void exercicio_51() {
    printf("Problema das N-Rainhas (5 Rainhas em Tabuleiro 5x5) - Versao Recursiva (Backtracking)\n");
    
    contador_solucoes = 0;
    rainhas_recursivo(0);
    
    if (contador_solucoes == 0) {
        printf("Nenhuma solucao encontrada.\n");
    } else {
        printf("Total de solucoes encontradas para o tabuleiro %dx%d: %d\n", N, N, contador_solucoes);
    }
}

// ----------------------------------------------------------------------
// Ex. 53: Função McCarthy f91
// ----------------------------------------------------------------------

int f91_recursivo(int n) {
    if (n >= 101) {
        return n - 10;
    }
    return f91_recursivo(f91_recursivo(n + 11));
}

void exercicio_53() {
    int n;
    printf("Funcao McCarthy f91 - Versao Recursiva\n");
    printf("Se N <= 100, f91(N) = f91(f91(N+11))\n");
    printf("Se N >= 101, f91(N) = N - 10\n");
    printf("Digite o valor de N: ");
    if (scanf("%d", &n) != 1) {
        printf("Entrada invalida.\n");
        clear_buffer();
        return;
    }
    clear_buffer();
    
    int resultado = f91_recursivo(n);
    printf("f91(%d) = %d\n", n, resultado);
    
    if (n <= 100) {
        printf("Para N <= 100, o resultado eh sempre 91.\n");
    }
}

// ----------------------------------------------------------------------
// Ex. 55: Executar fusc(7, 0)
// ----------------------------------------------------------------------

int fusc_recursivo_rastreio(int n, int profundidade) {
    for (int i = 0; i < profundidade; ++i) {
        printf("  ");
    }
    printf("fusc(%d,%d) \n", n, profundidade);
    
    if (n == 1) {
        return 1;
    }
    if (n % 2 == 0) {
        return fusc_recursivo_rastreio(n / 2, profundidade + 1);
    }
    return fusc_recursivo_rastreio((n - 1) / 2, profundidade + 1) + fusc_recursivo_rastreio((n + 1) / 2, profundidade + 1);
}

void exercicio_55() {
    printf("Executar fusc(7,0) e rastrear as chamadas - Funcao 'fusc' do enunciado\n");
    
    printf("Rastreio das chamadas:\n");
    int resultado = fusc_recursivo_rastreio(7, 0);
    printf("\nResultado final de fusc(7,0): %d\n", resultado);
}

// ----------------------------------------------------------------------
// Ex. 56: Valor de f(1,10) e função equivalente (Ex. 56.A: valor de f(1,10))
// ----------------------------------------------------------------------

double f_recursiva(double x, double y) {
    if (x >= y) {
        return (x + y) / 2;
    } else {
        return f_recursiva(f_recursiva(x + 2, y - 1), f_recursiva(x + 1, y - 2));
    }
}

void exercicio_56() {
    printf("Qual e o valor de f(1,10)? - Versao Recursiva da funcao 'f'\n");
    
    double x_inicial = 1.0;
    double y_inicial = 10.0;
    
    printf("Chamada: f(%.0lf, %.0lf)\n", x_inicial, y_inicial);
    double resultado = f_recursiva(x_inicial, y_inicial);
    
    printf("O valor de f(1,10) eh: %.2lf\n", resultado);
}

// ----------------------------------------------------------------------
// MENU PRINCIPAL
// ----------------------------------------------------------------------

void display_menu() {
    printf("\n--------------------------------------------------------------\n");
    printf("| Lista de Exercicios Impares - Recursividade em C           |\n");
    printf("--------------------------------------------------------------\n");
    printf("| 01. Ex. 01: Funcao x(n) e contagem de chamadas             |\n");
    printf("| 03. Ex. 03: Fatorial N! (Recursivo)                        |\n");
    printf("| 05. Ex. 05: Sequencia de invocacoes de F(5) (Fibonacci)    |\n");
    printf("| 07. Ex. 07: Produto a*b (Recursivo)                        |\n");
    printf("| 09. Ex. 09: Exponenciacao n^x (Recursivo)                  |\n");
    printf("| 11. Ex. 11: Inverter String (Recursivo)                    |\n");
    printf("| 13. Ex. 13: Soma dos Quadrados dos N primeiros (Recursivo) |\n");
    printf("| 15. Ex. 15: Maximo Divisor Comum (MDC) (Recursivo)         |\n");
    printf("| 17. Ex. 17: Torre de Hanoi (Recursivo)                     |\n");
    printf("| 19. Ex. 19: Soma de Vetor por Bissecacao (Recursivo)       |\n");
    printf("| 21. Ex. 21: Min/Max/Soma/Prod/Media de Vetor (Recursivo)   |\n");
    printf("| 23. Ex. 23: Maximo de Chamadas da Busca Binaria            |\n");
    printf("| 25. Ex. 25: Seq. Binarias sem '11' (Recursivo)             |\n");
    printf("| 27. Ex. 27: Series S e B (Recursivo)                       |\n");
    printf("| 29. Ex. 29: Natural para Binario (Recursivo)               |\n");
    printf("| 31. Ex. 31: Permutacoes de 1 a N (Recursivo)               |\n");
    printf("| 33. Ex. 33: Subvetor Palindromo (Recursivo)                |\n");
    printf("| 35. Ex. 35: Raiz Quadrada (Metodo de Newton) (Recursivo)   |\n");
    printf("| 37. Ex. 37: Validar Expressao Infixa (Recursivo)           |\n");
    printf("| 39. Ex. 39: Imprimir N Pares (Recursivo)                   |\n");
    printf("| 41. Ex. 41: Subconjuntos de Duas Letras (Recursivo)        |\n");
    printf("| 43. Ex. 43: Soma e Produto do Vetor (Recursivo)            |\n");
    printf("| 45. Ex. 45: Serie S = 1 + 1/n! (Recursivo)                 |\n");
    printf("| 47. Ex. 47: Soma de Serie [i,j] com incremento k (Recursivo)|\n");
    printf("| 49. Ex. 49: Leitura ate Negativo (Recursivo)               |\n");
    printf("| 51. Ex. 51: N-Rainhas (5x5) (Recursivo - Backtracking)     |\n");
    printf("| 53. Ex. 53: Funcao McCarthy f91 (Recursivo)                |\n");
    printf("| 55. Ex. 55: Executar fusc(7,0) (Rastreio)                  |\n");
    printf("| 56. Ex. 56: Valor de f(1,10) (Recursivo)                   |\n");
    printf("--------------------------------------------------------------\n");
    printf("| 0. Sair                                                    |\n");
    printf("--------------------------------------------------------------\n");
    printf("Selecione o numero do exercicio: ");
}

int main() {
    int escolha;
    
    do {
        display_menu();
        if (scanf("%d", &escolha) != 1) {
            clear_buffer();
            escolha = -1;
        }
        clear_buffer();

        printf("\n>>> EXERCICIO %d <<<\n", escolha);

        switch (escolha) {
            case 1: exercicio_01(); break;
            case 3: exercicio_03(); break;
            case 5: exercicio_05(); break;
            case 7: exercicio_07(); break;
            case 9: exercicio_09(); break;
            case 11: exercicio_11(); break;
            case 13: exercicio_13(); break;
            case 15: exercicio_15(); break;
            case 17: exercicio_17(); break;
            case 19: exercicio_19(); break;
            case 21: exercicio_21(); break;
            case 23: exercicio_23(); break;
            case 25: exercicio_25(); break;
            case 27: exercicio_27(); break;
            case 29: exercicio_29(); break;
            case 31: exercicio_31(); break;
            case 33: exercicio_33(); break;
            case 35: exercicio_35(); break;
            case 37: exercicio_37(); break;
            case 39: exercicio_39(); break;
            case 41: exercicio_41(); break;
            case 43: exercicio_43(); break;
            case 45: exercicio_45(); break;
            case 47: exercicio_47(); break;
            case 49: exercicio_49(); break;
            case 51: exercicio_51(); break;
            case 53: exercicio_53(); break;
            case 55: exercicio_55(); break;
            case 56: exercicio_56(); break;
            case 0: printf("Saindo do programa.\n"); break;
            default: printf("Opcao invalida. Tente novamente.\n");
        }

        if (escolha != 0) {
            pause_execution();
        }

    } while (escolha != 0);

    return 0;
}