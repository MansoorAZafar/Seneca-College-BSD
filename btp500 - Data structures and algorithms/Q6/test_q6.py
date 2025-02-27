import unittest
from Q6 import Iterative_Deepening_AStar
from graph import Graph, Vertex

class IDAStarTestCase(unittest.TestCase):
    
    @classmethod
    def setUpClass(cls):

        # Setup of the basic graph from graph.py        
        #region GRAPH A INIT
        """
        (A COORDS = {x: 0, y: 0})

        0 D 
        A B 
        C 0 
        """
        cls.graph_a = Graph()
        cls.a = Vertex('A', 0, 0)
        cls.b = Vertex('B', 1, 0)
        cls.c = Vertex('C', 0, 1)
        cls.d = Vertex('D', 1, 1)
        # Connecting them in the graph
        cls.graph_a.add_edge(cls.a, cls.b, 1)
        cls.graph_a.add_edge(cls.a, cls.c, 4)
        cls.graph_a.add_edge(cls.b, cls.c, 2)
        cls.graph_a.add_edge(cls.b, cls.d, 5)
        cls.graph_a.add_edge(cls.c, cls.d, 1)
        #endregion

        # setup of random graph online
        #region GRAPH B INIT
        # REFERENCE 
        #   https://media.geeksforgeeks.org/wp-content/uploads/20230223140425/mst1drawio.png
        # 
        """
        0 COORDS = {x: 0, y: 0}

        . 1 2 3 .
        0 . 8 . 4
        . 7 6 5 .
       
        
        """
        cls.graph_b = Graph()
        cls._0 = Vertex('0', 0, 0)
        cls._1 = Vertex('1', 1, 1)
        cls._2 = Vertex('2', 2, 1)
        cls._3 = Vertex('3', 3, 1)
        cls._4 = Vertex('4', 0, 4)
        cls._5 = Vertex('5', 3, -1)
        cls._6 = Vertex('6', 2, -1)
        cls._7 = Vertex('7', -1, -1)
        cls._8 = Vertex('8', 2, 0)
        # Connecting them in the graph
        cls.graph_b.add_edge(cls._0, cls._1, 4)
        cls.graph_b.add_edge(cls._0, cls._7, 8)

        cls.graph_b.add_edge(cls._1, cls._2, 8)
        cls.graph_b.add_edge(cls._1, cls._7, 11)

        cls.graph_b.add_edge(cls._2, cls._3, 7)
        cls.graph_b.add_edge(cls._2, cls._5, 4)
        cls.graph_b.add_edge(cls._2, cls._8, 2)

        cls.graph_b.add_edge(cls._3, cls._4, 9)
        cls.graph_b.add_edge(cls._3, cls._5, 14)
        
        cls.graph_b.add_edge(cls._4, cls._5, 10)
        
        cls.graph_b.add_edge(cls._5, cls._6, 2)
        
        cls.graph_b.add_edge(cls._6, cls._8, 6)
        cls.graph_b.add_edge(cls._6, cls._7, 1)
        
        cls.graph_b.add_edge(cls._7, cls._8, 7)
        #endregion
        
        # setup of random graph online
        #region GRAPH C INIT
        # Reference
        #   https://www.programiz.com/sites/tutorial2program/files/pa_6.png
        #
        cls.graph_c = Graph()
        """
        C COORDS = {x: 0, y: 0}

        A 0 D 0
        0 C 0 F 
        B 0 E 0
        """
        cls.a2 = Vertex('A', -1, 1)
        cls.b2 = Vertex('B', -1, -1)
        cls.c2 = Vertex('C', 0, 0)
        cls.d2 = Vertex('D', 1, 1)
        cls.e2 = Vertex('E', 1, -1)
        cls.f2 = Vertex('F', 2, 0)

        cls.graph_c.add_edge(cls.a2, cls.c2, 4)
        cls.graph_c.add_edge(cls.b2, cls.c2, 2)
        cls.graph_c.add_edge(cls.c2, cls.d2, 3)
        cls.graph_c.add_edge(cls.c2, cls.e2, 2)
        cls.graph_c.add_edge(cls.e2, cls.f2, 3)
        #endregion
        

    def test_bad_ida_star_types(self):
        """
        Passing in a non vertex object as either 1 or both of 
        the arguments should raise a ValueError.
        """
        with self.assertRaises(ValueError) as cm:
            Iterative_Deepening_AStar("Arg1 not a Vertex", Vertex('Arg2 Is a Vertex'))
        self.assertEqual(str(cm.exception), "Both start and goal should be Vertex Objects")

        with self.assertRaises(ValueError) as cm:
            Iterative_Deepening_AStar(Vertex("Arg1 is A Vertex"), 'Arg2 Is NOT a Vertex')
        self.assertEqual(str(cm.exception), "Both start and goal should be Vertex Objects")

        with self.assertRaises(ValueError) as cm:
            Iterative_Deepening_AStar("Arg1 not a Vertex", 'Arg2 Is not a vertex either lmao')
        self.assertEqual(str(cm.exception), "Both start and goal should be Vertex Objects")


    def test_impossible_graphs(self):
        """
        This test case tests for impossible cases, the 
        search algorithm should always return None, since it'll
        be impossible
        """
        impossible_vertex = Vertex('Z')
        impossible_vertex_2 = Vertex('Impossible')

        # Testing from Graph A
        # "walrus operator" is a crazy name for :=
        self.assertEqual(res := (Iterative_Deepening_AStar(self.a, impossible_vertex)), None, 
                         f"Vertex is impossible, should return None, {res} was returned")

        self.assertEqual(res := (Iterative_Deepening_AStar(impossible_vertex_2, self.c)), None, 
                         f"Vertex is impossible, should return None, {res} was returned")


        # Testing from Graph B
        self.assertEqual(res := (Iterative_Deepening_AStar(self._5, impossible_vertex)), None, 
                         f"Vertex is impossible, should return None, {res} was returned")

        self.assertEqual(res := (Iterative_Deepening_AStar(impossible_vertex_2, self._0)), None, 
                         f"Vertex is impossible, should return None, {res} was returned")
            

        # Testing from Graph C
        self.assertEqual(res := (Iterative_Deepening_AStar(self.a2, impossible_vertex)), None, 
                         f"Vertex is impossible, should return None, {res} was returned")

        self.assertEqual(res := (Iterative_Deepening_AStar(impossible_vertex_2, self.c2)), None, 
                         f"Vertex is impossible, should return None, {res} was returned")
        

    def test_graph_A(self):
        expectations = [
            (4.0, ['Node: A', 'Node: B', 'Node: C', 'Node: D']),
            (3.0, ['Node: C', 'Node: B', 'Node: A']),
            (3.0, ['Node: B', 'Node: C', 'Node: D']),
            (0.0, ['Node: A'])
        ]

        tests = [
            (self.a, self.d),
            (self.c, self.a),
            (self.b, self.d),
            (self.a, self.a)
        ]

        for experiments in zip(expectations, tests):
            expected = experiments[0]
            test = experiments[1] 

            res = Iterative_Deepening_AStar(test[0], test[1])

            self.assertEqual(
                (res[0], list(str(x) for x in res[1])), 
                (expected[0], expected[1])
            )

    
    def test_graph_B(self):
        # I hated looking at the actual diagram to find this out
        # NOT FUN
        # 0/10 WOULD NOT RECOMMEND
        # heres the reference again if you want
        #   https://media.geeksforgeeks.org/wp-content/uploads/20230223140425/mst1drawio.png

        expectations = [
            (21.0, ['Node: 0', 'Node: 7', 'Node: 6', 'Node: 5', 'Node: 4']),
            (14.0, ['Node: 8', 'Node: 2', 'Node: 1', 'Node: 0']),
            (15.0, ['Node: 1', 'Node: 2', 'Node: 3']),
            (0.0, ['Node: 8'])
        ]

        tests = [
            (self._0, self._4),
            (self._8, self._0),
            (self._1, self._3),
            (self._8, self._8)
        ]

        for experiments in zip(expectations, tests):
            expected = experiments[0]
            test = experiments[1] 

            res = Iterative_Deepening_AStar(test[0], test[1])

            self.assertEqual(
                (res[0], list(str(x) for x in res[1])), 
                (expected[0], expected[1])
            )


    def test_graph_C(self):
        # Reference
        #   https://www.programiz.com/sites/tutorial2program/files/pa_6.png
        # most straight forward test cases and graph, massive W

        expectations = [
            (9.0, ['Node: A', 'Node: C', 'Node: E', 'Node: F']),
            (5.0, ['Node: D', 'Node: C', 'Node: B']),
            (6.0, ['Node: E', 'Node: C', 'Node: A']),
            (0.0, ['Node: C'])
        ]

        tests = [
            (self.a2, self.f2),
            (self.d2, self.b2),
            (self.e2, self.a2),
            (self.c2, self.c2)
        ]

        for experiments in zip(expectations, tests):
            expected = experiments[0]
            test = experiments[1] 

            res = Iterative_Deepening_AStar(test[0], test[1])

            self.assertEqual(
                (res[0], list(str(x) for x in res[1])), 
                (expected[0], expected[1])
            )


if __name__ == "__main__":
    unittest.main()
