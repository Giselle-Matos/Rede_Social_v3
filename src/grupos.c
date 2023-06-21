#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rede_social.h"
#include "grupos.h"

void Liberar_mural_grupo(struct mural_grupo *mural_g)
{
    struct mural_grupo *atual = mural_g;
    while (atual != NULL)
    {
        struct mural_grupo *prox = atual->prox;
        free(atual);
        atual = prox;
    }
}



void Liberar_grupo_users(struct grupos_users *usuarios)
{
    struct grupos_users *atual = usuarios;
    while (atual != NULL)
    {
        struct grupos_users *prox = atual->prox;
        free(atual);
        atual = prox;
    }
}

void Liberar_grupos(struct grupos **lista_grupos)
{
    struct grupos *atual = *lista_grupos;
    while (atual != NULL)
    {
        struct grupos *prox = atual->prox;

        // Liberar a memória dos usuários do grupo
        Liberar_grupo_users(atual->usuarios);
        Liberar_mural_grupo(atual->mural_g);
        free(atual);
        atual = prox;
    }
    *lista_grupos = NULL;
}

struct mural_grupo *Cria_post_grupo(struct dados_user *usuario_logado)
{
    struct mural_grupo *novo_post = (struct mural_grupo *)malloc(sizeof(struct mural_grupo));
    strcpy(novo_post->user_post, usuario_logado->nome_user);
    getchar();
    printf("Digite o texto do post: ");
    fgets(novo_post->post, sizeof(novo_post->post), stdin);
    novo_post->post[strcspn(novo_post->post, "\n")] = '\0';
    novo_post->prox = NULL;
    strcpy(novo_post->user_post, usuario_logado->nome_user);

    return novo_post;
}

void Adiciona_post_grupo(struct dados_user *usuario_logado, struct grupos *grupo)
{
    if (grupo != NULL)
    {
        // Check if the user is a member of the group
        struct grupos_users *integrante_atual = grupo->usuarios;
        while (integrante_atual != NULL)
        {
            if (strcmp(integrante_atual->nome_users, usuario_logado->nome_user) == 0)
            {
                // User is a member of the group, allow adding the post
                struct mural_grupo *novo_post = Cria_post_grupo(usuario_logado);
                if (grupo->mural_g == NULL)
                {
                    grupo->mural_g = novo_post;
                }
                else
                {
                    struct mural_grupo *mural_atual = grupo->mural_g;
                    while (mural_atual->prox != NULL)
                    {
                        mural_atual = mural_atual->prox;
                    }
                    mural_atual->prox = novo_post;
                }
                printf("Post adicionado ao mural do grupo!\n");
                return;
            }
            integrante_atual = integrante_atual->prox;
        }
        printf("Você nao e membro deste grupo.\n");
    }
    else
    {
        printf("Você nao esta em nenhum grupo.\n");
    }
}

void Mostra_mural_grupo(struct mural_grupo *mural_g)
{
    int i = 1;
    struct mural_grupo *mural_atual = mural_g;
    while (mural_atual != NULL)
    {
        printf("Post [%d] - User: %s\n %s\n\n", i, mural_atual->user_post, mural_atual->post);
        mural_atual = mural_atual->prox;
        i++;
    }
    if(i==1){
        printf("Nao ha posts\n");
    }
}
char *Pesquisa_grupo(struct dados_user *usuario_logado, struct grupos *lista_grupos)
{
    char nome_grupo[50];
    int choice_mural;
    getchar();
    printf("Digite o nome do grupo: ");
    fgets(nome_grupo, sizeof(nome_grupo), stdin);
    nome_grupo[strcspn(nome_grupo, "\n")] = '\0';

    struct grupos *grupo_atual = lista_grupos;

    while (grupo_atual != NULL)
    {
        if (strcmp(grupo_atual->nome_grupo, nome_grupo) == 0)
        {
            printf("\nGrupo encontrado!\n\n");
            printf("Nome: %s\n", grupo_atual->nome_grupo);
            printf("Lider: %s\n", grupo_atual->lider_grupo);
            printf("Descricao: %s\n", grupo_atual->descricao);
            printf("Integrantes: \n");

            // conta o numero de integrantes do grupo
            struct grupos_users *integrante_atual = grupo_atual->usuarios;
            int num_integrantes = 0;

            while (integrante_atual != NULL)
            {
                num_integrantes++;
                integrante_atual = integrante_atual->prox;
            }
            // cria um array de structs para guardar os nomes e nos dos membros dos grupos
            struct grupos_users **integrantes_ordenados = (struct grupos_users **)malloc(num_integrantes * sizeof(struct grupos_users *));

            // preenche o array com os nomes e os nos dos membros dos grupos
            integrante_atual = grupo_atual->usuarios;
            int i = 0;
            while (integrante_atual != NULL)
            {
                integrantes_ordenados[i] = integrante_atual;
                i++;
                integrante_atual = integrante_atual->prox;
            }

            // ordena o array em ordem alfabetica baseado nos nomes dos integrantes dos grupos
            for (int i = 0; i < num_integrantes - 1; i++)
            {
                for (int j = i + 1; j < num_integrantes; j++)
                {
                    if (strcmp(integrantes_ordenados[i]->nome_users, integrantes_ordenados[j]->nome_users) > 0)
                    {
                        struct grupos_users *temp = integrantes_ordenados[i];
                        integrantes_ordenados[i] = integrantes_ordenados[j];
                        integrantes_ordenados[j] = temp;
                    }
                }
            }

            for (int i = 0; i < num_integrantes; i++)
            {
                printf("%s\n", integrantes_ordenados[i]->nome_users);
            }

            printf("\n[1] Ver posts\n[2] Adicionar post\n[3] Voltar\nSua resposta: ");
            scanf("%d", &choice_mural);
            if (choice_mural == 1)
            {
                Mostra_mural_grupo(grupo_atual->mural_g);
            }
            else if (choice_mural == 2)
            {
                Adiciona_post_grupo(usuario_logado, grupo_atual);
            }

            free(integrantes_ordenados);

            return grupo_atual->nome_grupo;
        }
        grupo_atual = grupo_atual->prox;
    }

    printf("\nGrupo não encontrado!\n");
    return NULL;
}

