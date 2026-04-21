

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINE 1024
#define MAXWORD 128

/* fallback strdup (portável) */
static char *my_strdup(const char *s){
    if(!s) return NULL;
    size_t l = strlen(s) + 1;
    char *p = (char*)malloc(l);
    if(!p) return NULL;
    memcpy(p, s, l);
    return p;
}
#define strdup my_strdup

/* utilitários */
void flush_stdin(void){ int c; while((c=getchar())!='\n' && c!=EOF); }
void str_to_lower(char *s){ for(; *s; ++s) *s = (char)tolower((unsigned char)*s); }

/* ex1: mostrar arquivo */
void ex1(void){
    char fname[256];
    printf("nome do arquivo: ");
    if(!fgets(fname, sizeof(fname), stdin)) return;
    fname[strcspn(fname, "\n")] = '\0';
    FILE *f = fopen(fname, "r");
    if(!f){ perror("erro ao abrir"); return; }
    char buf[1024];
    while(fgets(buf, sizeof(buf), f)) fputs(buf, stdout);
    fclose(f);
}

/* ex3: converter letras (inicial de frase maiúscula) */
void ex3(void){
    char fname[256];
    printf("nome do arquivo: "); if(!fgets(fname,sizeof(fname),stdin)) return; fname[strcspn(fname,"\n")]='\0';
    FILE *f = fopen(fname,"r"); if(!f){ perror("erro ao abrir"); return; }
    int c; int sentence_start=1;
    while((c=fgetc(f))!=EOF){
        if(isalpha(c)){
            if(sentence_start){ putchar(toupper(c)); sentence_start=0; }
            else putchar(tolower(c));
        } else {
            putchar(c);
            if(c=='.' || c=='!' || c=='?') sentence_start=1;
            else if(!isspace(c)) sentence_start=0;
        }
    }
    fclose(f);
}

/* ex5: contar ocorrencias de palavra (case-insensitive) */
void ex5(void){
    char fname[256], palavra[MAXWORD];
    printf("arquivo: "); if(!fgets(fname,sizeof(fname),stdin)) return; fname[strcspn(fname,"\n")]='\0';
    printf("palavra: "); if(!fgets(palavra,sizeof(palavra),stdin)) return; palavra[strcspn(palavra,"\n")]='\0';
    str_to_lower(palavra);
    FILE *f = fopen(fname, "r"); if(!f){ perror("erro ao abrir"); return; }
    int count = 0; char buf[MAXWORD];
    while(fscanf(f, "%127s", buf) == 1){
        int i = 0, j = (int)strlen(buf) - 1;
        while(i <= j && !isalnum((unsigned char)buf[i])) i++;
        while(j >= i && !isalnum((unsigned char)buf[j])){ buf[j] = '\0'; j--; }
        if(i > j) continue;
        char core[MAXWORD]; strncpy(core, buf + i, MAXWORD-1); core[MAXWORD-1] = '\0';
        str_to_lower(core);
        if(strcmp(core, palavra) == 0) count++;
    }
    fclose(f);
    printf("ocorre %d vezes\n", count);
}

/* ex7: concatenar dois arquivos */
void ex7(void){
    char f1[256], f2[256], out[256];
    printf("arquivo 1: "); if(!fgets(f1,sizeof(f1),stdin)) return; f1[strcspn(f1,"\n")]='\0';
    printf("arquivo 2: "); if(!fgets(f2,sizeof(f2),stdin)) return; f2[strcspn(f2,"\n")]='\0';
    printf("arquivo saida: "); if(!fgets(out,sizeof(out),stdin)) return; out[strcspn(out,"\n")]='\0';
    FILE *a=fopen(f1,"r"); if(!a){ perror("erro abrir 1"); return; }
    FILE *b=fopen(f2,"r"); if(!b){ perror("erro abrir 2"); fclose(a); return; }
    FILE *o=fopen(out,"w"); if(!o){ perror("erro criar"); fclose(a); fclose(b); return; }
    char buf[1024]; while(fgets(buf,sizeof(buf),a)) fputs(buf,o); while(fgets(buf,sizeof(buf),b)) fputs(buf,o);
    fclose(a); fclose(b); fclose(o);
    printf("concatenado em %s\n", out);
}

