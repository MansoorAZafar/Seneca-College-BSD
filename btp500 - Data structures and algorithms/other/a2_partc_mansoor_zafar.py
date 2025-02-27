# Main Author: Mansoor & Kosta 
# Main Reviewer:

from a1_partd import overflow
import random

# This function duplicates and returns the board. You may find this useful
def copy_board(board):
        current_board = []
        height = len(board)
        for i in range(height):
            current_board.append(board[i].copy())
        return current_board


def same_sign(a, b):
    """
        Returns if a and b are the same sign or not

        Args:
            a:
                - the first value
            b:
                - the second value
        
        Returns:
            - True if a & b are the same sign else False
    """
    return (a*b) >= 0


# This function is your evaluation function for the board
def evaluate_board(board, player):
	"""
	Gives a score to the given board based on the absolute sum of the pieces of PLAYER
		- if there is a win or loss
			- a WIN or LOSS value will be assigned through 1000, -1000 respectively

	Args:
		Board:
			- The current state of the board that will be evaluated
		Player:
			- The one being evaluated 

	Returns:
		the score for the given player
	"""
	# Abs(x) not 0 -> how many numbers pieces in that cell
	# sign indicates player -> + = player 1 | - = player 2
	# Return the score of the board
	score: int = 0
	winner = True
	first_non_zero_value = None

	# Find if there is a winner within the loop and also add on the score to the player
	for row in range(len(board)):
		for col in range(len(board[0])):
			n = board[row][col]

			if n == 0: continue 

			if not first_non_zero_value:
				first_non_zero_value = n
			elif not same_sign(first_non_zero_value, n):
				winner = False
			
			if same_sign(n, player):
				score += abs(n)
			else:
				score -= abs(n)

	return score if not winner else 1000 \
			if same_sign(first_non_zero_value, player) else -1000 


