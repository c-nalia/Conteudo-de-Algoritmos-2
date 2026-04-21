#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REGISTROS 500
#define MAX_NUMEROS 500
#define MAX_DISC 50
#define MAX_ALUNOS 200
#define MAX_CURSADAS 7
#define MAX_PREMATR 7
#define MAX_FUNC 100
#define MAX 100
#define MAX_CONTAS 200
#define MAX_REMOVIDAS 200

typedef struct { int dia, mes, ano; } Data;

typedef struct {
    int numero;
    char nome[50];
    double saldo;
} Conta;

typedef struct {
    int numero;
    char tipo;
    double valor;
} Movimentacao;

typedef struct {
    int codigo;
    char nome[100];
    char preReq[100];
} Materia;

typedef struct {
    int matricula;
    char nome[101];
    char curso[50];
    int semestre;
    char disciplinas_cursadas[MAX_CURSADAS][100];
    int totalCursadas;
} AlunoInfo;

typedef struct {
    int numero;
    char nome[101];
    char curso[50];
    double p1, p2, mt;
    double frequencia;
    int existe;
} AlunoNota;

typedef struct {
    int matricula;
    char nome[101];
    char curso[50];
    int semestre;
    char disciplinas_liberadas[MAX_PREMATR][100];
} PreMat;

typedef struct {
    int codigo;
    char descricao[50];
    int quantidade;
} Produto;

typedef struct {
    char nome[101];
    char corOlhos[20];
    double peso;
    Data nascimento;
} Resumo;

typedef struct {
    int chave;
    char info[101];
    Data data;
    int existe;
} RegistroFonte;

typedef struct{
    char nome[101];
    int idade;
    double nota;
    int existe;
} TurmaAluno;

typedef struct{
    char nome[101];
    int idade;
    double altura;
    int existe;
} PessoaF;

typedef struct{
    char telefone[20];
    char cidade[50];
    double tempoLigacao;
    int existe;
} TelefoneF;

typedef struct {
    char nome[101];
    char rua[101];
    int numero;
    char telefone[20];
    char cidade[50];
    char estado[4];
    int existe;
} Contato;

typedef struct {
    char sexo[4];
    int idade;
    double salario;
    char estadoCivil[20];
    int dependentes;
    double patrimonio;
    int calorias;
    char grauInstrucao[30];
    int existe;
} PessoaComplex;

/* utilitários de entrada */
static void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}
static void ler_string(const char *prompt, char *buf, size_t tam) {
    printf("%s", prompt);
    if(fgets(buf, (int)tam, stdin) == NULL) { buf[0] = '\0'; return; }
    buf[strcspn(buf, "\n")] = '\0';
}

/* ---------- produtos (despensa) ---------- */
void incluirProduto(const char *path){
    FILE *f = fopen(path, "ab");
    if(!f){ printf("erro ao abrir %s\n", path); return; }
    Produto p;
    printf("codigo: "); scanf("%d", &p.codigo); limpar_buffer();
    ler_string("descricao: ", p.descricao, sizeof p.descricao);
    printf("quantidade inicial: "); scanf("%d", &p.quantidade); limpar_buffer();
    fwrite(&p, sizeof p, 1, f);
    fclose(f);
    printf("produto cadastrado\n");
}

void entradaNoEstoque(const char *path){
    FILE *f = fopen(path, "r+b");
    if(!f){ printf("erro ao abrir %s\n", path); return; }
    int cod, qtd; printf("codigo: "); scanf("%d", &cod); limpar_buffer();
    printf("quantidade a adicionar: "); scanf("%d", &qtd); limpar_buffer();
    Produto p; int achou = 0;
    while(fread(&p, sizeof p, 1, f) == 1){
        if(p.codigo == cod){ p.quantidade += qtd; fseek(f, -sizeof p, SEEK_CUR); fwrite(&p, sizeof p, 1, f); printf("nova qtd de %s: %d\n", p.descricao, p.quantidade); achou = 1; break; }
    }
    if(!achou) printf("produto nao encontrado\n");
    fclose(f);
}

void retirardaDoEstoque(const char *path){
    FILE *f = fopen(path, "r+b");
    if(!f){ printf("erro ao abrir %s\n", path); return; }
    int cod, qtd; printf("codigo: "); scanf("%d", &cod); limpar_buffer();
    printf("quantidade a retirar: "); scanf("%d", &qtd); limpar_buffer();
    Produto p; int achou = 0;
    while(fread(&p, sizeof p, 1, f) == 1){
        if(p.codigo == cod){
            if(p.quantidade >= qtd){ p.quantidade -= qtd; fseek(f, -sizeof p, SEEK_CUR); fwrite(&p, sizeof p, 1, f); printf("nova qtd de %s: %d\n", p.descricao, p.quantidade); }
            else printf("estoque insuficiente: %d\n", p.quantidade);
            achou = 1; break;
        }
    }
    if(!achou) printf("produto nao encontrado\n");
    fclose(f);
}

