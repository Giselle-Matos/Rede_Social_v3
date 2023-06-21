#ifndef MURAL_H
#define MURAL_H

/**
 * Apaga_post(): responsavel por possibilitar que o usuario apague determiando post
 * a partir do indice do post.
 * @param struct posts **lista_posts
 * @param int post_number
*/

void Apaga_post(struct posts **lista_posts, int post_number);


/**
 * Liberar_grupos(): responsavel por liberar a memoria alocada para os nos da 
 * lista encadeada contendo as postagens do sistema
 * @param struct dados_user **lista_posts
*/


void Liberar_posts(struct dados_user **lista_posts);


void Mostra_posts(struct dados_user *lista_usuarios);
/*!
 * Busca_posts(): função responsável pela pesquisa pelo nome do usuário que deseja ser
 * buscado, informado pelo usuário que interage com o programa. A função percorre a lista
 * encadeada contendo todas as postagens do sistema e verifica se o nome do usuário informado
 * corresponde a algum nome de usuário de algum nó da lista encadeada. Caso seja igual, imprime
 * a postagem desse usuário na tela.
 * @param struct posts **lista_posts - Nó da lista encadeada contendo a postagem e o nome
 * usuário responsavel pela postagem
 * @param char busca_post_user -  utilizado na comparação com o nó da lista encadeada ao
 * percorre-la
 */
void Busca_posts(struct dados_user *lista_usuarios, char busca_post_user[50]);
/*!
 * Edita_mural(): função responsável pela alteração das postagens da lista encadeada, que ocorre
 * quando o usuário escolhe "Adicionar post". A função recebe como parametro a struct posts **lista_posts
 * e a struct dados_user *usuario_logado, de forma que seja possível percorrer a lista encadeada de postagens
 * e buscar pelo nome do usuario logado no sistema no momento. Dessa forma, apenas os posts do usuário logado
 * são mostrados na tela.
 * @param struct posts **lista_posts - nó da lista encadeada contendo a postagem e o nome do usuario responsavel
 * pela postagem
 * @param struct dados_user *usuario_logado - utilizado na comparação com o nó da lista encadeada lista_posts
 * ao percorre-la.
 */
void Postar(struct posts **lista_posts, char user[50]);
/*!
 * Exibe_mural(): função responsável por mostrar ao usuario uma tela de opções.
 * O usuário pode escolher Adicionar posts, Pesquisar posts (de outros usuarios
 * ou dele proprio) ou voltar. Ao escolher alguma dessas alternativas, é direcionado
 * para uma outra tela para a execução da funcionalidade escolhida.
 */
void Exibe_mural(struct dados_user *usuario_logado, struct dados_user *lista_usuarios);

#endif