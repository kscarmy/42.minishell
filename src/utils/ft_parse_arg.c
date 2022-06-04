/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guderram <guderram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:28:56 by guderram          #+#    #+#             */
/*   Updated: 2022/06/04 20:23:20 by guderram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int		ft_size_of_arg(t_data *data) // renvoie la taille d'un arg, pratique pour malloc tok->arg
{
	int	u;
	int i = 0;
	// int	dol_s;
	char	*tmp;

	// int	jean = 0;

	u = 0;
	// printf("IN SIZE OF ARG :\n");
	while (ft_is_separator(data->input, (data->i + u)) == 0 && data->input[data->i + u])
	{
		// printf ("u 1 %d\n", u);
		if (data->input[data->i + u] == '\"' && data->input[data->i + u + 1] != '\"' && data->input[data->i + u + 1] != '\0')
		{
			i = ft_str_size(ft_ret_double_quote(data, &data->input[data->i + u], 0));
			// printf("SIZE I %d\n", i);
			if (i != 0)
				u = u + i;
			while (i == 0 && data->input[data->i + u] != '\"')
				u++;
			if (i == 0)
				u++;

			// u = u + ft_str_size(ft_ret_double_quote(data, &data->input[data->i + u], 0));

		}
		else if (data->input[data->i + u] == '\'' && data->input[data->i + u + 1] != '\'' && data->input[data->i + u + 1] != '\0')
			u = u + ft_str_size(ft_ret_simple_quote(data, &data->input[data->i + u], 0));
		else if ((data->input[data->i + u] == '\"' && data->input[data->i + u + 1] == '\"') || (data->input[data->i + u] == '\'' && data->input[data->i + u + 1] == '\''))
			{
				// printf ("q null\n");
				u = u + 2;
			}
		else if (data->input[data->i + u] == '$')
		{
			tmp = ft_ret_dollar(data, &(data->input[data->i + u]));
			// printf("size of arg dollard in %d\n", u);
			if (ft_str_size(tmp) > 0)
				u = u + ft_str_size(tmp);
			else
				u++;
			ft_strdel(&tmp);
			// printf("size of arg dollard out %d\n", u);
		}
		else
			u++;
		// printf ("u 4 %d\n", u);
		// i++;
		// printf("<%c>\n", data->input[data->i + u]);
		// jean++;
	}
	// printf ("size arg %d\n", u);
	if (i != 0 && u == 0)
		u++;
	// printf ("EXIT SIZE OF ARG : (%d)\n", u);
	return (u);
}

void	ft_malloc_arg(t_data *data, t_token *tok) // malloc dans tok->arg l'argument
{
	int		i;
	int		u;
	int		size;
	char	*tmp;


	// int	jean = 0;

	// int bordel = 0;

	i = 0;
	u = 0;
	// printf ("\n-------------Entree malloc arg\n");
	size = ft_size_of_arg(data);
	// printf ("--------------size tok arg <%d>\n", size);
	tok->arg = ft_malloc_str(data, size);
	// printf ("INFO 1 %d <%s>\n", ft_str_size(tok->arg), tok->arg);
	if (size > 0 && tok->arg != NULL)
	{
		while (data->input[data->i + u] && ft_is_separator(data->input, (data->i + u)) == 0)
		{
			// printf ("----in while : <%s>\n", &(data->input[data->i + u]));
			if (data->input[data->i + u] == '\"' && data->input[data->i + u + 1] != '\"')
			{
				// printf ("in dq\n");
				tmp = ft_ret_double_quote(data, &data->input[data->i + u], 0);
				if (ft_str_size(tmp) > 0)
					u = u + 2 + ft_str_size(tmp);
				while (data->input[data->i + u] && ft_str_size(tmp) > 0 && data->input[data->i + u] != '\"')
					u++;
				if (data->input[data->i + u] == '\"')
					u++;

				// printf ("----IN malloc arg dbl q u size (%d)\n", u);
				if (ft_str_size(tmp) > 0)
					ft_copie_dest_src(tok, tmp);
				ft_strdel(&tmp);
				// printf ("1 u : %d, <%s>\n", u, &data->input[data->i + u]);
				// printf ("INFO 2 %d <%s>\n", ft_str_size(tok->arg), tok->arg);
			}
			else if (data->input[data->i + u] == '\'' && data->input[data->i + u + 1] != '\'')
			{
				// printf ("in sq\n");
				// printf("malloc arg sgl quote :\n");
				// printf ("u 1 %d\n", u);
				// printf("sgl pre tmp <%s> u %d c <%c>\n", tmp, u, data->input[data->i + u]);
				tmp = ft_ret_simple_quote(data, &data->input[data->i + u], 0);
				u = u + 2 + ft_str_size(tmp);
				// i = i + 2 + ft_str_size(tmp);
				// printf("sgl apr tmp <%s> u %d c <%c>\n", tmp, u, data->input[data->i + u]);
				// if (data->input[data->i + u] == '\'')
				// 	u++;
				// printf("tmp <%s> u %d c <%c>\n", tmp, u, data->input[data->i + u]);
				// u = u + ft_str_size(ft_ret_simple_quote(data, &data->input[data->i + u], 0));
				// printf ("u 2 %d <%s> <%s>\n", u, tok->arg, tmp);
				ft_copie_dest_src(tok, tmp);
				ft_strdel(&tmp);
				// printf ("2 u : %d, <%s>\n", u, &data->input[data->i + u]);
				// printf ("u 3 %d <%s>\n", u, tok->arg);
				// printf ("INFO 3 %d <%s>\n", ft_str_size(tok->arg), tok->arg);
			}
			else if ((data->input[data->i + u] == '\"' && data->input[data->i + u + 1] == '\"') || (data->input[data->i + u] == '\'' && data->input[data->i + u + 1] == '\''))
			{
				// printf ("Q null <%s>\n", &(data->input[data->i + u]));
				u = u + 2;
				// printf ("3 u : %d, <%s>\n", u, &data->input[data->i + u]);
				// printf ("Q null <%s>\n", &(data->input[data->i + u]));
				// printf ("INFO 4 %d <%s>\n", ft_str_size(tok->arg), tok->arg);
			}
			else if (data->input[data->i + u] == '$')
			{

				// printf("FDP\n");
				// printf ("4 u : %d, <%s>\n", u, &data->input[data->i + u]);
				tmp = ft_ret_dollar(data, &(data->input[data->i + u]));
				// printf("FDP <%s>\n", tmp);
				// printf("sizeof tok arg <%d>\n", ft_str_size(tok->arg));
				if (tmp != NULL)
					ft_copie_dest_src(tok, tmp);
				ft_strdel(&tmp);
				// ft_copie_dest_src(tok, ft_ret_dollar(data, &(data->input[data->i + u])));
				// printf("FDP\n");
				// u = u + ft_str_size(ft_ret_dollar(data, &(data->input[data->i + u])));
				// printf ("u : %d, <%s>\n", u, &data->input[data->i + u]);
				u++;
				// printf ("u : %d, <%s>\n", u, &data->input[data->i + u]);
				while (data->input[data->i + u] && data->input[data->i + u] != ' ' && data->input[data->i + u] != '$' && ft_is_separator(data->input, (data->i + u)) == 0 && data->input[data->i + u] != '\"' && data->input[data->i + u] != '\'')
					u++;
				// printf ("u : %d, <%s>\n", u, &data->input[data->i + u]);
				// printf("tok arg <%s>\n", tok->arg);
				// printf("FDP sortie\n");
				// printf ("4 u : %d, <%s>\n", u, &data->input[data->i + u]);
				// printf ("INFO 5 %d <%s>\n", ft_str_size(tok->arg), tok->arg);
			}
			else
			{
				i = 0;
				while (tok->arg[i] && tok->arg[i] != '\0')
					i++;
				// printf("els pre tok <%s> u %d i %d c <%c>\n", tok->arg, u, i, data->input[data->i + u]);
				tok->arg[i] = data->input[data->i + u];
				// i++;
				// printf("els apr tok <%s> u %d i %d c <%c>\n", tok->arg, u, i, data->input[data->i + u]);
				if (data->input[data->i + u] == ' ')
				{
					// printf("while space\n");
					u = u + ft_space(data->input, data->i + u);
				}
				else
					u++;
				// printf ("INFO 6 %d <%s>\n", ft_str_size(tok->arg), tok->arg);
			}
			// printf("fin bcl tmp <%s> u %d c <%c>\n", tmp, u, data->input[data->i + u]);
			// bordel++;
			// jean++;
		}
		while (tok->arg[i] && tok->arg[i] != '\0')
			i++;
		tok->arg[i] = '\0';
		data->i = data->i + u;
		// printf ("INFO 7 %d <%s>\n", ft_str_size(tok->arg), tok->arg);
	}
	if (size == 0 && data->input[data->i + u] == '\"')
	{
		// printf ("----OUI JEAN\n");
		// printf ("<%s>\n", &(data->input[data->i + u]));
		u++;
		while (data->input[data->i + u] && data->input[data->i + u] != '\"')
			u++;
		// printf ("<%s>\n", &(data->input[data->i + u]));
		if (data->input[data->i + u] == '\"')
			u++;
		// printf ("<%s>\n", &(data->input[data->i + u]));
		data->i = data->i + u;
	}
	else if (size == 0)
		data->err = 200; // erreur malloc
	// printf ("-------------Sortie malloc arg, %d <%s>\n", ft_str_size(tok->arg), tok->arg);
	// printf("\n");
}



/*	NOUVEAUX SYSTEME DE GESTION DES ARGUMENTS	*/



