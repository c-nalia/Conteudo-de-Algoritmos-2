#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <stdbool.h>
#include "base64_min.h"

#define FOR(i,a1,a2) for(int i=a1;i<a2;i++)
typedef long long int lli;
typedef struct{
    char nome[41];
    double quantidade;
}listaQ;

typedef struct{
    char nome[41];
    int l_size,c_size;
    double matriz[8][8];
}listaM;

void clear_buffer(){
    while(getchar()!='\n'&&getchar()!='0');
}

void clear_console(){
  if(_WIN32){
  	system("cls");
  }
  else system("clear");
}

void presstoContinue(){
	printf("-pressione a tecla enter para continuar-\n");
	int imput;
	imput=getchar();
	if(imput<0)getchar();
}

void arte_menu(){
    printf("                                             ,----,\n");
    printf("                                          ,/   .`|                                      ,--,\n");
    printf("      ,--,       ,---,   .--.--.        ,`   .'  :    ,---,                           ,--.'|     ,---,.     ,---,.\n");
    printf("    ,--.'|    ,`--.' |  /  /    '.    ;    ;     /   '  .' \\                       ,--,  | :   ,'  .' |   ,'  .' |\n");
    printf("    |  | :    |   :  : |  :  /`. /  .'_,/    ,'   /  ;    '.                  ,---.'|  : ' ,---.'   | ,---.'   |\n");
    printf("    :  : '    :   |  ' ;  |  |--`   |    :     |   :  :       \\                 |   | : _' | |   |   .' |   |   .'\n");
    printf("    |  ' |    |   :  | |  :  ;_     ;    |.';  ;   :  |   /\\   \\        ,---.   :   : |.'  | :   :  |-, :   :  :\n");
    printf("    '  | |    '   '  ;  \\  \\    `.  `----'  |  |   |  :  ' ;.   :      /     \\  |   ' '  ; : :   |  ;/| :   |  |-,\n");
    printf("    |  | :    |   |  |   `----.   \\     '   :  ;   |  |  ;/  \\   \\    /    / '  '   |  .'. | |   :   .' |   :  ;/|\n");
    printf("    '  : |__  '   :  ;   __ \\  \\  |     |   |  '   '  :  | \\  \\ ,'   .    ' /   |   | :  | ' |   |  |-, |   |   .'\n");
    printf("    |  | '.'| |   |  '  /  /`--'  /     '   :  |   |  |  '  '--'     '   ; :__  '   : |  : ; '   :  ;/| '   :  '\n");
    printf("    ;  :    ; '   :  | '--'.     /      ;   |.'    |  :  :           '   | '.'| |   | '  ,/  |   |    \\ |   |  |\n");
    printf("    |  ,   /  ;   |.'    `--'---'       '---'      |  | ,'           |   :    : ;   : ;--'   |   :   .' |   :  \\\n");
    printf("     ---`-'   '---'                                `--''              \\   \\  /  |   ,/       |   | ,'   |   | ,'\n");
    printf("                                                                       `----'   '---'        `----'     `----'\n");
    printf("\n");
}

char menu(){
    clear_console();
    arte_menu();
    printf("    \"Bem vindo ao programa casual feito para criacao de listas para uso qualquer!\"\n");
    printf("        Selecione uma das opcoes abaixo:\n");
    printf("        >> 1- Criar uma Nova Lista\n");
    printf("        >> 2- Modificar lista existente\n");
    printf("        >> 3- Ler lista existente\n");
    printf("        >> 4- Ver listas criadas\n");
    printf("        >> 5- Deletar ou Renomear listas\n");
    printf("        >> 6- Sair\n");
    printf("        (pressione F1 para ajuda)\n");

    //f1 = 0,59
    char imput=0;
    while((('6'<imput&&imput!=59)||imput<'1')){
        imput=getch();
        if(imput<=0){
            imput=getch();
        }
    }
    return imput;
}

