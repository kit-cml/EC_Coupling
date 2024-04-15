import os
import pandas as pd
import numpy as np

# def calculate_apd(file_vm, highest_vm_after_INa_zero, index_of_highest_vm):
#     # Calculate APD90 and APD50 using the provided data
#     vm_valley = file_vm['Vm'].iloc[-1]
#     Vm_90 = highest_vm_after_INa_zero - (0.9 * (highest_vm_after_INa_zero - vm_valley))
#     Vm_50 = highest_vm_after_INa_zero - (0.5 * (highest_vm_after_INa_zero - vm_valley))

#     index_closest_to_Vm_90_1 = file_vm['Vm'].loc[:index_of_highest_vm.index[0]].sub(Vm_90).abs().idxmin()
#     index_closest_to_Vm_90_2 = file_vm['Vm'].loc[index_of_highest_vm.index[0]:].sub(Vm_90).abs().idxmin()
#     Vm_90_1 = file_vm['Time'].loc[index_closest_to_Vm_90_1]
#     Vm_90_2 = file_vm['Time'].loc[index_closest_to_Vm_90_2]
#     APD90 = Vm_90_2 - Vm_90_1

#     index_closest_to_Vm_50_1 = file_vm['Vm'].loc[:index_of_highest_vm.index[0]].sub(Vm_50).abs().idxmin()
#     index_closest_to_Vm_50_2 = file_vm['Vm'].loc[index_of_highest_vm.index[0]:].sub(Vm_50).abs().idxmin()
#     Vm_50_1 = file_vm['Time'].loc[index_closest_to_Vm_50_1]
#     Vm_50_2 = file_vm['Time'].loc[index_closest_to_Vm_50_2]
#     APD50 = Vm_50_2 - Vm_50_1

#     APDtri = APD90 - APD50
#     return Vm_90, Vm_50, APD90, APD50, APDtri, index_closest_to_Vm_90_2, vm_valley

def calculate_apd(file_vm, highest_vm_after_INa_zero, index_of_highest_vm):
    if not file_vm.empty:
        vm_valley = file_vm['Vm'].iloc[-1]
        Vm_90 = highest_vm_after_INa_zero - (0.9 * (highest_vm_after_INa_zero - vm_valley))
        Vm_50 = highest_vm_after_INa_zero - (0.5 * (highest_vm_after_INa_zero - vm_valley))
        
        if not index_of_highest_vm.empty:
            index_closest_to_Vm_90_1 = file_vm['Vm'].loc[:index_of_highest_vm.index[0]].sub(Vm_90).abs().idxmin()
            index_closest_to_Vm_90_2 = file_vm['Vm'].loc[index_of_highest_vm.index[0]:].sub(Vm_90).abs().idxmin()
            
            Vm_90_1 = file_vm['Time'].loc[index_closest_to_Vm_90_1]
            Vm_90_2 = file_vm['Time'].loc[index_closest_to_Vm_90_2]
            APD90 = Vm_90_2 - Vm_90_1
            
            index_closest_to_Vm_50_1 = file_vm['Vm'].loc[:index_of_highest_vm.index[0]].sub(Vm_50).abs().idxmin()
            index_closest_to_Vm_50_2 = file_vm['Vm'].loc[index_of_highest_vm.index[0]:].sub(Vm_50).abs().idxmin()
            
            Vm_50_1 = file_vm['Time'].loc[index_closest_to_Vm_50_1]
            Vm_50_2 = file_vm['Time'].loc[index_closest_to_Vm_50_2]
            APD50 = Vm_50_2 - Vm_50_1
            
            APDtri = APD90 - APD50
            return Vm_90, Vm_50, APD90, APD50, APDtri, index_closest_to_Vm_90_2, vm_valley
        else:
            # Handle the case where index_of_highest_vm is empty
            return None, None, None, None, None, None, None
    else:
        # Handle the case where file_vm is empty
        return None, None, None, None, None, None, None