void relatorioTodos(const char *path){
    FILE *f = fopen(path, "rb");
    if(!f){ printf("erro ao abrir %s\n", path); return; }
    Produto p;
    printf("\n--- relatorio geral ---\n");
    while(fread(&p, sizeof p, 1, f) == 1) printf("cod: %d | %s | qtd: %d\n", p.codigo, p.descricao, p.quantidade);
    fclose(f);
}

void relatorioIndisponiveis(const char *path){
    FILE *f = fopen(path, "rb");
    if(!f){ printf("erro ao abrir %s\n", path); return; }
    Produto p; int any = 0;
    printf("\n--- produtos sem estoque ---\n");
    while(fread(&p, sizeof p, 1, f) == 1){
        if(p.quantidade == 0){ printf("cod: %d | %s\n", p.codigo, p.descricao); any = 1; }
    }
    if(!any) printf("todos disponiveis\n");
    fclose(f);
}

/* ---------- alunos com notas (arquivo) ---------- */
void cadastrarAlunosNotas(const char *path){
    FILE *f = fopen(path, "ab");
    if(!f){ printf("erro ao abrir %s\n", path); return; }
    int n; printf("quantos alunos cadastrar? "); scanf("%d", &n); limpar_buffer();
    for(int i=0;i<n;i++){
        AlunoNota a; a.existe = 1;
        printf("\naluno %d\nnumero: ", i+1); scanf("%d", &a.numero); limpar_buffer();
        ler_string("nome: ", a.nome, sizeof a.nome);
        ler_string("curso: ", a.curso, sizeof a.curso);
        printf("p1: "); scanf("%lf", &a.p1);
        printf("p2: "); scanf("%lf", &a.p2);
        printf("mt: "); scanf("%lf", &a.mt);
        printf("frequencia (%%): "); scanf("%lf", &a.frequencia); limpar_buffer();
        fwrite(&a, sizeof a, 1, f);
    }
    fclose(f);
    printf("alunos cadastrados\n");
}

void consultarAlunoNotas(const char *path, int numero){
    FILE *f = fopen(path, "rb");
    if(!f){ printf("erro ao abrir %s\n", path); return; }
    AlunoNota a; int found = 0;
    while(fread(&a, sizeof a, 1, f) == 1){
        if(a.existe && a.numero == numero){
            double mp = (a.p1 + a.p2)/2.0;
            double mf = 0.8*mp + 0.2*a.mt;
            printf("\nnumero: %d\nnome: %s\ncurso: %s\nmedia final: %.2lf\nfrequencia: %.2lf%%\ncond: %s\n", a.numero, a.nome, a.curso, mf, a.frequencia, (mf>=4.95 && a.frequencia>=70) ? "Aprovado" : "Reprovado");
            found = 1; break;
        }
    }
    if(!found) printf("aluno nao encontrado\n");
    fclose(f);
}

void alterarAlunoNotas(const char *path, int numero){
    FILE *f = fopen(path, "r+b");
    if(!f){ printf("erro ao abrir %s\n", path); return; }
    AlunoNota a; int found = 0;
    while(fread(&a, sizeof a, 1, f) == 1){
        if(a.existe && a.numero == numero){
            printf("alterando %s\n", a.nome);
            printf("nova p1: "); scanf("%lf", &a.p1);
            printf("nova p2: "); scanf("%lf", &a.p2);
            printf("nova mt: "); scanf("%lf", &a.mt);
            printf("nova frequencia: "); scanf("%lf", &a.frequencia); limpar_buffer();
            fseek(f, -sizeof a, SEEK_CUR); fwrite(&a, sizeof a, 1, f);
            printf("alterado\n");
            found = 1; break;
        }
    }
    if(!found) printf("aluno nao encontrado\n");
    fclose(f);
}

