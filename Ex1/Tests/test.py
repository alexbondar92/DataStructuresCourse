import random
import sys

commandStr = ["AddTrainer", "BuyGladiator", "UpdateLevels",
              "FreeGladiator", "UpgradeGladiator", "LevelUp"
              "GetTopGladiator", "GetAllGladiatorsByLevel"]

SUCCESS = "SUCCESS"
FAILURE = "FAILURE"
INVALID_INPUT = "INVALID_INPUT"

TrainersID = dict()
GladiatorsID = dict()
GladiatorsLevel = dict()
GladiatorsTrainer = dict()

size = 0
trainers_count = 0;
gladiators_count = 0;


def initline():
    global size, GladiatorsLevel, GladiatorsID
    inLine = "Init"
    outLine = "Init done."
    return inLine, outLine


# AddTrainer trainer_id
def AddTrainer():
    global TrainersID, trainers_count
    trainer_id = random.randint(-3, 5)
    inLine = "AddTrainer %d" % (trainer_id)
    outLine = "AddTrainer: "
    if trainer_id <= 0:
        outLine += INVALID_INPUT
    elif trainer_id in TrainersID.keys():
        outLine += FAILURE
    else:
        TrainersID[trainer_id] = {}
        trainers_count += 1
        outLine += SUCCESS
    return inLine, outLine

# BuyGladiator gladiator_id trainer_id level 
def BuyGladiator():
    global GladiatorsID, TrainersID, GladiatorsLevel, GladiatorsTrainer, gladiators_count
    gladiator_id = random.randint(-10, 900)
    trainer_id = random.randint(-3, 5)
    level = random.randint(-5, 10)
    inLine = "BuyGladiator %d %d %d" % (gladiator_id, trainer_id, level)
    outLine = "BuyGladiator: "
    if gladiator_id <= 0 or trainer_id <= 0 or level <=0:
        outLine += INVALID_INPUT
    elif gladiator_id in GladiatorsID.keys() or trainer_id not in TrainersID.keys():
        outLine += FAILURE
    else:
        GladiatorsID[gladiator_id] = gladiator_id
        GladiatorsLevel[gladiator_id] = level
        GladiatorsTrainer[gladiator_id] = trainer_id
        TrainersID[trainer_id][gladiator_id] = (GladiatorsID[gladiator_id], trainer_id, GladiatorsLevel[gladiator_id])
        gladiators_count += 1
        outLine += SUCCESS
    return inLine, outLine

# FreeGladiator gladiator_id
def FreeGladiator():
    global GladiatorsID, TrainersID, GladiatorsLevel, gladiators_count
    gladiator_id = random.randint(-10, 900)
    inLine = "FreeGladiator %d" % gladiator_id
    outLine = "FreeGladiator: "
    if gladiator_id <= 0 :
        outLine +=INVALID_INPUT
    elif gladiator_id not in GladiatorsID.keys():
        outLine += FAILURE
    else:
        GladiatorsID.pop(gladiator_id, None)
        TrainersID[GladiatorsTrainer[gladiator_id]].pop(gladiator_id, None)
        GladiatorsLevel.pop(gladiator_id, None)
        outLine += SUCCESS
    return inLine, outLine
    
    # GetTopGladiator trainer_id
def GetTopGladiator():
    global TrainersID, GladiatorsLevel
    trainer_id = random.randint(-3, 5)
    inLine = "GetTopGladiator: %d" % trainer_id
    outLine = ""
    if trainer_id == 0 :
        outLine += "GetTopGladiator: " + INVALID_INPUT
    elif trainer_id < 0:
        if any(GladiatorsID):
            #max_power = GladiatorsLevel[max(GladiatorsLevel)] #biggest_id
            all_gladiators = sorted(GladiatorsLevel.items() ,key = lambda (k,v):k)
            all_gladiators.sort(key = lambda (k,v) : v, reverse = True)
            #min_power_gladiator_id = (sorted((dict(filter(lambda (k,v): v == max_power, GladiatorsLevel.items()))).items(), lambda (k,v) : k, reverse = True))[0][0]
            outLine += "Gladiator with highest level is: " + "%d" % all_gladiators[0][0]
        else:
            outLine += "Gladiator with highest level is: " + "-1"
    elif trainer_id in TrainersID.keys():
        if any(TrainersID[trainer_id]):
            gladiators_of_trainer = sorted(TrainersID[trainer_id].items() ,key = lambda x:(x[1][0]))
            gladiators_of_trainer.sort(key = lambda x:(x[1][2]), reverse = True)
            #max_power = max(TrainersID[trainer_id].items(), key = lambda (k,v) :v[2])[1][2]
            #min_power_gladiator_id = (sorted((dict(filter(lambda (k,v): v[2] == max_power, TrainersID[trainer_id].items()))).items(), lambda (k,v) : k, reverse = True))[0][0]
            outLine += "Gladiator with highest level is: " + "%d" %  gladiators_of_trainer[0][0]
        else: 
            outLine += "Gladiator with highest level is: " + "-1"
    else:
        outLine += "GetTopGladiator: " + FAILURE
    return inLine, outLine

def natural_numbers():
    n = 0
    while True:
        n += 1
        yield n    
    
    # GetAllGladiatorsByLevel trainer_id
