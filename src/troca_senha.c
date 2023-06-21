#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rede_social.h"
#include <conio.h>
#include "troca_senha.h"

// troca de senha

void Troca_senha(struct dados_user *usuario_logado)
{
    int tam_max = 50;
    char troca_senha_verifica[tam_max];
    int loop_senha = 0;
    int i = 0;
    char ch;

    while (loop_senha == 0)
    {
        printf("\nInsira a senha atual: ");
        i = 0;
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
                troca_senha_verifica[i] = ch;
                i++;
                printf("*");
            }
        }
        troca_senha_verifica[i] = '\0';

        if (strcmp(troca_senha_verifica, usuario_logado->senha_user) == 0)
        {
            printf("\nDigite a nova senha: ");

            i = 0;
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
                    usuario_logado->senha_user[i] = ch;
                    i++;
                    printf("*");
                }
            }
            usuario_logado->senha_user[i] = '\0';

            printf("\nSenha alterada\n\n");
            loop_senha = 1;
            break;
        }
        else
        {
            printf("\nA senha inserida não corresponde com a senha atual\nInsira uma senha válida\n");
        }
    }
}
