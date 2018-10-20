import os
import sys
import matplotlib as mpl
#mpl.use('Agg')
import matplotlib.pyplot as plot

def make_plot(data):
	#x = range(len(data))
	x = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 220, 240, 280, 300, 350]
	fig = plot.figure(figsize=(15,5))
	print "values x: %s" % x
	print " "
	print "x: %s" % len(x)
	print "data: %s" % len(data)
	axes = fig.add_subplot(111)
	#axes.plot(x, data, linewidth=2, color='b')
	#axes.plot(x, data, 'ro')
	axes.bar(x, data, width=1, edgecolor='White', alpha=0.8, color='b')
	axes.set_xlabel("Window Size")
	plot.axis((0,360,0,0.015))
	#axes.grid()
	axes.set_ylabel("Potency")
	#axes.margins(0.2)
	#plot.legend(loc="upper left")
	#plot.savefig("exerciseA/plot.png")
	plot.savefig("plot.png")

def make_plot_zoom(data_zoom):
        x = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 30, 40]
	fig = plot.figure(figsize=(15,5))
        print "values x: %s" % x
        print " "
        print "x: %s" % len(x)
        print "data: %s" % len(data_zoom)
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
	    #print "Throughput: %s" % teste[0]
	    #print "Delay: %s" % teste[1]
	    p = round((float(teste[0]) / float(teste[1])),4)
	    potency = float("{0:.4f}".format(p))
	    #print "Potency: %s" % p
	    data.append(potency)
	#print "Lines %s" % texto
	print "Data: %s" % data
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
            	#print "Throughput: %s" % teste[0]
            	#print "Delay: %s" % teste[1]
            	p = round((float(part[0]) / float(part[1])),4)
            	potency = float("{0:.4f}".format(p))
            	#print "Potency: %s" % p
            	data.append(potency)
	    i = i+1
        #print "Lines %s" % texto
        print "Data: %s" % data
        f.close()
        return data


def main():
	#print "Iniciou"
	#x = range(10)
	#print "x: %s" % x
	data = read_all_file()
	#data_zoom = [0.0021, 0.0042, 0.0065, 0.0081, 0.0098, 0.0109, 0.0117, 0.0122, 0.0125, 0.0126, 0.0128, 0.013, 0.0129, 0.0128, 0.0126, 0.0125, 0.0123, 0.0122, 0.012, 0.0119, 0.0102, 0.009]
	
	data_zoom = read_zoom_file()
	print "Data len: %s" % len(data_zoom)
	make_plot(data)
	make_plot_zoom(data_zoom)

if __name__ == "__main__":
	main()
