// senha: 2412
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <conio.h>
#include <bits/stdc++.h>
#include <ctime>

#define baixo 80
#define cima 72
#define esc 27
#define enter 13
#define f1 59

using namespace std;
void limpabuffer(){
	int c;
	while( (c = getchar() ) != '\n' && c != EOF);
}
void limpar(){
	system("cls");
}
void cabecalho(){
	printf("                 _\n");
printf("                ;`',\n");
printf("                `,  `,\n");
printf("                 ',   ;   ,,-\"\"==..,\n");
printf("                  \\    ','          \\\n");
printf("          ,-\"\"'-. , ;    '    __.-=\"-.;\n");
printf("        ,\" ,,_    \"V      _.\"\n");
printf("       ;,'   ''-,          \"=--,_\n");
printf("              ,-''    _  _       `,\n");
printf("             /   ,.-+(_)(_)?--.,   ;\n");
printf("            ,'  /   ; (_)       `\\ ,\n");
printf("            ; ,/    ;._.;         ;\n");
printf("            !,'     ;   ;\n");
printf("            V'      ;   ;\n");
printf("                    ;._.;\n");
printf("                    ;   ;\n");
printf("                    ;   ;        ~\n");
printf("     ~              ;._.;\n");
printf("               ~    ;   ;\n");
printf("                   .?   `.                ~\n");
printf("             __,.--;.___.;--.,___\n");
printf("       _,,-\"\"      ;     ;       \"\"-,,_\n");
printf("   .-??            ;     ;             ``-.\n");
printf("  \",              ?       `               ,\"        ~\n");
printf("    \"-_                                _-\"\n");
printf("~       ``----..,_          __,,..bmw-?\n");
printf("                  ```''''???                  ~\n");
printf("                              ~\n");
printf("             ~\n");

}
void escreverCentena(int n, string &out){
    static const string unidades[] = {"","um","dois","três","quatro","cinco","seis","sete","oito","nove"};
    static const string teens[] = {"dez","onze","doze","treze","quatorze","quinze","dezesseis","dezessete","dezoito","dezenove"};
    static const string dezenas[] = {"","dez","vinte","trinta","quarenta","cinquenta","sessenta","setenta","oitenta","noventa"};
    static const string centenas[] = {"","cento","duzentos","trezentos","quatrocentos","quinhentos","seiscentos","setecentos","oitocentos","novecentos"};

    if(n==0) return;
    if(n==100){
        if(!out.empty()) out += " e ";
        out += "cem";
        return;
    }
    int c = n/100;
    int rem = n%100;
    if(c>0){
        if(!out.empty()) out += " ";
        out += centenas[c];
    }
    if(rem>0){
        if(!out.empty()){
            if(c>0) out += " e ";
        }
        if(rem < 10){
            out += unidades[rem];
        } else if(rem < 20){
            out += teens[rem-10];
        } else {
            int d = rem / 10;
            int u = rem % 10;
            out += dezenas[d];
            if(u>0){
                out += " e ";
                out += unidades[u];
            }
        }
    }
}
string numeroPorExtenso(long long n){
    if(n==0) return "zero";
    string out = "";
    long long bilhao = 1000000000LL;
    long long milhao = 1000000LL;
    long long mil = 1000LL;

    int part;
    if(n/bilhao > 0){
        part = (int)(n/bilhao);
        if(part>1){
            out += numeroPorExtenso(part) + " bilhões";
        } else {
            out += "um bilhão";
        }
        n %= bilhao;
        if(n>0) out += (n < 100 ? " e " : " ");
    }
    if(n/milhao > 0){
        part = (int)(n/milhao);
        if(part>1){
            out += numeroPorExtenso(part) + " milhões";
        } else {
            out += "um milhão";
        }
        n %= milhao;
        if(n>0) out += (n < 100 ? " e " : " ");
    }
    if(n/mil > 0){
        part = (int)(n/mil);
        if(part>1){
            out += numeroPorExtenso(part) + " mil";
        } else {
            out += "mil";
        }
        n %= mil;
        if(n>0) out += (n < 100 ? " e " : " ");
    }
    if(n>0){
        int last = (int)n;
        escreverCentena(last, out);
    }
    return out;
}
void notas() {
    limpabuffer();
	int x=0,z=0;
    double y=0;
    char temp[100];
    printf("Digite o valor que deseja sacar! Utilize ponto\n");
    scanf("%lf", &y);
    sprintf(temp, "%.2f", y);
    for(int i=0; temp[i]; i++) {
        if(temp[i] == ',') temp[i] = '.';
    }
    x=atoi(strtok(temp,"."));
    z=atoi(strtok(NULL,"."));
    printf("NOTAS:\n");
    printf("%d nota(s) de B$ 100.00\n", x / 100);
    x %= 100;
    printf("%d nota(s) de B$ 50.00\n", x / 50);
    x %= 50;
    printf("%d nota(s) de B$ 20.00\n", x / 20);
    x %= 20;
    printf("%d nota(s) de B$ 10.00\n", x / 10);
    x %= 10;
    printf("%d nota(s) de B$ 5.00\n", x / 5);
    x %= 5;
    printf("%d nota(s) de B$ 2.00\n", x / 2);
    x %= 2;
    printf("MOEDAS:\n");
    printf("%d moeda(s) de B$ 1.00\n", x);
    printf("%d moeda(s) de B$ 0.50\n", z / 50);
    z %= 50;
    printf("%d moeda(s) de B$ 0.10\n", z / 10);
    z %= 10;
    printf("%d moeda(s) de B$ 0.01\n", z);
    printf("Pressione qualquer tecla para continuar...\n");
    getch();
}
void cheque(){
    limpabuffer();
    printf("Insira o valor do cheque a ser pago (use ponto ou vírgula como separador):\n");
    char entrada[100];
    if(!fgets(entrada, sizeof(entrada), stdin)) {
        printf("Entrada inválida.\n");
        getch();
        return;
    }
    for(int i=0; entrada[i]; i++){
        if(entrada[i]==',') entrada[i]='.';
    }
    double valor = atof(entrada);
    if(valor < 0){
        printf("Valor inválido.\n");
        getch();
        return;
    }
    long long inteiro = (long long)valor;
    int centavos = (int)round((valor - (double)inteiro) * 100.0);
    if(centavos == 100){
        inteiro += 1;
        centavos = 0;
    }
    string extensoInteiro = numeroPorExtenso(inteiro);
    string extensoCentavos = numeroPorExtenso(centavos);
    printf("\n----------------------------\n");
    if(inteiro == 1) printf("%s Bit", extensoInteiro.c_str());
    else printf("%s Bits", extensoInteiro.c_str());
    if(centavos > 0){
        if(centavos == 1) printf(" e %s CentBit\n", extensoCentavos.c_str());
        else printf(" e %s CentBits\n", extensoCentavos.c_str());
    } else {
        printf(" e zero CentBits\n");
    }
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    int d = tm_info->tm_mday;
    int m = tm_info->tm_mon + 1;
    int y = tm_info->tm_year + 1900;
    printf("Data do preenchimento: %02d/%02d/%04d\n", d, m, y);
    printf("----------------------------\n");
    printf("Pressione qualquer tecla para continuar...\n");
    getch();
}

int main(){
	int op = 0;
	char t;
	
	char space[] = "      ";
	char select[] = "\033[0;36m   >> ";
	char reset[] = "\033[0m";
	
	while(1){
		limpar();
		cabecalho();
		printf("      SISTEMA ILHAS BITLANDIA!\nOnde seu bit vira profit!\n");
		printf("%s Sacar dinheiro%s\n", (op == 0) ? select : space, reset);
		printf("%s Preencher um cheque%s\n", (op == 1) ? select : space, reset);
		printf("%s Sair%s\n\n", (op == 2) ? select : space, reset);

		t = getch();
		
        if(t == baixo){
        	if(op != 2) op++;
        	else op = 0;
		}
		else if(t == cima){
			if(op !=0) op--;
			else op = 2;
		}
		else if(t == enter){
			switch (op) {
				case 0:
					notas();
					break;
				case 1:
					cheque();
					break;
				case 2:
					printf("Saindo...\n");
					return 0;
					break;
			}
		}
	}
}
