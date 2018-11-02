import os
import sys
import matplotlib.pyplot as plot
from matplotlib import colors as mcolors

def make_plot(data):
	x = [50, 55, 60, 65, 70]
	#x = [50, 60]
	fig = plot.figure(figsize=(15,5))
	axes = fig.add_subplot(111)
	axes.bar(x, data, width=1, edgecolor='White', alpha=0.8, color='#086A87')
	for i in range(len(x)):
		axes.text(x[i] - 0.1, data[i] + 0.4, truncate(data[i], 2), fontsize=12, color='#086A87')
	axes.set_xlabel("Timeout (ms)")
	plot.axis((45,75,0,50.0))
	axes.set_ylabel("Potencia (Taxa de Transferencia / Atraso")
	plot.savefig("plot_timeout.png")

def truncate(f, n):
    '''Truncates/pads a float f to n decimal places without rounding'''
    s = '%.12f' % f
    i, p, d = s.partition('.')
    return '.'.join([i, (d+'0'*n)[:n]])

def read_all_file():
	data = []
	f = open('output.txt', 'r')
	texto = f.readlines()
	for linha in texto :
	    teste = linha.split(" ")
	    p = round((float(teste[0]) / float(teste[1]))*1000,4)
	    potency = float("{0:.4f}".format(p))
	    data.append(potency)
	f.close()
	return data


def main():
	data = read_all_file()
	make_plot(data)


if __name__ == "__main__":
	main()
