#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/wait.h>
#include <limits.h>
#include <errno.h>
#include <signal.h>
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>

int	*line_data(char *arv)
{
	int		i;
	int 	*data;

	i = -1;
    data = malloc(sizeof(int) * 6);
	data[0] = 0;
	data[1] = 0;
	data[2] = 0;
	data[3] = 0;
    data[4] = 0;
    data[5] = 0;
	while (arv[++i] != '\0')
	{
		if (arv[i] == '<')
			data[0]++;
        else if (arv[i] != ' ' && arv[i + 2] == '<')
            data[4]++;
		else if (arv[i] == '>')
			data[1]++;
        else if (arv[i] != ' ' && arv[i - 2] == '>')
            data[5]++;
		else if (arv[i] == '|')
			data[2]++;
        else if (arv[i] != ' ')
			data[3]++;
	}
    return (data);
}

int main(void)
{
    int *line;

    while (1)
    {
        char *test;

        test = readline("----->");
        line = line_data(test);
        printf("%d-----[<]\n", line[0]);
        printf("%d-----[>]\n", line[1]);
        printf("%d-----[|]\n", line[2]);
        printf("%d-----[cmd]\n", line[3]);
        printf("%d-----[f_in]\n", line[4]);
        printf("%d-----[f_out]\n", line[5]);
    } 
}