/* ex9: ler matriz de arquivo e mostrar */
void ex9(void){
    char fname[256]; printf("arquivo: "); if(!fgets(fname,sizeof(fname),stdin)) return; fname[strcspn(fname,"\n")]='\0';
    FILE *f=fopen(fname,"r"); if(!f){ perror("erro ao abrir"); return; }
    int m,n; if(fscanf(f, "%d %d", &m,&n) != 2){ printf("formato invalido\n"); fclose(f); return; }
    if(m <= 0 || n <= 0){ printf("dimensoes invalidas\n"); fclose(f); return; }
    int **mat = (int**)malloc(m * sizeof(int*)); if(!mat){ perror("malloc"); fclose(f); return; }
    for(int i=0;i<m;i++){ mat[i] = (int*)malloc(n * sizeof(int)); if(!mat[i]){ perror("malloc"); for(int k=0;k<i;k++) free(mat[k]); free(mat); fclose(f); return; } }
    for(int i=0;i<m;i++) for(int j=0;j<n;j++) if(fscanf(f, "%d", &mat[i][j])!=1) mat[i][j]=0;
    fclose(f);
    for(int i=0;i<m;i++){ for(int j=0;j<n;j++) printf("%d\t", mat[i][j]); printf("\n"); }
    for(int i=0;i<m;i++) free(mat[i]); free(mat);
}

/* ex11: compactador simplificado (mostra dicionario) */
void ex11(void){
    char fname[256]; printf("arquivo texto: "); if(!fgets(fname,sizeof(fname),stdin)) return; fname[strcspn(fname,"\n")]='\0';
    FILE *f=fopen(fname,"r"); if(!f){ perror("erro"); return; }
    char word[MAXWORD]; char *dict[1000]; int dict_count=0;
    while(fscanf(f, "%127s", word)==1){ char core[MAXWORD]; int p=0; for(size_t i=0;i<strlen(word);i++) if(isalnum((unsigned char)word[i])) core[p++]=tolower((unsigned char)word[i]); core[p]='\0'; if(p==0) continue; int idx=-1; for(int i=0;i<dict_count;i++) if(strcmp(dict[i], core)==0){ idx=i; break; } if(idx==-1){ dict[dict_count]=strdup(core); idx=dict_count++; if(dict_count>=1000) break; } }
    fclose(f);
    printf("dicionario (%d palavras):\n", dict_count);
    for(int i=0;i<dict_count;i++){ printf("%s\n", dict[i]); free(dict[i]); }
}

/* ex13: inverter cada bloco de 30 chars por linha */
void ex13(void){
    char in[256], out[256]; printf("arquivo entrada: "); if(!fgets(in,sizeof(in),stdin)) return; in[strcspn(in,"\n")]='\0';
    printf("arquivo saida: "); if(!fgets(out,sizeof(out),stdin)) return; out[strcspn(out,"\n")]='\0';
    FILE *f=fopen(in,"r"); if(!f){ perror("erro"); return; }
    FILE *o=fopen(out,"w"); if(!o){ perror("erro criar"); fclose(f); return; }
    char line[1024]; while(fgets(line,sizeof(line),f)){
        line[strcspn(line,"\n")]='\0'; int len=(int)strlen(line);
        for(int i=0;i<len;i+=30){ int chunk=(i+30<=len)?30:(len-i); for(int j=chunk-1;j>=0;j--) fputc(line[i+j], o); }
        fputc('\n', o);
    }
    fclose(f); fclose(o); printf("invertido para %s\n", out);
}

