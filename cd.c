#include <linux/limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

enum Opts
{
    NORMAL = 0,
    MEM1   = 1,
    MEM2   = 2,
    MEM3   = 3,
    MEM4   = 4,
    MEM5   = 5,
    SAVE   = 6,
    HOME   = 7,
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

        case 2:
            if (*argv[1] == '-')
                switch (argv[1][2])
                {
                    case '1':
                        opts.opts = MEM1;
                    case '2':
                        opts.opts = MEM2;
                    case '3':
                        opts.opts = MEM3;
                    case '4':
                        opts.opts = MEM4;
                    case '5':
                        opts.opts = MEM5;
                }
            else
            {
                strncpy(opts.dir, argv[1], PATH_MAX);
            }

        default:
            fprintf(stderr, "Invalid args");
    }

    return opts;
}

int
cd(enum Opts opts)
{
    // chdir(path) -> 0 / -1 err
    // getcwd(buf, size)
    char dir[PATH_MAX];
    getcwd(dir, PATH_MAX);
}

int
main(int argc, char *argv[])
{
    return cd(get_opts(argc, argv));
}
