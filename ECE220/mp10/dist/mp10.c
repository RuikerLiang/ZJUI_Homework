#include <stdint.h>
#include <stdio.h>

#include "mp10.h"

int32_t
mark_vertex_minimap(graph_t *g, pyr_tree_t *p)
{
	if (g->n_vertices <= 64)
	{
		for (int32_t i = 0; i < g->n_vertices; ++i)
			g->vertex[i].mm_bit = i;
	}
	int start = p->n_nodes - g->n_vertices - 1;
	for (int32_t i = start; i < p->n_nodes; ++i)
	{
		int32_t tmp = i, id = p->node[i].id;
		while (tmp > 84)
			tmp = (tmp - 1) / 4;
		g->vertex[id].mm_bit = tmp - 21;
	}
	return 1;
}

void build_vertex_set_minimap(graph_t *g, vertex_set_t *vs)
{
	vs->minimap = 0;
	for (int32_t i = 0; i < vs->count; ++i)
		vs->minimap = vs->minimap | (1ULL << g->vertex[vs->id[i]].mm_bit);
	return;
}

void build_path_minimap(graph_t *g, path_t *p)
{
	p->minimap = 0;
	for (int32_t i = 0; i < p->n_vertices; ++i)
		p->minimap = p->minimap | (1ULL << g->vertex[p->id[i]].mm_bit);
	return;
}

int32_t
merge_vertex_sets(const vertex_set_t *v1, const vertex_set_t *v2,
				  vertex_set_t *vint)
{
	vint->count = 0;
	int32_t p1 = 0, p2 = 0;
	while ((p1 < v1->count) && (p2 < v2->count))
	{
		if (v1->id[p1] > v2->id[p2])
			++p2;
		else if (v1->id[p1] < v2->id[p2])
			++p1;
		else
		{
			vint->id[vint->count++] = v1->id[p1];
			++p1, ++p2;
		}
	}
	if (vint->count)
		return 1;
	return 0;
}
