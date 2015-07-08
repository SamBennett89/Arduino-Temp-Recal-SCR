from __future__ import print_function
import csv
import re

f = open("Participant1.csv")

csv_f = csv.reader(f)

events = []

for row in csv_f:
    rowItem = row[-1]
    if rowItem.isdigit():
        rowItemInt = int(rowItem) + 2
        rowItemStr = str(rowItemInt)
        events.extend(rowItemStr)

numEvents = len(events)

print(numEvents)

print(events)
f.close()

i = 0
foundSwitch = 0

f2 = open("Participant 1.dat", 'r')
f3 = open("Participant1.dat", 'w+')

for line in f2:
    found0 = re.search(" 0 ", line)
    found1 = re.search(" 1 ", line)
    if found0 and foundSwitch == 0:
        f3.write(line.replace(" 0 ", events[i]))
        foundSwitch = 1
    elif found0 and foundSwitch == 1:
        f3.write(line.replace(" 0 ", " 1 "))
    elif found1 and foundSwitch == 1:
        foundSwitch = 0
        f3.write(line)
        i += 1
    else:
        f3.write(line)