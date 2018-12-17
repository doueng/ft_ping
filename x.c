
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	x_int(int res, char *file, int line)
{
  if (res == -1)
    {
      fprintf(stderr, "Error (%s, %d): %s\n",
	      file, line, strerror(errno));
      exit (1);
    }
  return (res);
}

void	*x_void(void *res, char *file, int line)
{
	if (res == NULL)
    {
      fprintf(stderr, "Error (%s, %d): %s\n",
	      file, line, strerror(errno));
      exit (1);
    }
  return (res);
}
