animal(dog)  :- is_true('has fur'), is_true('says woof').
animal(cat)  :- is_true('has fur'), is_true('says meow').
animal(duck) :- is_true('has feathers'), is_true('says quack').
animal(mouse) :- is_true('is small'), is_true('says squeak').
animal(bear) :- is_true('has fur'), is_true('says roar').
animal(tiger) :- is_true('has fur'), is_true('is orange').
animal(giraffe) :- is_true('has fur'), is_true('is tall').

is_true(Q) :-
        format("~w?\n", [Q]),
        read(yes).
