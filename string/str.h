/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <wp3d3p@yandex.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 02:33:53 by hgranule          #+#    #+#             */
/*   Updated: 2020/07/12 18:39:40 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_H
# define STR_H

# include <stddef.h>
# include <sys/types.h>

# define STR_NPOS -1ULL

enum			e_str_errcode
{
	STR_OK = 0x0,
	STR_ERR_ALLOC = 0x1,
	STR_ERR_UNKW = 0xff
};

/*
** string is incapsulated to this struct
*/
typedef struct	s_string
{
	size_t		sz;
	void		*d;
	unsigned	f;
	unsigned	err;
}				t_string;

/*
** Creates new not detached empty string.
*/
t_string		str_new_empty(void); // [OK]

/*
** Creates not detached copy of cstr.
*/
t_string		str_new_cstr(const char *cstr); // [OK]

/*
** Creates not detached copy of t_string.
*/
t_string		str_new_str(const t_string *str); // [OK]

/*
** Creates not detached copy of data with offset and size.
*/
t_string		str_raw(const void* data, size_t offset, size_t size); // [OK]

/*
** Creates a copy of data with offset and size and then detaching it.
*/
t_string		str_raw_detach(const void* data, size_t offset, size_t size); // [OK]

/*
** Returns 0 if string isn't detached
*/
unsigned		str_is_detached(const t_string *str); // [OK]

/*
** Returns an error code of the string
*/
unsigned		str_get_errcode(const t_string *str); // [OK]

/*
** Returns lenght of the string
*/
size_t			str_len(const t_string *str); // [OK]

/*
** Returns current capacity of the string
*/
size_t			str_capacity(const t_string *str); // [OK]

/*
** If @new_size is greater then current capacity, allocates more
** space. Returns error code.
*/
unsigned		str_reserve(t_string *str, size_t new_size); // [OK]

/*
** Resizes current string lenght.
** If @new_size is greater then current size, it could allocates more space,
** fills memory with symbol @c and changes current lenght.
** If @new_size is lower then current size, it could reallocates current
** string and changes current lenght.
** Returns error code.
*/
unsigned		str_resize(t_string *str, size_t new_size, int c); // [OK]

/*
** Resizes current string lenght.
** If @new_len is greater then current size, it could allocates more space,
** fills memory with symbol @c and changes current lenght.
** If @new_len is lower then current size, it changes current lenght.
** Returns error code.
*/
unsigned		str_relenght(t_string *str, size_t new_len, int c); // [OK]

/*
** WARNING!!! It returns pointer to a modifable data, so it's
** dangerous! Make all your changes with your wisdom.
**
** Returns modifable data of string. If string isn't detached
** data, must be immutable.
*/
char			*str_data(t_string *str); // [OK]

/*
** Allocating memory if string is not detached from old memory area.
**
** Many operations for strings are works with copies, when you create
** a copy of a string, you doesn't allocate new memory, you only referencing
** to old memory area.
** If you want allocate a new memory you need to use this function.
*/
unsigned		str_detach(t_string *str); // [OK]

/*
** Deletes string, and if it was detached, frees memory area.
*/
void			str_delete(t_string *str); // [OK]

/*
** Creates not detached copy of sub-string, which starts at @offset position
** with maximum lenght @len.
*/
t_string		str_substr(const t_string *str, size_t offset, size_t len); // [OK]

/*
** Creates not detached copy of sub-string, which starts at @offset position
** with maximum lenght @len.
*/
t_string		str_substr_cstr(const char *cstr, size_t offset, size_t len); // [OK]

/*
** Returns position of first appearence of @substr from
** position @offset in @n symbols maximum.
** If @substr string doesn't appears at @str string, then returns STR_NPOS.
*/
size_t			str_find_str(const t_string *str, const t_string *substr,
				size_t offset, size_t n); // [OK]

/*
** Returns position of first appearence of @substr from
** position @offset in @n symbols maximum.
** If @substr c-string doesn't appears at @str string, then returns STR_NPOS.
*/
size_t			str_find_cstr(const t_string *str, const char *substr,
				size_t offset, size_t n); // [OK]

/*
** Returns position of first appearence of symbol @c from
** position @offset in @n symbols maximum.
** If character @c doesn't appears at @str string, then returns STR_NPOS.
*/
size_t			str_find_ch(const t_string *str, int c,
				size_t offset, size_t n); // [OK]

/*
** Appends string @appendix to the end of string @str.
** If @str string isn't detached, detachs it and allocating memory
** for it.
**
** Returns error code.
*/
unsigned		str_append_str(t_string *str, const t_string *appendix); // [OK]

/*
** Appends string @appendix to the end of string @str.
** If @str string isn't detached, detachs it and allocating memory
** for it.
**
** Returns error code.
*/
unsigned		str_append_cstr(t_string *str, const char *appendix); // [OK]

/*
** Inserts string @ins to string @str to position @pos
**
** Returns error code.
*/
unsigned		str_insert_str(t_string *str, const t_string *ins, size_t pos); // [OK]

/*
** Inserts c-string @ins to string @str to position @pos.
**
** Returns error code.
*/
unsigned		str_insert_cstr(t_string *str, const char *ins, size_t pos); // [OK]

/*
** Erases substring with position @offset and lenght @len from string @str.
**
** Returns error code.
*/
unsigned		str_erase(t_string *str, size_t offset, size_t len); // [OK]

/*
** Replaces substr with position @offset and lenght @len with string @portion.
**
** Returns error code.
*/
unsigned		str_replace_str(t_string *str, const t_string *portion,
				size_t pos, size_t len); // [OK]

/*
** Replaces substr with position @offset and lenght @len with c-str @portion.
**
** Returns error code.
*/
unsigned		str_replace_cstr(t_string *str, const char *portion,
				size_t pos, size_t len); // [OK]

/*
** Calls function @callback to each character at substring with offset
** @offset and maximum lenght @len.
**
** Gives  to callback each character as @c and it's index as @i,
** and replace it with it's retuning value.
*/
void			str_map(t_string *str, size_t offset, size_t len,
				char (*callback)(char c, size_t i));

/*
** Calls function @callback to each character at substring with offset
** @offset and maximum lenght @len.
**
** Summarizes every returned value from @callback call with character @c
** and index @i as parametrs.
*/
ssize_t			str_count_if(t_string *str, size_t offset, size_t len,
				ssize_t (*callback)(char c, size_t i));

/*
** Writes string to a file-descriptor @fd.
** Returns result of call write(2).
*/
ssize_t			str_write_fd(const t_string *str, int fd); // [OK]

#endif
