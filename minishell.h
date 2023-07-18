#ifndef MINISHELL_H
# define MINISHELL_H

/* ---------------------- Bibliothèque----------------------------*/
# include <stdio.h>
# include <fcntl.h>
# include <curses.h>
// # include <term.h>
# include <dirent.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <termios.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/resource.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "./libft/include/libft.h"

# define SUCCESS 0

# define RESET "\033[0;39m"
# define GRAY "\033[0;90m"
# define RED "\033[0;91m"
# define GREEN "\033[0;92m"
# define YELLOW "\033[0;93m"
# define BLUE "\033[0;94m"
# define MAGENTA "\033[0;95m"
# define CYAN "\033[0;96m"
# define WHITE "\033[0;97m"

// extern int g_errno;
int	g_errno;

/* ----------- ENUM -> Type Token --------------- */
enum e_token
{
	WORD,
	S_QUOTE,
	D_QUOTE,
	RED_IN,
	RED_OUT,
	H_D,
	APPEND,
	SPACE,
	// SPACEE,
	PIPE
}	;

/*------------- Stucture token ------------*/
typedef struct s_tok
{
	int				len;
	char			*tok;
	enum e_token	type;
	struct s_tok	*next;
	struct s_tok	*prev;
}	t_tok;

/* ----------- Structure listes --------------- */
typedef t_dlist	t_env;

/* ----------- Structure parsing --------------- */
typedef struct s_shell
{
	int		i;
	int		status;
	char	cwd[1024];
	char	**arg;
	// char	**env;
	t_env	*env;
	t_tok	*token;
	t_dlist	*trash_lst;
}	t_shell;

/*------------- Stucture executions ------------*/
typedef struct s_exec
{
	int		idx;
	char	**append;
	char	*last_append;
	char	*append_first_cmd;
	int		number_of_pipes;
	int		nb_probable_of_heredocs;
	int		idx_doublon_append;
	int		nb_of_valid_heredoc;
	char	*last_heredoc;
	char	**tab_cmd;
	char	**cmd_n_arg;
	char	**env_cpy;
	char	*path;
	char	**access_path;
	char	*cmd_path;
	char	**redi_infile;
	char	**redi_outfile;
	char	**heredoc;
	char	*str_heredoc;
	int		cmd_number;
	t_dlist	**trash_lst_exe;
}	t_exec;

typedef struct s_pipe
{
	int		fd_pipe1[2];
	int		fd_pipe2[2];
	int		fd_in;
	int		fd_out;
	char	*infile;
	char	*outfile;
	t_exec	exec_info;
}	t_pipe;

/* ---------------- Builtings ------------------ */
void		echo_minishell(char **tab);
void		pwd_minishell(t_shell *info);
void		cd_minishell(t_shell *info, char *arg);
void		env_minishell(t_shell *info, char *arg);
void		unset_minishell(t_shell *info, char **arg);
void		exit_minishell(char **arg, t_dlist **trash);
void		export_minishell(t_shell *info, char **arg);

/* -------------- Fonctions principales -----------------------*/
int			parse_builtins(t_shell *info, t_exec *exec);
void		init_shell(t_shell *info, t_exec *exec, char **envp);
int			parse_shell(char *buff, t_shell *info, t_exec *exec);
int 		shell_execution(t_exec *info_exec, char **env, t_shell *info);

/* -------------- Fonctions parsing -----------------------*/
char		*ft_word(char *str, t_shell *info);
char		*ft_squote(char *str, t_shell *info);
char		*ft_dquote(char *str, t_shell *info);
int			check_syntax(t_tok *lst, t_dlist **trash);
char		*red_in(char *str, t_tok **lst, t_dlist **trash);
char		*red_out(char *str, t_tok **lst, t_dlist **trash);
char		*ft_pipe(char *str, t_tok **lst, t_dlist **trash);
char		*ft_space(char *str, t_tok **lst, t_dlist **trash);
void 		pars_to_exec(t_shell *info, t_exec *exec, t_dlist **trash);

/* -------------- Fonctions utilitaires -----------------------*/
int			ft_issigle(char c);
int			ft_isquote(char c);
int			ft_isword(int token);
int			ft_quotelen(char *str);
int			ft_tabsize(char **tab);
void		ft_tabreset(char **tab);
int			check_printchar(char c);
int			ft_checkquote(char *str);
int			ft_isparsing_char(char c);
void		ft_strswap(char **s1, char **s2);
int			ft_error_msg(int errno, char *str);
int			found_char(const char *str, int c);
char    	*tab_to_str(char **tab, t_dlist **trash);
char		**ft_split_var(char *var, t_dlist **trash);
void    	reset_shelltab(t_exec *exec, t_shell *shell);
char		**split_arg(char *str, int egal, t_dlist **trash);

