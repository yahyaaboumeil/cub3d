#include "parsing.h"

bool	check_file(char *file)
{
	char	*pos;

	pos = ft_strnstr(file, ".cub", ft_strlen(file));
	if (pos == NULL)
		return (false);
	if (file == pos)
		return (false);
	if (ft_strncmp(".cub", pos, ft_strlen(pos)))
		return (false);
	return (true);
}
