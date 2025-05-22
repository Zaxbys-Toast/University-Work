/* WSC Schedule Program */
is_hot(Person) :- 
	is_in_class(Person, Class),
	is_in_room(Class, Room),
	has_temperature(Room, Temp),
	Temp > 80.
is_in_class(will, csc380).
is_in_class(toby,csc380).
is_in_class(bob,csc480).
is_in_class(toby,csc480).
is_in_room(csc480,wsc100).
is_in_room(csc380,wsc238).
has_temperature(wsc100,65).
has_temperature(wsc238,92).
