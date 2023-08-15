#include "../../minishell.h"

/* ------------------------- cd sans option ------------------------------*/
static void	go_home(t_shell *info)
{
	char	*path_home_2;
	t_list	*path;

	path = find_var_env(info->env, "HOME");\
	if (!path)
	{
		printf("Minishell: cd : HOME not set\n");
		return ;
	}
	path_home_2 = path->valeur;
	chdir(path_home_2);
	getcwd(info->cwd, 1024);
}

/* ---------------------------- fonction cd ---------------------------------*/
void	cd_minishell(t_shell *info, char *arg)
{
	int			ret;
	char		**tab;
	char		*path;
	struct stat	filestat;

	if (!arg)
		go_home(info);
	else
	{
		tab = ft_split(arg, ' ', &info->trash_lst);
		path = ft_strjoin(info->cwd, "/", &info->trash_lst);
		stat(ft_strjoin(path, *tab, &info->trash_lst), &filestat);
		if (S_ISREG(filestat.st_mode))
			ft_error_msg(1, *tab, "cd", 1);
		else if (S_ISDIR(filestat.st_mode))
		{
			ret = chdir(*tab);
			if (ret == -1)
				ft_error_msg(1, *tab, "cd", 0);
			else
				getcwd(info->cwd, 1024);
		}
		else
			ft_error_msg(1, *tab, "cd", 0);
	}
}
