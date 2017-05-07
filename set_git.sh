#!/bin/bash

path=$(eval git rev-parse --show-toplevel)
export GIT_HOME=$path
echo $GIT_HOME
