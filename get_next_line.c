#include "get_next_line.h"

char	*extract_line(char *stash)
{
    int		line_length;
    char	*line;

    line_length = 0;
    if (!stash)
        return (NULL);
    while (stash[line_length] && stash[line_length] != '\n')
        line_length++;
    if (stash[line_length] == '\n')
        line_length++;
    line = ft_substr(stash, 0, line_length);
    if (!line)
        return (NULL);
    return (line);
}

 char *get_next_line(int fd)
 {
    static char	*stash = NULL;
    char		*line;
    char		*buffer;
    ssize_t		nbytes;
    char		*temp;

    line = NULL;
    nbytes = 1;
    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
        return (NULL);
    buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
    if (!buffer)
        return (NULL);
    while (nbytes > 0)
    {
        nbytes = read(fd, buffer, BUFFER_SIZE);
        if (nbytes == -1)
        {
            free(buffer);
            free(stash);
            return (NULL);
        }
        if (nbytes == 0)
            break ;
        buffer[nbytes] = '\0';
        temp = stash;
        stash = ft_strjoin(stash, buffer);
        free(temp);
        if (ft_strchr(buffer, '\n'))
            break ;
    }
    free(buffer);
    if (!stash)
        return (NULL);
    line = extract_line(stash);
    if (!line)
        return (NULL);
    temp = ft_substr(stash, ft_strlen(line), ft_strlen(stash) - ft_strlen(line));
    free(stash);
    stash = temp;
    return (line);
}

int	main(void)
{
    int	fd;

    fd = open("text.txt", O_CREAT | O_RDONLY);
    if (fd < 0)
    {
        perror("Failed to open file");
        return (1);
    }
    printf("fd = %d\n", fd);
    printf("%s", get_next_line(fd));  // Read first line
    printf("%s", get_next_line(fd));  // Read second line
    printf("%s", get_next_line(fd));  // Read third line (etc.)
    close(fd);
    return (0);
}