void criar_lista(FILE *arquivo){
    clear_console();
    FILE *arquivo2,*arquivo3;
    printf("    >>Digite o nome que deseja dar a essa lista (ela ja estara no formato .dat)\n (maximo de 40 caracteres): ");

        char nome_lista[49];
        gets(nome_lista);
        if(strlen(nome_lista)>40){
            printf(">Nome da lista excede o tamanho maximo permitido<\n");
            presstoContinue();
            exit(-444);
        }
        strcat(nome_lista,".dat");

        char overwrite='S';
        if((arquivo = fopen(nome_lista,"rb")) != NULL){
            fclose(arquivo);
            printf(">Um aquivo com este nome ja existe, deseja sobre-escreve-lo? (s/n)<\n");
            do {
                    overwrite = toupper(getch());
                    } while (overwrite != 'S' && overwrite != 'N');
        }
        if(overwrite==0){
            return;
        }
        else
        {
            if ((arquivo = fopen(nome_lista,"wb")) == NULL) {
            printf (">Erro na abertura do arquivo<");
            exit(-444);
            }

            if ((arquivo3 = fopen ("list_of_lists.dat","ab")) == NULL) {
            printf ("Erro no catalogo do arquivo.");
            exit (-444);
            }
            fwrite(nome_lista, sizeof(nome_lista), 1, arquivo3);

            char auxstr[49];
            strcpy(auxstr,nome_lista);
            strcat(auxstr,"bak0");
            while((arquivo2 = fopen(auxstr,"rb")) != NULL){
                auxstr[strlen(auxstr)-1]++;
            }
            if ((arquivo2 = fopen(auxstr,"wb")) == NULL) {
            printf (">Erro na abertura do arquivo<");
            exit(-444);
            }
            fwrite(auxstr, sizeof(auxstr), 1, arquivo3);

            clear_console();
            printf("    >>Arquivo %s aberto<<\n\n",nome_lista);

            printf(">>Que tipo de lista deseja criar?\n");
            printf("Lista de objetos/nomes (Q), matriz de numeros (M)\n");
            char op;
            do{
                op=getch();
                op=toupper(op);
            }while(op!='Q'&&op!='M');

            if(op=='Q')
            {
                fwrite(&op, sizeof(op), 1, arquivo); //identificador do tipo de arquivo
                fwrite(&op, sizeof(op), 1, arquivo2);

                listaQ listaQ1;

                char S_N='S';
                while(S_N=='S')
                {

                    printf(">>Digite o nome do(a) objeto/pessoa: ");
                    gets(listaQ1.nome);
                    printf(">>Digite a quantidade correspondente ao objeto/pessoa: ");
                    scanf("%lf",&listaQ1.quantidade);
                    getchar();

                    fwrite(&listaQ1, sizeof(listaQ1), 1, arquivo);
                    fwrite(&listaQ1, sizeof(listaQ1), 1, arquivo2);
                    fflush(arquivo);

                    printf("\n Adicionar outro item (s/n)? \n");
                    do {
                    S_N = toupper(getch());
                    } while (S_N != 'S' && S_N != 'N');
                }
            }

            else{
                fwrite(&op, sizeof(op), 1, arquivo);
                fwrite(&op, sizeof(op), 1, arquivo2);

                listaM listaM1;

                char S_N='S';
                while(S_N=='S')
                {

                    printf(">>Digite o nome da matriz: ");
                    gets(listaM1.nome);

                    int l,c;
                    printf(">>Digite quantas linhas ha nessa matriz:\n");
                    scanf("%d",&l);
                    getchar();
                    while(l>8||l<1){
                        printf(">Quantidade invalida (tamanho maximo: 8)< \n");
                        scanf("%d",&l);
                        getchar();
                    }
                    listaM1.l_size=l;

                    printf(">>Digite quantas colunas ha nessa matriz:\n");
                    scanf("%d",&c);
                    getchar();
                    while(c>8||c<1){
                        printf(">Quantidade invalida (tamanho maximo: 8)< \n");
                        scanf("%d",&c);
                        getchar();
                    }
                    listaM1.c_size=c;
                    
                    printf(">>Digite os elementos dessa matriz:\n");
                    for(int i=0;i<l;i++){
                        for(int j=0;j<c;j++){
                            scanf("%lf",&listaM1.matriz[i][j]);
                            getchar();
                        }
                    }
                    
                    fwrite(&listaM1, sizeof(listaM1), 1, arquivo);
                    fwrite(&listaM1, sizeof(listaM1), 1, arquivo2);
                    fflush(arquivo);

                    printf("\n Adicionar outra Matriz (s/n)? ");
                    do {
                    S_N = toupper(getch());
                    } while (S_N != 'S' && S_N != 'N');
                }
            }
        }
        fclose(arquivo);
        fclose(arquivo2);
        fclose(arquivo3);
        return;
}

