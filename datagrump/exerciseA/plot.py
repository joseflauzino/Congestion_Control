import os
import sys
import matplotlib.pyplot as plot

def make_plot(data):
	x = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 220, 240, 280, 300, 350]
	fig = plot.figure(figsize=(15,5))
	axes = fig.add_subplot(111)
	axes.bar(x, data, width=1, edgecolor='White', alpha=0.8, color='b')
	axes.set_xlabel("Window Size")
	plot.axis((0,360,0,0.015))
	axes.set_ylabel("Potency")
	plot.savefig("plot.png")

def make_plot_zoom(data_zoom):
        x = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 30, 40]
	fig = plot.figure(figsize=(15,5))
        axes = fig.add_subplot(111)
        axes.bar(x, data_zoom, width=0.8, edgecolor='White', alpha=0.6, color='b')
        axes.set_xlabel("Window Size")
        plot.axis((0,35,0,0.015))
        axes.set_ylabel("Potency")
        plot.savefig("plot_zoom.png")

def read_all_file():
	data = []
	#f = open('exerciseA/output.txt', 'r')
	f = open('output.txt', 'r')
	texto = f.readlines()
	for linha in texto :
	    teste = linha.split(" ")
	    p = round((float(teste[0]) / float(teste[1])),4)
	    potency = float("{0:.4f}".format(p))
	    data.append(potency)
	f.close()
	return data

def read_zoom_file():
        data = []
        #f = open('exerciseA/output.txt', 'r')
        f = open('output.txt', 'r')
        text = f.readlines()
	i = 1
        for line in text :
            if i <= 22:
	    	part = line.split(" ")
            	p = round((float(part[0]) / float(part[1])),4)
            	potency = float("{0:.4f}".format(p))
            	data.append(potency)
	    i = i+1
        f.close()
        return data

def main():
	data = read_all_file()
	data_zoom = read_zoom_file()
	make_plot(data)
	make_plot_zoom(data_zoom)

if __name__ == "__main__":
	main()
