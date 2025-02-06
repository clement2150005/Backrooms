/*==================================================================//
// 		 ____			  _								  			//
// 		|  _ \		  	 | |								 		//
// 		| |_) | __ _  ___| | ___ __ ___   ___  _ __ ___  ___ 		//
// 		|  _ < / _` |/ __| |/ | '__/ _ \ / _ \| '_ ` _ \/ __|		//
// 		| |_) | (_| | (__|   <| | | (_) | (_) | | | | | \__ \		//
// 		|____/ \__,_|\___|_|\_|_|  \___/ \___/|_| |_| |_|___/		//
//																	//
//			Author:   Clement Colin									//
//			Created:  February 6, 2025								//
//==================================================================*/

#include <backrooms.h>

void	first_time_chapter_called(t_game *game, int *first, int *running, int *i)
{
	(void)game;
	(void)*running;
	(void)*i;
	*first = FALSE;
}

void	chapter_1(t_game *game, int *i, int *running)
{
	static int	first = TRUE;
	int			chapter_end;

	chapter_end = FALSE;
	if (first)
		first_time_chapter_called(game, &first, running, i);
	if (chapter_end)
		(*i)++;
}

void	chapter_2(t_game *game, int *i, int *running)
{
	static int	first = TRUE;
	int			chapter_end;

	chapter_end = FALSE;
	first_time_chapter_called(game, &first, running, i);
	if (chapter_end)
		(*i)++;
}

void	chapter_3(t_game *game, int *i, int *running)
{
	static int	first = TRUE;
	int			chapter_end;

	chapter_end = FALSE;
	first_time_chapter_called(game, &first, running, i);
	if (chapter_end)
		(*i)++;
}

void	chapter_4(t_game *game, int *i, int *running)
{
	static int	first = TRUE;
	int			chapter_end;

	chapter_end = FALSE;
	first_time_chapter_called(game, &first, running, i);
	if (chapter_end)
		(*i)++;
}

void	chapter_5(t_game *game, int *i, int *running)
{
	static int	first = TRUE;
	int			chapter_end;

	chapter_end = FALSE;
	first_time_chapter_called(game, &first, running, i);
	if (chapter_end)
		*running = FALSE;
}