void excluirAlunoNotas(const char *path, int numero){
    FILE *f = fopen(path, "rb");
    FILE *aux = fopen("aux_alunos.bin", "wb");
    if(!f || !aux){ printf("erro ao abrir arquivos\n"); if(f) fclose(f); if(aux) fclose(aux); return; }
    AlunoNota a; int found = 0;
    while(fread(&a, sizeof a, 1, f) == 1){
        if(a.existe && a.numero == numero){ a.existe = 0; found = 1; }
        if(a.existe) fwrite(&a, sizeof a, 1, aux);
    }
    fclose(f); fclose(aux);
    remove(path); rename("aux_alunos.bin", path);
    printf(found ? "aluno excluido\n" : "aluno nao encontrado\n");
}

void listarAlunosNotas(const char *path){
    FILE *f = fopen(path, "rb");
    if(!f){ printf("erro ao abrir %s\n", path); return; }
    AlunoNota a;
    printf("\n--- lista alunos ---\n");
    while(fread(&a, sizeof a, 1, f) == 1){
        if(a.existe){
            double mp = (a.p1 + a.p2)/2.0;
            double mf = 0.8*mp + 0.2*a.mt;
            printf("num: %d | nome: %s | media final: %.2lf | freq: %.2lf%% | %s\n", a.numero, a.nome, mf, a.frequencia, (mf>=4.95 && a.frequencia>=70) ? "Aprovado":"Reprovado");
        }
    }
    fclose(f);
}

/* ---------- disciplinas e pré-matrícula ---------- */
void cadastrarMaterias(const char *path){
    FILE *f = fopen(path, "wb");
    if(!f){ printf("erro ao abrir %s\n", path); return; }
    int n; printf("quantas materias? "); scanf("%d", &n); limpar_buffer();
    for(int i=0;i<n;i++){
        Materia m;
        printf("codigo: "); scanf("%d", &m.codigo); limpar_buffer();
        ler_string("nome: ", m.nome, sizeof m.nome);
        ler_string("pre-req (digite vazio se nao): ", m.preReq, sizeof m.preReq);
        fwrite(&m, sizeof m, 1, f);
    }
    fclose(f);
    printf("materias cadastradas\n");
}

void cadastrarAlunosInfo(const char *path){
    FILE *f = fopen(path, "wb");
    if(!f){ printf("erro ao abrir %s\n", path); return; }
    int n; printf("quantos alunos? "); scanf("%d", &n); limpar_buffer();
    for(int i=0;i<n;i++){
        AlunoInfo a;
        printf("matricula: "); scanf("%d", &a.matricula); limpar_buffer();
        ler_string("nome: ", a.nome, sizeof a.nome);
        ler_string("curso: ", a.curso, sizeof a.curso);
        printf("semestre: "); scanf("%d", &a.semestre); limpar_buffer();
        printf("quantas disciplinas cursadas? (max %d): ", MAX_CURSADAS); scanf("%d", &a.totalCursadas); limpar_buffer();
        for(int j=0;j<a.totalCursadas;j++) { printf("disc %d: ", j+1); fgets(a.disciplinas_cursadas[j], sizeof a.disciplinas_cursadas[j], stdin); a.disciplinas_cursadas[j][strcspn(a.disciplinas_cursadas[j], "\n")] = '\0'; }
        fwrite(&a, sizeof a, 1, f);
    }
    fclose(f);
    printf("alunos info cadastrados\n");
}

void gerarPreMatricula(const char *alunosPath, const char *materiasPath, const char *saidaPath){
    FILE *fa = fopen(alunosPath, "rb");
    FILE *fm = fopen(materiasPath, "rb");
    FILE *fo = fopen(saidaPath, "wb");
    if(!fa || !fm || !fo){ printf("erro ao abrir arquivos\n"); if(fa) fclose(fa); if(fm) fclose(fm); if(fo) fclose(fo); return; }
    AlunoInfo ai;
    Materia m;
    while(fread(&ai, sizeof ai, 1, fa) == 1){
        PreMat p;
        p.matricula = ai.matricula;
        strncpy(p.nome, ai.nome, sizeof p.nome);
        strncpy(p.curso, ai.curso, sizeof p.curso);
        p.semestre = ai.semestre;
        for(int k=0;k<MAX_PREMATR;k++) strcpy(p.disciplinas_liberadas[k], "N/A");
        int totalLib = 0;
        rewind(fm);
        while(fread(&m, sizeof m, 1, fm) == 1 && totalLib < MAX_PREMATR){
            int liberar = 1;
            if(strlen(m.preReq) > 0 && strcmp(m.preReq, "vazio") != 0){
                liberar = 0;
                for(int j=0;j<ai.totalCursadas;j++){
                    if(strcmp(ai.disciplinas_cursadas[j], m.preReq) == 0){ liberar = 1; break; }
                }
            }
            if(liberar) { strncpy(p.disciplinas_liberadas[totalLib++], m.nome, sizeof p.disciplinas_liberadas[0]); }
        }
        fwrite(&p, sizeof p, 1, fo);
    }
    fclose(fa); fclose(fm); fclose(fo);
    printf("arquivo pre-matricula gerado: %s\n", saidaPath);
}

