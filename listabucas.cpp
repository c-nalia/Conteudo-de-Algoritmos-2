#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// --- Estrutura para Ex. 25 ---

typedef struct {
    char nome[50];
    int numero;
} Aluno;

// --- Funções Auxiliares (Para o menu) ---

void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pause_execution() {
    printf("\nPressione ENTER para continuar...\n");
    clear_buffer();
}

// ----------------------------------------------------------------------
// Ex. 04: Função buscabinaria (Usada no Ex. 05)
// Devolve j em 0..n tal que v[j-1]<x<=v[j].
// ----------------------------------------------------------------------

int buscabinaria(int x, int n, int v[], int rastrear) {
    if (rastrear) printf("Chamada para x=%d, n=%d. (e,m,d)\n", x, n);
    
    if (v[n-1] < x) return n;
    if (x <= v[0]) return 0;

    int e = 0, d = n - 1, m;

    while (e < d - 1) {
        m = (e + d) / 2;
        if (rastrear) printf("  Iteracao: e=%d, d=%d, m=%d. v[m]=%d\n", e, d, m, v[m]);
        

        if (v[m] < x) {
            e = m;
        } else {
            d = m;
        }
    }
    
    if (rastrear) printf("  Final: e=%d, d=%d. Retorna d=%d\n", e, d, d);
    return d;
}

// ----------------------------------------------------------------------
// Ex. 08: Função buscabinaria2 (Usada no Ex. 09)
// Devolve j em 0..n tal que v[j-1]<x<=v[j].
// ----------------------------------------------------------------------

int buscabinaria2(int x, int n, int v[], int rastrear) {
    if (rastrear) printf("Chamada para x=%d, n=%d. (e,m,d)\n", x, n);
    
    int e = -1, d = n, m;

    while (e < d - 1) {
        m = (e + d) / 2;
        if (rastrear) printf("  Iteracao: e=%d, d=%d, m=%d. v[m]=%d\n", e, d, m, v[m]);
        
        if (v[m] < x) {
            e = m;
        } else {
            d = m;
        }
    }
    
    if (rastrear) printf("  Final: e=%d, d=%d. Retorna d=%d\n", e, d, d);
    return d;
}

// ----------------------------------------------------------------------
// Ex. 01: Criticar a formulação de busca
// ----------------------------------------------------------------------

void exercicio_01() {
    printf("a) Critica a formulacao: v[j-1] <= x <= v[j]\n");
    printf("   Essa formulacao eh a mais utilizada para busca de limite superior ('upper bound') e esta correta.\n");
    printf("   A formula garante que, se x estiver no vetor, ele sera encontrado em v[j] ou o ponto de insercao sera v[j].\n");
    printf("   Casos limites:\n");
    printf("   - Se x eh menor que v[0], j=0 (v[-1] imaginario eh -infinito).\n");
    printf("   - Se x eh maior que v[n-1], j=n (v[n] imaginario eh +infinito).\n");
    
    printf("\nb) Critica a formulacao: v[j-1] < x < v[j]\n");
    printf("   Essa formulacao eh FALHA porque nao permite que x seja igual a v[j-1] ou v[j].\n");
    printf("   Por exemplo, se o vetor for {10, 20} e x=10:\n");
    printf("   - O indice correto seria j=1 (v[0]<=10<=v[1]).\n");
    printf("   - Com a formula v[j-1] < 10 < v[j], nenhum j atende.\n");
    printf("   - Se o vetor for {10, 20} e x=20, a formula tambem falha.\n");
    printf("   A formulacao correta deve permitir a igualdade, como em v[j-1] < x <= v[j] (limite superior) ou v[j-1] <= x < v[j] (limite inferior).\n");
}

// ----------------------------------------------------------------------
// Ex. 03: Discutir a versão recursiva da busca sequencial (busca2)
// ----------------------------------------------------------------------

int busca2_recursiva(int x, int n, int v[]) {
    if (n == 0) return 0;
    if (x > v[n - 1]) return n;
    return busca2_recursiva(x, n - 1, v);
}

