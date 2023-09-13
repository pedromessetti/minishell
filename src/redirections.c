/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections..c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmessett <pmessett>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:14:46 by pmessett          #+#    #+#             */
/*   Updated: 2023/09/12 18:20:46 by pmessett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bind_redir_in(t_cmd_tb *cmd, t_token *redir)
{

    if (cmd->io.in != -1)
		close(cmd->io.in);
     cmd->io.in = open(redir->content, O_RDONLY);
    if ( cmd->io.in == -1)
    {
        ft_printf("minishell: %s: %s\n", redir->content, strerror(errno));
        cmd->io.in = -1;
        return (1);
    }
    return (0);
}

int	bind_redir_out(t_cmd_tb *cmd, t_token *redir)
{
    if (cmd->io.out != -1)
        close(cmd->io.out);
    cmd->io.out = open(redir->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (cmd->io.out == -1)
    {
        ft_printf("minishell: %s: %s\n", redir->content, strerror(errno));
        return (1);
    }
    return (0);
}

int	bind_redir_append(t_cmd_tb *cmd, t_token *redir)
{
    if (cmd->io.out != -1)
        close(cmd->io.out);
    cmd->io.out = open(redir->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (cmd->io.out == -1)
    {
        ft_printf("minishell: %s: %s\n", redir->content, strerror(errno));
        return (1);
    }
    return (0);
}



int	bind_redir_here_doc(t_cmd_tb *cmd, t_token *redir)
{
    (void)cmd;
    (void)redir;
    //TODO: something

    return (0);
}