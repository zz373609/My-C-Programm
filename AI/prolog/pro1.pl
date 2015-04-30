price(bmw,expensive).
engine(bmw,_3cylinder).
transmission(bmw,manual).
drive(bmw,frontwheel).
fuel(bmw,hybrid).
doors(bmw,twodoors).
features(bmw,iphoneinput).

price_choose(cheap):- spend(P), P < 10.
price_choose(normal):- spend(P), P >= 10 , P < 20.
price_choose(expensive):- spend(P), P >= 20.

engine_type(_3cylinder):- e_choose(E), E =:= 1.
engine_type(_4cylinder):- e_choose(E), E =:= 2.
engine_type(_5cylinder):- e_choose(E), E =:= 3.
engine_type(_6cylinder):- e_choose(E), E =:= 4.
engine_type(_8cylinder):- e_choose(E), E =:= 5.


transmission_type(manual):- t_choose(T), T =:= 1.
transmission_type(auto):- t_choose(T), T =:= 2.

drive_prefer(frontwheel):- d_choose(D), D =:= 1.
drive_prefer(rearwheel):- d_choose(D), D =:= 2.
drive_prefer(awd):- d_choose(D), D == 3.


fuel_type(gasoline):- f_choose(F), F =:= 1.
fuel_type(hybrid):- f_choose(F), F =:= 2.
fuel_type(electric):- f_choose(F), F =:= 3.

doors_needs(twodoors):- door_choose(Door), Door =:= 1.
doors_needs(threedoors):- door_choose(Door), Door =:= 2.
doors_needs(fourdoors):- door_choose(Door), Door =:= 3.

features_needs(iphoneinput):- ft_choose(Ft), Ft =:= 1.
features_needs(cdinput):- ft_choose(Ft), Ft =:= 2.
features_needs(backupcamera):- ft_choose(Ft), Ft =:= 3.



price_ok(C):-price_choose(Pr),price(C,Pr).
engine_ok(C):- engine_type(En),engine(C,En).
transmission_ok(C):- transmission_type(Tra),transmission(C,Tra).
drive_prefer_ok(C):- drive_prefer(Dri),drive(C,Dri).
fuel_type_ok(C):- fuel_type(Fue),fuel(C,Fue).
doors_needs_ok(C):- doors_needs(Dor),doors(C,Dor).
features_needs_ok(C):- features_needs(Fea),features(C,Fea).

car(C):-price_ok(C),engine_ok(C),transmission_ok(C),drive_prefer_ok(C),fuel_type_ok(C),doors_needs_ok(C),features_needs_ok(C).

advise:- write('What price would you like to spend(/k),such as 10,15, or more'),nl,read(Price),nl,
		 assert(spend(Price)),
		 write('Choose the engine you like, just type in number'), nl,
		 write('1. 3cylinder'),nl,
		 write('2. 4cylinder'),nl,
		 write('3. 5cylinder'),nl,
		 write('4. 6cylinder'),nl,
		 write('5. 8cylinder'),nl,
		 read(Engine),nl,
		 assert(e_choose(Engine)),
		 write('what transmission you want'), nl,
		 write('1. manual'),nl,
		 write('2. auto'),nl,
		 read(Transmission),nl,
		 assert(t_choose(Transmission)),
		 write('what drive wheel you want to'), nl,
		 write('1. frontwheel'),nl,
		 write('2. rearwheel'),nl,
		 write('3. awd'),nl,
		 read(Drive_prefer),nl,
		 assert(d_choose(Drive_prefer)),
		 write('what type gasoline you want'),nl,
		 write('1. gasoline'),nl,
		 write('2. hybrid'),nl,
		 write('3. electric'),nl,
		 read(Fuel_type),nl,
		 assert(f_choose(Fuel_type)),
		 write('How many doors you want'),nl,
		 write('1. twodoors'),nl,
		 write('2. threedoors'),nl,
		 write('3. fourdoors'),nl,
		 read(Doors_number),nl,
		 assert(door_choose(Doors_number)),
		 write('What features you want to add in'),nl,
		 write('1. iphoneinput'),nl,
		 write('2. cdinput'),nl,
		 write('3. backupcamera'),nl,
		 read(Features),nl,
		 assert(ft_choose(Features)),
		 findall(C,car(C),Cs),
         write('You might enjoy the following cars: '), nl,
         writelist(Cs),
         retract(spend(Price)), retract(e_choose(Engine)),
         retract(t_choose(Transmission)),retract(d_choose(Drive_prefer)),
         retract(f_choose(Fuel_type)),
         retract(door_choose(Doors_number)),
         retract(ft_choose(Features)).
        
        
writelist([]).
writelist([H|T]) :- writeonce(H,T), writelist(T).  
writeonce(H,T) :- member(H,T).
writeonce(H,T) :- not(member(H,T)), write(H), nl.
		 
		 
		 
		 
		 
		 
		 
		 
		 
		 
		 
		  
		



