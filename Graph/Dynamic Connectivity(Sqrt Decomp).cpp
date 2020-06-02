/***
    Having N isolated nodes at first, there will be 3 types of queries :
    Type 1 : connect node u and node v by an edge
    Type 2 : remove the edge between node u and node v
    Type 3 : Is node u and node v in the same connected component ?
    M queries in total. No invalid removal.

    Divide the queries into sqrt(M) blocks.

    While processing block b, there will be 3 types of edges :

    Type 1 : Exists at the starting of the block and won't be removed in this block.
    Type 2 : Does not exist in the start of the block and won't be added
             in this block
    Type 3 : Will be added/removed in this block.

    We can ignore Type 2 edges.
    Before starting to process a block,we will build a graph G with the Type 1 edges.
    If there are X components, we build a new graph G' with X nodes. We remove the
    nodes which won't be affected at all by the current block.
    Now we will start processing the block :

    We do nothing for Type1 and Type2 query.
    For type 3 query, we add the edges in G' which were added in the block and
    hasn't been removed yet and run a dfs to answer the query.

    Complexity : O( (N+M) * sqrt(N+M) )

    https://www.spoj.com/problems/DYNACON1/
    https://www.spoj.com/problems/DYNACON2/


***/