/* -------------- Fonctions utiles liste -----------------------*/
void		tok_clearlst(t_tok **lst);
char		*ft_strdup_exec(char *str);
int			ft_lstsize_heredoc(t_list *lst);
void		display_node_heredoc(t_list *lst);
void		tok_addlst(t_tok **lst, t_tok *token);
void		tab_to_lst(t_shell *info, char **envp);
char		**lst_to_tab(t_env *lst, t_dlist **trash);
t_list		*find_var_env(t_env *env, char *var, int if_dd);
char    	**tokenlst_to_tab(t_tok *token, t_dlist **trash);
t_tok		*new_node(char *str, int token, t_dlist **trash);
t_list		*ft_lstnew_heredoc(char *data, t_dlist **trash_lst);
void		display_lst_heredoc(t_list **ptr_to_head, char *name);
void		fill_node(t_list *node, char *s1, char *s2, int if_var);
void		str_to_node(char *str, t_list *node, t_shell *info, int first_time);
void		creat_and_add(char *tmp, char *str, int type, int index, t_shell *info);
/* -------------- Fonctions test -----------------------*/
void		print_node(t_tok *node);
void		print_trash(t_dlist **trash);
void		test(char *str, char *fonction);
void		print_tab(char **tab, char *ft);
void		print_token(t_tok **lst, char *ft);
void		print_parsing(t_exec *exec, char *ft);
void		print_list(t_env *lst, char *ft, int info);

/* -------------- Fonctions d'execution ---------------------*/
char		*get_path(char **env);
void		handle_append(t_exec *exe);
void		command_not_found(char *cmd);
char		**handle_infile(t_exec *exe);
char		**handle_outfile(t_exec *exe);
int			handle_heredoc(t_exec *d_exe);
void		pre_handle_append(t_exec *exe);
void		create_heredoc_tab(t_exec *exe);
void		setup_infile_cmd(t_pipe *d_pipe);
void		close_pipes(t_pipe *d, int process);
char		*find_last_element(char **tab_append_out);
void		handle_pipes(int (*fd1)[2], int (*fd2)[2]);
void		setup_middle_cmd(t_pipe *d_pipe, int option);
char		*strjoin_exec(char const *s1, char const *s2);
void		handle_redirections(t_exec *exe, t_pipe *pipe);
void		error_infile_outfile(int error_nb, t_exec *exe);
void		last_cmd(t_pipe *d, int process, t_exec *d_exe);
void		setup_outfile_cmd(t_pipe *d_pipe, t_exec *d_exe);
char		**ft_split_exec(const char *str, char c, int var);
void		handle_dup_fd_single_cmd(t_pipe *d_pip, t_exec *exe);
//void		middle_cmd(t_pipe *d, char *cmd_path, int process);
char    	*ft_strcpy(char *s1, char *s2);
int			is_tab_heredoc_empty(char **tab);
void		first_cmd(t_pipe *d, t_exec *d_exe);
char		**create_tab(t_list **lst, t_dlist **trash);
int			convert_tab_to_fd_heredoc(char **heredoc_res);
void		middle_cmd(t_pipe *d, t_exec *exe, int process);
char		*ft_strcat_heredoc(char *dest, char *src, int end);
char		*create_str_heredoc(char **exe_heredoc, t_exec *exe);
void		init_struc_exec(t_exec *d, t_shell infos, char **env);
char		*get_cmd_path(char *cmd, t_exec *info, t_dlist **trash);
int			is_builtins(char *cmd_to_compare, char** builtins_list);
char    	**heredoc_data_saved(char *to_check, t_exec *exe, char *buffer);
void		builtins_1(t_pipe *d, t_exec *d_exe, t_shell *d_shell, char *cmd);
void		builtins_0(t_pipe *d_pip, t_exec *d_exe, t_shell *d_shell, char *cmd);
void		child_process_1(t_pipe *d, t_exec *d_exe, t_shell *d_shell, char *cmd);
void		init_struc_pipe(t_pipe *d, char *infile, char *outfile, t_exec *exe);
void		child_process_0(t_pipe *d_pip, t_exec *d_exe, t_shell *d_shell, char *cmd);
void		builtins_exec(char *builtins_name, t_shell *info, char **cmd, t_exec *exe);
void		handle_single_cmd(t_pipe *d_pip, t_exec *d_exe, t_shell *d_shell, char *cmd);

/*-----------------------------Signals-----------------------------*/

void	handle_signals(int sig_num);

#endif
