
-module(sensor).
-export([ sensor/2 ]).

% sensor: starts the main sensor loop
sensor ( Id, Watcher ) ->
  io:fwrite("sensor : start: ~p~n", [ Id ]),
  { _, _, Seed } = erlang:now(),
  sensor_loop(Id, Watcher, system:rand(Seed, int)).

% sensor_loop: generates a random number for Measurement between 1 and 11
%   inclusively, if Measurement is 11 crash else send watcher the sensor's
%   Id and the Measurement
sensor_loop ( Id, Watcher, State ) ->
  { NextState, Measurement } = State(1, 11),
  if Measurement =< 10 ->
    Watcher ! { Id, Measurement };
  true ->
    exit(anomalous_reading)
  end,
  { LastState, SleepTime } = NextState(1, 10000),
  timer:sleep(SleepTime),
  sensor_loop(Id, Watcher, LastState).