void mostrarPreMat(const char *path){
    FILE *f = fopen(path, "rb");
    if(!f){ printf("arquivo %s nao existe\n", path); return; }
    PreMat p;
    printf("\n--- PRE-MATRICULA ---\n");
    while(fread(&p, sizeof p, 1, f) == 1){
        printf("\naluno: %s | matricula: %d | curso: %s | semestre: %d\n", p.nome, p.matricula, p.curso, p.semestre);
        printf("disciplinas liberadas:\n");
        for(int i=0;i<MAX_PREMATR;i++) printf(" - %s\n", p.disciplinas_liberadas[i]);
    }
    fclose(f);
}

/* ---------- numeros pares (ordenar) ---------- */
void criarNumerosArquivo(){
    FILE *f = fopen("dados_numeros.bin", "wb");
    if(!f){ printf("erro ao criar arquivo\n"); return; }
    int n, val; printf("quantos numeros? "); scanf("%d", &n); limpar_buffer();
    for(int i=1;i<=n;i++){ printf("digite o numero %d: ", i); scanf("%d", &val); fwrite(&val, sizeof val, 1, f); }
    fclose(f);
    printf("arquivo criado\n");
}

void copiarParesOrdenados(){
    FILE *fin = fopen("dados_numeros.bin", "rb");
    FILE *fout = fopen("pares_ordenados.bin", "wb");
    if(!fin || !fout){ printf("erro ao abrir arquivos\n"); if(fin) fclose(fin); if(fout) fclose(fout); return; }
    int pares[MAX_NUMEROS], total=0, num;
    while(fread(&num, sizeof num, 1, fin) == 1) if(num % 2 == 0) pares[total++] = num;
    fclose(fin);
    for(int i=0;i<total-1;i++){
        int min = i;
        for(int j=i+1;j<total;j++) if(pares[j] < pares[min]) min = j;
        if(min != i){ int tmp = pares[i]; pares[i] = pares[min]; pares[min] = tmp; }
    }
    for(int i=0;i<total;i++) fwrite(&pares[i], sizeof pares[i], 1, fout);
    fclose(fout);
    printf("pares copiados e ordenados\n");
}

void listarInteirosArquivo(const char *path){
    FILE *f = fopen(path, "rb");
    if(!f){ printf("arquivo %s nao existe\n", path); return; }
    int v;
    printf("\nconteudo de %s:\n", path);
    while(fread(&v, sizeof v, 1, f) == 1) printf("%d ", v);
    printf("\n");
    fclose(f);
}

/* ---------- registros fonte (copiar) ---------- */
void criarFonte(){
    FILE *f = fopen("FONTE.bin", "wb");
    if(!f){ printf("erro ao criar FONTE.bin\n"); return; }
    int n; printf("quantos registros? "); scanf("%d", &n); limpar_buffer();
    for(int i=1;i<=n;i++){
        RegistroFonte r; printf("chave: "); scanf("%d", &r.chave); limpar_buffer();
        ler_string("informacao: ", r.info, sizeof r.info);
        do{ printf("data (d m a): "); scanf("%d %d %d", &r.data.dia, &r.data.mes, &r.data.ano); limpar_buffer(); } while(r.data.dia<1||r.data.mes<1||r.data.mes>12);
        r.existe = 1;
        fwrite(&r, sizeof r, 1, f);
    }
    fclose(f);
}

void copiarFonteParaNova(){
    FILE *fin = fopen("FONTE.bin", "rb");
    FILE *fout = fopen("FONTENOVA.bin", "wb");
    if(!fin || !fout){ printf("erro ao abrir arquivos\n"); if(fin) fclose(fin); if(fout) fclose(fout); return; }
    RegistroFonte r;
    while(fread(&r, sizeof r, 1, fin) == 1) if(r.existe) fwrite(&r, sizeof r, 1, fout);
    fclose(fin); fclose(fout); remove("FONTE.bin");
    printf("copiado para FONTENOVA.bin\n");
}

