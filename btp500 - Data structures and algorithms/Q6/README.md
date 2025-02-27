# Iterative Deepening A* (IDA*)

Table of Contents:

    1. Explaination 
    2. Testing 

## Explaination
Firstly, I added an x and y property to the Vertex class to easily implement the euclidean space heuristic. 

![{4931784E-D5C6-48F6-B81A-7CA055737226}](https://github.com/user-attachments/assets/f333c646-8d16-4ebd-82b7-c5e83c04aa82)

Then, I made a function to actually calculate euclidean distance, which is as simple as following the formula:

$$\sqrt{(x_2 - x_1)^2 + (y_2 - y_1)^2}$$

Afterwords, I simply implemented the actual evaluation method, this just added g(n) (the running cost) + the heuristic cost h(n), or in this case, the euclidean distance from the current node to the goal node.

```python
def evaluation(start: Vertex, goal: Vertex, g_n):
    return g_n + euclidean_distance(start, goal)
```

Then I started with the actual IDA* implemention. To implement it, I started by assigning the defalt threshold to the euclidean distance from the given starting node and the given goal node. The reason why it's the euclidean distance is because the running cost or g(n) is 0 so it wouldn't matter and my evaluation function, needs g(n) as a parameter.
```python
threshold = euclidean_distance(start, goal)
```

Then I looped until a soltuion was found, also known as iterative deepning!!! (wow). Within this loop, I used a stack-ish design to hold the nodes that I will checking. The start starts off with just the root, this will be re-initalized with just the root everytime we begin the deepening. Then I create a variable to hold the minimum f_score I can get for each branch's f_score suprasses the threshold. This helps it not take too much a big step in the threshold and makes the increase not too drasticially high. 
```python
 stack = [(start, 0, [start])]
 min_f_score = float('inf') 
```

Then, we check, while there are items in the stack, we get the front, get it's f_score and check 2 things
1. is the f(n) of the current node greater than the threshold?
2. if the current node the goal node

If yes to the first one, then we want to use "threshold pruning", basically, we're going to skip it for now because its too expensive to search for however, we'll keep it in mind by assigning our minimum f(n) to this branch's f(n) if its lower than the current minimum.
```python
 if f_score > threshold:
     min_f_score = min(f_score, min_f_score)
     continue
```

If yes to the 2nd condition, just return the cost so far [g(n)] and the path we've accumulated.
```python
if curr_node == goal:
    return g_n, path
```

If neither of these are true, we just expand the node, and if we haven't already visited the node within this context then we add it to the stack
```python
for neighbor, weight in curr_node.adjacencies:
    if neighbor not in path: 
        stack.append((neighbor, g_n + weight, path + [neighbor]))
```

Finally, if the minimum f(n) score is still infinity from our initialization all the way at the start of the iterative deepening loop, then that means the node we want, is impossible so just return None. However, if it's not, then we assign our threshold to the minimum f(n) we need.
```python
if min_f_score == float('inf'):
    return None
threshold = min_f_score
```

## Testing
The way I tested this with your graph of
```python
graph = Graph()
    # Constructing some nodes
    a = Vertex('A')
    b = Vertex('B')
    c = Vertex('C')
    d = Vertex('D')
    # Connecting them in the graph
    graph.add_edge(a, b, 1)
    graph.add_edge(a, c, 4)
    graph.add_edge(b, c, 2)
    graph.add_edge(b, d, 5)
    graph.add_edge(c, d, 1)
```
![{001E90BE-9454-40F3-87F2-BA5FBEBAABCE}](https://github.com/user-attachments/assets/5c2e6fe8-9f4e-4ca6-ab96-d9164356dcde)

Was by testing if my algorithm could give me the optimal path for not only going the longest path, Node A -> Node D but also if it could work in the other way, Node C -> Node A and of course, if it worked 
with just one node to itself, Node A -> Node A. So basically, I tested if it works backwords, forwards and no direction.

![{739642DC-7F71-4684-9100-2BA7FBF45904}](https://github.com/user-attachments/assets/9eaf0a8b-db33-421f-9140-27d83fe200dd)
