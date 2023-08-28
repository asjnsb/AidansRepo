import os

dir = "D:/Roms/NGP/" 

for i in os.listdir(dir):
    pre=""
    #print(i)
    for x in i:
        if ("." in x):
            pre += x
            break
        pre += x
    newName = dir + i.replace(pre, "")
    oldName = dir + i
    try:
        os.rename(oldName,newName)
        #print(oldName + " -> " + newName)
    except Exception as e:
        print(f"An exception occurred: {str(e)}")
        continue