void listarResumoArquivo(const char *path){
    FILE *f = fopen(path, "rb");
    if(!f){ printf("arquivo %s nao existe\n", path); return; }
    Resumo r;
    printf("\n--- conteudo de %s ---\n", path);
    while(fread(&r, sizeof r, 1, f) == 1) printf("nome: %s | olhos: %s | peso: %.2lf | nascimento: %02d/%02d/%04d\n", r.nome, r.corOlhos, r.peso, r.nascimento.dia, r.nascimento.mes, r.nascimento.ano);
    fclose(f);
}

/* ---------- arquivo 24 (homens/mulheres) ---------- */
void criarHomensMulheres(){
    FILE *fh = fopen("homens.dat", "wb");
    FILE *fm = fopen("mulheres.dat", "wb");
    if(!fh || !fm){ printf("erro ao abrir arquivos\n"); if(fh) fclose(fh); if(fm) fclose(fm); return; }
    int n; printf("quantos registros? "); scanf("%d", &n); limpar_buffer();
    for(int i=1;i<=n;i++){
        char nome[101], cor[20];
        int sexo;
        double altura, peso;
        Data nasc;
        ler_string("nome: ", nome, sizeof nome);
        do{ printf("sexo (1=masc,2=fem): "); scanf("%d", &sexo); limpar_buffer(); } while(sexo!=1 && sexo!=2);
        ler_string("cor olhos: ", cor, sizeof cor);
        do{ printf("altura (m): "); scanf("%lf", &altura); limpar_buffer(); } while(altura<=0);
        do{ printf("peso (kg): "); scanf("%lf", &peso); limpar_buffer(); } while(peso<=0);
        do{ printf("nascimento d m a: "); scanf("%d %d %d", &nasc.dia, &nasc.mes, &nasc.ano); limpar_buffer(); } while(nasc.mes<1 || nasc.mes>12 || nasc.dia<1);
        Resumo r; strncpy(r.nome, nome, sizeof r.nome); strncpy(r.corOlhos, cor, sizeof r.corOlhos); r.peso = peso; r.nascimento = nasc;
        if(sexo==1) fwrite(&r, sizeof r, 1, fh); else fwrite(&r, sizeof r, 1, fm);
    }
    fclose(fh); fclose(fm);
    printf("arquivos criados\n");
}

/* ---------- agenda/contatos ---------- */
void criarAgenda(const char *path){
    FILE *f = fopen(path, "ab");
    if(!f){ printf("erro ao abrir %s\n", path); return; }
    int n; printf("quantos contatos? "); scanf("%d", &n); limpar_buffer();
    for(int i=0;i<n;i++){
        Contato c; ler_string("nome: ", c.nome, sizeof c.nome);
        ler_string("rua: ", c.rua, sizeof c.rua);
        printf("numero: "); scanf("%d", &c.numero); limpar_buffer();
        ler_string("telefone: ", c.telefone, sizeof c.telefone);
        ler_string("cidade: ", c.cidade, sizeof c.cidade);
        ler_string("estado (UF): ", c.estado, sizeof c.estado);
        c.existe = 1;
        fwrite(&c, sizeof c, 1, f);
    }
    fclose(f);
    printf("agenda salva\n");
}

void listarAgenda(const char *path){
    FILE *f = fopen(path, "rb");
    if(!f){ printf("arquivo %s nao existe\n", path); return; }
    Contato c;
    printf("\n--- contatos ---\n");
    while(fread(&c, sizeof c, 1, f) == 1){
        if(c.existe) printf("nome: %s\nrua: %s\nnum: %d\nfone: %s\ncidade: %s\nestado: %s\n\n", c.nome, c.rua, c.numero, c.telefone, c.cidade, c.estado);
    }
    fclose(f);
}

void removerContato(const char *path, const char *nomeRem){
    FILE *f = fopen(path, "rb");
    FILE *aux = fopen("aux_cont.bin", "wb");
    if(!f || !aux){ printf("erro ao abrir arquivos\n"); if(f) fclose(f); if(aux) fclose(aux); return; }
    Contato c; int removed = 0;
    while(fread(&c, sizeof c, 1, f) == 1){
        if(c.existe && strcmp(c.nome, nomeRem) == 0){ c.existe = 0; removed = 1; printf("removido %s\n", nomeRem); }
        fwrite(&c, sizeof c, 1, aux);
    }
    fclose(f); fclose(aux); remove(path); rename("aux_cont.bin", path);
    if(!removed) printf("contato nao encontrado\n");
}

