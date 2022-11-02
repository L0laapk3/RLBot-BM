# RLBot-BM

## What is RLBot-BM?

RLBot-BM is a library that replaces the critical path of [RLBot](https://rlbot.org/). 
It is build ontop of RLBot, and remains backwards compatible, but the input and output data is routed through bakkesmod instead.

RLBot-BM's approach has a number of advantages:
* Tick perfect, no more dropped ticks when the framerate dips
* Zero-latency, bots can respond immediately in the next tick
* Guarantees with regards to minimum provided computation time for each tick (currently 4ms)
* The GameState is complete: it includes extra information not found in RLBot such as individual wheel contact and suspension distance
* Tick perfect state setting
* Dropshot tile data and rumble item type data (rumble TBD)
* Uses multiple hooks, bots get extra time while the game renders frames in parallel (TBD)
* Working lockstep functionality that allows bots as much time as required to compute each tick
* A single ticks information describes the complete (including jump timers, etc) game state on its own, no need to handle every tick and remember things from previous ticks

## Project status

All the features listed above, except the ones listed as TBD, are fully implemented and functional.

## Example bots:
* **CPP**: [RLBot-BM_RLUtilitiesCPPExampleBot](https://github.com/L0laapk3/RLBot-BM_RLUtilitiesCPPExampleBot)
