import matplotlib.pyplot as plt
# Sample data
categories = ['Category 1', 'Category 2', 'Category 3']
values = [7, 9.66, 100]
# Create a figure and a set of subplots
fig, ax = plt.subplots()
# Create a bar chart
ax.bar(categories, values)
# Set the title and labels
ax.set_title('Column Graph Example')
ax.set_xlabel('Categories')
ax.set_ylabel('Values')
# Display the graph
plt.show()
