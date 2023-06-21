#include <stdio.h>
#include <stdlib.h>
#include "rede_social.h"
#include "login_cadastro.h"
#include "perfil.h"
#include "mural.h"
#include "grupos.h"
#include "menu.h"
#include <windows.h>

#define YELLOW  14

// observações: o trabalho foi criado em ambiente windows, portanto, 
// é possivel que algumas funcionalidades so funcionem apropriadamente 
// atraves desse S.O. 

void setConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void clearScreen() {
    system("cls");
}

struct dados_user *usuario_logado = NULL;
struct grupos* lista_grupos = NULL;
//struct posts *lista_posts = NULL;

int main(void)
{
	struct dados_user *lista_usuarios = (struct dados_user *)malloc(sizeof(struct dados_user));
	lista_usuarios = NULL;

	int choice_inicio, login_sucesso = 0, choice_menu = 1, choice_main = 1;
	while (choice_main != 0)
	{ // criar um loop infinito proposital
		setConsoleColor(YELLOW);

		printf("\nBem-Vindo a Rede Social!\n");
		printf("Selecione uma opcao:\n\n1 - Criar uma conta\n2 - Logar em uma conta existente\n3 - Sair\nSua resposta: ");
		scanf("%d", &choice_inicio);
		getchar(); // Consumir o caractere de nova linha pendente
		
		clearScreen();
		switch (choice_inicio)
		{
		case 1:
			printf("Vamos criar uma conta!\n");
			Criar_conta(&lista_usuarios);
			
			printf("\nDeseja logar? [S=1/N=0]\nSua resposta: ");
			scanf("%d", &choice_inicio);
			if (choice_inicio == 0)
			{
				break;
			}

		case 2:
			clearScreen();
			printf("Ola! Vamos fazer o login\nSe necessario, pressione qualquer tecla para continuar\n");
			Login(&lista_usuarios, &login_sucesso, &usuario_logado);
			break;
		case 3:
			clearScreen();
			Liberar_usuarios(&lista_usuarios);
			Liberar_grupos(&lista_grupos);
			Liberar_posts(&lista_usuarios);
			Liberar_mensagens();
			login_sucesso = 0;
			printf("Saindo...\n");
			return 0;
		default:
			printf("Opcao invalida!\n");
			break;
		}

		while (login_sucesso == 1 && choice_menu != 0)
		{

			Exibir_menu(&choice_menu, usuario_logado, &login_sucesso, &lista_usuarios);
		}
	}
	return 0;
}