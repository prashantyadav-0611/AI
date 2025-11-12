% Each state is a list of facts: [on(a,table), on(b,table), on(c,a), clear(b), clear(c)]

% Define initial state
initial_state([on(a,table), on(b,table), on(c,a), clear(b), clear(c)]).

%Define goal conditions
goal([on(a,b), on(b,table), on(c,a)]).

% Check if all goals are satisfied in a state
satisfied([], _).
satisfied([Goal | Rest], State) :-
    member(Goal, State),
    satisfied(Rest, State).

% Move rule (simulate move logically)
move(State, move(X, From, To), NewState) :-
    member(on(X, From), State),
    member(clear(X), State),
    member(clear(To), State),
    X \= To,
    % Remove old facts
    delete(State, on(X, From), S1),
    delete(S1, clear(To), S2),
    delete(S2, clear(X), S3),
    % Add new facts
    append([on(X, To), clear(From)], S3, NewState).

%Recursive planner
plan(State, _, []) :-
    goal(Goals),
    satisfied(Goals, State),
    write('Goal reached!'), nl.

plan(State, Visited, [Action | Rest]) :-
    move(State, Action, NextState),
    \+ member(NextState, Visited),      % avoid loops
    write('Action: '), write(Action), nl,
    plan(NextState, [NextState | Visited], Rest).

% Entry point
solve :-
    initial_state(State),
    plan(State, [State], Steps),
    nl, write('Plan = '), write(Steps), nl.
