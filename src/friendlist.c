#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rede_social.h"
#include "friendlist.h"


void Listar_amigos(struct dados_user *usuario_logado)
{
    int choice_lista = 0;
    int i, j, swapped;
    int n = 0;
    struct dados_user *amigo = usuario_logado->lista_amigos;
    struct dados_user *temp;

    // Conta o número de amigos
    while (amigo != NULL) {
        n++;
        amigo = amigo->prox;
    }

    // Cria um array de amigos
    struct dados_user *amigos[n];
    amigo = usuario_logado->lista_amigos;

    for (i = 0; i < n; i++) {
        amigos[i] = amigo;
        amigo = amigo->prox;
    }

    // Ordena
    for (i = 0; i < n - 1; i++) {
        swapped = 0;
        for (j = 0; j < n - i - 1; j++) {
            if (strcmp(amigos[j]->nome_user, amigos[j + 1]->nome_user) > 0) {
                temp = amigos[j];
                amigos[j] = amigos[j + 1];
                amigos[j + 1] = temp;
                swapped = 1;
            }
        }

        if (swapped == 0)
            break;
    }

    printf("Lista de amigos de %s:\n\n", usuario_logado->nome_user);

    for (i = 0; i < n; i++) {
        printf("- %s\n", amigos[i]->nome_user);
    }

    printf("[1] Ver lista de amigos dos amigos\n[2] Voltar\nSua resposta: ");
    scanf("%d", &choice_lista);

    if (choice_lista == 1) {
        clearScreen();
        int encontrou = 0;
        char amigo[50];
        getchar();
        printf("Digite o nome do amigo que deseja ver a lista de amigos: ");
        fgets(amigo, sizeof(amigo), stdin);
        amigo[strcspn(amigo, "\n")] = '\0';

        // Busca pelo amigo na lista de amigos do usuario_logado
        struct dados_user *amigo_busca = usuario_logado->lista_amigos;

        while (amigo_busca != NULL) {
            if (strcmp(amigo_busca->nome_user, amigo) == 0) {
                printf("Amigo encontrado!\n\n");
                Listar_amigos(amigo_busca);
                encontrou = 1;
                break;
            }
            amigo_busca = amigo_busca->prox;
        }

        if (encontrou == 0) {
            printf("\nAmigo nao encontrado\n");
        }
        
    }
}

void Remove_amigo(struct dados_user *usuario_logado, char *username_friend)
{
    struct dados_user *amigo = usuario_logado->lista_amigos;
    struct dados_user *anterior = NULL;

    if (amigo != NULL && strcmp(amigo->nome_user, username_friend) == 0) {
        usuario_logado->lista_amigos = amigo->prox;
        free(amigo);
        printf("Amigo removido com sucesso!\n");
        return;
    }

    while (amigo != NULL && strcmp(amigo->nome_user, username_friend) != 0) {
        anterior = amigo;
        amigo = amigo->prox;
    }

    if (amigo != NULL) {
        anterior->prox = amigo->prox;
        free(amigo);
        printf("Amigo removido com sucesso!\n");
    } else {
        printf("Usuário nao encontrado.\n");
    }
}

void Union(struct dados_user *rep1, struct dados_user *rep2)
{
    if (rep1->rank > rep2->rank) {
        rep2->parent = rep1;
    } else if (rep1->rank < rep2->rank) {
        rep1->parent = rep2;
    } else {
        rep2->parent = rep1;
        rep1->rank++;
    }
}

void Make_set(struct dados_user **lista_usuarios)
{
    struct dados_user *atual = *lista_usuarios;

    while (atual != NULL) {
        atual->parent = atual;
        atual->rank = 0;
        atual = atual->prox;
    }
}

struct dados_user *Find_set(struct dados_user *usuario)
{
    if (usuario != usuario->parent)
        usuario->parent = Find_set(usuario->parent);
    return usuario->parent;
}

void Find_friendship(struct dados_user *usuario_logado, char *username_friend, struct dados_user **lista_usuarios)
{
    if (strcmp(usuario_logado->nome_user, username_friend) == 0) {
        printf("Voce nao pode adicionar a si mesmo como amigo.\n");
        return;
    }

    struct dados_user *atual = *lista_usuarios;
    struct dados_user *user_found = NULL;

    while (atual != NULL) {
        if (strcmp(atual->nome_user, username_friend) == 0) {
            printf("Usuario encontrado!\n");
            user_found = atual;
            break;
        }
        atual = atual->prox;
    }

    if (user_found == NULL) {
        printf("Usuario nao encontrado.\n");
        return;
    }

    struct dados_user *amigo = usuario_logado->lista_amigos;
    while (amigo != NULL) {
        if (strcmp(amigo->nome_user, username_friend) == 0) {
            printf("Voces ja sao amigos!\n");
            return;
        }
        amigo = amigo->prox;
    }

    struct dados_user *rep1 = Find_set(user_found);
    struct dados_user *rep2 = Find_set(usuario_logado);
    if (rep1 != rep2) {
        Union(rep1, rep2);
        printf("\nAgora voces sao amigos!\n");

        struct dados_user *novo_amigo = (struct dados_user *)malloc(sizeof(struct dados_user));
        strcpy(novo_amigo->nome_user, user_found->nome_user);
        novo_amigo->lista_amigos = NULL;
        novo_amigo->prox = usuario_logado->lista_amigos;
        usuario_logado->lista_amigos = novo_amigo;

        novo_amigo = (struct dados_user *)malloc(sizeof(struct dados_user));
        strcpy(novo_amigo->nome_user, usuario_logado->nome_user);
        novo_amigo->lista_amigos = NULL;
        novo_amigo->prox = user_found->lista_amigos;
        user_found->lista_amigos = novo_amigo;
    }
}

void Adiciona_amigo(struct dados_user *usuario_logado, struct dados_user **lista_usuarios, char *username_friend)
{
    Find_friendship(usuario_logado, username_friend, lista_usuarios);
}

void Main_friendlist(struct dados_user *usuario_logado, struct dados_user **lista_usuarios)
{
    int friend_choice;
    int friend_control = 0;
    char username_friend[50];

    Make_set(lista_usuarios);

    while (friend_control == 0) {
        printf("\nLista de Amigos\n\n[1] Adicionar Amigos\n[2] Listar amigos\n[3] Remover amigos\n[4] Voltar\nSua escolha: ");
        scanf("%d", &friend_choice);
        getchar();

        switch (friend_choice) {
            case 1:
                clearScreen();
                printf("Digite o nome do usuario que deseja adicionar como amigo: ");
                fgets(username_friend, sizeof(username_friend), stdin);
                username_friend[strcspn(username_friend, "\n")] = '\0';
                Adiciona_amigo(usuario_logado, lista_usuarios, username_friend);
                break;
            case 2:
                clearScreen();
                Listar_amigos(usuario_logado);
                break;
            case 3:
                clearScreen();
                printf("Digite o nome do usuario que deseja desfazer amizade: ");
                fgets(username_friend, sizeof(username_friend), stdin);
                username_friend[strcspn(username_friend, "\n")] = '\0';
                Remove_amigo(usuario_logado, username_friend);
                break;
            case 4:
                clearScreen();
                friend_control = 1;
                break;
            default:
                break;
        }
    }
}
