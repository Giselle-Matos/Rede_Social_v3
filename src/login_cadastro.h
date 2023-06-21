#ifndef LOGIN_CADASTRO_H
#define LOGIN_CADASTRO_H


/**
 * Criar_usuario(): Função responsável pela alocação de memoria para criar um novo usuário.
 * Retorna o proprio nó alocado.
 */
struct dados_user *Criar_usuario();

/**
 * Liberar_usuarios(): função responsável por liberar a memoria que estava sendo ocupada pela
 * lista encadeada relacionada aos usuarios cadastrados no sistema.
 * @param struct dados_user **lista_usuarios - utilizado para percorrer a lista encadeada
 * relacionada aos usuarios cadastrados no sistema
 */
void Liberar_usuarios(struct dados_user **lista_usuarios);
/**
 * Adicionar_usuario(): Função responsável por adicionar o nó alocado pela função
 * Criar_usuario() na lista encadeada lista_usuarios. Na função, é verificado se a lista está
 * vazia ou se contém algum elemento. Caso esteja vazia, o nó é adicionado na primeira posição.
 * Caso exista um ou mais elementos, a lista é percorrida até o final, onde o nó é então alocado.
 * @param struct dados_user **lista_usuarios - utilizado para percorrer a lista encadeada
 * relacionada aos usuarios cadastrados no sistema
 * @param struct dados_user *novo_user - nó alocado pela função Criar_usuario
 */
void Adicionar_usuario(struct dados_user **lista_usuarios, struct dados_user *novo_usuario);
/**
 * Login(): Função responsável pelo login do usuário no sistema. Pede ao usuario que insira
 * seu nome de usuario e sua senha e verifica se os dados inseridos são iguais aos dados
 * de algum nó da lista encadeada relacionada aos usuarios cadastrados no sistema. Caso
 * sejam iguais a um nó, o usuário tem acesso ao sistema. Caso contrário, é informado ao
 * usuario que os dados estao incorretos.
 * @param struct dados_user **lista_usuarios -  nó da lista encadeada relacionada aos usuarios
 * cadastrados no sistema
 * @param int *login_sucesso - ponteiro para uma variavel de controle que informa se o usuário
 * está logado no sistema ou não
 * @param struct dados_user **usuario_logado - nó contendo das informações do usuario logado
 * no sistema no momento
 */

void Login(struct dados_user **lista_usuarios, int *login_sucesso, struct dados_user **usuario_logado);
/**
 * Criar_conta(): função responsável pela criação da conta do usuário. Pede ao usuário que
 * informe seu nome de usuario e senha para que seja cadastrado no sistema atraves da função
 * Adiciona_usuario().
 * @param strucr dados_user **lista_usuarios - nó da lista encadeada relacionada aos usuarios
 * cadastrados no sistema
 */
void Criar_conta(struct dados_user **lista_usuarios);

#endif