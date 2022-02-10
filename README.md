# RLBot-BM_Lib

## What is RLBot-BM_Lib?

RLBot-BM_Lib is a library that replaces the critical path of [RLBot](https://rlbot.org/). 
It is build ontop of RLBot, and remains backwards compatible, but the input and output data is routed through bakkesmod instead.

This has a number of advantages:
* Tick perfect, no more dropped ticks when the framerate dips
* Zero-latency mode
* Guarantees with regards to minimum provided computation time for each tick
* Extra information is provided such as per wheel contact information
* Working lockstep functionality that allows bots as much time as required to compute each tick (NYI)
* Tick perfect state setting (NYI)

## Project status

**Working:**
* Bot controls routed through RLBot-BM
* All of the above listed features except where stated otherwise

**In progress:**
* Game date routed through RLBot-BM

**Planned:**
* Replace RLBot state setting
