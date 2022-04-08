/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 15:42:16 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/04/08 17:52:59 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_pipex.h"

char	*ft_envp_path(char **envp, int argc)
{
	int	i;

	i = 0;
	while (envp != NULL)
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			return (&envp[i][argc]);
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

void	ft_setcommand(t_comm_path *var, char	*arg)
{
	var->comm = ft_split(arg, ' ');
	var->ok = 1;
	var->next = 0;
}

t_comm_path	**ft_accesslist(char **l_paths, char **argv, int argc)
{
	int			i;
	t_comm_path	**aux_l;
	t_comm_path	*var;
	int			co;

	i = 2;
	aux_l = malloc(sizeof(t_comm_path *));
	*aux_l = 0;
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
	}
	return (aux_l);
}

int	main(int argc, char **argv, char **envp)
{
	char		*path;
	char		**l_paths;
	t_comm_path	**comm_dir;
	int			fd;
	int			e;

	e = 0;
	comm_dir = 0;
	if (argc != 4)
		ft_args_error();
	path = ft_envp_path(envp, argc);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		e = 1;
		ft_file_error(argv[1]);
	}
	close(fd);
	ft_open_outfile(argv[argc - 1]);
	l_paths = ft_split(path, ':');
	comm_dir = ft_accesslist(l_paths, argv, argc);
	//ft_command_validation(comm_dir, argv, e);
	ft_first_part(comm_dir[0], envp, argv);
	ft_final_part(comm_dir, l_paths);
	return (0);
}
