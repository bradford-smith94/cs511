
-module(watcher).
-export([watcher/2, filler/2]).

% spawn_sensor: create a sensor process with giving it the id Id and this
%   process so it knows it's watcher
spawn_sensor ( Id ) ->
  { Sensor, _ } = spawn_monitor(sensor, sensor, [Id, self()]),
  Sensor.

% filler: fills a list with sensors
filler ( Count, { Ctx, Multiple } ) ->
  Id = Multiple + Count,
  { lists:append(Ctx, [{spawn_sensor(Id), Id}]), Multiple }.

% watcher: starts the main watcher loop
watcher ( Multiple, Count ) ->
  { Sensors, _ } = system:loop(0, Count - 1, 1, ?MODULE, filler, { [], Multiple }),
  io:fwrite("watcher: launch ~p~n", [ Sensors ]),
  watcher_loop(Sensors).

% watcher_loop: receives messages from sensors, if the sensor crashed restart
%   it, else print it's Id and Measurement
watcher_loop ( Sensors ) ->
  receive
  { 'DOWN', _, process, Pid, Reason } ->
    { _, Id } = lists:keyfind(Pid, 1, Sensors),
    io:fwrite("watcher: receive-down[~p] (~s)~n", [ Id, Reason ]),
    S = lists:keyreplace(Id, 2, Sensors, { spawn_sensor(Id), Id });
  { Id, Integer } ->
    io:fwrite("watcher: receive-mark[~p] (~p)~n", [ Id, Integer ]),
    S = Sensors
  end,
  watcher_loop(S).