/* ex15: substituir palavras usando dicionario (orig sub por linha) */
void ex15(void){
    char txt[256], dict[256], out[256]; printf("arquivo texto: "); if(!fgets(txt,sizeof(txt),stdin)) return; txt[strcspn(txt,"\n")]='\0';
    printf("arquivo dicionario: "); if(!fgets(dict,sizeof(dict),stdin)) return; dict[strcspn(dict,"\n")]='\0';
    printf("arquivo saida: "); if(!fgets(out,sizeof(out),stdin)) return; out[strcspn(out,"\n")]='\0';
    FILE *f=fopen(txt,"r"); if(!f){ perror("erro texto"); return; }
    FILE *d=fopen(dict,"r"); if(!d){ perror("erro dict"); fclose(f); return; }
    char a[MAXWORD], b[MAXWORD]; char *orig[1000], *sub[1000]; int dc=0;
    while(fscanf(d, "%127s %127s", a,b)==2){ orig[dc]=strdup(a); sub[dc]=strdup(b); for(char *p=orig[dc]; *p; ++p) *p = (char)tolower((unsigned char)*p); dc++; if(dc>=1000) break; }
    fclose(d);
    FILE *o=fopen(out,"w"); if(!o){ perror("erro criar"); fclose(f); return; }
    char w[MAXWORD];
    while(fscanf(f, "%127s", w)==1){
        char prefix[10]="", suffix[10]="", core[MAXWORD]; int i0=0, i1=(int)strlen(w)-1;
        while(i0<=i1 && ispunct((unsigned char)w[i0])){ int L=strlen(prefix); if(L<9){ prefix[L]=w[i0]; prefix[L+1]='\0'; } i0++; }
        while(i1>=i0 && ispunct((unsigned char)w[i1])){ int L=strlen(suffix); if(L<9){ suffix[L]=w[i1]; suffix[L+1]='\0'; } i1--; }
        int p=0; for(int k=i0;k<=i1 && p<MAXWORD-1;k++) core[p++]=w[k]; core[p]='\0';
        char core_low[MAXWORD]; strncpy(core_low, core, MAXWORD); core_low[MAXWORD-1]='\0'; str_to_lower(core_low);
        int found=0; for(int k=0;k<dc;k++) if(strcmp(core_low, orig[k])==0){ fprintf(o, "%s%s%s ", prefix, sub[k], suffix); found=1; break; }
        if(!found) fprintf(o, "%s%s%s ", prefix, core, suffix);
    }
    fclose(f); fclose(o); for(int k=0;k<dc;k++){ free(orig[k]); free(sub[k]); }
    printf("traducao escrita em %s\n", out);
}

/* comparator para qsort */
int cmp_int(const void *a, const void *b){ int ia = *(const int*)a; int ib = *(const int*)b; return (ia>ib)-(ia<ib); }

/* ex17: ler vetores A e B e criar C ordenado */
void ex17(void){
    char a_fn[256], b_fn[256], c_fn[256]; printf("arquivo A: "); if(!fgets(a_fn,sizeof(a_fn),stdin)) return; a_fn[strcspn(a_fn,"\n")]='\0';
    printf("arquivo B: "); if(!fgets(b_fn,sizeof(b_fn),stdin)) return; b_fn[strcspn(b_fn,"\n")]='\0';
    printf("arquivo C saida: "); if(!fgets(c_fn,sizeof(c_fn),stdin)) return; c_fn[strcspn(c_fn,"\n")]='\0';
    FILE *fa=fopen(a_fn,"r"); if(!fa){ perror("erro A"); return; }
    FILE *fb=fopen(b_fn,"r"); if(!fb){ perror("erro B"); fclose(fa); return; }
    int A[10000], B[10000]; int na=0, nb=0;
    while(na<10000 && fscanf(fa, "%d", &A[na])==1) na++; while(nb<10000 && fscanf(fb, "%d", &B[nb])==1) nb++;
    fclose(fa); fclose(fb);
    qsort(A, na, sizeof(int), cmp_int); qsort(B, nb, sizeof(int), cmp_int);
    FILE *fc=fopen(c_fn,"w"); if(!fc){ perror("erro criar C"); return; }
    int ia=0, ib=0; while(ia<na && ib<nb){ if(A[ia] <= B[ib]) fprintf(fc, "%d\n", A[ia++]); else fprintf(fc, "%d\n", B[ib++]); }
    while(ia<na) fprintf(fc, "%d\n", A[ia++]); while(ib<nb) fprintf(fc, "%d\n", B[ib++]); fclose(fc);
    printf("vetor C criado em %s\n", c_fn);
}

