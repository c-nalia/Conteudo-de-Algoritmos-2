#include <bits/stdc++.h>
using namespace std;

typedef struct reg *no;
struct reg {
    char nome[51];
    int prioridade;
    struct reg *prox;
};

void insere(no *lista) {
    char temp[51];
    int tempint;

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    cout << "Digite o nome do paciente: ";
    cin.getline(temp, 51);

    cout << "Digite a prioridade do paciente (1=regular, 2=ruim, 3=pessimo): ";
    cin >> tempint;

    no v = (no) malloc(sizeof(struct reg));
    strcpy(v->nome, temp);
    v->prioridade = tempint;
    v->prox = NULL;

    // Inserção ordenada
    if (*lista == NULL || v->prioridade > (*lista)->prioridade) {
        v->prox = *lista;
        *lista = v;
    } else {
        no atual = *lista;
        while (atual->prox != NULL && atual->prox->prioridade >= v->prioridade)
            atual = atual->prox;
        v->prox = atual->prox;
        atual->prox = v;
    }

    cout << "Paciente inserido com sucesso!\n";
}

void listar(no lista) {
    if (lista == NULL) {
        cout << "Nenhum paciente na fila.\n";
        return;
    }
    cout << "\n--- Fila de pacientes ---\n";
    while (lista != NULL) {
        cout << "Nome: " << lista->nome << " | Prioridade: " << lista->prioridade << "\n";
        lista = lista->prox;
    }
}

int main() {
    no lista = NULL;
    int l = -1;

    cout << "Bem-vindo ao sistema do pronto socorro de Rolandia - Parana!\n";

    while (l != 0) {
        cout << "\nDigite o que deseja fazer:\n";
        cout << "1 - Inserir novo paciente\n";
        cout << "2 - Listar pacientes\n";
        cout << "0 - Sair\n";
        cout << "Opcao: ";
        cin >> l;
                system("cls");
        switch (l) {
            case 1:
                insere(&lista);
                getchar();
                break;
            case 2:
                listar(lista);
                getchar();
                getchar();
                break;
            case 0:
                cout << "Encerrando...\n";
                break;
            default:
                cout << "Opção inválida!\n";
        }
    }

    return 0;
}
