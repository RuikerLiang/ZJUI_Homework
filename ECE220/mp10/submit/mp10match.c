#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "mp5.h"
#include "mp10.h"

//
// These variables hold the heads of two singly-linked lists of
// requests.
//
// The avaialble list consists of unpaired requests: partner
// should be NULL, and next is used to form the list.
//
// The shared list consists of groups with non-empty start and end
// vertex intersections.  Only one of the requests in the group is in
// the list.  The others are linked through the first's partner field
// and then through the next field of the others in the group.  The
// next field of the first request in a group is used to form the
// shared list.
//
// Note: for MP2, you should only build groups of two in the shared
// list.
//

static request_t *available = NULL;
static request_t *shared = NULL;

void free_all(request_t* ptr, vertex_set_t* tmp_src, vertex_set_t* tmp_dst)
{
    if (ptr)
    {
        if (ptr->dst_vs)
            free_vertex_set(ptr->dst_vs);
        if (ptr->src_vs)
            free_vertex_set(ptr->src_vs);
        if (ptr->path)
            free_path(ptr->path);
    }
    if (tmp_src)
        free_vertex_set(tmp_src);
    if (tmp_dst)
        free_vertex_set(tmp_dst);
}

int32_t
handle_request(graph_t *g, pyr_tree_t *p, heap_t *h, request_t *r)
{
    request_t *ptr = r;
    ptr->dst_vs = new_vertex_set(), ptr->src_vs = new_vertex_set();
    ptr->path = new_path();
    vertex_set_t* tmp_src = new_vertex_set(), *tmp_dst = new_vertex_set();
    if (!ptr->dst_vs || !ptr->src_vs || !ptr->path || !tmp_src || !tmp_dst)
    {
        free_all(ptr,tmp_src, tmp_dst);
        return 0;
    }
    find_nodes(&ptr->from, ptr->src_vs, p, 0);
    find_nodes(&ptr->to, ptr->dst_vs, p, 0);
    tmp_src->id = (int32_t*)malloc(ptr->src_vs->count * sizeof(*tmp_dst->id));
    tmp_src->id_array_size = ptr->src_vs->count;
    tmp_dst->id = (int32_t*)malloc(ptr->dst_vs->count * sizeof(*tmp_dst->id));
    tmp_dst->id_array_size = ptr->dst_vs->count;
    if (!tmp_src->id || !tmp_dst->id)
    {
        free_all(ptr, tmp_src, tmp_dst);
        return 0;
    }
    build_vertex_set_minimap(g, ptr->src_vs);
    build_vertex_set_minimap(g, ptr->dst_vs);
    r->partner = NULL;
    //for (request_t *i = available, *lst = NULL, *nxt = i->next; i; lst = i, i = nxt, nxt = nxt->next)
    request_t* i = available, *lst = NULL, *nxt = NULL;
    if (i)
        nxt = i->next;
    while (i)
    {
        if (merge_vertex_sets(ptr->src_vs, i->src_vs, tmp_src) && merge_vertex_sets(ptr->dst_vs, i->dst_vs, tmp_dst) && dijkstra(g, h, tmp_src, tmp_dst, ptr->path))
        {
            // Change src and dst set
            free_vertex_set(ptr->src_vs);
            free_vertex_set(ptr->dst_vs);
            free_vertex_set(i->src_vs);
            free_vertex_set(i->dst_vs);
            ptr->src_vs = tmp_src;
            i->src_vs = tmp_src;
            ptr->dst_vs = tmp_dst;
            i->dst_vs = tmp_dst;
            build_vertex_set_minimap(g, ptr->src_vs);
            build_vertex_set_minimap(g, ptr->dst_vs);
            // Delete request from available
            if (lst)
                lst->next = i->next;
            else
                available = i->next;
            // Initialize partner into the shared
            ptr->partner = i;
            i->next = NULL;
            // Set path
            i->path = ptr->path;
            build_path_minimap(g, ptr->path);
            ptr->next = shared;
            shared = ptr;
            ptr = NULL;
            return 1;
        }
        lst = i, i = nxt;
        if (nxt)
            nxt = nxt->next;
    }
    ptr->next = available;
    available = ptr;
    if (ptr->path)
        free_path(ptr->path);
    ptr->path = NULL;
    ptr = NULL;
    free_all(ptr, tmp_src, tmp_dst);
    return 1;
}


void print_results()
{
    request_t *r;
    request_t *prt;

    printf("Matched requests:\n");
    for (r = shared; NULL != r; r = r->next)
    {
        printf("%5d", r->uid);
        for (prt = r->partner; NULL != prt; prt = prt->next)
        {
            printf(" %5d", prt->uid);
        }
        printf(" src=%016lX dst=%016lX path=%016lX\n", r->src_vs->minimap,
               r->dst_vs->minimap, r->path->minimap);
    }

    printf("\nUnmatched requests:\n");
    for (r = available; NULL != r; r = r->next)
    {
        printf("%5d src=%016lX dst=%016lX\n", r->uid, r->src_vs->minimap,
               r->dst_vs->minimap);
    }
}

int32_t
show_results_for(graph_t *g, int32_t which)
{
    request_t *r;
    request_t *prt;

    // Can only illustrate one partner.
    for (r = shared; NULL != r; r = r->next)
    {
        if (which == r->uid)
        {
            return show_find_results(g, r, r->partner);
        }
        for (prt = r->partner; NULL != prt; prt = prt->next)
        {
            if (which == prt->uid)
            {
                return show_find_results(g, prt, r);
            }
        }
    }

    for (r = available; NULL != r; r = r->next)
    {
        if (which == r->uid)
        {
            return show_find_results(g, r, r);
        }
    }
    return 0;
}

static void
free_request(request_t *r)
{
    free_vertex_set(r->src_vs);
    free_vertex_set(r->dst_vs);
    if (NULL != r->path)
    {
        free_path(r->path);
    }
    free(r);
}

void free_all_data()
{
    request_t *r;
    request_t *prt;
    request_t *next;

    // All requests in a group share source and destination vertex sets
    // as well as a path, so we need free those elements only once.
    for (r = shared; NULL != r; r = next)
    {
        for (prt = r->partner; NULL != prt; prt = next)
        {
            next = prt->next;
            free(prt);
        }
        next = r->next;
        free_request(r);
    }

    for (r = available; NULL != r; r = next)
    {
        next = r->next;
        free_request(r);
    }
}
