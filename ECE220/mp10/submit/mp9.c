#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "mp5.h"
#include "mp10.h"

#define MY_INFINITY 1000000000

// Find the nodes in range of loc and push them into vs
// input: loc location and range information
//        vs point set
//        p, nnum pointer to the tree and the index of current node in the tree
// output: none
void find_nodes(locale_t *loc, vertex_set_t *vs, pyr_tree_t *p, int32_t nnum)
{
    // Do not modify the following line nor add anything above in the function.
    record_fn_call();
    int32_t bound = p->n_nodes;
    // judge if going into the leaves node
    if (nnum * 4 + 1 > bound)
    {
        if (in_range(loc, p->node[nnum].x, p->node[nnum].y_left))
        {
            if (vs->count == vs->id_array_size)
            {
                int32_t* new_ptr = NULL;
                if (!vs->id_array_size)
                {
                    new_ptr = malloc(64 * sizeof(*vs->id));
                    if (new_ptr)
                    {
                        vs->id = new_ptr;
                        vs->id_array_size = 64;
                    }
                }
                else
                {
                    new_ptr = realloc(vs->id, 2 * vs->id_array_size * sizeof (*vs->id));
                    if (new_ptr)
                    {
                        vs->id = new_ptr;
                        vs->id_array_size = 2 * vs->id_array_size;
                    }
                }
            }
            /* vs->id[vs->count++] = p->node[nnum].id; */
            for (int32_t i = 0; i < vs->count; ++i)
            {
                if (vs->id[i] >= p->node[nnum].id)
                {
                    vs->count++;
                    for (int32_t j = vs->count - 1; j > i; --j)
                        vs->id[j] = vs->id[j - 1];
                    vs->id[i] = p->node[nnum].id;
                    return;
                }
            }
            vs->id[vs->count++] = p->node[nnum].id;
        }
        return;
    }
    // judge if the circle is in each children
    if (loc->y - loc->range <= p->node[nnum].y_left && loc->x - loc->range <= p->node[nnum].x)
        find_nodes(loc, vs, p, 4 * nnum + 1);
    if (loc->y - loc->range <= p->node[nnum].y_right && loc->x + loc->range >= p->node[nnum].x)
        find_nodes(loc, vs, p, 4 * nnum + 2);
    if (loc->y + loc->range >= p->node[nnum].y_left && loc->x - loc->range <= p->node[nnum].x)
        find_nodes(loc, vs, p, 4 * nnum + 3);
    if (loc->y + loc->range >= p->node[nnum].y_right && loc->x + loc->range >= p->node[nnum].x)
        find_nodes(loc, vs, p, 4 * nnum + 4);
    return;
}

// Delete the nodes not in range of loc out from vs
// input: g pointer to the graph
//        vs points set
//        loc location and range information
// output: none
void trim_nodes(graph_t *g, vertex_set_t *vs, locale_t *loc)
{
    int32_t n = vs->count;
    // judge whether each element is in range
    for (int i = 0; i < n; ++i)
        if (!in_range(loc, g->vertex[vs->id[i]].x, g->vertex[vs->id[i]].y))
        {
            // swap the i-th element with the last element and delete the last element
            n--;
            int32_t tmp = vs->id[n];
            vs->id[n] = vs->id[i];
            vs->id[i] = tmp;
            vs->count--, i--;
        }
}


// Find the father node in heap
// input: p, refers to a node in heap
// output: father of p
int32_t findFa(int32_t p)
{
    return (p - 1) / 2;
}
// Compare the distance form sec of two vectex in the graph
// input: a, b two index of elements in g
//        g pointer to graph
// output: 1 if distance to a is less than distance to b
//         0 otherwise
int32_t compareDis(int32_t a, int32_t b, graph_t *g)
{
    return (g->vertex[a].from_src < g->vertex[b].from_src);
}
// Sawp two elemets in heap
// intput: a, b two element index in heap
//         h the pointer to the heap
// output: none
void swapInHeap(int32_t *a, int32_t *b, heap_t *h)
{
    int32_t tmp = h->elt[*b];
    h->elt[*b] = h->elt[*a];
    h->elt[*a] = tmp;
    tmp = *b;
    *b = *a;
    *a = tmp;
}
// Find the son of p with minimal distanece
// input: p index of element in g
//        h, g pointer to heap and graph
// output: the index of the son
int32_t findMinSon(int32_t p, heap_t *h, graph_t *g)
{
    int32_t lc = 2 * p + 1, rc = 2 * p + 2;
    if (lc >= h->n_elts)
        return -1;
    if (rc >= h->n_elts || compareDis(h->elt[lc], h->elt[rc], g))
        return lc;
    else
        return rc;
}
int32_t push_down(int32_t p, heap_t *h, graph_t *g)
{
    int32_t son = findMinSon(p, h, g);
    if (son == -1)
        return p;
    // compare the p and the children node of p to determine whether to push down p
    while (compareDis(h->elt[son], h->elt[p], g))
    {
        swapInHeap(&p, &son, h);
        son = findMinSon(p, h, g);
        if (son == -1)
            break;
    }
    return p;
}

