
-module(system).
-export([ loop/6, floor/1, rand/1, rand/2 ]).

%loop ( From, To, By, Module, Fn, Ctx ) ->
%  if
%    By < 0 ->
%      if
%        From >= To ->
%          loop(From + By, To, By, Module, Fn, Module:Fn(From, Ctx));
%        true ->
%          Ctx
%      end;
%    true ->
%      if
%        From =< To ->
%          loop(From + By, To, By, Module, Fn, Module:Fn(From, Ctx));
%        true ->
%          Ctx
%      end
%  end.

% loop: a generic loop, iterates from 'From' to 'To' in increments of 'By'
%   executing function 'Fn' from module 'Module' with argument context 'Ctx'
loop ( From, To, By, Module, Fn, Ctx ) when By < 0, From >= To ->
  loop(From + By, To, By, Module, Fn, Module:Fn(From, Ctx));
loop ( From, To, By, Module, Fn, Ctx ) when From =< To ->
  loop(From + By, To, By, Module, Fn, Module:Fn(From, Ctx));
loop ( From, To, By, Module, Fn, Ctx ) ->
  _ = From, %match these against anything to suppress unused
  _ = To,
  _ = By,
  _ = Module,
  _ = Fn,
  Ctx.


% floor: returns the floor of X using trunc
floor ( X ) when X < 0 ->
  T = trunc(X),
  case X - T == 0 of
    true -> T;
    false -> T - 1
  end;
floor ( X ) ->
  trunc(X).

% rand ( seed ): seeds the random number generator with Seed
rand ( Seed ) ->
  fun ( ) ->
    X = 10000 * math:sin(Seed),
    {rand(Seed + 1), X - floor(X)}
  end.

% rand (Seed, int): returns a function that generates a random number from Lo to
%   Hi inclusive
rand ( Seed, int ) ->
  fun ( Lo, Hi ) ->
    X = 10000 * math:sin(Seed),
    {rand(Seed + 1, int), floor((X - floor(X)) * (Hi + 1 - Lo) + Lo)}
  end.

