/***
    s   --> current state
    ns  --> neighboring state of s state

    F(s)--> evaluates some state

    e   --> F(s)
    ne  --> F(ns)

    T   --> Temperature

    P(e,ne,T) --> Probability of moving to the neighboring state ns

    When we are trying to find global maximum :
    if ne >= e :
        P(e,ne,T) = 1
    else :
        P(e,ne,T) = exp((ne-e)/T)

***/

/*** Pseudo Code ***/
    T = sth around 1e9
    mul = 0.997
    for it = 0 to trough lim :
        ns = neighbour(s) ( Pick a random neighbour )
        if P(e,ne,T) >= random(0,1) :
            s = ns
        if T >= 1e-20:
            T *= mul

/***
    Suppose you can afford LIM iterations given the time limit.
    It's better Run the algorithm several(1<x<10) times, everytime with different
    temperature and the number of iterations each time will be (LIM/x)
***/


/***
    Selecting the parameters

    *  An essential requirement for the neighbour() function is that the diameter
       of the search graph must be small. In the traveling salesman problem,
       the search space for n = 20 cities has n! = 2,432,902,008,176,640,000 states;
       yet the neighbor generator function that swaps two consecutive cities can get
       from any state (tour) to any other state in at most {n(n-1)/2 = 190 steps

    * In TSP, it's better to swap adjacent elements as it does not do any drastic change
      to the current state
***/