def GetAllGladiatorsByLevel():
    global TrainersID, GladiatorsLevel
    trainer_id = random.randint(-3, 5)
    gen = natural_numbers()
    inLine = "GetAllGladiatorsByLevel %d" % trainer_id
    outLine = ""
    if trainer_id == 0:
        outLine += "GetAllGladiatorsByLevel: " + INVALID_INPUT
    elif trainer_id < 0:
           all_gladiators = sorted(GladiatorsLevel.items() ,key = lambda (k,v):k)
           all_gladiators.sort(key = lambda (k,v) : v, reverse = True)
           gen = natural_numbers()
           first = 1
           for gladiator in all_gladiators:
                if first == 1:
                    outLine += "Level\t||\tGladiator\n"
                first = 0
                i = gen.next()
                outLine += "%d\t||\t%d\n" %  (i,gladiator[0])
           outLine += "and there are no more gladiators!"
    elif trainer_id in TrainersID.keys():
           gladiators_of_trainer = sorted(TrainersID[trainer_id].items() ,key = lambda x:(x[1][0]))
           gladiators_of_trainer.sort(key = lambda x:(x[1][2]), reverse = True)
           first = 1
           for gladiator in gladiators_of_trainer:
                if first == 1:
                    outLine += "Level\t||\tGladiator\n"
                first = 0
                i = gen.next()
                outLine += "%d\t||\t%d\n" %  (i,gladiator[0])
           outLine += "and there are no more gladiators!"
    else:
        outLine += "GetAllGladiatorsByLevel: " + "FAILURE"
    return inLine, outLine

# UpgradeGladiator gladiator_id upgraded_id
def UpgradeGladiator():
    global GladiatorsID, GladiatorsLevel, GladiatorsTrainer, gladiators_count
    gladiator_id = random.randint(1, 900)
    upgraded_id = random.randint(-10, 1500)
    inLine = "UpgradeGladiator %d %d" % (gladiator_id ,upgraded_id)
    outLine = "UpgradeGladiator: "
    if gladiator_id <= 0 or  upgraded_id <= 0:
        outLine +=INVALID_INPUT
    elif gladiator_id not in GladiatorsID.keys() or gladiator_id == upgraded_id or upgraded_id in GladiatorsID.keys():
        outLine += FAILURE
    else:
        level = GladiatorsLevel[gladiator_id]
        trainer = GladiatorsTrainer[gladiator_id]
        GladiatorsID.pop(gladiator_id, None)
        TrainersID[GladiatorsTrainer[gladiator_id]].pop(gladiator_id, None)
        GladiatorsLevel.pop(gladiator_id, None)
        GladiatorsID[upgraded_id] = upgraded_id
        GladiatorsLevel[upgraded_id] = level
        GladiatorsTrainer[upgraded_id] = trainer
        TrainersID[trainer][upgraded_id] = (GladiatorsID[upgraded_id], trainer, GladiatorsLevel[upgraded_id])
        outLine += SUCCESS
    return inLine, outLine

# LevelUp gladiator_id level_increase 
def LevelUp():
    global GladiatorsID, GladiatorsLevel, gladiators_count
    gladiator_id = random.randint(-1, 1000)
    level_increase = random.randint(-10, 7)
    inLine = "LevelUp %d %d" % (gladiator_id, level_increase)
    outLine = "LevelUp: "
    if gladiator_id <= 0 or level_increase <= 0:
        outLine += INVALID_INPUT
    elif gladiator_id not in GladiatorsID.keys():
        outLine += FAILURE
    else:
        level = GladiatorsLevel[gladiator_id] + level_increase
        GladiatorsLevel[gladiator_id] = level
        trainer_id = GladiatorsTrainer[gladiator_id]
        TrainersID[trainer_id][gladiator_id] = (gladiator_id, trainer_id, level)
        outLine += SUCCESS
    return inLine, outLine

    # UpdateLevels stimulantCode stimulantFactor
def UpdateLevels():
    global TrainersID, GladiatorsLevel, GladiatorsTrainer
    stimulantCode = random.randint(89,1072)
    stimulantFactor = random.randint(-100, 4)
    inLine = "UpdateLevels %d %d" % (stimulantCode, stimulantFactor)
    outLine = "UpdateLevels: "
    if stimulantCode < 1 or stimulantFactor < 1:
        outLine += INVALID_INPUT
    else:
        for (gladiator_id, student_level) in GladiatorsLevel.items():
            if (gladiator_id % stimulantCode)==0:
                GladiatorsLevel[gladiator_id] *= stimulantFactor
                if GladiatorsTrainer[gladiator_id] > 0 :
                    TrainersID[GladiatorsTrainer[gladiator_id]][gladiator_id] = (TrainersID[GladiatorsTrainer[gladiator_id]][gladiator_id][0], TrainersID[GladiatorsTrainer[gladiator_id]][gladiator_id][1] * stimulantFactor, TrainersID[GladiatorsTrainer[gladiator_id]][gladiator_id][2] * stimulantFactor)
        outLine += SUCCESS
    return inLine, outLine
    
def main():
    if len(sys.argv) < 3:
        print "Usage %s <lines>" % sys.argv[0]
        exit(0)
    lines = int(sys.argv[1])
    infname = "%s.in" % sys.argv[2]
    outfname = "%s.out" % sys.argv[2]
    functions = [AddTrainer, BuyGladiator, FreeGladiator, UpgradeGladiator,
                 LevelUp, GetTopGladiator, GetAllGladiatorsByLevel, UpdateLevels]
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
            infhandler.write("Quit\n")
            outfhandler.write("Quit done.\n")


main()
