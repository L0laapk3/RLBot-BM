# RLBot-BM

## What is RLBot-BM?

RLBot-BM is a library that replaces the critical path of [RLBot](https://rlbot.org/). 
It is build ontop of RLBot, and remains backwards compatible, but the input and output data is routed through bakkesmod instead.

RLBot-BM's approach has a number of advantages over RLBot:
* Tick perfect, no more dropped ticks when the framerate dips
* Exact tick information, no interpolated values at a random point between two ticks
* Zero-latency, bots can respond immediately in the next tick
* Guarantees with regards to minimum provided computation time for each tick (currently 4ms)
* The GameState is complete: it includes extra information not found in RLBot such as per wheel contact info and suspension distances
* Tick perfect state setting
<<<<<<< HEAD
* Dropshot tile data and rumble item type data
* Uses multiple hooks, bots get extra time while the game renders frames in parallel (NYI)
* Lockstep functionality that allows bots as much time as required to compute each tick without slowing the game to a crawl (NYI)

## Project status

**Working:**
* All of the above listed features except where stated otherwise
* Bot controls routed through RLBot-BM
* Gamestate data routed through RLBot-BM
* Statesetting routed through RLBot-BM
* Dropshot tile data
=======
* Dropshot tile data and rumble item type data (rumble TBD)
* Uses multiple hooks, bots get extra time while the game renders frames in parallel (TBD)
* Working lockstep functionality that allows bots as much time as required to compute each tick
* No need to handle and remember every single tick to keep a complete state, the tick packet includes timer information such as when cars were demolished

## Project status

All the features listed above, except the ones listed as TBD, are fully implemented and functional.
>>>>>>> d0c2bc677ebe946b3702a8705d1711bed82aab79

## Example bots
* **CPP**: [RLBot-BM_RLUtilitiesCPPExampleBot](https://github.com/L0laapk3/RLBot-BM_RLUtilitiesCPPExampleBot)
* **rust**: (no example bot yet, only a framework) [rlbot-bm-rust](https://github.com/LHolten/rlbot-bm-rust)
