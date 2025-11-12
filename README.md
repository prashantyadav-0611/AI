# AI
**LAB -1**
**Problem 1.1:** Breadth-First SearchAim: To implement the Breadth-First Search algorithm.
Working of Code: This C program implements the Breadth-First Search (BFS) algorithm for solving the classic 8-puzzle problem. The BFS strategy is to systematically explore all possible states (configurations of tiles) level by level, beginning from the initial state4. The program uses a queue data structure to manage the states that need to be visited, ensuring that states closer to the start are explored first5. Each state in the puzzle is represented by a $3 \times 3$ array of integers, and the code includes utility functions to check if a state is the goal state or if it has already been visited6. The core logic involves finding the position of the blank tile (0), generating all valid neighbor states by sliding the blank tile, and adding these new, unvisited states to the queue. By strictly adhering to the level-by-level traversal of the state space, this implementation guarantees that the shortest path (minimum number of moves) to reach the goal configuration is found first, if a solution exists.

**Output**
<img width="315" height="240" alt="Screenshot 2025-11-12 192818" src="https://github.com/user-attachments/assets/3ae38ef6-7f4e-4ac6-b500-c04464c43143" />

**Time Complexity:** $O(V + E)$ 
**Space Complexity:** $O(V)$ 


**Problem 1.2:** Depth-First SearchAim: To implement the Depth-First Search algorithm.
Working of Code: This C program implements the Depth-First Search (DFS) algorithm to solve the 8-puzzle problem, offering an alternative state-space search approach13. DFS fundamentally explores one branch of the search tree as deep as possible before needing to backtrack14. The implementation utilizes a stack structure to manage the states to be explored, naturally facilitating the deep, recursive-like traversal of the state space15. States are explored by finding the blank tile and generating valid successor states, which are then pushed onto the stack if they have not been visited16. A critical component in this implementation is the depth limit (MAX_DEPTH), which is set to prevent the search from running indefinitely in infinite or very long branches17. The search continues by popping the most recently pushed state and examining its successors until the goal configuration is reached or the depth limit is hit18. This method is memory efficient but does not guarantee finding the shortest path.
**Output**
<img width="363" height="241" alt="Screenshot 2025-11-12 192926" src="https://github.com/user-attachments/assets/e4b29a9d-903a-4983-9d9f-044cb3bc3268" />

**Time Complexity:** $O(V + E)$ 
**Space Complexity:** $O(V)$ 


**Problem 1.3:** Best First SearchAim: To implement the Best First Search algorithm.
Working of Code: This program uses the Best-First Search strategy, an informed search technique, for solving the 8-puzzle problem23. Unlike uninformed searches, it uses a heuristic function to estimate the cost from the current state to the goal state24. The specific heuristic used here is the "misplaced tiles" count, which calculates how many tiles are not in their final position25. The algorithm manages its search using a priority queue, which is crucial for always selecting the state with the lowest heuristic cost as the next state to explore2626. This greedy approach effectively guides the search directly towards the goal, improving search efficiency compared to BFS or DFS. States are continuously generated, their heuristic cost is computed, and they are added to the priority queue until the goal state (where misplaced tiles equals zero) is found.
**Output**
<img width="296" height="241" alt="Screenshot 2025-11-12 192506" src="https://github.com/user-attachments/assets/a16a3244-9e1c-4498-b927-c2193cff7915" />

**Time Complexity:** $O(E \log V)$ 
**Space Complexity:** $O(V)$ 


**Problem 1.4:** Hill ClimbingAim: To implement the Hill Climbing algorithm31.
Working of Code: This program applies the Hill Climbing algorithm, a local search technique, to solve the 8-puzzle problem32. It operates by starting at an initial state and iteratively moving to a neighboring state that has a strictly better (lower) heuristic value33. The heuristic function used is the misplaced tiles count, aiming to reduce this count with every move34. At each step, the algorithm generates all possible successor states and chooses the single best neighbor—the one that minimizes the misplaced tiles count the most35. The process is greedy; it only looks one step ahead and does not maintain a list of visited states36. The algorithm terminates when the goal state (cost 0) is reached, or when it reaches a state where no neighboring state has a better heuristic value37. This termination point may be a goal state, but it is often a local optimum or local minima, a known limitation of the Hill Climbing approach.
**Output**
<img width="296" height="241" alt="Screenshot 2025-11-12 192506" src="https://github.com/user-attachments/assets/885e1b5b-0e13-47fd-a7a6-14f200aaf6b8" />

