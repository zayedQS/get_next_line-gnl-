#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(void)
{
    int     fd;
    char    *line;

    // 1. فتح الملف لقراءته
    fd = open("test.txt", O_RDONLY);

    // 2. قراءة الملف سطرًا سطرًا
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line); // تحرير الذاكرة ضروري جداً
    }

    // 3. إغلاق الملف
    close(fd);
    return (0);
}