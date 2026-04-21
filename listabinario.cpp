#define MAX_REGISTROS 500
#define MAX_NUMEROS 500
#define MAX_DISC 50
#define MAX_ALUNOS 50
#define MAX_CURSADAS 7
#define MAX_PREMATR 7
#define MAX_FUNC 100
#define MAX 100
typedef struct {
    int numero;
    char nome[50];
    double saldo;
} Conta;
typedef struct {
    char sexo;
    int idade;
    char fumante;
} Pessoa;
typedef struct {
    int numero;
    char tipo;
    double valor;
} Movimentacao;
typedef struct {
    int matricula;
    char nome[50];
    char curso[30];
} Aluno;
typedef struct {
    int codigo;
    char nome[100];
    char preReq[100];
} DISCIPLINA;

typedef struct {
    int matricula;
    char nome[101];
    char curso[50];
    int semestre;
    char disciplinas_cursadas[MAX_CURSADAS][100];
    int totalCursadas;
} ALUNO;
typedef struct {
    int numero;
    char nome[101];
    char curso[50];
    double p1, p2, mt;
    double frequencia;
    int existe;
} ALUNO2;
typedef struct {
    int matricula;
    char nome[101];
    char curso[50];
    int semestre;
    char disciplinas_liberadas[MAX_PREMATR][100];
} PREMATRICULA;
typedef struct {
    char nome[101];
    int sexo;
    char corOlhos[20];
    double altura;
    double peso;
    DATA nascimento;
} CADASTRO;

typedef struct {
    char nome[101];
    char corOlhos[20];
    double peso;
    DATA nascimento;
} RESUMO;
typedef struct {
    int dia, mes, ano;
} DATA;
typedef struct {
    int chave;
    char info[101];
    DATA data;
    int existe;
} REGISTRO;
typedef struct{
    char nome[101];
    int idade;
    double nota;
    int existe;
}TURMA;
typedef struct{
    char nome[101];
    int idade;
    double altura;
    int existe;
}PESSOA;
typedef struct{
    char telefone[20];
    char cidade[50];
    double tempoLigacao;
    int existe;
} TELEFONE;
typedef struct {
    char nome[101];
    char rua[101];
    int numero;
    char telefone[20];
    char cidade[50];
    char estado[3];
    int existe;
} CONTATO;
typedef struct {
    char sexo[2];
    int idade;
    double salario;
    char estadoCivil[20];
    int dependentes;
    double patrimonio;
    int calorias;
    char grauInstrucao[30];
    int existe;
} PESSOA;
typedef struct {
    int codigo;
    char descricao[50];
    int quantidade;
} Produto;
//-------------------------------------------------
int encontrarConta(Conta contas[], int n, int numero){
    int i = 0, achou = 0, idx = -1;
    while(i < n && achou == 0){
        if(contas[i].numero == numero){
            idx = i;
            achou = 1;
        }
        i++;
    }
    return idx;
}

int contaRemovida(int removidas[], int n, int numero){
    int i = 0, achou = 0;
    while(i < n && achou == 0){
        if(removidas[i] == numero){
            achou = 1;
        }
        i++;
    }
    return achou;
}
void carregarAlunos(Aluno alunos[], int *n){
    FILE *arq;
    if((arq = fopen("alunos.bin", "rb")) == NULL){
        printf("Erro ao abrir arquivo alunos.bin\n");
        *n = 0;
        return;
    }
    int i = 0;
    Aluno aluno;
    while(fread(&aluno, sizeof(Aluno), 1, arq) == 1){
        if(i >= MAX){
            printf("Vetor cheio! Alguns alunos não foram carregados.\n");
            break;
        }
        alunos[i] = aluno;
        i++;
    }
    *n = i;
    fclose(arq);
}

void pesquisaPorMatricula(Aluno alunos[], int n){
    int matricula;
    int continuar = 1;

    while(continuar == 1){
        printf("\nDigite a matrícula (ou um número negativo para voltar): ");
        scanf("%d", &matricula);
        fflush(stdin);

        if(matricula < 0){
            continuar = 0; 
        } 
        else{
            int achou = 0;
            int i = 0;
            while(i < n && achou == 0){
                if(alunos[i].matricula == matricula){
                    printf("\nAluno encontrado!\n");
                    printf("Matrícula: %d\nNome: %s\nCurso: %s\n", alunos[i].matricula, alunos[i].nome, alunos[i].curso);
                    achou = 1;
                }
                i++;
            }
            if(achou == 0){
                printf("Matrícula %d não encontrada.\n", matricula);
            }
        }
    }
}

void pesquisaPorNome(Aluno alunos[], int n){
    char nome[50];
    int continuar = 1;

    while(continuar == 1){
        printf("\nDigite o nome (ou 'FIM' para voltar): ");
        fgets(nome, sizeof(nome), stdin);
        nome[strcspn(nome, "\n")] = '\0';

        if(strcmp(nome, "FIM") == 0){
            continuar = 0;
        } 
        else{
            int achou = 0;
            int i = 0;
            while (i < n && achou == 0) {
                if(strcasecmp(alunos[i].nome, nome) == 0){
                    printf("\nAluno encontrado!\n");
                    printf("Matrícula: %d\nNome: %s\nCurso: %s\n", alunos[i].matricula, alunos[i].nome, alunos[i].curso);
                    achou = 1;
                }
                i++;
            }
            if(achou == 0){
                printf("Aluno com nome '%s' não encontrado.\n", nome);
            }
        }
    }
}
void adicionarProduto(const char *arquivo){
    FILE *arq = fopen(arquivo, "a+b");
    if(!arq) { printf("Erro ao abrir arquivo.\n"); return; }

    Produto p;
    printf("Código do produto: ");
    scanf("%d", &p.codigo);
    fflush(stdin);

    printf("Descrição: ");
    fgets(p.descricao, sizeof(p.descricao), stdin);
    p.descricao[strcspn(p.descricao, "\n")] = '\0';

    printf("Quantidade inicial: ");
    scanf("%d", &p.quantidade);
    fflush(stdin);

    fwrite(&p, sizeof(Produto), 1, arq);
    fclose(arq);
    printf("Produto cadastrado com sucesso!\n");
}

void entradaProduto(const char *arquivo){
    FILE *arq;
    if((arq = fopen(arquivo, "r+b")) == NULL){ 
        printf("Erro ao abrir arquivo.\n"); 
        return; 
    }

    int codigo, qtd;
    printf("Código do produto: ");
    scanf("%d", &codigo);
    fflush(stdin);
    printf("Quantidade a adicionar: ");
    scanf("%d", &qtd);
    fflush(stdin);

    Produto p;
    int encontrado = 0;
    while(fread(&p, sizeof(Produto), 1, arq) == 1){
        if(p.codigo == codigo) {
            p.quantidade += qtd;
            fseek(arq, -sizeof(Produto), SEEK_CUR);
            fwrite(&p, sizeof(Produto), 1, arq);
            printf("Nova quantidade de %s: %d\n", p.descricao, p.quantidade);
            encontrado = 1;
        }
    }

    if(!encontrado){
        printf("Produto não encontrado.\n");
    }
    fclose(arq);
}

