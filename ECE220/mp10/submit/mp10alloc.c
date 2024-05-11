#include <stdint.h>
#include <stdlib.h>

#include "mp10.h"


vertex_set_t*
new_vertex_set ()
{
    vertex_set_t* tmp = (vertex_set_t*)malloc(sizeof(*tmp));
    if (tmp == NULL)
        return NULL;
    tmp->count = 0;
    tmp->id = NULL;
    tmp->id_array_size = 0;
    tmp->minimap = 0;
    return tmp;
}


void
free_vertex_set (vertex_set_t* vs)
{
    if (vs->id != NULL)
        free(vs->id);
    free(vs);
    return;
}


path_t*
new_path ()
{
    path_t* tmp = (path_t*)malloc(sizeof(*tmp));
    if (tmp == NULL)
        return NULL;
    tmp->id = NULL;
    tmp->minimap = 0;
    tmp->n_vertices = 0;
    tmp->tot_dist = 0;
    return tmp;
}


void
free_path (path_t* path)
{
    if (path->id != NULL)
        free(path->id);
    free(path);
    return;
}

