# AISD2
# Lifts and mountains

## Problem description
The goal of the task is to find the **shortest route** through a given terrain described as a rectangular grid of cells. 
Each cell has a height expressed as a non-negative integer.  

The time of moving between cells depends on the height difference:
- ⬆️ **If A > B** (we go higher): time = `A - B + 1` minutes.`  
- ⬇️ **If A ≤ B** (we go down or move on flat ground): time = `1` minute.  

We can move only to edge-adjacent cells (at most four directions).
We cannot leave the map.

Additionally, there may be **lifts** in the area:
- Each lift leads from one cell to another (one-way)  
- Using a lift takes a specified amount of time.  
- The lift operates at a fixed minute interval. If we reach the starting cell at time `t`, and the nearest ride is at time `k`, we must wait `(k - t)` minutes, and then add the travel time. 

Example:
If we are at the lift’s starting cell at **minute 8**, the lift runs every **5 minutes**, and the ride lasts **3 minutes**, then we will reach the destination cell at **minute 13** (8 + 2 waiting + 3 riding).

---

## 📥 Input
The input provides, in order:
1. The width and height of the map.
2. The starting position (column, row).
3. The destination position (column, row).  
4. The number of lifts.  
5. Descriptions of the lifts – for each:
   - starting position (column, row),  
   - destination position (column, row), 
   - travel time in minutes,  
   - departure interval (runs every X minutes).  
6. Heights of all map cells.  

All values are non-negative.
---

## 📤 Output
You must print the **shortest time** needed to reach the destination point from the starting point.

---

## 🔍 Example 1
**Input**

9 8 0 0 8 7 0<br>
0 0 0 0 0 0 0 0 8<br> 
0 9 9 9 9 9 9 9 0<br>  
0 1 0 1 0 0 0 9 0<br> 
0 9 0 0 0 1 0 9 0  <br>
0 9 1 1 1 1 0 9 0  <br>
0 9 0 0 0 0 0 9 0  <br>
0 9 9 9 9 1 9 9 0  <br>
8 0 0 0 0 0 0 0 0 <br>

**Output**

18

