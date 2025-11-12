# Adaptive Cache Replacement Policy in SimpleScalar

## Overview

This project enhances the **SimpleScalar** simulator by implementing a **Dynamic Heuristic-Based Adaptive Cache Replacement Policy** for the cache. The new mechanism automatically switches between replacement strategies such as **LRU**, **FIFO**, **LFU**, **MRU**, and **Random** depending on runtime access behavior. This dynamic adaptation improves cache performance and reduces miss rates across different workloads.

---

## Core Concept

Traditional cache policies (e.g., LRU or FIFO) work well only under specific conditions. This project introduces a heuristic-based system that continuously monitors access behavior and selects the optimal policy at runtime.

### Heuristic Logic

The system tracks:

* **Sequential Accesses (seq_accesses)**
* **Reuse Accesses (reuse_accesses)**
* **Random Accesses (random_accesses)**

The policy is chosen using these ratios:

| Condition                              | Selected Policy |
| -------------------------------------- | --------------- |
| reuse_ratio > 0.6                      | LRU             |
| seq_ratio > 0.6                        | FIFO            |
| rand_ratio > 0.6                       | Random          |
| reuse_ratio > 0.35 && seq_ratio < 0.3  | LFU             |
| seq_ratio > 0.25 && reuse_ratio < 0.25 | MRU             |
| Default                                | LRU             |

Counters are decayed (halved) every 4096 accesses to maintain adaptivity.

---

## Installation and Setup

Ensure SimpleScalar (v3.0) is installed:

```bash
git clone https://github.com/toddmaustin/simplesim-3.0.git
cd simplesim-3.0
```

Removing old cache.c and cache.h file (assuming you are currently in `simplesim-3.0`):

```bash
rm cache.c cache.h
```

Adding new cahce.c and cache.h files, Assuming you cloned the Adaptive Cache Replacement Policy repository inside `simplesim-3.0`:

```bash
cp Adaptive_Cache_Replacement_Policy/config_cache/* .
```

Now build the simulator:

```bash
make clean && make
```

Example usage:

```bash
./sim-cache -cache:dl1 dl1:128:32:4:a tests/bin.little/test-fmath
```

Where:

* `dl1` = Level 1 data cache
* `a` = Adaptive replacement policy
* `128` = Number of lines in cache
* `32` = Block size in bytes
* `4` = 4-way set associative

Example for other policies:

```bash
-cache:dl1 dl1:128:32:4:l   # LRU
-cache:dl1 dl1:128:32:4:f   # FIFO
-cache:dl1 dl1:128:32:4:r   # Random
-cache:dl1 dl1:128:32:4:u   # LFU
-cache:dl1 dl1:128:32:4:m   # MRU
```

To run user-defined programs:

```bash
./sim-cache -cache:dl1 dl1:128:32:4:a Adaptive_Cache_Replacement_Policy/program/binary/out4
```

---

## Folder Structure

| Folder             | Description                                                        |
| ------------------ | ------------------------------------------------------------------ |
| `config_cache`     | Contains modified cache configuration files (`cache.c`, `cache.h`) |
| `plot`             | Contains performance plots for different benchmarks                |
| `report`           | Includes detailed report and analysis                              |
| `table`            | Contains benchmark statistics tables                               |
| `program`          | Includes user-defined program source and binaries                  |
| `workflow_diagram` | Contains system and policy workflow diagrams                       |

---

## Cache structure 
<img width="10084" height="932" alt="header_file" src="https://github.com/user-attachments/assets/c91a1f81-656b-4f4a-981e-e0fd690db3e4" />


## Workflow Diagram

The adaptive cache logic works as follows:
<img width="1627" height="4948" alt="main_logic" src="https://github.com/user-attachments/assets/110acc0a-3fea-49c9-a043-57665c219905" />



---

## Future Work

* Explore reinforcement learning (RL) or machine learning (ML)-based tuning

---

## Author

**Fenil Shah (25CS06020)**
**Priyanka Kundu (25CS06011)**

---

## References

1. N. Megiddo, D. Modha, *ARC: A Self-Tuning, Low Overhead Replacement Cache*, FAST 2003.
2. D. Patterson & J. Hennessy, *Computer Architecture: A Quantitative Approach*.
3. SimpleScalar: [http://www.simplescalar.com](http://www.simplescalar.com)