def calculate_ca(file_ca):
    #Find Ca_Peak
    ca_peak = file_ca['cai'].max()
    index_ca_peak = file_ca['cai'].idxmax()

    #find Ca_Diastole
    ca_valley = file_ca['cai'].iloc[-1]

    #Calculate Ca_90 and Ca_50
    Ca_90 = ca_peak - (0.9 * (ca_peak - ca_valley))
    Ca_50 = ca_peak - (0.5 * (ca_peak - ca_valley))

    # Find index of the value closest to Ca_90
    index_Ca_90_1 = file_ca['cai'].loc[:index_ca_peak].sub(Ca_90).abs().idxmin()
    index_Ca_90_2 = file_ca['cai'].loc[index_ca_peak:].sub(Ca_90).abs().idxmin()

    # Get the corresponding 'Time' values for the indices found above
    Ca_90_1 = file_ca['Time'].loc[index_Ca_90_1]
    Ca_90_2 = file_ca['Time'].loc[index_Ca_90_2]

    # Calculate CaD90 using the Time values
    CaD90 = Ca_90_2 - Ca_90_1

    # Find index of the value closest to Ca_50
    index_Ca_50_1 = file_ca['cai'].loc[:index_ca_peak].sub(Ca_50).abs().idxmin()
    index_Ca_50_2 = file_ca['cai'].loc[index_ca_peak:].sub(Ca_50).abs().idxmin()

    # Get the corresponding 'Time' values for the indices found above
    Ca_50_1 = file_ca['Time'].loc[index_Ca_50_1]
    Ca_50_2 = file_ca['Time'].loc[index_Ca_50_2]

    #Calculate CaD50 using the Time values
    CaD50 = Ca_50_2 - Ca_50_1

    #Calculate Catri
    catri = CaD90 - CaD50
    return ca_peak, ca_valley, CaD90, CaD50, catri

# def calculate_dVm(file_vm, index_of_highest_vm, highest_vm_after_INa_zero, vm_valley, index_closest_to_Vm_90_2, file_dvmdt):
#     Vm_30 = highest_vm_after_INa_zero - (0.3 * (highest_vm_after_INa_zero - vm_valley))

#     index_closest_to_Vm_30 = file_vm['Vm'].loc[index_of_highest_vm.index[0]:].sub(Vm_30).abs().idxmin()

#     if index_closest_to_Vm_30 is not None and index_closest_to_Vm_90_2 is not None:
#         # Kondisi pertama: index_closest_to_Vm_30 dan index_closest_to_Vm_90_2 diketahui
#         index_max_vm_between_30_90 = file_vm['Vm'].loc[index_closest_to_Vm_30:index_closest_to_Vm_90_2].idxmax()
        
#     elif index_closest_to_Vm_30 is not None and index_closest_to_Vm_90_2 is None:
#         # Kondisi kedua: index_closest_to_Vm_30 diketahui, index_closest_to_Vm_90_2 tidak diketahui
#         index_max_vm_between_30_90 = file_vm['Vm'].loc[index_closest_to_Vm_30:].idxmax()
        
#     else:
#         # Kondisi ketiga: index_closest_to_Vm_30 dan index_closest_to_Vm_90_2 tidak diketahui
#         index_max_vm_between_30_90 = file_vm['Vm'].loc[index_of_highest_vm:].idxmax()

#     dvmdt_repol = file_dvmdt['dVm/dt'].iloc[index_max_vm_between_30_90]

#     max_dvmdt = file_dvmdt['dVm/dt'].max()

#     return dvmdt_repol, max_dvmdt

# def calculate_dVm(file_vm, index_of_highest_vm, highest_vm_after_INa_zero, vm_valley, index_closest_to_Vm_90_2, file_dvmdt):
#     Vm_30 = highest_vm_after_INa_zero - (0.3 * (highest_vm_after_INa_zero - vm_valley))

#     index_closest_to_Vm_30 = file_vm['Vm'].loc[index_of_highest_vm.index[0]:].sub(Vm_30).abs().idxmin()

#     if index_closest_to_Vm_30 is not None and index_closest_to_Vm_90_2 is not None:
#         # Kondisi pertama: index_closest_to_Vm_30 dan index_closest_to_Vm_90_2 diketahui
#         slice_vm = file_vm['Vm'].loc[index_closest_to_Vm_30:index_closest_to_Vm_90_2]
#     elif index_closest_to_Vm_30 is not None and index_closest_to_Vm_90_2 is None:
#         # Kondisi kedua: index_closest_to_Vm_30 diketahui, index_closest_to_Vm_90_2 tidak diketahui
#         slice_vm = file_vm['Vm'].loc[index_closest_to_Vm_30:]
#     else:
#         # Kondisi ketiga: index_closest_to_Vm_30 dan index_closest_to_Vm_90_2 tidak diketahui
#         slice_vm = None  # Set to None if both indices are unknown

