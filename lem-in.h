/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpascaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:44:23 by mpascaud          #+#    #+#             */
/*   Updated: 2018/05/09 17:28:58 by mpascaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef LEM_IN_H

# define LEM_IN_H
# define BUFF_SIZE 65
# define MAX_FD 4865

# include <stdlib.h>
# include <unistd.h>

#include <stdio.h>



int				get_next_line(const int fd, char **line);
char			*ft_strnew(size_t size);
size_t			ft_strlen(const char *s);
char			*ft_strcpy(char *dest, const char *src);
char			*ft_strncat(char *dest, const char *src, size_t n);
int				ft_isdigit(int c);
char			*ft_strstr(const char *haystack, const char *needle);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_atoi(const char *str);

typedef struct	s_filist
{
	char	*line;
	struct	s_filist	*previous;
	struct	s_filist	*next;
}				t_filist;

typedef struct	s_roomlist
{
	int		taken;
	int		way;



	char				**beftunnels;
	char				**tunnels;
	int					place;
	char				*name;
	struct	s_roomlist	*previous;
	struct	s_roomlist	*next;
}				t_roomlist;

typedef struct	s_waylist
{
	char	*name;
	int		way;
	int		place;
	int		ants;
	struct	s_waylist	*previous;
	struct	s_waylist	*next;

}				t_waylist;

typedef struct	s_listlist
{
	struct	s_waylist	*waylist;
	int		ants;
	struct	s_listlist	*previous;
	struct	s_listlist	*next;
}				t_listlist;

typedef struct	s_namelist
{
	char	*name;
	struct s_namelist	*previous;
	struct s_namelist	*next;
}				t_namelist;

typedef struct	s_variables
{

	char        *tmp;
	t_filist    *filist;
	t_filist    *filistart;
	t_roomlist  *roomlist;
	t_roomlist  *roomlistart;
	t_listlist  *listlist;
	t_listlist  *listlistart;
	t_namelist  *namelist;
	t_namelist  *namelistart;
	int         way;

}				t_variables;


#endif
















