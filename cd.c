#include <assert.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Tremendo codigo spaguitti aka clon de cd
 * con registros para guardar directorios */

enum Opts
{
    NORMAL = 0, // also false
    MEM1   = 1,
    MEM2   = 2,
    MEM3   = 3,
    MEM4   = 4,
    MEM5   = 5,
    HOME   = 6,
    SAVE   = 8, // use 4rd bit
};

static char  registers[5][PATH_MAX];
static FILE *file;
#define REGFILE "/home/hugo/.local/share/cd/registers"

struct DirOpts
{
    enum Opts opts;
    char      dir[PATH_MAX];
};

void
load_registers()
{
    file = fopen(REGFILE, "r+");
    assert(file);
    for (int i = 0; i < 5; i++)
        fgets(registers[i], PATH_MAX, file);
}

void
store_registers()
{
    rewind(file);
    for (int i = 0; i < 5; i++)
        fprintf(file, "%s\n", registers[i]);
    fclose(file);
}

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
            }
            else
                fprintf(stderr, "Invalid args\n");

            break;

        default:
            fprintf(stderr, "Invalid args\n");
            break;
    }
    return opts;
}

int
cd(struct DirOpts opts)
{
    char dir[PATH_MAX];
    if (opts.opts & HOME)
    {
        char *homepath = getenv("HOME");
        chdir(homepath);
        printf("%s", homepath);
    }

    else if (opts.opts == NORMAL)
    {
        if (*opts.dir == '/')
        {
            chdir(opts.dir);
            printf("%s", opts.dir);
        }

        else
        {
            getcwd(dir, PATH_MAX);
            strcat(dir, "/");
            strcat(dir, opts.dir);
            chdir(dir);
            printf("%s", dir);
        }
    }

    else if (opts.opts & SAVE)
    {
        switch (opts.opts & 0x7)
        {
            case MEM1:
                chdir(opts.dir);
                strcpy(registers[0], getcwd(dir, PATH_MAX));
                break;
            case MEM2:
                chdir(opts.dir);
                strcpy(registers[0], getcwd(dir, PATH_MAX));
                break;
            case MEM3:
                chdir(opts.dir);
                strcpy(registers[0], getcwd(dir, PATH_MAX));
                break;
            case MEM4:
                chdir(opts.dir);
                strcpy(registers[0], getcwd(dir, PATH_MAX));
                break;
            case MEM5:
                chdir(opts.dir);
                strcpy(registers[0], getcwd(dir, PATH_MAX));
                break;
        }
    }

    else
    {
        switch (opts.opts & 0x7)
        {
            case MEM1:
            case MEM2:
            case MEM3:
            case MEM4:
            case MEM5:
                chdir(registers[(opts.opts & 0x7) - MEM1]);
                printf("%s", registers[(opts.opts & 0x7) - MEM1]);
                break;
        }
    }

    return 0;
}

int
main(int argc, char *argv[])
{
    int ret;
    load_registers();
    ret = cd(get_opts(argc, argv));
    store_registers();
    return ret;
}