/* ex19/ex21: processar arquivo alunos com separador ';' */
void process_students_file(const char *prompt_file){
    char fname[256]; printf("%s: ", prompt_file); if(!fgets(fname,sizeof(fname),stdin)) return; fname[strcspn(fname,"\n")]='\0';
    FILE *f=fopen(fname,"r"); if(!f){ perror("erro"); return; }
    char line[512]; while(fgets(line,sizeof(line),f)){
        char *p=line; while(isspace((unsigned char)*p)) p++; if(*p=='\0') continue;
        for(char *s=p; *s; ++s) if(*s==';') *s=' ';
        char nome[256]; double n1=0.0, n2=0.0;
        if(sscanf(p, "%255s %lf %lf", nome, &n1, &n2) >= 1){ double media = (n1+n2)/2.0; printf("%s %.1f %.1f %.2f %s\n", nome, n1, n2, media, media>=5.0?"aprovado":"reprovado"); }
    }
    fclose(f);
}
void ex19(void){ process_students_file("arquivo 19 (linhas com ';')"); }
void ex21(void){ process_students_file("arquivo 21 (linhas com ';')"); }

/* ex23: separar modelos por sexo em arquivos binarios (struct Model) */
typedef struct { char nome[64]; char sexo; char olhos; float altura; float peso; } Model;
void ex23(void){
    char fname[256]; printf("arquivo modelos (texto): "); if(!fgets(fname,sizeof(fname),stdin)) return; fname[strcspn(fname,"\n")]='\0';
    FILE *f=fopen(fname,"r"); if(!f){ perror("erro"); return; }
    FILE *m = fopen("modelos_M.bin","wb"); FILE *fm = fopen("modelos_F.bin","wb");
    char line[256]; while(fgets(line,sizeof(line),f)){
        line[strcspn(line,"\n")]='\0'; if(line[0]=='\0') continue;
        char tmp[256]; char nome[64] = {0}; char sexo=0, olhos=0; float altura=0.0f, peso=0.0f;
        strncpy(tmp, line, sizeof(tmp)-1);
        for(char *s=tmp; *s; ++s) if(*s==';' || *s==',') *s = ' ';
        if(sscanf(tmp, "%63s %c %c %f %f", nome, &sexo, &olhos, &altura, &peso) >= 2){ Model mo; memset(&mo,0,sizeof(mo)); strncpy(mo.nome, nome, sizeof(mo.nome)-1); mo.sexo=sexo; mo.olhos=olhos; mo.altura=altura; mo.peso=peso; if(sexo=='M' || sexo=='m'){ if(m) fwrite(&mo, sizeof(mo), 1, m); } else if(sexo=='F' || sexo=='f'){ if(fm) fwrite(&mo, sizeof(mo), 1, fm); } }
    }
    if(m) fclose(m); if(fm) fclose(fm); fclose(f);
    printf("arquivos modelos_M.bin e modelos_F.bin criados (struct Model)\n");
}

/* menu */
int main(void){
    while(1){
        printf("\nlista 4 - exercicios ímpares (selecione):\n");
        printf(" 1  - ex1: mostrar arquivo\n");
        printf(" 3  - ex3: formata maius/minusc e inicial de frase\n");
        printf(" 5  - ex5: conta ocorrencias de palavra\n");
        printf(" 7  - ex7: concatena dois arquivos\n");
        printf(" 9  - ex9: ler matriz do arquivo e mostrar\n");
        printf("11  - ex11: compactar (versao simplificada)\n");
        printf("13  - ex13: inverter linhas de 30 colunas\n");
        printf("15  - ex15: traduzir com dicionario\n");
        printf("17  - ex17: merge vetores A e B ordenados\n");
        printf("19  - ex19: processa alunos (formato ; )\n");
        printf("21  - ex21: processa alunos (variante)\n");
        printf("23  - ex23: separar modelos por sexo (binarios)\n");
        printf(" 0  - sair\n");
        printf("opção: ");
        char opt[16]; if(!fgets(opt,sizeof(opt),stdin)) break; int n = atoi(opt);
        switch(n){ case 0: printf("tchau\n"); return 0; case 1: ex1(); break; case 3: ex3(); break; case 5: ex5(); break; case 7: ex7(); break; case 9: ex9(); break; case 11: ex11(); break; case 13: ex13(); break; case 15: ex15(); break; case 17: ex17(); break; case 19: ex19(); break; case 21: ex21(); break; case 23: ex23(); break; default: printf("opção inválida\n"); break; }
        printf("pressione enter para continuar..."); flush_stdin();
    }
    return 0;
}
