/*
   Copyright (c) 2018, MariaDB Corporation.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301  USA */


#ifndef LEX_STRING_INCLUDED
#define LEX_STRING_INCLUDED

typedef struct st_mysql_const_lex_string LEX_CSTRING;

/* Functions to compare if two lex strings are equal */
static inline bool lex_string_cmp(CHARSET_INFO *charset, const LEX_CSTRING *a,
                                  const LEX_CSTRING *b)
{
  return my_strcasecmp(charset, a->str, b->str);
}

/*
  Compare to LEX_CSTRING's and return 0 if equal
*/
static inline bool cmp(const LEX_CSTRING *a, const LEX_CSTRING *b)
{
  return (a->length != b->length ||
          memcmp(a->str, b->str, a->length));
}

/*
  Compare if two LEX_CSTRING are equal. Assumption is that
  character set is ASCII (like for plugin names)
*/
static inline bool lex_string_eq(const LEX_CSTRING *a, const LEX_CSTRING *b)
{
  if (a->length != b->length)
    return 0;                                   /* Different */
  return strcasecmp(a->str, b->str) == 0;
}

/*
  Compare if two LEX_CSTRING are equal in system character set
  (field names, user variables, etc - but *not* table names)
*/
static inline bool lex_string_syseq(const LEX_CSTRING *a, const LEX_CSTRING *b)
{
  return lex_string_cmp(system_charset_info, a, b) == 0;
}

#endif /* LEX_STRING_INCLUDED */