/* ---------- turmas e juntar ---------- */
void criarTurmasPadrao(){
    for(int t=0;t<2;t++){
        char nomeArq[20];
        sprintf(nomeArq, "turma%c.bin", t==0 ? 'A' : 'B');
        FILE *f = fopen(nomeArq, "ab");
        if(!f) { printf("erro ao abrir %s\n", nomeArq); continue; }
        TurmaAluno reg;
        printf("digitando 5 alunos para %s\n", nomeArq);
        limpar_buffer();
        for(int i=1;i<=5;i++){
            ler_string("nome: ", reg.nome, sizeof reg.nome);
            printf("idade: "); scanf("%d", &reg.idade); limpar_buffer();
            printf("nota: "); scanf("%lf", &reg.nota); limpar_buffer();
            reg.existe = 1;
            fwrite(&reg, sizeof reg, 1, f);
        }
        fclose(f);
    }
    printf("turmas criadas\n");
}

void listarTurmaArquivo(const char *path){
    FILE *f = fopen(path, "rb");
    if(!f){ printf("arquivo %s nao existe\n", path); return; }
    TurmaAluno r;
    printf("\n--- %s ---\n", path);
    while(fread(&r, sizeof r, 1, f) == 1) if(r.existe) printf("nome: %s | idade: %d | nota: %.2lf\n", r.nome, r.idade, r.nota);
    fclose(f);
}

void juntarTurmas(){
    FILE *a = fopen("turmaA.bin", "rb");
    FILE *b = fopen("turmaB.bin", "rb");
    FILE *out = fopen("turmaAB.bin", "wb");
    if(!a || !b || !out){ printf("erro ao abrir arquivos\n"); if(a) fclose(a); if(b) fclose(b); if(out) fclose(out); return; }
    TurmaAluno r;
    while(fread(&r, sizeof r, 1, a) == 1) if(r.existe) fwrite(&r, sizeof r, 1, out);
    while(fread(&r, sizeof r, 1, b) == 1) if(r.existe) fwrite(&r, sizeof r, 1, out);
    fclose(a); fclose(b); fclose(out);
    remove("turmaA.bin"); remove("turmaB.bin"); rename("turmaAB.bin", "turmaAB.bin");
    printf("turmas juntadas em turmaAB.bin\n");
}

/* ---------- intercalar arquivos por idade ---------- */
void intercalarTresArquivos(const char *a1, const char *a2, const char *a3, const char *saida){
    FILE *f1 = fopen(a1, "rb");
    FILE *f2 = fopen(a2, "rb");
    FILE *f3 = fopen(a3, "rb");
    FILE *out = fopen(saida, "wb");
    if(!f1 || !f2 || !f3 || !out){ printf("erro ao abrir arquivos\n"); if(f1) fclose(f1); if(f2) fclose(f2); if(f3) fclose(f3); if(out) fclose(out); return; }
    PessoaF lista[MAX_REGISTROS]; int total = 0;
    PessoaF p;
    while(fread(&p, sizeof p, 1, f1) == 1 && total < MAX_REGISTROS) if(p.existe) lista[total++] = p;
    while(fread(&p, sizeof p, 1, f2) == 1 && total < MAX_REGISTROS) if(p.existe) lista[total++] = p;
    while(fread(&p, sizeof p, 1, f3) == 1 && total < MAX_REGISTROS) if(p.existe) lista[total++] = p;
    fclose(f1); fclose(f2); fclose(f3);
    for(int i=0;i<total-1;i++){
        int min = i;
        for(int j=i+1;j<total;j++) if(lista[j].idade < lista[min].idade) min = j;
        if(min != i){ PessoaF tmp = lista[i]; lista[i] = lista[min]; lista[min] = tmp; }
    }
    for(int i=0;i<total;i++) fwrite(&lista[i], sizeof lista[i], 1, out);
    fclose(out);
    printf("arquivos intercalados em %s\n", saida);
}

/* ---------- atualização de contas usando movimentos e removidas ---------- */
int buscarConta(Conta contas[], int n, int numero){
    for(int i=0;i<n;i++) if(contas[i].numero == numero) return i;
    return -1;
}

int foiRemovida(int remov[], int n, int numero){
    for(int i=0;i<n;i++) if(remov[i] == numero) return 1;
    return 0;
}

