/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_log_restart.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 12:23:46 by fmessina          #+#    #+#             */
/*   Updated: 2019/06/24 11:34:23 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool		scop_log_restart(void)
{
	FILE	*file;
	time_t	now;
	char	*date;

	file = fopen(SCOP_LOG_FILENAME, "w");
	if (!file)
	{
		fprintf(stderr,
				"ERROR: could not open SCOP_LOG_FILENAME log file %s for writing\n",
				SCOP_LOG_FILENAME);
		return (false);
	}
	now = time(NULL);
	date = ctime(&now);
	fprintf(file, "SCOP_LOG_FILENAME log. local time %s\n", date);
	fclose(file);
	return (true);
}
