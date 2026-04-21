#include <stdio.h>
#include <string.h>

#define MAX 100

// Estrutura da banda
typedef struct {
    char nome[50];
    char tipo[30];
    int integrantes;
    int ranking; // 0 = não está entre as favoritas
} Banda;

// a) Função para cadastrar bandas
void cadastrarBandas(Banda bandas[], int n) {
    for (int i = 0; i < n; i++) {
        printf("\n=== Cadastro da %dª banda ===\n", i+1);

        printf("Nome da banda: ");
        getchar(); // limpar buffer
        fgets(bandas[i].nome, 50, stdin);
        bandas[i].nome[strcspn(bandas[i].nome, "\n")] = '\0';

        printf("Tipo de musica: ");
        fgets(bandas[i].tipo, 30, stdin);
        bandas[i].tipo[strcspn(bandas[i].tipo, "\n")] = '\0';

        printf("Numero de integrantes: ");
        scanf("%d", &bandas[i].integrantes);

        printf("Posicao no ranking (0 se nao estiver no top 5): ");
        scanf("%d", &bandas[i].ranking);
    }
}

// b) Buscar banda pelo ranking
void buscarPorRanking(Banda bandas[], int n, int pos) {
    int encontrada = 0;
    for (int i = 0; i < n; i++) {
        if (bandas[i].ranking == pos) {
            printf("\n--- Banda encontrada ---\n");
            printf("Nome: %s\n", bandas[i].nome);
            printf("Tipo: %s\n", bandas[i].tipo);
            printf("Integrantes: %d\n", bandas[i].integrantes);
            printf("Ranking: %d\n", bandas[i].ranking);
            encontrada = 1;
            break;
        }
    }
    if (!encontrada)
        printf("\nNao existe banda com esse ranking.\n");
}

// c) Exibir bandas de um determinado tipo de música
void buscarPorTipo(Banda bandas[], int n, char tipo[]) {
    int encontrada = 0;
    printf("\nBandas do tipo '%s' no ranking:\n", tipo);
    for (int i = 0; i < n; i++) {
        if (strcmp(bandas[i].tipo, tipo) == 0 && bandas[i].ranking > 0) {
            printf("- %s (Ranking %d)\n", bandas[i].nome, bandas[i].ranking);
            encontrada = 1;
        }
    }
    if (!encontrada)
        printf("Nenhuma banda desse tipo no ranking.\n");
}

// d) Verificar se uma banda está entre as favoritas
void verificarFavorita(Banda bandas[], int n, char nome[]) {
    int encontrada = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(bandas[i].nome, nome) == 0) {
            if (bandas[i].ranking > 0)
                printf("\nA banda '%s' esta no ranking (posicao %d).\n", bandas[i].nome, bandas[i].ranking);
            else
                printf("\nA banda '%s' NAO esta entre as favoritas.\n", bandas[i].nome);
            encontrada = 1;
            break;
        }
    }
    if (!encontrada)
        printf("\nBanda nao encontrada no cadastro.\n");
}
void banda() {
    Banda bandas[MAX];
    int n, opcao;

    printf("Quantas bandas deseja cadastrar? ");
    scanf("%d", &n);

    cadastrarBandas(bandas, n);

    do {
        printf("\n===== MENU =====\n");
        printf("1 - Buscar por ranking\n");
        printf("2 - Buscar por tipo de musica\n");
        printf("3 - Verificar se banda esta entre as favoritas\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int pos;
            printf("Digite a posicao do ranking (1 a 5): ");
            scanf("%d", &pos);
            buscarPorRanking(bandas, n, pos);
        } 
        else if (opcao == 2) {
            char tipo[30];
            printf("Digite o tipo de musica: ");
            getchar();
            fgets(tipo, 30, stdin);
            tipo[strcspn(tipo, "\n")] = '\0';
            buscarPorTipo(bandas, n, tipo);
        } 
        else if (opcao == 3) {
            char nome[50];
            printf("Digite o nome da banda: ");
            getchar();
            fgets(nome, 50, stdin);
            nome[strcspn(nome, "\n")] = '\0';
            verificarFavorita(bandas, n, nome);
        }

    } while (opcao != 0);

}


