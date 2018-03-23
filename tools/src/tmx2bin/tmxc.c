
#include "tmxc.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "malloc.h"

#include "SDL2/SDL.h"

/// File length
static int file_length;
/// Content as string
static char* file_content;

/// Calculate length of the file
/// < f File
static void calculate_length(FILE* f)
{
    int len = 0;
    char c;
    while ((c = fgetc(f)) != EOF) 
    {
        len ++;
    }
    rewind(f);
    file_length = len;
}

/// Create content
/// < f File
/// > 0 on success, 1 otherwise
static int create_content(FILE* f)
{
    // Allocate memory for the file content
    file_content = (char*)malloc(file_length * sizeof(char));
    if(file_content == NULL)
    {
        printf("Memory allocation error!\n");
        return 1;
    }

    // Store characters
    int p = 0;
    char c;
    while ((c = fgetc(f)) != EOF) 
    {
        file_content[p] = c;
        p ++;
    }
    rewind(f);

    return 0;
}

/// Get layer count
/// > Layer count
static int get_layer_count()
{
    // These WLEN things are actually quite useless
    const int WLEN = 3;
    int count = 0;

    char * s = file_content;

    int i = 0;
    for(; i < file_length - WLEN; i++)
    {
        if(
            s[i] == '/' && s[i+1] == 'l' && s[i+2] == 'a'
        )
        {
            count ++;
        }
    }

    return count;
}

/// Get numeric value between " "
/// < start Start pos
static int get_value(int start)
{
    char num[8];
    int n = 0;
    for(; n < 8; n++) num[n] = '\0';
    int i = start;
    int p = 0;
    for(; i < file_length && file_content[i] != '"'; i++)
    {
        num[p] = file_content[i];
        p ++;
    }
    return strtol(num,NULL,10);
}

/// Get tilemap dimensions, in tiles
/// < w Where width is stored
/// < h Where height is stored
static void get_dimensions(int* w, int* h)
{
    const int WLEN = 3;
    int count = 0;

    char * s = file_content;

    int i = 0;
    for(; i < file_length - WLEN; i++)
    {
        if(
         (count == 0 && ( s[i] == 't' && s[i+1] == 'h' && s[i+2] == '='))
        ||
         ( s[i] == 'h' && s[i+1] == 't' && s[i+2] == '=')
        )
        {
            if(count == 1)
            {
                *h = get_value(i+4);
                break;
            }
            else
            {
                *w = get_value(i+4);
            }
            count ++;
        }
    }

}

/// Get tile dimensions
/// TODO: Repeating code, replace with something better
/// < w Where width is stored
/// < h Where height is stored
static void get_tile_dimensions(int* w, int* h)
{
    const int WLEN = 3;
    int count = 0;

    char * s = file_content;

    int i = 0;
    for(; i < file_length - WLEN; i++)
    {
        if(
         (count == 0 && ( s[i] == 'e' && s[i+1] == 'w' && s[i+2] == 'i'))
        ||
         ( s[i] == 'e' && s[i+1] == 'h' && s[i+2] == 'e')
        )
        {
            if(count == 1)
            {
                *h = get_value(i+9);
                break;
            }
            else
            {
                *w = get_value(i+8);
            }
            count ++;
        }
    }

}

/// Parse CSV data to a layer data
/// < layer Layer
/// < start Start position in the file content
/// > End position
static int parse_CSV(int* layer, int start)
{
    char* s = file_content;
    int i = start;
    int p = 0;
    char buf[10];
    int bp = 0;

    for(; i < file_length && s[i] != '<'; i++)
    {
        if(s[i] != ',')
        {
            if(s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
            {
                buf[bp] = s[i];
                bp ++;
            }
        }
        else
        {
            if(bp > 0)
            {
                buf[bp] = '\0';
                
                layer[p] = (int)strtol(buf,NULL,10);
                p ++;
            }
            bp = 0;
        }
    }
    layer[p] = (int)strtol(buf,NULL,10);

    return i;
}

/// Parse layers
/// < layers Layers
static void parse_layers(LAYER* layers)
{
    const int WLEN = 3;
    int count = 0;

    char * s = file_content;

    int i = 0;
    for(; i < file_length - WLEN; i++)
    {
        if( s[i] == 'v' && s[i+1] == '"' && s[i+2] == '>')
        {
            i = parse_CSV(layers[count],i+3);
            count ++;
        }
    }
}

/// Load a tilemap from a file
TILEMAP* load_tilemap(const char* path)
{
    // Allocate memory for the map
    TILEMAP* t = (TILEMAP*)malloc(sizeof(TILEMAP));
    if(t == NULL)
    {
        printf("Memory allocation error!\n");
        return NULL;
    }
    // Open file
    FILE * f = fopen(path,"r");
    if(f == NULL)
    {
        printf("Failed to load a tilemap in %s!",path);
        return NULL;
    }

    // Calculate length
    calculate_length(f);
    // Create content
    if(create_content(f) != 0)
    {
        return NULL;
    }
    // Close file
    fclose(f);

    // Count layers
    t->layerCount = get_layer_count();
   
    // Get dimensions
    get_dimensions(&t->width,&t->height);
    get_tile_dimensions(&t->tileW,&t->tileH);
   
    // Calculate size in pixels
    t->pwidth = t->width * t->tileW;
    t->pheight = t->height * t->tileH;
    // Set tile count
    t->tcount = t->width * t->height;

    // Allocate memory for the layers
    t->layers = (LAYER*)malloc(sizeof(LAYER) * t->layerCount);
    if(t->layers == NULL)
    {
        printf("Memory allocation error!\n");
        return NULL;
    }
    int i = 0;
    for(; i < t->layerCount; i++)
    {
        t->layers[i] = (LAYER)malloc(sizeof(int) * t->width * t->height);
        if(t->layers[i] == NULL)
        {
            free(t->layers);
            printf("Memory allocation error!\n");
            return NULL;
        }
    }
    // Parse layers
    parse_layers(t->layers);

    // Free memory & set globals to their default values
    free(file_content);
    file_length = 0;

    return t;
}

/// Destroy a tilemap
void destroy_tilemap(TILEMAP* t)
{
    if(t == NULL) return;

    // Free layers
    int i = 0;
    for(; i < t->layerCount; i++)
    {
        free(t->layers[i]);
    }
    free(t);
}
