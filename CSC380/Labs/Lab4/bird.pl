hassize(bluebird, small).
hascovering(bird, feathers).
hascolor(bluebird, blue).
hasproperty(bird, flies).
isa(bluebird, bird).
isa(bird, vertebrate).
isbird(Animal) :- 
	hasproperty(Animal, flies),
	hascovering(Animal, feathers),
	isa(Animal, bird).	
	 
