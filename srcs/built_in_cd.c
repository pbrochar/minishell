/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 17:33:52 by pbrochar          #+#    #+#             */
/*   Updated: 2021/06/02 16:14:55 by pbrochar         ###   ########.fr       */
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

static char *manage_special_dir(t_master *msh, char **arg)
{
	int i;

	i = 0;
	if (!arg[1] || arg[1][0] == '~' || ft_strncmp(arg[1], "--\0", 3) == 0)
	{
		while (msh->envp[i])
		{
			if (ft_strncmp(msh->envp[i], "HOME", 4) == 0)
				return (&msh->envp[i][5]);
			i++;
		}
	}
	else if (ft_strncmp(arg[1], "-\0", 2) == 0)
	{
		while (msh->envp[i])
		{
			if (ft_strncmp(msh->envp[i], "OLDPWD", 6) == 0)
			{
				ft_printf("%s\n", &msh->envp[i][7]);
				return (&msh->envp[i][7]);
			}
			i++;
		}
	}
	return (arg[1]);
}

int built_in_cd(t_master *msh, char **arg)
{
	int		errnum;
	int		chdir_ret;
	char	buf[101];
	char	*old_dir;
	char	*folder;

	folder = manage_special_dir(msh, arg);
	old_dir = getcwd(buf, 100);
	chdir_ret = chdir(folder);
	if (chdir_ret == -1)
	{
		errnum = errno;
		printf("cd : %s: %s\n", arg[1], strerror(errnum));
	}
	else
		update_dir_env(msh, old_dir);
	update_prompt_values(msh);
	return (0);
}