-module(lib_misc).
-export([for/3, qsort/1, pythag/1]).

for(Max, Max, F) -> [F(Max)];
for(I, Max, F)   -> [F(I)|for(I+1, Max, F)].

%amazing how simple it seems to be
qsort([]) -> [];
qsort([Pivot|T]) ->
    qsort([X || X <- T, X <  Pivot])
    ++ [Pivot] ++
    qsort([X || X <- T, X >= Pivot]).

% the function pythag(N) generates a list of all integers {A, B, C}
% such that  A^2 + B^2 = C^2 and where the sum of the sides is 
% less than or equal to N
pythag(N) ->
    [{A, B, C} ||
	A <- lists:seq(1, N),
	B <- lists:seq(1, N),
	C <- lists:seq(1, N),
	A+B+C =< N,
	A*A + B*B =:= C*C
     ].