// Definição do tipo Complexo
typedef struct {
    float real;
    float imag;
} Complexo;

// Função para ler um número complexo
Complexo lerComplexo() {
    Complexo z;
    printf("Parte real: ");
    scanf("%f", &z.real);
    printf("Parte imaginaria: ");
    scanf("%f", &z.imag);
    return z;
}

// Função para exibir um número complexo
void imprimirComplexo(Complexo z) {
    if (z.imag >= 0)
        printf("%.2f + %.2fi\n", z.real, z.imag);
    else
        printf("%.2f - %.2fi\n", z.real, -z.imag);
}

// Função para somar dois complexos
Complexo somar(Complexo z1, Complexo z2) {
    Complexo r;
    r.real = z1.real + z2.real;
    r.imag = z1.imag + z2.imag;
    return r;
}

// Função para subtrair dois complexos
Complexo subtrair(Complexo z1, Complexo z2) {
    Complexo r;
    r.real = z1.real - z2.real;
    r.imag = z1.imag - z2.imag;
    return r;
}

// Função para multiplicar dois complexos
Complexo multiplicar(Complexo z1, Complexo z2) {
    Complexo r;
    // (a + bi)(c + di) = (ac - bd) + (ad + bc)i
    r.real = (z1.real * z2.real) - (z1.imag * z2.imag);
    r.imag = (z1.real * z2.imag) + (z1.imag * z2.real);
    return r;
}

// Programa principal
void complexo() {
    Complexo z1, z2, resultado;

    printf("Digite o primeiro numero complexo:\n");
    z1 = lerComplexo();

    printf("\nDigite o segundo numero complexo:\n");
    z2 = lerComplexo();

    printf("\nPrimeiro numero: ");
    imprimirComplexo(z1);
    printf("Segundo numero: ");
    imprimirComplexo(z2);

    resultado = somar(z1, z2);
    printf("\nSoma: ");
    imprimirComplexo(resultado);

    resultado = subtrair(z1, z2);
    printf("Subtracao: ");
    imprimirComplexo(resultado);

    resultado = multiplicar(z1, z2);
    printf("Multiplicacao: ");
    imprimirComplexo(resultado);


}

// Estrutura para Data
typedef struct {
    int dia, mes, ano;
} Data;

// Estrutura para Endereço
typedef struct {
    char rua[50];
    char cidade[30];
    char estado[3];
    char cep[10];
} Endereco;

// Estrutura para Aluno
typedef struct {
    char nome[50];
    Data nascimento;
    char rg[15];
    char sexo;
    Endereco endereco;
    int ra;       // Registro do Aluno (chave única)
    float cr;     // Coeficiente de Rendimento [0,1]
} Aluno;

// Função para cadastrar aluno
void inserirAluno(Aluno cadastro[], int *n) {
    if (*n >= MAX) {
        printf("\nCadastro cheio! Não é possível adicionar mais alunos.\n");
        return;
    }

    printf("\n=== Cadastro do aluno %d ===\n", *n + 1);
    getchar(); // limpar buffer do teclado

    printf("Nome: ");
    fgets(cadastro[*n].nome, 50, stdin);
    cadastro[*n].nome[strcspn(cadastro[*n].nome, "\n")] = '\0';

    printf("Data de nascimento (dd mm aaaa): ");
    scanf("%d %d %d", &cadastro[*n].nascimento.dia, &cadastro[*n].nascimento.mes, &cadastro[*n].nascimento.ano);

    getchar();
    printf("RG: ");
    fgets(cadastro[*n].rg, 15, stdin);
    cadastro[*n].rg[strcspn(cadastro[*n].rg, "\n")] = '\0';

    printf("Sexo (M/F): ");
    scanf(" %c", &cadastro[*n].sexo);

    getchar();
    printf("Rua: ");
    fgets(cadastro[*n].endereco.rua, 50, stdin);
    cadastro[*n].endereco.rua[strcspn(cadastro[*n].endereco.rua, "\n")] = '\0';

    printf("Cidade: ");
    fgets(cadastro[*n].endereco.cidade, 30, stdin);
    cadastro[*n].endereco.cidade[strcspn(cadastro[*n].endereco.cidade, "\n")] = '\0';

    printf("Estado (UF): ");
    fgets(cadastro[*n].endereco.estado, 3, stdin);
    cadastro[*n].endereco.estado[strcspn(cadastro[*n].endereco.estado, "\n")] = '\0';

    printf("CEP: ");
    fgets(cadastro[*n].endereco.cep, 10, stdin);
    cadastro[*n].endereco.cep[strcspn(cadastro[*n].endereco.cep, "\n")] = '\0';

    printf("RA: ");
    scanf("%d", &cadastro[*n].ra);

    printf("CR [0 a 1]: ");
    scanf("%f", &cadastro[*n].cr);

    (*n)++;
}