void Entra_grupo(struct dados_user *usuario_logado, struct grupos **lista_grupos)
{
    char *nome_grupo = Pesquisa_grupo(usuario_logado, *lista_grupos);

    if (nome_grupo != NULL)
    {
        struct grupos *grupo_atual = *lista_grupos;

        while (grupo_atual != NULL)
        {
            if (strcmp(grupo_atual->nome_grupo, nome_grupo) == 0)
            {
                struct grupos_users *novo_usuario_grupo = (struct grupos_users *)malloc(sizeof(struct grupos_users));
                strcpy(novo_usuario_grupo->nome_users, usuario_logado->nome_user);
                novo_usuario_grupo->prox = NULL;

                if (grupo_atual->usuarios == NULL)
                {
                    grupo_atual->usuarios = novo_usuario_grupo;
                }
                else
                {
                    struct grupos_users *usuario_grupo_temp = grupo_atual->usuarios;
                    while (usuario_grupo_temp->prox != NULL)
                    {
                        usuario_grupo_temp = usuario_grupo_temp->prox;
                    }
                    usuario_grupo_temp->prox = novo_usuario_grupo;
                }

                printf("Voce entrou no grupo!\n");
                return;
            }
            grupo_atual = grupo_atual->prox;
        }
    }
    else
    {
        printf("Grupo nao encontrado!\n");
    }
}
void Cria_grupo(struct dados_user *usuario_logado, struct grupos **lista_grupos)
{
    int choice_description = 0;
    struct grupos *grupo_atual = (struct grupos *)malloc(sizeof(struct grupos));
    printf("Digite o nome do grupo: ");
    getchar();
    fgets(grupo_atual->nome_grupo, sizeof(grupo_atual->nome_grupo), stdin);
    grupo_atual->nome_grupo[strcspn(grupo_atual->nome_grupo, "\n")] = '\0';
    printf("Deseja adicionar uma descricao ao grupo? [s=1/n=0]\nSua resposta: ");
    scanf("%d", &choice_description);
    if (choice_description == 1)
    {
        printf("Digite a descricao: ");
        getchar();
        fgets(grupo_atual->descricao, sizeof(grupo_atual->descricao), stdin);
        grupo_atual->descricao[strcspn(grupo_atual->descricao, "\n")] = '\0';
    }
    strcpy(grupo_atual->lider_grupo, usuario_logado->nome_user);
    printf("Grupo criado!\nObservacao: voce e o lider do grupo.\n\n");

    // Adicionar o grupo ao usuário logado
    if (usuario_logado->grupo == NULL)
    {
        usuario_logado->grupo = grupo_atual;

        // Adicionar o usuário criador à lista de integrantes do grupo
        struct grupos_users *novo_usuario_grupo = (struct grupos_users *)malloc(sizeof(struct grupos_users));
        strcpy(novo_usuario_grupo->nome_users, usuario_logado->nome_user);
        novo_usuario_grupo->prox = NULL;
        grupo_atual->usuarios = novo_usuario_grupo;
    }
    else
    {
        struct grupos *grupo_temp = usuario_logado->grupo;
        while (grupo_temp->prox != NULL)
        {
            grupo_temp = grupo_temp->prox;
        }
        grupo_temp->prox = grupo_atual;
    }

    // Adicionar o grupo à lista de grupos global
    if (*lista_grupos == NULL)
    {
        *lista_grupos = grupo_atual;
    }
    else
    {
        struct grupos *grupo_temp = *lista_grupos;
        while (grupo_temp->prox != NULL)
        {
            grupo_temp = grupo_temp->prox;
        }
        grupo_temp->prox = grupo_atual;
    }
}

void Exibe_grupos(struct dados_user *usuario_logado)
{
    int choice_grupos = 0;
    while (choice_grupos != 4)
    {
        if (lista_grupos == NULL)
        {
            printf("Nenhum grupo disponivel.\n");
        }
        else
        {
            printf("Grupos\n");
            struct grupos *grupo_atual = lista_grupos;
            while (grupo_atual != NULL)
            {
                if (grupo_atual->nome_grupo != NULL)
                {
                    printf("\n%s\n\n", grupo_atual->nome_grupo);
                }
                grupo_atual = grupo_atual->prox;
            }
        }

        printf("[1] Criar grupo\n[2] Entrar em um grupo\n[3] Pesquisar Grupo\n[4] Voltar\nSua resposta: ");
        scanf("%d", &choice_grupos);

        switch (choice_grupos)
        {
        case 1:
            clearScreen();
            Cria_grupo(usuario_logado, &lista_grupos);
            break;
        case 2:
            clearScreen();
            Entra_grupo(usuario_logado, &lista_grupos);
            break;
        case 3:
            clearScreen();
            Pesquisa_grupo(usuario_logado, lista_grupos);
            break;
        case 4:
            clearScreen();
            break;
        default:
            printf("Opcao invalida!\n");
        }
    }
}
