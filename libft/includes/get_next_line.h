/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:07:57 by MZimeris          #+#    #+#             */
/*   Updated: 2025/07/10 13:49:33 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// pour malloc free
# include <stdlib.h>
// pour open
# include <fcntl.h>
// pour open read close
# include <unistd.h> 

// valeur par défaut du BUFFER si non spécifié à la compilation
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# if BUFFER_SIZE > 10000
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif

# ifndef MAX_FD
#  define MAX_FD 10
# endif

char	*get_next_line(int fd);

// utils
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
char	*ft_substr(const char *s, unsigned int start, size_t len);

#endif /*GET_NEXT_LINE_H*/