void retiradaProduto(const char *arquivo){
    FILE *arq;
    if((arq = fopen(arquivo, "r+b")) == NULL){ 
        printf("Erro ao abrir arquivo.\n"); 
        return; 
    }

    int codigo, qtd;
    printf("Código do produto: ");
    scanf("%d", &codigo);
    fflush(stdin);
    printf("Quantidade a retirar: ");
    scanf("%d", &qtd);
    fflush(stdin);

    Produto p;
    int encontrado = 0;
    while(fread(&p, sizeof(Produto), 1, arq) == 1) {
        if(p.codigo == codigo) {
            if(p.quantidade >= qtd){
                p.quantidade -= qtd;
                fseek(arq, -sizeof(Produto), SEEK_CUR);
                fwrite(&p, sizeof(Produto), 1, arq);
                printf("Nova quantidade de %s: %d\n", p.descricao, p.quantidade);
            } 
            else{
                printf("Estoque insuficiente! Quantidade atual: %d\n", p.quantidade);
            }
            encontrado = 1;
        }
    }

    if(!encontrado){
        printf("Produto não encontrado.\n");
    }
    fclose(arq);
}

void relatorioGeral(const char *arquivo){
    FILE *arq;
    if((arq = fopen(arquivo, "rb")) == NULL){ 
        printf("Erro ao abrir arquivo.\n"); 
        return; 
    }

    Produto p;
    printf("\n--- Relatório Geral ---\n");
    int continuar = 1;
    while(fread(&p, sizeof(Produto), 1, arq) == 1 && continuar){
        printf("Código: %d | Produto: %s | Quantidade: %d\n", p.codigo, p.descricao, p.quantidade);
    }
    fclose(arq);
}

void relatorioIndisponivel(const char *arquivo){
    FILE *arq;
    if((arq = fopen(arquivo, "rb")) == NULL){ 
        printf("Erro ao abrir arquivo.\n"); 
        return; 
    }

    Produto p;
    int achou = 0, continuar = 1;
    printf("\n--- Produtos Não Disponíveis ---\n");
    while(fread(&p, sizeof(Produto), 1, arq) == 1 && continuar){
        if(p.quantidade == 0){
            printf("Código: %d | Produto: %s\n", p.codigo, p.descricao);
            achou = 1;
        }
    }
    if(!achou){
        printf("Todos os produtos estão disponíveis.\n");
    }
    fclose(arq);
}
void cadastrarAluno(const char *arquivo){
    FILE *arq;
    if((arq = fopen(arquivo, "a+b")) == NULL){
        printf("Erro ao abrir arquivo.\n"); exit(1); 
    }

    int n;
    printf("Quantos alunos deseja cadastrar? ");
    scanf("%d", &n);
    fflush(stdin);

    for(int i = 0; i < n; i++){
        ALUNO2 a;
        a.existe = 1;

        printf("\nAluno %d:\n", i+1);
        printf("Número: ");
        scanf("%d", &a.numero);
        fflush(stdin);

        printf("Nome: ");
        fgets(a.nome, sizeof(a.nome), stdin);
        a.nome[strcspn(a.nome, "\n")] = '\0';

        printf("Curso: ");
        fgets(a.curso, sizeof(a.curso), stdin);
        a.curso[strcspn(a.curso, "\n")] = '\0';

        printf("Nota P1: ");
        scanf("%lf", &a.p1);
        printf("Nota P2: ");
        scanf("%lf", &a.p2);
        printf("Nota MT: ");
        scanf("%lf", &a.mt);
        printf("Frequência (%%): ");
        scanf("%lf", &a.frequencia);
        fflush(stdin);

        fwrite(&a, sizeof(ALUNO), 1, arq);
    }

    fclose(arq);
    printf("\nAlunos cadastrados com sucesso!\n");
}

void consultarAluno(const char *arquivo, int numero){
    FILE *arq;
    if((arq = fopen(arquivo, "rb")) == NULL){ 
        printf("Erro ao abrir arquivo.\n"); 
        exit(1); 
    }

    ALUNO a;
    int encontrado = 0;
    while(fread(&a, sizeof(ALUNO), 1, arq) == 1){
        if(a.existe && a.numero == numero){
            double mp = (a.p1 + a.p2)/2;
            double mf = 0.8*mp + 0.2*a.mt;
            char cond[10];
            if(mf >= 4.95 && a.frequencia >= 70){
                strcpy(cond, "Aprovado");
            }
            else{
                strcpy(cond, "Reprovado");
            }

            printf("\nNúmero: %d\nNome: %s\nCurso: %s\nMédia Final: %.2lf\nFrequência: %.2lf%%\nCondição: %s\n", a.numero, a.nome, a.curso, mf, a.frequencia, cond);
            encontrado = 1;
            break;
        }
    }

    if(!encontrado){
        printf("Aluno não encontrado.\n");
    }

    fclose(arq);
}

void alterarAluno(const char *arquivo, int numero){
    FILE *arq;
    if((arq = fopen(arquivo, "r+b")) == NULL){ 
        printf("Erro ao abrir arquivo.\n"); 
        exit(1); 
    }

    ALUNO a;
    int encontrado = 0;
    while(fread(&a, sizeof(ALUNO), 1, arq) == 1){
        if(a.existe && a.numero == numero){
            encontrado = 1;
            printf("Alterando aluno %s:\n", a.nome);

            printf("Nova P1: ");
            scanf("%lf", &a.p1);
            printf("Nova P2: ");
            scanf("%lf", &a.p2);
            printf("Nova MT: ");
            scanf("%lf", &a.mt);
            printf("Nova Frequência (%%): ");
            scanf("%lf", &a.frequencia);
            fflush(stdin);

            fseek(arq, -sizeof(ALUNO), SEEK_CUR);
            fwrite(&a, sizeof(ALUNO), 1, arq);
            printf("Aluno alterado com sucesso!\n");
            break;
        }
    }

    if(!encontrado){
        printf("Aluno não encontrado.\n");
    }
    fclose(arq);
}

void excluirAluno(const char *arquivo, int numero){
    FILE *arq, *aux;
    if((arq = fopen(arquivo, "r+b")) == NULL){ 
        printf("Erro ao abrir arquivo.\n"); 
        exit(1); 
    }
    if((aux = fopen("aux.dat", "wb")) == NULL){ 
        printf("Erro ao abrir arquivo.\n"); 
        exit(1); 
    }

    ALUNO2 a;
    int encontrado = 0;
    while(fread(&a, sizeof(ALUNO), 1, arq) == 1){
        if(a.existe && a.numero == numero){
            encontrado = 1;
            a.existe = 0;
        }
        if(a.existe){
            fwrite(&a, sizeof(ALUNO), 1, aux);
        }
    }

    fclose(arq);
    fclose(aux);

    remove(arquivo);
    rename("aux.dat", arquivo);

    if(!encontrado){
        printf("Aluno não encontrado.\n");
    }
    else{
        printf("Aluno excluído com sucesso!\n");
    }
}

