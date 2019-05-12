
import subprocess



for i in range(512):
    # print(i)
    a = []

    j = 0
    for p in range(3):
        row = []
        for q in range(3):
            
            if i & (1<<j):
                row.append("#")
            else:
                row.append(".")
            j += 1
        a.append("".join(row))
    
    # print(a)
    
    f= open("data.in","w+")

    f.write("1\n3 3\n")
    for r in a:
        f.write("%s\n" % r)
    
    f.close()

    if subprocess.call(["g++", "-std=c++17", "solution.cpp"]) == 0:
        # print("worked")
        returned_output = subprocess.call("./a.out")

    else:
        print("compiled failed 1")


    if subprocess.call(["g++", "-std=c++17", "bruteforce.cpp"]) == 0:
        # print("worked")
        returned_output = subprocess.call("./a.out")

    else:
        print("compiled failed 1")
    

    f1=open("out1.txt","r")
    f2=open("out2.txt","r")

    valid = True

    for line1, line2 in zip(f1, f2):
        if line1 != line2:
            print("did not match")
            valid = False

            for r in a:
                print(r)
            

            break


    f1.close()
    f2.close()
    
    if (valid == False):
        break


    