void listas_disponiveis(FILE *arquivo,bool continue_){
    clear_console();
    char nome_lista[49];
    if ((arquivo = fopen ("list_of_lists.dat","rb")) == NULL) {
        printf ("Arquivo nao encontrado\n");
        fclose(arquivo);
        }
    else
    {
        printf("   >>Listas Existentes:\n\n");
        while(fread(nome_lista,sizeof(nome_lista),1,arquivo)==1){
         printf("%s\n",nome_lista);
        }
    }
    if(continue_==1){
        presstoContinue();
    }
    fclose(arquivo);
    return;
}

void ler_lista(FILE *arquivo){
    clear_console();
    listas_disponiveis(arquivo,0);
    printf("    >>Digite o nome da lista que deseja ver o conteudo : ");

        char nome_lista[49];
        gets(nome_lista);
        if(strlen(nome_lista)>40){
            printf(">Nome da lista excede o tamanho maximo permitido<\n");
            presstoContinue();
            exit(-444);
        }

        if((arquivo = fopen(nome_lista,"rb")) == NULL){
            printf (">Arquivo nao encontrado<\n");
            presstoContinue();
            return;
        }
        else{
            clear_console();
            printf("    >>Arquivo %s aberto<<\n\n",nome_lista);

            char op;
            fread(&op,sizeof(op),1,arquivo);

            if(op=='Q')
            {
                listaQ listaQ2;
                while(fread(&listaQ2,sizeof(listaQ2),1,arquivo)==1){
                    printf("    >>%s: ",listaQ2.nome);
                    printf("%.3lf\n\n",listaQ2.quantidade);
                }
            }

            else
            {
                listaM listaM2;
                while(fread(&listaM2,sizeof(listaM2),1,arquivo)==1){
                    printf("    >>  %s  <<\n",listaM2.nome);
                    for(int i=0;i<listaM2.l_size; i++){
                        for(int j=0; j<listaM2.c_size; j++){
                            printf("%.3lf  ",listaM2.matriz[i][j]);
                        }
                        printf("\n");
                    }
                    printf("\n");
                }
            }
            presstoContinue();
            printf("\n");
            fclose(arquivo);
        }
    return;
}

