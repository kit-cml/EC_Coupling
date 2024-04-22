#tension comparison
import pandas as pd
import matplotlib.pyplot as plt

# coupled = pd.read_csv("../result/chlorpromazine/0.00/0conc.csv")
data1 = pd.read_csv("./500/0.00/0conc.csv")
data2 = pd.read_csv("./1000/0.00/0conc.csv")
data3 = pd.read_csv("./1500/0.00/0conc.csv")
data4 = pd.read_csv("./2000/0.00/0conc.csv")

# Create a figure and subplots with shared x- axis            
plt.figure()

# Create scatter plots on each subplot
# plt.scatter(coupled['Time']-198000, coupled['cai'], label='Coupled', marker='o')
plt.scatter(data4['Time']-1998000, data4['cai'], color='red', label='2000 BCL')
# plt.scatter(data3['Time']-1498500, data3['cai'], color='orange', label='1500 BCL')
# plt.scatter(data2['Time']-999000, data2['cai'], color='blue', label='1000 BCL')
# plt.scatter(data1['Time']-499500, data1['cai'], color='lightblue', label='500 BCL')

# Add labels and title (optional)
# plt.ylabel('Force (kilo pascal)')
# plt.xlabel('Time (millisecond)')


# Add legend
plt.legend()  # Legend is placed on the top subplot

# Show the plot
plt.tight_layout()
plt.savefig("Cai.png")