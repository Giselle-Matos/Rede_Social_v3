#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "rede_social.h"
#include "login_cadastro.h"

// login e cadastro
struct dados_user *Criar_usuario()
{
    struct dados_user *novo_usuario = (struct dados_user *)malloc(sizeof(struct dados_user));
    if (novo_usuario == NULL)
    {
        printf("\nErro ao alocar memoria para novo usuario\n");
        return NULL;
    }
    novo_usuario->prox = NULL;
    return novo_usuario;
}

void Adicionar_usuario(struct dados_user **lista_usuarios, struct dados_user *novo_usuario)
{
    novo_usuario->prox = NULL;
    if (*lista_usuarios == NULL)
    {
        *lista_usuarios = novo_usuario; // Insere o novo usuário como o primeiro nó
    }
    else
    {
        struct dados_user *atual = *lista_usuarios;
        while (atual->prox != NULL)
        {
            atual = atual->prox; // Percorre a lista até o último nó
        }
        atual->prox = novo_usuario; // Adiciona o novo usuário após o último nó
    }
}

void Liberar_usuarios(struct dados_user **lista_usuarios)
{
    struct dados_user *atual = *lista_usuarios;
    while (atual != NULL)
    {
        struct dados_user *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    *lista_usuarios = NULL;
}

void Login(struct dados_user **lista_usuarios, int *login_sucesso, struct dados_user **usuario_logado)
{
    char tam_max = 50;
    char nome_user_verifica[tam_max];
    char senha_user_verifica[tam_max];
    char ch;
    getchar();
    printf("Digite o nome de usuario: ");
    fgets(nome_user_verifica, sizeof(nome_user_verifica), stdin);
    nome_user_verifica[strcspn(nome_user_verifica, "\n")] = '\0'; // Remove o '\n' da string

    printf("Digite a senha: ");
    int i = 0;
    while ((ch = getch()) != '\r')
    { // Verifica se a tecla Enter foi pressionada
        if (ch == '\b')
        { // Verifica se o backspace foi pressionado
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else if (i < tam_max - 1)
        {
            senha_user_verifica[i] = ch;
            i++;
            printf("*");
        }
    }
    senha_user_verifica[i] = '\0';
    struct dados_user *atual = *lista_usuarios;
    while (atual != NULL)
    {
        int verifica_nome = strcmp(nome_user_verifica, atual->nome_user);
        int verifica_senha = strcmp(senha_user_verifica, atual->senha_user);

        if (verifica_nome == 0 && verifica_senha == 0)
        {
            clearScreen();
            printf("\nLogin efetuado com sucesso!\n");
            printf("Ola, %s\n", atual->nome_user);

            *login_sucesso = 1;
            *usuario_logado = atual;
            break;
        }
        atual = atual->prox;
    }
    if (*login_sucesso == 0)
    {
        printf("\n\nNome de usuário ou senha inválidos!\n");
    }
}

void Criar_conta(struct dados_user **lista_usuarios)
{
    int tam_max = 50;
    char ch;
    struct dados_user *novo_usuario = Criar_usuario();
    if (novo_usuario == NULL)
    {
        return;
    }
    printf("\nDigite o nome de usuario: ");
    fgets(novo_usuario->nome_user, sizeof(novo_usuario->nome_user), stdin);
    novo_usuario->nome_user[strcspn(novo_usuario->nome_user, "\n")] = '\0'; // Remove o '\n' da string

    printf("Digite a senha: ");

    int i = 0;
    char senha_user[tam_max];
    while ((ch = getch()) != '\r')
    { // Verifica se a tecla Enter foi pressionada
        if (ch == '\b')
        { // Verifica se o backspace foi pressionado
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else if (i < tam_max - 1)
        {
            senha_user[i] = ch;
            i++;
            printf("*");
        }
    }
    senha_user[i] = '\0';
    strncpy(novo_usuario->senha_user, senha_user, sizeof(novo_usuario->senha_user));

    novo_usuario->posts = NULL;

    Adicionar_usuario(lista_usuarios, novo_usuario);
}