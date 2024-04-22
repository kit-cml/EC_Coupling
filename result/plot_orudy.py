#tension comparison
import pandas as pd
import matplotlib.pyplot as plt

# coupled = pd.read_csv("../result/chlorpromazine/0.00/0conc.csv")
# data1 = pd.read_csv("./500/0.00/0conc.csv")
# data2 = pd.read_csv("./1000/0conc.csv")
# data3 = pd.read_csv("./1500/0.00/0conc.csv")
data4 = pd.read_csv("orudy_cai.csv")

# Create a figure and subplots with shared x- axis            
plt.figure()

# Create scatter plots on each subplot
# plt.scatter(coupled['Time']-198000, coupled['cai'], label='Coupled', marker='o')
plt.scatter(data4['Time'], data4['Cai_2000msec']*0.000001, color='red', label='2000 BCL')
plt.scatter(data4['Time'], data4['Cai_1500msec']*0.000001, color='orange', label='1500 BCL')
plt.scatter(data4['Time'], data4['Cai_1000msec']*0.000001, color='blue', label='1000 BCL')
plt.scatter(data4['Time'], data4['Cai_500msec']*0.000001, color='lightblue', label='500 BCL')

# plt.scatter(data3['Time']-1498500, data3['cai'], color='orange', label='1500 BCL', marker='s')
# plt.scatter(data2['Time']-1998000, data2['cai'], color='blue', label='1000 BCL', marker='s')
# plt.scatter(data1['Time']-499500, data1['cai'], color='lightblue', label='500 BCL', marker='s')

# Add labels and title (optional)
# plt.ylabel('Force (kilo pascal)')
# plt.xlabel('Time (millisecond)')


# Add legend
plt.legend()  # Legend is placed on the top subplot

# Show the plot
plt.tight_layout()
plt.savefig("orudy_Cai.png")