#     if slice_vm is not None and not slice_vm.empty:
#         index_max_vm_between_30_90 = slice_vm.idxmax()
#         dvmdt_repol = file_dvmdt['dVm/dt'].iloc[index_max_vm_between_30_90]
#     else:
#         index_max_vm_between_30_90 = None
#         dvmdt_repol = None  # Set to None if the slice is empty

#     max_dvmdt = file_dvmdt['dVm/dt'].max()

#     return dvmdt_repol, max_dvmdt

def calculate_dVm(file_vm, index_of_highest_vm, highest_vm_after_INa_zero, vm_valley, index_closest_to_Vm_90_2, file_dvmdt):
    if 'dVm/dt' not in file_dvmdt.columns:
        print("Skipping calculation of dVm/dt due to missing column 'dVm/dt' in file_dvmdt.")
        return None
    index_closest_to_Vm_30 = None  # Initialize with a default value
    index_max_vm_between_30_90 = None  # Initialize with a default value
    dvmdt_repol = None  # Initialize with a default value
    max_dvmdt = None  # Initialize with a default value

    Vm_30 = highest_vm_after_INa_zero - (0.3 * (highest_vm_after_INa_zero - vm_valley))

    if not file_vm.empty and highest_vm_after_INa_zero is not None and vm_valley is not None:
        # Find the index closest to Vm_30
        filtered_values = np.where(file_vm['Vm'] > Vm_30)[0].tolist()
        if filtered_values:
            index_closest_to_Vm_30 = file_vm['Vm'].iloc[filtered_values].idxmin()

        if (
            index_closest_to_Vm_30 is not None
            and index_closest_to_Vm_90_2 is not None
            and index_closest_to_Vm_30 < index_closest_to_Vm_90_2
        ):
            # Kondisi pertama: index_closest_to_Vm_30 dan index_closest_to_Vm_90_2 diketahui
            index_max_vm_between_30_90 = file_vm['Vm'].loc[index_closest_to_Vm_30:index_closest_to_Vm_90_2].idxmax()

        if index_max_vm_between_30_90 is not None:
            dvmdt_repol = file_dvmdt['dVm/dt'].iloc[index_max_vm_between_30_90]

        max_dvmdt = file_dvmdt['dVm/dt'].max()

    return dvmdt_repol, max_dvmdt

def calculate_qnet_90(file_vm, file_contents, Vm_90):
    filtered_values = np.where((file_vm['Vm']>Vm_90))[0].tolist()

    file_contents_filter = file_contents.iloc[filtered_values]

    Inet = file_contents_filter['INaL'] + file_contents_filter['IK1'] + file_contents_filter['ICaL'] + file_contents_filter['IKr'] + file_contents_filter['IKs'] + file_contents_filter['Ito']

    file_contents_filter['Inet'] = Inet

    file_contents_filter['Time_New'] = file_contents_filter['Time'].diff()

    file_contents_filter['qNet_new'] = ((file_contents_filter['Inet']) * file_contents_filter['Time_New']) / 1000

    avg = file_contents_filter['qNet_new'].sum()

    return avg

def calculate_qnet(file_vm, file_contents):

    filtered_values_0 = np.where((file_vm['Vm'] == file_vm['Vm']))[0].tolist()

    file_contents_filter_0 = file_contents.iloc[filtered_values_0]

    Inet = file_contents_filter_0['INaL'] + file_contents_filter_0['IK1'] + file_contents_filter_0['ICaL'] + file_contents_filter_0['IKr'] + file_contents_filter_0['IKs'] + file_contents_filter_0['Ito']

    file_contents_filter_0['Inet'] = Inet

    file_contents_filter_0['Time_New'] = file_contents_filter_0['Time'].diff()

    file_contents_filter_0['qNet_new'] = ((file_contents_filter_0['Inet']) * file_contents_filter_0['Time_New']) / 1000

    qnet = file_contents_filter_0['qNet_new'].sum()

    return qnet

