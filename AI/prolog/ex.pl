
/* Sample Restaurant Advisor Prolog Program */
/* Contributed by an anonymous AI student from years past */

/* First Step: Think about the world of restaurants.
   What are the possible restaurants a user could go to?
   How can we characterize these restaurants? */

fast_food(jimmy_johns).
healthy(jimmy_johns).
food(jimmy_johns, sandwiches).
food(jimmy_johns, subs).
up_town(jimmy_johns).
price(jimmy_johns, moderate).

fast_food(wendys).
food(wendys, burgers).
food(wendys, fries).
food(wendys, soup).
food(wendys, salad).
kids_meal(wendys).
up_town(wendys).
price(wendys, cheap).

sit_down(bob_evans).
food(bob_evans, breakfast).
food(bob_evans, biscuits).
food(bob_evans, soup).
kids_meal(bob_evans).
kids_entertainment(bob_evans).
price(bob_evans, expensive).

sit_down(lams).
take_out(lams).
food(lams, chinese).
price(lams, moderate).

sit_down(damons).
food(damons, steak).
food(damons, ribs).
food(damons, chicken).
adult_entertainment(damons).
price(damons, expensive).

/* Don't stop with only five restaurants.  This is just an example!
   The more restaurants you think of, the more characteristics
   you will discover to describe them.  You can go back to the
   restaurants you described earlier and add in your new predicates
   with their appropriate values. */

/* Last Step: Compose rules that relate the answers to the questions
   you ask to the possible dining choices.  Use as many intermediate
   steps as you need.  Remember that, in a real world program,
   there could be hundreds of restaurants to choose from and you
   could ask the user more than three or four questions. */

can_get_to(R) :- up_town(R).
can_get_to(R) :- have_car(yes).

kids_ok(R) :- have_kids(no).
kids_ok(R) :- have_kids(yes), kids_meal(R).
kids_ok(R) :- have_kids(yes), kids_entertainment(R).

desired_price(cheap) :- will_spend(M), M < 5.
desired_price(moderate) :- will_spend(M), M >= 5, M < 10.
desired_price(expensive) :- will_spend(M), M >= 10.

price_ok(R) :- price(R, X), desired_price(X).

restaurant(R) :- can_get_to(R), kids_ok(R), price_ok(R).

/* Second Step: What information is available to base a
   decision on?  What questions should you ask the user? 
   Remember that the real world does not limit you to
   three questions. */

advise :- write('Do you have a car?  '), read(Car), nl,
          assert(have_car(Car)),
          write('Do you have kids?  '), read(Kids), nl,
          assert(have_kids(Kids)),
          write('How much money do you want to spend per person?  '),
          read(Money), nl,
          assert(will_spend(Money)), 
          findall(R,restaurant(R),Rs),
          write('You might enjoy the following restaurants: '), nl,
          writelist(Rs),
          retract(have_car(Car)), retract(have_kids(Kids)),
          retract(will_spend(Money)).

writelist([]).
writelist([H|T]) :- writeonce(H,T), writelist(T).  
writeonce(H,T) :- member(H,T).
writeonce(H,T) :- not(member(H,T)), write(H), nl.