void atualizarContas(){
    Conta contas[MAX_CONTAS];
    int nContas = 0;
    int removidas[MAX_REMOVIDAS]; int nRem = 0;
    Movimentacao mov;

    FILE *fAnt = fopen("contas_ant.bin", "rb");
    if(fAnt){
        while(fread(&contas[nContas], sizeof contas[nContas], 1, fAnt) == 1 && nContas < MAX_CONTAS) nContas++;
        fclose(fAnt);
    }
    FILE *fMov = fopen("mov.bin", "rb");
    if(fMov){
        while(fread(&mov, sizeof mov, 1, fMov) == 1){
            int idx = buscarConta(contas, nContas, mov.numero);
            if(idx != -1){
                if(mov.tipo == 'C') contas[idx].saldo += mov.valor;
                else if(mov.tipo == 'D') contas[idx].saldo -= mov.valor;
            }
        }
        fclose(fMov);
    }
    FILE *fNovas = fopen("novas_contas.bin", "rb");
    if(fNovas){
        while(fread(&contas[nContas], sizeof contas[nContas], 1, fNovas) == 1 && nContas < MAX_CONTAS) nContas++;
        fclose(fNovas);
    }
    FILE *fRem = fopen("removidas.bin", "rb");
    if(fRem){
        while(fread(&removidas[nRem], sizeof removidas[nRem], 1, fRem) == 1 && nRem < MAX_REMOVIDAS) nRem++;
        fclose(fRem);
    }
    FILE *fOut = fopen("contas_atualizadas.bin", "wb");
    if(fOut){
        for(int i=0;i<nContas;i++) if(!foiRemovida(removidas, nRem, contas[i].numero)) fwrite(&contas[i], sizeof contas[i], 1, fOut);
        fclose(fOut);
    }
    printf("atualizacao concluida\n");
}

/* ---------- pesquisa estatística de pessoas (ex38) ---------- */
void estatisticaPessoas(){
    FILE *f = fopen("resposta.bin", "rb");
    if(!f){ printf("arquivo resposta.bin nao encontrado\n"); return; }
    typedef struct { char sexo; int idade; char fumante; } PBrief;
    PBrief p;
    int total = 0, totalF = 0;
    int totalH = 0, homensNaoFumAbaixo40 = 0;
    int totalMul = 0, mulFumAcima40 = 0;
    while(fread(&p, sizeof p, 1, f) == 1){
        total++;
        if(p.fumante == 'S' || p.fumante == 's') totalF++;
        if(p.sexo == 'M' || p.sexo == 'm'){
            totalH++;
            if((p.fumante == 'N' || p.fumante == 'n') && p.idade < 40) homensNaoFumAbaixo40++;
        }
        if(p.sexo == 'F' || p.sexo == 'f'){
            totalMul++;
            if((p.fumante == 'S' || p.fumante == 's') && p.idade > 40) mulFumAcima40++;
        }
    }
    fclose(f);
    if(total>0) printf("percentual fumantes: %.2f%%\n", 100.0 * totalF / total); else printf("nenhuma pessoa entrevistada\n");
    if(totalH>0) printf("percentual homens nao fumantes <40: %.2f%%\n", 100.0 * homensNaoFumAbaixo40 / totalH); else printf("nenhum homem entrevistado\n");
    if(totalMul>0) printf("percentual mulheres fumantes >40: %.2f%%\n", 100.0 * mulFumAcima40 / totalMul); else printf("nenhuma mulher entrevistada\n");
}

