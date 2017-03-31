#ifndef PRINTING_H_
#define PRINTING_H_

#include <stdbool.h>

#define CLEAR		"\e[0m"

#define STR_BLACK	"\e[0;30m"
#define STR_RED		"\e[0;31m"
#define STR_GREEN	"\e[0;32m"
#define STR_YELLOW	"\e[0;33m"
#define STR_BLUE	"\e[0;34m"
#define STR_PURPLE	"\e[0;35m"
#define STR_CYAN	"\e[0;36m"
#define STR_WHITE	"\e[0;37m"

#define STR_BLACK_BOLD	"\e[1;30m"
#define STR_RED_BOLD	"\e[1;31m"
#define STR_GREEN_BOLD	"\e[1;32m"
#define STR_YELLOW_BOLD	"\e[1;33m"
#define STR_BLUE_BOLD	"\e[1;34m"
#define STR_PURPLE_BOLD	"\e[1;35m"
#define STR_CYAN_BOLD	"\e[1;36m"
#define STR_WHITE_BOLD	"\e[1;37m"

enum e_lcolor
  {
    RED = 0,
    GREEN,
    YELLOW,
    BLUE,
    PURPLE,
    CYAN,
    WHITE,
    BLACK_BOLD,
    RED_BOLD,
    GREEN_BOLD,
    YELLOW_BOLD,
    BLUE_BOLD,
    PURPLE_BOLD,
    CYAN_BOLD,
    WHITE_BOLD,
    NB_COLOR
  };

typedef enum e_lcolor e_color;

struct			s_listteam
{
  bool			used;
  int			team_id;
  char			symb;
  e_color		color;
  struct s_listteam	*next;
};

typedef struct s_listteam t_listteam;

t_listteam	*print_map(int *map, t_listteam *list, char *color[NB_COLOR]);

#endif /* !PRINTING_H_ */