int		ft_incre_one_arg(t_data *data, int u) // incremente en fonction d'un 'argument' d'entree
{
	// int	u;

	// u = 0;
	// printf ("incre one arg : u : %d <%s>\n", u, &data->input[data->i + u]);
	while (data->input[data->i + u] && data->input[data->i + u] != ' ' && ft_is_separator(data->input, data->i + u) == 0)
	{
		if (data->input[data->i + u] == '\'')
		{
			u++;
			while (data->input[data->i + u] && data->input[data->i + u] != '\'')
				u++;
			u++;
		}
		else if (data->input[data->i + u] == '\"')
		{
			u++;
			while (data->input[data->i + u] && data->input[data->i + u] != '\"')
				u++;
			u++;
		}
		else
			u++;
		// printf ("incre one arg : dans while u : %d <%s>\n", u, &data->input[data->i + u]);
	}
	// printf ("incre one arg : u : %d <%s>\n", u, &data->input[data->i + u]);
	return (u);
}

int		ft_size_one_arg(t_data *data, int s) // renvoie la taille d'un seul argument
{
	int	u;
	int	ret;
	char	*tmp;

	u = 0;
	// s = s + data->i;
	ret = 0;
	
	// ft_putstr("size one arg :\n");
	// ft_putnbr(s);
	s = s + data->i;
	// ft_putstr("size one arg :\n");
	// ft_putnbr(s);
	// ft_putstr("size one arg :\n");
	// ft_putnbr(ret);
	// ft_putstr("size one arg :\n");
	// printf("size one arg : entree\n");
	while (ft_is_separator(data->input, (s + u)) == 0 && data->input[s + u] && data->input[s + u] != ' ')
	{
		// ft_putstr("size one arg : while\n");
		// ft_putnbr(ret);
		// printf("size one arg : while : ret %d\n", ret);
		if (data->input[s + u] == '\"' && data->input[s + u + 1] != '\"' && data->input[s + u + 1] != '\0')
		{
			// ft_putstr("size one arg : 1\n");
			ret = ret + ft_str_size(ft_ret_double_quote(data, &data->input[s + u], 0));
			u++;
			while (data->input[s + u] != '\"')
				u++;
			u++;
		}
		else if (data->input[s + u] == '\'' && data->input[s + u + 1] != '\'' && data->input[s + u + 1] != '\0')
		{
			// ft_putstr("size one arg : 2\n");
			ret = ret + ft_str_size(ft_ret_simple_quote(data, &data->input[s + u], 0));
			while (data->input[s + u] != '\'')
				u++;
			u++;
			// u = u + ft_str_size(ft_ret_simple_quote(data, &data->input[s + u], 0));
		}
		else if ((data->input[s + u] == '\"' && data->input[s + u + 1] == '\"') || (data->input[s + u] == '\'' && data->input[s + u + 1] == '\''))
		{
			// ft_putstr("size one arg : 3\n");
			u = u + 2;
		}
		else if (data->input[s + u] == '$')
		{
			tmp = ft_ret_dollar(data, &(data->input[s + u]));
			// ft_putstr("size one arg : 4\n");
			// ft_putnbr(ret);
			// printf("size one arg : dollar entree\n");	
			if (ft_str_size(tmp) > 0)
			{
				// printf("size one arg : if\n");
				ret = ret + ft_str_size(tmp);
				u++;
				while (ft_is_separator(data->input, (s + u)) == 0 && data->input[s + u] && data->input[s + u] != ' ' && data->input[s + u] != '$')
					u++;
			}
			else
			{
				// printf("size one arg : else\n");
				ret++;
				u++;
			}
			ft_strdel(&tmp);
			ft_putnbr(ret);
			// printf("size one arg : dollar sortie\n");
		}
		else
		{
			// ft_putstr("size one arg : 5\n");
			// ft_putnbr(ret);
			u++;
			ret++;
			// ft_putnbr(ret);
		}
	}
	// ft_putstr("size one arg : sortie : ret :<");
	// ft_putnbr(ret);
	// ft_putstr(">\n");
	// printf("size one arg : sortie : ret %d\n", ret);
	return (ret);
}

