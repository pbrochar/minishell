/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 17:33:52 by pbrochar          #+#    #+#             */
/*   Updated: 2021/05/26 19:44:31 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "errno.h"

/*
** to do : voir avec l'environnement si on doit pas modifier la facon dont s'est gerer
** gerer cd -- (=cd), cd ~ , et cd -
*/

static void update_pwd(t_master *msh, char *new_dir)
{
	char *pwd;
	int i;

	i = 0;
	pwd = malloc(sizeof(char) * (ft_strlen(new_dir) + 5));
	if (pwd == NULL)
		return ;
	while (msh->envp[i] && ft_strncmp(msh->envp[i], "PWD", 3))
			i++;
	ft_strlcpy(pwd, "PWD=", 5);
	ft_strcat(pwd, new_dir);
	msh->envp[i] = pwd;
}

static void update_old_pwd(t_master *msh, char *old_dir)
{
	char	*old_pwd;
	int		i;
	
	old_pwd = malloc(sizeof(char) * (ft_strlen(old_dir) + 8));
	if (old_dir == NULL)
		return ; 
	i = 0;
	while (msh->envp[i] && ft_strncmp(msh->envp[i], "OLDPWD", 4))
		i++;
	ft_strlcpy(old_pwd, "OLDPWD=", 8);
	ft_strcat(old_pwd, old_dir);
	msh->envp[i] = old_pwd;
}

static void update_dir_env(t_master *msh, char *old_dir)
{
	char	buf[101];
	char	*new_dir;

	new_dir = getcwd(buf, 100);
	if (new_dir == NULL)
		return ;
	update_old_pwd(msh, old_dir);
	update_pwd(msh, new_dir);
}

int built_in_cd(t_master *msh, char *path)
{
	int		errnum;
	int		chdir_ret;
	char	buf[101];
	char	*old_dir;
	
	if (path[0] == '~' || path[0] == '-' || path[0] == '\0')
		printf("%c\n", path[0]);
	old_dir = getcwd(buf, 100);
	chdir_ret = chdir(path);
	if (chdir_ret == -1)
	{
		errnum = errno;
		printf("cd :%s: %s\n", strerror(errnum), path);
	}
	else
		update_dir_env(msh, old_dir);
	return (0);
}