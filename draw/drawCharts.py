import numpy as np
import matplotlib.pyplot as plt

times = []
people = []
cumulatedPeople = []
i = 0
with open('../out/peopleEvacuatedInTimeUnit.txt') as file:
    for line in file:
        splited = line.split(' ')
        times.append(int(splited[0]))
        people.append(int(splited[1]))
        if i == 0:
            cumulatedPeople.append(people[i])
        else:
            cumulatedPeople.append(cumulatedPeople[i - 1] + people[i])
        i += 1

plt.bar(times, people)
plt.xlabel("Liczba sekund")
plt.ylabel("Liczba ludzi ewakuowanych")
plt.savefig('../charts/peopleEvacuatedInTimeUnit.png')
plt.clf()

plt.bar(times, cumulatedPeople)
plt.xlabel("Liczba sekund")
plt.ylabel("Skumulowana liczba ludzi ewakuowanych")
plt.savefig('../charts/cumulatedPeopleEvacuatedInTimeUnit.png')
plt.clf()

################################

labels = []
people = []
with open('../out/nrPeopleInEachExit.txt') as file:
    for line in file:
        splited = line.split(',')
        labels.append(splited[0])
        people.append(int(splited[1]))

plt.bar(labels, people)
plt.xlabel("Wyjścia ewakuacyjne")
plt.ylabel("Liczba ludzi ewakuowanych")
plt.savefig('../charts/nrPeopleInEachExit.png')
plt.clf()