char	*ft_one_simple_arg(t_data *data, int i) // renvoie une chaine simple contenant des termes
{
	char	*ret;
	int		j;

	j = 0;
	while (data->input[i + j] && data->input[i + j] != ' ' && ft_is_separator(data->input, i + j) == 0 && data->input[i + j] != '\'' && data->input[i + j] != '\"' && data->input[i + j] != '$')
		j++;
	ret = ft_malloc_str(data, j);
	j = 0;
	while (data->input[i + j] && data->input[i + j] != ' ' && ft_is_separator(data->input, i + j) == 0 && data->input[i + j] != '\'' && data->input[i + j] != '\"' && data->input[i + j] != '$')
	{
		ret [j] = data->input[i + j];
		j++;
	}
	ret [j] = '\0';
	return (ret);
}

char	*ft_one_arg(t_data *data, int u) // renvoie le premier argument en partant de u dans data input
{
	char	*ret;
	char	*tmp;
	char	*tmp2;
	int		i;

	i = 0;

	// ft_putstr("one arg :\n");
	// ft_putnbr(u);
	// printf("one arg : malloc ret\n");
	// tmp = ft_size_one_arg(data, u);
	ret = ft_malloc_str(data, ft_size_one_arg(data, u));
	u = u + data->i;
	// ft_putstr("one arg : 1\n");
	while (data->input[i + u] && data->input[i + u] != ' ' && ft_is_separator(data->input, i + u) == 0)
	{
		/*	jean michel	*/
		// printf("one arg : debut while\n");
		// ft_putstr("one arg : i ");
		// ft_put
		if (data->input[i + u] == '\"' && data->input[i + u + 1] != '\"' && data->input[i + u + 1] != '\0')
		{
			// printf("one arg : dq : ret\n");
			tmp = ret;
			// printf("------ %p\n------ %p\n", ret, tmp);
			ret = ft_src_in_dest(data, ret, ft_ret_double_quote(data, &data->input[i + u], 0), 0);
			ft_strdel(&tmp);
			// printf("one arg : dq : ret : <%s>\n", ret);
			i++;
			while (data->input[i + u] != '\"')
				i++;
			i++;
			// printf("one arg : dq fin\n");
		}
		else if (data->input[i + u] == '\'' && data->input[i + u + 1] != '\'' && data->input[i + u + 1] != '\0')
		{
			// printf("one arg : sq : ret\n");
			tmp = ret;
			ret = ft_src_in_dest(data, ret, ft_ret_simple_quote(data, &data->input[i + u], 0), 0);
			ft_strdel(&tmp);
			// printf("one arg : sq : ret : <%s>\n", ret);
			i++;
			while (data->input[i + u] != '\'')
				i++;
			i++;
			// printf("one arg : sq fin\n");
			// ret = ret + ft_str_size(ft_ret_simple_quote(data, &data->input[i + u], 0));
			// i = i + ft_str_size(ft_ret_simple_quote(data, &data->input[i + u], 0));

		}
		else if ((data->input[i + u] == '\"' && data->input[i + u + 1] == '\"') || (data->input[i + u] == '\'' && data->input[i + u + 1] == '\''))
			i = i + 2;
		else if (data->input[i + u] == '$')
		{
			tmp2 = ft_ret_dollar(data, &(data->input[i + u]));
			if (ft_str_size(tmp2) > 0) // A FAIRE : ajouter la gestion de un seul doll directement dans la fonction ret_dollar
			{
				tmp = ret;
				ret = ft_src_in_dest(data, ret, tmp2, 0);
				ft_strdel(&tmp);
				// printf("one arg : dollar i %d\n", i);
			}
				// i = i + ft_str_size(ret);
				// ret[ft_str_size(ret)] = '\0';
			i++;
			while (ft_is_separator(data->input, (i + u)) == 0 && data->input[i + u] && data->input[i + u] != ' ' && data->input[i + u] != '$')
				i++;
			// printf("one arg : dollar i %d\n", i);
				// ret[i] = '\0';
			ft_strdel(&tmp2);
		}
		else
		{
			// printf("one arg : else");
			tmp = ret;
			ret = ft_src_in_dest(data, ret, ft_one_simple_arg(data, i + u), 0);
			ft_strdel(&tmp);
			while (data->input[i + u] && data->input[i + u] != ' ' && ft_is_separator(data->input, i + u) == 0 && data->input[i + u] != '\'' && data->input[i + u] != '\"' && data->input[i + u] != '$')
				i++;
		}
		/*	jean michel	*/
		// i++;
		// printf("one arg : fin while\n");
	}
	// printf("one arg : fin i %d\n", i);
	// ret[i] = '\0';
	// printf("one arg : ret : <%s>\n", ret);
	return (ret);
}

