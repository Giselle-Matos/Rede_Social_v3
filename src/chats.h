#ifndef CHATS_H
#define CHATS_H


/**
 * Enviar_mensagem(): responsavel pelo envio da mensagem para outro usuario, criando 
 * um no do tipo struct mensagens para armazenar o input do usuario, logo em seguida
 * armazenando esse no na lista encadeada de mensagens.
 * @param struct dados_user *usuario_logado - usuario logado no sistema no momento
 * @param struct dados_user *user_send - usuario que esta enviando a mensagem no momento.
*/

void Enviar_mensagem(struct dados_user *usuario_logado, struct dados_user *user_send);

/**
 * Pesquisa_chat(): solicita o nome do usuario e verifica se o usuario esta presente na 
 * lista de usuarios cadastrados no sistema. Caso afirmativo, oferece a opção de enviar mensagem
 * ou voltar para a pagina anterior.
 * @param struct dados_user *usuario_logado
 * @param struct dados_user **lista_usuarios
*/

void Pesquisa_chat(struct dados_user *usuario_logado, struct dados_user **lista_usuarios);

/**
 * Exibe_chats(): responsavel por exibir os usuarios disponiveis no sistema para 
 * @param struct dados_user *usuario_logado
 * @param struct dados_user **lista_usuarios
*/

void Exibe_chats(struct dados_user *usuario_logado, struct dados_user **lista_usuarios);


#endif