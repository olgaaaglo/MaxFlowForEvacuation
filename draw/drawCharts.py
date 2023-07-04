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

nrPeopleInEachExitInEachTimeUnit = {}
# exitLabels = ['4 - 6', '5 - 6']
exitLabels = ['17 - 27', '21 - 27']
nrPeopleExit0 = []
nrPeopleExit1 = []

with open('../out/nrPeopleInEachExitInEachTimeUnit.txt') as file:
    for line in file:
        splited = line.split(',')
        nrPeopleInEachExitInEachTimeUnit[exitLabels[0]] = 0
        nrPeopleInEachExitInEachTimeUnit[exitLabels[1]] = 0
        for i in range(0, len(splited) - 1, 2):
            nrPeopleInEachExitInEachTimeUnit[splited[i]] = int(splited[i + 1])
        nrPeopleExit0.append(nrPeopleInEachExitInEachTimeUnit[exitLabels[0]])
        nrPeopleExit1.append(nrPeopleInEachExitInEachTimeUnit[exitLabels[1]])

# plt.bar(times, people, width=3)
plt.bar(times, nrPeopleExit0, width=3)
plt.bar(times, nrPeopleExit1, width=3, bottom=nrPeopleExit0)
for i in range(len(people)):
    # plt.annotate(str(people[i]), xy=(times[i],people[i]), ha='center', va='bottom')
    if nrPeopleExit0[i] > 0:
        plt.annotate(str(nrPeopleExit0[i]), xy=(times[i], nrPeopleExit0[i]), ha='center', va='bottom')
    if nrPeopleExit1[i] > 0:
        plt.annotate(str(nrPeopleExit1[i]), xy=(times[i], nrPeopleExit0[i] + nrPeopleExit1[i]), ha='center', va='bottom')
plt.legend(exitLabels)
plt.xlabel("Czas ewakuacji [s]")
plt.ylabel("Liczba ludzi ewakuowanych")
plt.savefig('../charts/peopleEvacuatedInTimeUnit.png')
plt.clf()

plt.bar(times, cumulatedPeople, width=3)
for i in range(len(cumulatedPeople)):
    plt.annotate(str(cumulatedPeople[i]), xy=(times[i],cumulatedPeople[i]), ha='center', va='bottom')
plt.xlabel("Czas ewakuacji [s]")
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