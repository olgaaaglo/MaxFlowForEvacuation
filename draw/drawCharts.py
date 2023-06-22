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

plt.bar(times, people, width=3)
for i in range(len(people)):
    plt.annotate(str(people[i]), xy=(times[i],people[i]), ha='center', va='bottom')
plt.xlabel("Liczba sekund")
plt.ylabel("Liczba ludzi ewakuowanych")
plt.savefig('../charts/peopleEvacuatedInTimeUnit.png')
plt.clf()

plt.bar(times, cumulatedPeople, width=3)
for i in range(len(cumulatedPeople)):
    plt.annotate(str(cumulatedPeople[i]), xy=(times[i],cumulatedPeople[i]), ha='center', va='bottom')
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
for i in range(len(people)):
    plt.annotate(str(people[i]), xy=(labels[i],people[i]), ha='center', va='bottom')
plt.xlabel("Wyjścia ewakuacyjne")
plt.ylabel("Liczba ludzi ewakuowanych")
plt.savefig('../charts/nrPeopleInEachExit.png')
plt.clf()

#################################

people = []
times = []
with open('../out/pplVsTime.txt') as file:
    for line in file:
        splited = line.split(' ')
        people.append(int(splited[0]))
        times.append(int(splited[1]))

plt.bar(people, times, width=4)
for i in range(len(people)):
    plt.annotate(str(times[i]) + " - " + str(people[i]), xy=(people[i],times[i]), ha='center', va='bottom', fontsize=6)
plt.xlabel("Początkowa liczba osób")
plt.ylabel("Czas ewakuacji")
plt.savefig('../charts/pplVsTime.png')
plt.clf()