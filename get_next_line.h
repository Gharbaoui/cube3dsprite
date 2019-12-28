/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-ghar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 00:35:23 by mel-ghar          #+#    #+#             */
/*   Updated: 2019/11/04 18:52:54 by mel-ghar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

int		if_error(char **line, char **tmp, char **buffer, int fd);
char	*ft_strjoin(char *s1, char *s2, int is_free);
char	*ft_substr(char *str, int start, int len);
int		get_next_line(int fd, char **line);
int		ft_strlen(char *str);
int		handel(char **line, char **tmp, char **buff);
void	*ft_calloc(int a, int b);
int		pos_nl(char *buff);
int		handel_last_line(char **line, char **buff, char **tmp, int ret_read);
char	*ft_strdup(char *str);
#endif
