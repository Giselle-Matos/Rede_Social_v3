#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rede_social.h"
#include "chats.h"

void Liberar_mensagens()
{
    struct mensagens *mensagem_atual = usuario_logado->mensagem;
    struct mensagens *mensagem_prox;

    while (mensagem_atual != NULL)
    {
        mensagem_prox = mensagem_atual->prox;
        free(mensagem_atual);
        mensagem_atual = mensagem_prox;
    }

    usuario_logado->mensagem = NULL;
}


void Enviar_mensagem(struct dados_user *usuario_logado, struct dados_user *user_send)
{
    char mensagem[10000];
    getchar();
    printf("Digite sua mensagem: ");
    fgets(mensagem, sizeof(mensagem), stdin);
    mensagem[strcspn(mensagem, "\n")] = '\0'; // Remove o '\n' da string

    // Crie uma nova mensagem
    struct mensagens *nova_mensagem = (struct mensagens *)malloc(sizeof(struct mensagens));
    strcpy(nova_mensagem->text, mensagem);
    strcpy(nova_mensagem->user_send, usuario_logado->nome_user);
    strcpy(nova_mensagem->user_receive, user_send->nome_user);
    nova_mensagem->prox = NULL;

    // Verifique se a lista de mensagens do usuário receptor está vazia
    if (user_send->mensagem == NULL)
    {
        user_send->mensagem = nova_mensagem;
    }
    else
    {
        // Percorra a lista de mensagens até o final
        struct mensagens *mensagem_atual = user_send->mensagem;
        while (mensagem_atual->prox != NULL)
        {
            mensagem_atual = mensagem_atual->prox;
        }

        // Adicione a nova mensagem no final da lista
        mensagem_atual->prox = nova_mensagem;
    }

    printf("Mensagem enviada com sucesso!\n");
}

void Pesquisa_chat(struct dados_user *usuario_logado, struct dados_user **lista_usuarios)
{
    char username_search[50];
    int choice_search;
    getchar();
    printf("Digite o nome do usuario: ");
    fgets(username_search, sizeof(username_search), stdin);
    username_search[strcspn(username_search, "\n")] = '\0'; // Remove o '\n' da string

    struct dados_user *atual = *lista_usuarios;

    while (atual != NULL)
    {
        if (strcmp(atual->nome_user, username_search) == 0)
        {
            printf("Usuario encontrado\n[1] Enviar mensagem\n[2] Voltar\n");
            scanf("%d", &choice_search);
            if (choice_search == 1)
            {
                clearScreen();
                Enviar_mensagem(usuario_logado, atual);
            }
            break;
        }
        atual = atual->prox;
    }

    if (atual == NULL)
    {
        printf("Usuario nao encontrado\n");
    }
}


void Exibe_chats(struct dados_user *usuario_logado, struct dados_user **lista_usuarios)
{
    int num_chat, i = 0, choice_chat = 0, aux = 0;
    printf("Chats\nConversas\n\n");

    // Printar todos os usuários disponíveis no sistema
    struct dados_user *user_atual = *lista_usuarios;
    printf("Usuarios Disponiveis: \n");
    while (user_atual != NULL)
    {
        printf("[%d] %s\n", i, user_atual->nome_user);
        i++;
        user_atual = user_atual->prox;
    }
    i = 0;

    printf("Caixa de entrada: \n\n");

    // Exibir apenas as mensagens endereçadas ao usuário logado
    struct mensagens *mensagem_atual = usuario_logado->mensagem;
    int total_mensagens = 0;
    while (mensagem_atual != NULL)
    {
        total_mensagens++;
        mensagem_atual = mensagem_atual->prox;
    }

    // Armazenar as mensagens em um vetor temporário
    struct mensagens **mensagens_temp = (struct mensagens **)malloc(total_mensagens * sizeof(struct mensagens *));
    mensagem_atual = usuario_logado->mensagem;
    i = 0;
    while (mensagem_atual != NULL)
    {
        mensagens_temp[i] = mensagem_atual;
        mensagem_atual = mensagem_atual->prox;
        i++;
    }

    // Exibir as mensagens em ordem inversa
    for (i = total_mensagens - 1; i >= 0; i--)
    {
        printf("[%d] %s - %s\n", i, mensagens_temp[i]->user_send, mensagens_temp[i]->text);
    }

    printf("Para ver uma mensagem da caixa de entrada, digite o numero do chat: ");
    scanf("%d", &num_chat);

    if (num_chat >= 0 && num_chat < total_mensagens)
    {
        printf("%s - %s\n\n", mensagens_temp[num_chat]->user_send, mensagens_temp[num_chat]->text);

        // Remover a mensagem da lista
        mensagem_atual = usuario_logado->mensagem;
        struct mensagens *mensagem_anterior = NULL;
        i = 0;
        while (mensagem_atual != NULL)
        {
            if (i == num_chat)
            {
                if (mensagem_anterior == NULL)
                {
                    usuario_logado->mensagem = mensagem_atual->prox;
                }
                else
                {
                    mensagem_anterior->prox = mensagem_atual->prox;
                }

                struct mensagens *mensagem = mensagem_atual;
                mensagem_atual = mensagem_atual->prox;
                free(mensagem);
                aux = 1;
                break;
            }

            mensagem_anterior = mensagem_atual;
            mensagem_atual = mensagem_atual->prox;
            i++;
        }
    }
    else
    {
        printf("Conversa nao encontrada\n\n");
    }

    free(mensagens_temp);

    while (choice_chat != 2)
    {
        printf("[1] Pesquisar Usuario\n[2] Voltar\nSua resposta: ");
        scanf("%d", &choice_chat);

        if (choice_chat == 1)
        {
            clearScreen();
            Pesquisa_chat(usuario_logado, lista_usuarios);
        }
    }
}