def calculate_qinward(file_contents, file_contents_0):
    INaL_drug = file_contents['INaL'].sum()

    INaL_control = file_contents_0['INaL'].sum()

    ICaL_drug = file_contents['ICaL'].sum()

    ICaL_control = file_contents_0['ICaL'].sum()

    qinward = 0.5 * ((INaL_drug / INaL_control) + (ICaL_drug / ICaL_control))

    return qinward

# Function to save print statements to a CSV file
def save_prints_to_csv(print_output, csv_filename):
    with open(csv_filename, 'w') as csv_file:
        for output in print_output:
            csv_file.write(output + '\n')


result_apd = []
result_ca = []
result_dvmdt = []
result_qnet_90 = []
result_qnet = []
result_vmpeak = []
result_qinward = []
drug = []
conc = []
smp = []

def read_plt_files(folder_path, output_file_path):
    with open(output_file_path, 'w') as output_file:
        for root, dirs, files in os.walk(folder_path):
            # result = 1
            for dirname in dirs:
                # if dirname == '0.00':
                #     continue
    
                subdir_path = os.path.join(root, dirname)
                plt_files = [f for f in os.listdir(subdir_path) if f.endswith(".plt") and "_ires_" in f]
                plt_files_0 = [f for f in os.listdir(subdir_path) if f.endswith(".plt") and "0.00_ires_" in f]
                if not plt_files:
                    print(f"No _ires_ files found in {subdir_path}. Skipping this directory.", file=output_file)
                    continue
    
                for plt_file_0 in plt_files_0:
                    plt_file_path_0 = os.path.join(subdir_path, plt_file_0)
                    # file_contents_0 = pd.read_csv(plt_file_path_0, delimiter=' ')
                    try:
                        file_contents_0 = pd.read_csv(plt_file_path_0, delimiter=' ')
                    except (OSError, UnicodeDecodeError, pd.errors.ParserError) as e:
                        print(f"Skipping {plt_file_path_0} due to error: {e}", file=output_file)
                        continue
    
                for plt_file in plt_files:
                    plt_file_path = os.path.join(subdir_path, plt_file)
                    # file_contents = pd.read_csv(plt_file_path, delimiter=' ')
                    try:
                        file_contents = pd.read_csv(plt_file_path, delimiter=' ')
                    except (OSError, UnicodeDecodeError, pd.errors.ParserError) as e:
                        print(f"Skipping {plt_file_path} due to error: {e}", file=output_file)
                        continue
                    # Check if the file_contents is empty
                    if file_contents.empty:
                        print(f"Skipping {plt_file_path} due to empty file_contents.", file=output_file)
                        continue  # Skip processing this file if it's empty
                    
                    # Check if the dataframe is empty for these columns
                    # if is_empty_dataframe(file_contents):
                    #     continue  # Skip the file
    
                    # Find the index of the smallest 'INa' value within the first 301 rows (index 0-300)
                    idx_smallest_INa = file_contents['INa'][:301].idxmin()
                    
                    # Find the indices of the two values after the smallest 'INa' value
                    indices_after_smallest_INa = idx_smallest_INa + 3
    
                    plt_vmcheck = plt_file.replace("_ires_", "_vmcheck_")
                    plt_ca = plt_file.replace("_ires_", "_ca_i_")
                    plt_dvmdt = plt_file.replace("_ires_", "_dvmdt_")
                    
                    plt_file_vm = os.path.join(subdir_path, plt_vmcheck)
                    if not os.path.exists(plt_file_vm):
                        print(f"No corresponding _vmcheck_ file found for {plt_vmcheck}. Skipping this directory.", file=output_file)
                        continue
    
                    # # Check if the dataframe is empty for these columns
                    # if is_empty_dataframe(file_vm):
                    #     continue  # Skip the file
    
                    plt_file_ca = os.path.join(subdir_path, plt_ca)
                    if not os.path.exists(plt_file_ca):
                        print(f"No corresponding _ca_i_ file found for {plt_ca}. Skipping this directory.", file=output_file)
                        continue
                    
                    # if is_empty_dataframe(file_ca):
                    #     continue  # Skip the file
    
                    plt_file_dvmdt = os.path.join(subdir_path, plt_dvmdt)
                    if not os.path.exists(plt_file_dvmdt):
                        print(f"No corresponding _dvmdt_ file found for {plt_dvmdt}. Skipping this directory.", file=output_file)
                        continue
                    
                    # file_vm = pd.read_csv(plt_file_vm, delimiter=' ')
                    try:
                        file_vm = pd.read_csv(plt_file_vm, delimiter=' ')
                    except (OSError, UnicodeDecodeError, pd.errors.ParserError) as e:
                        print(f"Skipping {plt_vmcheck} due to error: {e}", file=output_file)
                        continue
                    # Check if the file_contents is empty
                    if file_vm.empty:
                        print(f"Skipping {plt_vmcheck} due to empty file_vm.", file=output_file)
                        continue  # Skip processing this file if it's empty
                    
                    # file_ca = pd.read_csv(plt_file_ca, delimiter=' ')
                    try:
                        file_ca = pd.read_csv(plt_file_ca, delimiter=' ')
                    except (OSError, UnicodeDecodeError, pd.errors.ParserError) as e:
                        print(f"Skipping {plt_ca} due to error: {e}", file=output_file)
                        continue
                    # Check if the file_contents is empty
                    if file_ca.empty:
                        print(f"Skipping {plt_ca} due to empty file_ca.", file=output_file)
                        continue  # Skip processing this file if it's empty
                        
                    # file_dvmdt = pd.read_csv(plt_file_dvmdt, delimiter=' ')
                    try:
                        file_dvmdt = pd.read_csv(plt_file_dvmdt, delimiter=' ')
                    except (OSError, UnicodeDecodeError, pd.errors.ParserError) as e:
                        print(f"Skipping {plt_dvmdt} due to error: {e}", file=output_file)
                        continue
                    # Check if the file_contents is empty
                    if file_dvmdt.empty:
                        print(f"Skipping {plt_dvmdt} due to empty file_dvmdt.", file=output_file)
                        continue  # Skip processing this file if it's empty
    
                    # if is_empty_dataframe(file_dvmdt):
                    #     continue  # Skip the file
    
                    # Filter '_ires_' file to get the desired 'Vm' values
                    filtered_values1 = np.where(file_vm.index > indices_after_smallest_INa)[0].tolist()
                    
                    # Find the highest 'Vm' value after 'idx_INa_zero'
                    highest_vm_after_INa_zero = file_vm['Vm'].iloc[filtered_values1].max()
                    
                    # Find the index of the highest 'Vm' value after 'idx_INa_zero'
                    index_of_highest_vm = file_vm[file_vm['Vm'] == highest_vm_after_INa_zero]
    
                    apd_result = calculate_apd(file_vm, highest_vm_after_INa_zero, index_of_highest_vm)
    
                    ca_result = calculate_ca(file_ca)
    
                    index_closest_to_Vm_90_2 = apd_result[5]
    
                    vm_valley = apd_result[6]
                    
                    # print(plt_file_path)
                    
                    # print(plt_dvmdt)
                    
                    # print(index_of_highest_vm, highest_vm_after_INa_zero, vm_valley, index_closest_to_Vm_90_2)
    
                    dvmdt_result = calculate_dVm(file_vm, index_of_highest_vm, highest_vm_after_INa_zero, vm_valley, index_closest_to_Vm_90_2, file_dvmdt)
    
                    Vm_90 = apd_result[0]
                    
                    qnet_result_90 = calculate_qnet_90(file_vm, file_contents, Vm_90)
    
                    qinward_result = calculate_qinward(file_contents, file_contents_0)
    
                    qnet_result = calculate_qnet(file_vm, file_contents)
    
                    result_apd.append(apd_result)
                    result_ca.append(ca_result)
                    result_dvmdt.append(dvmdt_result)
                    result_qnet_90.append(qnet_result_90)
                    result_qnet.append(qnet_result)
                    result_vmpeak.append(highest_vm_after_INa_zero)
                    result_qinward.append(qinward_result)
                    # print(plt_file_path)
                    # print(plt_file_path.split("_")[7].split(".")[0][3:])
                    # print(plt_file_path.split("\\")[1])
                    drug.append(plt_file_path.split("\\")[1])
                    conc.append(plt_file_path.split("\\")[2])
                    smp.append(int(plt_file_path.split("_")[7].split(".")[0][3:]))
    
    return result_apd, result_ca, result_dvmdt, result_qnet, result_vmpeak, result_qinward, drug, conc, smp

