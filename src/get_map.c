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

char	*get_path(int i)
{
	char	*prefix;
	char	suffix[2];
	char	*path;

	prefix = "./assets/maps/map.";
	suffix[0] = i + '0';
	suffix[1] = '\0';
 	path = strjoin(prefix, suffix);
	return (path);
}

void copy_old_map(char **new_map, char **old_map) {
	int i = 0;
	while (old_map[i]) {
		new_map[i] = strdup(old_map[i]);
		i++;
	}
	new_map[i] = NULL;
}

int expand_map_capacity(char ***map, int *map_capacity) {
	int new_capacity = (*map_capacity) * 2;
	char **new_map = calloc(new_capacity + 1, sizeof(char *));
	if (!new_map) {
		return -1;
	}

	if (*map) {
		copy_old_map(new_map, *map);
		free(*map);
	}

	*map_capacity = new_capacity;
	*map = new_map;
	return 0;
}

char **get_map(char *path) 
{
	char	**map;
	char	*line;
	int		map_capacity = 2;
	int		map_size = 0;
	int		fd = open(path, O_RDONLY);

	if (fd == -1) {
		perror("Error opening map file");
		return (NULL);
	}
	map = malloc(sizeof(char *) * (map_capacity + 1));
	if (!map) {
		close(fd);
		return (NULL);
	}
	line = get_next_line(fd);
	while (line) {
		if (line[strlen(line) - 1] == '\n')
			line[strlen(line) - 1] = '\0';
		if (map_size >= map_capacity) {
			if (expand_map_capacity(&map, &map_capacity) == -1) {
				free(line);
				break ;
			}
		}
		map[map_size] = strdup(line);
		free(line);
		map_size++;
		line = get_next_line(fd);
	}
	map[map_size] = NULL;
	close(fd);
	return (map);
}
