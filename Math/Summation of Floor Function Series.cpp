Subject: Formula for the sum of [ ] (the sign means floor)
Hello!

Is there any formula for the sum [p/q] + [2p/q] + [3p/q] + ... +
[np/q] (p, q, n are natural numbers)?

For example, [3/7] + [2*3/7] + [3*3/7] + [4*3/7] + [5*3/7]
            =  0   +    0    +    1    +    1    +    2
            = 4

I can't find a correct formula for any natural p and q.  I suspect
that it does not exist.  Maybe there is an algorithm for calculating
such sums?

It can be proved that if n = q - 1 then

[p/q] + [2p/q] + [3p/q] + ... + [(q-1)p/q] = (p-1)(q-1)/2.


Date: 01/14/2009 at 14:12:28
From: Doctor Vogler
Subject: Re: Formula for the sum of [ ]

Hi Ivan,

Thanks for writing to Dr. Math.  That's a very interesting question.
I think that your suspicion is correct that there is not a closed-form
formula for the general sum.  Fortunately, however, there is an
efficient algorithm for computing the sum.

By way of notation, I will write your sum as

  sum(k=1, n, [kp/q]).

Your formula for n=q-1 can be generalized to reduce n by any multiple
of q, as in

  sum(k=1, n, [kp/q]) =
      pt(n+1) - t(pqt + p + q - 1)/2 + sum(k=1, n-tq, [kp/q])

You'll notice that when t=1 and n=q-1 (so that the last sum is zero),
you get your formula.  Actually, your formula and this formula both
depend on p and q having no factors in common (so that p/q is a
fraction in reduced form).

Of course, it's also easy to reduce p by an integer multiple of q, and
then we get

  sum(k=1, n, [kp/q]) = tn(n+1)/2 + sum(k=1, n, [k(p-qt)/q]).

But when n and p are both smaller than q, then it's harder to figure
out what to do.  But here is one idea:  We can count the number of
times that [kp/q] = m for each number m.  It turns out that [kp/q] = m
when

  m <= kp/q < m+1

or

  mq/p <= k < (m+1)q/p

so that if both of those numbers are smaller than n, then this happens for

  {(m+1)q/p} - {mq/p}

different values of k, where I write {x} to mean x rounded *up* to the
nearest integer (which is also sometimes called the ceiling function),
in parallel to your notation [x] to mean x rounded *down* to the
nearest integer (which is also sometimes called the floor function).
(It turns out that these satisfy {x} = -[-x] for all x.  Also, if x is
an integer, then {x} = [x] = x, but if x is not an integer, then {x} =
[x] + 1.)  The last (biggest) m that will appear is m = [np/q], which
happens for

  n+1 - {mq/p}

different values of k.  So that means that

  sum(k=1, n, [kp/q]) =
       m(n + 1 - {mq/p}) + sum(k=1, m-1, k({(k+1)q/p} - {kq/p})).

By looking at how this sum nearly telescopes, we can rewrite it as

  sum(k=1, n, [kp/q]) = m(n + 1) - sum(k=1, m, {kq/p}).

If we additionally assume that mq/p is never an integer, then this is
the same as

  sum(k=1, n, [kp/q]) = mn - sum(k=1, m, [kq/p]).

Now you might ask whether we have actually made any progress.  We've
changed one sum that we don't know how to evaluate efficiently for
another sum that looks exactly the same.  But here's the clincher:
The new sum changed around some numbers, allowing us to repeat all
three formulas and continue to make progress.  So when we put it all
together, we get the following very efficient algorithm:

  Input: Positive integers n, p, q
  Output: s = sum(k=1, n, [kp/q])

  Algorithm:
    t = GCD(p, q)
    p = p/t
    q = q/t
    s = 0
    z = 1
    while (q > 0) and (n > 0)
      (point A)
      t = [p/q]
      s = s + ztn(n+1)/2
      p = p - qt
      (point B)
      t = [n/q]
      s = s + zpt(n+1) - zt(pqt + p + q - 1)/2
      n = n - qt
      (point C)
      t = [np/q]
      s = s + ztn
      n = t
      swap p and q (e.g. t = p, p = q, q = t)
      z = -z

It can be proven that this algorithm will finish in polynomial time,
which basically means that a computer could use this to evaluate sums
very quickly even if the input numbers are hundreds or thousands of
digits long.  In fact, this algorithm is comparable to the Euclidean
Algorithm for computing the GCD of two numbers.

The reason the algorithm works is that we initially force GCD(p, q) =
1, so that our formula for reducing n by a multiple of q will work.
Then subtracting qt from p and swapping p and q do not change this
fact.  Then at points A, B, and C, the sum we are looking for is

  s + z*sum(k=1, n, [kp/q]).

Going from A to B, we use the formula for reducing p by a multiple of
q.  Going from B to C, we use the formula for reducing n by a multiple
of q.  Then going from C to A, we use the last formula that I
demonstrated.  The reason that kq/p is never an integer at that point
is that kq/p is never an integer at point C (for k <= t) is that when
we went from B to C, we caused that n < q, and then

  k <= t <= np/q < qp/q = p

and since k is less than p, p cannot be a factor of k.  And then since
q and p have no factors in common, p cannot be a factor of kq, so kq/p
is not an integer, and we can use the formula with [] rather than the
one with {}.
