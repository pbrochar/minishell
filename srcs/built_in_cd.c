/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 17:33:52 by pbrochar          #+#    #+#             */
/*   Updated: 2021/09/10 15:36:24 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "errno.h"

static void	update_pwd(t_master *msh, char *new_dir)
{
	char	*pwd;
	int		i;

	i = 0;
	pwd = malloc(sizeof(char) * (ft_strlen(new_dir) + 5));
	if (pwd == NULL)
		return ;
	while (msh->envp[i] && ft_strncmp(msh->envp[i], "PWD", 3))
		i++;
	ft_strlcpy(pwd, "PWD=", 5);
	ft_strcat(pwd, new_dir);
	free(msh->envp[i]);
	msh->envp[i] = pwd;
}

static void	update_old_pwd(t_master *msh, char *old_dir)
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
	free(msh->envp[i]);
	msh->envp[i] = old_pwd;
}

static void	update_dir_env(t_master *msh, char *old_dir)
{
	char	buf[101];
	char	*new_dir;

	new_dir = getcwd(buf, 100);
	if (new_dir == NULL)
		return ;
	update_old_pwd(msh, old_dir);
	update_pwd(msh, new_dir);
}

static char	*manage_special_dir(t_master *msh, char **arg)
{
	if (!arg[1] || arg[1][0] == '~')
		return (cd_return_home(msh));
	else if (ft_strncmp(arg[1], "-\0", 2) == 0)
		return (cd_return_oldpwd(msh, arg[1]));
	return (arg[1]);
}

int	built_in_cd(t_master *msh, char **arg)
{
	int		chdir_ret;
	char	buf[101];
	char	*old_dir;
	char	*folder;

	if (arg && arg[0] && arg[1] && arg[2])
		return (print_err_too_m_a(msh));
	folder = manage_special_dir(msh, arg);
	if (folder && folder[0] == '\0')
		return (ret_value(msh, 0));
	old_dir = getcwd(buf, 100);
	if (old_dir == NULL)
		printf("%s\n", strerror(errno));
	if (folder != NULL && folder[0] != '\0')
		chdir_ret = chdir(folder);
	if (folder != NULL && chdir_ret == -1)
		return (print_err_bad_folder(msh, folder, errno));
	else if (folder != NULL && folder[0] != '\0')
		update_dir_env(msh, old_dir);
	update_prompt_values(msh);
	return (ret_value(msh, 0));
}