void listarAlunos(const char *arquivo){
    FILE *arq;
    if((arq = fopen(arquivo, "rb")) == NULL){ 
        printf("Erro ao abrir arquivo.\n"); 
        exit(1); 
    }

    ALUNO2 a;
    printf("\n--- Lista de Alunos ---\n");
    while(fread(&a, sizeof(ALUNO), 1, arq) == 1){
        if(a.existe){
            double mp = (a.p1 + a.p2)/2;
            double mf = 0.8*mp + 0.2*a.mt;
            char cond[10];
            if(mf >= 4.95 && a.frequencia >= 70){ 
                strcpy(cond, "Aprovado");
            }
            else{
                strcpy(cond, "Reprovado");
            }

            printf("Número: %d | Nome: %s | Média Final: %.2lf | Frequência: %.2lf%% | Condição: %s\n", a.numero, a.nome, mf, a.frequencia, cond);
        }
    }

    fclose(arq);
}
void cadastrarDisciplinas(const char *arquivo){
    FILE *arq;
    if((arq = fopen(arquivo, "w+b")) == NULL){ 
        printf("Erro ao abrir %s\n", arquivo); 
        exit(1);
    }

    int n;
    printf("Quantas disciplinas deseja cadastrar? ");
    scanf("%d", &n);
    fflush(stdin);

    for(int i = 0; i < n; i++){
        DISCIPLINA d;
        printf("\nDisciplina %d:\n", i+1);

        printf("Codigo: ");
        scanf("%d", &d.codigo);
        fflush(stdin);

        printf("Nome: ");
        fgets(d.nome, sizeof(d.nome), stdin);
        d.nome[strcspn(d.nome, "\n")] = '\0';

        printf("Pre-requisito (digite 'vazio' se nao houver): ");
        fgets(d.preReq, sizeof(d.preReq), stdin);
        d.preReq[strcspn(d.preReq, "\n")] = '\0';

        fwrite(&d, sizeof(DISCIPLINA), 1, arq);
    }
    fclose(arq);
}

void cadastrarAlunos(const char *arquivo){
    FILE *arq;
    if((arq = fopen(arquivo, "w+b")) == NULL){ 
        printf("Erro ao abrir %s\n", arquivo); 
        exit(1);
    }

    int n;
    printf("\nQuantos alunos deseja cadastrar? ");
    scanf("%d", &n);
    fflush(stdin);

    for(int i = 0; i < n; i++){
        ALUNO a;
        printf("\nAluno %d:\n", i+1);

        printf("Matricula: ");
        scanf("%d", &a.matricula);
        fflush(stdin);

        printf("Nome: ");
        fgets(a.nome, sizeof(a.nome), stdin);
        a.nome[strcspn(a.nome, "\n")] = '\0';

        printf("Curso: ");
        fgets(a.curso, sizeof(a.curso), stdin);
        a.curso[strcspn(a.curso, "\n")] = '\0';

        printf("Semestre: ");
        scanf("%d", &a.semestre);
        fflush(stdin);

        printf("Quantas disciplinas ja cursadas pelo aluno? (max %d): ", MAX_CURSADAS);
        scanf("%d", &a.totalCursadas);
        fflush(stdin);

        for(int j = 0; j < a.totalCursadas; j++){
            printf("Disciplina cursada %d: ", j+1);
            fgets(a.disciplinas_cursadas[j], sizeof(a.disciplinas_cursadas[j]), stdin);
            a.disciplinas_cursadas[j][strcspn(a.disciplinas_cursadas[j], "\n")] = '\0';
        }

        fwrite(&a, sizeof(ALUNO), 1, arq);
    }

    fclose(arq);
}

void gerarPrematricula(const char *arquivoAlunos, const char *arquivoDisciplinas, const char *arquivoPrematricula){
    FILE *farqAlunos = fopen(arquivoAlunos, "rb");
    FILE *farqDisc = fopen(arquivoDisciplinas, "rb");
    FILE *farqPrem = fopen(arquivoPrematricula, "w+b");

    if(!farqAlunos || !farqDisc || !farqPrem){
        printf("Erro ao abrir algum arquivo.\n");
        exit(1);
    }

    ALUNO a;
    DISCIPLINA d;

    while(fread(&a, sizeof(ALUNO), 1, farqAlunos) == 1){
        PREMATRICULA p;
        p.matricula = a.matricula;
        strcpy(p.nome, a.nome);
        strcpy(p.curso, a.curso);
        p.semestre = a.semestre;

        for(int i = 0; i < MAX_PREMATR; i++){
            strcpy(p.disciplinas_liberadas[i], "N/A");
        }

        int totalLiberadas = 0;

        rewind(farqDisc);
        while(fread(&d, sizeof(DISCIPLINA), 1, farqDisc) == 1){
            if(totalLiberadas >= MAX_PREMATR){
                break;
            }

            int liberar = 1;
            if(strlen(d.preReq) > 0){
                liberar = 0;
                for(int j = 0; j < a.totalCursadas; j++){
                    if(strcmp(a.disciplinas_cursadas[j], d.preReq) == 0){
                        liberar = 1;
                        break;
                    }
                }
            }
            if(liberar){
                strcpy(p.disciplinas_liberadas[totalLiberadas++], d.nome);
            }
        }

        fwrite(&p, sizeof(PREMATRICULA), 1, farqPrem);
    }

    fclose(farqAlunos);
    fclose(farqDisc);
    fclose(farqPrem);

    printf("\nArquivo de pré-matrícula gerado: %s\n", arquivoPrematricula);
}

