#!/bin/sh

erl -noshell -eval "main:main($1)." # -s erlang halt

