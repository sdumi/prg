-module(ball).

%% to run this program 
%% redefine the OTHERNODE macro
%%  > c(ball).
%%  > ball:install_code().
%%  > ball:run().

%% redefine this macro to your nodename
-define(OTHERNODE, x@yuck).

-export([install_code/0, run/0, internal/1]).

%% install_code() sends the code over the network
%% to my windows machine
install_code() -> 
    install_code(?MODULE).

install_code(Mod) ->
    ObjectPath = code:which(Mod),
    {ok, Bin} = file:read_file(ObjectPath),
    rpc:call(?OTHERNODE, code, load_binary,  [Mod, ObjectPath, Bin]).

run() ->
    Me    = spawn(?MODULE, internal, [true]),
    Other = spawn(?OTHERNODE, ?MODULE, internal, [false]),
    Me    ! Other,
    Other ! Me.

internal(Tag) ->
    etk:start(),
    Top = etk:toplevel([]),
    etk:wm([geometry, Top, "155x125+100+100"]),  
    Canvas = etk:canvas(Top, []),
    etk:pack([Canvas, {fill,both},{expand,yes}]),
    Self = self(),
    B = etk:button(Canvas, [{text, "Click to kill"},
                            {command, fun() -> Self ! quit end}]),
    etk:cmd(Canvas, [create,window,75,25,{window, B}]),
    receive
        Pid -> 
            link(Pid),
            loop(Tag, Canvas, Pid)
    end.

loop(true, Canvas, Pid) ->
    %% I got the tag create the ball
    etk:cmd(Canvas,[create, oval, 50,50,100,100,
                   {fill,red},{tag,x}]),
    receive
        quit -> exit(die);
        Other -> io:format("uugh:~p~n",[Other])
    after 2000 ->
            %% on timeout kill the ball
            etk:cmd(Canvas, [delete, x]),
            %% send a message to the other guy to create the ball
            Pid ! show,
            loop(false, Canvas, Pid)
    end;
loop(false, Canvas, Pid) ->
    receive
	quit ->
	    exit(die);
        show ->
            loop(true, Canvas, Pid)
    end.
