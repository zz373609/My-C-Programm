/*expensive*/
price(bmw_728,expensive).
engine(bmw_728,low).
transmission(bmw_728,manual).
drive(bmw_728,frontwheel).
fuel(bmw_728,hybrid).
doors(bmw_728,fourdoors).
features(bmw_728,iphoneinput).

price(audio_a6,expensive).
engine(audio_a6,low).
transmission(audio_a6,auto).
drive(audio_a6,awd).
fuel(audio_a6,gasoline).
doors(audio_a6,fourdoors).
features(audio_a6,iphoneinput).

price(land_rover,expensive).
engine(land_rover,low).
transmission(land_rover,auto).
drive(land_rover,awd).
fuel(land_rover,gasoline).
doors(land_rover,fourdoors).
features(land_rover,iphoneinput).

price(mercedes_benz_g65_mg,expensive).
engine(mercedes_benz_g65_mg,high).
transmission(mercedes_benz_g65_mg,auto).
drive(mercedes_benz_g65_mg,frontwheel).
fuel(mercedes_benz_g65_mg,hybrid).
doors(mercedes_benz_g65_mg,fourdoors).
features(mercedes_benz_g65_mg,iphoneinput).

price(brabus,expensive).
engine(brabus,low).
transmission(brabus,auto).
drive(brabus,frontwheel).
fuel(brabus,hybrid).
doors(brabus,fourdoors).
features(brabus,iphoneinput).

price(tesla,expensive).
engine(tesla,low).
transmission(tesla,auto).
drive(tesla,frontwheel).
fuel(tesla,electric).
doors(tesla,fourdoors).
features(tesla,iphoneinput).

price(acura_mdx,expensive).
engine(acura_mdx,low).
transmission(acura_mdx,auto).
drive(acura_mdx,frontwheel).
fuel(acura_mdx,hybrid).
doors(acura_mdx,fourdoors).
features(acura_mdx,iphoneinput).



/*very expensive and speed*/
price(bentley_continental,very_expensive).
engine(bentley_continental,high).
transmission(bentley_continental,auto).
drive(bentley_continental,awd).
fuel(bentley_continental,gasoline).
doors(bentley_continental,twodoors).
features(bentley_continental,iphoneinput).

price(ferrari_f430,very_expensive).
engine(ferrari_f430,high).
transmission(ferrari_f430,manual).
drive(ferrari_f430,awd).
fuel(ferrari_f430,gasoline).
doors(ferrari_f430,twodoors).
features(ferrari_f430,iphoneinput).

price(lamborghini_aventador,very_expensive).
engine(lamborghini_aventador,high).
transmission(lamborghini_aventador,manual).
drive(lamborghini_aventador,frontwheel).
fuel(lamborghini_aventador,hybrid).
doors(lamborghini_aventador,twodoors).
features(lamborghini_aventador,iphoneinput).

price(maybach_exelero,very_expensive).
engine(maybach_exelero,high).
transmission(maybach_exelero,manual).
drive(maybach_exelero,awd).
fuel(maybach_exelero,gasoline).
doors(maybach_exelero,twodoors).
features(maybach_exelero,iphoneinput).

price(porsche_918,very_expensive).
engine(porsche_918,high).
transmission(porsche_918,manual).
drive(porsche_918,awd).
fuel(porsche_918,gasoline).
doors(porsche_918,twodoors).
features(porsche_918,backupcamera).


/*normal*/
price(volkswagen_passat,normal).
engine(volkswagen_passat,low).
transmission(volkswagen_passat,manual).
drive(volkswagen_passat,awd).
fuel(volkswagen_passat,gasoline).
doors(volkswagen_passat,fourdoors).
features(volkswagen_passat,cdinput).

price(toyota_camry,normal).
engine(toyota_camry,low).
transmission(toyota_camry,auto).
drive(toyota_camry,frontwheel).
fuel(toyota_camry,hybrid).
doors(toyota_camry,fourdoors).
features(toyota_camry,cdinput).

price(honda_accord,normal).
engine(honda_accord,low).
transmission(honda_accord,auto).
drive(honda_accord,frontwheel).
fuel(honda_accord,hybrid).
doors(honda_accord,fourdoors).
features(honda_accord,cdinput).

