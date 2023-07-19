import pymorphy2 as pm
import string

morph = pm.MorphAnalyzer(lang='ru')

with open('/home/xander/Documents/source1/cpp/andanj/hepler/orig.txt', 'r') as filein:
    with open('/home/xander/Documents/source1/cpp/andanj/hepler/new.txt', 'w') as fileout:
        for line in filein:
            if line != "\n":
                line = line.lower()
                line ="".join(c for c in line if (c.isalpha() or c == " "))
                line = list(line.split(" "))
                for word in range(len(line)):
                    p = morph.parse(line[word])[0]
                    line[word] = str(p.normal_form)

                line = ' '.join(line)

                fileout.write(line)
                fileout.write("\n")

