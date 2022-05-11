/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 15:42:16 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/05/10 07:57:51 by potero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_envp_path(char **envp, int argc)
{
	int	i;

	i = 0;
	if (argc == 4)
		;
	while (envp != NULL)
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			return (&envp[i][4]);
		i++;
	}
	return (0);
}

void	ft_add_path(char **l_paths, char *argv, t_comm_path **aux_l)
{
	int			j;
	char		*aux;
	char		*aux_p;
	int			i;
	char		**s;

	j = -1;
	i = -1;
	printf("argv-> %s\n", argv);
	while (l_paths[++j] != 0)
	{
		aux = ft_strjoin(l_paths[j], "/");
		aux_p = ft_strjoin(aux, argv);
		free(aux);
		s = ft_split(aux_p, ' ');
		free(aux_p);
		i = access(s[0], X_OK);
		if (i == 0)
		{
			ft_lstadd_back(aux_l, ft_lstnew(s));
			return ;
		}
		free_variables_list(s);
	}
	ft_lstadd_back(aux_l, ft_lstnew_error(ft_split(argv, ' ')));
}

void	ft_setcommand(t_comm_path *var, char *arg)
{
	var->comm = ft_split(arg, ' ');
	var->ok = 1;
	var->next = 0;
}

t_comm_path	**ft_accesslist(char **l_paths, char *argv, int argc)
{
	t_comm_path	**aux_l;
	t_comm_path	*var;
	int			co;
	
	if (argc == 4)
		;
	printf("argv3-> %s\n", argv);
	aux_l = malloc(sizeof(t_comm_path *));
	*aux_l = 0;
	var = malloc(sizeof(t_comm_path));
	co = access(argv, X_OK);
	if (co == 0)
	{
		ft_setcommand(var, argv);
		ft_lstadd_back(aux_l, var);
		free_variables_list(var->comm);
	}
	else
		ft_add_path(l_paths, argv, aux_l);
	free(var);
/*
	while (i < argc - 1)
	{
		var = malloc(sizeof(t_comm_path));
		co = access(argv[i], X_OK);
		if (co == 0)
		{
			ft_setcommand(var, argv[i]);
			ft_lstadd_back(aux_l, var);
			free_variables_list(var->comm);
		}
		else
			ft_add_path(l_paths, argv[i], aux_l);
		free(var);
		i++;
	}*/
	return (aux_l);
}

int	execute(int argc, char **argv, char **envp)
{
	char		*path;
	char		**l_paths;
	t_comm_path	**comm_dir;
	int			fd;
	int			e;

	e = 0;
	comm_dir = 0;
	printf("argv2-> %s\n", argv[2]);
	if (argc != 4)
		ft_args_error();
	path = ft_envp_path(envp, argc);
	printf("path->%s\n", path);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		e = 1;
		ft_file_error(argv[1]);
	}
	close(fd);
	ft_open_outfile(argv[3]);
	printf("argv2.0-> %s\n", argv[2]);
	l_paths = ft_split(path, ':');
	printf("argv2.1-> %s\n", argv[2]);
	comm_dir = ft_accesslist(l_paths, argv[2], argc);
	ft_command_validation(comm_dir, e);
	ft_first_part(comm_dir[0], envp, argv);
	ft_final_part(comm_dir, l_paths);
	return (0);
}
