#ifndef PERFIL_H
#define PERFIL_H

/**
 * Pesquisa_perfil(): função responsável pela pesquisa do perfil de um determinado usuário.
 * Caso encontre o usuário, retorna o nó relacionado a esse usuário. Caso não encontre,
 * retorna NULL.
 * @param struct dados_user **lista_usuarios - utilizado para percorrer a lista encadeada
 * relacionada aos usuarios cadastrados no sistema
 */
struct dados_user *Pesquisa_perfil(struct dados_user **lista_usuarios);

/**
 * Edita_perfil(): função responsável pela mudança dos dados relacionados ao perfil do usuario
 * em struct dados_usuarios.
 * @param struct dados_user *usuario_logado - nó contendo das informações do usuario logado
 * no sistema no momento
 */
void Edita_perfil(struct dados_user *usuario_logado);
/**
 * Exibe_perfil(): Função que mostra os dados do usuario logado no momento e fornece a opção de
 * alterar as informações do perfil, pesquisar perfis ou voltar para a tela anterior.
 * @param struct dados_user *usuario_logado - nó contendo as informações do usuario logado no
 * sistema no momento
 * @param struct dados_user **lista_usuarios - nó da lista encadeada relacionada aos usuarios
 * cadastrados no sistema
 */
void Exibe_perfil(struct dados_user *usuario_logado, struct dados_user **lista_usuarios);

#endif