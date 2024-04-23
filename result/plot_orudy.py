#tension comparison
from scipy.signal import find_peaks
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

data_main = pd.read_csv("orudy_cai.csv")

# Create a figure and subplots with shared x- axis            
plt.figure()

# Create scatter plots on each subplot

plt.scatter(data_main['Time'], data_main['Cai_2000msec']*0.000001, color='red', label='2000 BCL')
plt.scatter(data_main['Time'], data_main['Cai_1500msec']*0.000001, color='orange', label='1500 BCL')
plt.scatter(data_main['Time'], data_main['Cai_1000msec']*0.000001, color='blue', label='1000 BCL')
plt.scatter(data_main['Time'], data_main['Cai_500msec']*0.000001, color='lightblue', label='500 BCL')

data1 = data_main['Cai_500msec']*0.000001
data2 = data_main['Cai_1000msec']*0.000001
data3 = data_main['Cai_1500msec']*0.000001
data4 = data_main['Cai_2000msec']*0.000001

# Add labels and title (optional)
# plt.ylabel('Force (kilo pascal)')
plt.xlabel('Time (millisecond)')


# Add legend
plt.title("Calcium Concentration (in mMol) ORd")
plt.legend()  # Legend is placed on the top subplot

# Show the plot
# plt.tight_layout()
plt.savefig("orudy_Cai.png")

print("non coupled:")

peaks = find_peaks(data1)[0]
idx_max_peak = peaks[np.argmax(data1[peaks])]
max_peak = data1[idx_max_peak]
print("Peak for 500 BCL: ",max_peak)

peaks = find_peaks(data2)[0]
idx_max_peak = peaks[np.argmax(data2[peaks])]
max_peak = data2[idx_max_peak]
print("Peak for 1000 BCL: ",max_peak)

peaks = find_peaks(data3)[0]
idx_max_peak = peaks[np.argmax(data3[peaks])]
max_peak = data3[idx_max_peak]
print("Peak for 1500 BCL: ",max_peak)

peaks = find_peaks(data4)[0]
idx_max_peak = peaks[np.argmax(data4[peaks])]
max_peak = data4[idx_max_peak]
print("Peak for 2000 BCL: ",max_peak)