Given a grid of size N x M, where K given cells are blocked.
Find number of ways to reach (N, M) from (1, 1) if you can move right or down.
N, M <= 1e5 K <= 1e3

Explanation:
First a basic formula, number of ways to reach (x2, y2) from (x1, y1) if x2 >= x1 and y2 >= y1:
F(x1, y1, x2, y2) = (x+y)!/(x!y!) where n! denotes n factorial.

Now, an interesting observation is that if I block a cell at (i, j) all cells with their
respective coordinates greater than or equal to i and j will be affected by it.

Let's say our set S = {all blocked cells + cell(N, M)}.
I now sort S on increasing basis of x coordinate and then increasing on y.
Also I maintin an array ans where ans[i] denotes number of ways to reach
cell at index i in sorted(S). Intially ans[i] = F(1, 1, S[i].x, S[i].y).

Now, I traverse the sorted(S) in increasing order and updating the
number of ways for all the cells that it affects.

for i=0 to S.size()-2:
    for j=i+1 to S.size()-1:
        if S[j].x<S[i].x or S[j].y<S[i].y:  //cell j not affected
            continue
        //ans[i] stores current number of ways to reach that cell
        //now all paths from cell (1,1) to cell j are blocked
        //so we subtract (number of ways to reach i * number of paths from i to j)
        ans[j] -= ans[i]*F(S[i].x, S[i].y, S[j].x, S[j].y)

print ans[S.size()-1]
