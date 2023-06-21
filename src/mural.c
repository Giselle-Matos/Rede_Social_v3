#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rede_social.h"
#include "mural.h"

void Liberar_posts(struct dados_user **lista_posts)
{
    struct dados_user *atual = *lista_posts;
    while (atual != NULL)
    {
        struct dados_user *temp = atual;
        atual = atual->prox;
        free(temp);
    }
    *lista_posts = NULL; // Define a lista como vazia
}

void Apaga_post(struct posts **lista_posts, int post_number)
{
    if (*lista_posts == NULL)
    {
        printf("Nenhum post encontrado.\n");
        return;
    }

    if (post_number < 1)
    {
        printf("Numero do post inválido.\n");
        return;
    }

    if (post_number == 1)
    {
        struct posts *temp = *lista_posts;
        *lista_posts = (*lista_posts)->prox;
        free(temp);
        printf("Post apagado com sucesso.\n");
        return;
    }

    struct posts *anterior = *lista_posts;
    struct posts *atual = (*lista_posts)->prox;
    int i = 2;

    while (atual != NULL)
    {
        if (i == post_number)
        {
            anterior->prox = atual->prox;
            free(atual);
            printf("Post apagado com sucesso.\n");
            return;
        }
        anterior = atual;
        atual = atual->prox;
        i++;
    }

    printf("Post nao encontrado.\n");
}

void Busca_posts(struct dados_user *lista_usuarios, char busca_post_user[50])
{
    struct dados_user *atual = lista_usuarios;
    int i = 1;
    int encontrou = 0;

    while (atual != NULL)
    {
        struct posts *atual_post = atual->posts;
        while (atual_post != NULL)
        {
            if (strcmp(atual_post->user_post, busca_post_user) == 0)
            {
                printf("User: %s - Post %d\n %s\n", atual_post->user_post, i, atual_post->postagem);
                encontrou = 1;
                i++;
            }
            atual_post = atual_post->prox;
        }
        atual = atual->prox;
    }

    if (!encontrou)
    {
        printf("Nenhum post encontrado para o usuario '%s'\n", busca_post_user);
    }
}

void Mostra_posts(struct dados_user *lista_usuarios)
{
    int i = 1;

    struct dados_user *atual = lista_usuarios;
    while (atual != NULL)
    {
        struct posts *atual_post = atual->posts;
        while (atual_post != NULL)
        {
            printf("Post [%d] - User: %s\n %s\n", i, atual_post->user_post, atual_post->postagem);
            atual_post = atual_post->prox;
            i++;
        }
        atual = atual->prox;
    }

    if (i == 1)
    {
        printf("Nenhum post disponivel.\n");
    }
}

void Postar(struct posts **lista_posts, char user[50])
{
    char postagem[500];
    printf("Digite sua postagem: ");
    getchar(); // Limpa o buffer do teclado
    fgets(postagem, sizeof(postagem), stdin);
    postagem[strcspn(postagem, "\n")] = '\0'; // Remove o caractere de nova linha do final da string

    struct posts *novo_post = (struct posts*) malloc(sizeof(struct posts));
    strcpy(novo_post->user_post, user);
    strcpy(novo_post->postagem, postagem);
    novo_post->prox = NULL;

    if (*lista_posts == NULL)
    {
        *lista_posts = novo_post;
    }
    else
    {
        struct posts *atual = *lista_posts;
        while (atual->prox != NULL)
        {
            atual = atual->prox;
        }
        atual->prox = novo_post;
    }

    printf("Postagem realizada com sucesso!\n");
}


void Exibe_mural(struct dados_user *usuario_logado, struct dados_user *lista_usuarios)
{
    int choice_mural, break_mural = 0;
    char busca_post_user[50];
    int post_number;

    while (break_mural == 0)
    {
        printf("\nOpcoes do mural:\n");
        printf("[1] Postar\n");
        printf("[2] Ver posts\n");
        printf("[3] Buscar posts de um usuario\n");
        printf("[4] Apagar post\n");
        printf("[5] Voltar para o menu principal\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &choice_mural);

        switch (choice_mural)
        {
            case 1:
                clearScreen();
                Postar(&usuario_logado->posts, usuario_logado->nome_user);
                break;
            case 2:
                clearScreen();
                Mostra_posts(usuario_logado);
                break;
            case 3:
                clearScreen();
                printf("Digite o nome do usuario: ");
                scanf("%s", busca_post_user);
                Busca_posts(lista_usuarios, busca_post_user);
                break;
            case 4:
                clearScreen();
                printf("Digite o numero do post que deseja apagar: ");
                scanf("%d", &post_number);
                Apaga_post(&usuario_logado->posts, post_number);
                break;
            case 5:
                clearScreen();
                break_mural = 1;
                break;
            default:
                printf("Opcao invalida. Digite novamente.\n");
                break;
        }
    }
}