// Ordenar alunos por nome (ordem alfabética)
void ordenarPorNome(Aluno cadastro[], int n) {
    Aluno temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(cadastro[i].nome, cadastro[j].nome) > 0) {
                temp = cadastro[i];
                cadastro[i] = cadastro[j];
                cadastro[j] = temp;
            }
        }
    }
    printf("\nCadastro ordenado por nome.\n");
}

// Ordenar alunos por CR (maiores primeiro)
void ordenarPorCR(Aluno cadastro[], int n) {
    Aluno temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (cadastro[i].cr < cadastro[j].cr) {
                temp = cadastro[i];
                cadastro[i] = cadastro[j];
                cadastro[j] = temp;
            }
        }
    }
    printf("\nCadastro ordenado por CR.\n");
}

// Buscar aluno pelo RA
void buscarPorRA(Aluno cadastro[], int n, int ra) {
    for (int i = 0; i < n; i++) {
        if (cadastro[i].ra == ra) {
            printf("\n=== Aluno encontrado ===\n");
            printf("Nome: %s\n", cadastro[i].nome);
            printf("Nascimento: %02d/%02d/%04d\n", cadastro[i].nascimento.dia, cadastro[i].nascimento.mes, cadastro[i].nascimento.ano);
            printf("RG: %s\n", cadastro[i].rg);
            printf("Sexo: %c\n", cadastro[i].sexo);
            printf("Endereco: %s, %s - %s, CEP: %s\n",
                   cadastro[i].endereco.rua, cadastro[i].endereco.cidade,
                   cadastro[i].endereco.estado, cadastro[i].endereco.cep);
            printf("RA: %d\n", cadastro[i].ra);
            printf("CR: %.2f\n", cadastro[i].cr);
            return;
        }
    }
    printf("\nAluno com RA %d não encontrado.\n", ra);
}

// Imprimir todos os alunos cadastrados
void imprimirCadastro(Aluno cadastro[], int n) {
    printf("\n=== Lista de Alunos (%d cadastrados) ===\n", n);
    for (int i = 0; i < n; i++) {
        printf("\nAluno %d:\n", i + 1);
        printf("Nome: %s\n", cadastro[i].nome);
        printf("Nascimento: %02d/%02d/%04d\n", cadastro[i].nascimento.dia, cadastro[i].nascimento.mes, cadastro[i].nascimento.ano);
        printf("RG: %s\n", cadastro[i].rg);
        printf("Sexo: %c\n", cadastro[i].sexo);
        printf("Endereco: %s, %s - %s, CEP: %s\n",
               cadastro[i].endereco.rua, cadastro[i].endereco.cidade,
               cadastro[i].endereco.estado, cadastro[i].endereco.cep);
        printf("RA: %d\n", cadastro[i].ra);
        printf("CR: %.2f\n", cadastro[i].cr);
    }
}