void modificar_lista(FILE *arquivo){
    clear_console();
    listas_disponiveis(arquivo,0);
    printf("    >>Digite o nome da lista que deseja modificar o conteudo: ");
    char op;
    int numero_de_indices=0;

        char nome_lista[49];
        gets(nome_lista);
        if(strlen(nome_lista)>40){
            printf(">Nome da lista excede o tamanho maximo permitido<\n");
            presstoContinue();
            exit(-444);
        }

        if((arquivo = fopen(nome_lista,"rb")) == NULL){
            printf (">Arquivo nao encontrado<\n");
            presstoContinue();
            return;
        }

        else{
            clear_console();
            printf("    >>Arquivo %s aberto<<\n\n",nome_lista);

            fread(&op,sizeof(op),1,arquivo);

            if(op=='Q')
            {
                listaQ listaQ2;
                while(fread(&listaQ2,sizeof(listaQ2),1,arquivo)==1){
                    numero_de_indices++;
                    printf("%d    >>%s: ",numero_de_indices,listaQ2.nome);
                    printf("%.3lf\n\n",listaQ2.quantidade);
                }
            }

            else // 'M'
            {
                listaM listaM2;
                while(fread(&listaM2,sizeof(listaM2),1,arquivo)==1){
                    numero_de_indices++;
                    printf("%d    >>  %s  <<\n",numero_de_indices,listaM2.nome);
                    for(int i=0;i<listaM2.l_size; i++){
                        for(int j=0; j<listaM2.c_size; j++){
                            printf("%.3lf  ",listaM2.matriz[i][j]);
                        }
                        printf("\n");
                    }
                    printf("\n");
                }
            }
        }

        int indice_requisitado,indices[numero_de_indices][2],novas_l_c[numero_de_indices][2];
        double novas_quant[numero_de_indices],novas_matrizes[numero_de_indices][8][8];
        char nomes_novos[numero_de_indices][41];
        FOR(itr,0,numero_de_indices) //preencher as matrizes com elementos nulos
        {
            FOR(k,0,2)
            {
                indices[itr][k]=0;
                novas_l_c[itr][k]=0;
            }
            novas_quant[itr]=0.0;
            strcpy(nomes_novos[itr], "null");
            for(int i=0;i<8;i++)
            {
                for(int j=0;j<8;j++)
                {
                    novas_matrizes[itr][i][j]=0.0;
                }
            }

        }

        FILE *arquivoaux;
        if ((arquivoaux = fopen("aux.dat","wb")) == NULL) {
            printf (">Erro na abertura do arquivo auxiliar<\n");
            exit(-444);
        }

        if(op=='Q')
        {
        fwrite(&op, sizeof(op), 1, arquivoaux); //identificador do tipo de arquivo

        char S_N='S';
        while(S_N=='S')
                {
                    printf(">>Digite o indice da lista que deseja modificar?\n");
                    scanf("%d",&indice_requisitado);
                    getchar();
                    while(indice_requisitado<1||indice_requisitado>numero_de_indices){
                        printf(">>Entrada invalida ");
                        scanf("%d",&indice_requisitado);
                        getchar();
                    }
                    indices[indice_requisitado-1][0]=1;
                    printf("\n\n");

                    printf("Deseja modificar o nome, a quantidade, os dois ou deletar um elemento? (N/Q/2/D):\n");
                    do{
                        op=getch();
                        op=toupper(op);
                    }while((op!='N'&&op!='Q')&&(op!='2'&&op!='D'));

                    switch(op)
                    {
                        case 'N':
                        {
                            indices[indice_requisitado-1][1]=1;

                            printf(">>Digite o nome do(a) objeto/pessoa: ");
                            gets(nomes_novos[indice_requisitado-1]);
                            break;
                        }

                        case 'Q': 
                        {
                            indices[indice_requisitado-1][1]=2;

                            printf(">>Digite a quantidade correspondente ao objeto/pessoa: ");
                            scanf("%lf",&novas_quant[indice_requisitado-1]);
                            getchar();
                            break;
                        }

                        case '2':
                        {
                            indices[indice_requisitado-1][1]=3;

                            printf(">>Digite o nome do(a) objeto/pessoa: ");
                            gets(nomes_novos[indice_requisitado-1]);
                            printf(">>Digite a quantidade correspondente ao objeto/pessoa: ");
                            scanf("%lf",&novas_quant[indice_requisitado-1]);
                            getchar();
                            break;
                        }

                        case 'D': indices[indice_requisitado-1][1]=-1;
                        break;

                        default: printf("erro");
                        exit(-444);
                    }

                    printf("\n Modificar outro item (s/n)? \n");
                    do {
                    S_N = toupper(getch());
                    } while (S_N != 'S' && S_N != 'N');
                }

            rewind(arquivo);
            fread(&op,sizeof(op),1,arquivo);
            listaQ listaQ2,lista_aux;
            int itr=0;
            lli size_Q2=sizeof(listaQ2);

            while(fread(&listaQ2,size_Q2,1,arquivo)==1){
                if(indices[itr][0]==1){
                    
                    lista_aux=listaQ2;

                    switch(indices[itr][1])
                    {
                        //fseek (FILE *arq, long numbytes, int origem);
                        case -1: 
                        break;

                        case 1:
                        {
                            strcpy(lista_aux.nome,nomes_novos[itr]);
                            fwrite(&lista_aux, sizeof(lista_aux), 1, arquivoaux);
                            break;
                        }
                        case 2:
                        {
                            lista_aux.quantidade=novas_quant[itr];
                            fwrite(&lista_aux, sizeof(lista_aux), 1, arquivoaux);
                            break;
                        }
                        case 3: 
                        {
                            strcpy(lista_aux.nome,nomes_novos[itr]);
                            lista_aux.quantidade=novas_quant[itr];
                            fwrite(&lista_aux, sizeof(lista_aux), 1, arquivoaux);
                            break;
                        }
                        default: printf("erro");
                        exit(-444);
                    }
                    fflush(arquivoaux);
                }

                else{
                    fwrite(&listaQ2,size_Q2, 1, arquivoaux);
                    fflush(arquivoaux);
                }

                itr++;
            }
        }


        else // 'M'
        {
        fwrite(&op, sizeof(op), 1, arquivoaux); //identificador do tipo de arquivo
        
        char S_N='S';
        while(S_N=='S')
                {
                    printf(">>Digite o indice da lista que deseja modificar?\n");
                    scanf("%d",&indice_requisitado);
                    getchar();
                    while(indice_requisitado<1||indice_requisitado>numero_de_indices){
                        printf(">>Entrada invalida ");
                        scanf("%d",&indice_requisitado);
                        getchar();
                    }
                    indices[indice_requisitado-1][0]=1;
                    printf("\n\n");

                    printf("Deseja modificar o nome, os elementos da matriz, os dois ou deletar um elemento? (N/Q/2/D):\n");
                    do{
                        op=getch();
                        op=toupper(op);
                    }while((op!='N'&&op!='Q')&&(op!='2'&&op!='D'));
                    
                    switch(op)
                    {
                        case 'N':
                        {
                            indices[indice_requisitado-1][1]=1;

                            printf(">>Digite o nome da matriz: ");
                            gets(nomes_novos[indice_requisitado-1]);
                            break;
                        }

                        case 'Q': 
                        {
                            //novas_l_c[numero_de_indices][2]
                            indices[indice_requisitado-1][1]=2;

                            int l,c;
                            printf(">>Digite quantas linhas ha nessa matriz:\n");
                            scanf("%d",&l);
                            getchar();
                            while(l>8||l<1){
                            printf(">Quantidade invalida (tamanho maximo: 8)< \n");
                            scanf("%d",&l);
                            getchar();
                            }
                            novas_l_c[indice_requisitado-1][0]=l;

                            printf(">>Digite quantas colunas ha nessa matriz:\n");
                            scanf("%d",&c);
                            getchar();
                            while(c>8||c<1){
                            printf(">Quantidade invalida (tamanho maximo: 8)< \n");
                            scanf("%d",&c);
                            getchar();
                            }
                            novas_l_c[indice_requisitado-1][1]=c;
                            
                            printf(">>Digite os elementos dessa matriz:\n");
                            for(int i=0;i<l;i++)
                            {
                                for(int j=0;j<c;j++){
                                    scanf("%lf",&novas_matrizes[indice_requisitado-1][i][j]);
                                    getchar();
                                }
                            }
                            break;
                            }

                        case '2':
                        {
                            indices[indice_requisitado-1][1]=3;

                            printf(">>Digite o nome da matriz: ");
                            gets(nomes_novos[indice_requisitado-1]);

                            int l,c;
                            printf(">>Digite quantas linhas ha nessa matriz:\n");
                            scanf("%d",&l);
                            getchar();
                            while(l>8||l<1){
                            printf(">Quantidade invalida (tamanho maximo: 8)< \n");
                            scanf("%d",&l);
                            getchar();
                            }
                            novas_l_c[indice_requisitado-1][0]=l;

                            printf(">>Digite quantas colunas ha nessa matriz:\n");
                            scanf("%d",&c);
                            getchar();
                            while(c>8||c<1){
                            printf(">Quantidade invalida (tamanho maximo: 8)< \n");
                            scanf("%d",&c);
                            getchar();
                            }
                            novas_l_c[indice_requisitado-1][1]=c;

                            printf(">>Digite os elementos dessa matriz:\n");
                            for(int i=0;i<l;i++)
                            {
                                for(int j=0;j<c;j++){
                                    scanf("%lf",&novas_matrizes[indice_requisitado-1][i][j]);
                                    getchar();
                                }
                            }
                            break;
                        }

                        case 'D': indices[indice_requisitado-1][1]=-1;
                        break;

                        default: printf("erro");
                        exit(-444);
                    }

                    printf("\n Modificar outro item (s/n)? \n");
                    do {
                    S_N = toupper(getch());
                    } while (S_N != 'S' && S_N != 'N');
                }

            rewind(arquivo);
            fread(&op,sizeof(op),1,arquivo);
            listaM listaM2,lista_aux;
            int itr=0;
            lli size_M2=sizeof(listaM2);

            while(fread(&listaM2,size_M2,1,arquivo)==1){
                if(indices[itr][0]==1){

                    lista_aux=listaM2;

                    switch(indices[itr][1])
                    {
                        //fseek (FILE *arq, long numbytes, int origem);
                        case -1: 
                        break;

                        case 1:
                        {
                            strcpy(lista_aux.nome,nomes_novos[itr]);
                            fwrite(&lista_aux, sizeof(lista_aux), 1, arquivoaux);
                            break;
                        }
                        case 2:
                        {
                            lista_aux.l_size=novas_l_c[itr][0];
                            lista_aux.c_size=novas_l_c[itr][1];
                            memcpy(lista_aux.matriz,novas_matrizes[itr],sizeof(novas_matrizes[itr]));
                            fwrite(&lista_aux, sizeof(lista_aux), 1, arquivoaux);
                            break;
                        }
                        case 3: 
                        {
                            strcpy(lista_aux.nome,nomes_novos[itr]);
                            lista_aux.l_size=novas_l_c[itr][0];
                            lista_aux.c_size=novas_l_c[itr][1];
                            memcpy(lista_aux.matriz,novas_matrizes[itr],sizeof(novas_matrizes[itr]));
                            fwrite(&lista_aux, sizeof(lista_aux), 1, arquivoaux);
                            break;
                        }
                        default: printf("erro");
                        exit(-444);
                    }
                }
                else fwrite(&listaM2,size_M2, 1, arquivoaux);
                itr++;
            }
            fflush(arquivoaux);
        }

        fclose(arquivo);
        fclose(arquivoaux);
        if (remove(nome_lista) != 0) {
            perror("Erro ao deletar arquivo original");
        }
        if (rename("aux.dat", nome_lista) != 0) {
            perror("Erro ao renomear arquivo auxiliar");
        }
        presstoContinue();
        return;
}

