sumsquares(0, 0).
sumsquares(1, 1).
sumsquares(N, NSum) :-
	N > 1,
	NMinus1 is N - 1,
	sumsquares(NMinus1, NMinus1Sum),
	square(N, NSquared),
	NSum is NSquared + NMinus1Sum.

square(N, N * N).  
