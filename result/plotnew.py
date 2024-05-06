#tension comparison
from scipy.signal import find_peaks
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

data_main = pd.read_csv("orudy_cai.csv")

data2 = pd.read_csv("./testing/0.00/0conc.csv")

# Create a figure and subplots with shared x- axis            
plt.figure()

# time1 = data1['Time']-999000
# time1 = time1[time1 <= 301]
time2 = data2['Time']-999000
# time2 = time2[time2 <= 301]
# time3 = data3['Time']-1498500

# Create scatter plots on each subplot
# plt.scatter(coupled['Time']-198000, coupled['cai'], label='Coupled', marker='o')
# plt.scatter(data4['Time']-1998000, data4['cai'], color='red', label='2000 BCL')
# plt.scatter(time3, data3['cai'].head(len(time3)), color='orange', label='1500 BCL')
plt.scatter(time2, data2['cai'].head(len(time2))*1000000, color='blue', label='Coupled')
# plt.scatter(time1, data1['cai'].head(len(time1)), color='lightblue', label='Not Scaled')
plt.scatter(data_main['Time'], data_main['Cai(x1.000.000)(milliM->picoM)'], color='red', label='Non-Coupled')

# plt.scatter(data4['Time']-1998000, data4['v'], color='red', label='2000 BCL')
# plt.scatter(data3['Time']-1498500, data3['v'], color='orange', label='1500 BCL')
# plt.scatter(data2['Time']-999000, data2['v'], color='blue', label='1000 BCL')
# plt.scatter(data1['Time']-499000, data1['v'], color='lightblue', label='500 BCL')


# Add labels and title (optional)
# plt.ylabel('Force (kilo pascal)')
plt.xlabel('Time (millisecond)')


# Add legend
plt.title("Calcium Concentration (in nMol) - 1000 BCL")
plt.ylim(ymax=500)
plt.legend()  # Legend is placed on the top subplot

# Show the plot
# plt.tight_layout()
plt.savefig("1000_bcl.png")

# print("Coupled:")

# peaks = find_peaks(data1['cai'])[0]
# idx_max_peak = peaks[np.argmax(data1['cai'][peaks])]
# max_peak = data1['cai'][idx_max_peak]
# print("Peak for Non Scaled: ",max_peak)

# peaks = find_peaks(data2['cai'])[0]
# idx_max_peak = peaks[np.argmax(data2['cai'][peaks])]
# max_peak = data2['cai'][idx_max_peak]
# print("Peak for Scaled: ",max_peak)

# data2 = data_main['Cai_1000msec']*0.000001

# peaks = find_peaks(data2)[0]
# idx_max_peak = peaks[np.argmax(data2[peaks])]
# max_peak = data2[idx_max_peak]
# print("Peak for Control: ",max_peak)

# peaks = find_peaks(data3['cai'])[0]
# idx_max_peak = peaks[np.argmax(data3['cai'][peaks])]
# max_peak = data3['cai'][idx_max_peak]
# print("Peak for 1500 BCL: ",max_peak)

# peaks = find_peaks(data4['cai'])[0]
# idx_max_peak = peaks[np.argmax(data4['cai'][peaks])]
# max_peak = data4['cai'][idx_max_peak]
# print("Peak for 2000 BCL: ",max_peak)
