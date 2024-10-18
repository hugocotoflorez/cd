#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

enum Opts
{
    NORMAL = 0, // also false
    MEM1   = 1,
    MEM2   = 2,
    MEM3   = 3,
    MEM4   = 4,
    MEM5   = 5,
    HOME   = 6,
    SAVE   = 7, // use 3rd bit
};

struct DirOpts
{
    enum Opts opts;
    char      dir[PATH_MAX];
};

struct DirOpts
get_opts(int argc, char **argv)
{
    struct DirOpts opts = { 0 };
    switch (argc)
    {
        case 1:
            opts.opts = HOME;
            break;

        case 2:
            if (*argv[1] == '-')
                switch (argv[1][1])
                {
                    case '1':
                        opts.opts = MEM1;
                        break;
                    case '2':
                        opts.opts = MEM2;
                        break;
                    case '3':
                        opts.opts = MEM3;
                        break;
                    case '4':
                        opts.opts = MEM4;
                        break;
                    case '5':
                        opts.opts = MEM5;
                        break;
                }
            else
                strncpy(opts.dir, argv[1], PATH_MAX);

            break;

        case 3:
            if (*argv[1] == '-')
            {
                switch (argv[1][1])
                {
                    case '1':
                        opts.opts = MEM1;
                        break;
                    case '2':
                        opts.opts = MEM2;
                        break;
                    case '3':
                        opts.opts = MEM3;
                        break;
                    case '4':
                        opts.opts = MEM4;
                        break;
                    case '5':
                        opts.opts = MEM5;
                        break;
                }
                opts.opts |= SAVE;
                strncpy(opts.dir, argv[2], PATH_MAX);
                break;
            }

        default:
            fprintf(stderr, "Invalid args");
            break;
    }
    return opts;
}

int
cd(struct DirOpts opts)
{
    // chdir(path) -> 0 / -1 err
    // getcwd(buf, size)
    // char dir[PATH_MAX];
    // getcwd(dir, PATH_MAX);

    if (opts.opts & HOME)
    {
        char *homepath = getenv("HOME");
        chdir(homepath);
        printf("%s\n", homepath);
    }

    if (opts.opts == NORMAL)
    {
        if (*opts.dir == '/')
        {
            chdir(opts.dir);
            printf("%s\n", opts.dir);
        }

        else
        {
            char dir[PATH_MAX];
            getcwd(dir, PATH_MAX);
            strcat(dir, "/");
            strcat(dir, opts.dir);
            chdir(dir);
            printf("%s\n", dir);
        }
    }

    return 0;
}

int
main(int argc, char *argv[])
{
    return cd(get_opts(argc, argv));
}
