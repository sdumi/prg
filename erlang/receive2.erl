-module(receive2).
-export([main/0, thread/0]).

main() ->
    Pid = spawn(receive2, thread, []),
    io:fwrite("Spawned new process ~w~n", [Pid]),
    Pid ! hello,
    exit(Pid, suckage).

thread() ->
    io:fwrite("This is a thread.~n", []),
    process_messages().

process_messages() ->
    receive
	hello ->
	    io:fwrite("Received hello~n"),
	    process_messages()
    after 2000 ->
	    io:fwrite("Timeout.~n")
    end.
