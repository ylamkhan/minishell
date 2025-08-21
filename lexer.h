/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsaoud <zsaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 20:24:02 by ylamkhan          #+#    #+#             */
/*   Updated: 2023/08/06 22:58:59 by zsaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "get_next_line.h"
# include "libft/libft.h"
# include <ctype.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define MAX_TOKENS 100
# define MAX_TOKEN_LENGTH 100
# define READ_END 0
# define WRITE_END 1
# define BUFFER_SIZE 1
# define ERROR -1

# define DEFAULT "\001\033[0;39m\002"
# define GRAY "\001\033[1;90m\002"
# define RED "\001\033[1;91m\002"
# define GREEN "\001\033[1;92m\002"
# define YELLOW "\001\033[1;93m\002"
# define BLUE "\001\033[1;94m\002"
# define MAGENTA "\001\033[1;95m\002"
# define CYAN "\001\033[1;96m\002"
# define WHITE "\001\033[0;97m\002"
# define PINK "\001\033[38;2;255;192;203m\002"

# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <unistd.h>

int			g_status;
typedef struct s_mini
{
	char	**full_cmd;
	char	*full_path;
	int		infile;
	int		outfile;
}			t_mini;

typedef struct s_prompt
{
	t_list	*cmds;
	char	**env;
	pid_t	pid;
}			t_prompt;

enum		e_mini_error
{
	QUOTE = 1,
	NDIR = 2,
	NPERM = 3,
	NCMD = 6,
	DUPERR = 7,
	FORKERR = 8,
	PIPERR = 9,
	PIPENDERR = 10,
	MEM = 11,
	IS_DIR = 12,
	NOT_DIR = 13,
	UNSET = 14,
	EXPORT = 15
};

void		handle_sigint(int sig);
extern void	rl_replace_line(const char *s, int i);
int			ft_strcmp(char *s1, char *s2);
int			d_s_quote(char *input, int *i);
void		free_content(void *content);
char		**ft_split_tab_esp(char *input, char *set);
char		**split_all(char **args, t_prompt *prompt, int *am);
int			ft_strchars_i(const char *s, char *set);
char		**ft_cmdsubsplit(char const *s, char *set);
char		**ft_matrix_replace_in(char ***big, char **small, int n);
int			syntax_error(char *input);
int			max_her_doc(char *input);
int			ft_putmatrix_fd(char **m, int nl, int fd);
char		*env_get_value(char *name, char **env);
char		*env_find_var(char *name, char **env);
int			backslach_point(char *input);
int			ft_matrixlen(char **t);
void		*run_cmd(t_prompt *p, t_list *cmds, int *is_exit);
int			check_arg(char *arg);
int			ft_count_words(char *input, char *set, int i[2]);
int			ft_putmatrix_fd(char **m, int nl, int fd);
int			ft_pwd(void);
int			ft_countchar(char *s, char c);
void		funcfree(char **a);
void		*mini_perror1(int err_type, char *param, int err);
char		*join_all(char **args);
char		*ft_strjoin2(char *s1, char *s2);
char		**ft_split_tab_esp1(char *input, char *set);
char		*expand_path(char *str, int i, int quotes[2], char *var);
char		**ft_dup_matrix(char **s);
char		**ft_update_matrix(char **env, char *s);
char		*ft_del(char *s, int sq, int dq);
void		ft_free_matrix(char ***m);
int			ft_matrixlen(char **t);
int			ft_strchr_i(const char *s, int c);
int			ft_atoi2(const char *nptr, long *nbr);
int			ft_countchar(char *s, char c);
int			ft_isspace(char c);
char		*get_next_line(int fd);
char		*expand_vars(char *str, int i, int quotes[2], t_prompt *prompt);
int			built(t_prompt *prompt, t_list *cmd, int *is_exit, int *n);
int			is_builtin(t_mini *n);
int			ft_cd(t_prompt *prompt);
void		cd_error(char **str[2]);
int			ft_pwd(void);
int			ft_echo(t_list *cmd);
int			ft_export(t_prompt *prompt);
int			ft_unset(t_prompt *prompt);
int			ft_exit(t_list *cmd, int *is_exit);
void		*check_args(char *out, t_prompt *p);
t_list		*fill_nodes(char **args, int i, t_prompt *p);
int			get_fd(int oldfd, char *path, int flags[2]);
t_mini		*ft_outfile1(t_mini *node, char **args, int *i);
t_mini		*ft_outfile2(t_mini *node, char **args, int *i);
t_mini		*ft_infile1(t_mini *node, char **args, int *i);
t_mini		*ft_infile2(t_mini *node, char **args, int *i, t_prompt *p);
void		*check_to_fork(t_prompt *prompt, t_list *cmd, int fd[2]);
void		ft_child(t_prompt *prompt, t_mini *n, int l, t_list *cmd);
void		exec_custom(char ***out, char *full, char *args, char **envp);
void		get_cmd(t_prompt *prompt, t_list *start, char **split_path,
				char *path);
int			get_here_doc(char *str[2], char *aux[2], t_prompt *p);
void		*mini_perror(int err_type, char *param, int err);
char		*ft_getenv(char *var, char **envp, int n);
char		**ft_setenv(char *var, char *value, char **envp, int n);
char		*ft_getprompt(t_prompt prompt);
void		free_content(void *content);
void		handle_sigint(int sig);
void		fun3(t_prompt **p, char *tmp, char *a);

#endif
