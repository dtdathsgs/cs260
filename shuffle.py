
import random
import numpy as np 


random.seed(10) # set seed for testing purpose

for test in range(1,11,1):
    test_number = random.randint(1,10000) # generate a random number of the number of nodes
    sample_list = np.arange(1,test_number + 1,1).tolist() # creat a permutation
    random.shuffle(sample_list)
    str_input = str(test_number) + " "
    for element in sample_list :
        str_input = str_input + str(element) + " " # creat a string of input to put in the test file
    f = open("test{:}".format(test),"w+")
    f.write(str_input) # dumps the input into a test file
    f.close()