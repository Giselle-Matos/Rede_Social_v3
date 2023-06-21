// rede_social.h
#ifndef REDE_SOCIAL_H
#define REDE_SOCIAL_H

/**
 * struct mural_grupo: responsavel pelo armazenamento dos dados dos posts
 * dos murais dos grupos, contendo o nome do usuario que criou
 *  determinado post, o conteudo do post em si e um ponteiro para a 
 * struct mural_grupo
*/

struct mural_grupo {
    char user_post[50];
    char post[500];
    struct mural_grupo *prox;
};

/**
 * struct grupos_users: responsavel pelo armazenamento do nome dos usuarios 
 * integrantes de um grupo, contendo: nome do usuario integrante, ponteiro
 * para struct grupo_users
*/

struct grupos_users{
    char nome_users[500];
    struct grupos_users *prox;
};

/**
 * Struct grupos: responsavel pelo armazenamento dos dados dos grupos criados, contendo:
 * nome do grupo, lider do grupo, descrição do grupo, ponteiro para a struct mural_grupo,
 * ponteiro para a struct grupos e ponteiro para a struct grupo_users
*/

struct grupos { 
    char nome_grupo[50];
    char lider_grupo[50];
    char descricao[500];
    struct mural_grupo *mural_g;
    struct grupos *prox;
    struct grupos_users *usuarios;
};

/**
 * Struct posts: struct responsavel pelo armazenamento das mensagens dos usuários, formando uma
 * lista encadeada. Cada nó dessa lista encadeada contem a postagem do usuário, o nome
 * do usuario que a criou e um ponteiro para o próximo nó.
*/

struct mensagens { 
    char user_send[50];
    char user_receive[50];
    char text[10000];
    struct mensagens *prox;
};

/**
 * Struct posts: struct responsavel pelo armazenamento das postagens dos usuários, formando uma
 * lista encadeada. Cada nó dessa lista encadeada contem a postagem do usuário, o nome
 * do usuario que a criou e um ponteiro para o próximo nó.
 */

struct posts
{
    char user_post[50];
    char postagem[500];
    struct posts *prox;
};

/**
 * Struct dados_user: struct responsável pelo armazenamento dos dados dos usuários
 */


struct dados_user {
    int rank;
    char nome_user[50];
    char senha_user[50];
    char nome_completo_user[128];
    char ocupacao_social_user[128];
    char endereco_user[128];
    char biografia_user[501];
    struct dados_user *parent;
    struct dados_user *prox;
    struct posts *posts;
    struct dados_user *lista_amigos;
    struct mensagens *mensagem;
    struct grupos *grupo;
};

/**
 * extern struct dados_user *usuario_logado: declaração de nó do tipo
 * struct dados_user responsável por armazenar os dados de todos os grupos 
 * cadastrados no sistema.
*/

extern struct grupos* lista_grupos;

/*!
 * extern struct dados_user *usuario_logado: declaração de nó do tipo
 * struct dados_user responsável por armazenar os dados do usuário
 * que está logado no sistema no momento.
 *
 */

extern struct dados_user *usuario_logado;

/**
 * clearScreen(): função do <windows.h> responsavel por limpar a tela do terminal
*/

void clearScreen();

/**
 * setConsoleColor(): função do <windows.h> responsavel pela escolha das cores
 * do que é apresentado no terminal 
*/

void setConsoleColor(int color);

#endif