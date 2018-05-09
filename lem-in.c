/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpascaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:29:32 by mpascaud          #+#    #+#             */
/*   Updated: 2018/05/09 17:02:09 by mpascaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lem-in.h"



t_filist	*ft_filstnew(char *tmp, t_filist *link)
{
	t_filist	*nextlink;
	char		*str;

	if (!(nextlink = (t_filist*)malloc(sizeof(t_filist))))
		return (NULL);
	nextlink->previous = link;
	str = ft_strnew(ft_strlen(tmp));
	nextlink->line = ft_strcpy(str, tmp);
	nextlink->next = NULL;
	return (nextlink);
}


t_roomlist	*ft_roomlstnew(t_roomlist *roomlist)
{
	t_roomlist	*nextlink;

	if (!(nextlink = (t_roomlist*)malloc(sizeof(t_roomlist))))
		return (NULL);
	nextlink->previous = roomlist;
	nextlink->place = -1;
	nextlink->next = NULL;
	return (nextlink);
}

int		ft_this_is_new_room(t_filist *filist)
{
	int		result;
	int		i;

	result = 0;
	i = 0;
	if (filist->line == NULL)
		return (0);
	while ((filist->line)[i] != '\0')
	{

		i++;
	}
	i--;
	while (ft_isdigit((filist->line)[i]) == 1)
	{
		i--;
		if (i < 0)
			return (0);
	}
	if ((filist->line)[i] == ' ' && (filist->line)[0] != '#')
	{
		return (1);
	}
	return (0);
}

void	ft_cpyname(t_filist *filist, t_roomlist *roomlist)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while ((filist->line)[i] != '\0')
		i++;
	i--;
	while (ft_isdigit((filist->line)[i]) == 1)
		i--;
	i--;
	while (ft_isdigit((filist->line)[i]) == 1)
		i--;
	i--;
	roomlist->name = ft_strnew(i + 1);
	while (j <= i)
	{
		(roomlist->name)[j] = (filist->line)[j];
		j++;
	}

}


void	ft_name(t_filist *filist, t_roomlist *roomlist)
{
	filist = filist->next;
	while (filist != NULL)
	{
		if (ft_this_is_new_room(filist) == 1)
		{
			roomlist->next = ft_roomlstnew(roomlist);
			roomlist = roomlist->next;
			ft_cpyname(filist, roomlist);
		}
		filist = filist->next;
	}
}

void	ft_show_roomlist(t_roomlist *roomlist)
{
	int		i;

	i = 0;
	roomlist = roomlist->next;
	while (roomlist != NULL)
	{
		printf("roomlist->name = %s\n", roomlist->name);
		printf("roomlist->place = %d\n", roomlist->place);
		while ((roomlist->beftunnels)[i] != NULL)
		{
			printf("roomlist->beftunnels[%d] = %s\n", i, roomlist->beftunnels[i]);
			i++;
		}
		i = 0;
		while ((roomlist->tunnels)[i] != NULL)
		{
			printf("roomlist->tunnels[%d] = %s\n", i, roomlist->tunnels[i]);
			i++;
		}
		printf("way = %d\n", roomlist->way);
		printf("taken = %d\n", roomlist->taken);
		printf("\n");
		i = 0;
		roomlist = roomlist->next;

	}
}


int		ft_disizit(t_filist *filist, t_roomlist *roomlist)
{
	int		i;

	i = 0;
	while ((roomlist->name)[i] != '\0')
	{
		if ((roomlist->name)[i] != (filist->line)[i])
		{
			return (0);
		}
		i++;
	}
	if (filist->line[i] != ' ' || ft_isdigit(filist->line[i + 1]) == 0)
		return (0);
	return (1);
}


void	ft_place_start(t_filist *filist, t_roomlist *roomlist)
{
	int		i;

	i = 0;
	filist = filist->next;
	roomlist = roomlist->next;
	while (filist != NULL)
	{
		if (ft_strstr(filist->line, "##start") && (filist->line)[7] == '\0')
		{
			filist = filist->next;
			while (roomlist != NULL)
			{
				if (ft_disizit(filist, roomlist) == 1)
				{
					roomlist->place = 0;
					return ;
				}
				roomlist = roomlist->next;
			}

		}
		filist = filist->next;
	}

}

void	ft_place_end(t_filist *filist, t_roomlist *roomlist)
{
	filist = filist->next;
	roomlist = roomlist->next;
	while (filist != NULL)
	{
		if (ft_strstr(filist->line, "##end") && (filist->line)[5] == '\0')
		{
			filist = filist->next;
			while (roomlist != NULL)
			{
				if (ft_disizit(filist, roomlist) == 1)
				{
					roomlist->place = -2;
					return ;
				}
				roomlist = roomlist->next;
			}
		}
		filist = filist->next;
	}
}


int		ft_disiz_tunnel(t_filist *filist, t_roomlist *roomlist)
{
	int		there_is_tunnel;
	int		i;

	there_is_tunnel = 0;
	i = 0;

	while ((filist->line)[i] != '\0')
	{
		if ((filist->line)[i] == '-')
			there_is_tunnel = 1;
		i++;
	}
	if (there_is_tunnel == 0)
		return (0);

	i = 0;
	while ((roomlist->name)[i] != '\0')
	{
		if ((filist->line)[i] != (roomlist->name)[i] || (filist->line)[i] == '\0')
			return (0);
		i++;
	}
	if ((filist->line)[i] != '-')
		return (0);
	return (1);
}

int		ft_disiz_beftunnel(t_filist *filist, t_roomlist *roomlist)
{
	int		there_is_tunnel;
	int		i;
	int		j;

	there_is_tunnel = 0;
	i = 0;
	j = 0;
	while ((filist->line)[i] != '\0')
	{
		if ((filist->line)[i] == '-')
		{
			there_is_tunnel = 1;
			i++;
			break ;
		}
		i++;
	}
	if (there_is_tunnel == 0)
		return (0);

	while ((roomlist->name)[j] != '\0')
	{
		if ((filist->line)[i] != (roomlist->name)[j] || (filist->line)[i] == '\0')
			return (0);
		i++;
		j++;
	}
	if ((filist->line)[i] != '\0')
		return (0);

	return (1);
}

char	*ft_link(t_filist *filist, t_roomlist *roomlist)
{
	char	*tunname;
	int		i;
	int		start;
	int		tmp;

	i = 0;
	start = 0;
	tmp = 0;
	while ((filist->line)[start] != '-')
		start++;
	start++;
	tmp = start;
	while ((filist->line)[tmp] != '\0')
	{
		tmp++;
		i++;
	}
	tunname = (char*)malloc(sizeof(char) * (i + 1));
	tmp = start;
	i = 0;
	while ((filist->line)[tmp] != '\0')
	{
		tunname[i] = (filist->line)[tmp];
		i++;
		tmp++;
	}
	tunname[i] = '\0';
	return (tunname);
}

char	*ft_beflink(t_filist *filist, t_roomlist *roomlist)
{
	char	*tunname;
	int		i;

	i = 0;
	while ((filist->line)[i] != '-')
	{
		i++;
	}
	tunname = (char*)malloc(sizeof(char) * (i + 1));
	i = 0;
	while ((filist->line)[i] != '-')
	{
		tunname[i] = (filist->line)[i];
		i++;
	}
	tunname[i] = '\0';
	return (tunname);
}


void	ft_tunnels(t_filist *filist, t_roomlist *roomlist)
{
	int		i;
	int		tunnbr;
	t_filist	*filistart;
	t_roomlist	*roomlistart;

	i = 0;
	tunnbr = 0;
	filist = filist->next;
	filistart = filist;
	roomlist = roomlist->next;
	roomlistart = roomlist;
	tunnbr = 0;
	filist = filistart;
	while (roomlist != NULL)
	{
		while (filist != NULL)
		{
			if (ft_disiz_tunnel(filist, roomlist) == 1)
			{
				tunnbr++;
			}
			filist = filist->next;
		}
		roomlist->tunnels = (char**)malloc(sizeof(char*) * (tunnbr + 1));
		roomlist = roomlist->next;
		filist = filistart;
		tunnbr = 0;
	}

	roomlist = roomlistart;
	i = 0;
	while (roomlist != NULL)
	{
		while (filist != NULL)
		{
			if (ft_disiz_tunnel(filist, roomlist) == 1)
			{
				(roomlist->tunnels)[i] = ft_link(filist, roomlist);
				i++;

			}
			filist = filist->next;
		}
		(roomlist->tunnels)[i] = NULL;
		roomlist = roomlist->next;
		filist = filistart;
		i = 0;
	}


	tunnbr = 0;
	filist = filistart;
	roomlist = roomlistart;
	while (roomlist != NULL)
	{
		while (filist != NULL)
		{
			if (ft_disiz_beftunnel(filist, roomlist) == 1)
			{
				tunnbr++;
			}
			filist = filist->next;
		}
		roomlist->beftunnels = (char**)malloc(sizeof(char*) * (tunnbr + 1));
		roomlist = roomlist->next;
		filist = filistart;
		tunnbr = 0;
	}

	roomlist = roomlistart;
	i = 0;
	filist = filistart;
	tunnbr = 0;
	while (roomlist != NULL)
	{
		while (filist != NULL)
		{
			if (ft_disiz_beftunnel(filist, roomlist) == 1)
			{
				(roomlist->beftunnels)[i] = ft_beflink(filist, roomlist);
				i++;
			}
			filist = filist->next;
		}
		(roomlist->beftunnels)[i] = NULL;
		roomlist = roomlist->next;
		filist = filistart;
		i = 0;
	}
}

int		ft_check_previous_place(t_roomlist *roomlist, int i, t_roomlist *roomlistart)
{
	int		empty;

	empty = 0;
	roomlistart = roomlistart->next;
	while (roomlistart != NULL)
	{
		if (ft_strcmp((roomlist->beftunnels)[i], roomlistart->name) == 0)
		{
		if (roomlist->place != 0 && roomlistart->place != -1 && roomlistart->place != -2 && (roomlist->place == -1 || roomlist->place > roomlistart->place + 1))
		{
			roomlist->place = roomlistart->place + 1;
			return (1);
		}
		if (roomlistart->place != 0 && roomlist->place != -1 && roomlist->place != -2 && (roomlistart->place == -1 || roomlistart->place > roomlist->place + 1))
		{
			roomlistart->place = roomlist->place + 1;
			return (1);
		}
	}
	roomlistart = roomlistart->next;
}
return (0);
}

int		ft_check_next_place(t_roomlist *roomlist, int i, t_roomlist *roomlistart)
{
	roomlistart = roomlistart->next;
	while (roomlistart != NULL)
	{
		if (ft_strcmp((roomlist->tunnels)[i], roomlistart->name) == 0)
		{
			if (roomlist->place != 0 && roomlistart->place != -1 && roomlistart->place != -2 && (roomlist->place == -1 || roomlist->place > roomlistart->place + 1))
			{
				roomlist->place = roomlistart->place + 1;
				return (1);
			}
			if (roomlistart->place != 0 && roomlist->place != -1 && roomlist->place != -2 && (roomlistart->place == -1 || roomlistart->place > roomlist->place + 1))
			{
				roomlistart->place = roomlist->place + 1;
				return (1);
			}
		}
		roomlistart = roomlistart->next;
	}
	return (0);
}


void	ft_place(t_filist *filist, t_roomlist* roomlist)
{
	int			i;
	t_filist	*filistart;
	t_roomlist	*roomlistart;

	i = 0;
	filistart = filist;
	roomlistart = roomlist;
	filist = filist->next;
	roomlist = roomlist->next;

	while (roomlist != NULL)
	{
		while ((roomlist->beftunnels)[i] != NULL)
		{
			if (ft_check_previous_place(roomlist, i, roomlistart) == 1)
			{
				roomlist = roomlistart;
				break ;
			}
			i++;
		}
		i = 0;
		roomlist = roomlist->next;
	}

	roomlist = roomlistart;
	roomlist = roomlist->next;
	i = 0;
	while (roomlist != NULL)
	{
		while ((roomlist->tunnels)[i] != NULL)
		{
			if (ft_check_next_place(roomlist, i, roomlistart) == 1)
			{
				roomlist = roomlistart;
				break ;
			}
			i++;
		}
		i = 0;
		roomlist = roomlist->next;
	}
}

int		ft_check_connection(t_roomlist *roomlistart, t_roomlist *roomlist)
{
	int		i;

	i = 0;
	while ((roomlist->beftunnels)[i] != NULL)
	{
		if (ft_strcmp((roomlist->beftunnels)[i], roomlistart->name) == 0)
			return (1);
		i++;
	}
	i = 0;
	while ((roomlist->tunnels)[i] != NULL)
	{
		if (ft_strcmp((roomlist->tunnels)[i], roomlistart->name) == 0)
			return (1);
		i++;
	}
	return (0);
}



void	ft_ways_to_zero(t_roomlist *roomlistart)
{
	int			max;
	int			duplicate;
	t_roomlist	*roomlist;

	roomlist = roomlistart;
	roomlist = roomlist->next;
	max = 0;
	duplicate = 0;
	while (roomlist != NULL)
	{
		if (roomlist->place > max && roomlist->place != -2)
			max = roomlist->place;
		if (roomlist->way == -1)
			roomlist->way = 0;
		roomlist = roomlist->next;
	}
	roomlist = roomlistart;
	roomlist = roomlist->next;
	while (max > 0)
	{
		while (roomlist->place != max)
		{
			roomlist = roomlist->next;
		}
		roomlist = roomlist->next;
		while (roomlist != NULL)
		{
			if (roomlist->place == max)
				roomlist->way = 0;
			roomlist = roomlist->next;
		}
		roomlist = roomlistart;
		roomlist = roomlist->next;
		max--;
	}

	roomlist = roomlistart;
	roomlist = roomlist->next;


}

void	ft_takens_to_one(t_roomlist *roomlistart, int way)
{
	roomlistart = roomlistart->next;
	while (roomlistart != NULL)
	{
		if (roomlistart->way == way && roomlistart->place != 0 && roomlistart->place != -2)
			roomlistart->taken = 1;
		roomlistart = roomlistart->next;
	}
}



int		ft_no_zero(t_roomlist *roomlistart)
{
	roomlistart = roomlistart->next;

	while (roomlistart != NULL)
	{
		if (roomlistart->way == 0 && roomlistart->place != -1)
		{
			return (0);
		}
		roomlistart = roomlistart->next;
	}


	return (1);
}

int		ft_search_previous(t_roomlist *roomlist, t_roomlist *roomlistart, int way)
{
	t_roomlist	*tmp;

	roomlistart = roomlistart->next;
	tmp = roomlistart;
	while (roomlistart != NULL)
	{
		if (roomlistart->place == roomlist->place - 1
				&& roomlistart->taken == 0 
				&& roomlistart->way == way
				&& ft_check_connection(roomlistart, roomlist) == 1)
		{
			return (1);
		}
		roomlistart = roomlistart->next;
	}
	while (tmp != NULL)
	{
		if (tmp->place == roomlist->place - 1
				&& tmp->taken == 0
				&& tmp->way == 0
				&& ft_check_connection(tmp, roomlist) == 1)
			return (0);
		tmp = tmp->next;
	}
	return (-1);
}


int		ft_search_next(t_roomlist *roomlist, t_roomlist *roomlistart, int way)
{
	roomlistart = roomlistart->next;
	while (roomlistart != NULL)
	{
		if ((roomlistart->place == roomlist->place + 1 || roomlistart->place == -2)
				&& roomlistart->taken == 0
				&& (roomlistart->way == 0 || roomlistart->way == way)
				&& ft_check_connection(roomlistart, roomlist) == 1)
		{
			return (1);
		}

		roomlistart = roomlistart->next;
	}
	return (0);
}


int		ft_search_first_reverse(t_roomlist *end, t_roomlist *roomlistart, int way)
{
	int			maxplace;
	t_roomlist	*roomlist;

	maxplace = 0;
	roomlist = roomlistart;
	roomlist = roomlist->next;

	while (roomlist != NULL)
	{
		if (roomlist->taken == 0
				&& roomlist->way == way
				&& roomlist->place > maxplace 
				&& ft_check_connection(end, roomlist) == 1)
			maxplace = roomlist->place;
		roomlist = roomlist->next;
	}

	roomlist = roomlistart;
	roomlist = roomlist->next;
	while (roomlist != NULL)
	{
		if (roomlist->taken == 0
				&& roomlist->way == way
				&& (roomlist->place != -1)
				&& ft_check_connection(end, roomlist) == 1)
		{
			if (roomlist->place < maxplace)
			{
				maxplace = roomlist->place;
			}
		}
		roomlist = roomlist->next;
	}

	roomlist = roomlistart;
	roomlist = roomlist->next;
	while (roomlist != NULL)
	{
		if (roomlist->taken == 0
				&& roomlist->way == way
				&& roomlist->place == maxplace
				&& ft_check_connection(end, roomlist) == 1)
		{
			roomlist->taken = 1;
			break ;
		}
		roomlist = roomlist->next;
	}
	return (maxplace);
}


void	ft_search_other_reverses(t_roomlist *roomlistart, int maxplace, int way)
{
	t_roomlist	*roomlist;
	t_roomlist	*roomax;

	roomlist = roomlistart;
	roomlist = roomlist->next;

	while (roomlist != NULL)
	{
		if (roomlist->taken == 1
				&& roomlist->way == way
				&& roomlist->place == maxplace)
		{
			roomax = roomlist;
			break ;
		}
		roomlist = roomlist->next;
	}

	roomlist = roomlistart;
	roomlist = roomlist->next;

	while (roomlist != NULL)
	{
		if (roomlist->place == 0
				&& ft_check_connection(roomlist, roomax) == 1)
		{
			return ;
		}
		if (roomlist->taken == 0
				&& roomlist->way == way
				&& roomlist->place == roomax->place - 1
				&& ft_check_connection(roomlist, roomax) == 1)
		{
			roomlist->taken = 1;
			roomax = roomlist;
			roomlist = roomlistart;
		}
		roomlist = roomlist->next;
	}
}

int		ft_reverse(t_roomlist *roomlist, int way)
{
	t_roomlist	*roomlistart;
	t_roomlist	*roomway;
	int		maxplace;

	roomlistart = roomlist;
	roomlist = roomlist->next;
	maxplace = 0;
	while (roomlist != NULL)
	{
		if (roomlist->place == -2)
		{
			maxplace = ft_search_first_reverse(roomlist, roomlistart, way);
		}
		roomlist = roomlist->next;
	}
	if (maxplace == 0)
		return (0);
	roomlist = roomlistart;
	roomlist = roomlist->next;

	ft_search_other_reverses(roomlistart, maxplace, way);

	return (1);
}

void	ft_reset(t_roomlist *roomlistart, int way)
{
	while (roomlistart != NULL)
	{
		if (!(roomlistart->taken == 1
					&& roomlistart->way <= way
					&& roomlistart->place > 0))
		{
			roomlistart->way = 0;
		}
		roomlistart = roomlistart->next;
	}
}


int		ft_way(t_filist *filist, t_roomlist *roomlist, t_roomlist *roomlistart, int way)
{
	int		progress;


	filist = filist->next;
	roomlist = roomlist->next;

	progress = 0;
	while (roomlist != NULL)
	{
		if (roomlist->place == 0 || roomlist->place == -2)
		{
			roomlist->way = way;
		}
		roomlist = roomlist->next;
	}

	roomlist = roomlistart;
	roomlist = roomlist->next;

	while (1)
	{
		while (roomlist != NULL)
		{
			if (roomlist->way == 0 && roomlist->place != 0 && roomlist->taken == 0 && ft_search_previous(roomlist, roomlistart, way) == 1)
			{
				roomlist->way = way;
			}

			if ((roomlist->way == way || roomlist->way == 0) && roomlist->place != 0 && roomlist->place != -2 && (ft_search_next(roomlist, roomlistart, way) == 0 || ft_search_previous(roomlist, roomlistart, way) == -1))
			{
				roomlist->way = -1;
			}
			roomlist = roomlist->next;
		}
		if (ft_no_zero(roomlistart) == 0)
		{
			roomlist = roomlistart;
			roomlist = roomlist->next;
		}
		else
		{
			if (ft_reverse(roomlistart, way) == 1)
			{
				ft_reset(roomlistart, way);
				return (1);
			}
			else
			{
				return (0);
			}
		}
	}


	return (0);
}

void	ft_init(t_roomlist *roomlist)
{
	roomlist = roomlist->next;
	while (roomlist != NULL)
	{
		roomlist->place = -1;
		roomlist->taken = 0;
		roomlist->way = 0;
		roomlist->beftunnels = NULL;
		roomlist = roomlist->next;
	}
}

t_waylist	*ft_waylistnew(t_roomlist *roomlist, int way, t_waylist *waylist)
{
	t_waylist	*nextlink;

	nextlink = (t_waylist*)malloc(sizeof(t_waylist));
	nextlink->previous = waylist;
	nextlink->next = NULL;
	return (nextlink);
}

t_waylist	*ft_waylist(t_roomlist *roomlistart, t_roomlist *roomlist, int way)
{
	int		max;
	t_waylist	*waylist;
	t_waylist	*waylistart;
	int		place;
	char	*str;

	max = way;
	place = 0;

	waylist = (t_waylist*)malloc(sizeof(t_waylist));
	waylist->name = NULL;
	waylist->way = way;
	waylist->place = -1;
	waylist->previous = NULL;
	waylist->next = NULL;
	waylistart = waylist;

	roomlist = roomlist->next;
	while (roomlist != NULL)
	{
		if ((roomlist->place == 0 || roomlist->way == way) && roomlist->place == place)
		{
			waylist->next = ft_waylistnew(roomlist, way, waylist);
			waylist = waylist->next;
			waylist->place = roomlist->place;
			waylist->way = roomlist->way;
			if (waylist->place == 0)
				waylist->way = way;
			str = ft_strnew(ft_strlen(roomlist->name));
			waylist->name = ft_strcpy(str, roomlist->name);
			place++;
			roomlist = roomlistart;
		}
		roomlist = roomlist->next;
	}

	roomlist = roomlistart;
	roomlist = roomlist->next;
	while (roomlist != NULL)
	{
		if (roomlist->place == -2)
		{
			waylist->next = ft_waylistnew(roomlist, way, waylist);
			waylist = waylist->next;
			waylist->place = roomlist->place;
			waylist->way = way;
			str = ft_strnew(ft_strlen(roomlist->name));
			waylist->name = ft_strcpy(str, roomlist->name);

		}
		roomlist = roomlist->next;
	}
	return (waylistart);
}

t_listlist	*ft_listlistnew(t_listlist *listlist, int way)
{
	t_listlist	*nextlink;

	nextlink = (t_listlist*)malloc(sizeof(t_listlist));
	nextlink->previous = listlist;
	nextlink->next = NULL;
	return (nextlink);
}

void	ft_listlist(t_listlist *listlist, t_roomlist *roomlistart, t_roomlist *roomlist, int way)
{
	int		max;

	max = way;
	way = 1;
	while (way <= max)
	{
		listlist->next = ft_listlistnew(listlist, way);
		listlist = listlist->next;
		listlist->waylist = ft_waylist(roomlistart, roomlist, way);
		way++;
	}

}

void	ft_ants(t_listlist *listlist, t_filist *filistart)
{
	t_listlist	*tmp;
	t_waylist	*waytmp;

	tmp = listlist;
	filistart = filistart->next;
	if (filistart != NULL)
		tmp->ants = ft_atoi(filistart->line);
	while (tmp != NULL)
	{
		waytmp = tmp->waylist;
		while (waytmp != NULL)
		{
			waytmp->ants = 0;
			waytmp = waytmp->next;
		}
		tmp = tmp->next;
	}
}

void	ft_show_listlist(t_listlist *listlist)
{
	t_listlist *tmp;
	t_waylist *waytmp;
	tmp = listlist;
	printf("ants = %d\n", tmp->ants);
	printf("\n");
	tmp = tmp->next;
	while (tmp != NULL)
	{
		waytmp = tmp->waylist;
		while (waytmp != NULL)
		{
			printf("way = %d, place = %d, name = %s, ants = %d\n", waytmp->way, waytmp->place, waytmp->name, waytmp->ants);

			waytmp = waytmp->next;
		}
		printf("\n");
		tmp = tmp->next;
	}
}


void	ft_free_beftunnels(t_roomlist *roomlist)
{
	int		i;

	i = 0;
	if (roomlist->beftunnels != NULL)
	{
		while ((roomlist->beftunnels)[i] != NULL)
		{
			free((roomlist->beftunnels)[i]);
			i++;
		}
		free((roomlist->beftunnels)[i]);
		free(roomlist->beftunnels);
	}


}

void	ft_free_tunnels(t_roomlist *roomlist)
{
	int		i;

	i = 0;
	if (roomlist->tunnels != NULL)
	{
		while ((roomlist->tunnels)[i] != NULL)
		{
			free((roomlist->tunnels)[i]);
			i++;
		}
		free((roomlist->tunnels)[i]);
		free(roomlist->tunnels);
	}
}

void	ft_free_only_two(t_filist *filistart, t_namelist *namelist)
{
	t_filist    *tmp;
	t_namelist	*namelistmp;

	tmp = filistart;
	namelistmp = namelist;
	
	while (tmp != NULL)
	{
		tmp = filistart->next;
		free(filistart->line);
		free(filistart);
		filistart = tmp;
	}
	free(tmp);

	while (namelist != NULL)
	{
		namelistmp = namelist->next;
		free(namelist->name);
		free(namelist);
		namelist = namelistmp;
	}
	free(namelist);

}

void	ft_free_no_listlist(t_filist *filistart, t_roomlist *roomlist, t_namelist *namelist)
{
	t_filist    *tmp;
	t_roomlist    *roomlistmp;
	t_namelist	*namelistmp;

	tmp = filistart;
	namelistmp = namelist;
	roomlistmp = roomlist->next;
	
	while (tmp != NULL)
	{
		tmp = filistart->next;
		free(filistart->line);
		free(filistart);
		filistart = tmp;
	}
	free(tmp);

	while (namelist != NULL)
	{
		namelistmp = namelist->next;
		free(namelist->name);
		free(namelist);
		namelist = namelistmp;
	}
	free(namelist);
	
	roomlistmp = roomlist->next;
	free(roomlist);
	roomlist = roomlistmp;

	while (roomlist != NULL)
	{
		free(roomlist->name);
		ft_free_beftunnels(roomlist);
		ft_free_tunnels(roomlist);
		roomlistmp = roomlist->next;
		free(roomlist);
		roomlist = roomlistmp;
	}
		free(roomlist);

}



void    ft_free(t_filist *filistart, t_roomlist *roomlist, t_listlist *listlist, t_namelist *namelist)
{
	t_filist    *tmp;
	t_roomlist    *roomlistmp;
	t_listlist    *listlistmp;
	t_waylist    *waylistmp;
	t_namelist	*namelistmp;
	int            i;

	i = 0;
	tmp = filistart;
	roomlistmp = NULL;
	listlistmp = NULL;
	waylistmp = NULL;
	namelistmp = namelist;

	while (tmp != NULL)
	{
		tmp = filistart->next;
		free(filistart->line);
		free(filistart);
		filistart = tmp;
	}
	free(tmp);

		
	while (namelist != NULL)
	{
		namelistmp = namelist->next;
		free(namelist->name);
		free(namelist);
		namelist = namelistmp;
	}
	free(namelist);




	roomlistmp = roomlist->next;
	free(roomlist);
	roomlist = roomlistmp;

	while (roomlist != NULL)
	{
		free(roomlist->name);
		ft_free_beftunnels(roomlist);
		ft_free_tunnels(roomlist);
		roomlistmp = roomlist->next;
		free(roomlist);
		roomlist = roomlistmp;
	}
		free(roomlist);


	listlistmp = listlist;
	while (listlistmp != NULL)
	{
		listlistmp = listlist->next;
		while (listlist->waylist != NULL)
		{
			free(listlist->waylist->name);
			waylistmp = listlist->waylist->next;
			free(listlist->waylist);
			listlist->waylist = waylistmp;
		}
		free(listlist);
		listlist = listlistmp;
	}
	free(listlist);
}

int		ft_at_least_one_room(char *tmp)
{
	int		result;
	int		i;

	result = 0;
	i = 0;
	if (tmp == NULL)
		return (0);
	while (tmp[i] != '\0')
	{
		i++;
	}
	i--;
	while (ft_isdigit(tmp[i]) == 1)
	{
		i--;
		if (i < 0)
			return (0);
	}
	i--;
	while (ft_isdigit(tmp[i]) == 1)
	{
		i--;
		if (i < 0)
			return (0);
	}
	if (tmp[i] == ' ' && tmp[0] != '#')
	{
		return (1);
	}
	return (0);
}

t_namelist		*ft_new_name(char *tmp, t_namelist *namelist)
{
	t_namelist	*newlink;
	char		*str;
	int			i;
	int			limit;


	i = 0;
	newlink = (t_namelist*)malloc(sizeof(t_namelist));
	newlink->previous = namelist;
	newlink->next = NULL;

	while (tmp[i])
		i++;
	i--;
	while (ft_isdigit(tmp[i]) == 1)
		i--;
	i--;
	while (ft_isdigit(tmp[i]) == 1)
		i--;
	
	limit = i;
	i = 0;
	newlink->name = ft_strnew(limit);
	while (i < limit)
	{
		(newlink->name)[i] = tmp[i];
		i++;
	}

	return (newlink);

}

int		ft_already(char	*name, t_namelist *namelistart)
{
	t_namelist	*namelist;

	namelist = namelistart;
	namelist = namelist->next;

	while (namelist->next != NULL)
	{
		if (ft_strcmp(name, namelist->name) == 0)
		{
			return (1);
		}
		namelist = namelist->next;
	}
	return (0);
}

int			ft_not_yet(char *tmp, t_namelist *namelistart)
{
	t_namelist	*namelist;
	int			i;
	int			j;
	int			ok;

	namelist = namelistart;
	namelist = namelist->next;
	i = 0;
	j = 0;
	ok = 0;

	while (namelist != NULL)
	{
		while (tmp[i] != '-')
		{
			if (tmp[i] != (namelist->name)[i])
			{
				break ;
			}
			if (tmp[i + 1] == '-')
				ok = 1;
			i++;
		}
		i = 0;
		namelist = namelist->next;
	}
	if (ok == 0)
		return (1);
	ok = 0;
	i = 0;
	namelist = namelistart;
	namelist = namelist->next;
	while (namelist != NULL)
	{
		while (tmp[i] != '-')
			i++;
		i++;
		while (tmp[i] != '\0')
		{
			if (tmp[i] != (namelist->name)[j])
			{
				break ;
			}
			if (tmp[i + 1] == '\0')
			{
				ok = 1;
			}
			i++;
			j++;
		}
		i = 0;
		j = 0;
		namelist = namelist->next;
	}
	if (ok == 0)
		return (1);
	return (0);
}

int		ft_valid_line(char *tmp, int check, t_namelist *namelistart)
{
	static int	step;
	int			i;
	t_namelist	*namelist;
	int			tunnel;

	i = 0;
	tunnel = 0;

	namelist = namelistart;
	if (tmp != NULL)
	{
		if (tmp[0] == '#')
			return (1);
	}
	if (check == 1)
	{
		if (step == 3)
			return (3);
		else
			return (-1);
	}
	if (tmp != NULL && step == 0)
	{
		while (tmp[i] != '\0')
		{
			if (ft_isdigit(tmp[i]) == 0)
			{
				step = 0;
				return (0);
			}
			i++;
		}
		step = 1;
		return (step);
	}
	if (tmp != NULL && (step == 1 || step == 2))
	{
		if (ft_at_least_one_room(tmp) == 1)
		{
			while (namelist->next != NULL)
				namelist = namelist->next;
			namelist->next = ft_new_name(tmp, namelist);
			namelist = namelist->next;
			if (ft_already(namelist->name, namelistart) == 1)
			{
				return (0);
			}
			step = 2;
			return (step);
		}
	}

	if (tmp != NULL && (step == 2 || step == 3))
	{
		while (tmp[i])
		{
			if (tmp[i] == '-')
				tunnel++;
			i++;
		}
		if (tunnel > 1 || (tunnel == 0 && tmp[0] != '#'))
			return (0);
		if (tunnel == 1)
		{
			if (ft_not_yet(tmp, namelistart) == 1)
				return (0);
		}
		step = 3;
		return (step);
	}
	return (step);
}

void	ft_show_filist(t_filist *filistart)
{
	t_filist	*filist;

	filist = filistart;
	filist = filist->next;

	while (filist != NULL)
	{
		filist = filist->next;
	}
}

int		ft_start_to_end(t_filist *filistart, t_roomlist *roomlist, t_roomlist *roomlistart, int way)
{
	t_roomlist	*start;
	t_roomlist	*end;

	start = roomlistart->next;
	end = roomlistart->next;
	while (start != NULL)
	{
		if (start->place == 0)
		{
			while (end != NULL)
			{
				if (end->place == -2 && ft_check_connection(start, end) == 1)
				{
					start->way = 1;
					end->way = 1;
					return (1);
				}
				end = end->next;
			}
		}
		start = start->next;
	}
	return (0);
}

void	ft_print_anthill(t_filist *filistart)
{
	t_filist	*filist;

	filist = filistart->next;
	while (filist != NULL)
	{
		printf("%s\n", filist->line);
		filist = filist->next;
	}
}


int		main(int argc, char **argv)
{
	char		*tmp;
	t_filist	*filist;
	t_filist	*filistart;
	t_roomlist	*roomlist;
	t_roomlist	*roomlistart;
	t_listlist	*listlist;
	t_listlist	*listlistart;
	t_namelist	*namelist;
	t_namelist	*namelistart;
	int			way;

	if (argc != 1)
	{
		printf("ERROR\n");
		return (0);
	}
	filist = (t_filist*)malloc(sizeof(t_filist));
	filist->previous = NULL;
	filist->line = NULL;
	filist->next = NULL;
	filistart = filist;
	way = 1;
	namelist = (t_namelist*)malloc(sizeof(t_namelist));
	namelist->name = NULL;
	namelist->previous = NULL;
	namelist->next = NULL;
	namelistart = namelist;
	tmp = NULL;
	while (get_next_line(0, &tmp))
	{
		if (ft_valid_line(tmp, 0, namelistart) == 0)
		{
			break ;
		}
		filist->next = ft_filstnew(tmp, filist);
		filist = filist->next;
		free(tmp);
	}
	free(tmp);
	ft_show_filist(filistart);
	if (ft_valid_line(NULL, 1, NULL) != 3)
	{
		printf("ERROR\n");
		ft_free_only_two(filistart, namelist);
		return (0);
	}
	roomlist = (t_roomlist*)malloc(sizeof(t_roomlist));
	roomlist->previous = NULL;
	roomlist->place = 0;
	roomlist->name = NULL;
	roomlist->previous = NULL;
	roomlist->next = NULL;
	roomlistart = roomlist;
	ft_name(filistart, roomlist);
	ft_init(roomlist);
	ft_place_start(filistart, roomlist);
	ft_place_end(filistart, roomlist);
	ft_tunnels(filistart, roomlist);
	ft_place(filistart, roomlist);
	if (ft_start_to_end(filistart, roomlist, roomlistart, way) == 0)
	{
		while (ft_way(filistart, roomlist, roomlistart, way) == 1)
		{
			way++;
		}
		way--;
	}
	if (way == 0 || ft_atoi(filistart->next->line) == 0
			|| ft_atoi(filistart->next->line) < 0)
	{
		printf("ERROR\n");
		ft_free_no_listlist(filistart, roomlist, namelist);
		return (0);
	}
	listlist = (t_listlist*)malloc(sizeof(t_listlist));
	listlist->previous = NULL;
	listlist->waylist = NULL;
	listlist->next = NULL;
	ft_listlist(listlist, roomlistart, roomlist, way);
	ft_ants(listlist, filistart);
	listlistart = listlist;	
	listlist = listlistart;
	ft_print_anthill(filistart);
	ft_free(filistart, roomlist,listlist, namelist);
	return (0);
}