// Push a element in heap up to maintain the feather of heap
// intput: p index of element in heap
//         h, p pointer to heap and graph
// output: the final index of pushed up element
int32_t push_up(int32_t p, heap_t *h, graph_t *g)
{
    int fa = findFa(p);
    // compare the father node of p and p to determine whether to push up p
    while (compareDis(h->elt[p], h->elt[fa], g))
    {
        swapInHeap(&p, &fa, h);
        fa = findFa(p);
    }
    return p;
}

// Insert a element into the heap
// input: id index of element in graph
//        h, g pointer to heap and graph
// output: the final index of pushed element
int32_t heapInsert(int32_t id, heap_t *h, graph_t *g)
{
    int32_t p = h->n_elts;
    h->n_elts++;
    h->elt[p] = id;
    p = push_up(p, h, g);
    return p;
}
// Pop out the top element in heap
// input: h, g, pointer to heap and graph
// output: none
void heapPop(heap_t *h, graph_t *g)
{
    int32_t p = h->n_elts - 1, tmp = 0;
    g->vertex[h->elt[p]].heap_id = -1;
    swapInHeap(&tmp, &p, h);
    h->n_elts--;
    g->vertex[h->elt[p]].heap_id = push_down(p, h, g);
}

// Get the distance from sec to dest
// input: g, h pointer to heap and graph
//        src, dest set of source points and destnations
//        path the path to be outputed
// output: 0 cannot find a path
//         1 find a path
int32_t
dijkstra(graph_t *g, heap_t *h, vertex_set_t *src, vertex_set_t *dest,
         path_t *path)
{
    int32_t n = g->n_vertices, nsrc = src->count, ndest = dest->count;
    h->n_elts = 0;
    // Initialize all elements
    for (int i = 0; i < n; ++i)
    {
        g->vertex[i].heap_id = -1;
        g->vertex[i].from_src = MY_INFINITY;
        g->vertex[i].pred = -1;
    }
    // Initialize the elements in src and heap
    for (int32_t i = 0; i < nsrc; ++i)
        g->vertex[src->id[i]].from_src = 0,
        g->vertex[src->id[i]].heap_id = heapInsert(src->id[i], h, g);
    // Main task in dijkstra
    while (h->n_elts)
    {
        // Take out the top in heap
        int32_t x = h->elt[0];
        heapPop(h, g);
        int32_t m_edges = g->vertex[x].n_neighbors;
        for (int32_t i = 0; i < m_edges; ++i)
        {
            int32_t v = g->vertex[x].neighbor[i];
            int32_t w = g->vertex[x].distance[i];
            if (w + g->vertex[x].from_src < g->vertex[v].from_src)
            {
                g->vertex[v].from_src = w + g->vertex[x].from_src;
                g->vertex[v].pred = x;
                // Judge whether v is already in heap
                if (g->vertex[v].heap_id == -1)
                    g->vertex[v].heap_id = heapInsert(v, h, g);
                g->vertex[v].heap_id = push_up(g->vertex[v].heap_id, h, g);
            }
        }
    }

    // Find the point in dst with minimal distance
    int32_t minn = MY_INFINITY, min_ind = -1;
    for (int32_t i = ndest - 1; i >= 0; --i)
        if (g->vertex[dest->id[i]].from_src < minn)
            minn = g->vertex[dest->id[i]].from_src,
            min_ind = dest->id[i];
    if (minn == MY_INFINITY)
        return 0;
    path->n_vertices = 0;
    path->tot_dist = minn;
    //test
    //printf("%d %d\n%d %d\n", nsrc, ndest, minn, min_ind);

    // Push the point into the path
    int32_t tmp = min_ind;
    while (tmp != -1)
    	path->n_vertices++,
        tmp = g->vertex[tmp].pred;
    
    path->id = (int32_t*)malloc(path->n_vertices * sizeof(int32_t));
    if (path == NULL)
        return 0;

    for (int32_t i = 0; i < path->n_vertices; ++i)
    {
        path->id[path->n_vertices - 1 - i] = min_ind;
        min_ind = g->vertex[min_ind].pred;
    }
    if (path->n_vertices == 1)
        path->id[path->n_vertices++] = path->id[0];
    //test
    /*
    for (int i = 0; i < nsrc; ++i)
        if (g->vertex[src->id[i]].pred != -1)
            printf("\n%d\n", src->id[i]);
    */
    return 1;
}
