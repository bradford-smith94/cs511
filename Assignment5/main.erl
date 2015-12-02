
-module(main).
-export([ main/1, filler/2, run/0, test/2]).

% filler: spawns Count number of watchers
filler ( Count, Args = { Module, Fn, N } ) ->
  spawn(Module, Fn, [ Count, erlang:min(N - Count, 10) ]),
  Args.

% test: a test function for Erlang's random:uniform
test (_,_ ) ->
  io:fwrite("t~p~n", [random:uniform(11)]).

% main: starts the main loop with N number of processes
main ( N ) ->
  %random:seed(erlang:now()),
  system:loop(0, N, 10, ?MODULE, filler, { watcher, watcher, N }).
  %system:loop(0, 10, 1, ?MODULE, test, 0).

% run: a test function for system:rand
run ( ) ->
  { _, _, Seed } = erlang:now(),
  Fn = system:rand(Seed, 1, 11),
  { Fn1, R1 } = Fn(),
  { Fn2, R2 } = Fn1(),
  { _, R3 } = Fn2(),
  io:fwrite("~p~n", [[R1,R2,R3]]).

