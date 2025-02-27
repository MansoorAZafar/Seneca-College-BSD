# !!! Look at test_q6.py for more and proper testing !!!
from graph import Graph, Vertex
import math

# Heuristic + Cost so far
def evaluation(start, goal, g_n):
    """
    Returns the total cost for the node 
    
    Args:
        Start
            The current node you are at
        Goal
            The ending node desired to reach at the end
    
    Returns:
        the cost so far + the estimation of the remaining
    """
    # f(n) = Cost so far + Heuristic
    # f(n) = g(n) + h(n)
    #   g(n) = cost from start to node n  
    #       - THE COST SO FAR
    #   h(n) = estimate from node n to goal
    #       - THE ESTIMATED COST REMAINING
    return g_n + euclidean_distance(start, goal)

def euclidean_distance(a, b):
    """
    Returns the distance between 2 nodes in euclidean space

    Args:
        A:
            The starting point 
        B
            The ending point 

    Returns:
        the distance between b and a
    """
    return math.sqrt((b.x - a.x)**2 + (b.y - a.y)**2)

 
def Iterative_Deepening_AStar(start, goal):
    """
    Finds and returns the most optimal path and evaluated cost 
    between a starting point and a goal

    Args:
        Start: Vertex
            - The vertex to begin with
        Goal: Vertex
            - The vertex you want to go to

    Returns
        1. None, if the goal is impossible to reach
        2. (cost, path), a tuple that contains the cost of reaching the path and the actual path itself
    """
    if not isinstance(start, Vertex) or not isinstance(goal, Vertex):
        raise ValueError("Both start and goal should be Vertex Objects") 
    
    # this is equal to the f_n since g_n would be 0 right now
    threshold = euclidean_distance(start, goal)  

    # Iterative Deepening
    while True:
        stack = [(start, 0, [start])]
        
        # assign it to infinity becuase
        # no nodes have been considered / gone through yet at this iteration
        # the base state
        min_f_score = float('inf') 
        
        while stack:
            curr_node, g_n, path = stack.pop()
            f_score = evaluation(curr_node, goal, g_n)

            if f_score > threshold:
                # Threshold pruning
                #   - Skip this because its too expensive to search for
                #     in the current context
                # However, we now only consder paths that are too expensive
                min_f_score = min(f_score, min_f_score)
                continue

            if curr_node == goal:
                return g_n, path
            
            # Expand the neighbors
            for neighbor, weight in curr_node.adjacencies:
                if neighbor not in path: 
                    # If we haven't explored in within this branch
                    stack.append((neighbor, g_n + weight, path + [neighbor]))
                
        if min_f_score == float('inf'):
            # Node doesn't exist, get out
            return None
        threshold = min_f_score
        

if __name__ == "__main__":
    # !!! Look at test_q6.py for more and proper testing !!!
    # Create graph
    graph = Graph()
    a = Vertex('A', 0, 0)
    b = Vertex('B', 1, 0)
    c = Vertex('C', 0, 1)
    d = Vertex('D', 1, 1)

    # Adding edges to the graph
    graph.add_edge(a, b, 1)
    graph.add_edge(a, c, 4)
    graph.add_edge(b, c, 2)
    graph.add_edge(b, d, 5)
    graph.add_edge(c, d, 1)

    cost, path = Iterative_Deepening_AStar(a, d)

    print(f"Cost: {cost}")
    print("Path: ")

    for i in range(len(path) - 1):
        print(f"{path[i]} -> {path[i+1]}")

    # !!! Look at test_q6.py for more and proper testing !!!
    
