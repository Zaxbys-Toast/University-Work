fact(0, 1).
fact(N, Nfact) :-
	N > 0,
	NMinus1 is N - 1,
	fact(NMinus1, FactMinus1),
	Nfact is N * NMinus1.
