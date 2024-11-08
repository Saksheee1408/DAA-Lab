import sys
from math import inf

def tsp_branch_and_bound(distances):
    n = len(distances)
    tour = [0]  # Initialize the starting tour
    cost = inf  # Start with infinity as the initial cost to minimize against

    # Initialize the bound by summing up minimum distances for each row
    bound = 0
    for i in range(n):
        bound += min(distances[i])  # Find the minimum distance from city i to any other city

    bound = bound / 2  # Average it for an initial estimation

    # Recursive helper function to explore and update paths
    def branch_and_bound(node, rem_cities, current_cost, current_tour):
        nonlocal tour, cost
        
        # Base case: if all cities are visited, complete the tour back to the start
        if not rem_cities:
            total_cost = current_cost + distances[node][0]  # Complete the tour
            if total_cost < cost:
                cost = total_cost
                tour = current_tour + [0]  # Record the optimal tour
            return
        
        # Recursive case: add each remaining city to the path
        for i in rem_cities:
            new_cost = current_cost + distances[node][i]
            # Calculate bound for this path
            new_bound = new_cost + bound
            # Continue only if the new bound is below the current minimum cost
            if new_bound < cost:
                branch_and_bound(i, [c for c in rem_cities if c != i], new_cost, current_tour + [i])

    # Start the search from the first city
    branch_and_bound(0, list(range(1, n)), 0, [0])
    
    return tour, cost

# Distance matrix as input
distances = [
    [0, 10, 15, 20],
    [10, 0, 35, 25],
    [15, 35, 0, 30],
    [20, 25, 30, 0]
]

# Run the function
tour, minimum_cost = tsp_branch_and_bound(distances)
print("Minimum cost:", minimum_cost)
print("Tour:", tour)