if __name__ == "__main__":
    folder_path = "D:/backup_CML_1/New_Drugs/Chantest_Endo/Testing"
    # read_plt_files(folder_path)
    output_file_path = "D:/backup_CML_1/New_Drugs/Chantest_Endo/output_error_2.txt"
    read_plt_files(folder_path, output_file_path)

result_apd_df = pd.DataFrame(result_apd, columns=['Vm_90', 'Vm_50', 'APD90', 'APD50', 'APDtri', 'index_Vm_90', 'Vm_Resting'])
result_apd_df_fix = result_apd_df.drop(['Vm_90', 'Vm_50', 'index_Vm_90'], axis=1)
result_ca_df = pd.DataFrame(result_ca, columns=['Ca_Peak', 'Ca_Diastole', 'CaD90', 'CaD50', 'Catri'])
result_dvmdt_df = pd.DataFrame(result_dvmdt, columns=['dVm/dt_Repol', 'dVm/dt_Max'])
result_qnet_90_df = pd.DataFrame(result_qnet_90, columns=['qNet_Vm_repol_90'])
result_qnet_df = pd.DataFrame(result_qnet, columns = ['qNet_CL'])
result_qinward_df = pd.DataFrame(result_qinward, columns = ['qInward'])
result_vmpeak_df = pd.DataFrame(result_vmpeak, columns=['Vm_Peak'])
drug_name = pd.DataFrame(drug, columns=['Drug_Name'])
concentration = pd.DataFrame(conc, columns=['Cmax'])
sample = pd.DataFrame(smp, columns=['Sample_ID'])