**Time Complexity:** $O(b^d)$ 
**Space Complexity:** $O(bd)$

**LAB - 2**
**Problem 2.1:** A* SearchAim: To implement the A* Search algorithm42.
Working of Code: This program implements the A* Search algorithm, a powerful and highly efficient informed search algorithm, applied here to a pathfinding problem on a grid43. A* is distinguished by its use of the evaluation function $f(n) = g(n) + h(n)$ to choose which node to explore next44. Here, $g(n)$ is the actual cost (distance) from the start node to the current node $n$, and $h(n)$ is the heuristic cost (estimated distance) from $n$ to the goal node, calculated using the Manhattan distance454545. The implementation uses a Min-Heap to act as a priority queue, efficiently allowing the algorithm to consistently select the node with the minimum $f$-value. By combining the path cost already taken and an admissible heuristic estimate, A* guarantees the discovery of an optimal path (shortest path) from the source to the destination, assuming a consistent heuristic47. Obstacles ("water cells") are handled by assigning them an infinite heuristic cost, thus preventing the algorithm from exploring them.
**Output**
<img width="414" height="231" alt="Screenshot 2025-11-12 194216" src="https://github.com/user-attachments/assets/b18a93ff-f00c-4369-9c17-29b4d9f09342" />
<img width="229" height="230" alt="Screenshot 2025-11-12 194236" src="https://github.com/user-attachments/assets/5c07de7f-f947-4632-aade-0c0ceb29bc7c" />

**Time Complexity:** $O(E)$ 
**Space Complexity:** $O(V)$ 


**Problem 2.2:** Water Jug ProblemAim: To implement the Water Jug Problem algorithm52.
Working of Code: This program provides a solution for the classic Water Jug Problem by employing a state-space search approach, specifically using a recursive Depth-First Search (DFS) implementation535353. The state space is defined by the current water levels in the two jugs, represented as a pair $(j1, j2)$54. The key to the solution lies in systematically exploring all possible valid operations from any given state: filling either jug completely, emptying either jug, and pouring water from one jug to the other until the receiving jug is full or the source jug is empty55. The code uses a 2D array, visited[MAXCAP+1][MAXCAP+1], to efficiently track and avoid re-exploring states already visited, preventing infinite loops56565656. The recursive dfs function explores these possibilities, recording each step in the path array until the is_goal condition (reaching the target water amount in the specified jug) is met, at which point the sequence of steps is printed as the solution57575757.
**Output**
<img width="538" height="94" alt="Screenshot 2025-11-12 194446" src="https://github.com/user-attachments/assets/0b09c82e-8820-44fa-87be-db541d07fe04" />
<img width="538" height="94" alt="Screenshot 2025-11-12 194446" src="https://github.com/user-attachments/assets/973e3a48-37cb-41b9-b6b8-05c9527081d2" />

**Time Complexity:** $O(V + E)$ 
**Space Complexity:** $O(V)$ 