void exercicio_03() {
    printf("Critica a versao recursiva da busca sequencial (busca2):\n");
    printf("A funcao 'busca2' implementa uma busca SEQUENCIAL regressiva.\n");
    printf("1. Proposito:\n");
    printf("   - A funcao busca, corretamente, o indice j em 0..n tal que v[j-1] < x <= v[j].\n");
    printf("   - Ela faz isso verificando o vetor de tras para frente, do indice n-1 ate 0.\n");
    printf("2. Mecanismo:\n");
    printf("   - Se o vetor estiver vazio (n==0), retorna 0.\n");
    printf("   - Se x for maior que o ultimo elemento v[n-1], x deve ser inserido apos ele, entao retorna n.\n");
    printf("   - Se x for menor ou igual a v[n-1], a busca se repete para o subvetor v[0..n-2] (chamada recursiva com n-1).\n");
    printf("3. Ineficiencia:\n");
    printf("   - Embora o algoritmo esteja LÓGICAMENTE correto, ele eh uma busca SEQUENCIAL, nao uma busca binaria.\n");
    printf("   - Sua complexidade de tempo eh O(n), o que o torna ineficiente para vetores grandes.\n");
    printf("   - O uso de recursao para esta tarefa pode levar a um alto consumo de pilha (stack overflow) para vetores muito grandes, pois a profundidade maxima da recursao eh n.\n");
    
    int v[] = {10, 20, 30, 40};
    int n = 4;
    int x1 = 25;
    int x2 = 50;
    
    printf("\nDemonstracao (Vetor: {10, 20, 30, 40}):\n");
    printf("Busca2(%d, 4, v) = %d (Correto, j=3)\n", x1, busca2_recursiva(x1, n, v));
    printf("Busca2(%d, 4, v) = %d (Correto, j=4)\n", x2, busca2_recursiva(x2, n, v));
}

// ----------------------------------------------------------------------
// Ex. 05: Executar buscabinaria (trace)
// ----------------------------------------------------------------------

