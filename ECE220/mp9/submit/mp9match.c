#include <stdint.h>
#include <stdio.h>

#include "mp5.h"
#include "mp9.h"

// Find a path that can match the request
// input: g, p, h pointer to graph, tree and heap
//        r1, r2 pointer to the request information
//        src_vs, dst_vs points set
//        path the outputed path
// output: 0 cannot find a path matches the request
//         1 found a path matches the request
int32_t
match_requests (graph_t* g, pyr_tree_t* p, heap_t* h,
		request_t* r1, request_t* r2,
		vertex_set_t* src_vs, vertex_set_t* dst_vs, path_t* path)
{
	src_vs->count = dst_vs->count = 0;
	// Insert the nodes
	find_nodes(&r1->from, src_vs, p, 0);
	find_nodes(&r1->to, dst_vs, p, 0);
	//test
	/*
	int cnt1 = find_nodes_inst(&r1->from, src_vs, p, 0);
	int cnt2 = find_nodes_inst(&r1->to, dst_vs, p, 0);
	printf("%d %d\n", cnt1, cnt2);
	*/
	// Delete the nodes which are not met up the second require
	trim_nodes(g, src_vs, &r2->from);
	trim_nodes(g, dst_vs, &r2->to);
	if (src_vs->count == 0 || dst_vs->count == 0)
		return 0;
	if (!dijkstra(g, h, src_vs, dst_vs, path))
		return 0;
	if (path->n_vertices > MAX_PATH_LENGTH)
		return 0;
	return 1;
}
