/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 17:42:21 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/27 14:47:32 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIEWER_H
# define VIEWER_H

# include <libc.h>
# include <locale.h>
# include <ncurses.h>
# include <pthread.h>
# include "libft.h"
# include "corewar.h"
# include "ressources.h"

# define KEY_FPS_LL 'p'
# define KEY_FPS_PP 'o'
# define KEY_LPF_LL 'k'
# define KEY_LPF_PP 'l'
# define KEY_PROCESS_LL 'i'
# define KEY_PROCESS_PP 'j'
# define KEY_PAUSE ' '
# define KEY_QUIT 'q'

# define FLAG_EVENT_CORE 1
# define FLAG_EVENT_TIMER 2
# define FLAG_EVENT_PAUSE 4
# define FLAG_EVENT_QUIT 8

# define FLAG_KEY_EVENT_FPS 16
# define FLAG_KEY_EVENT_LPF 32
# define FLAG_KEY_EVENT_PAUSE 64
# define FLAG_KEY_EVENT_PROCESS 256

# define LIFE_DEAD 0
# define LIFE_LOW 25
# define LIFE_MEDIUM 50
# define LIFE_HIGH 75
# define LIFE_FULL 100

# define ONOFF(x) ((x) ? "ON" : "OFF")
# define PRINT_CARRY (CARRY ? 'C' : ' ')
# define PRINT_LIVE (LIVE ? 'L' : ' ')

# define COLOR_FG(x) (COLOR_PAIR(((x) % 4) + 2))
# define COLOR_BG(x) (COLOR_PAIR(((x) % 4) + 9))

# define CHAMP_L 8
# define CHAMP_C ((4 < (MAX_PLAYERS)) ? (68 / 4) : (68 / MAX_PLAYERS))
# define TITLE_L 12
# define TITLE_C 68
# define ARENA_L (LINES - CHAMP_L)
# define ARENA_C (COLS - TITLE_C)
# if REG_NUMBER % 2
#  define REGIS_L (REG_NUMBER + 2)
# else
#  define REGIS_L (REG_NUMBER + 1)
# endif
# define REGIS_C 68
# define PROCS_L (LINES - (REGIS_L + CHAMP_L + TITLE_L))
# define PROCS_C 68
# define INFOS_L (CHAMP_L)
# define INFOS_C (COLS - TITLE_C)

# define ARENA_NAME "ARENA"
# define TITLE_NAME "TITLE"
# define REGIS_NAME "REGISTER"
# define PROCS_NAME "PROCESSUS"
# define INFOS_NAME "INFOS"

typedef struct s_vm			t_vm;

typedef struct s_process	t_process;

typedef struct		s_viewer
{
	unsigned char	arena[MEM_SIZE];
	char			owner[MEM_SIZE];
	int				arena_flags[MEM_SIZE];
	WINDOW			*win_arena;
	WINDOW			*win_arena_box;
	WINDOW			*win_title;
	WINDOW			*win_title_box;
	WINDOW			*win_champions[MAX_PLAYERS];
	WINDOW			*win_champions_box[MAX_PLAYERS];
	WINDOW			*win_processes;
	WINDOW			*win_processes_box;
	WINDOW			*win_register;
	WINDOW			*win_register_box;
	WINDOW			*win_infos;
	WINDOW			*win_infos_box;
	int				process_selected;
	int				process_offset;
	char			anim_state[MAX_PLAYERS];
	int				fps;
	int				lpf;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	pthread_t		th_core;
	pthread_t		th_render;
	pthread_t		th_input;
	pthread_t		th_timer;
	pthread_t		th_anim[MAX_PLAYERS];
	int				event_flags;
	int				heal_flag[MAX_PLAYERS];
	int				credits_flag;
	t_vm			*vm;
}					t_viewer;

typedef struct		s_anim
{
	t_viewer		*v;
	int				i;
}					t_anim;

/*
** vw_draw_life.c
*/
void				draw_life_full(t_viewer *v, int i);
void				draw_life_high(t_viewer *v, int i);
void				draw_life_medium(t_viewer *v, int i);
void				draw_life_low(t_viewer *v, int i);

/*
** vw_draw_img.c
*/
void				draw_skull(t_viewer *v, int i);
void				draw_laurels(t_viewer *v, int i);
void				draw_cup(t_viewer *v, int i);
void				draw_logo(t_viewer *v);

/*
** vw_draw_tools.c
*/
void				heal(t_viewer *v, int i);
void				maj_lifes(t_viewer *v);
void				show_credits(t_viewer *v);

/*
** vw_init_win.c
*/
void				create_newwin(int arg[4], char *title,
						WINDOW **win_content, WINDOW **win_box);
void				init_infos(t_viewer *v);
void				init_arena(t_viewer *v);
void				init_register(t_viewer *v);

/*
** vw_init.c
*/
void				viewer_init(t_viewer *v, t_vm *vm);
void				viewer_run(t_viewer *v);
void				viewer_free(t_viewer *v);

/*
** vw_maj_process.c
*/
void				maj_process(t_viewer *v);

/*
** vw_maj_win.c
*/
void				maj_register(t_viewer *v, t_process *process);
void				maj_arena(t_viewer *v);
void				maj_infos_input(t_viewer *v);
void				maj_infos_cycle(t_viewer *v);

/*
** vw_th_anim.c
*/
void				*th_anim_routine(void *p_data);

/*
** vw_th_core.c
*/
void				*th_core_routine(void *p_data);

/*
** vw_th_input.c
*/
void				*th_input_routine(void *p_data);

/*
** vw_th_render.c
*/
void				*th_render_routine(void *p_data);

/*
** vw_th_timer.c
*/
void				*th_timer_routine(void *p_data);

#endif
