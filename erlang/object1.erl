%Example taken from "Thinking in Erlang" (scribd.com)
-module(object1).
-export([main/0, new/1, get/1, set/2, delete/1, construct/1]).

%Testing
main() ->
    Object = new(1),
    io:fwrite("Get data: ~w~n", [object1:get(Object)]),
    set(Object, 2),
    io:fwrite("Get data: ~w~n", [object1:get(Object)]),
    delete(Object).

%Interface
new(Thing) ->
    spawn(object1, construct, [Thing]).

get(Object) ->
    Object ! {get, self()},
    receive
	{return, Object, Thing} ->
	    Thing
    end.

set(Object, Thing) ->
    Object ! {set, self(), Thing}.

delete(Object) ->
    exit(Object).

%Internals
construct(Thing) ->
    io:fwrite("Called constructor: ~w~n", [Thing]),
    process_flag(trap_exit, true),
    process_messages(Thing).

process_messages(Thing) ->
    receive
	{get, Caller} ->
	    io:fwrite("Called get~n"),
	    Caller ! {return, self(), Thing},
	    process_messages(Thing);
	{set, _Caller, NewThing} ->
	    io:fwrite("Called set~n", []),
	    process_messages(NewThing);
	{'EXIT', _Caller, _Reason} ->
	    io:fwrite("Called destructor~n", []),
	    true
    end.