void deletar_ou_renomear(FILE *arquivo){
    FILE *arquivo2;
    clear_console();
    listas_disponiveis(arquivo,0);

    if ((arquivo = fopen ("list_of_lists.dat","rb")) == NULL) {
            printf (">Arquivo nao encontrado<\n");
            fclose(arquivo);
        }
    if ((arquivo2 = fopen("aux.dat","wb")) == NULL) {
            printf (">Erro na abertura do arquivo auxiliar<\n");
            exit(-444);
        }



    printf("Digite o nome arquivo que deseja-se fazer uma acao sobre: ");
    char nome_lista[49],nome_lista_aux2[49];

    gets(nome_lista);
    if(strlen(nome_lista)>40){
            printf(">Nome da lista excede o tamanho maximo permitido<\n");
            presstoContinue();
            exit(-444);
     }

    printf("Deletar ou Renomear (D/R):\n");
    char op;
    do{
        
        op=toupper(getch());
    }while((op!='D')&&(op!='R'));
    
    if(op=='D'){
        if (remove(nome_lista) != 0) {
            perror("Erro ao deletar arquivo original");
        }

        while(fread(nome_lista_aux2,sizeof(nome_lista_aux2),1,arquivo)==1)
        {
            if(strcmp(nome_lista_aux2,nome_lista)!=0)fwrite(nome_lista_aux2,sizeof(nome_lista_aux2),1,arquivo2);
        }
    }

    else{// 'R'
        char nome_lista_aux1[49];
        printf("Escreva o novo nome para o arquivo (sem \".dat\"): ");

        gets(nome_lista_aux1);
        if(strlen(nome_lista_aux1)>40){
            printf(">Nome da lista excede o tamanho maximo permitido<\n");
            presstoContinue();
            exit(-444);
        }
        strcat(nome_lista_aux1,".dat");

        if (rename(nome_lista, nome_lista_aux1) != 0) {
            perror("Erro ao renomear arquivo auxiliar");
        }

        while(fread(nome_lista_aux2,sizeof(nome_lista_aux2),1,arquivo)==1)
        {
            if(strcmp(nome_lista_aux2,nome_lista)==0){
            fwrite(nome_lista_aux1,sizeof(nome_lista_aux1),1,arquivo2);
            }
            else fwrite(nome_lista_aux2,sizeof(nome_lista_aux2),1,arquivo2);
        }
    }

    fclose(arquivo);
    fclose(arquivo2);
        if (remove("list_of_lists.dat") != 0) {
            perror("Erro ao deletar arquivo original");
        }
        if (rename("aux.dat", "list_of_lists.dat") != 0) {
            perror("Erro ao renomear arquivo auxiliar");
        }
    presstoContinue();
    return;
}


void decode() {
    FILE *arq = fopen("....txt", "rb");
    if (!arq) {
        perror("falta o arquivo");
        return;
    }
    char string[621];   
    fread(string, 1, 620, arq);
    string[621] = '\0';
    fclose(arq);

char decoded[128];
size_t out_len;
int ret = base64_decode(string, strlen(string), decoded, &out_len);
decoded[out_len] = '\0';
printf("Texto Ajuda: \n%s\n", decoded);
getch();


    decoded[out_len] = '\0'; // se for texto
}




int main(){
    FILE *arquivo;
    bool fechar_o_programa=false;
    char operacao;

    while(!fechar_o_programa){
        operacao=menu();
        switch(operacao){
            case '1': criar_lista(arquivo);break;
            case '2': modificar_lista(arquivo);break;
            case '3': ler_lista(arquivo);break;
            case '4': listas_disponiveis(arquivo,1);break;
            case '5': deletar_ou_renomear(arquivo); break;
            case '6': fechar_o_programa=true; break;
            case 59: clear_console(); decode(); break;
            default:  printf("erro_menu"); exit(-444);
        }	
    }

}