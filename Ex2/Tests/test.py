import random
import sys
import collections

commandStr = ["addTrainingGroup", "addGladiator",
              "trainingGroupFight", "getMinTrainingGroup"]

SUCCESS = "SUCCESS"
FAILURE = "FAILURE"
INVALID_INPUT = "INVALID_INPUT"

GroupID = dict()
GladiatorsID = dict()
GroupScore = collections.defaultdict(list)
GladiatorsGroup = dict()
LosingGroups = set()

groups_count = 0;
gladiators_count = 0;


def initline():
    global GroupID, groups_count
    inLine = "init 2 0 1"
    outLine = "init done."
    GroupID[0] = {}
    GroupID[1] = {}
    groups_count += 2
    return inLine, outLine


# addTrainingGroup trainingGroupID
def addTrainingGroup():
    global GroupID, groups_count
    trainingGroupID = random.randint(-2, 8)
    inLine = "addTrainingGroup %d" % (trainingGroupID)
    outLine = "addTrainingGroup: "
    if trainingGroupID < 0:
        outLine += INVALID_INPUT
    elif trainingGroupID in GroupID.keys():
        outLine += FAILURE
    else:
        GroupID[trainingGroupID] = {}
        groups_count += 1
        outLine += SUCCESS
    return inLine, outLine

# addGladiator gladiatorID score trainingGroupID
def addGladiator():
    global GladiatorsID, GroupID, GroupScore, GladiatorsGroup, gladiators_count
    gladiatorID = random.randint(-10, 1000)
    score = random.randint(-10, 1000)
    trainingGroupID = random.randint(-2, 8)
    inLine = "addGladiator %d %d %d" % (gladiatorID, score, trainingGroupID)
    outLine = "addGladiator: "
    if gladiatorID < 0 or trainingGroupID < 0 or score <0:
        outLine += INVALID_INPUT
    elif gladiatorID in GladiatorsID.keys() or trainingGroupID not in GroupID.keys():
        outLine += FAILURE
    else:
        GladiatorsID[gladiatorID] = gladiatorID
        if trainingGroupID in GroupScore.keys():
            GroupScore[trainingGroupID].append(score)
        else:
            GroupScore[trainingGroupID] = [score]
        GladiatorsGroup[gladiatorID] = trainingGroupID
        GroupID[trainingGroupID][gladiatorID] = (GladiatorsID[gladiatorID], trainingGroupID)
        gladiators_count += 1
        outLine += SUCCESS
    return inLine, outLine

# getMinTrainingGroup
def getMinTrainingGroup():
    global GroupID, LosingGroups
    inLine = "getMinTrainingGroup"
    outLine = "getMinTrainingGroup: "
    for group_id in sorted(GroupID):
        if group_id not in LosingGroups:
            outLine += SUCCESS + " %d" % group_id
            break			
    return inLine, outLine

def sum_n_strongest(group, num):
    sortedGroup = sorted(group, reverse=True)
    topNum = sortedGroup[:num]
    Sum = 0
    for element in topNum:
        Sum += element
    return Sum
	
    # trainingGroupFight trainingGroup1 trainingGroup2 k1 k2
def trainingGroupFight():
    global GroupID, GroupScore, LosingGroups
    trainingGroup1 = random.randint(-1, 8)
    trainingGroup2 = random.randint(-1, 8)
    k1 = random.randint(-1, 10)
    k2 = random.randint(-1, 10)
    inLine = "trainingGroupFight %d %d %d %d" % (trainingGroup1, trainingGroup2, k1, k2)
    outLine = "trainingGroupFight: "
    if k1 <= 0 or k2 <= 0 or trainingGroup1 < 0 or trainingGroup2 < 0:
        outLine += INVALID_INPUT
    elif trainingGroup1 not in GroupID.keys() or trainingGroup2 not in GroupID.keys() or trainingGroup1 == trainingGroup2 or len(GroupID[trainingGroup1]) < k1 or len(GroupID[trainingGroup2]) < k2:
        outLine += FAILURE
    elif trainingGroup1 in LosingGroups or trainingGroup2 in LosingGroups:
        outLine += FAILURE
    else:
        sum1 = sum_n_strongest(GroupScore[trainingGroup1], k1)
        sum2 = sum_n_strongest(GroupScore[trainingGroup2], k2)
        if sum1 == sum2:
            if trainingGroup1 < trainingGroup2:
                LosingGroups.add(trainingGroup2)
            else:
                LosingGroups.add(trainingGroup1)
        elif sum1 < sum2:
            LosingGroups.add(trainingGroup1)
        else:
            LosingGroups.add(trainingGroup2)
        outLine += SUCCESS
    return inLine, outLine
    
def main():
    if len(sys.argv) < 3:
        print("Usage %s <lines>" % sys.argv[0])
        exit(0)
    lines = int(sys.argv[1])
    infname = "%s.in" % sys.argv[2]
    outfname = "%s.out" % sys.argv[2]
    functions = [addTrainingGroup, addGladiator,
                 getMinTrainingGroup, trainingGroupFight]
    with open(infname, 'wb') as infhandler:
        with open(outfname, 'wb') as outfhandler:
            inLine, outLine = initline()
            infhandler.write(inLine + "\n")
            outfhandler.write(outLine + "\n")
            while lines > 0:
                f = random.randint(0, len(functions)-1)
                func = functions[f]
                inLine, outLine = func()
                if inLine is not "":
                    infhandler.write(inLine + "\n")
                    outfhandler.write(outLine + "\n")
                    lines -= 1
            infhandler.write("quit\n")
            outfhandler.write("quit done.\n")


main()