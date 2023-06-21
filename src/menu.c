#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "rede_social.h"
#include "perfil.h"
#include "mural.h"
#include "troca_senha.h"
#include "friendlist.h"
#include "chats.h"
#include "grupos.h"
#include "menu.h"

void Exibir_menu(int *choice_menu, struct dados_user *usuario_logado, int *login_sucesso, struct dados_user **lista_usuarios)
{

    printf("Menu: \n1 - Perfil\n2 - Mural\n3 - Lista de amigos\n4 - Mensagens\n5 - Trocar senha\n6 - Grupos\n7 - Log-out\nSua escolha: ");
    scanf("%d", &*choice_menu);
    switch (*choice_menu)
    {
    case 1:
        clearScreen();
        Exibe_perfil(usuario_logado, lista_usuarios);
        break;
    case 2:
        clearScreen();
        usuario_logado->posts = NULL;
        Exibe_mural(usuario_logado, *lista_usuarios);
        break;
    case 3:
        clearScreen();
        Main_friendlist(usuario_logado, lista_usuarios);
        break;
    case 4:
        clearScreen();
        Exibe_chats(usuario_logado, lista_usuarios);
        break;
    case 5:
        clearScreen();
        Troca_senha(usuario_logado);
        break;
    case 6:
        clearScreen();
        Exibe_grupos(usuario_logado);
        break;
    case 7:
        clearScreen();
        *login_sucesso = 0;
        *choice_menu = 0;
        printf("Deslogando...\n");
        break;
    }
    // Reinicializar a variável choice_menu para 1 após o logout
    if (*choice_menu == 0)
    {
        *choice_menu = 1;
    }
}
