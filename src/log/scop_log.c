/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_log.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 11:46:44 by fmessina          #+#    #+#             */
/*   Updated: 2019/02/18 16:20:26 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool		scop_log(const char *message, ...)
{
	FILE	*file;
	va_list	argptr;

	file = fopen(LOG_FILENAME, "a");
	if (!file)
	{
		fprintf(
			stderr,
			"ERROR: could not open LOG_FILENAME %s file for appending\n",
			LOG_FILENAME);
		return (false);
	}
	va_start(argptr, message);
	vfprintf(file, message, argptr);
	va_end(argptr);
	fclose(file);
	return (true);
}

bool		scop_log_err(const char *message, ...)
{
	FILE	*file;
	va_list	argptr;

	file = fopen(LOG_FILENAME, "a");
	if (!file)
	{
		fprintf(stderr,
				"ERROR: could not open LOG_FILENAME %s file for appending\n",
				LOG_FILENAME);
		return (false);
	}
	va_start(argptr, message);
	vfprintf(file, message, argptr);
	va_end(argptr);
	va_start(argptr, message);
	vfprintf(stderr, message, argptr);
	va_end(argptr);
	fclose(file);
	return (true);
}
