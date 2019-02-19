/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_log_restart.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 12:23:46 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/18 16:21:28 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool		scop_log_restart(void)
{
	FILE	*file;
	time_t	now;
	char	*date;

	file = fopen(LOG_FILENAME, "w");
	if (!file)
	{
		fprintf(stderr,
				"ERROR: could not open LOG_FILENAME log file %s for writing\n",
				LOG_FILENAME);
		return (false);
	}
	now = time(NULL);
	date = ctime(&now);
	fprintf(file, "LOG_FILENAME log. local time %s\n", date);
	fclose(file);
	return (true);
}