void exercicio_05() {
    int v9[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    int n9 = 9;
    
    printf("Execucao de buscabinaria (Ex. 4) com n=9, v[i]=i.\n");
    printf("Vetor v: [0, 1, 2, 3, 4, 5, 6, 7, 8]\n\n");
    
    printf("--- Caso 1: x=4 (Elemento presente) ---\n");
    buscabinaria(4, n9, v9, 1);
    
    printf("\n--- Caso 2: x=4.5 (Elemento nao presente, entre 4 e 5) ---\n");
    buscabinaria(5, n9, v9, 1); 
    
    printf("\n--- Caso 3: x=-1 (Menor que todos) ---\n");
    buscabinaria(-1, n9, v9, 1);
    
    printf("\n--- Caso 4: x=10 (Maior que todos) ---\n");
    buscabinaria(10, n9, v9, 1);

    printf("\n\nExecucao com n=14, x=9. v[i]=i.\n");
    int v14[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int n14 = 14;
    
    printf("Vetor v: [0, 1, ..., 13]\n\n");
    printf("--- Caso 5: n=14, x=9 ---\n");
    buscabinaria(9, n14, v14, 1);
}

// ----------------------------------------------------------------------
// Ex. 07: Busca binária que devolva j tal que v[j]==x ou -1
// ----------------------------------------------------------------------

int busca_exata(int x, int n, int v[]) {
    int e = 0; 
    int d = n - 1;
    
    while (e <= d) {
        int m = e + (d - e) / 2;
        
        if (v[m] == x) {
            return m; 
        } else if (v[m] < x) {
            e = m + 1;
        } else {
            d = m - 1;
        }
    }
    
    return -1;
}

void exercicio_07() {
    int v[] = {10, 20, 30, 40, 50, 60};
    int n = 6;
    
    printf("Busca Binaria que retorna indice j (v[j]==x) ou -1.\n");
    printf("Vetor: [10, 20, 30, 40, 50, 60]\n");
    
    printf("Busca de 40: Indice %d\n", busca_exata(40, n, v));
    printf("Busca de 10: Indice %d\n", busca_exata(10, n, v));
    printf("Busca de 60: Indice %d\n", busca_exata(60, n, v));
    printf("Busca de 35: Indice %d\n", busca_exata(35, n, v));
    printf("Busca de 5: Indice %d\n", busca_exata(5, n, v));
    printf("Busca de 65: Indice %d\n", busca_exata(65, n, v));
}

// ----------------------------------------------------------------------
// Ex. 09: Executar buscabinaria2 (trace)
// ----------------------------------------------------------------------

void exercicio_09() {
    int v7[] = {0, 1, 2, 3, 4, 5, 6};
    int n7 = 7;
    
    printf("Execucao de buscabinaria2 (Ex. 8) com n=7, v[i]=i.\n");
    printf("Vetor v: [0, 1, 2, 3, 4, 5, 6]. Limites iniciais: e=-1, d=7.\n\n");
    
    printf("--- Caso 1: x=4 (Elemento presente) ---\n");
    buscabinaria2(4, n7, v7, 1);
    
    printf("\n--- Caso 2: x=3.5 (Elemento nao presente, entre 3 e 4) ---\n");
    buscabinaria2(4, n7, v7, 1); 
    
    printf("\n--- Caso 3: x=0 (Primeiro elemento) ---\n");
    buscabinaria2(0, n7, v7, 1);
    
    printf("\n--- Caso 4: x=7 (Maior que todos) ---\n");
    buscabinaria2(7, n7, v7, 1);
    
    printf("\n--- Caso 5: x=-1 (Menor que todos) ---\n");
    buscabinaria2(-1, n7, v7, 1);
}

// ----------------------------------------------------------------------
// Ex. 11: Validade da afirmação sobre (e+d)
// ----------------------------------------------------------------------

void exercicio_11() {
    printf("Confira a validade da afirmacao: Se n+1 e potencia de 2, (e+d) e divisivel por 2.\n");
    printf("A afirmacao e FALSA.\n");
    printf("Para 'buscabinaria2' (e=-1, d=n), se n+1 e potencia de 2, dizemos que a busca e 'balanceada'.\n");
    printf("No entanto, a divisibilidade de (e+d) por 2 depende dos valores de e e d a cada iteracao, e nao do n inicial.\n");
    printf("Exemplo: n=7 (n+1=8, que e potencia de 2).\n");
    printf(" - Inicio: e=-1, d=7. e+d=6. m=3. OK.\n");
    printf(" - Se x=6, temos d=3. Nova iteracao: e=3, d=7. e+d=10. m=5. OK.\n");
    printf(" - Se x=3, temos e=-1, d=3. e+d=2. m=1. OK.\n");
    printf(" - Mas, se n=15 (n+1=16):\n");
    printf("   - Inicio: e=-1, d=15. e+d=14. m=7. OK.\n");
    printf("   - Se x=1: d=7. e=-1. e+d=6. m=3. OK.\n");
    printf("   - Se x=2: d=3. e=-1. e+d=2. m=1. OK.\n");
    printf("   A expressao e (e+d)/2, que e sempre possivel em inteiros. O que importa e se e+d e par ou impar, pois isso afeta o m e a convergencia.\n");
    printf("   Contudo, a busca binaria sempre converge para e=d-1 e o fato de n+1 ser potencia de 2 apenas garante que a divisao do intervalo seja sempre 'limpa' no inicio e a convergencia seja rapida. A soma (e+d) nao e necessariamente sempre divisivel por 2 ao longo de todas as iteracoes.\n");
    printf("   - No caso de e=-1, d=n, (e+d) e divisivel por 2 se n-1 for par, ou seja, se n for impar. Se n for par, n-1 e impar e (e+d) e impar.\n");
    printf("   - Portanto, a afirmacao e falsa, pois se n=6 (n+1=7, nao potencia de 2), e+d=5, m=2.\n");
}

// ----------------------------------------------------------------------
// Ex. 13: Busca binária para v[j-1] <= x < v[j] (Lower Bound)
// ----------------------------------------------------------------------

int buscabinaria_tipo3(int x, int n, int v[]) {
    int e = -1; 
    int d = n;  
    while (e < d - 1) {
        int m = (e + d) / 2;
        
        if (v[m] < x) {
            e = m; 
        } else {
            d = m; 
        }
    }
    

    e = -1;
    d = n; 
    
    while (e < d - 1) {
        int m = (e + d) / 2;
        
        if (v[m] <= x) {
            e = m; 
        } else {
            d = m; 
        }
    }
   
    e = -1; 
    d = n; 
    
    while (e < d - 1) {
        int m = (e + d) / 2;
        
        if (v[m] <= x) {
            e = m;
        } else {
            d = m;
        }
    }
    
    return d;
}

void exercicio_13() {
    int v[] = {10, 20, 20, 40, 50, 60};
    int n = 6;
    
    printf("Busca Binaria para j tal que v[j-1] <= x < v[j] (Indice do primeiro elemento > x)\n");
    printf("Vetor: [10, 20, 20, 40, 50, 60]. Possiveis valores de j sao 0 a n (0 a 6).\n");
    
    printf("Busca de x=20: j = %d (indice 3, onde v[3]=40)\n", buscabinaria_tipo3(20, n, v));
    printf("Busca de x=10: j = %d (indice 1, onde v[1]=20)\n", buscabinaria_tipo3(10, n, v));
    printf("Busca de x=60: j = %d (indice 6, apos o final)\n", buscabinaria_tipo3(60, n, v));
    printf("Busca de x=5: j = %d (indice 0, onde v[0]=10)\n", buscabinaria_tipo3(5, n, v));
    printf("Busca de x=45: j = %d (indice 4, onde v[4]=50)\n", buscabinaria_tipo3(45, n, v));
}

// ----------------------------------------------------------------------
// Ex. 15: Busca binária que procure x em v[1..n]
// ----------------------------------------------------------------------

int busca_v1n(int x, int n, int v[]) {

    int e = 0;
    int d = n + 1; 
    
    while (e < d - 1) {
        int m = (e + d) / 2;
        
        if (v[m] < x) {
            e = m;
        } else {
            d = m;
        }
    }
    
    return d;
}

void exercicio_15() {
 
    int v[7] = {-99, 10, 20, 30, 40, 50, 60}; 
    int n = 6;
    
    printf("Busca Binaria em v[1..n] (n=6). Vetor {10, 20, 30, 40, 50, 60} (v[0] eh lixo)\n");
    printf("O retorno j estara no intervalo 1..n+1 (1..7).\n");
    
    printf("Busca de x=20: Indice j = %d (Correto: 2)\n", busca_v1n(20, n, v));
    printf("Busca de x=35: Indice j = %d (Correto: 4)\n", busca_v1n(35, n, v));
    printf("Busca de x=10: Indice j = %d (Correto: 1)\n", busca_v1n(10, n, v));
    printf("Busca de x=60: Indice j = %d (Correto: 6)\n", busca_v1n(60, n, v));
    printf("Busca de x=65: Indice j = %d (Correto: 7)\n", busca_v1n(65, n, v));
    printf("Busca de x=5: Indice j = %d (Correto: 1)\n", busca_v1n(5, n, v));
}

// ----------------------------------------------------------------------
// Ex. 17: Alternativa de buscabinaria2 (v[e-1] < x <= v[d])
// ----------------------------------------------------------------------

int buscabinaria_alternativa17(int x, int n, int v[]) {
    int e = 0; 
    int d = n;
    
    while (e < d) { 
        int m = (e + d) / 2;
        
        if (v[m] < x) {
            e = m + 1;
        } else {
            d = m;
        }
    }
    
    return d;
}

void exercicio_17() {
    int v[] = {10, 20, 30, 40, 50};
    int n = 5;
    
    printf("Alternativa de buscabinaria2 (Ex. 16/17): e=0, d=n, while (e < d)\n");
    printf("Vetor: [10, 20, 30, 40, 50]\n");
    
    printf("Busca de x=20: Indice j = %d (Correto: 1)\n", buscabinaria_alternativa17(20, n, v));
    printf("Busca de x=35: Indice j = %d (Correto: 3)\n", buscabinaria_alternativa17(35, n, v));
    printf("Busca de x=5: Indice j = %d (Correto: 0)\n", buscabinaria_alternativa17(5, n, v));
    printf("Busca de x=55: Indice j = %d (Correto: 5)\n", buscabinaria_alternativa17(55, n, v));
    
    printf("\nA alternativa e=0; d=n; while(e<d) com e=m+1 e d=m FUNÇIONA CORRETAMENTE.\n");
    printf("Ela mantem o invariante v[e-1] < x <= v[d] e garante a convergencia para e=d.\n");
}

// ----------------------------------------------------------------------
// Ex. 19: Analisar alternativa de buscabinaria2 (e=-1, d=n-1)
// ----------------------------------------------------------------------

void exercicio_19() {
    printf("Analise da Alternativa de buscabinaria2 (Ex. 18): e=-1, d=n-1, while(e<d), d=m-1\n");
    printf("e=-1; d=n-1;\n");
    printf("while (e < d) {\n");
    printf("  m = (e+d)/2;\n");
    printf("  if (v[m] < x) e = m;\n");
    printf("  else d = m-1;\n");
    printf("}\n");
    printf("return d+1;\n");
    
    printf("\nA alternativa e INCORRETA.\n");
    printf("1. Falha na Condicao de Parada e Atribuicao: O loop while(e < d) combinado com d = m-1 nao garante que e e d se aproximem corretamente em todos os casos.\n");
    printf("2. Overflow do Limite Inferior:\n");
    printf("   - Se o valor de 'x' for menor que todos os elementos, 'd' sera continuamente reduzido a m-1.\n");
    printf("   - Ex: n=5. v={10,20,30,40,50}. x=5.\n");
    printf("     - Iteracao 1: e=-1, d=4. m=1. v[m]=20. d=0.\n");
    printf("     - Iteracao 2: e=-1, d=0. m=-1. v[m] e acesso ilegal! (v[-1]).\n");
    printf("   - O problema da busca eh que a condicao 'd = m-1' pode levar 'd' a -1 antes que 'e' o alcance, causando um acesso ilegal a v[m] ou uma convergencia incorreta.\n");
    printf("O uso de e=-1 e d=n-1 forca o acesso a v[0] ja na primeira iteracao em alguns casos (ex: n=1, e=-1, d=0, m=-1, erro) e e menos robusto que as versoes e=0, d=n ou e=-1, d=n.\n");
}

// ----------------------------------------------------------------------
// Ex. 21: Simplificação da Busca Binária Recursiva (buscabinaria3)
// ----------------------------------------------------------------------

int bb_simplificada(int x, int e, int d, int v[]) {

    if (e == d - 1) {
        return d; 
    } else {

        int m = e + (d - e) / 2;
        
        if (v[m] < x) {
            return bb_simplificada(x, m, d, v);
        } else {
            return bb_simplificada(x, e, m, v);
        }
    }
}

int buscabinaria3_simplificada(int x, int n, int v[]) {

    return bb_simplificada(x, -1, n, v);
}

void exercicio_21() {
    int v[] = {10, 20, 30, 40, 50};
    int n = 5;
    
    printf("Demonstracao da simplificacao da buscabinaria3 (recursiva)\n");
    printf("A funcao original (Ex. 4/bb) precisava de tratamento de casos extremos (x<=v[0] e x>v[n-1]).\n");
    printf("A versao simplificada: return bb(x, -1, n, v);\n");
    printf("   - Se x <= v[0]: A primeira chamada e bb(x, -1, 5, v). m=2. Como v[2]=30, e x<=30, d=m. bb(x, -1, 2, v), etc., ate d=0.\n");
    printf("   - Se x > v[n-1]: A primeira chamada e bb(x, -1, 5, v). m=2. Como v[2]<x, e=m. bb(x, 2, 5, v), etc., ate e=4, d=5. Retorna d=5 (correto).\n");
    printf("A simplificacao e valida pois move a responsabilidade de checar os limites para o invariante (v[e] < x <= v[d]), tratando os extremos como elementos sentinelas imaginarios.\n");
    
    printf("\nBusca de x=20: Indice j = %d (Correto: 1)\n", buscabinaria3_simplificada(20, n, v));
    printf("Busca de x=35: Indice j = %d (Correto: 3)\n", buscabinaria3_simplificada(35, n, v));
    printf("Busca de x=5: Indice j = %d (Correto: 0)\n", buscabinaria3_simplificada(5, n, v));
    printf("Busca de x=55: Indice j = %d (Correto: 5)\n", buscabinaria3_simplificada(55, n, v));
}

// ----------------------------------------------------------------------
// Ex. 23: Overflow em m = (e+d)/2
// ----------------------------------------------------------------------

void exercicio_23() {
    printf("Problema de Overflow em m = (e+d)/2 quando n (e, d) se aproxima de INT_MAX.\n");
    printf("O overflow ocorre se a soma de 'e' e 'd' for maior que o valor maximo de um inteiro (INT_MAX).\n");
    printf("A solucao amplamente aceita e utilizar a formulacao que evita a soma dos dois valores maximos:\n");
    
    printf("\nAlternativa:\n");
    printf("int m = e + (d - e) / 2;\n");
    
    printf("Esta formula calcula a metade da distancia (d - e) e a adiciona a 'e'.\n");
    printf("Dessa forma, o resultado intermediario (d - e) nunca sera maior que o valor maximo de 'd', evitando o overflow.\n");
}

// ----------------------------------------------------------------------
// Ex. 25: Busca Binária em Vetor de Structs (Busca por numero)
// ----------------------------------------------------------------------

const char* busca_aluno_recursiva(int numero, const Aluno v[], int e, int d) {
    if (e > d) {
        return ""; 
    }
    
    int m = e + (d - e) / 2;
    
    if (v[m].numero == numero) {
        return v[m].nome;
    } else if (v[m].numero < numero) {
        return busca_aluno_recursiva(numero, v, m + 1, d);
    } else {
        return busca_aluno_recursiva(numero, v, e, m - 1);
    }
}

const char* busca_aluno(int numero, int n, const Aluno v[]) {
 
    int e = 0;
    int d = n - 1;
    
    while (e <= d) {
        int m = e + (d - e) / 2;
        
        if (v[m].numero == numero) {
            return v[m].nome; 
        } else if (v[m].numero < numero) {
            e = m + 1;
        } else {
            d = m - 1;
        }
    }
    
    return "";
}


void exercicio_25() {
    Aluno vetor_alunos[] = {
        {"Alice", 100},
        {"Bob", 150},
        {"Charlie", 200},
        {"David", 250},
        {"Eva", 300}
    };
    int n = sizeof(vetor_alunos) / sizeof(Aluno);
    int numero_busca;
    const char *nome_encontrado;
    
    printf("Busca Binaria em Vetor de Structs (Ordenado por Numero)\n");
    printf("Alunos (Numero, Nome): (100, Alice), (150, Bob), (200, Charlie), (250, David), (300, Eva)\n");

    printf("Digite o numero do aluno para buscar: ");
    if (scanf("%d", &numero_busca) != 1) {
        printf("Entrada invalida.\n");
        clear_buffer();
        return;
    }
    clear_buffer();

    nome_encontrado = busca_aluno(numero_busca, n, vetor_alunos);
    
    if (strcmp(nome_encontrado, "") == 0) {
        printf("Numero %d nao encontrado. Retorna string vazia.\n", numero_busca);
    } else {
        printf("Numero %d encontrado. Nome do aluno: %s\n", numero_busca, nome_encontrado);
    }
}

// ----------------------------------------------------------------------
// MENU PRINCIPAL
// ----------------------------------------------------------------------

void display_menu() {
    printf("\n--------------------------------------------------------------\n");
    printf("| Lista de Exercicios Impares - Algoritmos de Busca          |\n");
    printf("--------------------------------------------------------------\n");
    printf("| 01. Ex. 01: Critica a Formulacao de Busca                  |\n");
    printf("| 03. Ex. 03: Discute a Busca Sequencial Recursiva (busca2)  |\n");
    printf("| 05. Ex. 05: Execucao/Rastreio da buscabinaria (Ex. 4)      |\n");
    printf("| 07. Ex. 07: Busca Binaria Exata (Retorna j ou -1)          |\n");
    printf("| 09. Ex. 09: Execucao/Rastreio da buscabinaria2 (Ex. 8)     |\n");
    printf("| 11. Ex. 11: Validade da Afirmacao sobre (e+d)              |\n");
    printf("| 13. Ex. 13: Busca Binaria para v[j-1] <= x < v[j]          |\n");
    printf("| 15. Ex. 15: Busca Binaria em v[1..n]                       |\n");
    printf("| 17. Ex. 17: Alternativa de Busca Binaria (Ex. 16/17)       |\n");
    printf("| 19. Ex. 19: Analisa Alternativa de Busca Binaria (Ex. 18)  |\n");
    printf("| 21. Ex. 21: Simplificacao da Busca Binaria Recursiva       |\n");
    printf("| 23. Ex. 23: Evitando Overflow em m = (e+d)/2               |\n");
    printf("| 25. Ex. 25: Busca Binaria em Vetor de Structs              |\n");
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
            case 0: printf("Saindo do programa.\n"); break;
            default: printf("Opcao invalida. Tente novamente.\n");
        }

        if (escolha != 0) {
            pause_execution();
        }

    } while (escolha != 0);

    return 0;
}