void aluno(){
    Aluno cadastro[MAX];
    int n = 0, opcao, ra;

    do {
        printf("\n===== MENU =====\n");
        printf("1 - Inserir novo aluno\n");
        printf("2 - Ordenar por nome\n");
        printf("3 - Ordenar por CR\n");
        printf("4 - Buscar por RA\n");
        printf("5 - Imprimir cadastro\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirAluno(cadastro, &n);
                break;
            case 2:
                ordenarPorNome(cadastro, n);
                break;
            case 3:
                ordenarPorCR(cadastro, n);
                break;
            case 4:
                printf("Digite o RA do aluno: ");
                scanf("%d", &ra);
                buscarPorRA(cadastro, n, ra);
                break;
            case 5:
                imprimirCadastro(cadastro, n);
                break;
            case 0:
                printf("\nSaindo...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }
    } while (opcao != 0);


}


// Definição da struct
struct vetor {
    float x;
    float y;
    float z;
};

// Função para ler um vetor
struct vetor lerVetor() {
    struct vetor v;
    printf("Digite as coordenadas (x y z): ");
    scanf("%f %f %f", &v.x, &v.y, &v.z);
    return v;
}

// Função para somar dois vetores
struct vetor somaVetores(struct vetor v1, struct vetor v2) {
    struct vetor r;
    r.x = v1.x + v2.x;
    r.y = v1.y + v2.y;
    r.z = v1.z + v2.z;
    return r;
}

// Função para imprimir um vetor
void imprimirVetor(struct vetor v) {
    printf("(%.2f, %.2f, %.2f)\n", v.x, v.y, v.z);
}

void somadevetores() {
    struct vetor v1, v2, resultado;

    printf("Digite o primeiro vetor:\n");
    v1 = lerVetor();

    printf("Digite o segundo vetor:\n");
    v2 = lerVetor();

    resultado = somaVetores(v1, v2);

    printf("\nA soma dos vetores é: ");
    imprimirVetor(resultado);


}

#define MAX 100

typedef struct {
    char nome[50];
    int idade;
    float salario;
    struct {
        int dia;
        int mes;
        int ano;
    } nascimento;
} Funcionario;

typedef struct {
    Funcionario funcionarios[MAX];
    int qtd;
} TipoCadastro;

void IniciaCadastro(TipoCadastro *cadastro) {
    cadastro->qtd = 0;
}

void InserirFuncionario(TipoCadastro *cadastro) {
    if (cadastro->qtd >= MAX) return;
    Funcionario f;
    getchar();
    printf("\nNome: ");
    fgets(f.nome, 50, stdin);
    f.nome[strcspn(f.nome, "\n")] = '\0';
    printf("Idade: ");
    scanf("%d", &f.idade);
    printf("Salario: ");
    scanf("%f", &f.salario);
    printf("Data de nascimento (dd mm aaaa): ");
    scanf("%d %d %d", &f.nascimento.dia, &f.nascimento.mes, &f.nascimento.ano);
    cadastro->funcionarios[cadastro->qtd++] = f;
}

void ListaFuncionarios(TipoCadastro *cadastro) {
    if (cadastro->qtd == 0) {
        printf("\nNenhum funcionario cadastrado.\n");
        return;
    }
    printf("\n=== Lista de Funcionarios ===\n");
    for (int i = 0; i < cadastro->qtd; i++) {
        printf("Funcionario %d:\n", i + 1);
        printf("Nome: %s\n", cadastro->funcionarios[i].nome);
        printf("Idade: %d\n", cadastro->funcionarios[i].idade);
        printf("Salario: %.2f\n", cadastro->funcionarios[i].salario);
        printf("Nascimento: %02d/%02d/%04d\n\n",
               cadastro->funcionarios[i].nascimento.dia,
               cadastro->funcionarios[i].nascimento.mes,
               cadastro->funcionarios[i].nascimento.ano);
    }
}

void SalarioIntervalo(TipoCadastro *cadastro, float v1, float v2) {
    if (cadastro->qtd == 0) {
        printf("\nNenhum funcionario cadastrado.\n");
        return;
    }
    float soma = 0;
    int count = 0;
    printf("\n=== Funcionarios com salario entre %.2f e %.2f ===\n", v1, v2);
    for (int i = 0; i < cadastro->qtd; i++) {
        float s = cadastro->funcionarios[i].salario;
        if (s >= v1 && s <= v2) {
            printf("Nome: %s | Idade: %d | Salario: %.2f\n",
                   cadastro->funcionarios[i].nome,
                   cadastro->funcionarios[i].idade, s);
            soma += s;
            count++;
        }
    }
    if (count > 0)
        printf("\nMedia dos salarios listados: %.2f\n", soma / count);
    else
        printf("\nNenhum funcionario encontrado nesse intervalo.\n");
}

Funcionario BuscaNome(TipoCadastro *cadastro, char nome[]) {
    Funcionario vazio;  
    strcpy(vazio.nome, "");  
    vazio.idade = 0;
    vazio.salario = 0.0;
    for (int i = 0; i < cadastro->qtd; i++)
        if (strcmp(cadastro->funcionarios[i].nome, nome) == 0)
            return cadastro->funcionarios[i];
    return vazio;
}

Funcionario ListaMaraja(TipoCadastro *cadastro) {
    Funcionario vazio;
    strcpy(vazio.nome, "");
    vazio.idade = 0;
    vazio.salario = 0.0;
    if (cadastro->qtd == 0) return vazio;
    Funcionario maior = cadastro->funcionarios[0];
    for (int i = 1; i < cadastro->qtd; i++)
        if (cadastro->funcionarios[i].salario > maior.salario)
            maior = cadastro->funcionarios[i];
    return maior;
}

void ListaAniversarioMes(TipoCadastro *cadastro, int mes) {
    if (cadastro->qtd == 0) {
        printf("\nNenhum funcionario cadastrado.\n");
        return;
    }
    int encontrados = 0;
    printf("\n=== Funcionarios com aniversario no mes %d ===\n", mes);
    for (int i = 0; i < cadastro->qtd; i++)
        if (cadastro->funcionarios[i].nascimento.mes == mes) {
            printf("Nome: %s | Dia: %02d\n",
                   cadastro->funcionarios[i].nome,
                   cadastro->funcionarios[i].nascimento.dia);
            encontrados++;
        }
    if (encontrados == 0)
        printf("Nenhum funcionario faz aniversario neste mes.\n");
}

int cadastro() {
    TipoCadastro empresa;
    IniciaCadastro(&empresa);
    int opcao;
    do {
        printf("\n===== MENU =====\n");
        printf("1 - Inserir funcionario\n");
        printf("2 - Listar funcionarios\n");
        printf("3 - Listar por salario intervalo\n");
        printf("4 - Buscar por nome\n");
        printf("5 - Funcionario com maior salario\n");
        printf("6 - Lista aniversario por mes\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        if (opcao == 1)
            InserirFuncionario(&empresa);
        else if (opcao == 2)
            ListaFuncionarios(&empresa);
        else if (opcao == 3) {
            float v1, v2;
            printf("Digite intervalo v1 v2: ");
            scanf("%f %f", &v1, &v2);
            SalarioIntervalo(&empresa, v1, v2);
        }
        else if (opcao == 4) {
            char nome[50];
            getchar();
            printf("Digite nome: ");
            fgets(nome, 50, stdin);
            nome[strcspn(nome, "\n")] = '\0';
            Funcionario f = BuscaNome(&empresa, nome);
            if (strcmp(f.nome, "") == 0)
                printf("Funcionario nao encontrado.\n");
            else
                printf("Nome: %s | Idade: %d | Salario: %.2f | Nascimento: %02d/%02d/%04d\n",
                       f.nome, f.idade, f.salario,
                       f.nascimento.dia, f.nascimento.mes, f.nascimento.ano);
        }
        else if (opcao == 5) {
            Funcionario f = ListaMaraja(&empresa);
            if (strcmp(f.nome, "") == 0)
                printf("Nenhum funcionario cadastrado.\n");
            else
                printf("Funcionario com maior salario: %s | Salario: %.2f\n", f.nome, f.salario);
        }
        else if (opcao == 6) {
            int mes;
            printf("Digite mes (1-12): ");
            scanf("%d", &mes);
            ListaAniversarioMes(&empresa, mes);
        }
    } while (opcao != 0);
    return 0;
}
int main() {
    int l;
    do {
        printf("\nSelecione o exercício (só valem ímpares,9 envolve tudo sobre funcionários). Digite 0 para sair: ");
        scanf("%d", &l);
        switch(l) {
            case 1:
                banda();
                break;
            case 3:
                complexo();
                break;
            case 5:
                aluno();
                break;
            case 7:
                somadevetores();
                break;
            case 9:
                cadastro();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(l != 0);
    return 0;
}



