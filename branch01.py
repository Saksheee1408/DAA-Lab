#Branch And Bound 0/1 knapsack
#1.define one function knapsack initialize max_value=0,best_items=[]
#2.define bound function bound_value=current_value nd bound_weight=current_weight
#3.one loop,start index to n,if bound_weight[i]<=capacity....return bound_value
#3.main function is explore...base condition is like if we reach all the items index==n and current_value>max_value...change,and copy items,return
#4.find bound using bound function if its less than max,return
#5.Include the item if current_weight+weights[i]<=W,append ,explore and pop
#6.Exclude the item 
def simple_knapsack(values, weights, capacity):
    """
    A simplified 0/1 knapsack using branch and bound
    values: list of item values
    weights: list of item weights
    capacity: maximum weight capacity
    """
    
    n = len(values)  # Number of items
    max_value = 0    # Best value found so far
    best_items = []  # Items in best solution
    
    def bound(items_taken, current_value, current_weight, start_index):
        """Simple bound calculation"""
        bound_value = current_value
        bound_weight = current_weight
        
        for i in range(start_index, n):
            if bound_weight + weights[i] <= capacity:
                bound_value += values[i]
                bound_weight += weights[i]
        
        return bound_value
    
    def explore(items_taken, current_value, current_weight, index):
        """Recursive function to explore possible combinations"""
        nonlocal max_value, best_items
        
        # If we've reached the end
        if index == n:
            if current_value > max_value:
                max_value = current_value
                best_items = items_taken.copy()
            return
        
        # Calculate bound
        possible_value = bound(items_taken, current_value, current_weight, index)
        if possible_value <= max_value:
            return
        
        # Try not taking the current item
        explore(items_taken, current_value, current_weight, index + 1)
        
        # Try taking the current item if possible
        if current_weight + weights[index] <= capacity:
            items_taken.append(index)
            explore(items_taken, current_value + values[index], 
                   current_weight + weights[index], index + 1)
            items_taken.pop()
    
    # Start the exploration
    explore([], 0, 0, 0)
    
    # Convert solution to 0/1 list
    solution = [0] * n
    for index in best_items:
        solution[index] = 1
    
    return max_value, solution

# Example usage
values =  [1,2,3]   # Values of items
weights = [4,5,1]   # Weights of items
capacity = 4              # Knapsack capacity

max_value, selected = simple_knapsack(values, weights, capacity)

# Print results
print(f"Maximum value: {max_value}")
print(f"Selected items (1 = selected, 0 = not selected): {selected}")

# Print detailed solution
print("\nItems selected:")
for i in range(len(selected)):
    if selected[i] == 1:
        print(f"Item {i+1}: value = {values[i]}, weight = {weights[i]}")
        