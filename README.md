# DSA-Project-Mini-SHDRLU #A-star algorithm #A* algorithm 
Solving a simple mini SHDRLU board game, moving blocks to achieve a goal 
A random board can be (N*N) size and the max number of blocks is N*N-N (0 represents empty space)
Example: 
|  0 |  1 |  0 |
|  4 |  2 |  0 |
|  6 |  5 |  3 |
A block can be moved on top of the other blocks (wherever having space)
A sample legal move is block 3 can be moved on top of block 4, col 2 -> col 0.
|  3 |  1 |  0 |
|  4 |  2 |  0 |
|  6 |  5 |  0 |

An atom goal is the goal where the target block must be placed in a (row,col) position (row: bottom up, col: left right)
A random board size 3*3 with number of blocks = 6

|  1 |  0 |  0 |
|  2 |  0 |  4 |
|  3 |  5 |  6 |
block: 4, goal: (0,1)
will be solved in the following steps: 
col 2 -> col 1:
|  1 |  0 |  0 |
|  2 |  4 |  0 |
|  3 |  5 |  6 |

col 0 -> col 2:
|  0 |  0 |  0 |
|  2 |  4 |  1 |
|  3 |  5 |  6 |

col 1 -> col 2:
|  0 |  0 |  4 |
|  2 |  0 |  1 |
|  3 |  5 |  6 |

col 1 -> col 0:
|  5 |  0 |  4 |
|  2 |  0 |  1 |
|  3 |  0 |  6 |

col 0 -> col 1:
|  5 |  0 |  0 |
|  2 |  0 |  1 |
|  3 |  4 |  6 |
Found in 5 steps!
