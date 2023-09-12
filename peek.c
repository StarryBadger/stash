#include "headers.h"
struct dirent **namelist;
off_t total_block_size = 0;
void totalBlockSize(char *path, const char *filename)
{
    char temp[PATH_MAX];
    strcpy(temp, path);
    if (temp[strlen(temp) - 1] != '/')
        strcat(temp, "/");
    strcat(temp, filename);
    struct stat statInfo;
    if (lstat(temp, &statInfo) == -1)
    {
        perror("lstat");
        return;
    }
    total_block_size += statInfo.st_blocks;
}
void peekL(char *path, const char *filename)
{
    char temp[PATH_MAX];
    strcpy(temp, path);
    if (temp[strlen(temp) - 1] != '/')
        strcat(temp, "/");

    strcat(temp, filename);

    struct stat statInfo;
    if (lstat(temp, &statInfo) == -1)
    {
        perror("lstat");
        return;
    }
    struct passwd *userInfo = getpwuid(statInfo.st_uid);
    struct group *grInfo = getgrgid(statInfo.st_gid);

    printf("%s", (S_ISDIR(statInfo.st_mode)) ? "d" : "-");
    printf((statInfo.st_mode & S_IRUSR) ? "r" : "-");
    printf((statInfo.st_mode & S_IWUSR) ? "w" : "-");
    printf((statInfo.st_mode & S_IXUSR) ? "x" : "-");
    printf((statInfo.st_mode & S_IRGRP) ? "r" : "-");
    printf((statInfo.st_mode & S_IWGRP) ? "w" : "-");
    printf((statInfo.st_mode & S_IXGRP) ? "x" : "-");
    printf((statInfo.st_mode & S_IROTH) ? "r" : "-");
    printf((statInfo.st_mode & S_IWOTH) ? "w" : "-");
    printf((statInfo.st_mode & S_IXOTH) ? "x" : "-");
    printf(" %2lu ", statInfo.st_nlink);
    printf("%s %s ", userInfo->pw_name, grInfo->gr_name);
    printf("%8lld ", (long long)statInfo.st_size);
    time_t currentTime = time(NULL);
    struct tm *fileTime = localtime(&statInfo.st_mtime);
    struct tm *currentTimeStruct = localtime(&currentTime);
    int monthDifference = (currentTimeStruct->tm_year - fileTime->tm_year) * 12 + currentTimeStruct->tm_mon - fileTime->tm_mon;
    char timestr[50];
    if (monthDifference > 6)
    {
        strftime(timestr, sizeof(timestr), "%b %d %Y ", localtime(&statInfo.st_mtime));
    }
    else
    {
        strftime(timestr, sizeof(timestr), "%b %d %H:%M", localtime(&statInfo.st_mtime));
    }
    printf("%s ", timestr);

    if (S_ISDIR(statInfo.st_mode))
        printf(BLUE "%s" RESET, filename);
    else if (S_IXUSR & statInfo.st_mode)
        printf(GREEN "%s" RESET, filename);
    else
        printf(WHITE "%s" RESET, filename);
    printf("\n");
}
void peekJist(char *path, const char *filename)
{
    char temp[PATH_MAX];
    strcpy(temp, path);
    if (temp[strlen(temp) - 1] != '/')
        strcat(temp, "/");
    strcat(temp, filename);
    struct stat statInfo;
    if (lstat(temp, &statInfo) == -1)
    {
        perror("lstat");
        return;
    }
    if (S_ISDIR(statInfo.st_mode))
        printf(BLUE "%s" RESET, filename);
    else if (statInfo.st_mode & S_IXUSR)
        printf(GREEN "%s" RESET, filename);
    else
        printf(WHITE "%s" RESET, filename);
    printf("\t");
}
void setFlags(char *flags, bool *L, bool *A)
{
    if (equal(flags, "-l"))
    {
        *L = true;
    }
    else if (equal(flags, "-a"))
    {
        *A = true;
    }
    else if (equal(flags, "-al") || equal(flags, "-la"))
    {
        *A = true;
        *L = true;
    }
}
void peek(command cmd)
{
    total_block_size = 0;
    bool L = false, A = false;
    char path[PATH_MAX];
    if (cmd.argc == 1)
    {
        getcwd(path, PATH_MAX - 1);
    }
    else if (cmd.argc == 2)
    {
        setFlags(cmd.argv[1], &L, &A);
        if (!L & !A)
            mystrcpy(path, cmd.argv[1]);
        else
            getcwd(path, PATH_MAX - 1);
    }
    else if (cmd.argc == 3)
    {
        setFlags(cmd.argv[1], &L, &A);
        setFlags(cmd.argv[2], &L, &A);
        if ((!L & !A))
        {
        }
        else if ((L && !A) || (!L && A))
        {
            mystrcpy(path, cmd.argv[2]);
        }
        else
        {
            if (equal(cmd.argv[1], "-al") || equal(cmd.argv[1], "-la"))
            {
                mystrcpy(path, cmd.argv[2]);
            }
            else
            {
                getcwd(path, PATH_MAX - 1);
            }
        }
    }
    else if (cmd.argc == 4)
    {
        setFlags(cmd.argv[1], &L, &A);
        setFlags(cmd.argv[2], &L, &A);
        mystrcpy(path, cmd.argv[3]);
    }
    else
    {
        fprintf(stderr, "\x1b[31mpeek: Too many arguments\n\x1b[0m");
        return;
    }
    if (prefix("~", path))
    {
        mystrcpy(path, replaceTildeWithHome(path));
    }
    DIR *directory = opendir(path);
    if (!directory)
    {
        fprintf(stderr, "\x1b[31m%s is not a valid directory/flag\n\x1b[0m", path);
        return;
    }
    int n = scandir(path, &namelist, 0, alphasort);
    if (n < 0)
    {
        fprintf(stderr, "\x1b[31mpeek: Could not scan directory\n\x1b[0m");
    }
    int maxLength = 0;
    for (int i = 0; i < n; i++)
    {
        if (length(namelist[i]->d_name) > maxLength)
            maxLength = length(namelist[i]->d_name);
    }
    if (L)
    {
        for (int i = 0; i < n; ++i)
        {
            if (!A && prefix(".", namelist[i]->d_name))
                continue;
            totalBlockSize(path, namelist[i]->d_name);
        }
        printf("total %4lu\n", total_block_size);
    }
    for (int i = 0; i < n; ++i)
    {
        if (!A && prefix(".", namelist[i]->d_name))
            continue;
        if (L)
        {
            peekL(path, namelist[i]->d_name);
        }
        else
        {
            peekJist(path, namelist[i]->d_name);
        }

        free(namelist[i]);
    }
    if (!L)
    {
        printf("\n");
    }
    free(namelist);
}
