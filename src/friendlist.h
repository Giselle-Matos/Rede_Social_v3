#ifndef FRIENDLIST_H
#define FRIENDLIST_H

/**
 * Listar_amigos(): responsavel por mostrar ao usuario a lista de usuarios com quem possui
 * amizade. A lista é mostrada de forma ordenada (ordem alfabetica), utilizando o algoritmo 
 * bubble sort. Foi utilizado esse algoritmo devido a maior facilidade de implementação, 
 * apesar de nao ter a melhor complexidade dentre os algoritmos existentes (O(n^2) para 
 * qualquer caso). Além disso, nao foi especificado no enunciado do trabalho que o sistema 
 * deveria suportar uma grande quantidade de dados, ou seja, uma grande quantidade de usuarios. 
 * Dessa forma, nao se faz necessario um algoritmo de maior eficiencia ja que o tempo de execução
 * nao é alterado de forma significativa.
 * @param struct dados_user *usuario_logado
*/

void Listar_amigos(struct dados_user *usuario_logado);

/**
 * Remove_amigo(): responsavel pela remoção do amigo da lista de amigos
 * @param struct dados_user *usuario_logado
 * @param char *username_friend
*/

void Remove_amigo(struct dados_user *usuario_logado, char *username_friend);


/**
 * Union(): responsavel por alterar o representante dos conjuntos ao criar uma amizade.
 * @param struct dados_user *rep1 - representante do usuario com que se quer fazer amizade
 * @param struct dados_user *rep2 - representante do usuario logado
*/

void Union(struct dados_user *rep1, struct dados_user *rep2);


/**
 * Make_set(): responsavel por criar cada aresta dos conjuntos disjuntos, fazendo com que
 * seus representantes apontem para si mesmos e altere o rank
 * @param struct dados_user **lista_usuarios
*/

void Make_set(struct dados_user **lista_usuarios);

/**
 * Find_set(): função responsavel por encontrar o representante de um conjunto de maneira 
 * recursiva, alterando o representante de todos os nós conforme percorre a lista (path compression)
 * @param struct dados_user *usuario
*/

struct dados_user *Find_set(struct dados_user *usuario);

/**
 * Find_friendship(): reponsavel por verificar se os usuarios ja sao amigos. Caso sejam, 
 * exibe uma mensagem indicando que ja sao amigos. Caso nao sejam, torna os usuarios amigos
 * ao fazer a Union e mudar o representante dos conjuntos. 
 * @param struct dados_user *usuario_logado - Responsável pelo recebimento correto da nova
 * senha por usuario_logado->senha_user
 * @param char *username_friend - variavel auxiliar contendo o input do usuario
 * @param struct dados_user **lista_usuarios - utilizado para percorrer a lista encadeada
 * relacionada aos usuarios cadastrados no sistema
*/

void Find_friendship(struct dados_user *usuario_logado, char *username_friend, struct dados_user **lista_usuarios);

/**
 * Adiciona_amigo(): responsavel por adicionar um amigo a lista de amigos. Na prática,
 * essa função apenas chama outra função.
 * @param struct dados_user *usuario_logado - Responsável pelo recebimento correto da nova
 * senha por usuario_logado->senha_user
 * @param struct dados_user **lista_usuarios - utilizado para percorrer a lista encadeada
 * relacionada aos usuarios cadastrados no sistema
 * @param char *username_friend - variavel auxiliar contendo o input do usuario
*/


void Adiciona_amigo(struct dados_user *usuario_logado, struct dados_user **lista_usuarios, char *username_friend);

/**
 * Main_friendlist(): responsável por apresentar ao usuario as opções da lista de amigos, como
 * Adicionar amigos, listar amigos, remover amigos e voltar. 
 * @param struct dados_user *usuario_logado - Responsável pelo recebimento correto da nova
 * senha por usuario_logado->senha_user
 * @param struct dados_user **lista_usuarios - utilizado para percorrer a lista encadeada
 * relacionada aos usuarios cadastrados no sistema
 * @param char *username_friend - variavel auxiliar contendo o input do usuario
*/

void Main_friendlist(struct dados_user *usuario_logado, struct dados_user **lista_usuarios);
/*!
 * Troca_senha(): responsável pela mudança da senha do usuário. Por motivos de segurança,
 * é pedida a senha anterior do usuário antes da senha atual e a senha é ocultada enquanto
 * o usuário a insere.
 * @param struct dados_user *usuario_logado - Responsável pelo recebimento correto da nova
 * senha por usuario_logado->senha_user
 */

#endif