/* ---------- menu principal simplificado ---------- */
int main(){
    int opc = -1;
    while(opc != 0){
        printf("\n=== menu principal(ex pares) ===\n");
        printf("1 - despensa (produtos)\n");
        printf("2 - alunos (notas)\n");
        printf("3 - disciplinas e pre-matricula\n");
        printf("4 - numeros pares ordenados\n");
        printf("5 - fonte / registros\n");
        printf("6 - homens/mulheres (arquivo 24)\n");
        printf("7 - agenda / contatos\n");
        printf("8 - turmas (criar/juntar)\n");
        printf("9 - intercalar 3 arquivos (por idade)\n");
        printf("10 - atualizar contas (movimentacoes)\n");
        printf("11 - estatistica de pessoas (resposta.bin)\n");
        printf("0 - sair\n");
        printf("escolha: ");
        if(scanf("%d", &opc) != 1){ limpar_buffer(); opc = 0; break; }
        limpar_buffer();
        if(opc == 1){
            int sub = -1;
            while(sub != 0){
                printf("\n-- despensa --\n1-add 2-entrada 3-retirada 4-relatorio 5-indisponiveis 0-voltar\n");
                printf("escolha: "); scanf("%d",&sub); limpar_buffer();
                if(sub==1) incluirProduto("despensa.bin");
                if(sub==2) entradaNoEstoque("despensa.bin");
                if(sub==3) retirardaDoEstoque("despensa.bin");
                if(sub==4) relatorioTodos("despensa.bin");
                if(sub==5) relatorioIndisponiveis("despensa.bin");
            }
        } else if(opc == 2){
            int s=-1;
            while(s!=0){
                printf("\n-- alunos (notas) --\n1-cadastrar 2-consultar 3-alterar 4-excluir 5-listar 0-voltar\n");
                printf("escolha: "); scanf("%d", &s); limpar_buffer();
                if(s==1) cadastrarAlunosNotas("alunos_notas.bin");
                if(s==2){ int num; printf("numero: "); scanf("%d",&num); limpar_buffer(); consultarAlunoNotas("alunos_notas.bin", num); }
                if(s==3){ int num; printf("numero: "); scanf("%d",&num); limpar_buffer(); alterarAlunoNotas("alunos_notas.bin", num); }
                if(s==4){ int num; printf("numero: "); scanf("%d",&num); limpar_buffer(); excluirAlunoNotas("alunos_notas.bin", num); }
                if(s==5) listarAlunosNotas("alunos_notas.bin");
            }
        } else if(opc == 3){
            int ss=-1;
            while(ss!=0){
                printf("\n-- disciplinas / pre-matricula --\n1-cadastrar materias 2-cadastrar alunos info 3-gerar pre 4-mostrar pre 0-voltar\n");
                printf("escolha: "); scanf("%d",&ss); limpar_buffer();
                if(ss==1) cadastrarMaterias("materias.bin");
                if(ss==2) cadastrarAlunosInfo("alunos_info.bin");
                if(ss==3) gerarPreMatricula("alunos_info.bin","materias.bin","prematricula.bin");
                if(ss==4) mostrarPreMat("prematricula.bin");
            }
        } else if(opc == 4){
            int t=-1;
            while(t!=0){
                printf("\n-- numeros pares --\n1-criar arquivo numeros 2-listar numeros 3-copiar pares ordenados 4-listar pares 0-voltar\n");
                printf("escolha: "); scanf("%d",&t); limpar_buffer();
                if(t==1) criarNumerosArquivo();
                if(t==2) listarInteirosArquivo("dados_numeros.bin");
                if(t==3) copiarParesOrdenados();
                if(t==4) listarInteirosArquivo("pares_ordenados.bin");
            }
        } else if(opc == 5){
            int q=-1;
            while(q!=0){
                printf("\n-- fonte / registros --\n1-criar fonte 2-listar fonte 3-copiar fonte 0-voltar\n");
                printf("escolha: "); scanf("%d",&q); limpar_buffer();
                if(q==1) criarFonte();
                if(q==2) listarResumoArquivo("FONTE.bin");
                if(q==3) copiarFonteParaNova();
            }
        } else if(opc == 6){
            criarHomensMulheres();
            listarResumoArquivo("homens.dat");
            listarResumoArquivo("mulheres.dat");
        } else if(opc == 7){
            int a=-1;
            while(a!=0){
                printf("\n-- agenda --\n1-criar 2-listar 3-remover 0-voltar\n");
                printf("escolha: "); scanf("%d",&a); limpar_buffer();
                if(a==1) criarAgenda("agenda.bin");
                if(a==2) listarAgenda("agenda.bin");
                if(a==3){ char nome[101]; ler_string("nome a remover: ", nome, sizeof nome); removerContato("agenda.bin", nome); }
            }
        } else if(opc == 8){
            int b=-1;
            while(b!=0){
                printf("\n-- turmas --\n1-criar padrao 2-listar A 3-listar B 4-juntar 5-listar AB 0-voltar\n");
                printf("escolha: "); scanf("%d",&b); limpar_buffer();
                if(b==1) criarTurmasPadrao();
                if(b==2) listarTurmaArquivo("turmaA.bin");
                if(b==3) listarTurmaArquivo("turmaB.bin");
                if(b==4) juntarTurmas();
                if(b==5) listarTurmaArquivo("turmaAB.bin");
            }
        } else if(opc == 9){
            char a1[100], a2[100], a3[100], out[100];
            ler_string("arquivo1: ", a1, sizeof a1);
            ler_string("arquivo2: ", a2, sizeof a2);
            ler_string("arquivo3: ", a3, sizeof a3);
            ler_string("saida: ", out, sizeof out);
            intercalarTresArquivos(a1, a2, a3, out);
        } else if(opc == 10){
            atualizarContas();
        } else if(opc == 11){
            estatisticaPessoas();
        } else if(opc == 0){
            printf("saindo...\n");
        } else {
            printf("opcao invalida\n");
        }
    }
    return 0;
}