class GameTree:
    """
    A decision tree that will create a tree a tree containing the best 
    possible moves to make given a certain board
    """

    class Node:
        def __init__(self, board, depth, player, tree_height = 4):
            """
                Initializes a node containing the state of a board

                Args:
                    Board
                        - the current state of the board 
                    Depth
                        - The current level in which the board resides
                    Player
                        - The player who made a move on this board
                    Tree_Height
                        - the maximum height the tree is allowed to reach
                
                Returns: N/A
            """
            self.board = board
            self.depth = depth
            self.player = player 
            self.tree_height = tree_height
            
            self.children = []
            self.move = (0,0)


        def is_terminal(self) -> bool:
            """
                Returns if the current board has ended because either
                someone has won or the max depth has been reached

                Args:
                    None
                
                Returns:
                    True or False depending on the state of the board
            """
            return abs(evaluate_board(self.board, self.player)
                       ) == 1000 or self.depth >= self.tree_height
            

    def __init__(self, board, player, tree_height = 4):
        """
            Initializes the actual game/decision tree and its root node

            Args:
                Board
                    - the base state of the board
                Player
                    - the current player who will be making a move
                Tree_height
                    - The maximum height the tree is allowed to reach
            
            Returns: N/A
        """
        self.player = player
        self.board = copy_board(board)
        self.MAX_SUBTREES = 7

        # The root is the board before our player makes a move
        #   -> So we temporarily change the root's player to the opposite one
        #       -> So we can build the tree, starting with the 'next player'
        #           or in this case, starting with the desired player
        player_old = -1 if player == 1 else 1
        self.root = self.Node(board, 0, player_old, tree_height)
        

        self.build_tree(self.root)
        self.root.player = player

    def build_tree(self, node):
        """
            Recursively builds the tree with the top 7 most highly rated moves in each level

            Args:
                Node
                    - The current state of the game
            Returns: N/A                
        """

        if not node.is_terminal():
            valid_moves_scores = []    
            next_player = -1 if node.player == 1 else 1
            
            for move in self.valid_moves(node.board, next_player):
                new_board = copy_board(node.board)
                self.make_move(new_board, move, next_player)

                move_score = evaluate_board(new_board, next_player)
                child = self.Node(new_board, node.depth + 1, next_player)
                child.move = move

                valid_moves_scores.append((move_score, child))
            
            best_moves = sorted(valid_moves_scores, key=lambda x: x[0], reverse=True)[:self.MAX_SUBTREES]

            for _, child in best_moves:
                node.children.append(child) # Only add the top 7 best subtrees
                self.build_tree(child)
    
    def get_move(self): 
        """
            Either returns the best move player A can make OR the
            worst move player A can make
        """  
        # Select the move based on the worst one for the opponent 
        # This in turn can also be the 'best' move for the player (if applicable)
        best_move = None
        best_score = None
        best_moves = []
        worst_opponent_score = float('inf')

        for child in self.root.children:
            # Basically, we get the lowest possible maximum score for the opponent
            # and choose that move as our desired one
            #   - We are choosing the most optimal move even if our opponent picks
            #     their best move in response
            opponent_score = max(self.alpha_beta_pruning(grandchild) for grandchild 
                                 in child.children) if child.children else float('-inf')

            if opponent_score == float('-inf'):
                # End the iteration early, no need to check anymore subtrees
                # avoids running minimax anymore 
                return child.move 

            if opponent_score < worst_opponent_score:
                worst_opponent_score = opponent_score
                best_score = opponent_score

                best_moves.append((child.move, opponent_score))
                best_move = child.move
        
        if any(x[1] != best_score for x in best_moves):
            # If there is a best move, pick it
            return best_move
        # If all the moves have the same score, pick a random move
        return random.choice(best_moves)[0]
        
    
    def minimax(self, node):
        """
            Maximize player 1's if first player, otherwise, Minimize 
            player 1's score if player 2 
            
            Args:
                node:
                    - the current subtree that is being evaluated 
            
            Returns:
                - The worst score for the opponent
        """
        # The max score for positive player is 1000
        # The max score for a negative player is 1000
        if not node.children:
            return evaluate_board(node.board, node.player)

        if node.player == 1:
            # Maximize this players score
            return max(self.minimax(child) for child in node.children)
        else:
            # Minimize the opposite player's score
            return min(self.minimax(child) for child in node.children)


    def alpha_beta_pruning(self, node, alpha=float('-inf'), beta=float('inf')):
        """
            Returns the most optimal play to play assuming the opponent also picks 
            their best play

            Args:
                Node
                    - The current node being evaluated
                Alpha
                    - The best score possible by maximizing the player so far
                Beta
                    - the best score possible by minimizing the player so far
            
            Returns:
                - the optimal score for the player
        """
        if not node.children:
            return evaluate_board(node.board, node.player)

        if node.player == 1:
            # Maximize player
            maxEval = float('-inf')
            for child in node.children:
                eval = self.alpha_beta_pruning(child, alpha, beta)
                maxEval = max(maxEval, eval)
                alpha = max(alpha, eval)

                # Opponent will ignore this path because its less optimal
                # for them, they have a path worse for you already
                if beta <= alpha:
                    break
            return maxEval
        else:
            minEval = float('inf')
            #Minimize player
            for child in node.children:
                eval = self.alpha_beta_pruning(child, alpha, beta)
                minEval = min(minEval, eval)
                beta = min(beta, eval)

                # Player already has chosen a better path
                if beta <= alpha:
                    break
            return minEval

        
    def clear_tree(self):
        """
            Will clear the tree using a Breadth-first-search approach by adding the nodes
            into the queue and linearly deleting them
        """
        que = [self.root]
        while que:
            curr_node = que.pop(0)
            
            if curr_node.children:
                que.extend(curr_node.children)

            curr_node.children = None
            del(curr_node)

        self.root = None

        
    def valid_moves(self, board, player):
        """
            Creates a list of tuples that the player can make.
            A move is valid IF
                1. it is a 0 
                OR
                2. The desired index shares the same sign as the player

            Args:
                Board:
                    - the current state of the board to be evaluated
                Player:
                    - the desired entity to find possible moves for
            
            Returns:
                a list of tuples that contain the row and column for possible moves
        """
        return [(row,col) for row in range(len(board)) 
                for col in range(len(board[0])) if same_sign(board[row][col], player)]

    
    def make_move(self, board, move, player):
        """
            Adds 1 at the desired move and then overflows,
            then ensures only the result of the overflow is in the queue

            Args:
                Board:
                    - the current state of the board that will be modifed
                Move:
                    - the row and column tuple that contains the indicies for the play
                Player:
                    - the entity that will actually make the move 
        """
        
        i,j = move
        board[i][j] = (abs(board[i][j]) + 1) * player
        overflow(board, None)
