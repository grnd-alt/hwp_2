from asyncio.windows_events import NULL
from fileinput import filename
import matplotlib.pyplot as plt
from numpy import linspace

def plotXY(filename):
    with open(filename) as file:
        x = []
        y = []
        lines = file.readlines()
        for line in lines:
            x.append(line.split(";")[0])
            y.append(line.split(";")[1])
        plt.plot(x,y)
def plotXYtogether(filename1,filename2):
    t = linspace(0,5,24)
    with open(filename1) as file:
        x = []
        y1 = []
        lines = file.readlines()
        for line in lines:
            x.append(line.split(";")[0])
            y1.append(float(line.split(";")[1].replace('\n','')))
        with open(filename2) as file2:
            y2 = []
            lines2 = file2.readlines()
            for line2 in lines2:
                y2.append(float(line2.split(";")[1]))
            plt.plot(t,y1)
            plt.plot(t,y2)
            plt.show()
def loadColFromFile(filename,col):
    with open(filename) as file:
        y = []
        lines = file.readlines()
        for line in lines:
            y.append(float(line.split(";")[col].replace("\n","")))
        return y
def plotXYfrom3(filename):
    t = linspace(0,5,129)
    y = loadColFromFile(filename,2)
    plt.plot(t,y)
    plt.show()
def plotAllXYfrom3(filenames):
    # plt.xscale("log")
    plt.grid()
    # plt.clf()
    t = linspace(0,5,128)
    graphs = []
    i = 0.8
    for name in filenames:
        t = loadColFromFile(name,0)
        graphs.append(loadColFromFile(name,1))
        plt.plot(t,graphs[-1],label=name)
    plt.legend()
    plt.show()
if __name__ == "__main__":
    plotAllXYfrom3([
        './hwp_2/5.3/data_3.txt',
        './hwp_2/5.3/data_4.txt',
        './hwp_2/5.3/data_5.txt',
        './hwp_2/5.3/data_d1.txt', #d2 = d1 && 4 = D4 COLLECT NEW DATA!!!
        './hwp_2/5.3/data_d2.txt', 
        './hwp_2/5.3/data_D4.txt'
        ]) 