price(ford_explorer,normal).
engine(ford_explorer,high).
transmission(ford_explorer,auto).
drive(ford_explorer,frontwheel).
fuel(ford_explorer,hybrid).
doors(ford_explorer,fourdoors).
features(ford_explorer,iphoneinput).

price(jeep_grand_cherokee,normal).
engine(jeep_grand_cherokee,high).
transmission(jeep_grand_cherokee,auto).
drive(jeep_grand_cherokee,awd).
fuel(jeep_grand_cherokee,gasoline).
doors(jeep_grand_cherokee,fourdoors).
features(jeep_grand_cherokee,iphoneinput).


/*cheap*/
price(hyundai,cheap).
engine(hyundai,high).
transmission(hyundai,auto).
drive(hyundai,frontwheel).
fuel(hyundai,hybrid).
doors(hyundai,fourdoors).
features(hyundai,iphoneinput).

price(kia_k5,cheap).
engine(kia_k5,low).
transmission(kia_k5,auto).
drive(kia_k5,awd).
fuel(kia_k5,gasoline).
doors(kia_k5,fourdoors).
features(kia_k5,cdinput).


price(chery_qq,cheap).
engine(chery_qq,low).
transmission(chery_qq,auto).
drive(chery_qq,awd).
fuel(chery_qq,gasoline).
doors(chery_qq,fourdoors).
features(chery_qq,cdinput).


/*pirce*/
price_level(cheap):- income(P),P<10.
price_level(normal):- income(P),P>=10,P<20.
price_level(expensive):- income(P),P>=20,P<50.
price_level(very_expensive):- income(P),P>50.

/*brand*/

features_have(iphoneinput):- brand_choose(yes).
features_have(backupcamera):- brand_choose(yes).
features_have(cdinput):- brand_choose(no).

/*engine*/
engine_power(low):- engine_choose(no).
engine_power(high):- engine_choose(yes).

/*save*/
fuel_type(gasoline):- save_choose(no).
fuel_type(hybrid):- save_choose(yes).
fuel_type(electric):- save_choose(yes).

drive_prefer(frontwheel):- save_choose(yes).
drive_prefer(awd):- save_choose(no).

/*use_for*/
transmission_type(manual):- purpose(speed).
transmission_type(manual):- purpose(pesonal).
transmission_type(auto):- purpose(speed).
transmission_type(auto):- purpose(pesonal).
transmission_type(auto):- purpose(family).
transmission_type(auto):- purpose(other).

doors_needs(twodoors):- purpose(speed).
doors_needs(threedoors):- purpose(speed).
doors_needs(fourdoors):- purpose(pesonal).
doors_needs(fourdoors):- purpose(family).
doors_needs(fourdoors):- purpose(other).

/*combine infor*/
price_ok(C):- price_level(Pr),price(C,Pr).
for_ok(C):- transmission(C,T),transmission_type(T),doors(C,D),doors_needs(D).
engine_ok(C):- engine_power(E),engine(C,E).
brand_ok(C):- features(C,F),features_have(F).
save_ok(C):- drive(C,Dr),drive_prefer(Dr),fuel(C,Fu),fuel_type(Fu).


/*find car*/
car(C):-price_ok(C),engine_ok(C),brand_ok(C),save_ok(C),for_ok(C).


advise:- write('what is your income monthly/lees_10/10/20/more?/k'),nl,read(Price),nl,
		 assert(income(Price)),nl,
	     write('Do want good barnd? yes/no'),nl,read(Brand),nl,
	     assert(brand_choose(Brand)),nl,
	     write('Do you want powerful engine? yes/no'),nl,read(Engine),nl,
	     assert(engine_choose(Engine)),nl,
	     write('Would you like to save money about gasoline? yes/no'),nl,read(Save),nl,
	     assert(save_choose(Save)),nl,
	     write('What purpose you car use for? family, pesonal,speed,other'),nl,read(Reason),nl,
	     assert(purpose(Reason)),nl,
	     findall(C,car(C),Cs),
         write('You might enjoy the following cars: '), nl,
         writelist(Cs),
         retract(income(Price)),retract(brand_choose(Brand)),
         retract(engine_choose(Engine)),retract(save_choose(Save)),
         retract(purpose(Reason)).
        
        
writelist([]).
writelist([H|T]) :- writeonce(H,T), writelist(T).  
writeonce(H,T) :- member(H,T).
writeonce(H,T) :- not(member(H,T)), write(H), nl.
		 
	     