**LAB - 3**
**Problem 3.1:** Chess Minimax InterfaceAim: To implement the Chess Minimax Interface algorithm61.
Working of Code: This Python program creates a functional, graphical Chess game interface using the tkinter library and implements a computer opponent utilizing the Minimax search algorithm with Alpha-Beta Pruning62626262. The core of the AI is the alpha_beta function, which recursively explores the game tree to a specified depth (controlled by the user's difficulty selection)63636363. The search is guided by the evaluate_board function, a static evaluation heuristic that assigns a numerical score to a board state, primarily based on the material advantage (piece values), with checkmate being the highest priority64. The Minimax logic ensures the computer (the maximizing player) chooses the move that yields the highest score, assuming the opponent (the minimizing player) plays optimally65. Alpha-beta pruning is employed to dramatically reduce the number of nodes evaluated, making the search computationally feasible by cutting off branches that cannot possibly lead to a better result for the current player.
**Output**
<img width="335" height="158" alt="Screenshot 2025-11-12 194734" src="https://github.com/user-attachments/assets/97a8f1c4-6d75-497f-bfd4-76b026c20a15" />
<img width="609" height="643" alt="Screenshot 2025-11-12 194818" src="https://github.com/user-attachments/assets/baaff052-f557-4fcd-b00a-73b28dca87b3" />

**Time Complexity:** $O(b^d)$ 
**Space Complexity:** $O(bd)$ 


**Problem 3.2:** Minimax AlgorithmAim: To implement the Minimax Algorithm algorithm70.
Working of Code: This C program implements the fundamental Minimax algorithm to serve as the AI logic for a game of Tic-Tac-Toe on a $3 \times 3$ board71. The algorithm's function, generate_tree, recursively explores the entire game tree from the current state to determine the best possible move for the AI (maximizing player, 'X')72727272. For each possible move, it simulates the outcome, assuming the opponent (minimizing player, 'O') will always choose the move that minimizes the AI's score73737373. The get_score function acts as the utility function, providing a terminal value: $+1$ if 'X' wins, $-1$ if 'O' wins, and $0$ for a draw74747474. Since Tic-Tac-Toe is a finite, deterministic, perfect-information game, Minimax, by exploring the entire tree (or up to a goal state), guarantees the optimal move75. The find_best_move function iterates through all legal moves to find the one that returns the maximum Minimax value from the subsequent tree traversal.
**Output**
<img width="398" height="522" alt="Screenshot 2025-11-12 195045" src="https://github.com/user-attachments/assets/f32d2757-e77c-45d5-b2a8-8b9076434673" />

<img width="358" height="300" alt="Screenshot 2025-11-12 195308" src="https://github.com/user-attachments/assets/6aabf866-4544-4c84-a692-ed4fa6c9b5e3" />

**Time Complexity:** $O(b^d)$ 
**Space Complexity:** $O(bd)$ 


**LAB - 4**
**Problem 4.1:** Monkey and Banana ProblemAim: To implement the Monkey and Banana Problem algorithm80.
Working of Code: This Prolog program models and solves the classic Monkey and Banana Problem using its built-in logical reasoning and inference engine81. The problem is defined by the initial state and the goal state82. The state is represented as a fact: state(MonkeyPos, MonkeyStatus, BoxPos, HasBanana)83. The heart of the program is the set of move rules, which define the four possible actions: walk(M, N), push(P, N), climb, and grasp84. Each rule specifies the preconditions (the current state) and the effects (the resulting state) of the action85. The search predicate utilizes Prolog's depth-first nature and backtracking to recursively find a sequence of actions that transition from the initial state to the goal state86868686. It includes a check to ensure that the search does not enter a loop by revisiting a state already encountered in the current path. Once the can_get_banana predicate triggers a successful search, the resulting Plan (sequence of actions) is printed.
**Output**
<img width="556" height="287" alt="Screenshot 2025-11-12 195555" src="https://github.com/user-attachments/assets/af7e2e9d-2652-43d7-a1df-5ac96ca16116" />

**Time Complexity:** $O(b^d)$ 
**Space Complexity:** $O(bd)$ 


**Problem 4.2:** Word Block ProblemAim: To implement the Word Block Problem algorithm92.
Working of Code: This Prolog program is designed to solve the Word Block Problem, a type of planning problem where the goal is to arrange blocks of letters to form a target word or configuration93. The state of the world is defined by a list of facts, such as on(X, Y) (block $X$ is on block $Y$) and clear(X) (the top of block $X$ is clear). The goal predicate defines the desired final configuration of the block. The move rule is the operational core, specifying the preconditions for moving a block (the block to be moved and the destination must be clear) and how the state list is updated by deleting old facts and asserting new ones. The plan predicate implements a recursive, depth-first planner that searches for a sequence of valid moves that transform the initial_state into a state that satisfies all goal conditions. Prolog's backtracking is used to efficiently test different move sequences, and a Visited list prevents the program from cycling infinitely by revisiting states.
**Output**
<img width="139" height="35" alt="Screenshot 2025-11-12 201348" src="https://github.com/user-attachments/assets/ceb311bd-d101-47dc-ba98-eaff9c69818b" />
<img width="646" height="587" alt="Screenshot 2025-11-12 201414" src="https://github.com/user-attachments/assets/dead44c0-1788-40db-8c5b-5d00015097be" />
<img width="601" height="475" alt="Screenshot 2025-11-12 201606" src="https://github.com/user-attachments/assets/c5133fc7-d5ec-4737-b85e-da71e11c668a" />

**Time Complexity:** $O(n!)$ 
**Space Complexity:** $O(n)$ 101
