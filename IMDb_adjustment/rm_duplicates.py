file = open("newout.txt", "w")
count = 0
with open("newin.txt") as f:
    for line in f:
        count += 1
        if(count > 10):
            line = line.split(",")
            first = line[0].split("\t")
            last_list = first + line[1:]
            dup_dict = {}
            
            for i in last_list:
                i = i.strip('\t')
                dup_dict[str(i)] = [0, False]
            
            for i in last_list:
                if(i in dup_dict):
                    dup_dict[str(i)][0] = dup_dict[str(i)][0] + 1
        
        
            out = ""
            for i in last_list:
                if(i in dup_dict):
                    if(dup_dict[str(i)][0] == 1):
                        out += i + ";"
                    elif(dup_dict[str(i)][0] > 1 and dup_dict[str(i)][1] == False):
                        dup_dict[str(i)][1] = True
                        out += i + ";"
            out = out[:-3]
            out += '\n'
            file.write(out)
