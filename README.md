# RLBot-BM
<p align="center">
<img src="https://user-images.githubusercontent.com/6313423/214428677-3add4ab6-f974-4467-a35d-de0e7bd01e58.png" width="300px" />
</p>

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
* Dropshot tile data
* Rumble item type and timing data
* Uses multiple hooks, bots get extra time while the game renders frames in parallel (TBD)
* Working lockstep functionality that allows bots as much time as required to compute each tick
* No need to handle and remember every single tick to keep a complete state, the tick packet includes timer information such as when cars were demolished

## Project status

All the features listed above, except the ones listed as TBD, are fully implemented and functional.

### Known issues

* isRumble bit is always false

## Example bots
* **CPP**: [RLBot-BM_RLUtilitiesCPPExampleBot](https://github.com/L0laapk3/RLBot-BM_RLUtilitiesCPPExampleBot)
* **rust**: [rlbot-bm-rust](https://github.com/LHolten/rlbot-bm-rust)
