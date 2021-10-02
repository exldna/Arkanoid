# include "level.h"

extern LevelSize LEVEL_BUFFER_SIZE;
extern size_t LEVEL_BUFFER_LEN;

extern Level level;


void init_level ()
{
    level = malloc (LEVEL_BUFFER_LEN);
}


void load_level (size_t i)
{
    // config path
    string level_config_path = malloc (
        strlen (RESOURCE_DIR LEVEL_CONFIG_FILE_PREFIX LEVEL_CONFIG_FILE_TYPE) + 3
    );

    sprintf (level_config_path, "%s%s%zd%s",
        RESOURCE_DIR, 
        LEVEL_CONFIG_FILE_PREFIX, 
        i,
        LEVEL_CONFIG_FILE_TYPE
    );

    // open config file
    FILE* level_config;
    level_config = fopen (level_config_path, "r");

    if (level_config == NULL)
    {
        error_exit ("Load level", "Failed to open file");
    }

    // configure level
    char curr = ' ';
    size_t pos = 0;

    while ((curr = fgetc (level_config)) != EOF)
    {
        if (curr == '\n')
        {
            continue;
        }

        switch (curr)
        {
            case '#':
                level[pos] = wall;
                break;
            case '0':
                level[pos] = block_0;
                break;
            case '1':
                level[pos] = block_1;
                break;
            case '2':
                level[pos] = block_2;
                break;
            default:
                level[pos] = space;
        };

        ++pos;
    }

    // close operation
    fclose (level_config);
    free (level_config_path);
}


void break_block (size_t i)
{
    switch (level[i])
    {
        case block_2:
            level[i] = block_1;
            break;
        case block_1:
            level[i] = block_0;
            break;
        case block_0:
            level[i] = space;
            break;
    }
}


bool check_cell (size_t i)
{
    return level[i] != space;
}