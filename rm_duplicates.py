file = open("out.txt", "w")
count = 0
with open("data.txt") as f:
    for line in f:
        count += 1
        if(count > 10):
            line = line.split(",")
            dup_dict = {}

            for i in line:
                dup_dict[str(i)] = [0, False]

            for i in line:
                if(i in dup_dict):
                    dup_dict[str(i)][0] = dup_dict[str(i)][0] + 1


            out = ""
            for i in line:
                if(i in dup_dict):
                    if(dup_dict[str(i)][0] == 1):
                        out += i + ","
                    elif(dup_dict[str(i)][0] > 1 and dup_dict[str(i)][1] == False):
                        dup_dict[str(i)][1] = True
                        out += i + ","
            file.write(out)