void	ft_malloc_builtin_arg(t_data *data, t_token *tok) // permet de malloc les arguments d'un builtin dans arg.
{
	int		u;
	int max = 0;
	char	*tmp;
	char	*tmp2;

	u = 0;
	// printf("malloc builting arg :\n");
	while (data->input[data->i + u] && ft_is_separator(data->input, data->i + u) == 0 && max < 20)
	{
		// printf("malloc builtin : debut while\n");
		u = u + ft_space(data->input, data->i + u);
		// printf("malloc builtin : strdel\n");
		// ft_strdel(&tok->arg);
		// printf("malloc builtin : one arg tmp\n");
		tmp = ft_one_arg(data, u);
		if (tok->arg != NULL)
			tmp2 = tok->arg;
		// printf("malloc builtin : one arg tok arg\n");
		// printf("tok arg <%s>\n", tok->arg);
		tok->arg = ft_src_in_dest(data, tok->arg, tmp, ' ');
		// printf("tok arg <%s>\n", tok->arg);
		// ft_strdel(&tmp);
		ft_strdel(&tmp2);
		// ft_putstr("le free de tmp <");
		// ft_putstr(tmp);
		// ft_putstr(">\n");
		// printf("malloc builtin : free tmp <%s> %p", tmp, tmp);
		// if (tmp != NULL)
		// {
		// 	free(tmp);
		// 	tmp = NULL;
		// }
		// ft_strdel(&tmp);
		// ft_putstr("le free de tmp : OK\n");
		// printf("malloc builtin : incre one arg : u %d <%s>\n", u, &data->input[data->i + u]);
		u = ft_incre_one_arg(data, u);
		// printf("malloc builtin : fin while : u %d <%s>\n", u, &data->input[data->i + u]);
		max ++;
		// ft_strdel(&tmp); // probleme cheloue ici ???
	}
	// printf("malloc builting arg : sortie : <%s>\n", tok->arg);
	data->i = data->i + u;
}
