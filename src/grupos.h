#ifndef GRUPOS_H
#define GRUPOS_H

/**
 * Liberar_grupo_users(): responsavel por liberar a memoria alocada para os 
 * nos da struct grupo_users, contendo a informação dos usuarios presentes
 * em determinado grupo.
*/


void Liberar_grupo_users(struct grupos_users *usuarios);

/**
 * Liberar_mensagens(): responsavel por liberar a memoria alocada para os nos da 
 * struct mensagens
*/

void Liberar_mensagens();

/**
 * Liberar_grupos(): responsavel por liberar a memoria alocada para os nos da 
 * struct grupos presentes na lista encadeada lista_grupos
 * @param struct grupos **lista_grupos
*/

void Liberar_grupos(struct grupos **lista_grupos);

/**
 * Pesquisa_grupo(): responsavel pela verificação da presença do grupo na lista de grupos
 * cadastrados no sistema, mostrando, se presente, os dados referentes a esse grupo. Também 
 * é apresentado ao usuario as alternativas de ver post, adiiconar post, ou voltar. 
 * @param struct dados_user *usuario_logado
 * @param grupos *lista_grupos
*/

char *Pesquisa_grupo(struct dados_user *usuario_logado, struct grupos *lista_grupos);

/**
 * Entra_grupo(): responsavel por permitir a entrada do usuario logado em um determinado 
 * grupo. O grupo informado pelo usuario é pesquisado atraves da chamada da função Pesquisa_grupo
 * e, caso o grupo exista, um nó contendo o nome do usuario é criado e esse nó é alocado 
 * no final da lista encadeada de usuarios participantes struct grupos_users
 * @param struct dados_user *usuario_logado
 * @param  struct grupos **lista_grupos - lista contendo todos os grupos presentes no sistema
*/

void Entra_grupo(struct dados_user *usuario_logado, struct grupos **lista_grupos);

/**
 * Cria_grupo(): responsavel pela criação de um grupo, criando um no e o alocando na 
 * lista encadeada global de todos os grupos existentes no sistema. É solicitado ao usuario
 * que informe o nome do grupo e oferece a alternativa de adicionar uma descrição ao grupo. 
 * O usuario criador do grupo é automaticamente o lider do grupo e um integrante do mesmo.
 * @param struct dados_user *usuario_logado
 * @param  struct grupos **lista_grupos
*/

void Cria_grupo(struct dados_user *usuario_logado, struct grupos **lista_grupos);

/**
 * Exibe_grupos(): responsavel por exibir a tela inicial referente aos grupos, exibindo
 * primeiramente os grupos disponiveis no sistema e perguntando ao usuario se deseja 
 * criar um grupo, entrar em um grupo, pesquisar um grupo ou voltar para a tela anterior.
 * @param struct dados_user *usuario_logado
*/

void Exibe_grupos(struct dados_user *usuario_logado);

#endif
