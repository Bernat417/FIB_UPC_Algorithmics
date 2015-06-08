#! /usr/bin/env python
f1 = open('Tiempo0.txt', 'r')
f2 = open('Tiempo.txt', 'w')
i=0
total=0.0
line = f1.readline()
a = 2
b = 0
while line != "":
	total += float(line)
	if i == 9:
		i=0
		f2.write("instance_100_500_"+str(a)+"_"+str(b)+"_*.txt ")
		b+=1
		if b > 9:
			b=0
			a+=1
		f2.write(str(total/10.0))
		f2.write(' seg\n')
		total=0.0
	else:
		i+=1
	line = f1.readline()
f1.closed
f2.closed
	
