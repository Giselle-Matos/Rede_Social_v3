#ifndef MENU_H
#define MENU_H

/**
 * Exibir_menu(): Função responsável pela exibição do menu principal mostrado ao usuário apos
 * o login ser efetuado com sucesso. Atraves dele, o usuario pode navegar para o perfil, mural,
 * lista de amigos, mensagens, troca de senha, grupos ou log-out.
 * @param int *choice_menu - ponteiro para uma variavel de controle para loops e switch
 * @param struct dados_user *usuario_logado - nó contendo das informações do usuario logado
 * no sistema no momento
 * @param int *login_sucesso - ponteiro para uma variavel de controle que informa se o usuario
 * esta logado no sistema ou não
 * @param struct dados_user **lista_usuarios - nó da lista encadeada relacionada aos usuarios
 * cadastrados no sistema
 */
void Exibir_menu(int *choice_menu, struct dados_user *usuario_logado, int *login_sucesso, struct dados_user **lista_usuarios);


#endif