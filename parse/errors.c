/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annamarianunes <annamarianunes@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:10:32 by annamarianu       #+#    #+#             */
/*   Updated: 2023/08/25 13:30:22 by annamarianu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//verifica se o caractere é '<' ou '>. Se for, retorna 1, se não, retorna 0
static int is_caract(char x)
{
    if(x == '<' || x == '>')
        return (1);
    return (0);
}

//Ela verifica se há um redirecionamento de entrada válido na posição i da string.
static int redirecionamento_entrada(char *str, int i)
{
    if(!str[i])
        return (1);
    if(i < 2)
        return (0);
    if(is_caract(str[i - 1]) && is_caract(str[i - 2]) && is_caract(str[i])) 
        return (1);
    if(str[i] == '<' && str[i - 1] == '>')
        return (1);
    return (0);
}

//verifica se há um erro de sintaxe relacionado ao uso do caractere de pipe '|'
static int check_pipe(char *str, int i)
{
    if(i == 0)
        return (1);
    if(!str[i + 1])
        return (1);
    if(str[i - 1] == '<' || str[i - 1] == '>')
        return (1);
}

//analisa a sintaxe de uma string de entrada procurando por erros de redirecionamento e uso incorreto de pipes.
int check_input(char *str)
{
    int i;
    int errors;

    i = 0;
    errors = 0;
    while(str[i])
    {
        if(str[i] == '>')
            if (redirecionamento_entrada(str, i))
                errors = ft_print(2, "syntax error near unexpected token '>'\n");
        if(str[i] == '<')
            if(redirecionamento_entrada(str, i))
                errors = ft_print(2, "syntax error near unexpected token '<'\n");
        if(str[i] == '|')
            if(check_pipe (str, i))
                errors = ft_print(2, "syntax error near unexpected token '|'\n");
        if(errors != 0)
            return (1);
        i++;
    }
    return(0);
}

