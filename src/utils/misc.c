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

char	*strjoin(const char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*result;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (strdup(s2));
	if (!s2)
		return (strdup(s1));
	len1 = strlen(s1);
	len2 = strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (!result)
	{
		fprintf(stderr, "ERROR: memory allocation failed in strjoin");
		exit(EXIT_FAILURE);
	}
	result[len1 + len2] = '\0';
	strcpy(result, s1);
	strcat(result, s2);
	return (result);
}