void listarArquivoPrematricula(const char *arquivo){
    FILE *arq;
    if((arq = fopen(arquivo, "rb")) == NULL){ 
        printf("Arquivo %s nao existe.\n", arquivo); 
        exit(1);
    }

    PREMATRICULA p;
    printf("\n--- PRE-MATRICULA ---\n");
    while(fread(&p, sizeof(PREMATRICULA), 1, arq) == 1){
        printf("\nAluno: %s | Matricula: %d | Curso: %s | Semestre: %d\n", p.nome, p.matricula, p.curso, p.semestre);
        printf("Disciplinas liberadas:\n");
        for(int i = 0; i < MAX_PREMATR; i++){
            printf(" - %s\n", p.disciplinas_liberadas[i]);
        }
    }

    fclose(arq);
}
int validaData24(int d, int m, int a){
    int dias_mes[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if((a % 400 == 0) || (a % 4 == 0 && a % 100 != 0)) {
        dias_mes[2] = 29;
    }
    if(m < 1 || m > 12){
        return 0;
    }
    if(d < 1 || d > dias_mes[m]){
        return 0;
    }
    return 1;
}

void criarArquivo24(){
    FILE *homens, *mulheres;

    if((homens = fopen("homens.dat", "w+b")) == NULL){
        printf("Erro ao abrir homens.dat\n");
        exit(1);
    }
    if((mulheres = fopen("mulheres.dat", "w+b")) == NULL){
        printf("Erro ao abrir mulheres.dat\n");
        exit(1);
    }

    int n;
    printf("Quantos registros deseja cadastrar? ");
    scanf("%d", &n);
    fflush(stdin);

    for(int i = 1; i <= n; i++){
        CADASTRO c;
        RESUMO r;

        printf("\nRegistro %d:\n", i);

        printf("Nome: ");
        fgets(c.nome, sizeof(c.nome), stdin);
        c.nome[strcspn(c.nome, "\n")] = '\0';

        do{
            printf("Sexo (1=Masculino, 2=Feminino): ");
            scanf("%d", &c.sexo);
            fflush(stdin);
            if(c.sexo != 1 && c.sexo != 2){
                printf("Sexo invalido! Digite 1 ou 2.\n");
            }     
        }while(c.sexo != 1 && c.sexo != 2);

        printf("Cor dos olhos: ");
        fgets(c.corOlhos, sizeof(c.corOlhos), stdin);
        c.corOlhos[strcspn(c.corOlhos, "\n")] = '\0';

        do{
            printf("Altura (m): ");
            scanf("%lf", &c.altura);
            fflush(stdin);
            if(c.altura <= 0){
                printf("Altura invalida! Digite um valor positivo.\n");
            }
        }while(c.altura <= 0);

        do{
            printf("Peso (kg): ");
            scanf("%lf", &c.peso);
            fflush(stdin);
            if(c.peso <= 0){
                printf("Peso invalido! Digite um valor positivo.\n");
            }
        }while(c.peso <= 0);

        do{
            printf("Data de nascimento (dia mes ano): ");
            scanf("%d %d %d", &c.nascimento.dia, &c.nascimento.mes, &c.nascimento.ano);
            fflush(stdin);
            if(!validaData24(c.nascimento.dia, c.nascimento.mes, c.nascimento.ano)){
                printf("Data invalida! Digite novamente.\n");
            }
        }while(!validaData(c.nascimento.dia, c.nascimento.mes, c.nascimento.ano));

        strcpy(r.nome, c.nome);
        strcpy(r.corOlhos, c.corOlhos);
        r.peso = c.peso;
        r.nascimento = c.nascimento;

        if(c.sexo == 1){
            fwrite(&r, sizeof(RESUMO), 1, homens);
        }
        else{
            fwrite(&r, sizeof(RESUMO), 1, mulheres);
        }
    }

    fclose(homens);
    fclose(mulheres);

    printf("\nRegistros cadastrados com sucesso em homens.dat e mulheres.dat!\n");
}

void listarArquivo24(const char *arquivo){
    FILE *arq;
    if((arq = fopen(arquivo, "rb")) == NULL){
        printf("Arquivo %s nao existe.\n", arquivo);
        exit(1);
    }

    RESUMO r;
    printf("\n--- Conteudo de %s ---\n", arquivo);
    while(fread(&r, sizeof(RESUMO), 1, arq) == 1){
        printf("Nome: %s | Cor dos olhos: %s | Peso: %.2lf | Data de nascimento: %02d/%02d/%04d\n", r.nome, r.corOlhos, r.peso, r.nascimento.dia, r.nascimento.mes, r.nascimento.ano);
    }

    fclose(arq);
}
int validaData(int d, int m, int a){
    int dias_mes[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if((a % 400 == 0) || (a % 4 == 0 && a % 100 != 0)) {
        dias_mes[2] = 29;
    }
    if(m < 1 || m > 12){
        return 0;
    }
    if(d < 1 || d > dias_mes[m]){
        return 0;
    }
    return 1;
}

void criarFonte(){
    FILE *arq;
    if((arq = fopen("FONTE.bin", "w+b")) == NULL){
        printf("Erro ao criar FONTE.bin\n");
        exit(1);
    }

    REGISTRO r;
    int n;
    printf("Quantos registros deseja cadastrar? ");
    scanf("%d", &n);
    fflush(stdin);

    for(int i = 1; i <= n; i++){
        printf("\nRegistro %d:\n", i);

        printf("Chave: ");
        scanf("%d", &r.chave);
        fflush(stdin);

        printf("Informacao: ");
        fgets(r.info, sizeof(r.info), stdin);
        r.info[strcspn(r.info, "\n")] = '\0';

        do{
            printf("Data (dia mes ano): ");
            scanf("%d %d %d", &r.data.dia, &r.data.mes, &r.data.ano);
            fflush(stdin);
            if(!validaData(r.data.dia, r.data.mes, r.data.ano)){
                printf("Data invalida! Digite novamente.\n");
            }
        }while(!validaData(r.data.dia, r.data.mes, r.data.ano));

        r.existe = 1;
        fwrite(&r, sizeof(REGISTRO), 1, arq);
    }

    fclose(arq);
}

void copiarFonteNova(){
    FILE *arqFonte = fopen("FONTE.bin", "rb");
    FILE *arqNova = fopen("FONTENOVA.bin", "w+b");

    if(!arqFonte || !arqNova){
        printf("Erro ao abrir arquivos.\n");
        exit(1);
    }

    REGISTRO r;
    while(fread(&r, sizeof(REGISTRO), 1, arqFonte) == 1){
        if(r.existe){
            fwrite(&r, sizeof(REGISTRO), 1, arqNova);
        }
    }

    fclose(arqFonte);
    fclose(arqNova);
    remove("FONTE.bin");

    printf("\nArquivo copiado para FONTENOVA.bin com sucesso!\n");
}


void listarArquivo22(const char *arquivo) {
    FILE *arq;
    if((arq = fopen(arquivo, "rb")) == NULL){
        printf("Arquivo %s nao existe.\n", arquivo);
        return;
    }

    RESUMO r;
    printf("\n--- Conteudo de %s ---\n", arquivo);
    while (fread(&r, sizeof(RESUMO), 1, arq) == 1) {
        printf("Nome: %s | Cor dos olhos: %s | Peso: %.2lf | Data de nascimento: %02d/%02d/%04d\n",
               r.nome, r.corOlhos, r.peso, r.nascimento.dia, r.nascimento.mes, r.nascimento.ano);
    }

    fclose(arq);
}
void criarNumeros(){
    FILE *arq;
    if((arq = fopen("numeros.bin", "w+b")) == NULL){
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    int n, num;
    printf("Quantos numeros deseja cadastrar? ");
    scanf("%d", &n);

    for(int i = 1; i <= n; i++){
        printf("Digite o numero %d: ", i);
        scanf(" %d", &num);
        fwrite(&num, sizeof(int), 1, arq);
    }

    fclose(arq);
}

void copiarParesOrdenados(){
    FILE *arqIn = fopen("numeros.bin", "rb");
    FILE *arqOut = fopen("pares.bin", "w+b");

    if(!arqIn || !arqOut){
        printf("Erro ao abrir arquivos.\n");
        exit(1);
    }

    int pares[MAX_NUMEROS];
    int total = 0, num;

    while(fread(&num, sizeof(int), 1, arqIn) == 1) {
        if(num % 2 == 0){
            pares[total++] = num;
        }
    }
    fclose(arqIn);

    for(int i = 0; i < total - 1; i++){
        int min = i;
        for(int j = i + 1; j < total; j++){
            if(pares[j] < pares[min]){
                min = j;
            }
        }
        if(min != i){
            int temp = pares[i];
            pares[i] = pares[min];
            pares[min] = temp;
        }
    }

    for(int i = 0; i < total; i++){
        fwrite(&pares[i], sizeof(int), 1, arqOut);
    }

    fclose(arqOut);
    printf("Numeros pares copiados e ordenados em pares.bin\n");
}
void listarArquivo20(const char *arquivo){
    FILE *arq;
    if((arq = fopen(arquivo, "rb")) == NULL){
        printf("Arquivo %s nao existe.\n", arquivo);
        exit(1);
    }

    int num;
    printf("\nConteudo de %s:\n", arquivo);
    while(fread(&num, sizeof(int), 1, arq) == 1){
        printf("%d ", num);
    }
    printf("\n");

    fclose(arq);
}

void criarArquivo18(const char *arquivo){
    FILE *arq;
    if((arq = fopen(arquivo, "w+b")) == NULL){
        printf("Erro ao abrir o arquivo %s.\n", arquivo);
        exit(1);
    }

    PESSOA cadastro;
    int n;
    printf("Quantos registros deseja cadastrar em %s? ", arquivo);
    scanf("%d", &n);
    fflush(stdin);

    for (int i = 1; i <= n; i++) {
        printf("\nRegistro %d:\n", i);

        printf("Sexo (M/F): ");
        fgets(cadastro.sexo, sizeof(cadastro.sexo), stdin);
        cadastro.sexo[strcspn(cadastro.sexo, "\n")] = '\0';

        printf("Idade: ");
        scanf("%d", &cadastro.idade);
        fflush(stdin);

        printf("Salario: ");
        scanf("%lf", &cadastro.salario);
        fflush(stdin);

        printf("Estado civil: ");
        fgets(cadastro.estadoCivil, sizeof(cadastro.estadoCivil), stdin);
        cadastro.estadoCivil[strcspn(cadastro.estadoCivil, "\n")] = '\0';

        printf("Número de dependentes: ");
        scanf("%d", &cadastro.dependentes);
        fflush(stdin);

        printf("Patrimonio: ");
        scanf("%lf", &cadastro.patrimonio);
        fflush(stdin);

        printf("Calorias absorvidas por dia: ");
        scanf("%d", &cadastro.calorias);
        fflush(stdin);

        printf("Grau de instrução: ");
        fgets(cadastro.grauInstrucao, sizeof(cadastro.grauInstrucao), stdin);
        cadastro.grauInstrucao[strcspn(cadastro.grauInstrucao, "\n")] = '\0';

        cadastro.existe = 1;
        fwrite(&cadastro, sizeof(PESSOA), 1, arq);
    }
    fclose(arq);
}

void listarArquivo(const char *arquivo) {
    FILE *arq;
    if((arq = fopen(arquivo, "rb")) == NULL){
        printf("Arquivo %s nao existe.\n", arquivo);
        exit(1);
    }

    PESSOA p;
    printf("\n--- Conteudo de %s ---\n\n", arquivo);
    while(fread(&p, sizeof(PESSOA), 1, arq) == 1){
        if(p.existe){
            printf("Sexo: %s | Idade: %d | Salario: %.2lf | Estado civil: %s | Dependentes: %d | Patrimonio: %.2lf | Calorias: %d | Grau instrucao: %s\n", p.sexo, p.idade, p.salario, p.estadoCivil, p.dependentes, p.patrimonio, p.calorias, p.grauInstrucao);
        }
    }
    fclose(arq);
}

void intercalarArquivos(const char *a1, const char *a2, const char *a3, const char *saida) {
    FILE *arq1 = fopen(a1, "rb");
    FILE *arq2 = fopen(a2, "rb");
    FILE *arq3 = fopen(a3, "rb");
    FILE *arqOut = fopen(saida, "wb");

    if(!arq1 || !arq2 || !arq3 || !arqOut){
        printf("Erro ao abrir algum dos arquivos.\n");
        exit(1);
    }

    PESSOA todos[MAX_REGISTROS];
    int total = 0;
    PESSOA p;

    while(fread(&p, sizeof(PESSOA), 1, arq1) == 1 && total < MAX_REGISTROS){
        if(p.existe){
            todos[total++] = p;
        } 
    }
    while(fread(&p, sizeof(PESSOA), 1, arq2) == 1 && total < MAX_REGISTROS){
        if(p.existe){
            todos[total++] = p;
        } 
    }
    while(fread(&p, sizeof(PESSOA), 1, arq3) == 1 && total < MAX_REGISTROS) {
        if(p.existe){
            todos[total++] = p;
        } 
    }

    fclose(arq1);
    fclose(arq2);
    fclose(arq3);

    for(int i = 0; i < total - 1; i++){
        int min = i;
        for(int j = i + 1; j < total; j++){
            if(todos[j].idade < todos[min].idade){
                min = j;
            }
        }
        if(min != i){
            PESSOA temp = todos[i];
            todos[i] = todos[min];
            todos[min] = temp;
        }
    }

    for(int i = 0; i < total; i++){
        fwrite(&todos[i], sizeof(PESSOA), 1, arqOut);
    }
    fclose(arqOut);

    printf("\nArquivos intercalados e ordenados por idade em %s.\n", saida);
}
void criarAgenda(const char *arquivo) {
    FILE *arq;
    if((arq = fopen(arquivo, "a+b")) == NULL){
        printf("Erro ao abrir o arquivo %s.\n", arquivo);
        exit(1);
    }

    CONTATO cadastro;
    int n;

    printf("Quantos contatos deseja cadastrar? ");
    scanf("%d", &n);
    fflush(stdin);

    for (int i = 1; i <= n; i++) {
        printf("\nContato %d:\n", i);

        printf("Nome: ");
        fgets(cadastro.nome, sizeof(cadastro.nome), stdin);
        cadastro.nome[strcspn(cadastro.nome, "\n")] = '\0';

        printf("Rua: ");
        fgets(cadastro.rua, sizeof(cadastro.rua), stdin);
        cadastro.rua[strcspn(cadastro.rua, "\n")] = '\0';

        printf("Número: ");
        scanf("%d", &cadastro.numero);
        fflush(stdin);

        printf("Telefone: ");
        fgets(cadastro.telefone, sizeof(cadastro.telefone), stdin);
        cadastro.telefone[strcspn(cadastro.telefone, "\n")] = '\0';

        printf("Cidade: ");
        fgets(cadastro.cidade, sizeof(cadastro.cidade), stdin);
        cadastro.cidade[strcspn(cadastro.cidade, "\n")] = '\0';

        printf("Estado: ");
        fgets(cadastro.estado, sizeof(cadastro.estado), stdin);
        cadastro.estado[strcspn(cadastro.estado, "\n")] = '\0';

        cadastro.existe = 1;
        fwrite(&cadastro, sizeof(CONTATO), 1, arq);
    }

    fclose(arq);
}

void listarAgenda(const char *arquivo){
    FILE *arq;
    CONTATO cadastro;

    if((arq = fopen(arquivo, "rb")) == NULL){
        printf("Arquivo %s nao existe.\n", arquivo);
        exit(1);
    }

    printf("\n--- Contatos cadastrados ---\n\n");

    while((fread(&cadastro, sizeof(CONTATO), 1, arq)) == 1){
        if(cadastro.existe){
            printf("Nome: %s\nRua: %s\nNúmero: %d\nTelefone: %s\nCidade: %s\nEstado: %s\n\n",
                   cadastro.nome, cadastro.rua, cadastro.numero,
                   cadastro.telefone, cadastro.cidade, cadastro.estado);
        }
    }

    fclose(arq);
}

void removerContato(const char *arquivo, const char *nome){
    FILE *arq, *aux;
    CONTATO cadastro;
    int removido = 0;

    if((arq = fopen(arquivo, "rb")) == NULL){
        printf("Arquivo %s nao existe.\n", arquivo);
        exit(1);
    }

    if((aux = fopen("aux.bak", "wb")) == NULL){
        printf("Erro ao criar arquivo auxiliar.\n");
        fclose(arq);
        exit(1);
    }

    while((fread(&cadastro, sizeof(CONTATO), 1, arq)) == 1){
        if(cadastro.existe && strcmp(cadastro.nome, nome) == 0){
            cadastro.existe = 0;
            removido = 1;
            printf("Contato '%s' removido.\n", nome);
        }
        fwrite(&cadastro, sizeof(CONTATO), 1, aux);
    }

    fclose(arq);
    fclose(aux);

    remove(arquivo);
    rename("aux.bak", arquivo);

    if(!removido){
        printf("Contato '%s' nao encontrado.\n", nome);
    }
}
void criarArquivo(const char *arquivo) {
    FILE *arq;
    if ((arq = fopen(arquivo, "w+b")) == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", arquivo);
        exit(1);
    }

    TELEFONE cadastro;
    int n;

    printf("Quantos registros deseja cadastrar em %s? ", arquivo);
    scanf("%d", &n);
    fflush(stdin);

    for(int i = 1; i <= n; i++){
        printf("Digite o telefone %d: ", i);
        fgets(cadastro.telefone, sizeof(cadastro.telefone), stdin);
        cadastro.telefone[strcspn(cadastro.telefone, "\n")] = '\0';

        printf("Digite a cidade %d: ", i);
        fgets(cadastro.cidade, sizeof(cadastro.cidade), stdin);
        cadastro.cidade[strcspn(cadastro.cidade, "\n")] = '\0';

        printf("Digite o tempo de ligacao %d (em minutos): ", i);
        scanf("%lf", &cadastro.tempoLigacao);
        fflush(stdin);

        cadastro.existe = 1;
        fwrite(&cadastro, sizeof(TELEFONE), 1, arq);
        printf("\n");
    }

    fclose(arq);
}

void listarComuns(const char *arquivo1, const char *arquivo2) {
    FILE *arq1, *arq2;
    TELEFONE t1, t2;

    if((arq1 = fopen(arquivo1, "rb")) == NULL){
        printf("Arquivo %s nao existe.\n", arquivo1);
        exit(1);
    }

    if ((arq2 = fopen(arquivo2, "rb")) == NULL) {
        printf("Arquivo %s nao existe.\n", arquivo2);
        fclose(arq1);
        exit(1);
    }

    printf("\n--- Telefones das cidades em comum ---\n\n");

    while((fread(&t1, sizeof(TELEFONE), 1, arq1)) == 1){
        if(t1.existe){
            rewind(arq2);
            while((fread(&t2, sizeof(TELEFONE), 1, arq2)) == 1){
                if(t2.existe && strcmp(t1.cidade, t2.cidade) == 0){
                    printf("Cidade: %s | Telefone1: %s | Telefone2: %s\n", t1.cidade, t1.telefone, t2.telefone);
                }  
            }
        }
    }

    fclose(arq1);
    fclose(arq2);
}
void listarTurma(const char *arquivo){
    FILE *arq;
    TURMA cadastro;

    if((arq = fopen(arquivo, "rb")) == NULL){
        printf("Arquivo %s nao existe.\n", arquivo);
        return;
    }

    printf("\n--- Alunos cadastrados em %s ---\n\n", arquivo);

    while((fread(&cadastro, sizeof(TURMA), 1, arq)) == 1){
        if(cadastro.existe){
            printf("Nome: %s\nIdade: %d\nNota: %.2lf\n\n", cadastro.nome, cadastro.idade, cadastro.nota);
        }
    }

    fclose(arq);
}


void juntar(){
    FILE *arq1, *arq2, *aux;
    TURMA c;
    if((arq1 = fopen("turmaA.bin", "r+b")) == NULL){
        printf("Arquivo nao exite.\n");
        exit(1);
    }
    if((arq2 = fopen("turmaB.bin", "r+b")) == NULL){
        printf("Arquivo nao exite.\n");
        exit(1);
    }
    if((aux = fopen("aux.bak", "w+b")) == NULL){
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    while((fread(&c, sizeof(TURMA), 1, arq1)) == 1){
        if(c.existe){
            fwrite(&c, sizeof(TURMA), 1, aux);
        }
    }
    while((fread(&c, sizeof(TURMA), 1, arq2)) == 1){
        if(c.existe){
            fwrite(&c, sizeof(TURMA), 1, aux);
        }
    }
    printf("Arquivos turmaA.bin e turmaB.bin foram unidos em turmaAB.bin.\n");

    fclose(arq1);
    fclose(arq2);
    fclose(aux);

    remove("turmaA.bin");
    remove("turmaB.bin");
    rename("aux.bak", "turmaAB.bin");
    
}
void criarturma(){
    FILE *arq;
    for(int t = 1; t <= 2; t++){
        char turma[20];
        if(t == 1){
            strcpy(turma, "turmaA.bin");
        }
        else{
             strcpy(turma, "turmaB.bin");
        }
        
        if((arq = fopen(turma, "r+b")) == NULL){
            if((arq = fopen(turma, "w+b")) == NULL){
                printf("Erro ao abrir o arquivo.\n");
                exit(1);
            }
        }
        TURMA cadastro;
        printf("Digite os dados de 5 alunos da %s:\n", turma);
        for(int i = 1; i <= 5; i++){
            printf("Digite o nome do aluno %d: \n", i);
            fgets(cadastro.nome, sizeof(cadastro.nome), stdin);
            cadastro.nome[strcspn(cadastro.nome, "\n")] = '\0';
            
            printf("Digite a idade da aluno %d: \n", i);
            scanf(" %d", &cadastro.idade);
            fflush(stdin);

            printf("Digite a nota do aluno %d: \n", i);
            scanf(" %lf", &cadastro.nota);
            fflush(stdin);
            printf("\n");
            
            cadastro.existe = 1;
            fwrite(&cadastro, sizeof(TURMA), 1, arq);
        }
        fclose(arq);
    }
}
void deletar_2(){
    FILE *arq, *aux;
    PESSOA c;
    if((arq = fopen("pessoas.bin", "r+b")) == NULL){
        printf("Arquivo nao exite.\n");
        exit(1);
    }
    if((aux = fopen("aux.bak", "wb")) == NULL){
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    int i = 1;
    while((fread(&c, sizeof(PESSOA), 1, arq)) == 1){
        if(c.existe && i == 2){
            c.existe = 0;
            printf("Pessoa 2 deletada.\n");
        }
        if(c.existe){
            fwrite(&c, sizeof(PESSOA), 1, aux);
        }
        i++;
    }
    fclose(arq);
    fclose(aux);

    remove("pessoas.bin");
    rename("aux.bak", "pessoas.bin");
}
void criar(){
    FILE *arq;
    if((arq = fopen("dados.bin", "r+b")) == NULL){
        if((arq = fopen("dados.bin", "w+b")) == NULL){
            printf("Erro ao abrir o arquivo.\n");
            exit(1);
        }
    }
    int n;
    printf("Digite 5 numeros: \n");
    for(int i = 0; i < 5; i++){
        scanf(" %d", &n);
        fwrite(&n, sizeof(n), 1, arq);
    }
    fclose(arq);
}

void listar(){
    FILE *arq;
    if((arq = fopen("dados.bin", "rb")) == NULL){
        printf("Arquivo nao exite.\n");
        exit(1);
    }
    int n;
    while((fread(&n, sizeof(n), 1, arq)) == 1){
        printf("%d ", n);
    }
    printf("\n");
    fclose(arq);
}
ex2(){
    criar();
    listar();
    return 0;
}
ex4(){
	FILE *arq;

    if((arq = fopen("dados.bin", "rb")) == NULL){
        printf("Arquivo 'dados.bin' nao encontrado.\n");
    }
    else{
        printf("Arquivo 'dados.bin' existe.\n");
        fclose(arq);
    }
    return 0;
}
ex6a8(){
	criar();
    listar();
    deletar_2();
    printf("\n\n---- NOVA LISTAGEM! ----\n");
    listar();
    return 0;
}
ex10a12(){
    criarturma();
    listarTurma("turmaA.bin");
    listarTurma("turmaB.bin");
    juntar();
    listarTurma("turmaAB.bin");
    return 0;
}
ex14(){
    criarArquivo("arquivo1.bin");
    criarArquivo("arquivo2.bin");

    listarComuns("arquivo1.bin", "arquivo2.bin");

    return 0;
}
ex16(){
    criarAgenda("agenda.bin");
    listarAgenda("agenda.bin");

    char nomeRemover[101];
    printf("Digite o nome do contato a ser removido: ");
    fgets(nomeRemover, sizeof(nomeRemover), stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    removerContato("agenda.bin", nomeRemover);

    printf("\n--- Agenda atualizada ---\n");
    listarAgenda("agenda.bin");

    return 0;
}
ex18(){
	    criarArquivo18("regiao1.bin");
    criarArquivo18("regiao2.bin");
    criarArquivo18("regiao3.bin");

    listarArquivo("regiao1.bin");
    listarArquivo("regiao2.bin");
    listarArquivo("regiao3.bin");

    intercalarArquivos("regiao1.bin", "regiao2.bin", "regiao3.bin", "intercalado.bin");

    listarArquivo("intercalado.bin");

    return 0;
}
ex20(){
	    criarNumeros();
    listarArquivo20("numeros.bin");

    copiarParesOrdenados();
    listarArquivo20("pares.bin");

    return 0;
}
ex22(){
	    criarFonte();
    listarArquivo22("FONTE.bin");

    copiarFonteNova();
    listarArquivo22("FONTENOVA.bin");

    return 0;
}
ex24(){
	criarArquivo24();
    listarArquivo("homens.dat");
    listarArquivo("mulheres.dat");
    return 0;
}
ex26(){
	    cadastrarDisciplinas("disciplinas.bin");
    cadastrarAlunos("alunos.bin");
    gerarPrematricula("alunos.bin", "disciplinas.bin", "prematricula.bin");
    listarArquivoPrematricula("prematricula.bin");
    return 0;
}
ex28(){
	int main(){
    const char *arquivo = "alunos.dat";
    int opc, num;

    do{
        printf("\n--- Menu ---\n");
        printf("1. Cadastrar aluno\n");
        printf("2. Consultar aluno\n");
        printf("3. Alterar aluno\n");
        printf("4. Excluir aluno\n");
        printf("5. Listar alunos\n");
        printf("6. Deletar Arquivo\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opc);
        fflush(stdin);

        switch(opc){
            case 1: 
                cadastrarAluno(arquivo); 
                break;
            case 2:
                printf("Digite o número do aluno: "); 
                scanf("%d", &num);
                consultarAluno(arquivo, num);
                break;
            case 3:
                printf("Digite o número do aluno: "); 
                scanf("%d", &num);
                alterarAluno(arquivo, num);
                break;
            case 4:
                printf("Digite o número do aluno: "); 
                scanf("%d", &num);
                excluirAluno(arquivo, num);
                break;
            case 5: 
                listarAlunos(arquivo); 
                break;
            case 6: 
                remove("alunos.dat");
                break;
            case 0: 
                printf("Saindo...\n"); 
                break;
            default: 
                printf("Opção inválida!\n");
                break;
        }
    }while(opc != 0);

    return 0;
}
}
ex30(){
	    FILE *arqSal, *arqDesc, *arqOut;
    float salBruto[MAX_FUNC], desc[MAX_FUNC], salLiq[MAX_FUNC];
    int n = 0;

    if((arqSal = fopen("salbruto.bin", "rb")) == NULL){
        printf("Erro ao abrir salbruto.bin\n");
        exit(1);
    }
    if((arqDesc = fopen("desc.bin", "rb")) == NULL){
        printf("Erro ao abrir desc.bin\n");
        fclose(arqSal);
        exit(1);
    }

    while(fread(&salBruto[n], sizeof(float), 1, arqSal) == 1 && fread(&desc[n], sizeof(float), 1, arqDesc) == 1){
        n++;
        if(n >= MAX_FUNC){
            break;
        }
    }

    fclose(arqSal);
    fclose(arqDesc);

    for(int i = 0; i < n; i++){
        salLiq[i] = salBruto[i] - desc[i];
    }

    if((arqOut = fopen("salliq.txt", "w")) == NULL){
        printf("Erro ao criar salliq.txt\n");
        exit(1);
    }

    fprintf(arqOut, "Funcionario | Salario Bruto | Desconto | Salario Liquido\n");
    fprintf(arqOut, "--------------------------------------------------------\n");
    for(int i = 0; i < n; i++){
        fprintf(arqOut, "%3d         | %.2f        | %.2f    | %.2f\n", i+1, salBruto[i], desc[i], salLiq[i]);
    }
    fclose(arqOut);

    printf("Arquivo salliq.txt gerado com sucesso!\n");
    return 0;
}
ex32(){
	int main(){
    Aluno alunos[MAX];
    int n, opcao;
    int sair = 0;

    carregarAlunos(alunos, &n);

    while(sair == 0){
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1 - Pesquisa por matrícula\n");
        printf("2 - Pesquisa por nome\n");
        printf("3 - Fim\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        fflush(stdin);

        switch (opcao) {
            case 1:
                pesquisaPorMatricula(alunos, n);
                break;
            case 2:
                pesquisaPorNome(alunos, n);
                break;
            case 3:
                printf("Encerrando programa...\n");
                sair = 1;
                break;
            default:
                printf("Opção inválida.\n");
                break;
        }
    }

    return 0;
}
}
ex34(){
    const char *arquivo = "despensa.bin";
    int opc = 0;
    int sair = 0;

    while(!sair) {
        printf("\n=== MENU ===\n");
        printf("1 - Adicionar produto\n");
        printf("2 - Entrada de produto\n");
        printf("3 - Retirada de produto\n");
        printf("4 - Relatório geral\n");
        printf("5 - Produtos não disponíveis\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opc);
        fflush(stdin);

        switch(opc){
            case 1:
                adicionarProduto(arquivo);
                break;
            case 2:
                entradaProduto(arquivo);
                break;
            case 3:
                retiradaProduto(arquivo);
                break;
            case 4:
                relatorioGeral(arquivo);
                break;
            case 5:
                relatorioIndisponivel(arquivo);
                break;
            case 0:
                printf("Saindo...\n");
                sair = 1;
                break;
            default:
                printf("Opção inválida.\n");
                break;
        }
    }
    return 0;
}
ex36(){
	    Conta contas[MAX_CONTAS];
    int nContas = 0;

    int removidas[MAX_REMOVIDAS];
    int nRemovidas = 0;

    Movimentacao mov;

    FILE *fContas = fopen("contas_ant.bin", "rb");
    if(fContas){
        nContas = 0;
        while(fread(&contas[nContas], sizeof(Conta), 1, fContas) == 1 && nContas < MAX_CONTAS){
            nContas++;
        }
        fclose(fContas);
    }

    FILE *fMov = fopen("mov.bin", "rb");
    if(fMov){
        while(fread(&mov, sizeof(Movimentacao), 1, fMov) == 1){
            int idx = encontrarConta(contas, nContas, mov.numero);
            if(idx != -1){
                if(mov.tipo == 'C'){
                    contas[idx].saldo += mov.valor;
                }
                else if(mov.tipo == 'D'){
                    contas[idx].saldo -= mov.valor;
                }
            }
        }
        fclose(fMov);
    }

    FILE *fNovas = fopen("novas_contas.bin", "rb");
    if(fNovas){
        while(fread(&contas[nContas], sizeof(Conta), 1, fNovas) == 1 && nContas < MAX_CONTAS){
            nContas++;
        }
        fclose(fNovas);
    }

    FILE *fRem = fopen("removidas.bin", "rb");
    if(fRem){
        nRemovidas = 0;
        while(fread(&removidas[nRemovidas], sizeof(int), 1, fRem) == 1 && nRemovidas < MAX_REMOVIDAS){
            nRemovidas++;
        }
        fclose(fRem);
    }

    FILE *fAtual = fopen("contas_atualizadas.bin", "wb");
    if(fAtual){
        int i = 0;
        while(i < nContas){
            if(!contaRemovida(removidas, nRemovidas, contas[i].numero)){
                fwrite(&contas[i], sizeof(Conta), 1, fAtual);
            }
            i++;
        }
        fclose(fAtual);
    }

    printf("Atualização concluída!\n");
    return 0;
}
ex38(){
	    FILE *arq = fopen("resposta.bin", "rb");
    if (!arq) {
        printf("Erro ao abrir arquivo resposta.bin\n");
        return 1;
    }

    Pessoa p;
    int total = 0;
    int totalFumantes = 0;

    int totalHomens = 0;
    int homensNaoFumantesAbaixo40 = 0;

    int totalMulheres = 0;
    int mulheresFumantesAcima40 = 0;

    while (fread(&p, sizeof(Pessoa), 1, arq) == 1) {
        total++;
        if(p.fumante == 'S' || p.fumante == 's'){
            totalFumantes++;
        }

        if(p.sexo == 'M' || p.sexo == 'm'){
            totalHomens++;
            if((p.fumante == 'N' || p.fumante == 'n') && p.idade < 40){
                homensNaoFumantesAbaixo40++;
            }
        }

        if(p.sexo == 'F' || p.sexo == 'f'){
            totalMulheres++;
            if((p.fumante == 'S' || p.fumante == 's') && p.idade > 40){
                mulheresFumantesAcima40++;
            }
        }
    }
    fclose(arq);

    if(total > 0){
        printf("Percentual de fumantes: %.2f%%\n", 100.0 * totalFumantes / total);
    } 
    else{
        printf("Nenhuma pessoa entrevistada.\n");
    }

    if(totalHomens > 0){
        printf("Percentual de homens não fumantes abaixo de 40 anos: %.2f%%\n", 100.0 * homensNaoFumantesAbaixo40 / totalHomens);
    } 
    else{
        printf("Nenhum homem entrevistado.\n");
    }

    if(totalMulheres > 0){
        printf("Percentual de mulheres fumantes acima de 40 anos: %.2f%%\n", 100.0 * mulheresFumantesAcima40 / totalMulheres);
    }
    else{
        printf("Nenhuma mulher entrevistada.\n");
    }

    return 0;
}