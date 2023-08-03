#include "../../minishell.h"

/* ------------------------- cd sans option ------------------------------*/
static void	go_home(t_shell *info)
{
	char	*path_home_2;
	t_list	*path;

	path = find_var_env(info->env, "HOME", 1);
	path_home_2 = path->valeur;
	chdir(path_home_2);
	getcwd(info->cwd, 1024);
}

/* ---------------------------- fonction cd ---------------------------------*/
void	cd_minishell(t_shell *info, char *arg)
{
	int			ret;
	struct stat	filestat;

	if (!arg)
		go_home(info);
	else
	{
		if (stat(info->cwd, &filestat) == 0)
		{
			if (S_ISREG(filestat.st_mode))
				ft_error_msg(1, arg);
			else if (S_ISDIR(filestat.st_mode))
			{
				ret = chdir(arg);
				if (ret == -1)
					ft_error_msg(1, arg);
				else
					getcwd(info->cwd, 1024);
			}
		}
		else
			perror("Error access file or directory\n");
	}
}
