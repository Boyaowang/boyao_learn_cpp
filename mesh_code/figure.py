# -*- coding: utf-8 -*-
"""
Created on Mon Jul 04 13:16:20 2016

@author: Tian Li
"""
import os
import math
import numpy as np
import matplotlib
import matplotlib.pyplot as plt
import seaborn as sns
#matplotlib.rcParams.update({})
matplotlib.rcParams.update({'font.family':'serif','font.serif': 'Times New Roman','font.size': 9})

from matplotlib.ticker import MultipleLocator, FormatStrFormatter
from scipy import interpolate
def main():
    
    myfile = open('codeMeshInput.txt','r')
    lines = myfile.readlines()
    myfile.close()
    
    layerNum = int(lines[11].split(' ')[1])
    initialMass = (4./3.)*3.1415926*pow((9.5/2./1000.),3.)*float(lines[10].split(' ')[1])

    
    #with open('output','r') as myfile:
        #count = sum(1 for line in myfile)
    myfile = open('codeMeshOutput.txt','r')
    lines = myfile.readlines()
    myfile.close()
    
    time=[]
    particleMass=[]
    
    
    temperatureC=[]
    temperatureB=[]

    for x in range (0,len(lines)):
        tempMass=0.
        temp = lines[x].split(' ')
        time.append(float(temp[1]))
        temperatureB.append(float(temp[3+layerNum]))
        temperatureC.append(float(temp[2+layerNum]))
        for y in range (5+layerNum,5+layerNum+layerNum*4):
            #print(y)
            tempMass = tempMass + (float(temp[y]))              
        particleMass.append(1.-tempMass/initialMass)



 #EXP Temperature
    luEx1Time2 = [0.644122, 2.73752, 4.99195, 6.60225, 8.05153, 9.82287, 12.0773, 16.1031, 17.7134, 21.7391, 24.1546, 25.7649, 28.3414, 31.723, 34.4605, 36.5539, 39.1304, 42.029, 44.1224, 46.0548, 49.7585, 51.6908, 53.7842, 55.8776, 57.971, 60.0644, 61.8357, 65.2174, 67.7939, 69.5652, 71.8196, 73.913, 75.5233, 77.7778, 79.7101, 81.4815, 83.2528]
    luEx1Cen = [295.07, 295.136, 295.208, 295.259, 295.305, 355.559, 336.62, 377.936, 390.66, 409.798, 460.567, 492.301, 530.403, 559.025, 593.963, 609.871, 635.299, 654.401, 682.982, 724.231, 816.23, 873.321, 936.754, 1101.57, 1389.96, 1405.86, 1409.09, 1412.36, 1434.62, 1479.04, 1529.8, 1542.54, 1542.59, 1533.16, 1466.68, 1378.03, 1298.88]
    luEx2Time2 = [0.805153, 2.41546, 5.47504, 7.72947, 10.1449, 11.2721, 14.0097, 15.62, 17.7134, 19.8068, 21.9002, 23.9936, 27.6973, 31.8841, 36.0709, 39.9356, 43.6393, 46.0548, 47.8261, 49.7585, 51.6908, 53.6232, 55.7166, 57.4879, 58.7762, 60.3865, 62.6409, 63.9291, 66.1836, 67.7939, 69.5652, 71.4976, 73.591, 75.2013, 78.0998, 79.7101, 81.4815, 83.4138, 85.8293, 87.7617]
    luEx2Cen = [295.075, 295.126, 292.055, 292.126, 298.539, 355.605, 374.701, 403.267, 403.333, 406.568, 409.803, 454.226, 511.373, 578.04, 644.707, 739.879, 806.531, 847.796, 942.901, 1022.17, 1117.28, 1285.26, 1412.06, 1427.96, 1440.67, 1443.89, 1447.13, 1447.17, 1456.75, 1520.17, 1593.1, 1621.67, 1634.41, 1643.97, 1634.55, 1583.91, 1479.41, 1425.61, 1241.93, 1235.65]
    luEx1Time1 = [0, 2.0934, 4.50886, 5.95813, 8.05153, 10.306, 12.0773, 14.0097, 16.1031, 18.0354, 19.9678, 22.0612, 24.1546, 25.7649, 28.0193, 29.9517, 32.0451, 33.9775, 36.2319, 38.0032, 40.0966, 42.351, 43.8003, 46.0548, 47.6651, 50.0805, 52.0129, 54.1063, 55.8776, 57.971, 60.0644, 61.9968, 65.7005, 67.7939, 70.0483, 71.8196, 74.0741, 76.0064, 77.7778, 79.5491, 81.8035, 83.5749, 85.6683, 87.9227, 89.694]
    luEx1Sur = [298.213, 333.136, 355.39, 406.129, 586.79, 770.624, 894.244, 973.513, 1002.09, 1052.85, 1116.28, 1189.21, 1239.97, 1262.2, 1287.62, 1300.35, 1452.5, 1376.52, 1408.28, 1427.34, 1430.58, 1595.4, 1611.29, 1636.71, 1652.6, 1617.82, 1598.88, 1579.93, 1630.68, 1570.55, 1583.29, 1592.86, 1611.98, 1624.72, 1624.79, 1628.02, 1621.75, 1615.48, 1580.68, 1441.33, 1466.75, 1276.71, 1251.43, 1238.83, 1232.54]
    luEx2Time1 = [0.161031, 1.93237, 4.02576, 5.95813, 8.05153, 9.82287, 11.7552, 13.8486, 15.781, 18.0354, 19.8068, 21.9002, 23.6715, 25.7649, 27.6973, 29.7907, 31.8841, 33.9775, 35.7488, 38.3253, 39.6135, 41.7069, 43.8003, 45.8937, 47.8261, 49.7585, 51.6908, 53.7842, 55.8776, 57.649, 59.5813, 61.6747, 63.7681, 65.8615, 67.4718, 69.4042, 71.6586, 73.913, 75.5233, 77.6167, 79.5491, 81.4815, 83.7359, 85.5072, 87.6006, 90.0161]
    luEx2Sur = [301.391, 336.299, 339.533, 358.605, 384.017, 631.202, 1131.86, 1398.06, 1410.8, 1426.71, 1426.77, 1477.53, 1528.27, 1537.85, 1575.93, 1601.34, 1576.06, 1572.96, 1550.84, 1544.58, 1535.12, 1541.52, 1563.76, 1560.66, 1582.9, 1563.95, 1532.33, 1503.88, 1456.42, 1453.31, 1409.02, 1390.07, 1377.47, 1456.74, 1355.41, 1311.11, 1289, 1295.41, 1381.01, 1317.71, 1295.59, 1276.64, 1264.04, 1257.76, 1254.66, 1254.73]

 
    #EXP Mass    
    luEx1Time3 = [1.30933, 3.10966, 4.90998, 6.54664, 7.85597, 9.6563, 11.293, 13.0933, 14.4026, 16.2029, 19.1489, 22.4223, 25.6956, 28.6416, 32.0786, 34.6972, 38.2979, 41.7349, 45.3355, 47.9542, 51.7185, 54.6645, 57.1195, 59.9018, 63.3388, 67.7578, 70.3764, 72.8314, 76.7594, 82.8151, 89.0344, 91.653]
    luEx1mass = [0.00400802, 0.0240481, 0.0781563, 0.134269, 0.164329, 0.204409, 0.220441, 0.282565, 0.340681, 0.372745, 0.460922, 0.53507, 0.593186, 0.653307, 0.711423, 0.765531, 0.799599, 0.831663, 0.865731, 0.893788, 0.917836, 0.945892, 0.953908, 0.961924, 0.965932, 0.971944, 0.981964, 0.993988, 0.993988, 1, 1, 0.997996]
    luEx2Time3 = [1.63666, 2.94599, 6.21931, 9.49264, 14.5663, 16.0393, 19.3126, 20.6219, 22.5859, 28.8052, 33.7152, 38.2979, 44.6809, 51.3912, 53.6825, 57.9378, 62.0295, 66.1211, 68.7398, 73.6498, 76.4321, 81.8331, 86.743, 90.3437]
    luEx2mass = [0.00400802, 0.0440882, 0.140281, 0.236473, 0.376754, 0.436874, 0.509018, 0.533066, 0.591182, 0.713427, 0.777555, 0.839679, 0.893788, 0.941884, 0.961924, 0.965932, 0.971944, 0.971944, 0.973948, 0.987976, 0.98998, 0.993988, 0.993988, 0.98998]

    dluEx2Time3 = [1.4363, 3.27519, 4.91705, 6.56532, 7.79659, 9.44059, 11.2934, 12.7323, 15.819, 21.1563, 25.8785, 30.8057, 34.0867, 37.1628, 42.2843, 46.9995, 50.2747, 51.915, 53.9605, 54.9873, 58.4653, 60.3074, 62.9702, 66.4483, 79.5368]
    dluEx2mass = [0.0234987, 0.0156658, 0.0443864, 0.104439, 0.125326, 0.164491, 0.224543, 0.261097, 0.355091, 0.454308, 0.545692, 0.639687, 0.684073, 0.725849, 0.770235, 0.827676, 0.843342, 0.86423, 0.866841, 0.887728, 0.895561, 0.903394, 0.924282, 0.932115, 0.934726]
    dluEx1Time3 = [1.63973, 4.50805, 5.75053, 7.59796, 9.04548, 11.9234, 17.2655, 21.7901, 23.4271, 28.3527, 31.4266, 33.2778, 40.0396, 41.2709, 43.113, 47.8287, 49.8743, 51.1039, 54.1741, 55.8127, 59.2908, 62.3663, 71.9783, 73.4125, 75.4542, 84.8617]
    dluEx1mass = [0.0182768, 0.0443864, 0.120104, 0.154047, 0.232376, 0.305483, 0.428198, 0.553525, 0.558747, 0.644909, 0.67624, 0.72846, 0.793734, 0.814621, 0.822454, 0.882507, 0.885117, 0.898172, 0.911227, 0.924282, 0.932115, 0.971279, 0.97389, 0.986945, 0.971279, 0.97389]
    
    f, axarr = plt.subplots(1,2,figsize=(144/25.4,67/25.4),dpi=400)   
    #f.suptitle('Pyrolysis Wurzenberger exp. 20% MC, d=2 cm, T_gas=T_wall=1098 K', fontweight='bold')
    
    a0,=axarr[0].plot(time, temperatureB,color=sns.color_palette()[0],label='Mesh code',zorder=20)             
    axarr[0].plot(time, temperatureC,color=sns.color_palette()[0],zorder=20)
    a,=axarr[0].plot(luEx1Time1, luEx1Sur, 'o',color=sns.color_palette()[3],label='Experiment 1',markersize=3,zorder=0, markerfacecolor='none')
    aa,=axarr[0].plot(luEx2Time1, luEx2Sur, 's',color=sns.color_palette()[3],label='Experiment 2',markersize=3,zorder=0, markerfacecolor='none')
    axarr[0].plot(luEx1Time2, luEx1Cen, 'o',color=sns.color_palette()[3],markersize=3,zorder=0, markerfacecolor='none')
    axarr[0].plot(luEx2Time2, luEx2Cen, 's',color=sns.color_palette()[3],markersize=3,zorder=0, markerfacecolor='none')
    axarr[0].set_xlabel('Time (s)')
    axarr[0].set_ylabel('Temperature (K)')   
    axarr[0].text(7, 1300, 'Surface',fontsize=9,zorder=30)
    axarr[0].text(36, 400, 'Center',fontsize=9,zorder=30)
    axarr[0].set_xlim([0, 100])
    axarr[0].set_xticks([0, 20, 40, 60, 80, 100])
    axarr[0].set_ylim([300, 1800])
    axarr[0].set_yticks([300, 600, 900, 1200, 1500, 1800])
    axarr[0].text(0.07, 0.93,'(a)', ha='center', va='center', transform=axarr[0].transAxes)
    axarr[0].tick_params('both',direction='in',right='on', top='on',width=1)
    axarr[0].xaxis.set_minor_locator(matplotlib.ticker.AutoMinorLocator())
    axarr[0].tick_params('x', which='minor', direction='in',top='on')
    axarr[0].yaxis.set_minor_locator(matplotlib.ticker.AutoMinorLocator())
    axarr[0].tick_params('y', which='minor', direction='in',right='on')
    #legend = axarr[0].legend(bbox_to_anchor=(0.3, 1.01), loc=3, ncol=2)
    #legend = axarr[0].legend(bbox_to_anchor=(0.005, 1.0), loc=3, ncol=2)
    #frame = legend.get_frame()
    #frame.set_facecolor('1')
    for axis in ['top','bottom','left','right']:
        axarr[0].spines[axis].set_linewidth(1)
        
        
    axarr[1].plot(time, particleMass,color=sns.color_palette()[0],label='Mesh code')
    axarr[1].plot(luEx1Time3, luEx1mass, 'o',color=sns.color_palette()[3],label='Experiment 1',markersize=3, markerfacecolor='none')  
    axarr[1].plot(luEx2Time3, luEx2mass, 's',color=sns.color_palette()[3],label='Experiment 2',markersize=3, markerfacecolor='none')  
    axarr[1].set_xlabel('Time (s)')
    axarr[1].set_ylabel('Mass loss ratio (-)') 
    axarr[1].set_xlim([0, 100])
    axarr[1].set_xticks([0, 20, 40, 60, 80, 100])
    axarr[1].set_ylim([0, 1])
    axarr[1].tick_params('both',direction='in',right='on', top='on',width=1)
    axarr[1].text(0.07, 0.93,'(b)', ha='center', va='center', transform=axarr[1].transAxes)
    axarr[1].xaxis.set_minor_locator(matplotlib.ticker.AutoMinorLocator())
    axarr[1].tick_params('x', which='minor', direction='in',top='on')
    axarr[1].yaxis.set_minor_locator(matplotlib.ticker.AutoMinorLocator())
    axarr[1].tick_params('y', which='minor', direction='in',right='on')
    for axis in ['top','bottom','left','right']:
        axarr[1].spines[axis].set_linewidth(1)
    plt.legend(loc='lower right',ncol=1,fontsize=9,frameon=False)
    #plt.legend(loc='upper center', bbox_to_anchor=(0.5, -0.05),ncol=3)
    plt.tight_layout(pad=0.4)
    #plt.gcf().subplots_adjust(bottom=0.17,top=0.77, left=0.14, right=0.97) 
    plt.savefig('figure.png')
     
    
    
if __name__ == '__main__':
    main()