full_data = pd.concat([result_dvmdt_df, result_vmpeak_df, result_apd_df_fix, result_ca_df, result_qnet_90_df, result_qnet_df, result_qinward_df, drug_name, concentration, sample], axis=1)

df_sorted = full_data.sort_values(['Drug_Name','Sample_ID'])

df_filtered = df_sorted[df_sorted['Cmax'] != '0.00']

drug = df_filtered.groupby(['Sample_ID', 'Drug_Name']).filter(lambda x: len(x) >= 4).groupby(['Sample_ID', 'Drug_Name'], as_index=False)[['dVm/dt_Repol', 'dVm/dt_Max', 'Vm_Peak', 'APD90', 'APD50', 'APDtri', 'Vm_Resting', 'Ca_Peak', 'Ca_Diastole', 'CaD90', 'CaD50', 'Catri', 'qNet_Vm_repol_90', 'qNet_CL', 'qInward']].mean()

# drug = df_filtered.groupby(['Sample_ID', 'Drug_Name'], as_index=False)[['dVm/dt_Repol', 'dVm/dt_Max', 'Vm_Peak', 'APD90', 'APD50', 'APDtri', 'Vm_Resting', 'Ca_Peak', 'Ca_Diastole', 'CaD90', 'CaD50', 'Catri', 'qNet_Vm_repol_90', 'qNet_CL', 'qInward']].mean()

df_sorted_2 = drug.sort_values(['Drug_Name','Sample_ID'])

d_train = df_sorted_2.set_index('Drug_Name')

high = ['disopyramide', 'ibutilide', 'vandetanib', 'azimilide', 'quinidine', 'sotalol', 'dofetilide', 'dofetilide', 'bepridil']
intermediate = ['clarithromycin', 'clozapine', 'domperidone', 'droperidol', 'pimozide', 'risperidone', 'astemizole', 'cisapride', 'terfenadine', 'chlorpromazine', 'ondansetron']
low = ['metoprolol', 'nifedipine', 'nitrendipine', 'tamoxifen', 'loratadine', 'verapamil', 'ranolazine', 'diltiazem', 'mexiletine']
label = []

for row in d_train.index:
    #print(row)
    if row in high:
        label.append('high')
    elif row in intermediate:
        label.append('intermediate')
    elif row in low:
        label.append('low')
    else:
        label.append('null')
d_train['risk_level'] = label

d_train1 = d_train.reset_index()

d_train1.to_csv('D:/backup_CML_1/New_Drugs/Chantest_Endo/data_testing_chantest.csv', index=False)